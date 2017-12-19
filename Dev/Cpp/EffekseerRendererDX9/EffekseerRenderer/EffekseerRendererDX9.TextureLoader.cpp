
#ifdef __EFFEKSEER_RENDERER_INTERNAL_LOADER__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------
#include <memory>
#include "EffekseerRendererDX9.RendererImplemented.h"
#include "EffekseerRendererDX9.TextureLoader.h"

#include "../../EffekseerRendererCommon/EffekseerRenderer.DXTK.DDSTextureLoader.h"
#include "../../EffekseerRendererCommon/EffekseerRenderer.PngTextureLoader.h"
#include "../../EffekseerRendererCommon/EffekseerRenderer.DDSTextureLoader.h"

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace EffekseerRendererDX9
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
TextureLoader::TextureLoader(LPDIRECT3DDEVICE9 device, ::Effekseer::FileInterface* fileInterface )
	: device			( device )
	, m_fileInterface	( fileInterface )
{
	ES_SAFE_ADDREF(device);

	if( m_fileInterface == NULL )
	{
		m_fileInterface = &m_defaultFileInterface;
	}

#ifdef __EFFEKSEER_RENDERER_INTERNAL_LOADER__
	EffekseerRenderer::PngTextureLoader::Initialize();
#endif
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
TextureLoader::~TextureLoader()
{
#ifdef __EFFEKSEER_RENDERER_INTERNAL_LOADER__
	EffekseerRenderer::PngTextureLoader::Finalize();
#endif

	ES_SAFE_RELEASE(device);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Effekseer::TextureData* TextureLoader::Load(const EFK_CHAR* path, ::Effekseer::TextureType textureType)
{
	std::unique_ptr<::Effekseer::FileReader>
		reader(m_fileInterface->OpenRead(path));

	if (reader.get() != NULL)
	{
		IDirect3DTexture9* texture = nullptr;
		Effekseer::TextureData* textureData = nullptr;

		size_t size_texture = reader->GetLength();
		char* data_texture = new char[size_texture];
		reader->Read(data_texture, size_texture);

		if (size_texture < 4)
		{
		}
		else if (data_texture[1] == 'P' &&
			data_texture[2] == 'N' &&
			data_texture[3] == 'G')
		{
			if (::EffekseerRenderer::PngTextureLoader::Load(data_texture, size_texture, false))
			{
				HRESULT hr;
				int32_t width = ::EffekseerRenderer::PngTextureLoader::GetWidth();
				int32_t height = ::EffekseerRenderer::PngTextureLoader::GetHeight();
				int32_t mipMapCount = 1;
				hr = device->CreateTexture(
					width,
					height,
					mipMapCount,
					D3DUSAGE_AUTOGENMIPMAP,
					D3DFMT_A8R8G8B8,
					D3DPOOL_DEFAULT,
					&texture,
					NULL);

				if (FAILED(hr))
				{
					::EffekseerRenderer::PngTextureLoader::Unload();
					goto Exit;
				}

				LPDIRECT3DTEXTURE9 tempTexture = NULL;
				hr = device->CreateTexture(
					width,
					height,
					mipMapCount,
					0,
					D3DFMT_A8R8G8B8,
					D3DPOOL_SYSTEMMEM,
					&tempTexture,
					NULL);

				if (FAILED(hr))
				{
					::EffekseerRenderer::PngTextureLoader::Unload();
					goto Exit;
				}

				uint8_t* srcBits = (uint8_t*)::EffekseerRenderer::PngTextureLoader::GetData().data();
				D3DLOCKED_RECT locked;
				if (SUCCEEDED(tempTexture->LockRect(0, &locked, NULL, 0)))
				{
					uint8_t* destBits = (uint8_t*)locked.pBits;

					for (int32_t h = 0; h < height; h++)
					{
						memcpy(destBits, srcBits, width * 4);

						// RGB入れ替え
						for (int32_t w = 0; w < width; w++)
						{
							std::swap(destBits[w * 4 + 0], destBits[w * 4 + 2]);
						}

						destBits += locked.Pitch;
						srcBits += (width * 4);
					}

					tempTexture->UnlockRect(0);
				}

				hr = device->UpdateTexture(tempTexture, texture);
				ES_SAFE_RELEASE(tempTexture);

				::EffekseerRenderer::PngTextureLoader::Unload();

				textureData = new Effekseer::TextureData();
				textureData->UserPtr = texture;
				textureData->UserID = 0;
				textureData->TextureFormat = Effekseer::TextureFormatType::ABGR8;
				textureData->Width = width;
				textureData->Height = height;
			}
		}
		else if (data_texture[0] == 'D' &&
			data_texture[1] == 'D' &&
			data_texture[2] == 'S' &&
			data_texture[3] == ' ')
		{
			EffekseerDirectX::CreateDDSTextureFromMemory(
				device,
				(uint8_t*)data_texture,
				size_texture,
				texture);

			// To get texture size, use loader
			EffekseerRenderer::DDSTextureLoader::Load(data_texture, size_texture);

			textureData = new Effekseer::TextureData();
			textureData->UserPtr = texture;
			textureData->UserID = 0;
			textureData->TextureFormat = EffekseerRenderer::DDSTextureLoader::GetTextureFormat();
			textureData->Width = EffekseerRenderer::DDSTextureLoader::GetWidth();
			textureData->Height = EffekseerRenderer::DDSTextureLoader::GetHeight();
		}
		else
		{
			// Create TGA Texture
			wchar_t* filepath = (wchar_t*)path;
			FILE* fp;
			const int TGA_HEADER_SIZE = 18;
			uint8_t tga_header[TGA_HEADER_SIZE];

			fp = _wfopen(filepath, L"rb");

			if (fp != NULL)
			{
				// tga ヘッダー読み込み
				for (int i = 0; i < TGA_HEADER_SIZE; i++)
				{
					tga_header[i] = fgetc(fp);
				}

				int width = tga_header[12];
				int height = tga_header[14];
				int map_size = width * height * 4;

				// カラーマップ取得
				uint8_t* color_map = new uint8_t[map_size];
				fread(color_map, sizeof(char), map_size, fp);

				fclose(fp);

				// テクスチャ作成
				HRESULT hr = device->CreateTexture
				(
					width,
					height,
					1,
					D3DUSAGE_AUTOGENMIPMAP,
					D3DFMT_A8R8G8B8,
					D3DPOOL_DEFAULT,
					&texture,
					NULL
				);

				LPDIRECT3DTEXTURE9 tempTexture = NULL;
				hr = device->CreateTexture
				(
					width,
					height,
					1,
					0,
					D3DFMT_A8R8G8B8,
					D3DPOOL_SYSTEMMEM,
					&tempTexture,
					NULL
				);

				D3DLOCKED_RECT locked;
				if (SUCCEEDED(tempTexture->LockRect(0, &locked, NULL, 0)))
				{
					uint8_t* destBits = (uint8_t*)locked.pBits;

					for (int h = 0; h < height; h++)
					{
						for (int w = 0; w < width; w++)
						{
							memcpy(destBits, color_map, 4);

							destBits += 4;
							color_map += 4;
						}
					}

					tempTexture->UnlockRect(0);
				}

				// ポインタの位置を戻してから削除
				color_map -= map_size;
				delete color_map;

				hr = device->UpdateTexture(tempTexture, texture);
				ES_SAFE_RELEASE(tempTexture);

				textureData = new Effekseer::TextureData();
				textureData->UserPtr = texture;
				textureData->UserID = 0;
				textureData->TextureFormat = Effekseer::TextureFormatType::ABGR8;
				textureData->Width = width;
				textureData->Height = height;
			}
		}

	Exit:;
		delete[] data_texture;
		return textureData;
	}

	return NULL;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void TextureLoader::Unload(Effekseer::TextureData* data)
{
	if( data != nullptr && data->UserPtr != nullptr)
	{
		IDirect3DTexture9* texture = (IDirect3DTexture9*)data->UserPtr;
		texture->Release();
	}

	if (data != nullptr)
	{
		delete data;
	}
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------

#endif // __EFFEKSEER_RENDERER_INTERNAL_LOADER__
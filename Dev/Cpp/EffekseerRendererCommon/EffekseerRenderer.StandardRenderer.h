
#ifndef	__EFFEKSEERRENDERER_STANDARD_RENDERER_BASE_H__
#define	__EFFEKSEERRENDERER_STANDARD_RENDERER_BASE_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------
#include <Effekseer.h>
#include <vector>

#include "EffekseerRenderer.CommonUtils.h"
#include "EffekseerRenderer.VertexBufferBase.h"

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace EffekseerRenderer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
struct StandardRendererState
{
private:
	static const int MAX_TEXTURE_SUM = 4;

public:
	bool								DepthTest;
	bool								DepthWrite;
	bool								Distortion;
	float								DistortionIntensity;

	::Effekseer::AlphaBlendType			AlphaBlend;
	::Effekseer::CullingType			CullingType;
	::Effekseer::TextureFilterType		TextureFilterType;
	::Effekseer::TextureWrapType		TextureWrapType;
	::Effekseer::TextureData*			TexturePtr[MAX_TEXTURE_SUM];
	int32_t								MultiTexBlendType;

	StandardRendererState()
	{
		DepthTest = false;
		DepthWrite = false;
		Distortion = false;
		DistortionIntensity = 1.0f;

		AlphaBlend = ::Effekseer::AlphaBlendType::Blend;
		CullingType = ::Effekseer::CullingType::Front;
		TextureFilterType = ::Effekseer::TextureFilterType::Nearest;
		TextureWrapType = ::Effekseer::TextureWrapType::Repeat;
		for (auto it : TexturePtr)
		{
			it = nullptr;
		}
		MultiTexBlendType = 0;
	}

	bool operator != (const StandardRendererState state)
	{
		if (DepthTest != state.DepthTest) return true;
		if (DepthWrite != state.DepthWrite) return true;
		if (Distortion != state.Distortion) return true;
		if (DistortionIntensity != state.DistortionIntensity) return true;
		if (AlphaBlend != state.AlphaBlend) return true;
		if (CullingType != state.CullingType) return true;
		if (TextureFilterType != state.TextureFilterType) return true;
		if (TextureWrapType != state.TextureWrapType) return true;
		for (int i = 0; i < MAX_TEXTURE_SUM; i++) 
		{
			if (TexturePtr[i] != state.TexturePtr[i]) return true;
		}
		if (state.MultiTexBlendType != MultiTexBlendType) return true;
		return false;
	}
};

template<typename RENDERER, typename SHADER, typename VERTEX, typename VERTEX_DISTORTION>
class StandardRenderer
{
private:
	static const int MAX_TEXTURE_SUM = 4;
private:
	RENDERER*	m_renderer;
	SHADER*		m_shader;
	SHADER*		m_shader_no_texture;

	SHADER*		m_shader_distortion;
	SHADER*		m_shader_no_texture_distortion;

	Effekseer::TextureData*		m_texture;

	StandardRendererState		m_state;

	std::vector<uint8_t>		vertexCaches;
	int32_t						vertexCacheMaxSize;

	bool						m_isDistortionMode;
public:

	StandardRenderer(RENDERER* renderer, SHADER* shader, SHADER* shader_no_texture, SHADER* shader_distortion, SHADER* shader_no_texture_distortion)
		: vertexCacheMaxSize(0)
		, m_isDistortionMode(false)
	{
		m_renderer = renderer;
		m_shader = shader;
		m_shader_no_texture = shader_no_texture;
		m_shader_distortion = shader_distortion;
		m_shader_no_texture_distortion = shader_no_texture_distortion;

		vertexCaches.reserve(m_renderer->GetVertexBuffer()->GetMaxSize());
		vertexCacheMaxSize = m_renderer->GetVertexBuffer()->GetMaxSize();
	}

	void UpdateStateAndRenderingIfRequired(StandardRendererState state)
	{
		if(m_state != state)
		{
			Rendering();
		}

		m_state = state;

		m_isDistortionMode = m_state.Distortion;
	}

	void BeginRenderingAndRenderingIfRequired(int32_t count, int32_t& offset, void*& data)
	{
		if (m_isDistortionMode)
		{
			if (count * sizeof(VERTEX_DISTORTION) + vertexCaches.size() > vertexCacheMaxSize)
			{
				Rendering();
			}

			auto old = vertexCaches.size();
			vertexCaches.resize(count * sizeof(VERTEX_DISTORTION) + vertexCaches.size());
			offset = old;
			data = (vertexCaches.data() + old);
		}
		else
		{
			if (count * sizeof(VERTEX) + vertexCaches.size() > vertexCacheMaxSize)
			{
				Rendering();
			}

			auto old = vertexCaches.size();
			vertexCaches.resize(count * sizeof(VERTEX) + vertexCaches.size());
			offset = old;
			data = (vertexCaches.data() + old);
		}
	}

	void ResetAndRenderingIfRequired()
	{
		Rendering();

		// It is always initialized with the next drawing.
		for (auto it : m_state.TexturePtr)
		{
			it = (Effekseer::TextureData*)0x1;
		}
	}

	void Rendering(const Effekseer::Matrix44& mCamera, const Effekseer::Matrix44& mProj)
	{
		if (vertexCaches.size() == 0) return;

		if (m_state.Distortion)
		{
			auto callback = m_renderer->GetDistortingCallback();
			if (callback != nullptr)
			{
				if (!callback->OnDistorting())
				{
					vertexCaches.clear();
					return;
				}
			}
		}

		if (m_state.Distortion && m_renderer->GetBackground() == 0)
		{
			vertexCaches.clear();
			return;
		}

		int32_t vertexSize = vertexCaches.size();
		int32_t offsetSize = 0;
		{
			VertexBufferBase* vb = m_renderer->GetVertexBuffer();

			void* data = nullptr;

			if (m_state.Distortion)
			{
				// For OpenGL ES(Because OpenGL ES 3.2 and later can only realize a vertex layout variable ring buffer)
				vb->Lock();
				data = vb->GetBufferDirect(vertexCaches.size());
				if (data == nullptr)
				{
					vertexCaches.clear();
					return;
				}
				memcpy(data, vertexCaches.data(), vertexCaches.size());
				vb->Unlock();
			}
			else if (vb->RingBufferLock(vertexCaches.size(), offsetSize, data))
			{
				assert(data != nullptr);
				memcpy(data, vertexCaches.data(), vertexCaches.size());
				vb->Unlock();
			}
			else
			{
				// 現状、描画するインスタンス数が多すぎる場合は描画しなくしている
				vertexCaches.clear();
				return;
			}

			vertexCaches.clear();

		}

		RenderStateBase::State& state = m_renderer->GetRenderState()->Push();
		state.DepthTest = m_state.DepthTest;
		state.DepthWrite = m_state.DepthWrite;
		state.CullingType = m_state.CullingType;
		state.AlphaBlend = m_state.AlphaBlend;

		SHADER* shader_ = nullptr;

		bool distortion = m_state.Distortion;

		if (distortion)
		{
			if (m_state.TexturePtr[0] != nullptr)
			{
				shader_ = m_shader_distortion;
			}
			else
			{
				shader_ = m_shader_no_texture_distortion;
			}
		}
		else
		{
			if (m_state.TexturePtr[0] != nullptr)
			{
				shader_ = m_shader;
			}
			else
			{
				shader_ = m_shader_no_texture;
			}
		}

		m_renderer->BeginShader(shader_);

		Effekseer::TextureData* textures[MAX_TEXTURE_SUM];

		for (int i = 0; i < MAX_TEXTURE_SUM; i++)
		{
			if (m_state.TexturePtr[i] != nullptr)
			{
				textures[i] = m_state.TexturePtr[i];
			}
			else
			{
				textures[i] = 0;
			}
		}

		//if (m_state.TexturePtr != nullptr)
		//{
		//	textures[0] = m_state.TexturePtr;
		//}
		//else
		//{
		//	textures[0] = 0;
		//}

		if (distortion)
		{
			textures[1] = m_renderer->GetBackground();
			m_renderer->SetTextures(shader_, textures, 2);
		}
		else
		{
			m_renderer->SetTextures(shader_, textures, 4);
		}

		((Effekseer::Matrix44*)(shader_->GetVertexConstantBuffer()))[0] = mCamera;
		((Effekseer::Matrix44*)(shader_->GetVertexConstantBuffer()))[1] = mProj;

		if (distortion)
		{
			((float*) (shader_->GetPixelConstantBuffer()))[0] = m_state.DistortionIntensity;
		}
		else
		{
			// テクスチャのセット状況
			for (int i = 0; i < 4; i++)
			{
				if (textures[i] != nullptr)
				{
					((float*)(shader_->GetPixelConstantBuffer()))[i * 4] = 1.0f;
				}
				else
				{
					((float*)(shader_->GetPixelConstantBuffer()))[i * 4] = 0.0f;
				}
			}

			// 合成用のブレンドモードをセット
			((float*)(shader_->GetPixelConstantBuffer()))[4 * 4] = m_state.MultiTexBlendType;
		}

		shader_->SetConstantBuffer();

		state.TextureFilterTypes[0] = m_state.TextureFilterType;
		state.TextureWrapTypes[0] = m_state.TextureWrapType;

		m_renderer->GetRenderState()->Update(distortion);

		if (distortion)
		{
			m_renderer->SetVertexBuffer(m_renderer->GetVertexBuffer(), sizeof(VERTEX_DISTORTION));
			m_renderer->SetIndexBuffer(m_renderer->GetIndexBuffer());
			m_renderer->SetLayout(shader_);
			m_renderer->DrawSprites(vertexSize / sizeof(VERTEX_DISTORTION) / 4, offsetSize / sizeof(VERTEX_DISTORTION));
		}
		else
		{
			int32_t spriteCount = vertexSize / sizeof(VERTEX) / 4;
			m_renderer->SetVertexBuffer(m_renderer->GetVertexBuffer(), sizeof(VERTEX));
			m_renderer->SetIndexBuffer(m_renderer->GetIndexBuffer());
			m_renderer->SetLayout(shader_);
			m_renderer->SetMultiTexBlendType(m_state.MultiTexBlendType);
			m_renderer->DrawSprites(spriteCount, offsetSize / sizeof(VERTEX));
		}

		m_renderer->EndShader(shader_);

		m_renderer->GetRenderState()->Pop();
	}

	void Rendering()
	{
		Rendering(m_renderer->GetCameraMatrix(), m_renderer->GetProjectionMatrix());
	}
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif	// __EFFEKSEERRENDERER_STANDARD_RENDERER_H__
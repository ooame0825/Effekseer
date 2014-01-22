
#ifdef __EFFEKSEER_RENDERER_INTERNAL_LOADER__

#ifndef	__EFFEKSEERRENDERER_MODELLOADER_H__
#define	__EFFEKSEERRENDERER_MODELLOADER_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------
#include "EffekseerRenderer.RendererImplemented.h"
#include "EffekseerRenderer.DeviceObject.h"

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace EffekseerRenderer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
class ModelLoader
	: public ::Effekseer::ModelLoader
{
private:
	::Effekseer::FileInterface* m_fileInterface;
	::Effekseer::DefaultFileInterface m_defaultFileInterface;

public:
	ModelLoader( ::Effekseer::FileInterface* fileInterface );
	virtual ~ModelLoader();

public:
	void* Load( const EFK_CHAR* path );

	void Unload( void* data );
};
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif	// __EFFEKSEERRENDERER_MODELLOADER_H__

#endif // __EFFEKSEER_RENDERER_INTERNAL_LOADER__
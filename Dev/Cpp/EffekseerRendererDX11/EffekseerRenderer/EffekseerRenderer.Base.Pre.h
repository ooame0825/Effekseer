
#ifndef	__EFFEKSEERRENDERER_BASE_PRE_H__
#define	__EFFEKSEERRENDERER_BASE_PRE_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------
#include <Effekseer.h>

#include <windows.h>
#include <d3d11.h>

#ifdef __EFFEKSEER_RENDERER_INTERNAL_LOADER__
#if __EFFEKSEER_RENDERER_DIRECTXTEX || __EFFEKSEER_RENDERER_DIRECTXTEX__
#include <DirectXTex.h>
#else
#include <d3dx11.h>
#endif
#endif

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace EffekseerRenderer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
class Renderer;

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif	// __EFFEKSEERRENDERER_PRE_BASE_H__

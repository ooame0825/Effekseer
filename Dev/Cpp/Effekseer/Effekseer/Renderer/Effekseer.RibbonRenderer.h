
#ifndef	__EFFEKSEER_RIBBON_RENDERER_H__
#define	__EFFEKSEER_RIBBON_RENDERER_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------
#include "../Effekseer.Base.h"
#include "../Effekseer.Vector2D.h"
#include "../Effekseer.Vector3D.h"
#include "../Effekseer.Matrix43.h"
#include "../Effekseer.Color.h"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Effekseer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------

class RibbonRenderer
{
private:
	static const int MAX_TEXTURE_SUM = 4;

public:

	struct NodeParameter
	{
		Effect*				EffectPointer;
		int32_t				TextureIndex[MAX_TEXTURE_SUM];
		AlphaBlendType			AlphaBlend;
		TextureFilterType	TextureFilter;
		TextureWrapType	TextureWrap;
		bool				ZTest;
		bool				ZWrite;
		bool				ViewpointDependent;

		bool				Distortion;
		float				DistortionIntensity;

		int					MultiTexBlendType;
		::Effekseer::TextureFilterType		BlendTextureFilterType;
		::Effekseer::TextureWrapType		BlendTextureWrapType;
	};

	struct InstanceParameter
	{
		int32_t			InstanceCount;
		int32_t			InstanceIndex;
		Matrix43		SRTMatrix43;
		Color		AllColor;

		// 左、右
		Color		Colors[2];

		float	Positions[2];

		RectF	UV;
		RectF   BlendUV;
	};

public:
	RibbonRenderer() {}

	virtual ~RibbonRenderer() {}

	virtual void BeginRendering( const NodeParameter& parameter, int32_t count, void* userData ) {}

	virtual void Rendering( const NodeParameter& parameter, const InstanceParameter& instanceParameter, void* userData ) {}

	virtual void EndRendering( const NodeParameter& parameter, void* userData ) {}
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif	// __EFFEKSEER_RIBBON_RENDERER_H__

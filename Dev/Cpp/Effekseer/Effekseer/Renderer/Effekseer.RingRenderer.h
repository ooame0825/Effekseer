
#ifndef	__EFFEKSEER_RING_RENDERER_H__
#define	__EFFEKSEER_RING_RENDERER_H__

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

class RingRenderer
{
private:
	static const int MAX_TEXTURE_SUM = 4;

public:

	struct NodeParameter
	{
		Effect*				EffectPointer;
		int32_t				TextureIndex[MAX_TEXTURE_SUM];
		AlphaBlendType		AlphaBlend;
		TextureFilterType	TextureFilter;
		TextureWrapType	TextureWrap;
		bool				ZTest;
		bool				ZWrite;
		BillboardType		Billboard;
		int32_t				VertexCount;
		bool				IsRightHand;

		bool				Distortion;
		float				DistortionIntensity;

		float				DepthOffset;
		bool				IsDepthOffsetScaledWithCamera;
		bool				IsDepthOffsetScaledWithParticleScale;

		int					MultiTexBlendType;
		::Effekseer::TextureFilterType		BlendTextureFilterType;
		::Effekseer::TextureWrapType		BlendTextureWrapType;
	};

	struct InstanceParameter
	{
		Matrix43	SRTMatrix43;
		float		ViewingAngle;
		Vector2D	OuterLocation;
		Vector2D	InnerLocation;
		float		CenterRatio;
		Color		OuterColor;
		Color		CenterColor;
		Color		InnerColor;
		
		RectF	UV;
		RectF   BlendUV;
	};

public:
	RingRenderer() {}

	virtual ~RingRenderer() {}

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
#endif	// __EFFEKSEER_RING_RENDERER_H__

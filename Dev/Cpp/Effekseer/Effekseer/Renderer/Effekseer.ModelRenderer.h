
#ifndef	__EFFEKSEER_MODEL_RENDERER_H__
#define	__EFFEKSEER_MODEL_RENDERER_H__

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

class ModelRenderer
{
	static const int MAX_TEXTURE_SUM = 4;
public:

	struct NodeParameter
	{
		Effect*				EffectPointer;
		AlphaBlendType		AlphaBlend;
		TextureFilterType	TextureFilter;
		TextureWrapType	TextureWrap;
		bool				ZTest;
		bool				ZWrite;
		BillboardType		Billboard;

		bool				Lighting;
		CullingType		Culling;
		int32_t				ModelIndex;
		int32_t				TextureIndex[MAX_TEXTURE_SUM];
		int32_t				NormalTextureIndex;
		float				Magnification;
		bool				IsRightHand;

		bool				Distortion;
		float				DistortionIntensity;

		float				DepthOffset;
		bool				IsDepthOffsetScaledWithCamera;
		bool				IsDepthOffsetScaledWithParticleScale;

		int					MultiTexBlendType;
	};

	struct InstanceParameter
	{
		Matrix43		SRTMatrix43;
		RectF			UV;
		Color			AllColor;
		int32_t			Time;
	};

public:
	ModelRenderer() {}

	virtual ~ModelRenderer() {}

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
#endif	// __EFFEKSEER_MODEL_RENDERER_H__

﻿
#ifndef	__EFFEKSEER_SPRITE_RENDERER_H__
#define	__EFFEKSEER_SPRITE_RENDERER_H__

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

class SpriteRenderer
{
public:
	static const int MAX_TEXTURE_SUM = 4;

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
		bool				IsRightHand;

		bool				Distortion;
		float				DistortionIntensity;

		float				DepthOffset;
		bool				IsDepthOffsetScaledWithCamera;
		bool				IsDepthOffsetScaledWithParticleScale;

		int32_t				MultiTexBlendType;
		::Effekseer::TextureFilterType		BlendTextureFilterType;
		::Effekseer::TextureWrapType		BlendTextureWrapType;
	};

	struct InstanceParameter
	{
		Matrix43		SRTMatrix43;
		Color		AllColor;

		// 左下、右下、左上、右上
		Color		Colors[4];

		Vector2D	Positions[4];

		RectF	UV;
		RectF   BlendUV;
	};

public:
	SpriteRenderer() {}

	virtual ~SpriteRenderer() {}

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
#endif	// __EFFEKSEER_SPRITE_RENDERER_H__

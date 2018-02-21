#ifdef ENABLE_LIGHTING
float4	fLightDirection		: register( c0 );
float4	fLightColor			: register( c1 );
float4	fLightAmbient		: register( c2 );
#endif

#ifdef ENABLE_COLOR_TEXTURE
float4 g_setTexture[3]			: register(c3);
float4 g_multiTexBlendType		: register(c6);

Texture2D	g_colorTexture[4]	: register( t0 );
sampler2D	g_colorSampler[4]	: register( s0 );
#endif

#ifdef ENABLE_NORMAL_TEXTURE
Texture2D	g_normalTexture		: register( t4 );
sampler2D	g_normalSampler		: register( s4 );
#endif

struct PS_Input
{
	float4 UV		: TEXCOORD0;
#if ENABLE_NORMAL_TEXTURE
	half3 Normal	: TEXCOORD1;
	half3 Binormal	: TEXCOORD2;
	half3 Tangent	: TEXCOORD3;
#endif
	float4 Color	: COLOR;
};

float4 PS( const PS_Input Input ) : COLOR
{
	float diffuse = 1.0;

#if ENABLE_LIGHTING && ENABLE_NORMAL_TEXTURE
	half3 texNormal = (tex2D(g_normalSampler, Input.UV.xy).xyz  - 0.5) * 2.0;
	half3 localNormal = (half3)normalize(
		mul(
		texNormal,
		half3x3( (half3)Input.Tangent, (half3)Input.Binormal, (half3)Input.Normal )
		) );

	//return float4( localNormal , 1.0 );

	diffuse = max( dot( fLightDirection.xyz, localNormal.xyz ), 0.0 );
#endif

#ifdef ENABLE_COLOR_TEXTURE
	float4 Output = tex2D(g_colorSampler[0], Input.UV.xy) * Input.Color;
	Output.xyz = Output.xyz * diffuse;

	float4 BlendTexture = float4(0,0,0,0);
	bool BlendEnable = false;

	for (int i = 0; i < 3; i++)
	{
		// テクスチャが有効かチェック
		int TextureEnable = g_setTexture[i];

		if (TextureEnable == 1)
		{
			// αテクスチャ有
			if (i == 0)
			{
				Output.a = tex2D(g_colorSampler[i + 1], Input.UV.xy).a;
			}

			// 合成画像有
			if (i == 1)
			{
				BlendTexture = tex2D(g_colorSampler[i + 1], Input.UV.zw);
				BlendEnable = true;
			}

			// 合成画像αテクスチャ有
			if (BlendEnable == true && i == 2)
			{
				BlendTexture.a = tex2D(g_colorSampler[i + 1], Input.UV.zw).a;
			}
		}
	}

	if (BlendEnable == true)
	{
		int blend_type = g_multiTexBlendType;

		// Blend
		// Alpha Blend
		if (blend_type == 0)
		{
			Output.rgb = BlendTexture.rgb * BlendTexture.a + Output.rgb * (1.0f - BlendTexture.a);
		}
		// Addition
		else if (blend_type == 1)
		{
			Output.rgb += BlendTexture.rgb * BlendTexture.a;
		}
		// Subtract
		else if (blend_type == 2)
		{
			Output.rgb -= BlendTexture.rgb * BlendTexture.a;
		}
		// Multiply
		else if (blend_type == 3)
		{
			Output.rgb *= BlendTexture.rgb * BlendTexture.a;
		}
	}
#else
	float4 Output = Input.Color;
	Output.xyz = Output.xyz * diffuse;
#endif

#if ENABLE_LIGHTING
	Output.xyz = Output.xyz + fLightAmbient.xyz;
#endif

	if( Output.a == 0.0 ) discard;

	return Output;
}

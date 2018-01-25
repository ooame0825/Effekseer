Texture2D	g_texture		: register( t0 );
sampler2D	g_sampler[4]	: register( s0 );

float4 g_setTexture[4]		: register( c0 );
float4 g_MultiTexBlendType  : register( c4 );

struct PS_Input
{
	float4 Color	: TEXCOORD0;
	float2 UV		: TEXCOORD1;
};

float4 PS( const PS_Input Input ) : COLOR
{
	float4 Output = Input.Color * tex2D(g_sampler[0], Input.UV);
	float4 BlendTexture;
	bool BlendEnable = false;
	
	for (int i = 1; i < 4; i++)
	{
		// テクスチャが有効かチェック
		int TextureEnable = g_setTexture[i];

		if (TextureEnable == 1)
		{
			// αテクスチャ有
			if (i == 1)
			{
				Output.a = tex2D(g_sampler[i], Input.UV).a;
			}

			// 合成画像有
			if (i == 2)
			{
				BlendTexture = tex2D(g_sampler[i], Input.UV);
				BlendEnable = true;
			}

			// 合成画像αテクスチャ有
			if (BlendEnable == true && i == 3)
			{
				BlendTexture.a = tex2D(g_sampler[i], Input.UV).a;
			}
		}
	}

	if (BlendEnable == true)
	{
		// Blend
		// Alpha Blend
		if ((int)g_MultiTexBlendType.x == 0)
		{
			Output.rgb = BlendTexture.rgb * BlendTexture.a + Output.rgb * (1.0f - BlendTexture.a);
		}
		// Addition
		else if ((int)g_MultiTexBlendType.x == 1)
		{
			Output.rgb += BlendTexture.rgb * BlendTexture.a;
		}
		// Subtract
		else if ((int)g_MultiTexBlendType.x == 2)
		{
			Output.rgb -= BlendTexture.rgb * BlendTexture.a;
		}
		// Multiply
		else if ((int)g_MultiTexBlendType.x == 3)
		{
			Output.rgb *= BlendTexture.rgb * BlendTexture.a;
		}
	}

	return Output;
}

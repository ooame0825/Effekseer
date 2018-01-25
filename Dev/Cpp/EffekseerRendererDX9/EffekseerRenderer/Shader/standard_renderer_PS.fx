Texture2D	g_texture		: register( t0 );
sampler2D	g_sampler[4]	: register( s0 );

float4 g_setTexture[3]		: register( c0 );

struct PS_Input
{
	float4 Color	: TEXCOORD0;
	float2 UV		: TEXCOORD1;
};

float4 PS( const PS_Input Input ) : COLOR
{
	float4 Output = Input.Color * tex2D(g_sampler[0], Input.UV);
	
	for (int i = 1; i < 4; i++)
	{
		int blend_type = g_setTexture[i - 1];
		float4 SrcColor = tex2D(g_sampler[i], Input.UV);

		// Blend
		// Alpha Blend
		if (blend_type == 1)
		{
			Output.rgb = SrcColor.rgb * SrcColor.a + Output.rgb * (1.0f - SrcColor.a);
		}
		// Addition
		else if (blend_type == 2)
		{
			Output.rgb += SrcColor.rgb;
		}
		// Subtract
		else if (blend_type == 3)
		{
			Output.rgb -= SrcColor.rgb;
		}
		// Multiply
		else if (blend_type == 4)
		{
			Output.rgb *= SrcColor.rgb;
		}
	}

	return Output;
}

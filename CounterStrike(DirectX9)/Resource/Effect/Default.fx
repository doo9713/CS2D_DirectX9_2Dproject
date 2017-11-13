float4x4 WVP;
float4 ADDC;
float4 MULC;
int ML;
float TW;
float4 ER;
float4 ADDAC;
struct vs_input
{
	float4 Pos : POSITION0;
	float2 UV : TEXCOORD0;
};

struct vs_output
{
	float4 Pos : POSITION0;
	float2 UV : TEXCOORD0;
	float4 TPos : TEXCOORD1;
};

vs_output vs_main(vs_input input)
{
	vs_output output;
	output.Pos = mul(input.Pos, WVP);
	output.TPos = output.Pos;
	output.UV = input.UV;
	return output;
}

texture Image;
sampler Base = sampler_state
{
	Texture = (Image);
};

struct ps_input
{
	float2 uv : TEXCOORD0;
	float4 Pos : TEXCOORD1;
};

float4 ps_main(ps_input input) : COLOR0
{
	float2 UV = input.uv;
	if(ML)
	{
		UV.x = ((int)(UV.x * ML)) / (float)ML;
		UV.y = ((int)(UV.y * ML)) / (float)ML;
	}
	if(TW)
	{
		UV.x = UV.x + sin(TW * UV.y);
	}
	float4 color = tex2D(Base, UV);
	if(color.r + 0.0001f > ER.r && ER.r > color.r - 0.0001f &&
	   color.g + 0.0001f > ER.g && ER.g > color.g - 0.0001f &&
	   color.b + 0.0001f > ER.b && ER.b > color.b - 0.0001f)
	{
		color.a = 0;
	}
	else
	{
		color = (color + ADDC) * MULC + ADDAC;
	}
	return color;
}

technique DefaultRendering
{
	pass Default
	{ 
		LIGHTING = FALSE;
		CULLMODE = NONE;
		AlphaBlendEnable = TRUE;
		SrcBlend = SRCALPHA;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_main();
	}
}
#include "SpriteRender.h"
#include "GameObj.h"

RTTILINK(CSpriteRender, CComponent)

void CSpriteRender::ChangeColorRemove(UINT Red, UINT Green, UINT Blue)
{
	ColorRemove.w = 1;
	ColorRemove.x = Red / 255.0;
	ColorRemove.y = Green / 255.0;
	ColorRemove.z = Blue / 255.0;
}

void CSpriteRender::ChangeColorAdd(UINT Alpha, UINT Red, UINT Green, UINT Blue)
{
	ColorAdd.w = Alpha / 255.0;
	ColorAdd.x = Red / 255.0;
	ColorAdd.y = Green / 255.0;
	ColorAdd.z = Blue / 255.0;
}

void CSpriteRender::ChangeColorAddAfter(UINT Alpha, UINT Red, UINT Green, UINT Blue)
{
	ColorAddAfter.w = Alpha / 255.0;
	ColorAddAfter.x = Red / 255.0;
	ColorAddAfter.y = Green / 255.0;
	ColorAddAfter.z = Blue / 255.0;
}

void CSpriteRender::ChangeColorMul(UINT Alpha, UINT Red, UINT Green, UINT Blue)
{
	ColorMul.w = Alpha / 255.0;
	ColorMul.x = Red / 255.0;
	ColorMul.y = Green / 255.0;
	ColorMul.z = Blue / 255.0;
}

void CSpriteRender::Render()
{
	if (ShaderKey == "")
		DRX.Draw(gameObj.World, RenderKey.data(), Page);
	else
	{
		auto Effect = SHADER.GetEffect(ShaderKey.data());
		if (Effect)
		{
			Effect->SetVector("ADDC", &ColorAdd);
			Effect->SetVector("MULC", &ColorMul);
			Effect->SetInt("ML", MosaicLevel);
			Effect->SetFloat("TW", Twist);
			Effect->SetVector("ER", &ColorRemove);
			Effect->SetVector("ADDAC", &ColorAddAfter);
			DRX.Draw(Effect, gameObj.World, RenderKey.data(), Page);
		}
	}
}

CSpriteRender::CSpriteRender(CGameObj* Owner)
	: CComponent(Owner), Page(0), ColorAdd(0, 0, 0, 0), ColorMul(1, 1, 1, 1), ShaderKey(""), MosaicLevel(0), Twist(0), ColorRemove(-1, -1, -1, -1)
{
}


CSpriteRender::~CSpriteRender()
{
}

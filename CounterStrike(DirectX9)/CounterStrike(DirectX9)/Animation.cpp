#include "Animation.h"
#include "SpriteRender.h"
#include "GameObj.h"
#include "AnimClipList.h"

RTTILINK(CAnimation, CComponent)

void CAnimation::AnimationChange(string Name)
{
	if (Name == AnimationClipName)
		return;
	AnimationClipName = Name;
	Time = 0;
	Page = 0;
	RenderPage = ANIMCLIP.GetBeginRenderPage(Name.data());
}

void CAnimation::Update()
{
	if (CSR)
	{
		Time += TIME.Delta;
		CSR->RenderKey = ANIMCLIP.Animation(AnimationClipName.data(), Page, Time, RenderPage);
		CSR->Page = RenderPage;
	}
	else
		CSR = gameObj.GetComponent<CSpriteRender>();
}

CAnimation::CAnimation(CGameObj* Owner)
	: CComponent(Owner), AnimationClipName(""), Page(0), Time(0), CSR(nullptr), RenderPage(0)
{
}

CAnimation::~CAnimation()
{
}

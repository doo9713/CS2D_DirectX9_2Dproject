#pragma once

#include "Component.h"

class CSpriteRender;
class CAnimation : public CComponent
{
	RTTICHECK
private :
	string AnimationClipName;
	UINT Page;
	UINT RenderPage;
	double Time;
	CSpriteRender* CSR;
public :
	_declspec(property(get = GetAnimationClipName, put = AnimationChange)) string AnimationName;
	const string& GetAnimationName() const{ return AnimationClipName; }
	void AnimationChange(string Name);
public :
	void Update();
public :
	CAnimation(CGameObj* Owner);
	~CAnimation();
};


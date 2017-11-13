#pragma once

#include "Component.h"

class CSpriteRender : public CComponent
{
	RTTICHECK
private :
	D3DXVECTOR4 ColorAddAfter;
	D3DXVECTOR4 ColorAdd;
	D3DXVECTOR4 ColorMul;
	D3DXVECTOR4 ColorRemove;
public :
	void ChangeColorRemove(UINT Red = 0, UINT Green = 0, UINT Blue = 0);
	void ChangeColorAdd(UINT Alpha = 0, UINT Red = 0, UINT Green = 0, UINT Blue = 0);
	void ChangeColorAddAfter(UINT Alpha = 0, UINT Red = 0, UINT Green = 0, UINT Blue = 0);
	void ChangeColorMul(UINT Alpha = 0, UINT Red = 0, UINT Green = 0, UINT Blue = 0);
public :
	float Twist;
	UINT Page;
	UINT MosaicLevel;
	string RenderKey;
	string ShaderKey;
public :
	void Render();
public :
	CSpriteRender(CGameObj* Owner);
	~CSpriteRender();
};


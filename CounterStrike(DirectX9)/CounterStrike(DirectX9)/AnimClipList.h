#pragma once

#include "Defines.h"

class CAnimClip;
class CAnimClipList
{
private :
	map<string, CAnimClip*> ClipList;
public :
	void OnLoad(const char* Key, const char* Path);
	UINT GetBeginRenderPage(const char* Key);
	const char* Animation(const char* Key, UINT& Page, double& Time, UINT& RenderPage);
public :
	CAnimClipList();
	~CAnimClipList();
};


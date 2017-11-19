#pragma once

#include "Defines.h"

class CAnimClip
{
private :
	struct Clip
	{
		string Name;
		double Time;
		UINT Page;
	};
	vector<Clip*> ClipList;
	double AllTime;
public :
	UINT GetBeginRenderPage() { return ClipList[0]->Page; }
	void OnLoad(const char* Path);
	const char* Animation(UINT& Page, double& Time, UINT& RenderPage);
public :
	CAnimClip();
	~CAnimClip();
};


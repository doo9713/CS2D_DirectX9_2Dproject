#include "AnimClip.h"

void CAnimClip::OnLoad(const char * Path)
{
	FILE* fp = fopen(Path, "rt");
	if (fp == nullptr)
		return;

	float Temp;
	fscanf(fp, "%f\n", &Temp);
	AllTime = Temp;

	char NameTemp[256];
	UINT PageTemp;

	while (fscanf(fp, "%s %d %f\n", NameTemp, &PageTemp, &Temp) > 0)
	{
		Clip* clip = new Clip;
		clip->Name = NameTemp;
		clip->Page = PageTemp;
		if (ClipList.size() > 0)
			clip->Time = Temp + ClipList.back()->Time;
		else
			clip->Time = Temp;
		ClipList.emplace_back(clip);
	}

	fclose(fp);
}

const char* CAnimClip::Animation(UINT& Page, double& Time, UINT& RenderPage)
{
	if (AllTime <= Time)
	{
		Time -= AllTime;
		Page = 0;
	}
	else
	{
		if (ClipList[Page]->Time <= Time)
			if (ClipList.size() - 1 != Page)
				++Page;
	}
	RenderPage = ClipList[Page]->Page;
	return ClipList[Page]->Name.data();
}

CAnimClip::CAnimClip()
{
}

CAnimClip::~CAnimClip()
{
	for (auto clip : ClipList)
		delete clip;
	ClipList.clear();
}

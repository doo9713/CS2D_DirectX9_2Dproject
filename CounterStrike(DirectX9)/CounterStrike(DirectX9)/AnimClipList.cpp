#include "AnimClipList.h"
#include "AnimClip.h"

CAnimClipList ANIMCLIP;

void CAnimClipList::OnLoad(const char * Key, const char * Path)
{
	auto finder_name = ClipList.find(Key);
	if (finder_name != ClipList.end())
		return;
	CAnimClip* Clip = new CAnimClip;
	Clip->OnLoad(Path);
	ClipList.insert(make_pair(Key, Clip));
}

UINT CAnimClipList::GetBeginRenderPage(const char * Key)
{
	auto finder_name = ClipList.find(Key);
	if (finder_name == ClipList.end())
		return 0;
	return finder_name->second->GetBeginRenderPage();
}

const char * CAnimClipList::Animation(const char * Key, UINT & Page, double & Time, UINT & RenderPage)
{
	auto finder_name = ClipList.find(Key);
	if (finder_name == ClipList.end())
		return "";
	return finder_name->second->Animation(Page, Time, RenderPage);
}

CAnimClipList::CAnimClipList()
{
}


CAnimClipList::~CAnimClipList()
{
	for (auto clip : ClipList)
		delete clip.second;
	ClipList.clear();
}

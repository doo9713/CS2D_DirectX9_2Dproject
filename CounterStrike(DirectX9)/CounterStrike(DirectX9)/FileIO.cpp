#include "FileIO.h"

// 파일 검색
void UTILITY::FileFinder::Find
(
	bool IsFolder,
	std::function<void
	(
		const std::string& _path,
		const std::string& _elimit,
		const std::string& _name,
		UINT _attribute
		)> Func
)
{
	std::string FullPath = Path + "/*." + Elimit;

	__finddata64_t Result;
	intptr_t Handle;

	Handle = _findfirst64(FullPath.data(), &Result);

	if (Handle == -1)
		return;

	FindData.clear();

	do 
	{
		if (IsFolder)
		{
			if (Result.attrib & _A_SUBDIR)
			{
				if(strcmp(Result.name, ".") == 0 || strcmp(Result.name, ".."))
					continue;
				FindData.emplace_back(Result.name);
			}
			else continue;
		}
		else
		{
			if (!(Result.attrib & _A_SUBDIR))
			{
				if (Elimit == "*")
					FindData.emplace_back(Result.name);
				else
				{
					std::string Temp = Result.name;
					Temp = Temp.substr(0, Temp.rfind(Elimit) - 1);
					FindData.emplace_back(Temp);
				}
			}
			else continue;
		}

		if (Func != nullptr)
			Func(Path, Elimit, FindData.back(), Result.attrib);
	
	} while (_findnext64(Handle, &Result) == 0);

	_findclose(Handle);
}

int UTILITY::ReadInt(const char* Path, const char* Colum, const char* Key, int Default)
{
	static char Temp[256];
	static char DefaultStr[256];
	_itoa(Default, DefaultStr, 10);
	GetPrivateProfileStringA(Colum, Key, DefaultStr, Temp, 255, Path);
	return atoi(Temp);
}

double UTILITY::ReadDouble(const char* Path, const char* Colum, const char* Key, double Default)
{
	static char Temp[256];
	static char DefaultStr[256];
	_gcvt(Default, 20, DefaultStr);
	GetPrivateProfileStringA(Colum, Key, DefaultStr, Temp, 255, Path);
	return atof(Temp);
}

std::string UTILITY::ReadString(const char* Path, const char* Colum, const char* Key, const char* Default)
{
	static char Temp[256];
	GetPrivateProfileStringA(Colum, Key, Default, Temp, 255, Path);
	return Temp;
}

void UTILITY::WriteInt(const char* Path, const char* Colum, const char* Key, int Data)
{
	static char Temp[256];
	_itoa(Data, Temp, 10);
	WritePrivateProfileStringA(Colum, Key, Temp, Path);
}

void UTILITY::WriteDouble(const char* Path, const char* Colum, const char* Key, double Data)
{
	static char Temp[256];
	_gcvt(Data, 20, Temp);
	WritePrivateProfileStringA(Colum, Key, Temp, Path);
}

void UTILITY::WriteString(const char* Path, const char* Colum, const char* Key, const char* Data)
{
	WritePrivateProfileStringA(Colum, Key, Data, Path);
}
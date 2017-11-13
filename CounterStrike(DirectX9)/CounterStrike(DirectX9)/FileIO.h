#pragma once

#include "UtilConstant.h"

namespace UTILITY
{
	struct FileFinder
	{
	private :
		std::string Path;
		std::string Elimit;
		std::list<std::string> FindData;
	public :
		std::string GetPath() const { return Path; }
		std::string GetElimit() const { return Elimit; }
		const std::list<std::string>& GetFile() const { return FindData; }
		void SetPath(const char* Path) { this->Path = Path; }
		void SetElimit(const char* Elimit) { this->Elimit = Elimit; }
		void Find(bool IsFolder = false,
			std::function<void(const std::string& _path,
				const std::string& _elimit,
				const std::string& _name,
				UINT _attribute)> Func = nullptr);
	public :
		FileFinder(const char* Path = ".", const char* Elimit = "*")
			: Path(Path), Elimit(Elimit)
		{}
		FileFinder(std::string Paht = ".", std::string Elimit = "*")
			: Path(Path), Elimit(Elimit)
		{}
	};

	int ReadInt(const char* Path, const char* Colum, const char* Key, int Default = 0);
	double ReadDouble(const char* Path, const char* Colum, const char* Key, double Default = 0);
	std::string ReadString(const char* Path, const char* Colum, const char* Key, const char* Default = "");

	void WriteInt(const char* Path, const char* Colum, const char* Key, int Data);
	void WriteDouble(const char* Path, const char* Colum, const char* Key, double Data);
	void WriteString(const char* Path, const char* Colum, const char* Key, const char* Data);
}
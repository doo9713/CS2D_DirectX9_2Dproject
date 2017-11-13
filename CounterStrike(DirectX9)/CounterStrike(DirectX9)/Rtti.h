#pragma once

#include "UtilConstant.h"

namespace UTILITY
{
	struct RTTI
	{
	private :
		static UINT UniqueKeyValue;
		UINT UniqueKey;
		RTTI* Parent;
	public :
		bool operator==(const RTTI& other)
		{
			return UniqueKey == other.UniqueKey;
		}
	public :
		bool TreeIn(const RTTI& other)
		{
			RTTI* Tree = this;
			do 
			{
				if (*Tree == other)
					return true;
				Tree = Tree->Parent;
			} while (Tree);
			return false;
		}
	public :
		RTTI(RTTI* _Parent = nullptr)
			: UniqueKey(UniqueKeyValue++), Parent(_Parent)
		{}
	};

	// RTTI ����
	#define RTTICHECK public : static RTTI _rtti; public : virtual RTTI& GetRTTI() const { return _rtti; }
	// ���� ���� RTTI
	#define RTTIBASE(mytype) RTTI mytype::_rtti;
	// RTTI ��ũ �����
	#define RTTILINK(mytype, parent) RTTI mytype::_rtti(&parent::_rtti);
}
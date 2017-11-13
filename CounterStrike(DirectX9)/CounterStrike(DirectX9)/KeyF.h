#pragma once

#include "UtilConstant.h"

namespace UTILITY
{
	struct KeyManager
	{
	private :
		struct Key
		{
		public :
			short key;
			bool Down;
			bool Push;
			bool Pull;
			void Set()
			{
				if (GetAsyncKeyState(key) & 0x8000)
				{
					if (Down) Push = false;
					else Push = true;
					Down = true;
					Pull = false;
				}
				else
				{
					if (Down) Pull = true;
					else Pull = false;
					Down = false;
					Push = false;
				}
			}
			Key(short virtualkey = VK_LBUTTON)
				: key(virtualkey), Down(false), Push(false), Pull(false)
			{}
		};
		Key data[255];
	public :
		bool Push(short nKey) { return data[nKey].Push; }
		bool Pull(short nKey) { return data[nKey].Pull; }
		bool Down(short nKey) { return data[nKey].Down; }
		bool Up(short nKey) { return !data[nKey].Down; }
		__forceinline void Set()
		{
			for (int i = 0; i < 255; ++i)
				data[i].Set();
		}
	public :
		KeyManager()
		{
			for (int i = 1; i < 255; ++i)
				data[i].key = (short)i;
		}
	};

	extern KeyManager KEY;
}
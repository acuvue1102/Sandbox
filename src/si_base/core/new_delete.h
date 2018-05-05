/////////////////////////////////////////
// new_delete.h
//
// �������m�ۂ͒���new���g�킸�A
// ��Ƀt�b�N�ł���悤�ɂ��邽�߁A�����̃}�N���o�R�ō��.
/////////////////////////////////////////
#pragma once

namespace SI
{
	template<typename T>
	inline void SafeDelete(T*& pointer)
	{
		delete pointer;
		pointer = nullptr;
	}

	template<typename T>
	inline void SafeDeleteArray(T*& pointer)
	{
		delete[] pointer;
		pointer = nullptr;
	}
}

#define SI_NEW(type, ...)              (new type(__VA_ARGS__))
#define SI_NEW_ARRAY(type, size)       (new type[(size)])
#define SI_DELETE(p)                   (SI::SafeDelete(p))
#define SI_DELETE_ARRAY(p)             (SI::SafeDeleteArray(p))

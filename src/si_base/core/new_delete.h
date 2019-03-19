/////////////////////////////////////////
// new_delete.h
//
// �������m�ۂ͒���new���g�킸�A
// ��Ƀt�b�N�ł���悤�ɂ��邽�߁A�����̃}�N���o�R�ō��.
/////////////////////////////////////////
#pragma once

#include <stdlib.h>

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

	inline void SafeFree(void*& p)
	{
		free(p);
		p = nullptr;
	}
}

#define SI_NEW(type, ...)              (new type(__VA_ARGS__))
#define SI_NEW_ARRAY(type, size)       (new type[(size)])
#define SI_DELETE(p)                   (delete (p))
#define SI_DELETE_ARRAY(p)             (delete[] (p))
#define SI_MALLOC(size)                (malloc(size))
#define SI_FREE(p)                     (free(p))
#define SI_ALIGNED_MALLOC(size,align)  (_aligned_malloc(size, align))
#define SI_ALIGNED_FREE(p)             (_aligned_free(p))

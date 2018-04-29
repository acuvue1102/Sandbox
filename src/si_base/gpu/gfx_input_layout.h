﻿#pragma once

#include <stdint.h>
#include "si_base/gpu/gfx_enum.h"

namespace SI
{
	struct GfxInputElement
	{
		const char* m_semanticsName     = nullptr;
		uint32_t    m_semanticsId       = 0;
		GfxFormat   m_format            = kGfxFormat_Unknown;
		uint32_t    m_inputSlot         = 0;
		uint32_t    m_alignedByteOffset = 0; // offsetのバイト数.
	};

} // namespace SI
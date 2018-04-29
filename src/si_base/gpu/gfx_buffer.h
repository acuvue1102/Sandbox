﻿#pragma once

#include <stdint.h>
#include "si_base/gpu/gfx_enum.h"

namespace SI
{
	class BaseBuffer;
	struct GfxBufferDesc
	{
		size_t       m_bufferSizeInByte  = 0;
		const void*  m_initialData       = nullptr;
		GfxHeapType  m_heapType          = kGfxHeapType_Default;
	};

	class GfxBuffer
	{
	public:
		GfxBuffer(BaseBuffer* base=nullptr)
			: m_base(base)
		{
		}

		~GfxBuffer()
		{
		}
		
		void* Map  (uint32_t subResourceId = 0);
		void  Unmap(uint32_t subResourceId = 0);

	public:
		      BaseBuffer* GetBaseBuffer()      { return m_base; }
		const BaseBuffer* GetBaseBuffer() const{ return m_base; }

	private:
		BaseBuffer* m_base;
	};

	class GfxVertexBufferView
	{
	public:
		GfxVertexBufferView(
			GfxBuffer* buffer = nullptr,
			size_t strideInByte = 0)
			: m_buffer(buffer)
			, m_strideInByte(strideInByte)
		{}
		
		inline void             SetBuffer(GfxBuffer* buffer) { m_buffer = buffer;             }
		inline void             SetStride(size_t strideInByte) { m_strideInByte = strideInByte; }

		inline const GfxBuffer* GetBuffer() const{ return m_buffer; }
		inline size_t           GetStride() const{ return m_strideInByte; }

	private:
		GfxBuffer* m_buffer;
		size_t     m_strideInByte;
	};

} // namespace SI

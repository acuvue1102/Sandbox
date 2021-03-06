﻿#include "si_base/gpu/dx12/dx12_swap_chain.h"
#include "si_base/gpu/gfx_texture.h"
#include "si_base/gpu/gfx_command_queue.h"
#include "si_base/gpu/gfx_swap_chain.h"

namespace SI
{
	GfxSwapChain::GfxSwapChain(BaseSwapChain* base)
		: m_base(base)
	{
	}

	GfxSwapChain::~GfxSwapChain()
	{
	}

	int GfxSwapChain::Present(uint32_t syncInterval)
	{
		return m_base->Present(syncInterval);
	}
	
	int GfxSwapChain::Flip()
	{
		return m_base->Flip();
	}
	
	int GfxSwapChain::Wait()
	{
		return m_base->Wait();
	}
	
	GfxTexture GfxSwapChain::GetSwapChainTexture()
	{
		GfxTexture tex(&m_base->GetSwapChainTexture());
		return tex;
	}

	GfxCpuDescriptor GfxSwapChain::GetSwapChainCpuDescriptor()
	{
		return m_base->GetSwapChainCpuDescriptor();
	}
	
	GfxTestureEx_SwapChain& GfxSwapChain::GetTexture()
	{
		return m_base->GetTexture();
	}

} // namespace SI

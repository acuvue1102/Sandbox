﻿
#include "si_base/gpu/gfx_device.h"

#include "si_base/core/core.h"
#include "si_base/gpu/dx12/dx12_device.h"
#include "si_base/gpu/gfx_command_queue.h"
#include "si_base/gpu/gfx_graphics_command_list.h"
#include "si_base/gpu/gfx_texture.h"
#include "si_base/gpu/gfx_swap_chain.h"
#include "si_base/gpu/gfx_graphics_state.h"
#include "si_base/gpu/gfx_fence.h"
#include "si_base/gpu/gfx_root_signature.h"
#include "si_base/gpu/gfx_buffer.h"
#include "si_base/gpu/gfx_descriptor_heap.h"

namespace SI
{
	GfxDevice::GfxDevice()
		: Singleton(this)
		, m_base(nullptr)
	{
	}

	GfxDevice::~GfxDevice()
	{
		Terminate();
	}

	int GfxDevice::Initialize(const GfxDeviceConfig& config)
	{
		if(m_base) return 0;

		m_base = SI_NEW(BaseDevice);
		return m_base->Initialize(config);
	}

	int GfxDevice::Terminate()
	{
		if(!m_base) return 0;

		int ret = m_base->Terminate();
		SI_DELETE(m_base);
		
		return ret;
	}
		
	GfxCommandQueue GfxDevice::CreateCommandQueue()
	{
		GfxCommandQueue cq(m_base->CreateCommandQueue());
		return cq;
	}
	
	void GfxDevice::ReleaseCommandQueue(GfxCommandQueue& commandQueue)
	{
		m_base->ReleaseCommandQueue(commandQueue.GetBaseCommandQueue());
		commandQueue = GfxCommandQueue(nullptr);
	}
	
	GfxSwapChain GfxDevice::CreateSwapChain(
		const GfxDeviceConfig& config,
		GfxCommandQueue& commandQueue)
	{
		GfxSwapChain sc(m_base->CreateSwapChain(config, *commandQueue.GetBaseCommandQueue()));
		return sc;
	}
	
	void GfxDevice::ReleaseSwapChain(GfxSwapChain& swapChain)
	{
		m_base->ReleaseSwapChain(swapChain.GetBaseSwapChain());
		swapChain = GfxSwapChain(nullptr);
	}
	
	GfxGraphicsCommandList GfxDevice::CreateGraphicsCommandList()
	{
		GfxGraphicsCommandList gcl(m_base->CreateGraphicsCommandList());
		return gcl;
	}

	void GfxDevice::ReleaseGraphicsCommandList(GfxGraphicsCommandList& commandList)
	{
		m_base->ReleaseGraphicsCommandList(commandList.GetBaseGraphicsCommandList());
		commandList = GfxGraphicsCommandList();
	}
	
	GfxGraphicsState GfxDevice::CreateGraphicsState(const GfxGraphicsStateDesc& desc)
	{
		GfxGraphicsState s(m_base->CreateGraphicsState(desc));
		return s;
	}

	void GfxDevice::ReleaseGraphicsState(GfxGraphicsState& state)
	{
		m_base->ReleaseGraphicsState(state.GetBaseGraphicsState());
		state = GfxGraphicsState();
	}
	
	GfxFence GfxDevice::CreateFence()
	{
		GfxFence f(m_base->CreateFence());
		return f;
	}

	void GfxDevice::ReleaseFence(GfxFence& fence)
	{
		m_base->ReleaseFence(fence.GetBaseFence());
		fence = GfxFence();
	}

	GfxFenceEvent GfxDevice::CreateFenceEvent()
	{
		GfxFenceEvent e(m_base->CreateFenceEvent());
		return e;
	}

	void GfxDevice::ReleaseFenceEvent(GfxFenceEvent& event)
	{
		m_base->ReleaseFenceEvent(event.GetBaseFenceEvent());
		event = GfxFenceEvent();
	}

	GfxRootSignature GfxDevice::CreateRootSignature(const GfxRootSignatureDesc& desc)
	{
		GfxRootSignature s(m_base->CreateRootSignature(desc));
		return s;
	}

	void GfxDevice::ReleaseRootSignature(GfxRootSignature& signature)
	{
		m_base->ReleaseRootSignature(signature.GetBaseRootSignature());
		signature = GfxRootSignature();
	}

	
	GfxBuffer GfxDevice::CreateBuffer(const GfxBufferDesc& desc)
	{
		GfxBuffer b(m_base->CreateBuffer(desc));
		return b;
	}

	void GfxDevice::ReleaseBuffer(GfxBuffer& buffer)
	{
		m_base->ReleaseBuffer(buffer.GetBaseBuffer());
		buffer = GfxBuffer();
	}
	
	GfxTexture GfxDevice::CreateTexture(const GfxTextureDesc& desc)
	{
		GfxTexture t(m_base->CreateTexture(desc));
		return t;
	}

	void GfxDevice::ReleaseTexture(GfxTexture& texture)
	{
		m_base->ReleaseTexture(texture.GetBaseTexture());
		texture = GfxTexture();
	}
		
	GfxDescriptorHeap GfxDevice::CreateDescriptorHeap(const GfxDescriptorHeapDesc& desc)
	{
		GfxDescriptorHeap d(m_base->CreateDescriptorHeap(desc));
		return d;
	}

	void GfxDevice::ReleaseDescriptorHeap(GfxDescriptorHeap& descriptorHeap)
	{
		m_base->ReleaseDescriptorHeap(descriptorHeap.GetBaseDescriptorHeap());
		descriptorHeap = GfxDescriptorHeap();
	}
	
	void GfxDevice::CreateRenderTargetView(
		GfxDescriptorHeap& descriptorHeap,
		uint32_t descriptorIndex,
		GfxTexture& texture,
		const GfxRenderTargetViewDesc& desc)
	{
		m_base->CreateRenderTargetView(
			*descriptorHeap.GetBaseDescriptorHeap(),
			descriptorIndex,
			*texture.GetBaseTexture(),
			desc);
	}

	void GfxDevice::CreateShaderResourceView(
		GfxDescriptorHeap& descriptorHeap,
		uint32_t descriptorIndex,
		GfxTexture& texture,
		const GfxShaderResourceViewDesc& desc)
	{
		m_base->CreateShaderResourceView(
			*descriptorHeap.GetBaseDescriptorHeap(),
			descriptorIndex,
			*texture.GetBaseTexture(),
			desc);
	}
	
	void GfxDevice::CreateSampler(
		GfxDescriptorHeap& descriptorHeap,
		uint32_t descriptorIndex,
		const GfxSamplerDesc& desc)
	{
		m_base->CreateSampler(
			*descriptorHeap.GetBaseDescriptorHeap(),
			descriptorIndex,
			desc);
	}
	
	void GfxDevice::CreateConstantBufferView(
		GfxDescriptorHeap& descriptorHeap,
		uint32_t descriptorIndex,
		const GfxConstantBufferViewDesc& desc)
	{
		m_base->CreateConstantBufferView(
			*descriptorHeap.GetBaseDescriptorHeap(),
			descriptorIndex,
			desc);
	}
}

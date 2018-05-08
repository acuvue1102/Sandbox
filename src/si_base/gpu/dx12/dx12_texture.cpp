﻿
#include "si_base/gpu/dx12/dx12_texture.h"

#if SI_USE_DX12

#include <dxgi1_4.h>
#include <comdef.h>
#include "si_base/core/core.h"
#include "si_base/gpu/dx12/dx12_enum.h"
#include "si_base/gpu/gfx_texture.h"

namespace SI
{
	BaseTexture::BaseTexture()
	{
	}

	BaseTexture::~BaseTexture()
	{
		Terminate();
	}
	
	int BaseTexture::Initialize(ID3D12Device& device, const GfxTextureDesc& desc)
	{
		D3D12_HEAP_PROPERTIES heapProperties = {};
		heapProperties.Type                 = GetDx12HeapType(desc.m_heapType);
		heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		heapProperties.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapProperties.CreationNodeMask     = 1;
		heapProperties.VisibleNodeMask      = 1;

		DXGI_FORMAT format = GetDx12Format(desc.m_format);

		const D3D12_CLEAR_VALUE* clearValue = nullptr;
		D3D12_CLEAR_VALUE cv = {};

		D3D12_RESOURCE_FLAGS resourceFlag = D3D12_RESOURCE_FLAG_NONE;
		if(desc.m_resourceState.GetStateFlags() & GfxResourceState::kRenderTarget.GetStateFlags())
		{
			resourceFlag |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

			cv.Format = format;
			cv.Color[0] = desc.m_clearColor[0];
			cv.Color[1] = desc.m_clearColor[1];
			cv.Color[2] = desc.m_clearColor[2];
			cv.Color[3] = desc.m_clearColor[3];
			clearValue = &cv;
		}

		D3D12_RESOURCE_DESC textureDesc = {};
		textureDesc.MipLevels          = desc.m_mipLevels;
		textureDesc.Format             = format;
		textureDesc.Width              = desc.m_width;
		textureDesc.Height             = desc.m_height;
		textureDesc.Flags              = resourceFlag;
		textureDesc.DepthOrArraySize   = desc.m_depth;
		textureDesc.SampleDesc.Count   = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Dimension          = GetDx12ResourceDimension(desc.m_dimension);

		SetWidth(desc.m_width);
		SetHeight(desc.m_height);
		SetDepth(desc.m_depth);

		HRESULT hr = device.CreateCommittedResource(
			&heapProperties,
			D3D12_HEAP_FLAG_NONE,
			&textureDesc,
			(D3D12_RESOURCE_STATES)desc.m_resourceState.GetStateFlags(),
			clearValue,
			IID_PPV_ARGS(&m_resource));
		if(FAILED(hr))
		{
			SI_ASSERT(0, "error CreateCommittedResource", _com_error(hr).ErrorMessage());
			return -1;
		}

		if(desc.m_name)
		{
			wchar_t wName[64];
			wName[0] = 0;
			size_t num = 0;
			errno_t ret = mbstowcs_s(&num, wName, desc.m_name, ArraySize(wName));
			if(ret == 0)
			{
				m_resource->SetName(wName);
			}
		}

		return 0;
	}

	int BaseTexture::InitializeAsSwapChainTexture(
		const GfxDeviceConfig& config,
		ID3D12Device& device,
		IDXGISwapChain3& swapChain,
		int swapChainBufferId)
	{
		SetWidth(config.m_width);
		SetHeight(config.m_height);
		SetDepth(1);
		
		SI_ASSERT(m_resource == nullptr);
		HRESULT hr = swapChain.GetBuffer(swapChainBufferId, IID_PPV_ARGS(&m_resource));
		if(FAILED(hr))
		{
			SI_ASSERT(0, "error swapChain->GetBuffer", _com_error(hr).ErrorMessage());
			return -1;
		}

		m_resource->SetName(L"SwapChain");

		return 0;
	}

	int BaseTexture::Terminate()
	{
		m_resource.Reset();
		return 0;
	}

} // namespace SI

#endif // SI_USE_DX12

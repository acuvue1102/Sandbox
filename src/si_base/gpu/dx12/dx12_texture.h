﻿#pragma once

#include "si_base/gpu/gfx_config.h"

#if SI_USE_DX12
#include <d3d12.h>
#include <wrl/client.h>

struct IDXGISwapChain3;

namespace SI
{
	struct GfxTextureDesc;

	class BaseTexture
	{
		template<typename T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	public:
		BaseTexture();
		~BaseTexture();

		int Initialize(ID3D12Device& device, const GfxTextureDesc& desc);

		int InitializeAsSwapChainTexture(
			const GfxDeviceConfig& config,
			ID3D12Device& device,
			IDXGISwapChain3& swapChain,
			int swapChainBufferId);

		int Terminate();
		
		uint32_t GetWidth() const
		{
			return m_width;
		}

		uint32_t GetHeight() const
		{
			return m_height;
		}

		uint32_t GetDepth() const
		{
			return m_depth;
		}
		
		void SetWidth(uint32_t w)
		{
			m_width = w;
		}
		
		void SetHeight(uint32_t h)
		{
			m_height = h;
		}
		
		void SetDepth(uint32_t d)
		{
			m_depth = d;
		}

	public:
		ComPtr<ID3D12Resource>& GetComPtrResource()
		{
			return m_resource;
		}

	private:
		ComPtr<ID3D12Resource>            m_resource;
		uint32_t                          m_width  = 0;
		uint32_t                          m_height = 0;
		uint32_t                          m_depth  = 0;
	};

} // namespace SI

#endif // SI_USE_DX12

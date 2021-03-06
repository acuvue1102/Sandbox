﻿#pragma once

#include "si_base/gpu/gfx_config.h"

#if SI_USE_DX12
#include <d3d12.h>
#include <wrl/client.h>
#include <cstdint>
#include <vector>
#include "si_base/core/singleton.h"
#include "si_base/concurency/mutex.h"
#include "si_base/gpu/gfx_enum.h"
#include "si_base/gpu/dx12/dx12_declare.h"
#include "si_base/gpu/dx12/dx12_descriptor_heap.h"
#include "si_base/gpu/dx12/dx12_upload_pool.h"

struct IDXGIFactory4;

namespace SI
{
	class PoolAllocatorEx;
	struct GfxCpuDescriptor;
	struct GfxRaytracingShaderTablesDesc;

	template<typename T> class GfxStdDeviceTempAllocator;
	template<typename T> using GfxTempVector = std::vector<T, GfxStdDeviceTempAllocator<T>>;

	class BaseDevice : public Singleton<BaseDevice>
	{
		template<typename T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	public:
		BaseDevice();
		~BaseDevice();
		
		int Initialize(const GfxDeviceConfig& config);
		int Terminate();

	public:
		BaseCommandQueue* CreateCommandQueue();
		void ReleaseCommandQueue(BaseCommandQueue* cq);

		BaseSwapChain* CreateSwapChain(
			const GfxDeviceConfig& config,
			BaseCommandQueue& commandQueue);
		void ReleaseSwapChain(BaseSwapChain* sc);

		BaseGraphicsCommandList* CreateGraphicsCommandList();
		void ReleaseGraphicsCommandList(BaseGraphicsCommandList* gcl);

		BaseFence* CreateFence();
		void ReleaseFence(BaseFence* f);

		BaseFenceEvent* CreateFenceEvent();
		void ReleaseFenceEvent(BaseFenceEvent* e);

		BaseRootSignature* CreateRootSignature(const GfxRootSignatureDesc& desc);
		void ReleaseRootSignature(BaseRootSignature* r);

		BaseGraphicsState* CreateGraphicsState(const GfxGraphicsStateDesc& desc);
		void ReleaseGraphicsState(BaseGraphicsState* s);

		BaseComputeState* CreateComputeState(const GfxComputeStateDesc& desc);
		void ReleaseComputeState(BaseComputeState* s);

		BaseBuffer* CreateBuffer(const GfxBufferDesc& desc);
		void ReleaseBuffer(BaseBuffer* b);

		BaseTexture* CreateTexture(const GfxTextureDesc& desc);
		void ReleaseTexture(BaseTexture* t);

		BaseTexture* CreateTextureWICAndUpload(
			const char* name,
			const void* buffer,
			size_t bufferSize);

		BaseDescriptorHeap* CreateDescriptorHeap(const GfxDescriptorHeapDesc& desc);
		void ReleaseDescriptorHeap(BaseDescriptorHeap* d);

		BaseRaytracingStateDesc* CreateRaytracingStateDesc();
		void ReleaseRaytracingStateDesc(BaseRaytracingStateDesc& raytracingStateDesc);

		BaseRaytracingState* CreateRaytracingState(BaseRaytracingStateDesc& desc);
		void ReleaseRaytracingState(BaseRaytracingState* raytracingState);

		BaseRaytracingScene* CreateRaytracingScene();
		void ReleaseRaytracingScene(BaseRaytracingScene* raytracingScene);

		BaseRaytracingShaderTables* CreateRaytracingShaderTables(GfxRaytracingShaderTablesDesc& desc);
		void ReleaseRaytracingShaderTables(BaseRaytracingShaderTables* shaderTable);
		
		void CreateRenderTargetView(
			BaseDescriptorHeap& descriptorHeap,
			uint32_t descriptorIndex,
			BaseTexture& texture,
			const GfxRenderTargetViewDesc& desc);

		void CreateRenderTargetView(
			GfxDescriptor& descriptor,
			BaseTexture& texture,
			const GfxRenderTargetViewDesc& desc);

		void CreateDepthStencilView(
			BaseDescriptorHeap& descriptorHeap,
			uint32_t descriptorIndex,
			BaseTexture& texture,
			const GfxDepthStencilViewDesc& desc);

		void CreateDepthStencilView(
			GfxDescriptor& descriptor,
			BaseTexture& texture,
			const GfxDepthStencilViewDesc& desc);

		void CreateShaderResourceView(
			BaseDescriptorHeap& descriptorHeap,
			uint32_t descriptorIndex,
			BaseTexture& texture,
			const GfxShaderResourceViewDesc& desc);

		void CreateShaderResourceView(
			GfxDescriptor& descriptor,
			BaseTexture& texture,
			const GfxShaderResourceViewDesc& desc);

		void CreateShaderResourceView(
			BaseDescriptorHeap& descriptorHeap,
			uint32_t descriptorIndex,
			BaseBuffer& buffer,
			const GfxShaderResourceViewDesc& desc);

		void CreateShaderResourceView(
			GfxDescriptor& descriptor,
			BaseBuffer& buffer,
			const GfxShaderResourceViewDesc& desc);
		
		void CreateUnorderedAccessView(
			BaseDescriptorHeap& descriptorHeap,
			uint32_t descriptorIndex,
			BaseTexture& texture,
			const GfxUnorderedAccessViewDesc& desc);

		void CreateUnorderedAccessView(
			GfxDescriptor& descriptor,
			BaseTexture& texture,
			const GfxUnorderedAccessViewDesc& desc);
		
		void CreateSampler(
			BaseDescriptorHeap& descriptorHeap,
			uint32_t descriptorIndex,
			const GfxSamplerDesc& desc);

		void CreateSampler(
			GfxDescriptor& descriptor,
			const GfxSamplerDesc& desc);

		void CreateConstantBufferView(
			BaseDescriptorHeap& descriptorHeap,
			uint32_t descriptorIndex,
			const GfxConstantBufferViewDesc& desc);

		void CreateConstantBufferView(
			GfxDescriptor& descriptor,
			const GfxConstantBufferViewDesc& desc);

		void CopyDescriptors(
			uint32_t                 dstDescriptorRangeCount,
			const GfxCpuDescriptor*  dstDescriptorRangeStarts,
			const uint32_t*          dstDescriptorRangeSizes,
			uint32_t                 srcDescriptorRangeCount,
			const GfxCpuDescriptor*  srcDescriptorRangeStarts,
			const uint32_t*          srcDescriptorRangeSizes,
			GfxDescriptorHeapType    type);

		void CopyDescriptorsSimple(
			uint32_t                 descriptorCount,
			GfxCpuDescriptor         dstDescriptorRangeStart,
			GfxCpuDescriptor         srcDescriptorRangeStart,
			GfxDescriptorHeapType    type);

		// upload用のバッファを作るだけ.
		int CreateUploadBuffer(
			ComPtr<ID3D12Resource>& outBufferUploadHeap,
			GfxTempVector<D3D12_PLACED_SUBRESOURCE_FOOTPRINT>&   outLayouts,
			BaseBuffer&             targetBuffer,
			const void*             srcBuffer,
			size_t                  srcBufferSize);

		int CreateUploadTexture(
			ComPtr<ID3D12Resource>& outTextureUploadHeap,
			GfxTempVector<D3D12_PLACED_SUBRESOURCE_FOOTPRINT>& outLayouts,
			BaseTexture& targetTexture,
			const void* srcBuffer,
			size_t srcBufferSize);

		// upload用のバッファを作って登録、Flushまで転送はしない.
		int UploadBufferLater(
			BaseBuffer&             targetBuffer,
			const void*             srcBuffer,
			size_t                  srcBufferSize,
			GfxResourceStates       before,
			GfxResourceStates       after);

		int UploadTextureLater(
			BaseTexture&            targetTexture,
			const void*             srcBuffer,
			size_t                  srcBufferSize,
			GfxResourceStates       before,
			GfxResourceStates       after);

		// upload用のバッファを転送する.
		int FlushUploadPool(BaseGraphicsCommandList& commandList);

		bool IsDxrAvairable() const{ return m_isDxrAvairable; }

	public:
		PoolAllocatorEx* GetObjectAllocator(){ return m_objectAllocator; }
		PoolAllocatorEx* GetTempAllocator()  { return m_tempAllocator; }

	public:
		ComPtr<ID3D12Device5>& GetComPtrDevice()
		{
			return m_device;
		}

		void* GetNative()
		{
			return m_device.Get();
		}
		
	public:
		size_t GetDescriptorSize(GfxDescriptorHeapType type);

	private:
		int InitializeFactory(ComPtr<IDXGIFactory4>& outDxgiFactory) const;

		int InitializeDevice(
			ComPtr<IDXGIFactory4>& dxgiFactory,
			ComPtr<ID3D12Device5>& outDevice,
			bool enableDxr) const;

	private:
		GfxDeviceConfig                   m_config;
		ComPtr<IDXGIFactory4>             m_dxgiFactory; // 持ちたくないが、DX12ではdeviceから参照出来ないので持つ.
		ComPtr<ID3D12Device5>             m_device;
		ComPtr<ID3D12PipelineState>       m_pipelineState;
		PoolAllocatorEx*                  m_objectAllocator;
		PoolAllocatorEx*                  m_tempAllocator;
		bool                              m_initialized;

		//ComPtr<ID3D12Device5>              m_dxrDevice;
		//ComPtr<ID3D12StateObjectPrototype> m_dxrStateObject;
		bool                              m_isDxrAvairable;

		size_t                            m_descriptorSize[(int)GfxDescriptorHeapType::Max];
		BaseUploadPool                    m_uploadPool;
	};

} // namespace SI

#define SI_BASE_DEVICE() (*SI::BaseDevice::GetInstance())

#endif

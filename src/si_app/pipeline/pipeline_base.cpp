﻿
#include "si_app/pipeline/pipeline_base.h"

#include <string>
#include <si_base/core/core.h>
#include <si_base/gpu/gfx.h>

#include "si_app/file/path_storage.h"

namespace SI
{
	struct PosColorVertex
	{
		float m_x;
		float m_y;
		float m_z;
		float m_r;
		float m_g;
		float m_b;
		float m_a;
	};

	//////////////////////////////////////////////////////////
	
	PipelineBase::PipelineBase(int observerSortKey)
		: AppModule(observerSortKey)
	{
	}

	PipelineBase::~PipelineBase()
	{
		m_device.Terminate();
	}
	
	int PipelineBase::OnInitialize(const AppInitializeInfo& info)
	{
		GfxDeviceConfig deviceConfig;
		deviceConfig.m_width = info.m_width;
		deviceConfig.m_height = info.m_height;
		deviceConfig.m_hWnd = info.m_hWnd;
		if(m_device.Initialize(deviceConfig) != 0)
		{
			return -1;
		}

		GfxCoreDesc coreDesc;
		m_core.Initialize(coreDesc);

		m_commandQueue = m_device.CreateCommandQueue();
		m_swapChain = m_device.CreateSwapChain(deviceConfig, m_commandQueue);

		GfxContextManagerDesc contextManagerDesc;
		m_contextManager.Initialize(contextManagerDesc);
		//m_graphicsCommandList = m_device.CreateGraphicsCommandList();

		m_renderer.Initialize();

		return 0;
	}

	int PipelineBase::OnTerminate()
	{
		//m_device.ReleaseGraphicsCommandList(m_graphicsCommandList);
		
		m_renderer.Terminate();

		m_contextManager.Terminate();
			
		m_device.ReleaseSwapChain(m_swapChain);

		m_device.ReleaseCommandQueue(m_commandQueue);

		m_core.Terminate();

		//m_device.Terminate();

		return 0;
	}
	
	void PipelineBase::OnUpdate(const App& app, const AppUpdateInfo&)
	{
	}

	void PipelineBase::OnRender(const App& app, const AppUpdateInfo&)
	{
		BeginRender();

		EndRender();
	}
	
	void PipelineBase::BeginRender()
	{
		m_contextManager.ResetContexts();

		GfxGraphicsContext& context = m_contextManager.GetGraphicsContext(0);
		context.ResourceBarrier(
			m_swapChain.GetTexture(),
			GfxResourceState::RenderTarget);
		
		m_device.FlushUploadPool(*context.GetGraphicsCommandList());
	}

	void PipelineBase::EndRender()
	{
		GfxGraphicsContext& context = m_contextManager.GetLastGraphicsContext();
		context.ResourceBarrier(
			m_swapChain.GetTexture(),
			GfxResourceState::Common);
		
		m_contextManager.CloseContexts();

		m_contextManager.Execute(m_commandQueue);
			
		int ret = m_swapChain.Present(1);
		if(ret != 0) return;

		if( m_swapChain.Flip() != 0 )
		{
			return;
		}

		m_core.Flip();
	}

} // namespace SI

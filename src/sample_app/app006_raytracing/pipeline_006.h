#pragma once

#include <cstdint>
#include <si_app/pipeline/pipeline_base.h>
#include <si_base/math/math_declare.h>
#include <si_base/gpu/gfx.h>

namespace SI
{
namespace APP006
{
	class Pipeline  : public PipelineBase
	{
	public:
		explicit Pipeline(int observerSortKey);
		virtual ~Pipeline();

		int  OnInitialize(const AppInitializeInfo&) override;
		int  OnTerminate()                          override;

		void OnUpdate(const App& app, const AppUpdateInfo&)         override;
		void OnRender(const App& app, const AppUpdateInfo&)         override;
		void OnKeyboard(const App& app, Key k, bool isDown)         override;

		int LoadAsset(const AppInitializeInfo& info);

	protected:
		struct RaytracingShaderConstant;
		struct TextureShaderConstant;

	protected:
		static const int kMaxRaytracingCompute = 15;
		GfxRootSignatureEx       m_computeRootSignatures;
		GfxRootSignatureEx       m_rootSignatures;
		GfxComputeState          m_computeStates[kMaxRaytracingCompute];
		GfxGraphicsState         m_graphicsStates;
		GfxBufferEx_Constant     m_constantBuffers;
		TextureShaderConstant*   m_textureConstant;

		GfxRootSignatureEx       m_dxrGlobalRootSignatures;
		GfxRootSignatureEx       m_dxrLocalRootSignatures;
		GfxBufferEx_Constant     m_dxrConstantBuffers;
		RaytracingShaderConstant*   m_dxrConstant;
		GfxRaytracingState       m_dxrState;
		GfxDescriptorHeapEx      m_dxrDescriptorHeap;
		GfxBufferEx_Upload       m_dxrVertex;
		GfxBufferEx_Upload       m_dxrIndex;
		GfxRaytracingScene       m_dxrScene;
		GfxRaytracingShaderTables m_dxrShaderTables;
		
		GfxComputeShader         m_raytracingCS[kMaxRaytracingCompute];

		GfxVertexShader          m_textureVS;
		GfxPixelShader           m_texturePS;

		GfxBufferEx_Vertex       m_quadVertexBuffer;		
		GfxTestureEx_Uav         m_resultTexture;

		GfxDynamicSampler        m_sampler;
		int                      m_currentComputeId;
	};
	
} // namespace APP006
} // namespace SI
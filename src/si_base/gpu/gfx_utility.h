﻿#pragma once

#include "si_base/core/core.h"
#include "si_base/gpu/gfx_enum.h"

namespace SI
{
	inline size_t GetFormatBits(GfxFormat format)
	{
		size_t kTable[] =
		{
			0,       // GfxFormat::Unknown,
			8 * 16,  // GfxFormat::R32G32B32A32_Typeless,
			8 * 16,  // GfxFormat::R32G32B32A32_Float,
			8 * 16,  // GfxFormat::R32G32B32A32_Uint,
			8 * 16,  // GfxFormat::R32G32B32A32_Sint,
			8 * 12,  // GfxFormat::R32G32B32_Typeless,
			8 * 12,  // GfxFormat::R32G32B32_Float,
			8 * 12,  // GfxFormat::R32G32B32_Uint,
			8 * 12,  // GfxFormat::R32G32B32_Sint,
			8 * 8,   // GfxFormat::R16G16B16A16_Typeless,
			8 * 8,   // GfxFormat::R16G16B16A16_Float,
			8 * 8,   // GfxFormat::R16G16B16A16_Unorm,
			8 * 8,   // GfxFormat::R16G16B16A16_Uint,
			8 * 8,   // GfxFormat::R16G16B16A16_Snorm,
			8 * 8,   // GfxFormat::R16G16B16A16_Sint,
			8 * 8,   // GfxFormat::R32G32_Typeless,
			8 * 8,   // GfxFormat::R32G32_Float,
			8 * 8,   // GfxFormat::R32G32_Uint,
			8 * 8,   // GfxFormat::R32G32_Sint,
			8 * 8,   // GfxFormat::R32G8X24_Typeless,
			8 * 8,   // GfxFormat::D32_Float_S8X24_Uint,
			8 * 8,   // GfxFormat::R32_Float_X8X24_Typeless,
			8 * 8,   // GfxFormat::X32_Typeless_G8X24_Uint,
			8 * 4,   // GfxFormat::R10G10B10A2_Typeless,
			8 * 4,   // GfxFormat::R10G10B10A2_Unorm,
			8 * 4,   // GfxFormat::R10G10B10A2_Uint,
			8 * 4,   // GfxFormat::R11G11B10_Float,
			8 * 4,   // GfxFormat::R8G8B8A8_Typeless,
			8 * 4,   // GfxFormat::R8G8B8A8_Unorm,
			8 * 4,   // GfxFormat::R8G8B8A8_Unorm_SRGB,
			8 * 4,   // GfxFormat::R8G8B8A8_Uint,
			8 * 4,   // GfxFormat::R8G8B8A8_Snorm,
			8 * 4,   // GfxFormat::R8G8B8A8_Sint,
			8 * 4,   // GfxFormat::R16G16_Typeless,
			8 * 4,   // GfxFormat::R16G16_Float,
			8 * 4,   // GfxFormat::R16G16_Unorm,
			8 * 4,   // GfxFormat::R16G16_Uint,
			8 * 4,   // GfxFormat::R16G16_Snorm,
			8 * 4,   // GfxFormat::R16G16_Sint,
			8 * 4,   // GfxFormat::R32_Typeless,
			8 * 4,   // GfxFormat::D32_Float,
			8 * 4,   // GfxFormat::R32_Float,
			8 * 4,   // GfxFormat::R32_Uint,
			8 * 4,   // GfxFormat::R32_Sint,
			8 * 4,   // GfxFormat::R24G8_Typeless,
			8 * 4,   // GfxFormat::D24_Unorm_S8_Uint,
			8 * 4,   // GfxFormat::R24_Unorm_X8_Typeless,
			8 * 4,   // GfxFormat::X24_Typeless_G8_Uint,
			8 * 2,   // GfxFormat::R8G8_Typeless,
			8 * 2,   // GfxFormat::R8G8_Unorm,
			8 * 2,   // GfxFormat::R8G8_Uint,
			8 * 2,   // GfxFormat::R8G8_Snorm,
			8 * 2,   // GfxFormat::R8G8_Sint,
			8 * 2,   // GfxFormat::R16_Typeless,
			8 * 2,   // GfxFormat::R16_Float,
			8 * 2,   // GfxFormat::D16_Unorm,
			8 * 2,   // GfxFormat::R16_Unorm,
			8 * 2,   // GfxFormat::R16_Uint,
			8 * 2,   // GfxFormat::R16_Snorm,
			8 * 2,   // GfxFormat::R16_Sint,
			8 * 1,   // GfxFormat::R8_Typeless,
			8 * 1,   // GfxFormat::R8_Unorm,
			8 * 1,   // GfxFormat::R8_Uint,
			8 * 1,   // GfxFormat::R8_Snorm,
			8 * 1,   // GfxFormat::R8_Sint,
			8 * 1,   // GfxFormat::A8_Unorm,
			1,       // GfxFormat::R1_Unorm,
			8 * 4,   // GfxFormat::R9G9B9E5_SHAREDEXP,
			8 * 4,   // GfxFormat::R8G8_B8G8_Unorm,
			8 * 4,   // GfxFormat::G8R8_G8B8_Unorm,
			8 / 2,   // GfxFormat::BC1_Typeless,
			8 / 2,   // GfxFormat::BC1_Unorm,
			8 / 2,   // GfxFormat::BC1_Unorm_SRGB,
			8 * 1,   // GfxFormat::BC2_Typeless,
			8 * 1,   // GfxFormat::BC2_Unorm,
			8 * 1,   // GfxFormat::BC2_Unorm_SRGB,
			8 * 1,   // GfxFormat::BC3_Typeless,
			8 * 1,   // GfxFormat::BC3_Unorm,
			8 * 1,   // GfxFormat::BC3_Unorm_SRGB,
			8 / 2,   // GfxFormat::BC4_Typeless,
			8 / 2,   // GfxFormat::BC4_Unorm,
			8 / 2,   // GfxFormat::BC4_Snorm,
			8 * 1,   // GfxFormat::BC5_Typeless,
			8 * 1,   // GfxFormat::BC5_Unorm,
			8 * 1,   // GfxFormat::BC5_Snorm,
			8 * 2,   // GfxFormat::B5G6R5_Unorm,
			8 * 2,   // GfxFormat::B5G5R5A1_Unorm,
			8 * 4,   // GfxFormat::B8G8R8A8_Unorm,
			8 * 4,   // GfxFormat::B8G8R8X8_Unorm,
			8 * 4,   // GfxFormat::R10G10B10_XR_BIAS_A2_Unorm,
			8 * 4,   // GfxFormat::B8G8R8A8_Typeless,
			8 * 4,   // GfxFormat::B8G8R8A8_Unorm_SRGB,
			8 * 4,   // GfxFormat::B8G8R8X8_Typeless,
			8 * 4,   // GfxFormat::B8G8R8X8_Unorm_SRGB,
			8 * 1,   // GfxFormat::BC6H_Typeless,
			8 * 1,   // GfxFormat::BC6H_UF16,
			8 * 1,   // GfxFormat::BC6H_SF16,
			8 * 1,   // GfxFormat::BC7_Typeless,
			8 * 1,   // GfxFormat::BC7_Unorm,
			8 * 1,   // GfxFormat::BC7_Unorm_SRGB,		//GfxFormat::AYUV,
			//kGfxF  ormat_Y410,
			//GfxFormat::Y416,
			//GfxFormat::NV12,
			//GfxFormat::P010,
			//GfxFormat::P016,
			//GfxFormat::420_OPAQUE,
			//GfxFormat::YUY2,
			//GfxFormat::Y210,
			//GfxFormat::Y216,
			//GfxFormat::NV11,
			//GfxFormat::AI44,
			//GfxFormat::IA44,
			//GfxFormat::P8,
			//GfxFormat::A8P8,
			//GfxFormat::B4G4R4A4_Unorm,
			//GfxFormat::P208,
			//GfxFormat::V208,
			//GfxFormat::V408,
		};
		static_assert(SI::ArraySize(kTable) == (size_t)GfxFormat::Max, "tableError");

		return kTable[(int)format];
	}
	
	inline bool IsBlockCompression(GfxFormat format)
	{
		bool kTable[] =
		{
			false,       // GfxFormat::Unknown,
			false,  // GfxFormat::R32G32B32A32_Typeless,
			false,  // GfxFormat::R32G32B32A32_Float,
			false,  // GfxFormat::R32G32B32A32_Uint,
			false,  // GfxFormat::R32G32B32A32_Sint,
			false,  // GfxFormat::R32G32B32_Typeless,
			false,  // GfxFormat::R32G32B32_Float,
			false,  // GfxFormat::R32G32B32_Uint,
			false,  // GfxFormat::R32G32B32_Sint,
			false,   // GfxFormat::R16G16B16A16_Typeless,
			false,   // GfxFormat::R16G16B16A16_Float,
			false,   // GfxFormat::R16G16B16A16_Unorm,
			false,   // GfxFormat::R16G16B16A16_Uint,
			false,   // GfxFormat::R16G16B16A16_Snorm,
			false,   // GfxFormat::R16G16B16A16_Sint,
			false,   // GfxFormat::R32G32_Typeless,
			false,   // GfxFormat::R32G32_Float,
			false,   // GfxFormat::R32G32_Uint,
			false,   // GfxFormat::R32G32_Sint,
			false,   // GfxFormat::R32G8X24_Typeless,
			false,   // GfxFormat::D32_Float_S8X24_Uint,
			false,   // GfxFormat::R32_Float_X8X24_Typeless,
			false,   // GfxFormat::X32_Typeless_G8X24_Uint,
			false,   // GfxFormat::R10G10B10A2_Typeless,
			false,   // GfxFormat::R10G10B10A2_Unorm,
			false,   // GfxFormat::R10G10B10A2_Uint,
			false,   // GfxFormat::R11G11B10_Float,
			false,   // GfxFormat::R8G8B8A8_Typeless,
			false,   // GfxFormat::R8G8B8A8_Unorm,
			false,   // GfxFormat::R8G8B8A8_Unorm_SRGB,
			false,   // GfxFormat::R8G8B8A8_Uint,
			false,   // GfxFormat::R8G8B8A8_Snorm,
			false,   // GfxFormat::R8G8B8A8_Sint,
			false,   // GfxFormat::R16G16_Typeless,
			false,   // GfxFormat::R16G16_Float,
			false,   // GfxFormat::R16G16_Unorm,
			false,   // GfxFormat::R16G16_Uint,
			false,   // GfxFormat::R16G16_Snorm,
			false,   // GfxFormat::R16G16_Sint,
			false,   // GfxFormat::R32_Typeless,
			false,   // GfxFormat::D32_Float,
			false,   // GfxFormat::R32_Float,
			false,   // GfxFormat::R32_Uint,
			false,   // GfxFormat::R32_Sint,
			false,   // GfxFormat::R24G8_Typeless,
			false,   // GfxFormat::D24_Unorm_S8_Uint,
			false,   // GfxFormat::R24_Unorm_X8_Typeless,
			false,   // GfxFormat::X24_Typeless_G8_Uint,
			false,   // GfxFormat::R8G8_Typeless,
			false,   // GfxFormat::R8G8_Unorm,
			false,   // GfxFormat::R8G8_Uint,
			false,   // GfxFormat::R8G8_Snorm,
			false,   // GfxFormat::R8G8_Sint,
			false,   // GfxFormat::R16_Typeless,
			false,   // GfxFormat::R16_Float,
			false,   // GfxFormat::D16_Unorm,
			false,   // GfxFormat::R16_Unorm,
			false,   // GfxFormat::R16_Uint,
			false,   // GfxFormat::R16_Snorm,
			false,   // GfxFormat::R16_Sint,
			false,   // GfxFormat::R8_Typeless,
			false,   // GfxFormat::R8_Unorm,
			false,   // GfxFormat::R8_Uint,
			false,   // GfxFormat::R8_Snorm,
			false,   // GfxFormat::R8_Sint,
			false,   // GfxFormat::A8_Unorm,
			false,   // GfxFormat::R1_Unorm,
			false,   // GfxFormat::R9G9B9E5_SHAREDEXP,
			false,   // GfxFormat::R8G8_B8G8_Unorm,
			false,   // GfxFormat::G8R8_G8B8_Unorm,
			true,    // GfxFormat::BC1_Typeless,
			true,    // GfxFormat::BC1_Unorm,
			true,    // GfxFormat::BC1_Unorm_SRGB,
			true,    // GfxFormat::BC2_Typeless,
			true,    // GfxFormat::BC2_Unorm,
			true,    // GfxFormat::BC2_Unorm_SRGB,
			true,    // GfxFormat::BC3_Typeless,
			true,    // GfxFormat::BC3_Unorm,
			true,    // GfxFormat::BC3_Unorm_SRGB,
			true,    // GfxFormat::BC4_Typeless,
			true,    // GfxFormat::BC4_Unorm,
			true,    // GfxFormat::BC4_Snorm,
			true,    // GfxFormat::BC5_Typeless,
			true,    // GfxFormat::BC5_Unorm,
			true,    // GfxFormat::BC5_Snorm,
			false,   // GfxFormat::B5G6R5_Unorm,
			false,   // GfxFormat::B5G5R5A1_Unorm,
			false,   // GfxFormat::B8G8R8A8_Unorm,
			false,   // GfxFormat::B8G8R8X8_Unorm,
			false,   // GfxFormat::R10G10B10_XR_BIAS_A2_Unorm,
			false,   // GfxFormat::B8G8R8A8_Typeless,
			false,   // GfxFormat::B8G8R8A8_Unorm_SRGB,
			false,   // GfxFormat::B8G8R8X8_Typeless,
			false,   // GfxFormat::B8G8R8X8_Unorm_SRGB,
			true,    // GfxFormat::BC6H_Typeless,
			true,    // GfxFormat::BC6H_UF16,
			true,    // GfxFormat::BC6H_SF16,
			true,    // GfxFormat::BC7_Typeless,
			true,    // GfxFormat::BC7_Unorm,
			true,    // GfxFormat::BC7_Unorm_SRGB,
			//GfxFormat::AYUV,
			//kGfxFormat_Y410,
			//GfxFormat::Y416,
			//GfxFormat::NV12,
			//GfxFormat::P010,
			//GfxFormat::P016,
			//GfxFormat::420_OPAQUE,
			//GfxFormat::YUY2,
			//GfxFormat::Y210,
			//GfxFormat::Y216,
			//GfxFormat::NV11,
			//GfxFormat::AI44,
			//GfxFormat::IA44,
			//GfxFormat::P8,
			//GfxFormat::A8P8,
			//GfxFormat::B4G4R4A4_Unorm,
			//GfxFormat::P208,
			//GfxFormat::V208,
			//GfxFormat::V408,
		};
		static_assert(SI::ArraySize(kTable) == (size_t)GfxFormat::Max, "tableError");

		return kTable[(int)format];
	}

	inline bool IsArrayDimension(GfxDimension dimension)
	{
		return dimension == GfxDimension::Texture1DArray ||
			   dimension == GfxDimension::Texture2DArray ||
			   dimension == GfxDimension::Texture2DMSArray ||
			   dimension == GfxDimension::TextureCubeArray;
	}

	inline bool IsCubeDimension(GfxDimension dimension)
	{
		return dimension == GfxDimension::TextureCube ||
			   dimension == GfxDimension::TextureCubeArray;
	}

	inline GfxShaderVisibility GetShaderVisibility(GfxShaderType shaderType)
	{
		switch (shaderType)
		{
		case GfxShaderType::Vertex:
			return GfxShaderVisibility::Vertex;
		case GfxShaderType::Pixel:
			return GfxShaderVisibility::Pixel;
		case GfxShaderType::Geometry:
			return GfxShaderVisibility::Geometry;
		case GfxShaderType::Hull:
			return GfxShaderVisibility::Hull;
		case GfxShaderType::Domain:
			return GfxShaderVisibility::Domain;
		case GfxShaderType::Compute:
		default:
			return GfxShaderVisibility::All;
		}
	}

	inline const char* GetSemanticsName(GfxSemanticsType type)
	{
		static const char* kSemanticsNames[] =
		{
			"",         // Invalid
			"POSITION", // Position
			"NORMAL",   // Normal
			"TEXCOORD", // UV,
			"TANGENT",  // Tangent,
			"COLOR",    // Color,
		};
		SI_ASSERT( (0 < (int)type) && ((int)type < (int)ArraySize(kSemanticsNames)));

		return kSemanticsNames[(int)type];
	}

} // namespace SI

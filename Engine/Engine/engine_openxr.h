#pragma once

#ifdef _WIN32
#define XR_USE_PLATFORM_WIN32
#define XR_USE_GRAPHICS_API_D3D11
#define GRAPHICS_DX11
#endif

#ifdef GRAPHICS_DX11
#define XR_USE_GRAPHICS_API_D3D11
#include <d3d11.h>
#include <DirectXMath.h>
#endif

#ifdef GRAPHICS_VULKAN
#define XR_USE_GRAPHICS_API_VULKAN
#include <vulkan.h>
#endif

#include <openxr/openxr.h>
#include <openxr/openxr_platform.h>

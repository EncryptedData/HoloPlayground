module;
#define VULKAN_HPP_NO_CONSTRUCTORS
#define VULKAN_HPP_DISPATCH_LOADER_DYNAMIC 1
#include <vulkan/vulkan.hpp>
#include <iostream>

export module Engine.Vulkan;

VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE
std::string layer = "layer";
std::vector<std::string> requestedValidationLayers;


namespace VulkanEngine
{
	export class RenderEngine {
	private:
		vk::Instance _instance;
		vk::DynamicLoader _loader;

		bool _validationEnabled = true;

		bool initDynamicLoader();
		bool initInstance();
		bool validateExtensions();
		bool enableValidation();

	

	public:
		bool Init();
	};


}

module :private;

namespace VulkanEngine
{
	bool RenderEngine::Init()
	{
		initDynamicLoader();
		initInstance();
		validateExtensions();
		return true;

	}

	bool RenderEngine::initDynamicLoader()
	{
		PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = _loader.getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");
		VULKAN_HPP_DEFAULT_DISPATCHER.init(vkGetInstanceProcAddr);

		return true;
	}

	bool RenderEngine::initInstance()
	{
		vk::ApplicationInfo appInfo{ .pApplicationName = "No.", .applicationVersion = 1, .pEngineName = "I said no", .engineVersion = 1, .apiVersion = VK_API_VERSION_1_3 };

		vk::InstanceCreateInfo instanceCreateInfo{ .pApplicationInfo = &appInfo };

		vk::Instance instance = vk::createInstance(instanceCreateInfo, nullptr);

		_instance = instance;



		//TODO: Handle errors if instance creation fails

		return true;
	}

	bool RenderEngine::validateExtensions()
	{
		std::vector<vk::ExtensionProperties> properties = vk::enumerateInstanceExtensionProperties();

		if (properties.empty())
		{
			return false;
		}

		for (auto extensionProperty : properties) 
		{

		}
	}
	bool RenderEngine::enableValidation()
	{
		std::vector<vk::LayerProperties> layerProperties = vk::enumerateInstanceLayerProperties();

		if (layerProperties.empty())
		{
			return false;
		}

		for (auto layer : requestedValidationLayers)
		{
			/*
			std::vector<vk::LayerProperties>::iterator it = std::find(layerProperties.begin(), layerProperties.end(), [&layer](std::vector<vk::LayerProperties>::iterator x) {
				return layer == (*x).layerName;
				});
				*/
		
		}

		return false;
	}
}




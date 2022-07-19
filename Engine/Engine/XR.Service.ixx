
module;

#include "engine_openxr.h"

export module Engine.XR.Service;
import <cstdint>;
import <vector>;
import <cstring>;
import <algorithm>;

namespace Engine::XR
{
	export using ExtensionList = std::vector<const char*>;

	export class OpenXrService
	{
	public:

		~OpenXrService() = default;

		explicit OpenXrService();

		bool Initialize(const ExtensionList& wanted_extensions);

	private:

		XrInstance _instance;
		XrSession _session;
		XrSessionState _sessionState;
		XrSpace _space;
		XrSystemId _systemId;
		XrEnvironmentBlendMode _blendMode;
		XrDebugUtilsMessengerEXT _debugMessenger;

		std::vector<XrView> _views;
		std::vector<XrViewConfigurationView> _configViews;
		
		bool _debugMessengerEnabled;

		/// <summary>
		/// Query OpenXR for all extensions in wanted_extensions.
		/// </summary>
		/// <param name="wanted_extensions">The OpenXR extensions to query.</param>
		/// <returns>TRUE if all extensions are available by this runtime, FALSE otherwise</returns>
		bool CheckExtensionsAreAvailable(const ExtensionList& wanted_extensions);

		/// <summary>
		/// Init OpenXR with the given extensions
		/// </summary>
		/// <param name="extensions">The extensions to enable</param>
		/// <returns>TRUE if OpenXR was successful, FALSE otherwise</returns>
		bool CreateXrInstance(const ExtensionList& extensions);

		/// <summary>
		/// If the user has provided a debugging extension, then enable debugging
		/// </summary>
		/// <param name="wantedExtensions">The extensions to query</param>
		void EnableDebugExtensionsIfDefined(const ExtensionList& wantedExtensions);

		bool QuerySystemInfo();

		bool QueryEnvironmentBlendModes();
	};

	

}

module :private;

namespace Engine::XR
{
	const XrFormFactor AppConfigForm = XR_FORM_FACTOR_HEAD_MOUNTED_DISPLAY;
	const XrViewConfigurationType AppConfigView = XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO;

	OpenXrService::OpenXrService() :
		_instance{nullptr},
		_debugMessenger{},
		_debugMessengerEnabled{false}
	{
	}

	bool OpenXrService::Initialize(const ExtensionList& wanted_extensions)
	{
		if (!CheckExtensionsAreAvailable(wanted_extensions))
			return false;

		if (!CreateXrInstance(wanted_extensions))
			return false;

		EnableDebugExtensionsIfDefined(wanted_extensions);

		if (!QuerySystemInfo())
			return false;

		return true;
	}

	bool OpenXrService::CheckExtensionsAreAvailable(const ExtensionList& wanted_extensions)
	{
		std::uint32_t platformExtensionCount = 0;
		xrEnumerateInstanceExtensionProperties(nullptr, 0, &platformExtensionCount, nullptr);
		std::vector<XrExtensionProperties> platformExtensions{ platformExtensionCount, {XR_TYPE_EXTENSION_PROPERTIES} };
		xrEnumerateInstanceExtensionProperties(nullptr, platformExtensionCount, &platformExtensionCount, platformExtensions.data());

		for (const auto& wanted_extension : wanted_extensions)
		{
			bool foundExtension = false;

			for (const auto& platformExtension : platformExtensions)
			{
				if (std::strcmp(wanted_extension, platformExtension.extensionName) == 0)
				{
					foundExtension = true;
					break;
				}
			}

			if (!foundExtension)
			{
				return false;
			}
		}

		return true;
	}

	bool OpenXrService::CreateXrInstance(const ExtensionList& extensions)
	{
		const char* HOLOPLAYGROUND_STR = "HoloPlayground";

		XrInstanceCreateInfo createInfo = { XR_TYPE_INSTANCE_CREATE_INFO };
		createInfo.enabledExtensionCount = (std::uint32_t)extensions.size();
		createInfo.enabledExtensionNames = extensions.data();
		createInfo.applicationInfo.apiVersion = XR_CURRENT_API_VERSION;
		createInfo.applicationInfo.applicationVersion = XR_MAKE_VERSION(0, 0, 1);
		createInfo.applicationInfo.engineVersion = XR_MAKE_VERSION(0, 0, 1);
		std::strcpy(createInfo.applicationInfo.applicationName, HOLOPLAYGROUND_STR);
		std::strcpy(createInfo.applicationInfo.engineName, HOLOPLAYGROUND_STR);

		XrResult result = xrCreateInstance(&createInfo, &_instance);
		if (result != XrResult::XR_SUCCESS || !_instance)
		{
			return false;
		}

		return true;
	}

	void OpenXrService::EnableDebugExtensionsIfDefined(const ExtensionList& wantedExtensions)
	{
		// Is the debug extension wanted?
		auto iter = std::find(wantedExtensions.begin(), wantedExtensions.end(), XR_EXT_DEBUG_UTILS_EXTENSION_NAME);
		if (wantedExtensions.end() == iter)
		{
			return;
		}

		XrDebugUtilsMessengerCreateInfoEXT debugInfo = { XR_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT };
		debugInfo.messageTypes =
			XR_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
			XR_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
			XR_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT |
			XR_DEBUG_UTILS_MESSAGE_TYPE_CONFORMANCE_BIT_EXT;

		debugInfo.messageSeverities =
			XR_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
			XR_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
			XR_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
			XR_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

		debugInfo.userCallback = [](XrDebugUtilsMessageSeverityFlagsEXT /*severity*/, XrDebugUtilsMessageTypeFlagsEXT /*types*/, const XrDebugUtilsMessengerCallbackDataEXT* msg, void* /*userData*/)
		{
			printf("%s: %s\n", msg->functionName, msg->message);

			return (XrBool32)XR_FALSE;
		};

		PFN_xrCreateDebugUtilsMessengerEXT fn_xrCreateDebugUtilsMessengerEXT = nullptr;
		xrGetInstanceProcAddr(_instance, "xrCreateDebugUtilsMessengerEXT", (PFN_xrVoidFunction*)(&fn_xrCreateDebugUtilsMessengerEXT));

		if (!fn_xrCreateDebugUtilsMessengerEXT)
		{
			return;
		}
		
		XrResult result = fn_xrCreateDebugUtilsMessengerEXT(_instance, &debugInfo, &_debugMessenger);

		if (XrResult::XR_SUCCESS == result)
		{
			_debugMessengerEnabled = true;
		}
	}

	bool OpenXrService::QuerySystemInfo()
	{
		XrSystemGetInfo systemInfo = { XR_TYPE_SYSTEM_GET_INFO };
		systemInfo.formFactor = XR_FORM_FACTOR_HEAD_MOUNTED_DISPLAY;
		XrResult result = xrGetSystem(_instance, &systemInfo, &_systemId);
		return result == XrResult::XR_SUCCESS;
	}

	bool OpenXrService::QueryEnvironmentBlendModes()
	{
		
		std::uint32_t blendCount = 0;
		XrResult result = xrEnumerateEnvironmentBlendModes(_instance, _systemId, AppConfigView, 1, &blendCount, &_blendMode);

		return result == XrResult::XR_SUCCESS;
	}
}


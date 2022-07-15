
import Engine.XR;
import Engine.Vulkan;

int main()
{
	
	Engine::XR::ExtensionList extensions{};
	Engine::XR::OpenXrPlatform platform{};

	VulkanEngine::RenderEngine engine;

	engine.Init();

	if (!platform.Initialize(extensions))
	{
		return -1;
	}



	return 0;
}

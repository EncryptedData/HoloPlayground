
import Engine.XR;

int main()
{
	Engine::XR::ExtensionList extensions{};
	Engine::XR::OpenXrPlatform platform{};

	if (!platform.Initialize(extensions))
	{
		return -1;
	}

	return 0;
}

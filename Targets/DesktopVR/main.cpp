
import Engine.XR;

int main()
{
	Engine::XR::OpenXrPlatform platform{};

	if (!platform.Initialize())
	{
		return -1;
	}

	return 0;
}

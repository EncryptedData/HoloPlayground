export module SDL.Platform;
import Engine.Core.Platform;
import <SDL2/SDL.h>;

export class SDLPlatform :
	public Engine::Core::IPlatform
{
public:
	explicit SDLPlatform() :
		_window{nullptr},
		_shouldContinue{true},
		_windowWidth{-1},
		_windowHeight{-1}
	{}

	~SDLPlatform() override
	{
		if (_window)
		{
			SDL_DestroyWindow(_window);
		}

		SDL_Quit();
	}

	bool Initialize(int width, int height)
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
		{
			return false;
		}

		_windowWidth = width;
		_windowHeight = height;

		_window = SDL_CreateWindow("HoloPlayground", SDL_WINDOWPOS_UNDEFINED, 
			SDL_WINDOWPOS_UNDEFINED, _windowWidth, _windowHeight, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);

		if (!_window)
		{
			return false;
		}

		return true;
	}

	virtual void Update() override
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				_shouldContinue = false;
				break;
			}
		}
	}

	virtual bool ShouldContinue() override
	{
		return _shouldContinue;
	}

private:
	SDL_Window* _window;
	bool _shouldContinue;
	int _windowWidth;
	int _windowHeight;
};
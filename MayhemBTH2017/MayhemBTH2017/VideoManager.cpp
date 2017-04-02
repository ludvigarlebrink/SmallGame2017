#include "VideoManager.h"



VideoManager * VideoManager::m_instance = nullptr;


//::.. DUMMY CONSTRUCTORS ..:://
VideoManager::VideoManager()
{
}


VideoManager::~VideoManager()
{
}


//::.. FAKE CONSTRUCTORS ..:://
void VideoManager::StartUp()
{
	if (m_instance == nullptr)
	{
		Init();
	}
}

void VideoManager::ShutDown()
{
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}


//::.. GET FUNCTIONS ..:://
VideoManager & VideoManager::Get()
{
	return *m_instance;
}

glm::vec2 VideoManager::GetScreenResolution() const
{
	return glm::vec2();
}


//::.. HELPER FUNCTIONS ..:://
void VideoManager::Init()
{
	// Init SDL.
	SDL_Init(SDL_INIT_VIDEO);

	// Create the application window.
	m_window = SDL_CreateWindow(
		"Super Amazeballs Game",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);

	// Window debugging.

#ifdef _DEBUG

	if (m_window == nullptr)
	{
		SDL_GetError();
		exit(1);
	}

#endif

}
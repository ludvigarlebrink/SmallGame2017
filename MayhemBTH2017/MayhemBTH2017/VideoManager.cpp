#include "VideoManager.h"



VideoManager * VideoManager::m_instance = nullptr;


//::.. DUMMY CONSTRUCTORS ..:://
VideoManager::VideoManager()
{
}


VideoManager::~VideoManager()
{
}


//::.. FAKE FUNCTIONS ..:://
void VideoManager::StartUp()
{
	if (m_instance == nullptr)
	{
		m_instance = this;
		Init();
	}
}

void VideoManager::ShutDown()
{
	DisplayShutDown();
}


//::.. GET FUNCTIONS ..:://
VideoManager * VideoManager::Get()
{
	return m_instance;
}


bool VideoManager::GetIsClosed()const
{
	return m_isClosed;
}

int VideoManager::GetScreenHeight()const
{
	return m_screenHeight;
}

int VideoManager::GetScreenWidth()const
{
	return m_screenWidth;
}

SDL_Window* VideoManager::GetWindow()const
{
	return m_window;
}


//::.. HELPER FUNCTIONS ..:://
void VideoManager::Init()
{
	// Init SDL.
	SDL_Init(SDL_INIT_VIDEO);

	DisplayCreate(800, 600, "test");

	// Window debugging.

#ifdef _DEBUG

	if (m_window == nullptr)
	{
		SDL_GetError();
		exit(1);
	}

#endif

}

#ifdef _DEBUG

static void APIENTRY openglCallbackFunction(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei lenght, const GLchar* message, const void* userParam)
{
	std::string output = message;
	output += "\n";
	OutputDebugStringA((output).c_str());
}

#endif

void VideoManager::DisplayCreate(int width, int height, const std::string& title)
{
	m_screenWidth = width;
	m_screenHeight = height;

	SDL_GL_SetAttribute(
		SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG
	);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
		, width, height, SDL_WINDOW_OPENGL);

	m_glContext = SDL_GL_CreateContext(m_window);
	GLenum status = glewInit();

#ifdef _DEBUG

	if (status != GLEW_OK)
	{
		std::cout << "GLEW STATUS FAIL\n";
	}

	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(openglCallbackFunction, nullptr);
	glDebugMessageControl(
		GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true);

#endif

	SDL_SetRelativeMouseMode(SDL_FALSE);
	m_isClosed = false;
}

void VideoManager::DisplayShutDown()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();

}

void VideoManager::DisplayUpdate()
{
	SDL_GL_SwapWindow(m_window);
}

//::.. SET FUNCTIONS ..:://

void VideoManager::SetIsClosed(bool x)
{
	m_isClosed = x;
}

void VideoManager::SetScreenHeight(int x)
{
	m_screenHeight = x;
}

void VideoManager::SetScreenWidth(int x)
{
	m_screenWidth = x;
}


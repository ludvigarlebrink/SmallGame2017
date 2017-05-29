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
		m_instance = this;
		Init();
	}
}

void VideoManager::ShutDown()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}


//::.. GET FUNCTIONS ..:://
VideoManager * VideoManager::Get()
{
	return m_instance;
}


bool VideoManager::GetIsClosed() const
{
	return m_isClosed;
}


int VideoManager::GetHeight() const
{
	return m_height;
}


int VideoManager::GetWidth() const
{
	return m_width;
}


SDL_Window* VideoManager::GetWindow() const
{
	return m_window;
}


#ifdef _DEBUG

static void APIENTRY openglCallbackFunction(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei lenght, const GLchar* message, const void* userParam)
{
	std::string output = message;
	output += "\n";
	OutputDebugStringA((output).c_str());
}

#endif

//::.. HELP FUNCTIONS ..:://
void VideoManager::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(
		SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG
	);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_width = 1280;
	m_height = 768;

	m_window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		m_width, m_height, SDL_WINDOW_OPENGL);

	SDL_SetWindowFullscreen(m_window, 0);
	SDL_ShowCursor(SDL_DISABLE);

	m_glContext = SDL_GL_CreateContext(m_window);
	GLenum status = glewInit();

	if (status != GLEW_OK)
	{
		// << "GLEW STATUS FAIL\n";
	}

	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glEnable(GL_DEBUG_OUTPUT);
#ifdef _DEBUG
	glDebugMessageCallback(openglCallbackFunction, nullptr);
#endif
	glDebugMessageControl(
		GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true);


	m_isClosed = false;
}




void VideoManager::Swap()
{
	SDL_GL_SwapWindow(m_window);
}

//::.. SET FUNCTIONS ..:://

void VideoManager::SetIsClosed(bool x)
{
	m_isClosed = x;
}

void VideoManager::SetHeight(int x)
{
	m_height = x;
}

void VideoManager::SetWidth(int x)
{
	m_width = x;
}


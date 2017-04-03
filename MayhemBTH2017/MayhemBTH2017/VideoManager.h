#ifndef __VIDEOMANAGER_H__
#define __VIDEOMANAGER_H__


#include "glew.h"
#include <Windows.h>
#include <assert.h>
#include <string>
#include <SDL.h>
#include <glm.hpp>
#include <iostream>



class VideoManager
{
public:
	//::.. DUMMY CONSTRUCTORS ..:://
	VideoManager();
	virtual ~VideoManager();

	//::.. FAKE FUNCTIONS ..:://
	void StartUp();
	void ShutDown();

	//::.. GET FUNCTIONS ..:://
	static VideoManager* Get();
	bool GetIsClosed()const;
	int GetScreenHeight()const;
	int GetScreenWidth()const;
	SDL_Window* GetWindow()const;
	void Swap();

	//::.. SET FUNCTIONS ..:://
	void SetIsClosed(bool x);
	void SetScreenHeight(int x);
	void SetScreenWidth(int x);

private:
	//::.. HELPER FUNCTIONS ..:://
	void Init();
	void Create(int width, int height, const std::string& title);


private:
	static VideoManager * m_instance;

	SDL_Window * m_window;

	glm::vec2	m_scrRes;
	bool		m_isFullScreen;

	bool m_isClosed;
	int m_screenHeight;
	int m_screenWidth;
	SDL_GLContext m_glContext;
};


#endif
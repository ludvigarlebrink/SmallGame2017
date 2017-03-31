#ifndef __VIDEOMANAGER_H__
#define __VIDEOMANAGER_H__


#include <assert.h>
#include <SDL.h>
#include <glm.hpp>
#include <string>
#include <glew.h>
#include <iostream>
#include <Windows.h>


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
	VideoManager& Get();

	glm::vec2 GetScreenResolution() const;


	//::.. SDL FUNCTIONS ..:://
	void DisplayCreate(int width, int height, const std::string& title);
	void DisplayShutDown();
	void DisplayUpdate();

	//::.. SDL SET FUNCTIONS ..:://
	void SetIsClosed(bool x);
	void SetScreenHeight(int x);
	void SetScreenWidth(int x);

	//::.. SDL GET FUNCTIONS ..:://
	bool GetIsClosed()const;
	int GetScreenHeight()const;
	int GetScreenWidth()const;
	SDL_Window* GetWindow()const;


private:
	//::.. HELPER FUNCTIONS ..:://
	void Init();

private:
	static VideoManager * m_instance;


	//::.. SDL MEMBERS ..:://
	glm::vec2	m_scrRes;
	bool		m_isFullScreen;
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_isClosed;
	int m_screenWidth;
	int m_screenHeight;
};


#endif
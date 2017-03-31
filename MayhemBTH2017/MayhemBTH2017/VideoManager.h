#ifndef __VIDEOMANAGER_H__
#define __VIDEOMANAGER_H__


#include <assert.h>
#include <SDL.h>
#include <glm.hpp>


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

private:
	//::.. HELPER FUNCTIONS ..:://
	void Init();

private:
	static VideoManager * m_instance;

	SDL_Window * m_window;

	glm::vec2	m_scrRes;
	bool		m_isFullScreen;
};


#endif
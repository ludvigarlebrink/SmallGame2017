#ifndef __ANIMCLIP_H__
#define __ANIMCLIP_H__


#include "AnimUtil.h"
#include "Timer.h"
#include "TimeManager.h"

#include <glm.hpp>


class AnimClip
{
public:
	AnimClip();
	virtual ~AnimClip();

	//::.. MODIFY FUNCTIONS ..:://
	void Play();
	void Stop();

	void Update();

	//::.. GET FUNCTIONS ..:://
	const char * GetName() const;
	bool GetIsPlaying() const;
	KeyFrame * GetCurrentKeyFrame() const;
	KeyFrame * GetPreviousKeyFrame() const;
	uint32_t GetNumKeys();
	int32_t GetFirstKey();
	int32_t GetLastKey();
	float GetInter() const;

	//::.. SET FUNCTIONS ..:://
	void SetAnimation(KeyFrame * keyFrames, 
		int32_t firstKey, int32_t lastKey);
	void SetName(const char * name);
	void SetSpeedModifier(float speed);

private:
	TimeManager *	m_timeManager;

	const char *	m_name;

	bool			m_isPlaying;
	float			m_speedModifier;
	float			m_inter;
	int32_t			m_currKeyI;
	int32_t			m_preKeyI;

	uint32_t		m_numKeys;
	int32_t			m_firstKey;
	int32_t			m_lastKey;
	KeyFrame *		m_keys;

	Timer			m_timer;

};

#endif // !__ANIMCLIP_H__
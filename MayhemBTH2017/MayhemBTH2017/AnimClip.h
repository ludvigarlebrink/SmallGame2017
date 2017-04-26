#ifndef __ANIMCLIP_H__
#define __ANIMCLIP_H__


#include "AnimUtil.h"
#include "Timer.h"


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
	uint32_t GetNumKeys();
	int32_t GetFirstKey();
	int32_t GetLastKey();

	//::.. SET FUNCTIONS ..:://
	void SetAnimation(KeyFrame * keyFrames, 
		int32_t firstKey, int32_t lastKey);
	void SetName(const char * name);

private:
	const char *	m_name;

	bool			m_isPlaying;
	float			m_currKey;
	int32_t			m_currKeyI;

	uint32_t		m_numKeys;
	int32_t			m_firstKey;
	int32_t			m_lastKey;
	KeyFrame *		m_keys;

	Timer			m_timer;

};

#endif // !__ANIMCLIP_H__
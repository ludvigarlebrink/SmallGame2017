#ifndef __ANIMCONTROLLER_H__
#define __ANIMCONTROLLER_H__


#include "AnimClip.h"
#include "AnimSkeleton.h"

#include <glew.h>
#include <vector>


class AnimController
{
public:
	static const uint32_t MAX_CLIPS = 10;

	AnimController();
	virtual ~AnimController();

	void QuickUpdate(GLuint locations);
	void Update(GLuint locations);

	bool SwitchAnim(const char * anim);
	bool SwitchAnimAt(uint32_t index);

	void AddAnimation(AnimClip * clip);


	//::.. GET FUNCTIONS ..:://
	AnimSkeleton * GetSkeleton() const;
	uint32_t GetNumClips() const;
	uint32_t GetCurrentClip() const;
	AnimClip * GetCurrentAnimClip() const;
	std::vector<AnimClip *> GetClips() const;

	//::.. SET FUNCTIONS ..:://
	void SetSkeleton(AnimSkeleton * skel);

private:
	AnimSkeleton *			m_skel;

	uint32_t				m_numClips;
	uint32_t				m_currClip;
	std::vector<AnimClip *>	m_clips;

	KeyFrame *				m_keyUp;
	KeyFrame *				m_keyBase;
	KeyFrame *				m_keyDown;
	KeyFrame *				m_keyDown2;


};


#endif
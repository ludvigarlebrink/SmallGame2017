#ifndef __ATOMICBOMB_H__
#define __ATOMICBOMB_H__


#include "PrefabManager.h"
#include "VideoManager.h"
#include "Timer.h"
#include "Camera.h"


class AtomicBomb
{
public:
	AtomicBomb();
	virtual ~AtomicBomb();

	void StartBombSequence();
	void Update(Camera &cam);


private:
	Prefab * m_bomber;
	Prefab * m_atomicBomb;

	bool m_sequenceStarted;

};

#endif // !__ATOMICBOMB_H__
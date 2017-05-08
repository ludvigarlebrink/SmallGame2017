#ifndef __TRANSITIONMANAGER_H__
#define __TRANSITIONMANAGER_H__


class TransitionManager
{
public:
	TransitionManager();
	virtual ~TransitionManager();

	void StartUp();
	void ShutDown();

private:

};


#endif // !__TRANSITIONMANAGER_H__
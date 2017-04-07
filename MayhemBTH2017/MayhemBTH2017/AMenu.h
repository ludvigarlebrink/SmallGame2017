#ifndef __AMENU_H__
#define __AMENU_H__





class AMenu
{
public:
	AMenu();
	virtual ~AMenu();

	virtual void Init() = 0;
	virtual void Update() = 0;



};


#endif
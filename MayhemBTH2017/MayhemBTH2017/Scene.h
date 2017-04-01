#ifndef __SCENE_H__
#define __SCENE_H__

class Scene
{
public:
	Scene();
	virtual ~Scene();

	bool Load();
	bool Free();

	void Update();

private:
	

};


#endif
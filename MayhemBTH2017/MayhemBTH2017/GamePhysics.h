#pragma once
#include <Box2D\Box2D.h>
#include "Box.h"

class GamePhysics
{
public:
	GamePhysics();
	virtual ~GamePhysics();

	void enterWorld();

	void update();


private:
	std::unique_ptr<b2World> m_world;
	Box m_newBox;
	Box m_newBox2;



};


#ifndef __LEVELEDITORPROPPLACER_H__
#define __LEVELEDITORPROPPLACER_H__


#include "PropHandler.h"
#include "Camera.h"
#include "Transform.h"
#include "PropHandler.h"
#include "TimeManager.h"


#include <glm.hpp>
#include <vector>


class LevelEditorPropPlacer
{
public:
	LevelEditorPropPlacer();
	virtual ~LevelEditorPropPlacer();

	void Update(int32_t pos);
	void Render(Camera& cam);

	void Place();
	void Remove();

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();

private:
	TimeManager *						m_time;

	PropHandler							m_propHandler;
	std::vector<PropHandler::Prop *>	m_props;

	int32_t								m_currentSelected;
	glm::vec2							m_pos;
};


#endif
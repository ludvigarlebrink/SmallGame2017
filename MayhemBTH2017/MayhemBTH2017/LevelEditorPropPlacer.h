#ifndef __LEVELEDITORPROPPLACER_H__
#define __LEVELEDITORPROPPLACER_H__


#include "PropHandler.h"
#include "Camera.h"
#include "Transform.h"
#include "PropHandler.h"
#include "TimeManager.h"
#include "InputManager.h"


#include <math.h>
#include <glm.hpp>
#include <vector>

class LevelEditorPropPlacer
{
public:

	struct PropsExport
	{
		uint32_t	id;
		glm::vec2	pos;
		float		rot;
	};

	LevelEditorPropPlacer();
	virtual ~LevelEditorPropPlacer();
	
	void Start(glm::vec2 pos);

	void Update(int32_t pos);
	void Render(Camera& cam);
	void RenderProps(Camera& cam);

	void Place();
	void Remove();

	//::.. GET FUNCTIONS ..:://
	PropsExport * GetPropExport();
	uint32_t GetNumProps();


private:
	//::.. HELP FUNCTIONS ..:://
	void Init();

private:
	TimeManager *						m_time;
	InputManager *						m_input;

	bool								m_snap;

	PropHandler							m_propHandler;
	std::vector<PropHandler::Prop *>	m_props;

	int32_t								m_currentSelected;
	glm::vec2							m_pos;
};


#endif
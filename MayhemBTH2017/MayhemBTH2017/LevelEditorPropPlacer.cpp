#include "LevelEditorPropPlacer.h"



LevelEditorPropPlacer::LevelEditorPropPlacer()
{
	Init();
	m_time = TimeManager::Get();
}


LevelEditorPropPlacer::~LevelEditorPropPlacer()
{
}

void LevelEditorPropPlacer::Update(int32_t pos)
{
	m_currentSelected = pos;
	m_props[m_currentSelected]->prefab->SetPosition(glm::vec3(m_pos.x, m_pos.y, 0.0f));
	m_props[m_currentSelected]->prefab->Update();
}

void LevelEditorPropPlacer::Render(Camera & cam)
{
	m_props[m_currentSelected]->prefab->Render(cam);
}

void LevelEditorPropPlacer::Init()
{
	m_props.resize(m_propHandler.NUM_PROPS);

	for (uint32_t i = 0; i < m_propHandler.NUM_PROPS; i++)
	{
		m_props[i] = m_propHandler.Instantiate(i);
	}
}

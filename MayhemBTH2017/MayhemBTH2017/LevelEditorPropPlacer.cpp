#include "LevelEditorPropPlacer.h"



LevelEditorPropPlacer::LevelEditorPropPlacer()
{
	Init();
	m_time = TimeManager::Get();
	m_input = InputManager::Get();

	m_snap = true;
}


LevelEditorPropPlacer::~LevelEditorPropPlacer()
{
}

void LevelEditorPropPlacer::Start(glm::vec2 pos)
{
	m_pos = pos;
}

void LevelEditorPropPlacer::Update(int32_t pos)
{
	m_currentSelected = pos;

	m_pos.x -= m_input->GetAxis(CONTROLLER_AXIS_LEFT_X) * m_time->GetDeltaTime() * 20;
	m_pos.y -= m_input->GetAxis(CONTROLLER_AXIS_LEFT_Y) * m_time->GetDeltaTime() * 20;

	if (m_snap)
	{
		m_props[m_currentSelected]->prefab->SetPosition(glm::vec3(std::round(m_pos.x), 
			std::round(m_pos.y) + 0.5f, 0.0f));
	}
	else
	{
		m_props[m_currentSelected]->prefab->SetPosition(glm::vec3(m_pos.x, m_pos.y, 0.0f));
	}

	m_props[m_currentSelected]->prefab->Update();

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_A))
	{
		m_props.push_back(m_propHandler.Instantiate(m_props[m_currentSelected]->id));

		if (m_snap)
		{
			m_props[m_props.size() - 1]->prefab->SetPosition(glm::vec3(std::round(m_pos.x), 
				std::round(m_pos.y) + 0.5f, 0.0f));
		}
		else
		{
			m_props[m_props.size() - 1]->prefab->SetPosition(glm::vec3(m_pos.x, m_pos.y, 0.0f));
		}
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_B))
	{
		m_snap = !m_snap;
	}

}

void LevelEditorPropPlacer::Render(Camera & cam)
{
	m_props[m_currentSelected]->prefab->Render(cam);
}

void LevelEditorPropPlacer::RenderProps(Camera & cam)
{
	for (uint32_t i = m_propHandler.NUM_PROPS; i < m_props.size(); i++)
	{
		m_props[i]->prefab->Render(cam);
	}
}

void LevelEditorPropPlacer::Place()
{
	// TODO
}

void LevelEditorPropPlacer::Remove()
{
	// TODO
}

LevelEditorPropPlacer::PropsExport * LevelEditorPropPlacer::GetPropExport()
{
	uint32_t size = m_props.size() - m_propHandler.NUM_PROPS;
	int x = m_props.size();
	PropsExport * props = new PropsExport[size];

	uint32_t counter = 0;

	for (uint32_t i = m_propHandler.NUM_PROPS; i < m_props.size(); i++)
	{
		props[counter].id = m_props[i]->id;
		props[counter].pos.x = m_props[i]->prefab->GetPosition().x;
		props[counter].pos.y = m_props[i]->prefab->GetPosition().y;

		++counter;
	}

	return props;
}


uint32_t LevelEditorPropPlacer::GetNumProps()
{
	uint32_t toReturn = m_props.size() - m_propHandler.NUM_PROPS;
	return toReturn;
}


void LevelEditorPropPlacer::Init()
{
//	m_props.resize(m_propHandler.NUM_PROPS);

	for (uint32_t i = 0; i < m_propHandler.NUM_PROPS; i++)
	{
		m_props.push_back(m_propHandler.Instantiate(i));
	}
}

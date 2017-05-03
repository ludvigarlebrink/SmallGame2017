#include "PropHandler.h"



PropHandler::PropHandler()
{
	Init();
}


PropHandler::~PropHandler()
{
}


PropHandler::Prop * PropHandler::Instantiate(const char * name)
{
	for (uint32_t i = 0; i < NUM_PROPS; i++)
	{
		if (strcmp(m_props[i]->name, name))
		{
			Prefab * pre;

			if (m_props[i]->hasAnimation)
			{
				const char * def = "Default";
				pre = PrefabManager::Instantiate(m_props[i]->name,
					m_props[i]->name, &def, 1);
			}
			else
			{
				pre = PrefabManager::Instantiate(m_props[i]->name,
					nullptr, nullptr, 0);
			}

			Prop * prop = new Prop;
			prop->id = i;
			prop->prefab = pre;

			return prop;
		}
	}

	return nullptr;
}


PropHandler::Prop * PropHandler::Instantiate(uint32_t id)
{
	Prefab * pre;

	if (m_props[id]->hasAnimation)
	{
		const char * def = "Default";
		pre = PrefabManager::Instantiate(m_props[id]->name,
			m_props[id]->name, &def, 1);
	}
	else
	{
		pre = PrefabManager::Instantiate(m_props[id]->name,
			nullptr, nullptr, 0);
	}

	Prop * prop = new Prop;
	prop->id = id;
	prop->prefab = pre;

	return prop;
}

PropHandler::PropInfo * PropHandler::GetPropInfo(uint32_t id)
{
	return m_props[id];
}


//::.. HELP FUNCTIONS ..:://
void PropHandler::Init()
{
	for (uint32_t i = 0; i < NUM_PROPS; i++)
	{
		m_props[i] = new PropInfo;
	}

	// 0. Candle
	m_props[0]->name = "Candle";
	m_props[0]->hasAnimation = false;
	m_props[0]->gridX = 2;
	m_props[0]->gridY = 4;

	// temp	  
	m_props[1]->name = "Candle";
	m_props[1]->hasAnimation = false;
	m_props[1]->gridX = 2;
	m_props[1]->gridY = 4;

	// temp	  ->
	m_props[2]->name = "Candle";
	m_props[2]->hasAnimation = false;
	m_props[2]->gridX = 2;
	m_props[2]->gridY = 4;
			  
	// temp
	m_props[3]->name = "Candle";
	m_props[3]->hasAnimation = false;
	m_props[3]->gridX = 2;
	m_props[3]->gridY = 4;
			  
	// temp
	m_props[4]->name = "Candle";
	m_props[4]->hasAnimation = false;
	m_props[4]->gridX = 2;
	m_props[4]->gridY = 4;
			  
	// temp
	m_props[5]->name = "Candle";
	m_props[5]->hasAnimation = false;
	m_props[5]->gridX = 2;
	m_props[5]->gridY = 4;
			  
	// temp
	m_props[6]->name = "Candle";
	m_props[6]->hasAnimation = false;
	m_props[6]->gridX = 2;
	m_props[6]->gridY = 4;
			  
	// temp
	m_props[7]->name = "Candle";
	m_props[7]->hasAnimation = false;
	m_props[7]->gridX = 2;
	m_props[7]->gridY = 4;
			  
	// temp
	m_props[8]->name = "Candle";
	m_props[8]->hasAnimation = false;
	m_props[8]->gridX = 2;
	m_props[8]->gridY = 4;
			  
	// temp
	m_props[9]->name = "Candle";
	m_props[9]->hasAnimation = false;
	m_props[9]->gridX = 2;
	m_props[9]->gridY = 4;

	// temp
	m_props[10]->name = "Candle";
	m_props[10]->hasAnimation = false;
	m_props[10]->gridX = 2;
	m_props[10]->gridY = 4;

	// temp
	m_props[11]->name = "Candle";
	m_props[11]->hasAnimation = false;
	m_props[11]->gridX = 2;
	m_props[11]->gridY = 4;
			   
	// temp	   
	m_props[12]->name = "Candle";
	m_props[12]->hasAnimation = false;
	m_props[12]->gridX = 2;
	m_props[12]->gridY = 4;
			   
	// temp	   
	m_props[13]->name = "Candle";
	m_props[13]->hasAnimation = false;
	m_props[13]->gridX = 2;
	m_props[13]->gridY = 4;
			   
	// temp	   
	m_props[14]->name = "Candle";
	m_props[14]->hasAnimation = false;
	m_props[14]->gridX = 2;
	m_props[14]->gridY = 4;
			   
	// temp	   
	m_props[15]->name = "Candle";
	m_props[15]->hasAnimation = false;
	m_props[15]->gridX = 2;
	m_props[15]->gridY = 4;
}
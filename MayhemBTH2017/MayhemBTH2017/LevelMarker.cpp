#include "LevelMarker.h"



LevelMarker::LevelMarker()
	: m_currentPosX(20), m_currentPosY(20)
{

	m_input = InputManager::Get();
	m_mode = NORMAL;


	m_levelShader.Init(".\\Assets\\GLSL\\LevelMarkerShader", false, false);
	m_megaTexture = m_textureTemp.Import(".\\Assets\\Textures\\textureMap.png");

	Vertex3D verts[6];


	verts[0].position = glm::vec3(-0.5f, -0.5f, 0.0f);
	verts[0].normal = glm::vec3(1.0f, 1.0f, 0.0f);
	verts[0].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 0.0f);

	verts[1].position = glm::vec3(-0.5f, 0.5f, 0.0f);
	verts[1].normal = glm::vec3(1.0f, 1.0f, 0.0f);
	verts[1].texCoordsAlpha = glm::vec3(0.0f, 0.0f, 0.0f);

	verts[2].position = glm::vec3(0.5f, -0.5f, 0.0f);
	verts[2].normal = glm::vec3(1.0f, 1.0f, 0.0f);
	verts[2].texCoordsAlpha = glm::vec3(1.0f, 1.0f, 0.0f);

	verts[3].position = glm::vec3(0.5f, -0.5f, 0.0f);
	verts[3].normal = glm::vec3(1.0f, 1.0f, 0.0f);
	verts[3].texCoordsAlpha = glm::vec3(1.0f, 1.0f, 0.0f);

	verts[4].position = glm::vec3(-0.5f, 0.5f, 0.0f);
	verts[4].normal = glm::vec3(1.0f, 1.0f, 0.0f);
	verts[4].texCoordsAlpha = glm::vec3(0.0f, 0.0f, 0.0f);

	verts[5].position = glm::vec3(0.5f, 0.5f, 0.0f);
	verts[5].normal = glm::vec3(0.5f, 0.5f, 0.0f);
	verts[5].texCoordsAlpha = glm::vec3(1.0f, 0.0f, 0.0f);

	m_transform.SetPosition(0.0f, 0.0f, 0.0f);
	m_mesh.Load(verts, 6);

}


LevelMarker::~LevelMarker()
{
	delete m_megaTexture;
}

void LevelMarker::MoveUp(float speed)
{

}

void LevelMarker::MoveRight(float speed)
{

}

//::.. SET FUNCTIONS ..:://
void LevelMarker::SetMarkerMode(uint32_t markerMode)
{
	m_mode = markerMode;
}

void LevelMarker::SetCurrentPosX(uint32_t pos)
{
	m_currentPosX = pos;
}

void LevelMarker::SetCurrentPosY(uint32_t pos)
{
	m_currentPosY = pos;
}

void LevelMarker::SetSavedPosX(uint32_t pos)
{
	m_savedPosX = pos;
}

void LevelMarker::SetSavedPosY(uint32_t pos)
{
	m_savedPosY = pos;
}

void LevelMarker::SetStartX(uint32_t value)
{
	startX = value;
}

void LevelMarker::SetStartY(uint32_t value)
{
	startY = value;
}

void LevelMarker::SetEndX(uint32_t value)
{
	endX = value;
}

void LevelMarker::SetEndY(uint32_t value)
{
	endY = value;
}

void LevelMarker::SetSizeX(uint32_t value)
{
	sizeX = value;
}

void LevelMarker::SetSizeY(uint32_t value)
{
	sizeY = value;
}

//::.. GET FUNCTIONS ..:://
uint32_t LevelMarker::GetMarkerMode()
{
	return m_mode;
}

uint32_t LevelMarker::GetCurrentPosX()
{
	return m_currentPosX;
}

uint32_t LevelMarker::GetCurrentPosY()
{
	return m_currentPosY;
}

uint32_t LevelMarker::GetSavedPosX()
{
	return m_savedPosX;
}

uint32_t LevelMarker::GetSavedPosY()
{
	return m_savedPosY;
}

uint32_t LevelMarker::GetStartX()
{
	return startX;
}

uint32_t LevelMarker::GetStartY()
{
	return startY;
}

uint32_t LevelMarker::GetEndX()
{
	return endX;
}

uint32_t LevelMarker::GetEndY()
{
	return endY;
}

uint32_t LevelMarker::GetSizeX()
{
	return sizeX;
}

uint32_t LevelMarker::GetSizeY()
{
	return sizeY;
}
//
//void LevelMarker::Update(Camera & camera)
//{
//	
//	Render(camera);
//}

//::.. UPDATE FUNCTIONS ..:://
void LevelMarker::Render(Camera & camera, glm::vec2 m_uv)
{
	ClampPos();
	//temp stuff-------------------------------
	m_megaTexture->Bind(0);

	glm::vec4 markerLoc;

	// FIX TEXTURE
	std::cout << m_uv.x << std::endl;
	std::cout << m_uv.y << std::endl;
	std::cout << "- - - - - - -" << std::endl;
	markerLoc.x = (32 * m_uv.x) / 512.0;
	markerLoc.y = (32 * m_uv.y) / 512.0;
	markerLoc.z = 32 / 512.0;
	markerLoc.w = 32 / 512.0;

	m_levelShader.SendTexture(0, "t", markerLoc);
	m_levelShader.Bind();



	
	//temp stuff-------------------------------END

	if (m_mode == ADD_SPAWN_POINT)
	{

		startX = m_currentPosX;
		startY = m_currentPosY;
		endX = m_currentPosX + 3;
		endY = m_currentPosY + 3;

		sizeX = endX - startX + 1;
		sizeY = endY - startY + 1;

		float offsetX;
		float offsetY;

		if (sizeX % 2 == 0)
		{
			offsetX = (startX + (sizeX / 2)) - 0.5f;
		}
		else
		{
			offsetX = (startX + (sizeX / 2));
		}

		if (sizeY % 2 == 0)
		{
			offsetY = (startY + (sizeY / 2)) - 0.5f;
		}
		else
		{
			offsetY = (startY + (sizeY / 2));
		}


		m_transform.SetScale(sizeX, sizeY, 1.0f);
		m_transform.SetPosition(offsetX, offsetY, -2.001f);
		m_levelShader.Update(m_transform, camera);
		m_levelShader.TempUpdateAlpha(1.0f);
		m_mesh.Render();
	}


	if (m_mode == ADD_BLOCK || m_mode == REMOVE_BLOCK)
	{

		if (m_currentPosX > m_savedPosX)
		{
			startX = m_savedPosX;
			endX = m_currentPosX;
		}
		else
		{
			startX = m_currentPosX;
			endX = m_savedPosX;
		}

		if (m_currentPosY > m_savedPosY)
		{
			startY = m_savedPosY;
			endY = m_currentPosY;
		}
		else
		{
			startY = m_currentPosY;
			endY = m_savedPosY;
		}


		sizeX = endX - startX + 1;
		sizeY = endY - startY + 1;

		float offsetX;
		float offsetY;

		if (sizeX % 2 == 0)
		{
			offsetX = (startX + (sizeX / 2)) - 0.5f;
		}
		else
		{
			offsetX = (startX + (sizeX / 2));
		}

		if (sizeY % 2 == 0)
		{
			offsetY = (startY + (sizeY / 2)) - 0.5f;
		}
		else
		{
			offsetY = (startY + (sizeY / 2));
		}


		m_transform.SetScale(sizeX, sizeY, 1.0f);
		m_transform.SetPosition(offsetX, offsetY, -2.001f);
		m_levelShader.Update(m_transform, camera);
		m_levelShader.TempUpdateAlpha(1.0f);
		m_mesh.Render();
	}
	else
	{
		m_transform.SetScale(1.0f, 1.0f, 1.0f);
		m_transform.SetPosition(m_currentPosX, m_currentPosY, -2.001f);
		m_levelShader.Update(m_transform, camera);
		m_levelShader.TempUpdateAlpha(1.0f);
		m_mesh.Render();
	}
}


void LevelMarker::ClampPos()
{
	if (m_mode == NORMAL || ADD_BLOCK || REMOVE_BLOCK)
	{
		if (m_currentPosX >= SIZE_X)
		{
			m_currentPosX = SIZE_X - 1;
		}
		else if (m_currentPosX <= 1)
		{
			m_currentPosX = 1;
		}

		if (m_currentPosY >= SIZE_Y)
		{
			m_currentPosY = SIZE_Y - 1;
		}
		else if (m_currentPosY <= 1)
		{
			m_currentPosY = 1;
		}
	}
	else if (m_mode == ADD_SPAWN_POINT)
	{
		if (m_currentPosX >= SIZE_X - 4)
		{
			m_currentPosX = SIZE_X - 4;
		}
		else if (m_currentPosX <= 1)
		{
			m_currentPosX = 1;
		}

		if (m_currentPosY >= SIZE_Y - 4)
		{
			m_currentPosY = SIZE_Y - 4;
		}
		else if (m_currentPosY <= 1)
		{
			m_currentPosY = 1;
		}
	}

}
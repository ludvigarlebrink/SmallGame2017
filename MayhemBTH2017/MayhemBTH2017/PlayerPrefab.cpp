#include "PlayerPrefab.h"
#include <iostream>

//::.. CONSTRUCTORS ..:://
PlayerPrefab::PlayerPrefab(int32_t id)
{
	Init(id, nullptr);
	m_weapRotY = 90;
	m_defaultRot = 90;
	m_player->SetRotation(glm::vec3(0.0f, 90.0f, 0.0f));
}


PlayerPrefab::PlayerPrefab(int32_t id, Prefab * weapon)
{
	Init(id, weapon);
}


PlayerPrefab::~PlayerPrefab()
{
	Free();
}


void PlayerPrefab::Update(float x, float y, float speed)
{
	m_x = x;
	m_y = y;

	AnimController * anim = m_player->GetAnimController();
	AnimSkeleton * skel = anim->GetSkeleton();
	anim->GetCurrentAnimClip()->SetSpeedModifier(speed * 4);

	if (x > 0.300000f)
	{
		m_player->SetRotation(glm::vec3(0.0f, 90.0f, 0.0f));
		if (m_weapon != nullptr)
		{
			m_weapRotY = 90;
			m_defaultRot = 90;

		}
	}
	
	else if( x < -0.300000f)
	{
		m_player->SetRotation(glm::vec3(0.0f, -90.0f, 0.0f));
		if (m_weapon != nullptr)
		{
			m_weapRotY = -90;
			m_defaultRot = -90;
		}
	}
	else
	{
		m_player->SetRotation(glm::vec3(0.0f, m_defaultRot, 0.0f));
		if (m_weapon != nullptr)
		{
			m_weapRotY = m_defaultRot;
		}
	}

	if (y < 0.0f)
	{
		for (uint32_t i = 0; i < skel->GetNumJoints(); i++)
		{
			glm::quat rot1(glm::quat_cast(m_keyBase->localTx[i]));
			glm::quat rot2(glm::quat_cast(m_keyUp->localTx[i]));
			glm::quat rot3 = glm::lerp(rot1, rot2, abs(y));
			m_kf->localTx[i] = glm::mat4(rot3);
			m_kf->localTx[i][3] = m_keyBase->localTx[i][3];
		}
	}
	else
	{
		if (abs(y) < 0.5f)
		{
			for (uint32_t i = 0; i < skel->GetNumJoints(); i++)
			{
				glm::quat rot1(glm::quat_cast(m_keyBase->localTx[i]));
				glm::quat rot2(glm::quat_cast(m_keyDown1->localTx[i]));
				glm::quat rot3 = glm::lerp(rot1, rot2, abs(y * 2));
				m_kf->localTx[i] = glm::mat4(rot3);
				m_kf->localTx[i][3] = m_keyBase->localTx[i][3];
			}
		}
		else
		{
			for (uint32_t i = 0; i < skel->GetNumJoints(); i++)
			{
				glm::quat rot1(glm::quat_cast(m_keyDown1->localTx[i]));
				glm::quat rot2(glm::quat_cast(m_keyDown2->localTx[i]));
				glm::quat rot3 = glm::lerp(rot1, rot2, abs((y - 0.5f) * 2));
				m_kf->localTx[i] = glm::mat4(rot3);
				m_kf->localTx[i][3] = m_keyBase->localTx[i][3];
			}
		}
	}

	skel->Update(m_kf, nullptr, 0, true, 1, 11);
	anim->GetCurrentAnimClip()->Update();
	skel->Update(anim->GetCurrentAnimClip()->GetCurrentKeyFrame(), 
		anim->GetCurrentAnimClip()->GetPreviousKeyFrame(), anim->GetCurrentAnimClip()->GetInter(), false, 12);

	Joint * hand = skel->GetJointAt(6);

	if (m_weapon != nullptr)
	{
		m_weapon->SetPosition(glm::vec3(m_player->GetTransform().GetModelMatrix() * hand->globalTx[3]));
		m_weapon->SetRotation(glm::vec3(y * -90, m_weapRotY, 0.0f));



			//m_transform.SetPosition(m_player->GetTransform().GetModelMatrix() * hand->globalTx * glm::vec4(m_spawnPointOffset.x, m_spawnPointOffset.y, m_spawnPointOffset.z, 1.0f));

		m_transform.SetPosition(m_player->GetTransform().GetModelMatrix() * hand->globalTx * glm::vec4(m_spawnPointOffset, 1.0f));	


		m_matrix = m_transform.GetModelMatrix();
		m_projectileSpawnPoint = glm::vec3(m_matrix[3].x, m_matrix[3].y, 0.0f);
	}
}


void PlayerPrefab::Render(Camera & cam)
{
	//Renders the prefab meshes
	m_player->Render(cam);
	if (m_weapon != nullptr)
	{
		m_weapon->Render(cam);
	}
}


Prefab * PlayerPrefab::GetPlayerPrefab()
{
	return m_player;
}


glm::vec3 PlayerPrefab::GetProjectileSpawnPoint()
{
	return m_projectileSpawnPoint;
}


//::.. SET FUNCTIONS ..:://
void PlayerPrefab::SetWeapon(Prefab * weapon, glm::vec3 spawnPoint)
{
	m_weapon = weapon;
	m_spawnPointOffset = spawnPoint;
}

void PlayerPrefab::SetAnimState(uint32_t playerAnimState)
{
}


//::.. HELP FUNCTIONS ..:://
void PlayerPrefab::Init(int32_t id, Prefab * weapon)
{
	std::string mat = "Player";
	mat.append(std::to_string(id + 1));

	std::string * sanim = new std::string;
	sanim[0] = "Run";
	m_player = PrefabManager::Instantiate("Player", "Player", sanim, 1, mat.c_str());
	m_player->SetScale(glm::vec3(1.3f));

	AnimController * anim = m_player->GetAnimController();
	AnimSkeleton * skel = anim->GetSkeleton();

	m_kf = new KeyFrame;
	m_kf->localTx = new glm::mat4[anim->GetSkeleton()->GetNumJoints()];

	MrAnimHandler * animHandler = new MrAnimHandler;

	animHandler->Import(".\\Assets\\Animations\\Player@Up.mranim");

	m_keyUp = new KeyFrame[animHandler->GetNumKeyFramedJoints()];
	m_keyUp->localTx = new glm::mat4[skel->GetNumJoints()];

	for (uint32_t j = 0; j < skel->GetNumJoints(); j++)
	{
		m_keyUp->localTx[j] = animHandler->GetKeyFramedJoints()[j].matrix[0];
	}

	animHandler->Import(".\\Assets\\Animations\\Player@Run.mranim");

	m_keyBase = new KeyFrame[animHandler->GetNumKeyFramedJoints()];
	m_keyBase->localTx = new glm::mat4[skel->GetNumJoints()];

	for (uint32_t j = 0; j < skel->GetNumJoints(); j++)
	{
		m_keyBase->localTx[j] = animHandler->GetKeyFramedJoints()[j].matrix[0];
	}

	animHandler->Import(".\\Assets\\Animations\\Player@Down_01.mranim");

	m_keyDown1 = new KeyFrame[animHandler->GetNumKeyFramedJoints()];
	m_keyDown1->localTx = new glm::mat4[skel->GetNumJoints()];

	for (uint32_t j = 0; j < skel->GetNumJoints(); j++)
	{
		m_keyDown1->localTx[j] = animHandler->GetKeyFramedJoints()[j].matrix[0];
	}

	animHandler->Import(".\\Assets\\Animations\\Player@Down_02.mranim");

	m_keyDown2 = new KeyFrame[animHandler->GetNumKeyFramedJoints()];
	m_keyDown2->localTx = new glm::mat4[skel->GetNumJoints()];

	for (uint32_t j = 0; j < skel->GetNumJoints(); j++)
	{
		m_keyDown2->localTx[j] = animHandler->GetKeyFramedJoints()[j].matrix[0];
	}

	delete animHandler;
}


void PlayerPrefab::Free()
{
	if (m_kf != nullptr)
	{
		delete[] m_kf->localTx;
		delete m_kf;
		m_kf = nullptr;
	}

	if (m_keyUp != nullptr)
	{
		delete[] m_keyUp->localTx;
		delete m_keyUp;
		m_keyUp = nullptr;
	}

	if (m_keyBase != nullptr)
	{
		delete[] m_keyBase->localTx;
		delete m_keyBase;
		m_keyBase = nullptr;
	}

	if (m_keyDown1 != nullptr)
	{
		delete[] m_keyDown1->localTx;
		delete m_keyDown1;
		m_keyDown1 = nullptr;
	}

	if (m_keyDown2 != nullptr)
	{
		delete[] m_keyDown2->localTx;
		delete m_keyDown2;
		m_keyDown2 = nullptr;
	}

	// Delete the player last.
	if (m_player != nullptr)
	{
	
		delete m_player;
		m_player = nullptr;
	}
}
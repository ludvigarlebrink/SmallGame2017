#include "PlayerPrefab.h"


//::.. CONSTRUCTORS ..:://
PlayerPrefab::PlayerPrefab()
{
	Init(nullptr);
	m_weapRotY = 90;
	m_player->SetRotation(glm::vec3(0.0f, 90.0f, 0.0f));
}


PlayerPrefab::PlayerPrefab(Prefab * weapon)
{
	Init(weapon);
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

	if (x > 0.3f)
	{
		m_player->SetRotation(glm::vec3(0.0f, 90.0f, 0.0f));
		m_weapRotY = 90;
	}
	
	if( x < -0.3f)
	{
		m_player->SetRotation(glm::vec3(0.0f, -90.0f, 0.0f));
		m_weapRotY = -90;
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
	m_weapon->SetPosition(glm::vec3(m_player->GetTransform().GetModelMatrix() * hand->globalTx[3]));
	m_weapon->SetRotation(glm::vec3(y * -90, m_weapRotY, 0.0f));

	m_projectileSpawnPoint = glm::vec3(m_player->GetTransform().GetModelMatrix() * hand->globalTx[3]);

	
}


void PlayerPrefab::Render(Camera & cam)
{
	//Renders the prefab meshes
	m_player->Render(cam);
	m_weapon->Render(cam);
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
void PlayerPrefab::SetWeapon(Prefab * weapon)
{
	m_weapon = weapon;
}

void PlayerPrefab::SetAnimState(uint32_t playerAnimState)
{
}


//::.. HELP FUNCTIONS ..:://
void PlayerPrefab::Init(Prefab * weapon)
{
	m_weapon = PrefabManager::Instantiate("Rifle", nullptr, nullptr, 0);
	m_weapon->SetScale(glm::vec3(1.3f));

	m_player = PrefabManager::Instantiate("");
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
	delete m_player;
	delete m_weapon;
}
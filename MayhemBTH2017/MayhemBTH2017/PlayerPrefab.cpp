#include "PlayerPrefab.h"



//::.. CONSTRUCTORS ..:://
PlayerPrefab::PlayerPrefab()
{
	Init(nullptr);
}


PlayerPrefab::PlayerPrefab(Prefab * weapon)
{
	Init(weapon);
}


PlayerPrefab::~PlayerPrefab()
{
	Free();
}


void PlayerPrefab::Update(float x, float y)
{
	m_x = x;
	m_y = y;


	AnimController * anim = m_player->GetAnimController();
	AnimSkeleton * skel = anim->GetSkeleton();


	if (y < 0)
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



	skel->Update(m_kf, true, 1, 11);

	anim->GetCurrentAnimClip()->Update();

	skel->Update(anim->GetCurrentAnimClip()->GetCurrentKeyFrame(), false, 12);

}


void PlayerPrefab::Render(Camera & cam)
{
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


//::.. SET FUNCTIONS ..:://
void PlayerPrefab::SetWeapon(Prefab * weapon)
{
	m_weapon = weapon;
}


//::.. HELP FUNCTIONS ..:://
void PlayerPrefab::Init(Prefab * weapon)
{
	m_weapon = weapon;

	m_player = PrefabManager::Instantiate("");

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
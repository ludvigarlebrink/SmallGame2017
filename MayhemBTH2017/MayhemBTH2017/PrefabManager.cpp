#include "PrefabManager.h"

#include <iostream>
#include <iomanip>

uint32_t PrefabManager::numPrefabs = 0;
Prefab * PrefabManager::prefabs = nullptr;


PrefabManager::PrefabManager()
{
	// Do nothing...
	// TEMP
	prefabs = new Prefab[POOL_SIZE];
}


PrefabManager::~PrefabManager()
{
	// Do nothing...
}

Prefab * PrefabManager::Instantiate(const char * name)
{
	// Check cache first
	// Temp file path

	// Fix this search
	for (uint32_t i = 0; i < numPrefabs; i++)
	{

	}

	const char* filepath = ".\\Assets\\Prefabs\\super.mr";

	//	m_handler->Import(filepath);
//	MrHandler * mrHandler = new MrHandler;

	MrMeshHandler * meshHandler = new MrMeshHandler;


	meshHandler->Import(".\\Assets\\Meshes\\super.mrmesh");
	std::cout << "Mesh Imported" << std::endl;


	MrSkelHandler * skelHandler = new MrSkelHandler;

	if (skelHandler->Import(".\\Assets\\Skeletons\\super.mrskel"))
	{
		std::cout << "Skel Imported" << std::endl;
	}
	else
	{
		std::cout << "Skel FAIL" << std::endl;
	}

	MrAnimHandler * animHandler = new MrAnimHandler;

	if(animHandler->Import(".\\Assets\\Animations\\super@animation.mranim"))
	{
		std::cout << "Anim Imported" << std::endl;
	}
	else
	{
		std::cout << "Anim FAIL" << std::endl;
	}


	// DEBUG SKEL
	for (size_t i = 0; i < skelHandler->GetNumJoints(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int n = 0; n < 4; n++)
			{

				std::cout << std::fixed << std::setprecision(2) << skelHandler->GetMatrix()[i][j][n] << "\t";
			}

			std::cout << std::endl;
		}

		std::cout << std::endl;

		std::cout << "ID:\t" << skelHandler->GetIDs()[i] << std::endl;
		std::cout << "PAR ID:\t" << skelHandler->GetParentIDs()[i] << std::endl;

		std::cout << std::endl;
		std::cout << std::endl;
	}

	// Create the prefab.

	// Create the mesh.
	Mesh * mesh = new Mesh;
	uint64_t numVerts = meshHandler->GetNumVerts();
	Vertex3DSkelAnimation * vert = new Vertex3DSkelAnimation[numVerts];

	for (uint32_t i = 0; i < numVerts; i++)
	{
		vert[i].position = meshHandler->GetPositions()[i];
		vert[i].normal = meshHandler->GetNormals()[i];
		vert[i].texCoordsAlpha = glm::vec3(meshHandler->GetTexCoords()[i], 1);

		// FIX WRONG ORDER
		vert[i].jointIDs = meshHandler->GetJointIDs()[i];
		vert[i].weights = meshHandler->GetSkinWeights()[i];
	}

	mesh->Load(vert, numVerts);



	AnimController * animContrl = new AnimController;
	
	// Set skeleton.
	AnimSkeleton * animSkel = new AnimSkeleton;

	glm::mat4 * localTx = new glm::mat4[skelHandler->GetNumJoints()];

	for (uint32_t i = 0; i < skelHandler->GetNumJoints(); i++)
	{
		localTx[i] = skelHandler->GetMatrix()[i];
	}

	animSkel->SetSkeleton(skelHandler->GetParentIDs(), localTx, skelHandler->GetNumJoints());
	animContrl->SetSkeleton(animSkel);

	// Set animations.
	AnimClip * animClip = new AnimClip;
	KeyFrame * key = new KeyFrame[animHandler->GetNumKeyFrames()];

	for (uint32_t i = 0; i < animHandler->GetNumKeyFrames(); i++)
	{
		key[i].localTx = new glm::mat4[skelHandler->GetNumJoints()];

		for (uint32_t j = 0; j < skelHandler->GetNumJoints(); j++)
		{
			key[i].localTx[j] = animHandler->GetKeyFrames()[i].matrix[j];
		}
	}

	animClip->SetName("SUPER");
	animClip->SetAnimation(key, 1, 59);

	animContrl->AddAnimation(animClip);


	Prefab * prefab = new Prefab;

	prefab->SetMesh(mesh);
	prefab->SetAnimController(animContrl);
	
	prefab->SetName("HEJ");

	prefab->Create();

	std::cout << "DONE!" << std::endl;


	return prefab;
}

bool PrefabManager::Destroy(Prefab * prefab)
{
	return false;
}


//::.. HELP FUNCTIONS ..:://
void PrefabManager::Load()
{
}
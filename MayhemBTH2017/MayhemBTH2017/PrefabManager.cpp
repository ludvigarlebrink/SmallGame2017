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

	skelHandler->Import(".\\Assets\\Skeletons\\super.mrskel");

	MrAnimHandler * animHandler = new MrAnimHandler;

	animHandler->Import(".\\Assets\\Animations\\Player@Run.mranim");



	// Create the prefab.

	// Create the mesh.
	Mesh * mesh = new Mesh;
	uint64_t numVerts = meshHandler->GetNumVerts();
	Vertex3DSkelAnimation * vert = new Vertex3DSkelAnimation[numVerts];

	for (uint32_t i = 0; i < numVerts; i++)
	{
		vert[i].position = meshHandler->GetPositions()[i];
		vert[i].normal = meshHandler->GetNormals()[i];
		vert[i].texCoordsAlpha = glm::vec3(meshHandler->GetTexCoords()[i].x, meshHandler->GetTexCoords()[i].y, 1);

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
	KeyFrame * key = new KeyFrame[animHandler->GetNumKeyFramedJoints()];

	for (uint32_t i = 0; i < animHandler->GetNumKeyFramedJoints(); i++)
	{
		key[i].localTx = new glm::mat4[skelHandler->GetNumJoints()];

		for (uint32_t j = 0; j < skelHandler->GetNumJoints(); j++)
		{
			key[i].localTx[j] = animHandler->GetKeyFramedJoints()[j].matrix[i];
		}
	}

	animClip->SetName("SUPER");
	animClip->SetAnimation(key, 1, 59);

	animContrl->AddAnimation(animClip);


	// MATERIAL
	MrMatHandler * test = new MrMatHandler;

	delete meshHandler;
	delete skelHandler;
	delete animHandler;

	//SPECAL 1
	MrAnimHandler animHandler1;
//	if (animHandler1.Import(".\\Assets\\Animations\\super@base.mranim"))
	{
//		std::cout << "YEYE Imported" << std::endl;
//		//animHandler->Import(".\\Assets\\Animations\\super@up.mranim");
//		//KeyFrame * keyUp = new KeyFrame;
//		//uint32_t hej = skelHandler->GetNumJoints();
//		//keyUp[0].localTx = new glm::mat4[skelHandler->GetNumJoints()];
	}
//	else
//	{
//		std::cout << "Anim FAIL" << std::endl;
//	}


	//	for (uint32_t i = 0; i < 1; i++)
	//	{
	//		keyUp[0].localTx[i] = animHandler1->GetKeyFramedJoints()[0].matrix[i];
	//	}


	Prefab * prefab = new Prefab;

	prefab->SetMesh(mesh);
	prefab->SetAnimController(animContrl);

	prefab->SetName("HEJ");
	prefab->SetAlbedoID(TextureManager::AddTexture(nullptr));
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
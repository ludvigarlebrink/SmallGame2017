#include "PrefabManager.h"

#include <iostream>
#include <string>
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
	const char* filepath = name;

	//	m_handler->Import(filepath);
	//	MrHandler * mrHandler = new MrHandler;

	MrMeshHandler * meshHandler = new MrMeshHandler;


	meshHandler->Import(".\\Assets\\Meshes\\super.mrmesh");
	std::cout << "Mesh Imported" << std::endl;


	MrSkelHandler * skelHandler = new MrSkelHandler;

	skelHandler->Import(".\\Assets\\Skeletons\\super.mrskel");

	MrAnimHandler * animHandler = new MrAnimHandler;

	animHandler->Import(".\\Assets\\Animations\\Player@Run.mranim");


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
	KeyFrame * key = new KeyFrame[30];

	for (uint32_t i = 0; i < 30; i++)
	{
		key[i].localTx = new glm::mat4[animHandler->GetNumKeyFramedJoints()];

		for (uint32_t j = 0; j <  animHandler->GetNumKeyFramedJoints(); j++)
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


	Prefab * prefab = new Prefab;

	prefab->SetMesh(mesh);
	prefab->SetAnimController(animContrl);

	prefab->SetName("HEJ");
	prefab->SetAlbedoID(TextureManager::AddTexture(nullptr));
	prefab->Create();

	std::cout << "DONE!" << std::endl;

	return prefab;
}

Prefab * PrefabManager::Instantiate(const char * mesh, const char * skel, const char ** anim, uint32_t numAnim)
{
	Prefab * prefab = new Prefab;

	if (mesh != nullptr)
	{
		MrMeshHandler * meshHandler = new MrMeshHandler;

		std::string filepath(".\\Assets\\Meshes\\");
		filepath.append(mesh);
		filepath.append(".mrmesh");

		meshHandler->Import(filepath.c_str());

		Mesh * mesh = new Mesh;
		uint32_t numVerts = meshHandler->GetNumVerts();
		Vertex3DSkelAnimation * vert = new Vertex3DSkelAnimation[numVerts];

		for (uint32_t i = 0; i < numVerts; i++)
		{
			vert[i].position = meshHandler->GetPositions()[i];
			vert[i].normal = meshHandler->GetNormals()[i];
			vert[i].texCoordsAlpha = glm::vec3(meshHandler->GetTexCoords()[i].x, meshHandler->GetTexCoords()[i].y, 1);

			if (meshHandler->GetHasSkinWeights())
			{
				vert[i].jointIDs = meshHandler->GetJointIDs()[i];
				vert[i].weights = meshHandler->GetSkinWeights()[i];
			}
		}

		delete meshHandler;

		prefab->SetMesh(mesh);
	}

	if (skel != nullptr)
	{
		// Skeleton
		MrSkelHandler * skelHandler = new MrSkelHandler;

		AnimSkeleton * animSkel = new AnimSkeleton;
		AnimController * animCtrl = new AnimController;

		skelHandler->Import(".\\Assets\\Skeletons\\super.mrskel");

		std::string filepath(".\\Assets\\Skeletons\\");
		filepath.append(skel);
		filepath.append(".mrskel");


		glm::mat4 * localTx = new glm::mat4[skelHandler->GetNumJoints()];

		for (uint32_t i = 0; i < skelHandler->GetNumJoints(); i++)
		{
			localTx[i] = skelHandler->GetMatrix()[i];
		}

		animSkel->SetSkeleton(skelHandler->GetParentIDs(), localTx, skelHandler->GetNumJoints());
		animCtrl->SetSkeleton(animSkel);

		delete skelHandler;

		// Animation.
		MrAnimHandler * animHandler = new MrAnimHandler;

		for (uint32_t i = 0; i < numAnim; i++)
		{	
			std::string animFilepath(".\\Assets\\Animations\\");
			animFilepath.append(anim[i]);
			animFilepath.append(".mranim");

			animHandler->Import(animFilepath.c_str());

			AnimClip * animClip = new AnimClip;
			KeyFrame * key = new KeyFrame[30];

			for (uint32_t j = 0; j < 30; j++)
			{
				key[j].localTx = new glm::mat4[animHandler->GetNumKeyFramedJoints()];

				for (uint32_t n = 0; n < animHandler->GetNumKeyFramedJoints(); n++)
				{
					key[j].localTx[n] = animHandler->GetKeyFramedJoints()[n].matrix[j];
				}
			}

			animClip->SetAnimation(key, 0, 30);
			animCtrl->AddAnimation(animClip);
		}

		delete animHandler;

		prefab->SetAnimController(animCtrl);
	}


	prefab->SetName(mesh);
	prefab->Create();

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
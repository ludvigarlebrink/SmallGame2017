#include "MeshImporter.h"



MeshImporter::MeshImporter()
{
	mBoneFinalTf.resize(4);
}


MeshImporter::~MeshImporter()
{
	// Do nothing...
}

Mesh& MeshImporter::Import()
{
	Assimp::Importer	m_importer;


	const aiScene * scene = m_importer.ReadFile(".\\Assets\\Sprites\\hej4.fbx", aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

	if (scene == NULL)
	{
		std::cout << "Could not load mesh: " << m_importer.GetErrorString() << std::endl;
		return Mesh();
	}


	//	for (int i = 0; i < scene->mNumMeshes; i++)
	//	{
	//		aiMesh* imported_mesh = scene->mMeshes[i];
	//		Vertex3D m_meshVertex3D;
	//		// Position
	//		m_meshVertex3D.position.x = imported_mesh->mVertices->x;
	//		m_meshVertex3D.position.y = imported_mesh->mVertices->y;
	//		m_meshVertex3D.position.z = imported_mesh->mVertices->z;
	//
	//		// Normal
	//		m_meshVertex3D.normal.x = imported_mesh->mNormals->x;
	//		m_meshVertex3D.normal.y = imported_mesh->mNormals->y;
	//		m_meshVertex3D.normal.z = imported_mesh->mNormals->z;
	//
	//		// Texture Coords
	//		m_meshVertex3D.texCoordsAlpha.x = 1.0f;
	//		m_meshVertex3D.texCoordsAlpha.y = 1.0f;
	//		m_meshVertex3D.texCoordsAlpha.z = 1.0f;
	//
	//		m_mesh.LoadMesh(&m_meshVertex3D, imported_mesh->mNumVertices);
	//	}


	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> texCoords;
	std::vector<glm::vec4> id;
	std::vector<glm::vec4> weights;
	std::vector<unsigned int> ind;


	//INDICES

	// JUST SUPPORT ONE MESH
	std::cout << scene->mNumMeshes;


	size_t numVerts = scene->mMeshes[0]->mNumVertices;
	size_t numBones = scene->mMeshes[0]->mNumBones;
	int numInd = scene->mMeshes[0]->mNumFaces * 3;



	positions.reserve(numVerts);
	normals.reserve(numVerts);
	texCoords.reserve(numVerts);
	id.resize(numVerts);
	weights.resize(numVerts);

	std::cout << numBones << std::endl;



	const aiMesh* paiMesh = scene->mMeshes[0];
	const aiVector3D zero3D(0.0f, 0.0f, 0.0f);



	for (size_t i = 0; i < numVerts; i++)
	{
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &zero3D;

		positions.push_back(glm::vec3(pPos->x, pPos->y, pPos->z));
		normals.push_back(glm::vec3(pNormal->x, pNormal->y, pNormal->z));
		texCoords.push_back(glm::vec3(pTexCoord->x, pTexCoord->y, 1.0f));
	}

	for (size_t i = 0; i < paiMesh->mNumFaces; i++)
	{
		const aiFace& Face = paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		ind.push_back(Face.mIndices[0]);
		ind.push_back(Face.mIndices[1]);
		ind.push_back(Face.mIndices[2]);
	}

	


	// JOINTS :D:D::D:D:D:D:D:D:D

	size_t numBonez = 0;
	std::vector<BoneInfo> boneInfo;
	MeshEntry entry;

	std::vector<VtxBoneInfo> bone;

	for (size_t i = 0; i < paiMesh->mNumBones; i++)
	{
		size_t boneIndex = 0;

		std::string boneName(paiMesh->mBones[i]->mName.data);

		if (mBoneIdx.find(boneName) == mBoneIdx.end())
		{
			std::cout << boneName << std::endl;
			boneIndex = numBonez;
			numBonez++;
			BoneInfo bi; //Maybe identity?

			bi.boneOffset = paiMesh->mBones[i]->mOffsetMatrix;
			mBoneIdx[boneName] = boneIndex;
		}
		else
		{
			boneIndex = mBoneIdx[boneName];
		}


		

		for (size_t j = 0; j < paiMesh->mBones[i]->mNumWeights; j++)
		{

			size_t vertexID =  paiMesh->mBones[i]->mWeights[j].mVertexId;

			float weight = paiMesh->mBones[i]->mWeights[j].mWeight;

			//bones.(AddBoneData(boneIndex, weight));
		//	bone.push_back(AddBoneData(boneIndex, weight)):

			id[vertexID].x = boneIndex;
			id[vertexID].y = boneIndex;
			id[vertexID].z = boneIndex;
			id[vertexID].w = boneIndex;

			weights[j].x = weight;
			weights[j].y = weight;
			weights[j].z = weight;
			weights[j].w = weight;

			VtxBoneInfo tmp;
			tmp.AddBoneData(boneIndex, weight);
			bone.push_back(tmp);
		}
	}

//	size_t j = 0;
//
// 	for (size_t i = 0; i < bone.size() - 4; i += 4)
//	{
//		id[j].x = bone[i].ID[0];
//		id[j].y = bone[i + 1].ID[0];
//		id[j].z = bone[i + 2].ID[0];
//		id[j].w = bone[i + 3].ID[0];
//
//		weights[j].x = bone[i].W[0];
//		weights[j].y = bone[i + 1].W[0];
//		weights[j].z = bone[i + 2].W[0];
//		weights[j].w = bone[i + 3].W[0];
//
//		j++;
//		std::cout << j << std::endl;
//
//	}

	std::vector<Vertex3DSkelAnimation> vert;

	for (size_t i = 0; i < ind.size(); i++)
	{
		Vertex3DSkelAnimation tmp;
		tmp.position = positions[ind[i]];
		tmp.normal = normals[ind[i]];
		tmp.texCoordsAlpha = texCoords[ind[i]];
		tmp.jointIDs = id[ind[i]];
		tmp.weights = weights[ind[i]];
		vert.push_back(tmp);

	}
	

	
	std::cout << paiMesh->mNumBones << std::endl;

	for (size_t h = 0; h < 4; h++)
	{
		aiMatrix4x4 hej = paiMesh->mBones[h]->mOffsetMatrix;
		glm::mat4 hej2;

		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				hej2[i][j] = hej[i][j];
				mBoneOffsets.push_back(hej2);
			}
		}
	}
	

	
	const aiAnimation * aiAnim = scene->mAnimations[0];
	
//	const aiNodeAnim * pNodeAnim = aiAnim->mChannels[0]->mScalingKeys->mValue;


	std::cout << "Channles " << scene->mAnimations[0]->mNumChannels << std::endl;;
	std::cout << scene->mAnimations[0]->mChannels[0]->mNodeName.C_Str() << std::endl;
	std::cout << scene->mAnimations[0]->mChannels[1]->mNodeName.C_Str() << std::endl;
	std::cout << scene->mAnimations[0]->mChannels[2]->mNodeName.C_Str() << std::endl;
	std::cout << scene->mAnimations[0]->mChannels[3]->mNodeName.C_Str() << std::endl;
	std::cout << scene->mAnimations[0]->mChannels[4]->mNodeName.C_Str() << std::endl;
	std::cout << scene->mAnimations[0]->mChannels[5]->mNodeName.C_Str() << std::endl;
	std::cout << scene->mAnimations[0]->mChannels[6]->mNodeName.C_Str() << std::endl;
	std::cout << scene->mAnimations[0]->mChannels[7]->mNodeName.C_Str() << std::endl;


	std::vector<const aiNodeAnim*> boneAnim;

	for (size_t i = 0; i < scene->mAnimations[0]->mNumChannels; i++)
	{
		const aiNodeAnim * pNodeAnim = scene->mAnimations[0]->mChannels[i];

		// DOES NOT REALLY WORK
		// NEED INDEXING
		boneAnim.push_back(pNodeAnim);

		//scene->mAnimations[0]->mNumChannels;
	}








	//aiAnimation;


	
//	const aiNodeAnim anim;


	InitAnimation(scene->mRootNode, scene->mAnimations[0]);
	UpdateFrameTfs(1);

	

	m_jointSkeleton.AddMatTemp(mBoneFinalTf[0]);
	m_jointSkeleton.AddMatTemp(mBoneFinalTf[1]);
	m_jointSkeleton.AddMatTemp(mBoneFinalTf[2]);
	m_jointSkeleton.AddMatTemp(mBoneFinalTf[3]);


	m_mesh.Load(&vert[0], vert.size());

	return m_mesh;
}

JointSkeleton & MeshImporter::GetSkeleton()
{
	return m_jointSkeleton;
}

void MeshImporter::InitAnimation(aiNode * root, aiAnimation * pAnimation)
{
	pRootNode = root;

	// In case sometimes the root is some weird thing...
	pRootNode = root;
	std::string nodeName(pRootNode->mName.data);

	std::cout << "Children: " << pRootNode->mNumChildren << std::endl;
	while (mBoneIdx.find(nodeName) == mBoneIdx.end())
	{
		pRootNode = pRootNode->mChildren[0];
		nodeName = std::string(pRootNode->mName.data);
		std::cout << nodeName << std::endl;
	}

	// Then find the anim channels;
	pAnim = pAnimation;
	mBoneAnim.resize(mBoneIdx.size());
	for (uint32_t i = 0; i< pAnim->mNumChannels; ++i)
	{
		const aiNodeAnim* pNodeAnim = pAnim->mChannels[i];
		std::string name(pNodeAnim->mNodeName.data);

		// TODO: assume always finds a match
		uint32_t boneIdx = mBoneIdx[name];
		mBoneAnim[boneIdx] = pNodeAnim;

		//	printf("Idx: %2u, Name: %s\n", boneIdx, name.c_str());
	}
}

void MeshImporter::UpdateFrameTfs(int frameNum)
{
	/*
	printf("There are %d Rot %d Loc %d Scal Keys\n",
	pAnim->mChannels[0]->mNumRotationKeys,
	pAnim->mChannels[0]->mNumPositionKeys,
	pAnim->mChannels[0]->mNumScalingKeys);
	*/

	// Recursively update the transform;
	ReadNodeHeirarchy(frameNum, pRootNode, glm::mat4(1.0f));
}

const std::vector<glm::mat4> MeshImporter::GetTfs()
{
	return mBoneFinalTf;
}



void MeshImporter::ReadNodeHeirarchy(int frameIdx, const aiNode * pNode, const glm::mat4 & parTf)
{
	std::string nodeName(pNode->mName.data);
	if (mBoneIdx.find(nodeName) == mBoneIdx.end())
		return;

	uint32_t boneIdx = mBoneIdx[nodeName];

	const aiNodeAnim* pAnim = mBoneAnim[boneIdx];
	aiVectorKey& sc = pAnim->mScalingKeys[frameIdx % pAnim->mNumScalingKeys];
	aiMatrix4x4 matScale;
	aiMatrix4x4::Scaling(sc.mValue, matScale);

	aiQuatKey& qt = pAnim->mRotationKeys[frameIdx % pAnim->mNumRotationKeys];
	aiMatrix4x4 matRotat(qt.mValue.GetMatrix());

	aiVectorKey& tr = pAnim->mPositionKeys[frameIdx % pAnim->mNumPositionKeys];
	aiMatrix4x4 matTrans;
	aiMatrix4x4::Translation(tr.mValue, matTrans);

	// Convert from aiMatrix4x4 to glm::mat4
	glm::mat4 nodeTf;
	CopyMat(matTrans * matRotat * matScale, nodeTf);

	glm::mat4 globalTf = parTf * nodeTf;

	glm::mat4 finalTf = globalTf * mBoneOffsets[boneIdx];
	mBoneFinalTf[boneIdx] = finalTf;

	// Print out info
	//    cout << nodeName << endl;
	//    pprintMat4x4(finalTf);
	// pprintScQtTr(sc.mValue, qt.mValue, tr.mValue);
	//    pprintMat16(nodeTf);

	for (uint32_t i = 0; i< pNode->mNumChildren; ++i)
		ReadNodeHeirarchy(frameIdx, pNode->mChildren[i], globalTf);
}
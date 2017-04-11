#include "MeshImporter.h"



MeshImporter::MeshImporter()
{
	// Do nothing...
}


MeshImporter::~MeshImporter()
{
	// Do nothing...
}

Mesh& MeshImporter::Import()
{
	Assimp::Importer	m_importer;


	const aiScene * scene = m_importer.ReadFile(".\\Assets\\Sprites\\hej2.fbx", aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

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
	std::vector<unsigned int> ind;


	//INDICES

	// JUST SUPPORT ONE MESH

	unsigned int numVerts = scene->mMeshes[0]->mNumVertices;
	int numInd = scene->mMeshes[0]->mNumFaces * 3;



	positions.reserve(numVerts);
	normals.reserve(numVerts);
	texCoords.reserve(numVerts);

	const aiMesh* paiMesh = scene->mMeshes[0];
	const aiVector3D zero3D(0.0f, 0.0f, 0.0f);

	for (size_t i = 0; i < numVerts; i++)
	{
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : & zero3D;

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


	std::vector<Vertex3D> vert;

	for (size_t i = 0; i < ind.size(); i++)
	{
		Vertex3D tmp;
		tmp.position = positions[ind[i]];
		tmp.normal = normals[ind[i]];
		tmp.texCoordsAlpha = texCoords[ind[i]];
		vert.push_back(tmp);
	}


	m_mesh.LoadMesh(&vert[0], vert.size());

	return m_mesh;
}

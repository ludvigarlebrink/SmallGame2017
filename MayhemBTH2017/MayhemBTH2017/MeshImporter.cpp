#include "MeshImporter.h"



MeshImporter::MeshImporter()
{
	// Do nothing...
}


MeshImporter::~MeshImporter()
{
	// Do nothing...
}

void MeshImporter::ImportFromFile()
{


	scene = importer.ReadFile(".\\Assets\\Sprites\\hej.fbx", aiProcessPreset_TargetRealtime_Quality);

	if (!scene)
	{
		std::cout << "Could not load mesh: " << importer.GetErrorString() << std::endl;
		return;
	}

	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		aiMesh* imported_mesh = scene->mMeshes[i];
		Vertex3D m_meshVertex3D;
		// Position
		m_meshVertex3D.position.x = imported_mesh->mVertices->x;
		m_meshVertex3D.position.y = imported_mesh->mVertices->y;
		m_meshVertex3D.position.z = imported_mesh->mVertices->z;

		// Normal
		m_meshVertex3D.normal.x = imported_mesh->mNormals->x;
		m_meshVertex3D.normal.y = imported_mesh->mNormals->y;
		m_meshVertex3D.normal.z = imported_mesh->mNormals->z;

		// Texture Coords
		m_meshVertex3D.texCoordsAlpha.x = 1.0f;
		m_meshVertex3D.texCoordsAlpha.y = 1.0f;
		m_meshVertex3D.texCoordsAlpha.z = 1.0f;

		m_mesh.LoadMesh(&m_meshVertex3D, imported_mesh->mNumVertices);
	}
}

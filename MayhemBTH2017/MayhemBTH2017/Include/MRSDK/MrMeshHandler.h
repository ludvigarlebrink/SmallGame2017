#pragma once


#include <fstream>
#include <cstdint>
#include <glm.hpp>


class MrMeshHandler
{
public:
	//::.. CONSTRUCTORS ..:://
	MrMeshHandler();
	virtual ~MrMeshHandler();

	//::.. IMPORT/EXPORT ..:://
	bool Import(const char* filepath);
	bool Export(const char* filepath);

	void Free();

	//::.. GET FUNCTIONS ..:://
	const char * GetName();
	uint32_t GetNumVerts();
	bool GetHasSkinWeights();
	glm::vec3 * GetPositions();
	glm::vec2 * GetTexCoords();
	glm::vec3 * GetNormals();
	glm::vec3 * GetTangents();
	glm::vec3 * GetBiTangents();
	glm::vec4 * GetSkinWeights();
	glm::vec4 * GetJointIDs();

	//::.. SET FUNCTIONS ..:://
	void SetFileName(const char * fileName);
	void SetNumVerts(uint32_t numVerts);
	void SetHasSkinWeights(bool hasSkinWeights);
	void SetPositions(glm::vec3 * pos);
	void SetTexCoords(glm::vec2 * tex);
	void SetNormals(glm::vec3 * nor);
	void SetTangents(glm::vec3 * tan);
	void SetBiTangents(glm::vec3 * bi);
	void SetSkinWeights(glm::vec4 * weights);
	void SetJointIDs(glm::vec4 * jointIDs);


private:
	//::.. HELP FUNCTIONS .:://
	void Init();

private:
	bool			m_isLoaded;

	const char *	m_fileName;

	uint32_t		m_numVerts;
	bool			m_hasSkinWeights;

	glm::vec3 *		m_postions;
	glm::vec2 *		m_texCoords;
	glm::vec3 *		m_normals;
	glm::vec3 *		m_tangents;
	glm::vec3 *		m_bitangents;
	glm::vec4 *		m_skinWeights;
	glm::vec4 *		m_jointIDs;
};



inline MrMeshHandler::MrMeshHandler()
{
	Init();
}


inline MrMeshHandler::~MrMeshHandler()
{
	Free();
}


inline bool MrMeshHandler::Import(const char * filepath)
{
	if (m_isLoaded)
	{
		Free();
	}

	std::ifstream file(filepath, std::ios::binary);

	if (!file.is_open())
	{
		return false;
	}

	file.read(reinterpret_cast<char*>(&m_numVerts), sizeof(uint32_t));

	m_postions = new glm::vec3[m_numVerts];
	m_texCoords = new glm::vec2[m_numVerts];
	m_normals = new glm::vec3[m_numVerts];
	m_tangents = new glm::vec3[m_numVerts];
	m_bitangents = new glm::vec3[m_numVerts];
	m_skinWeights = new glm::vec4[m_numVerts];
	m_jointIDs = new glm::vec4[m_numVerts];


	// Positions.
	file.read(reinterpret_cast<char*>(m_postions), sizeof(glm::vec3) * m_numVerts);

	// Texture coords.
	file.read(reinterpret_cast<char*>(m_texCoords), sizeof(glm::vec2) * m_numVerts);

	// Normals.
	file.read(reinterpret_cast<char*>(m_normals), sizeof(glm::vec3) * m_numVerts);

	// Tangents.
	file.read(reinterpret_cast<char*>(m_tangents), sizeof(glm::vec3) * m_numVerts);

	// Bitangents.
	file.read(reinterpret_cast<char*>(m_bitangents), sizeof(glm::vec3) * m_numVerts);

	// Has skin weights.
	file.read(reinterpret_cast<char*>(&m_hasSkinWeights), sizeof(bool));

	if (m_hasSkinWeights)
	{
		// Skin weights.
		file.read(reinterpret_cast<char*>(m_skinWeights), sizeof(glm::vec4) * m_numVerts);


		// Joint weights.
		file.read(reinterpret_cast<char*>(m_jointIDs), sizeof(glm::vec4) * m_numVerts);
	}

	file.close();

	m_isLoaded = true;

	return true;
}


inline bool MrMeshHandler::Export(const char* filepath)
{
	std::ofstream file(filepath, std::ios::binary);

	if (!file.is_open())
	{
		return false;
	}


	file.write(reinterpret_cast<char*>(&m_numVerts), sizeof(uint32_t));


	// Positions.
	file.write(reinterpret_cast<char*>(m_postions), sizeof(glm::vec3) * m_numVerts);

	// Texture coords.
	file.write(reinterpret_cast<char*>(m_texCoords), sizeof(glm::vec2) * m_numVerts);

	// Normals.
	file.write(reinterpret_cast<char*>(m_normals), sizeof(glm::vec3) * m_numVerts);

	// Tangents.
	file.write(reinterpret_cast<char*>(m_tangents), sizeof(glm::vec3) * m_numVerts);

	// Bitangents.
	file.write(reinterpret_cast<char*>(m_bitangents), sizeof(glm::vec3) * m_numVerts);

	// Has skin weights.
	file.write(reinterpret_cast<char*>(&m_hasSkinWeights), sizeof(bool));

	if (m_hasSkinWeights)
	{
		// Skin weights.
		file.write(reinterpret_cast<char*>(m_skinWeights), sizeof(glm::vec4) * m_numVerts);

		// Joint weights.
		file.write(reinterpret_cast<char*>(m_jointIDs), sizeof(glm::vec4) * m_numVerts);
	}
	

	file.close();

	return true;
}


inline void MrMeshHandler::Free()
{
	if (!m_isLoaded)
	{
		return;
	}

	delete[] m_postions;
	delete[] m_texCoords;
	delete[] m_normals;
	delete[] m_tangents;
	delete[] m_bitangents;
	delete[] m_skinWeights;
	delete[] m_jointIDs;

	Init();
}


//::.. GET FUNCTIONS ..:://
inline const char * MrMeshHandler::GetName()
{
	return m_fileName;
}


inline uint32_t MrMeshHandler::GetNumVerts()
{
	return m_numVerts;
}

inline bool MrMeshHandler::GetHasSkinWeights()
{
	return m_hasSkinWeights;
}


inline glm::vec3 * MrMeshHandler::GetPositions()
{
	return m_postions;
}


inline glm::vec2 * MrMeshHandler::GetTexCoords()
{
	return m_texCoords;
}


inline glm::vec3 * MrMeshHandler::GetNormals()
{
	return m_normals;
}


inline glm::vec3 * MrMeshHandler::GetTangents()
{
	return m_tangents;
}


inline glm::vec3 * MrMeshHandler::GetBiTangents()
{
	return m_bitangents;
}


inline glm::vec4 * MrMeshHandler::GetSkinWeights()
{
	return m_skinWeights;
}


inline glm::vec4 * MrMeshHandler::GetJointIDs()
{
	return m_jointIDs;
}


//::.. SET FUNCTIONS ..:://
inline void MrMeshHandler::SetFileName(const char * fileName)
{
	m_fileName = fileName;
}


inline void MrMeshHandler::SetNumVerts(uint32_t numVerts)
{
	m_numVerts = numVerts;
}

inline void MrMeshHandler::SetHasSkinWeights(bool hasSkinWeights)
{
	m_hasSkinWeights = hasSkinWeights;
}


inline void MrMeshHandler::SetPositions(glm::vec3 * pos)
{
	m_postions = pos;
}


inline void MrMeshHandler::SetTexCoords(glm::vec2 * tex)
{
	m_texCoords = tex;
}


inline void MrMeshHandler::SetNormals(glm::vec3 * nor)
{
	m_normals = nor;
}


inline void MrMeshHandler::SetTangents(glm::vec3 * tan)
{
	m_tangents = tan;
}


inline void MrMeshHandler::SetBiTangents(glm::vec3 * bi)
{
	m_bitangents = bi;
}


inline void MrMeshHandler::SetSkinWeights(glm::vec4 * weights)
{
	m_skinWeights = weights;
}


inline void MrMeshHandler::SetJointIDs(glm::vec4 * jointIDs)
{
	m_jointIDs = jointIDs;
}


//::.. HELP FUNCTIONS ..:://
inline void MrMeshHandler::Init()
{
	m_isLoaded = false;

	m_numVerts = 0;
	m_hasSkinWeights = true;

	m_postions = nullptr;
	m_texCoords = nullptr;
	m_normals = nullptr;
	m_tangents = nullptr;
	m_bitangents = nullptr;
	m_skinWeights = nullptr;
	m_jointIDs = nullptr;
}

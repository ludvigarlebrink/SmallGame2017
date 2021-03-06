#pragma once


#include <fstream>
#include <cstdint>
#include <glm.hpp>



struct MrKeyFramedJoint
{
	uint32_t	jointID;
	uint32_t	numKeyframes;
	glm::mat4 *	matrix;
	int32_t	*	keyFrames;
};


class MrAnimHandler
{
public:
	//::.. CONSTRUCTORS ..:://
	MrAnimHandler();
	virtual ~MrAnimHandler();

	//::.. IMPORT/EXPORT ..:://
	bool Import(const char * filepath);
	bool Export(const char * filepath);

	void Free();

	//::.. SET FUNCTIONS ..:://
	void SetName(const char * name);
	void SetFirstKeyFrame(int32_t firstKeyFrame);
	void SetLastKeyFrame(int32_t lastKeyFrame);
	void SetNumKeyFramedJoints(uint32_t numKeyFramedJoints);
	void SetKeyframedJoint(MrKeyFramedJoint * keyFramedJoints);

	//::.. GET FUNCTIONS ..:://
	const char * GetName();
	int32_t GetFirstKeyFrame();
	int32_t GetLastKeyFrame();
	uint32_t GetNumKeyFramedJoints();
	MrKeyFramedJoint * GetKeyFramedJoints();


private:
	//::.. HELP FUNCTIONS ..:://
	void Init();

private:
	const char *		m_name;

	bool				m_isLoaded;

	int32_t				m_firstKeyFrame;
	int32_t				m_lastKeyFrame;

	uint32_t			m_numKeyFramedJoints;

	MrKeyFramedJoint *	m_keyFramedJoints;

};


//::.. CONSTRUCTORS ..:://
inline MrAnimHandler::MrAnimHandler()
{
	Init();
}


inline MrAnimHandler::~MrAnimHandler()
{
	Free();
}


//::.. IMPORT/EXPORT ..:://
inline bool MrAnimHandler::Import(const char * filepath)
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

	file.read(reinterpret_cast<char*>(&m_numKeyFramedJoints), sizeof(uint32_t));

	m_keyFramedJoints = new MrKeyFramedJoint[m_numKeyFramedJoints];

	for (uint32_t i = 0; i < m_numKeyFramedJoints; i++)
	{
		file.read(reinterpret_cast<char*>(&m_keyFramedJoints[i].jointID), sizeof(uint32_t));
		file.read(reinterpret_cast<char*>(&m_keyFramedJoints[i].numKeyframes), sizeof(uint32_t));

		m_keyFramedJoints[i].matrix = new glm::mat4[m_keyFramedJoints[i].numKeyframes];
		m_keyFramedJoints[i].keyFrames = new int32_t[m_keyFramedJoints[i].numKeyframes];

		file.read(reinterpret_cast<char*>(m_keyFramedJoints[i].matrix), sizeof(glm::mat4) * m_keyFramedJoints[i].numKeyframes);
		file.read(reinterpret_cast<char*>(m_keyFramedJoints[i].keyFrames), sizeof(int32_t) * m_keyFramedJoints[i].numKeyframes);
	}

	file.close();

	m_isLoaded = true;

	return true;
}


inline bool MrAnimHandler::Export(const char * filepath)
{
	std::ofstream file(filepath, std::ios::binary);

	if (!file.is_open())
	{
		return false;
	}

	file.write(reinterpret_cast<char*>(&m_numKeyFramedJoints), sizeof(uint32_t));

	for (uint32_t i = 0; i < m_numKeyFramedJoints; i++)
	{
		file.write(reinterpret_cast<char*>(&m_keyFramedJoints[i].jointID), sizeof(uint32_t));
		file.write(reinterpret_cast<char*>(&m_keyFramedJoints[i].numKeyframes), sizeof(uint32_t));
		file.write(reinterpret_cast<char*>(m_keyFramedJoints[i].matrix), sizeof(glm::mat4) * m_keyFramedJoints[i].numKeyframes);
		file.write(reinterpret_cast<char*>(m_keyFramedJoints[i].keyFrames), sizeof(int32_t) * m_keyFramedJoints[i].numKeyframes);
	}

	file.close();

	return true;
}


inline void MrAnimHandler::Free()
{
	if (!m_isLoaded)
	{
		return;
	}

	for (uint32_t i = 0; i < m_numKeyFramedJoints; i++)
	{
		delete[] m_keyFramedJoints[i].matrix;
		delete[] m_keyFramedJoints[i].keyFrames;
	}

	delete[] m_keyFramedJoints;

	Init();
}


//::.. SET FUNCTIONS ..:://
inline void MrAnimHandler::SetName(const char * name)
{
	m_name = name;
	m_isLoaded = true;
}


inline void MrAnimHandler::SetFirstKeyFrame(int32_t firstKeyFrame)
{
	m_firstKeyFrame = firstKeyFrame;
	m_isLoaded = true;
}


inline void MrAnimHandler::SetLastKeyFrame(int32_t lastKeyFrame)
{
	m_lastKeyFrame = lastKeyFrame;
	m_isLoaded = true;
}


inline void MrAnimHandler::SetNumKeyFramedJoints(uint32_t numKeyFramedJoints)
{
	m_numKeyFramedJoints = numKeyFramedJoints;
	m_isLoaded = true;
}


inline void MrAnimHandler::SetKeyframedJoint(MrKeyFramedJoint * keyFramedJoints)
{
	m_keyFramedJoints = keyFramedJoints;
}


//::.. GET FUNCTIONS ..:://
inline const char * MrAnimHandler::GetName()
{
	return m_name;
}


inline int32_t MrAnimHandler::GetFirstKeyFrame()
{
	return m_firstKeyFrame;
}


inline int32_t MrAnimHandler::GetLastKeyFrame()
{
	return m_lastKeyFrame;
}


inline uint32_t MrAnimHandler::GetNumKeyFramedJoints()
{
	return m_numKeyFramedJoints;
}


inline MrKeyFramedJoint * MrAnimHandler::GetKeyFramedJoints()
{
	return m_keyFramedJoints;
}


//::.. HELP FUNCTIONS ..:://
inline void MrAnimHandler::Init()
{
	m_isLoaded = false;

	m_numKeyFramedJoints = 0;

	m_keyFramedJoints = nullptr;
}

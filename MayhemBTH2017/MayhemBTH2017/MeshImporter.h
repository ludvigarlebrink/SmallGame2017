#ifndef __MESHIMPORTER_H__
#define __MESHIMPORTER_H__

#include "Mesh.h"
#include "StackPool.h"

//Assimp
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"
#include "assimp\anim.h"


#include "JointSkeleton.h"

#include <fstream>
#include <iostream>
#include <map>

#include <vector>

class MeshImporter
{
public:
	MeshImporter();
	virtual ~MeshImporter();

	Mesh& Import();
	JointSkeleton& GetSkeleton();


	void InitAnimation(aiNode* root, aiAnimation* pAnimation);

	void UpdateFrameTfs(int frameNum);

	const std::vector<glm::mat4> GetTfs();

private:

	#define NUM_BONES_PER_VERTEX 4
	struct BoneInfo
	{
		aiMatrix4x4 boneOffset;
		aiMatrix4x4 finalTransformation;
	};

	struct MeshEntry
	{
		uint32_t numIndices = 0;
		uint32_t baseVertex = 0;
		uint32_t baseIndex = 0;
	};


	Assimp::Importer	m_importer;
	Mesh				m_mesh;
	JointSkeleton		m_jointSkeleton;

	typedef unsigned int uint;
	struct VtxBoneInfo
	{
		uint  ID[NUM_BONES_PER_VERTEX];
		float  W[NUM_BONES_PER_VERTEX];

		void Reset() { memset(ID, 0, sizeof(ID)); memset(W, 0, sizeof(W)); }

		void AddBoneData(unsigned int BoneID, float weight)
		{
			for (unsigned int i = 0; i< NUM_BONES_PER_VERTEX; i++)
			{
				if (W[i] == 0.0f)
				{
					ID[i] = BoneID;
					W[i] = weight;
					return;
				}
			}

			//      printf("Error, more than 4 weights per vertex\n");
			weight /= NUM_BONES_PER_VERTEX;
			for (unsigned int i = 0; i< NUM_BONES_PER_VERTEX; i++)
			{
				W[i] += weight;
			}
			return;
			// should never arrive here (More bones than we have space for    
			assert(0);
		}
	};


	void ReadNodeHeirarchy(int frameIdx,
		const aiNode* pNode,
		const glm::mat4& parTf);


	aiNode * pRootNode;
	aiAnimation * pAnim;

	std::map<std::string, unsigned int> mBoneIdx;

	std::vector<glm::mat4> mBoneOffsets;

	std::vector<glm::mat4> mBoneFinalTf;

	std::vector<const aiNodeAnim*> mBoneAnim;



	template <typename RM, typename CM>
	void CopyMat(const RM& from, CM& to);

};


#endif

template<typename RM, typename CM>
inline void MeshImporter::CopyMat(const RM & from, CM & to)
{
	to[0][0] = from.a1; to[1][0] = from.a2;
	to[2][0] = from.a3; to[3][0] = from.a4;
	to[0][1] = from.b1; to[1][1] = from.b2;
	to[2][1] = from.b3; to[3][1] = from.b4;
	to[0][2] = from.c1; to[1][2] = from.c2;
	to[2][2] = from.c3; to[3][2] = from.c4;
	to[0][3] = from.d1; to[1][3] = from.d2;
	to[2][3] = from.d3; to[3][3] = from.d4;
}

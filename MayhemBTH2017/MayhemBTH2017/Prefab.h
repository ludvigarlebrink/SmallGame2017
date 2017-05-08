#ifndef __PREFAB_H__
#define __PREFAB_H__


#include "Transform.h"
#include "Mesh.h"
#include "AnimController.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "Material.h"


class Prefab
{
public:
	enum Space
	{
		SPACE_LOCAL = 0,
		SPACE_GLOBAL,
		NUM_SPACES
	};

	Prefab();
	virtual ~Prefab();

	virtual void Update();
	virtual void Render(Camera& cam);

	void Create();
	void Free();

	//::.. MODIFY FUNCTIONS ..:://
	void Move(glm::vec3 pos, uint32_t space = SPACE_LOCAL);
	void Move(float x, float y, float z, uint32_t space = SPACE_LOCAL);
	void Rotate(glm::vec3 rot, uint32_t space = SPACE_LOCAL);
	void Rotate(float x, float y, float z, uint32_t space = SPACE_LOCAL);
	void Scale(glm::vec3 scale, uint32_t space = SPACE_LOCAL);
	void Scale(float x, float y, float z, uint32_t space = SPACE_LOCAL);

	//::.. GET FUNCTIONS ..:://
	bool GetIsEnabled() const;
	const char * GetName() const;
	Transform& GetTransform(uint32_t space = SPACE_LOCAL);
	glm::vec3 GetPosition(uint32_t space = SPACE_LOCAL);
	glm::vec3 GetRotation(uint32_t space = SPACE_LOCAL);
	glm::vec3 GetScale(uint32_t space = SPACE_LOCAL);
	Mesh * GetMesh() const;
	AnimController * GetAnimController() const;

	//::.. SET FUNCTIONS ..:://
	void SetIsEnabled(bool enabled);
	void SetName(const char * name);
	void SetTransform(const Transform& transform, uint32_t space = SPACE_LOCAL);
	void SetPosition(glm::vec3 pos, uint32_t space = SPACE_LOCAL);
	void SetPosition(float x, float y, float z, uint32_t space = SPACE_LOCAL);
	void SetRotation(glm::vec3 rot, uint32_t space = SPACE_LOCAL);
	void SetRotation(float x, float y, float z, uint32_t space = SPACE_LOCAL);
	void SetScale(glm::vec3 scale, uint32_t space = SPACE_LOCAL);
	void SetScale(float x, float y, float z, uint32_t space = SPACE_LOCAL);
	void SetMesh(Mesh * mesh);
	void SetAnimController(AnimController * animController);
	void SetShaderProgram(const char * programName);
	void SetMaterial(Material * material);
	void SetAlbedoID(GLuint id);
	void SetVertShader(char * shader);
	void SetFragShader(char * shader);


private:
	//::.. HELP FUNCTIONS ..:://
	void Init();

private:
	enum Uniforms
	{
		M,
		V,
		P,
		JOINTS,
		ALBEDO_MAP,
		NORMAL_MAP,
		NUM_UNIFORMS
	};

	char *				m_vertShader;
	char *				m_fragShader;

	bool				m_hasBeenCreated;
	bool				m_isEnabled;
	bool				m_hasAnimation;

	const char *		m_name;
	
	Transform			m_localTx;
	Transform			m_globalTx;

	//TODO
	Transform			m_tx[NUM_SPACES];

	Mesh *				m_mesh;
	const char *		m_shaderProg;
	AnimController *	m_animController;
	Material *			m_material;
	GLuint				m_shaderProgram;
	GLuint				m_uniforms[NUM_UNIFORMS];
	GLuint				m_albedoID;
	GLuint				m_vao;
};


#endif 
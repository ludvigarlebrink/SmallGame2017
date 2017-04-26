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
	Prefab();
	virtual ~Prefab();

	void Update();
	void Render(Camera& cam);

	void Create();

	//::.. GET FUNCTIONS ..:://
	const char * GetName() const;
	const Transform& GetTransform() const;
	Mesh * GetMesh() const;
	AnimController * GetAnimController() const;

	//::.. SET FUNCTIONS ..:://
	void SetName(const char * name);
	void SetTransform(const Transform& transform);
	void SetMesh(Mesh * mesh);
	void SetAnimController(AnimController * animController);
	void SetShaderProgram(const char * programName);
	void SetMaterial(Material * material);

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
		NR_UNIFORMS
	};

	bool				m_hasBeenCreated;
	const char *		m_name;
	Transform			m_transform;
	Mesh *				m_mesh;
	const char *		m_shaderProg;
	AnimController *	m_animController;
	Material*			m_material;
	GLuint				m_shaderProgram;
	GLuint				m_uniforms[NR_UNIFORMS];
};


#endif 
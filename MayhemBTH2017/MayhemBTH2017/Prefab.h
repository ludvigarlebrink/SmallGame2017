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
	void Render(const Camera& cam);

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
	const char *		m_name;
	Transform			m_transform;
	Mesh *				m_mesh;
	const char *		m_shaderProg;
	AnimController *	m_animController;
	Material*			m_material;

};


#endif 
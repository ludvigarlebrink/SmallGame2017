#ifndef __MESHQUAD_H__
#define __MESHQUAD_H__

#include <glew.h>
#include "QuadShader.h"
#include "Camera.h"
#include "Transform.h"

class MeshQuad
{
public:
	//::.. CONSTRUCTORS ..:://
	MeshQuad();
	virtual ~MeshQuad();

	//::.. INITIALIZERS ..:://
	bool LoadMesh();
	//bool FreeMesh();

	//::.. RENDER ..:://
	bool Render();
	void Draw();


	//::.. HELP FUNCTIONS ..:://


private:
	GLuint m_vao;
	GLuint m_vbo;
	QuadShader quadShader;
	Camera m_camera;
	Transform m_transform;

	const static int SIZE_X = 84;
	const static int SIZE_Y = 48;

};

#endif // !__MESHQUAD_H__

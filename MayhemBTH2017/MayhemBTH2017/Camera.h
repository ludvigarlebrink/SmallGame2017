#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm.hpp>
#include <gtx\transform.hpp>


class Camera
{
public:
	//::.. DUMMY CONSTRUCTORS ..:://
	Camera();
	virtual ~Camera();

	//::.. FAKE FUNCTIONS ..:://

	//::.. GET FUNCTIONS ..:://
	glm::mat4 GetMvp()const;
	glm::mat4 GetModel()const;
	glm::mat4 GetProjection()const;
	glm::mat4 GetView()const;
	glm::vec3 GetCameraPos()const;

	//::.. SET FUNCTIONS ..:://
	void SetEye(glm::vec3 eye);
	void SetCenter(glm::vec3 center);
	void SetUp(glm::vec3 up);


	void Update();
	void Init();
private:
	//::.. HELPER FUNCTIONS ..:://
private:
	glm::mat4 m_mvp;
	glm::mat4 m_model;
	glm::mat4 m_projection;
	glm::mat4 m_view;
	glm::mat4 m_cameraPos;

	glm::vec3 m_eye;
	glm::vec3 m_center;
	glm::vec3 m_up;
};

#endif // !__CAMERA_H__

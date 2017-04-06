#ifndef __CAMERA_H__
#define __CAMERA_H__


#include <glm.hpp>
#include <gtx\transform.hpp>


class Camera
{
public:
	//::.. CONSTRUCTORS ..:://
	Camera();
	virtual ~Camera();

	//::.. SET FUNCTIONS ..::J//
	void SetPosition(glm::vec3 pos);
	void SetRotation(float x, float y);
	//void SetPosition()

	//::.. GET FUNCTIONS ..:://
	glm::mat4 GetView();
	glm::mat4 GetProjection();
	glm::vec3 GetPosition();


private:
	//::.. HELP FUNCTIONS ..:://
	void Init();

private:
	
	glm::mat4 m_perspective;
	glm::vec3 m_pos;
	glm::vec3 m_front;
	glm::vec3 m_up;
};

#endif // !__CAMERA_H__

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

	//::.. GET FUNCTIONS ..:://
	glm::mat4 GetView();
	glm::mat4 GetProjection();


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

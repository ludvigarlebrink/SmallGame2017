#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__


#include <glm.hpp>
#include <gtx\transform.hpp>


class Transform
{
public:
	//::.. CONSTRUCTORS ..:://
	Transform();							// Default constructor.
	Transform(glm::vec3 pos, 
		glm::vec3 rot, glm::vec3 scale);	// Set constructor.
	Transform(const Transform &object);		// Copy constructor.
	virtual ~Transform();					// Destructor.

	//::.. OPERATOR OVERLOADING ..:://
	void operator=(const Transform &object);

	//::.. MODIFY FUNCTIONS ..:://
	void Move();	// Move the object.
	void Rotate();	// Rotate the object.

	//::.. SET FUNCTIONS ..:://
	void SetPosition(glm::vec3 pos);				// Set position.
	void SetPosition(float x, float y, float z);	// Set position
	void SetRotation(glm::vec3 rot);				// Set rotation.
	void SetRotation(float x, float y, float z);	// Set rotation.
	void SetScale(glm::vec3 scale);					// Set scale.
	void SetScale(float x, float y, float z);		// Set scale.

	//::.. GET FUNCTIONS ..:://
	glm::vec3 GetPosition();		// Returns the position vector.
	glm::vec3 GetRotation();		// Returns the rotation vector.
	glm::vec3 GetScale();			// Returns the scale vector.
	glm::mat4 GetModelMatrix();		// Returns the model matrix.

private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
};


#endif
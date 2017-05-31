#ifndef __AGAMEOBJECT_H__
#define __AGAMEOBJECT_H__


#include "Transform.h"


class AGameObject
{
public:
	//::.. CONSTRUCTORS ..:://
	AGameObject();
	AGameObject(uint32_t instanceID, uint32_t parentID);
	virtual ~AGameObject();

	virtual void Start();
	virtual void Update();

	//::.. SET FUNCTIONS ..:://
	void SetInstanceID(uint32_t id);
	void SetParentID(uint32_t id);
	void SetLocalTransform(Transform transform);
	void SetGlobalTransform(Transform transform);

	//::.. GET FUNCTIONS ..:://
	uint32_t GetInstanceID() const;
	uint32_t GetParentID() const;
	Transform GetLocalTransform() const;
	Transform GetGlobalTransform() const;

private:
	uint32_t	m_instanceID;
	uint32_t	m_parentID;
	Transform	m_localTransform;
	Transform	m_globalTransform;
};


#endif // __AGAMEOBJECT_G__
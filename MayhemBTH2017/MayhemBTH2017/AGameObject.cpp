#include "AGameObject.h"



//::.. CONSTRUCTORS ..:://
AGameObject::AGameObject()
	: m_instanceID(0), m_parentID(0)
{
}

AGameObject::AGameObject(uint32_t instanceID, uint32_t parentID)
	: m_instanceID(instanceID), m_parentID(parentID)
{
}

AGameObject::~AGameObject()
{
}

void AGameObject::Start()
{
}

void AGameObject::Update()
{
}


//::.. SET FUNCTIONS ..:://
void AGameObject::SetInstanceID(uint32_t id)
{
	m_instanceID = id;
}

void AGameObject::SetParentID(uint32_t id)
{
	m_parentID = id;
}

void AGameObject::SetLocalTransform(Transform transform)
{
	m_localTransform = transform;
}

void AGameObject::SetGlobalTransform(Transform transform)
{
	m_globalTransform = transform;
}


//::.. GET FUNCTIONS ..:://
uint32_t AGameObject::GetInstanceID() const
{
	return m_instanceID;
}

uint32_t AGameObject::GetParentID() const
{
	return m_parentID;
}

Transform AGameObject::GetLocalTransform() const
{
	return m_localTransform;
}

Transform AGameObject::GetGlobalTransform() const
{
	return m_globalTransform;
}

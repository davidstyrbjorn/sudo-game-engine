#include "transform_component.h"

namespace sudo { namespace ecs { 

Transform::Transform()
{
	m_componentName = "Transform";

	position = math::Vector3(0, 0, 0);
	scale = math::Vector3(1, 1, 1);
}

void Transform::Start() 
{

}

void Transform::Update() 
{

}


} } 
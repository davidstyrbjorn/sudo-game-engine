#include "transform_component.h"

namespace sudo { namespace ecs { 

Transform::Transform()
{
	position = math::Vector3(0, 0, 0);
	scale = math::Vector3(1, 1, 1);
}

void Transform::Move(const math::Vector3 & a_vector)
{
	position = math::Vector3(position.getX() + a_vector.getX(), position.getY() + a_vector.getY(), position.getZ() + a_vector.getZ());
}

void Transform::Start()
{

}

void Transform::Update() 
{

}


} } 
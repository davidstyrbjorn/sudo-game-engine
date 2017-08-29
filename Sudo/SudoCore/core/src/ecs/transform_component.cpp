#include "transform_component.h"

/* Include the forward decleration */
#include"../math/vector3.h"
#include"../math/vector4.h"

namespace sudo { namespace ecs { 

Transform::Transform()
{
	position = new math::Vector3(0, 0, 0);
	scale = new math::Vector3(1, 1, 1);
}

void Transform::Start() 
{

}

void Transform::Update() 
{

}


} } 
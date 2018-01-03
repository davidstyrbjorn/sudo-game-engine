#include "../include/ecs/four_way_move_component.h"

#include"../include/ecs/entity.h"
#include"../include/ecs/transform_component.h"

#include"../include/math/vector2.h"
#include"../include/math/vector3.h"

#include"../include/systems/input_system.h"

namespace sudo { namespace ecs { 

FourWayMoveComponent::FourWayMoveComponent(math::Vector2 & a_moveSpeed, char* a_up, char* a_down, char* a_right, char* a_left)
{
	m_xSpeed = a_moveSpeed.x;
	m_ySpeed = a_moveSpeed.y;

	m_up = a_up;
	m_down = a_down;
	m_right = a_right;
	m_left = a_left;
}

FourWayMoveComponent::~FourWayMoveComponent()
{
	delete m_transform;
}

void FourWayMoveComponent::Start()
{
	m_transform = m_entityHolder->transform;
	m_inputSystem = sudo_system::InputSystem::Instance();
}

void FourWayMoveComponent::Update(float deltaTime) 
{
	if (m_inputSystem->GetKey(m_up)) 
	{
		// Move up
		m_transform->Move(math::Vector3(0, -m_ySpeed*deltaTime, 0));
	}
	else if (m_inputSystem->GetKey(m_down)) 
	{
		// Move down
		m_transform->Move(math::Vector3(0, m_ySpeed*deltaTime, 0));
	}
	if (m_inputSystem->GetKey(m_right))
	{
		// Move right
		m_transform->Move(math::Vector3(m_xSpeed*deltaTime, 0, 0));
	}
	else if (m_inputSystem->GetKey(m_left))
	{
		// Move left
		m_transform->Move(math::Vector3(-m_xSpeed*deltaTime, 0, 0));
	}
}

void FourWayMoveComponent::SetVelocity(math::Vector2 & a_newVelocity)
{
	m_xSpeed = a_newVelocity.x;
	m_ySpeed = a_newVelocity.y;
}

math::Vector2 FourWayMoveComponent::GetVelocity()
{
	return math::Vector2(m_xSpeed, m_ySpeed);
}

void FourWayMoveComponent::SetKeys(char * a_up, char * a_down, char * a_right, char * a_left)
{
	m_up = a_up;
	m_down = a_down;
	m_left = a_left;
	m_right = a_right;
}

char * FourWayMoveComponent::GetKeys(char * a_keyName)
{
	if (a_keyName == "up") {
		return m_up;
	}
	else if (a_keyName == "down") {
		return m_down;
	}
	else if (a_keyName == "right") {
		return m_right;
	}
	else if (a_keyName == "left") {
		return m_left;
	}
}

} } 
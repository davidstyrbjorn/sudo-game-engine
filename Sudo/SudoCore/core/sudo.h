#pragma once

#include<iostream>
#include<string>

#include"src\math\vector2.h"
#include"src\math\vector3.h"
#include"src\math\vector4.h"
#include"src\math\mat4.h"

#include"src\ecs\transform_component.h"
#include"src\ecs\rectangle_component.h"
#include"src\ecs\triangle_component.h"
#include"src\ecs\box_collider2D.h"
#include"src\ecs\component.h"
#include"src\ecs\entity.h"

#include"src\systems\input_system.h"
#include"src\systems\world_system.h"
#include"src\systems\render_system.h"
#include"src\systems\settings_system.h"

#include"src\graphics\shader.h"
#include"src\graphics\window.h"
#include"src\graphics\renderable2d.h"
#include"src\graphics\buffers\vertex_array_buffer.h"
#include"src\graphics\buffers\buffer_object.h"

#include"src\sudo_core.h"
#include"src\sudo_class.h"

#include"src\utility\utility.h"
#include"src\utility\timer.h"
#include"src\utility\linked_list.h"

#include"src\debug.h"

namespace sudo {

#define SUDO_FINAL_VERSION 0
#define SUDO_MAJOR_VERSION 1
#define SUDO_MINOR_VERSION 0

static std::string GetSudoVersion() {	
	return "[Sudo Game Engine] \nVersion: " + std::to_string(SUDO_FINAL_VERSION) + "." + std::to_string(SUDO_MAJOR_VERSION) + "." + std::to_string(SUDO_MINOR_VERSION); }
}
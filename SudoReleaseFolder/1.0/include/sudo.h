#pragma once

#include<iostream>
#include<string>

#include"math\math.h"
#include"math\vector2.h"
#include"math\vector3.h"
#include"math\vector4.h"
#include"math\mat4.h"
#include"math\color.h"

#include"ecs\transform_component.h"
#include"ecs\rectangle_component.h"
#include"ecs\triangle_component.h"
#include"ecs\sprite_component.h"
#include"ecs\sound_component.h"
#include"ecs\four_way_move_component.h"
#include"ecs\box_collider2D.h"
#include"ecs\component.h"
#include"ecs\entity.h"

#include"systems\input_system.h"
#include"systems\world_system.h"
#include"systems\settings_system.h"
#include"systems\sound_system.h"
#include"systems\batch_render_system.h"
#include"systems\particle_system.h"
#include"systems\text_system.h"

#include"graphics\shader.h"
#include"graphics\window.h"
#include"graphics\renderable2d.h"
#include"graphics\texture.h"
#include"graphics\buffers\vertex_array_buffer.h"
#include"graphics\buffers\vertex_buffer.h"
#include"graphics\buffers\buffer.h"
#include"graphics\buffers\index_buffer.h"

#include"sudo_core.h"
#include"sudo_class.h"

#include"utility\utility.h"
#include"utility\timer.h"
#include"utility\sudo_string.h"
#include"utility\sudo_random.h"

#include"sound\sound_buffer.h"
#include"sound\sound_source.h"

#include"debug.h"

namespace sudo {

#define SUDO_FINAL_VERSION 1
#define SUDO_MAJOR_VERSION 0
#define SUDO_MINOR_VERSION 0

static std::string GetSudoVersion() {	
	return "[Sudo Game Engine] \nVersion: " + std::to_string(SUDO_FINAL_VERSION) + "." + std::to_string(SUDO_MAJOR_VERSION) + "." + std::to_string(SUDO_MINOR_VERSION) + "!"; }
}
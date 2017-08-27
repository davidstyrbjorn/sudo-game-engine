#pragma once

#include<iostream>
#include<string>

#include"src\math\vector2.h"
#include"src\math\vector3.h"
#include"src\math\vector4.h"
#include"src\math\mat4.h"

#include"src\ecs\component.h"
#include"src\ecs\entity.h"

#include"src\systems\input_system.h"
#include"src\systems\world_system.h"

#include"src\graphics\shader.h"
#include"src\graphics\window.h"

#include"src\core_engine.h"
#include"src\sudo_class.h"

#include"src\utility\utility.h"
#include"src\utility\timer.h"
#include"src\utility\linked_list.h"

#include"src\debug.h"

namespace sudo {

#define SUDO_FINAL_VERSION 0
#define SUDO_MAJOR_VERSION 0
#define SUDO_MINOR_VERSION 1

static std::string GetSudoVersion() {	return "[Sudo Game Engine] \nVersion: " + std::to_string(SUDO_FINAL_VERSION) + "." + std::to_string(SUDO_MAJOR_VERSION) + "." + std::to_string(SUDO_MINOR_VERSION); }

}
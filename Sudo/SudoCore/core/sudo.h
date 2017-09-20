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
#include"src\ecs\sprite_component.h"

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
#include"src\graphics\buffers\vertex_buffer.h"
#include"src\graphics\buffers\buffer.h"

#include"src\sudo_core.h"
#include"src\sudo_class.h"

#include"src\utility\utility.h"
#include"src\utility\timer.h"
#include"src\utility\linked_list.h"

#include"src\debug.h"

namespace sudo {

#define SUDO_FINAL_VERSION 0
#define SUDO_MAJOR_VERSION 1
#define SUDO_MINOR_VERSION 5

static std::string GetSudoVersion() {	
	return "[Sudo Game Engine] \nVersion: " + std::to_string(SUDO_FINAL_VERSION) + "." + std::to_string(SUDO_MAJOR_VERSION) + "." + std::to_string(SUDO_MINOR_VERSION); }
}

// Texture test
/*
glEnable(GL_BLEND);
glBlendFunc(GL_BLEND, GL_ONE_MINUS_SRC_ALPHA);

int width, height;
glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

unsigned char *image = SOIL_load_image("D://sample.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
glGenerateMipmap(GL_TEXTURE_2D);
SOIL_free_image_data(image);
glBindTexture(GL_TEXTURE_2D, 0);
*/
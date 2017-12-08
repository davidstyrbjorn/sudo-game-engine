#pragma once

namespace sudo {

/* ===================================================== */
/* ===================================================== */

typedef unsigned int uint;

/* ===================================================== */
/* ===================================================== */

enum SudoBufferType {
	VERTEX_ONLY,
	VERTEX_COLOR,
	VERTEX_COLOR_TEXTURE
};

/* ===================================================== */
/* ===================================================== */

// System macros
#define SYSTEM_API

// Graphics macros
#define GRAPHICS_API
#define MAX_PIXEL_SIZE_X 6000
#define MIN_PIXEL_SIZE_X 0
#define MAX_PIXEL_SIZE_Y 6000
#define MIN_PIXEL_SIZE_Y 0

// Window macros
#define WINDOW_API 

// Time macros
#define TIME_API
#define DEFAULT_FPS_CAP 60
#define FIXED_UPDATE_MS 1000 / DEFAULT_FPS_CAP

// Particle macros
#define PARTICLE_GRAVITY_Y 0.001f

}
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

enum SudoBufferDataType {
	VERTEX,
	COLOR
};

enum RenderableType {
	SHAPE,
	SPRITE
};

/* ===================================================== */
/* ===================================================== */

#define MAX_PIXEL_SIZE_X 6000
#define MIN_PIXEL_SIZE_X 0
#define MAX_PIXEL_SIZE_Y 6000
#define MIN_PIXEL_SIZE_Y 0

}
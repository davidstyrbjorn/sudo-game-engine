#pragma once

namespace sudo {

typedef unsigned int uint;

enum SudoBufferType {
	VERTEX_ONLY,
	VERTEX_COLOR,
	VERTEX_COLOR_TEXTURE
};

enum SudoBufferDataType {
	VERTEX,
	COLOR
};

}
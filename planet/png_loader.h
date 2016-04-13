#pragma once

#include "common.h"
#include "opengl_common.h"
#include <lodepng.h>

namespace planet {

	struct PNGImage {
		u32 width;
		u32 height;
		vector<u8> pixels;
	};

	class PNGLoader {
	public:
		static PNGImage* load(string const& file);
	};
}
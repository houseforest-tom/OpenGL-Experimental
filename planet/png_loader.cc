#include "png_loader.h"

namespace planet {
	PNGImage* PNGLoader::load(string const& file) {

		PNGImage* image = new PNGImage();
		lodepng::State state;
		vector<u8> fileBuffer;
		lodepng::load_file(fileBuffer, file);
		lodepng::decode(image->pixels, image->width, image->height, state, fileBuffer);
		logMessage("Loaded pixel data from " + file
				   + " (Width: " + to_string(image->width)
				   + ", Height: " + to_string(image->height)
				   + ")");

		return image;
	}
}
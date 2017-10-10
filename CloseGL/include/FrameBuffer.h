#pragma once
#include <memory>
#include "Surface.h"
#include "PixelFormats.h"

namespace CloseGL::PixelPipeline
{
	struct FrameBuffer
	{
		std::vector<Surface<PixelFormats::ColorRGBA<float>>*> ColorBuffers;
		std::unique_ptr<Surface<PixelFormats::ColorR<float>>> DepthBuffer;
	};
}
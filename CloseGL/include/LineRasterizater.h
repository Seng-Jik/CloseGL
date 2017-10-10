#pragma once
#include <memory>
#include "PixelPipeline.h"

namespace CloseGL::PixelPipeline
{
	std::shared_ptr<PixelPipeline> CreateLineRasterizater();
}

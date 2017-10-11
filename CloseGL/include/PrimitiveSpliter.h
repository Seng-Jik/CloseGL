#pragma once
#include <vector>
#include "GeometryPipeline.h"

namespace CloseGL::Utils
{
	struct PrimitiveFromVerticleData
	{
		const float* Data = nullptr;
		size_t StripSize = 0;
	};

	std::vector<PrimitiveFromVerticleData> SplitPrimitive(const CloseGL::Geometry::GeometryPipelineOutput & input);
}
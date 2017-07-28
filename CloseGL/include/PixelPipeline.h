#pragma once
#include <functional>
#include "Surface.h"
#include "GeometryPipeline.h"
#include "FrameBuffer.h"

namespace CloseGL::PixelPipeline
{
	class PixelPipeline
	{
	public:
		struct Status
		{
			std::function<PixelFormats::ColorRGBA<float>(const float*, const Geometry::GeometryDataFormat&)> PixelShader;
			std::function<void(PixelFormats::ColorRGBA<float> src, PixelFormats::ColorRGBA<float>& dst)> Blender = [](auto src,auto& dst) { dst = src; };

			bool DepthTest = false;
			int ChildThreads = 0;
		};

		virtual void Draw(const Geometry::GeometryPipelineOutput& input,FrameBuffer& renderTarget, const Status& status) = 0;
	};
}
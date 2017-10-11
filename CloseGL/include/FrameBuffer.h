#pragma once
#include <memory>
#include "Surface.h"
#include "PixelFormats.h"
#include "Vectors.h"

namespace CloseGL::PixelPipeline
{
	struct FrameBuffer
	{
		std::vector<Surface<PixelFormats::ColorRGBA<float>>*> ColorBuffers;
		std::unique_ptr<Surface<PixelFormats::ColorR<float>>> DepthBuffer;

		inline CloseGL::Math::Vector2<int> GetMaxColorBufferSize() const;
	};
}


inline CloseGL::Math::Vector2<int> CloseGL::PixelPipeline::FrameBuffer::GetMaxColorBufferSize() const
{
	CloseGL::Math::Vector2<int> maxSize = { 0,0 };
	for (const auto& cbuffer : ColorBuffers)
	{
		auto size= cbuffer->GetSize();
		maxSize.x = std::max(size.x, maxSize.x);
		maxSize.y = std::max(size.y, maxSize.y);
	}

	return maxSize;
}
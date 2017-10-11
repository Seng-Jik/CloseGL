#pragma once
#include <PixelArray.h>
#include "Vectors.h"

namespace CloseGL
{
	template<typename TPixel>
	class Surface : public PixelArray<TPixel>
	{
	public:
		Surface(int width, int height);

		TPixel& GetPixel(int x, int y);                     
		Math::Vector2<int> GetSize() const;
	private:
		const Math::Vector2<int> size_;
	};

	template<typename TPixel>
	inline Surface<TPixel>::Surface(int width, int height) :
		size_{ width,height },
		PixelArray<TPixel>(width * height)
	{}

	template<typename TPixel>
	inline TPixel & Surface<TPixel>::GetPixel(int x, int y)
	{
		return (*this)[y * size_.x + x];
	}

	template<typename TPixel>
	inline Math::Vector2<int> Surface<TPixel>::GetSize() const
	{
		return size_;
	}
}
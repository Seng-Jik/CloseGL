#pragma once
#include <vector>
#include <algorithm>

namespace CloseGL
{
	template<typename TPixel>
	class PixelArray
	{
	public:
		PixelArray(size_t pixelCount);
		virtual ~PixelArray() {};

		virtual void Clear(TPixel clearColor);

		TPixel& operator[](size_t n);

	private:
		std::vector<TPixel> pixels_;
	};

	template<typename TPixel>
	inline PixelArray<TPixel>::PixelArray(size_t pixelCount)
	{
		pixels_.resize(pixelCount);
	}

	template<typename TPixel>
	inline void PixelArray<TPixel>::Clear(TPixel clearColor)
	{
		std::fill(pixels_.begin(), pixels_.end(), clearColor);
	}

	template<typename TPixel>
	inline TPixel & PixelArray<TPixel>::operator[](size_t n)
	{
		return pixels_[n];
	}
}
#pragma once
#include <PixelArray.h>

namespace CloseGL
{
	template<typename TPixel>
	class Surface : PixelArray<TPixel>
	{
	public:
		Surface(int width, int height);

		TPixel& GetPixel(int x, int y);
		int GetWidth();
		int GetHeight();                          

	private:
		const int width_, height_;
	};

	template<typename TPixel>
	inline Surface<TPixel>::Surface(int width, int height) :
		width_(width),
		height_(height),
		PixelArray(width*height)
	{}

	template<typename TPixel>
	inline TPixel & Surface<TPixel>::GetPixel(int x, int y)
	{
		return *this[y * width + x];
	}

	template<typename TPixel>
	inline int Surface<TPixel>::GetWidth()
	{
		return width_;
	}

	template<typename TPixel>
	inline int Surface<TPixel>::GetHeight()
	{
		return height_;
	}
}
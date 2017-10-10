#pragma once
#include <tuple>
#include <PixelArray.h>

namespace CloseGL
{
	template<typename TPixel>
	class Surface : public PixelArray<TPixel>
	{
	public:
		Surface(int width, int height);

		TPixel& GetPixel(int x, int y);
		int GetWidth();
		int GetHeight();                          
		std::tuple<int, int> GetSize();
	private:
		const std::tuple<int, int> size_;
	};

	template<typename TPixel>
	inline Surface<TPixel>::Surface(int width, int height) :
		size_(width,height),
		PixelArray<TPixel>(get<0>(size_)*get<1>(size_))
	{}

	template<typename TPixel>
	inline TPixel & Surface<TPixel>::GetPixel(int x, int y)
	{
		return (*this)[y * get<0>(size_) + x];
	}

	template<typename TPixel>
	inline int Surface<TPixel>::GetWidth()
	{
		return get<0>(size_);
	}

	template<typename TPixel>
	inline int Surface<TPixel>::GetHeight()
	{
		return get<1>(size_);
	}
	template<typename TPixel>
	inline std::tuple<int, int> Surface<TPixel>::GetSize()
	{
		return size_;
	}
}
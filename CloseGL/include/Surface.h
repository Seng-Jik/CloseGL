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
		int GetWidth() const;
		int GetHeight() const;                          
		std::tuple<int, int> GetSize() const;
	private:
		const std::tuple<int, int> size_;
	};

	template<typename TPixel>
	inline Surface<TPixel>::Surface(int width, int height) :
		size_(width,height),
		PixelArray<TPixel>(width * height)
	{}

	template<typename TPixel>
	inline TPixel & Surface<TPixel>::GetPixel(int x, int y)
	{
		return (*this)[y * std::get<0>(size_) + x];
	}

	template<typename TPixel>
	inline int Surface<TPixel>::GetWidth() const
	{
		return std::get<0>(size_);
	}

	template<typename TPixel>
	inline int Surface<TPixel>::GetHeight() const
	{
		return std::get<1>(size_);
	}
	template<typename TPixel>
	inline std::tuple<int, int> Surface<TPixel>::GetSize() const
	{
		return size_;
	}
}
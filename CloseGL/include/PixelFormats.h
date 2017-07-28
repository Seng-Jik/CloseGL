#pragma once
#include <cstdint>

namespace CloseGL::PixelFormats
{
	template<typename TBaseType>
	struct ColorRGBA
	{
		TBaseType r, g, b, a;
	};

	template<typename TBaseType>
	struct ColorR
	{
		TBaseType r;
	};
}

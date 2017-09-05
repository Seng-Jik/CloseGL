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
	struct ColorBGRA
	{
		TBaseType b, g, r, a;
	};

	template<typename TBaseType>
	struct ColorARGB
	{
		TBaseType a, r, g, b;
	};

	template<typename TBaseType>
	struct ColorABGR
	{
		TBaseType a, b, g, r;
	};

	template<typename TBaseType>
	struct ColorR
	{
		TBaseType r;
	};
}

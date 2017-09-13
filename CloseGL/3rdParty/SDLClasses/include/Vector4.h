#pragma once

namespace SDL
{
	template<typename T>
	struct Vector4
	{
		T x, y, z, w;
	};

	template<typename T>
	struct Rect
	{
		T x, y, w, h;
	};

	template<typename T>
	struct Color
	{
		T r, g, b, a;
	};
}

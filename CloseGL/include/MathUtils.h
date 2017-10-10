#pragma once

namespace CloseGL
{
	namespace Math
	{
		template<typename T>
		T Abs(T a)
		{
			return a < 0 ? -a : a;
		}

		template<typename T,typename U>	//U = float/double
		T Lerp(T a, T b, U lerp)
		{
			return (a - b) * lerp + b;
		}
	}
}
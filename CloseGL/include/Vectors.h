#pragma once

namespace CloseGL
{
	namespace Math
	{
		template<typename T>
		struct Vector2
		{
			T x, y;

			Vector2<T> operator + (const Vector2<T>& t)
			{
				return Vector2<T>{x + t.x, y + t.y};
			}

			Vector2<T> operator - (const Vector2<T>& t)
			{
				return Vector2<T>{x - t.x, y - t.y};
			}

			template<typename U>
			Vector2<T> operator * (U t)
			{
				return Vector2<T>{x * t, y * t};
			}
		};
	}
}
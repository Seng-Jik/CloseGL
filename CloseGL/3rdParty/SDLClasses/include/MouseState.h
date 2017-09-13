#pragma once
#include <cstdint>
#include "Vector2.h"

namespace SDL
{
	struct MouseState final
	{
		Vector2<int32_t> position;
		bool leftButton, rightButton, middleButton;
	};
}
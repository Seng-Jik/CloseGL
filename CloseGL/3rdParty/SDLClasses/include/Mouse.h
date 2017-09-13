#pragma once
#include "MouseState.h"
//#include "Haptic.h"

namespace SDL
{
	class Mouse final
	{
	public:
		MouseState GetMouseState() const;
		void SetMouseCursorShow(bool);

		//Haptic OpenHaptic();
	};
}
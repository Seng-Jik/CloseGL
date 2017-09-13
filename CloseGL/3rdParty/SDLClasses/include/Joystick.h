#pragma once
/*#include <string>
#include "Handler.h"
#include "Vector2.h"
//#include "Haptic.h"

// Comming soon
namespace SDL
{
	using namespace std;
	class Joystick final
	{
	public:

		enum class PowerLevel
		{
			Unknown,
			Empty,
			Low,
			Medium,
			Full,
			Wired,
			Max
		};

		static int GetJoystickDeviceCount();

		Joystick(int deviceIndex);
		~Joystick();

		PowerLevel GetPowerLevel();
		bool GetAttached();
		int16_t GetAxis(int axisIndex);
		Vector2<int> GetBall(int ballIndex);
		bool GetButton(int buttonIndex);

		Vector2<bool> GetHat(int hatIndex);

		int NumAxes();
		int NumBalls();
		int NumButtons();
		int NumHats();
		int NumJoysticks();

		string GetName();

		Haptic OpenHaptic();
	private:
		Handler joystickHandler_;
	};
}*/
#pragma once
#include <string>

namespace SDL
{
	using std::string;

	class Keyboard final
	{
	public:
		const uint8_t* GetKeyboardState(int& keyCount) const;
		uint32_t GetKeyboardScancode(const string& keyName) const;
		bool KeyPressed(uint32_t scanCode) const;
		bool KeyPressed(const string& keyName) const;
	};
}
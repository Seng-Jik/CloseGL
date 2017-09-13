#pragma once
#include <functional>

namespace SDL
{
	class Guard final
	{
	public:
		inline Guard(std::function<void()> unlock)
			:
			unlock_(unlock)
		{}

		inline ~Guard()
		{
			unlock_();
		}

	private:
		std::function<void()> unlock_;
	};
}
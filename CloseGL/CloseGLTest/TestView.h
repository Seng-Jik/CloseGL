#pragma once
#include <Window.h>
#include <SDLInstance.h>
#include <Surface.h>

namespace CloseGLTest::Toolkit
{
	class TestView
	{
	public:
		TestView(uint64_t timeout = 5000,int width = 1024,int height = 768);
		void Run();
	private:
		SDL::SDLInstance sdl_;
		SDL::Window wnd_;
		uint64_t timeout_;
	};
}
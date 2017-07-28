#pragma once
#include <functional>
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

		void SetUpdateFunction(std::function<void(float time,CloseGL::Surface<CloseGL::PixelFormats::ColorRGBA<float>>&)> update);
	private:
		SDL::SDLInstance sdl_;
		SDL::Window wnd_;
		CloseGL::Surface<CloseGL::PixelFormats::ColorRGBA<float>> sur_;
		uint64_t timeout_;
		std::function<void(float time, CloseGL::Surface<CloseGL::PixelFormats::ColorRGBA<float>>&)> update_;
	};
}
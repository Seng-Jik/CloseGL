#include "stdafx.h"
#include <Vector4.h>

using namespace SDL;
CloseGLTest::Toolkit::TestView::TestView(uint64_t timeout,int width, int height):
	wnd_("CloseGL Demo",Rect<int32_t>{Window::Center,Window::Center,width,height},Window::WindowFlag::Null),
	sur_(width,height),
	timeout_(timeout)
{
	
}

void CloseGLTest::Toolkit::TestView::Run()
{
	SDL_Surface* wndSurface = wnd_.GetWindowSurface().GetPtrToSDL_Surface();
	uint8_t* px = static_cast<uint8_t*>(wndSurface->pixels);

	const auto beginTime = sdl_.GetTicks();
	uint64_t timer = 0;
	int frames = 0;
	std::vector<uint64_t> frameTimes;
	while (timeout_ > sdl_.GetTicks() - beginTime)
	{
		sdl_.ProcessEvents();

		if (sdl_.QuitRequested()) break;
		
		const uint64_t frameBegin = sdl_.GetTicks();
		update_((sdl_.GetTicks() - beginTime) / 1000.0f, sur_);
		frameTimes.push_back(sdl_.GetTicks() - frameBegin);
		frames++;

		if (sdl_.GetTicks() - timer > 1000)
		{
			timer = sdl_.GetTicks();

			uint64_t avg = 0;
			for (auto i : frameTimes) avg += i;
			avg /= frameTimes.size();
			frameTimes.clear();

			wnd_.SetWindowTitle(string("CloseGL Demo     Draw Time:") + std::to_string(avg)+"     FPS:" + std::to_string(frames));
			frames = 0;
		}

		for (int y = 0; y < wndSurface->h; ++y) 
		{
			for (int x = 0; x < wndSurface->w; ++x)
			{
				const auto& p = sur_.GetPixel(x, y);
				px[y*wndSurface->pitch + x * 4 + 2] = static_cast<uint8_t>(255 * p.r);
				px[y*wndSurface->pitch + x * 4 + 1] = static_cast<uint8_t>(255 * p.g);
				px[y*wndSurface->pitch + x * 4] = static_cast<uint8_t>(255 * p.b);
				px[y*wndSurface->pitch + x * 4 + 3] = static_cast<uint8_t>(255 * p.a);
				
			}
		}

		wnd_.UpdateWindowSurface();
	}
}

void CloseGLTest::Toolkit::TestView::SetUpdateFunction(std::function<void(float time, CloseGL::Surface<CloseGL::PixelFormats::ColorRGBA<float>>&)> update)
{
	update_ = update;
}

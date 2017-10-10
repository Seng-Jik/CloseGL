#include "stdafx.h"
#include "TestView.h"
#include <Vector4.h>
#include <SDLInstance.h>

using namespace SDL;
CloseGLTest::Toolkit::TestView::TestView(uint64_t timeout,int width, int height):
	wnd_("CloseGL Demo",Rect<int32_t>{Window::Center,Window::Center,width,height},Window::WindowFlag::Null),
	sur_(width,height),
	timeout_(timeout)
{
	
}

void CloseGLTest::Toolkit::TestView::Run()
{
	const auto beginTime = sdl_.GetTicks();
	while (timeout_ > sdl_.GetTicks() - beginTime)
	{
		sdl_.ProcessEvents();

		if (sdl_.QuitRequested()) break;
		
		update_((sdl_.GetTicks() - beginTime) / 1000.0f, sur_);

		wnd_.GetWindowSurface().Shade([this](int x, int y, Surface& thisSurface, auto nowColor)
		{
			const auto& p = sur_.GetPixel(x, y);
			return Color<uint8_t>{
				static_cast<uint8_t>(255 * p.r),
				static_cast<uint8_t>(255 * p.g),
				static_cast<uint8_t>(255 * p.b),
				static_cast<uint8_t>(255 * p.a)
			};
		});
		wnd_.UpdateWindowSurface();
	}
}

void CloseGLTest::Toolkit::TestView::SetUpdateFunction(std::function<void(float time, CloseGL::Surface<CloseGL::PixelFormats::ColorRGBA<float>>&)> update)
{
	update_ = update;
}

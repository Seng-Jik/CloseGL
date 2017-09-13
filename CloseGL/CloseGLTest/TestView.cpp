#include "stdafx.h"
#include "TestView.h"
#include <Vector4.h>
#include <SDLInstance.h>

using namespace SDL;
CloseGLTest::Toolkit::TestView::TestView(uint64_t timeout,int width, int height):
	wnd_("CloseGL Demo",Rect<int32_t>{Window::Center,Window::Center,width,height},Window::WindowFlag::Null),
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

		auto& sur = wnd_.GetWindowSurface();
		sur.Shade([](int x, int y, Surface& thisSurface, auto nowColor)
		{
			return Color<uint8_t>{
				static_cast<uint8_t>(255 * sin(x / 255.0)),
				static_cast<uint8_t>(255 * cos(y / 255.0)),
				static_cast<uint8_t>(255 * sin(x / 255.0) * cos(y / 255.0)),
				1
			};
		});
		wnd_.UpdateWindowSurface();
	}
}

#pragma once
#include <string>
#include "Surface.h"

namespace SDL
{
	using std::string;

	template<typename T> struct Vector4;
	class GLContext;

	class Window final
	{
	public:

		enum class WindowFlag : uint32_t
		{
			Null = 0,
			FullScreen = 0x00000001,
			FullScreenDesktop = FullScreen | 0x00001000,
			OpenGL = 0x00000002
		};

		static const int32_t Center = -1;

		Window(const string& title, Rect<int32_t> rectangle, WindowFlag);

		void UpdateWindowSurface() const;
		inline Surface& GetWindowSurface() { return windowSurface_; }
		Handler GetHWND();

		void ShowSimpleMessageBox(const string& title, const string& msg) const;

		void SetWindowIcon(const Surface& icon);

		GLContext CreateOpenGLContext();
	private:
		Handler windowHandler_;
		Surface windowSurface_;
	};
}

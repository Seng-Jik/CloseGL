#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace CloseGL;
using namespace CloseGLTest::Toolkit;

namespace CloseGLTest
{
	TEST_CLASS(TestViewTest)
	{
	public:

		TEST_METHOD(TestTestView)
		{
			TestView tv(1000);
			
			tv.SetUpdateFunction([](float time, CloseGL::Surface<CloseGL::PixelFormats::ColorRGBA<float>>& sur) {
				sur.Clear(CloseGL::PixelFormats::ColorRGBA<float>{0, 1, 1, 1});
			});
			tv.Run();
		}

	};
}
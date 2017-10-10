#include "stdafx.h"
#include "TestView.h"

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
			TestView tv;
			
			tv.SetUpdateFunction([](float time, CloseGL::Surface<CloseGL::PixelFormats::ColorRGBA<float>>& sur) {
				sur.Clear(CloseGL::PixelFormats::ColorRGBA<float>{0, 1, 1, 1});
			});
			tv.Run();
		}

	};
}
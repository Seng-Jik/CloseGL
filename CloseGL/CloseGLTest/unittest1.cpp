#include "stdafx.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace CloseGL;

namespace CloseGLTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestTemplate)
		{
			Surface<PixelFormats::ColorRGBA<float>> surface(1024,768);
		}

	};
}
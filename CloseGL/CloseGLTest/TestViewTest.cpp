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
			TestView().Run();
		}

	};
}

#include "stdafx.h"
#include "CloseLogoCamera.h"
#include <ClassicLogo.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace CloseGL::Geometry;

namespace CloseGLTest
{
	TEST_CLASS(CloseLogoTest)
	{
	public:

		TEST_METHOD(BasicOperation)
		{
			CloseGLTest::Toolkit::CloseLogoCamera camera;
			auto& world = camera.GetWorld();
			
			CloseGL::Logo::ClassicLogo<> logo(world);

			logo.Rotate(-45);
			logo.Move();
			logo.Rotate(180);
			logo.Forward();
			logo.Rotate(-180);

			logo.Rotate(-30);
			logo.Move();

			camera.Run();
		}

	};
}
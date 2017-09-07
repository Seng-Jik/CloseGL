
#include "stdafx.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace CloseGL::Geometry;

namespace CloseGLTest
{
	TEST_CLASS(GeometryPipelineTest)
	{
	public:

		TEST_METHOD(TestPipeline)
		{
			GeometryDataFormat format;
			format.ElementCount = 4;
			format.UsedElementCount = 2;
			format.PositionElementOffset = 0;
			format.PositionElementCount = 2;

			GeometryPipeline<float> pipe(format,3);

			std::vector<float> vert =
			{
				0,0,0,0,
				0,0,0,0,
				0,0,0,0,
				0,0,0,0,
				0,0,0,0,
				0,0,0,0,
				0,0,0,0,
				0,0,0,0,
				0,0,0,0,
				0,0,0,0,
				0,0,0,0,
				0,0,0,0
			};
			pipe.SetChildThreads(1);
			pipe.Process(vert);

			
		}

	};
}
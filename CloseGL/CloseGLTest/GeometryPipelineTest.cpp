
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

			GeometryPipeline<float,3> pipe(format);

			const size_t PRI_COUNT = 4000000;
			std::vector<float> vert(format.ElementCount * 3 * PRI_COUNT);

			for (size_t i = 0; i < PRI_COUNT; ++i) {
				for (unsigned j = 0; j < format.ElementCount * 3; ++j)
					vert.at(i*format.ElementCount * 3 + j) = static_cast<float>(i);
			}

			pipe.SetChildThreads(0);
			pipe.Process(vert,false);

			
		}

	};
}
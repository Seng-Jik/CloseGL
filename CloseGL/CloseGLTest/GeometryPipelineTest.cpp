
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

			GeometryPipeline<3> pipe(format);

			//创建三角形Strip信息
			const auto pStriper = std::make_shared<const PrimitiveStriper<3>>();
			pipe.AddPass(pStriper);

			//顶点着色器
			const auto pVertexShader = std::make_shared<const VertexShader<3>>(
			[](float* attributes, const GeometryDataFormat&) {
				attributes[0] = 0;
			}
			);
			pipe.AddPass(pVertexShader);

			const size_t PRI_COUNT = 200;
			std::vector<float> vert(format.ElementCount * 3 * PRI_COUNT);

			for (size_t i = 0; i < PRI_COUNT; ++i) {
				for (unsigned j = 0; j < format.ElementCount * 3; ++j)
					vert.at(i*format.ElementCount * 3 + j) = static_cast<float>(i);
			}

			std::stringstream log;

			pipe.SetChildThreads(1);
			auto pResult = pipe.Process(vert,false);

			
			for (auto& out : pResult.outputs) {
				log << std::endl << "===========" << std::endl;
				log << "OutPtr:" << &out << std::endl;
				log << std::endl << "Verticle:" << std::endl;
				for (auto p : out.VertexData)
					log << p << " ";
				log << std::endl << "Strip:" << std::endl;
				for (auto p : out.StripData)
					log << p << " ";
			}


			Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(log.str().c_str());
		}

	};
}
#include "PrimitiveSpliter.h"

using namespace std;
using namespace CloseGL::Utils;

std::vector<PrimitiveFromVerticleData> CloseGL::Utils::SplitPrimitive(const CloseGL::Geometry::GeometryPipelineOutput & input)
{
	vector<PrimitiveFromVerticleData> tasks;

	PrimitiveFromVerticleData task;
	for (const auto& inputVec : input.Outputs)
	{
		const size_t vertexCount = inputVec.VertexData.size() / input.Format.ElementCount;

		for (int i = 0; i < vertexCount; ++i)
		{
			const bool stripFlag = inputVec.StripData[i];
			if (stripFlag)
			{
				task.StripSize++;
			}
			else
			{
				if (task.Data) tasks.push_back(task);
				task.Data = &inputVec.VertexData[i * input.Format.ElementCount];
				task.StripSize = 1;
			}
		}

		tasks.push_back(task);
	}

	return tasks;
}

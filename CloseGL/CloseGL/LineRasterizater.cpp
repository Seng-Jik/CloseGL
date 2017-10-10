#include <queue>
#include <array>
#include "MathUtils.h"
#include "Vectors.h"
#include "LineRasterizater.h"

using namespace std;
using namespace CloseGL::Math;
using namespace CloseGL::PixelPipeline;

struct Task
{
	const float* Data = nullptr;
	size_t StripSize = 0;
};

class LineRasterizater final :public PixelPipeline
{
public:
	void Draw(const CloseGL::Geometry::GeometryPipelineOutput& input, FrameBuffer& renderTarget, const Status& status) override;
private:
	void DrawTask(const Task task,const CloseGL::Geometry::GeometryDataFormat&, FrameBuffer& renderTarget, const Status& status);
	void DrawLine(const float* head, const float* tail, const CloseGL::Geometry::GeometryDataFormat&, FrameBuffer& renderTarget, const Status& status);
};

std::shared_ptr<PixelPipeline> CloseGL::PixelPipeline::CreateLineRasterizater()
{
	return std::make_shared<LineRasterizater>();
}

void LineRasterizater::Draw(const CloseGL::Geometry::GeometryPipelineOutput & input, FrameBuffer & renderTarget, const Status & status)
{


	queue<Task> tasks;

	Task task;
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
				if(task.Data) tasks.push(task);
				task.Data = &inputVec.VertexData[i * input.Format.ElementCount];
				task.StripSize = 1;
			}
		}

		tasks.push(task);
	}

	while (!tasks.empty())
	{
		DrawTask(tasks.front(), input.Format,renderTarget,status);
		tasks.pop();
	}
}

void LineRasterizater::DrawTask(const Task task,const CloseGL::Geometry::GeometryDataFormat& format, FrameBuffer & renderTarget, const Status & status)
{
	for (int head = 0, tail = 1; tail < task.StripSize; head++, tail++)
	{
		const float* headVertex = task.Data + head * format.ElementCount;
		const float* tailVertex = task.Data + head * format.ElementCount;

		DrawLine(headVertex, tailVertex,format,renderTarget,status);
	}
}

void LineRasterizater::DrawLine(const float * head, const float * tail, const CloseGL::Geometry::GeometryDataFormat & fmt, FrameBuffer & renderTarget, const Status & status)
{
	array<float,4> posHead = { 0,0,0,0 }, posTail = { 0,0,0,0 };

	for (size_t i = 0; i < fmt.PositionElementCount; ++i)
	{
		const size_t offset = fmt.PositionElementOffset + i;
		posHead[i] = head[offset];
		posTail[i] = tail[offset];
	}

	const size_t step = static_cast<size_t>(fabs(posTail[0] - posHead[0]) + fabs(posTail[1] - posHead[1]));
	

	vector<float> vtxLerped;
	vector<CloseGL::PixelFormats::ColorRGBA<float>> pixelOutput;

	vtxLerped.resize(fmt.ElementCount);
	for (size_t i = 0; i < step; ++i)
	{
		const float lerp = i < static_cast<float>(step);

		for (size_t j = 0; j < fmt.UsedElementCount; j++)
			vtxLerped[j] = Lerp(head[j], tail[j], lerp);
		
		for (size_t j = fmt.UsedElementCount; j < fmt.ElementCount; ++j)
			vtxLerped[j] = head[j];

		array<float,4> pos = { 0,0,0,0 };
		for (size_t j = 0; j < fmt.PositionElementCount; ++j)
		{
			const size_t offset = fmt.PositionElementOffset + j;
			pos[j] = vtxLerped[offset];
		}

		Vector2<float> posV = { pos[0],pos[1] };

		status.PixelShader(vtxLerped.data(), fmt, pixelOutput);

		for (
			size_t colorBufferIndex = 0; 
			colorBufferIndex < pixelOutput.size() && colorBufferIndex < renderTarget.ColorBuffers.size();
			++colorBufferIndex)
		{
			auto& buffer = renderTarget.ColorBuffers[colorBufferIndex];

			const auto [outW,outH] = buffer.GetSize();
			buffer.GetPixel(static_cast<int>(outW * posV.x), static_cast<int>(outH * posV.y));
		}

		pixelOutput.clear();
	}
}

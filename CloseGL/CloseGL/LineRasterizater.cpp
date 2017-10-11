#include <queue>
#include <array>
#include "MathUtils.h"
#include "Vectors.h"
#include "LineRasterizater.h"
#include "PrimitiveSpliter.h"

using namespace std;
using namespace CloseGL::Math;
using namespace CloseGL::PixelPipeline;

class LineRasterizater final :public PixelPipeline
{
public:
	void Draw(const CloseGL::Geometry::GeometryPipelineOutput& input, FrameBuffer& renderTarget, const Status& status) const override;
private:
	void DrawTask(Vector2<int> bufferSize,const CloseGL::Utils::PrimitiveFromVerticleData& task,const CloseGL::Geometry::GeometryDataFormat&, FrameBuffer& renderTarget, const Status& status) const;
	void DrawLine(Vector2<int> bufferSize,const float* head, const float* tail, const CloseGL::Geometry::GeometryDataFormat&, FrameBuffer& renderTarget, const Status& status) const;
};

std::shared_ptr<PixelPipeline> CloseGL::PixelPipeline::CreateLineRasterizater()
{
	return std::make_shared<LineRasterizater>();
}

void LineRasterizater::Draw(const CloseGL::Geometry::GeometryPipelineOutput & input, FrameBuffer & renderTarget, const Status & status) const
{
	const auto tasks = CloseGL::Utils::SplitPrimitive(input);

	for (const auto& task : tasks)
		DrawTask(renderTarget.GetMaxColorBufferSize(), task, input.Format, renderTarget, status);
}

void LineRasterizater::DrawTask(Vector2<int> bufferSize, const CloseGL::Utils::PrimitiveFromVerticleData& task,const CloseGL::Geometry::GeometryDataFormat& format, FrameBuffer & renderTarget, const Status & status) const
{
	for (int head = 0, tail = 1; tail < task.StripSize; head++, tail++)
	{
		const float* headVertex = task.Data + head * format.ElementCount;
		const float* tailVertex = task.Data + tail * format.ElementCount;

		DrawLine(bufferSize,headVertex, tailVertex,format,renderTarget,status);
	}
}

void LineRasterizater::DrawLine(Vector2<int> bufferSize,const float * head, const float * tail, const CloseGL::Geometry::GeometryDataFormat & fmt, FrameBuffer & renderTarget, const Status & status) const
{
	array<float,4> posHead = { 0,0,0,0 }, posTail = { 0,0,0,0 };

	for (size_t i = 0; i < fmt.PositionElementCount; ++i)
	{
		const size_t offset = fmt.PositionElementOffset + i;
		posHead[i] = head[offset];
		posTail[i] = tail[offset];
	}

	const size_t step = static_cast<size_t>(fabs(posTail[0] - posHead[0])*bufferSize.x + fabs(posTail[1] - posHead[1])*bufferSize.y);
	

	vector<float> vtxLerped;
	vector<CloseGL::PixelFormats::ColorRGBA<float>> pixelOutput;

	vtxLerped.resize(fmt.ElementCount);
	for (size_t i = 0; i < step; ++i)
	{
		const float lerp = i / static_cast<float>(step);

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

			auto [outW,outH] = buffer->GetSize();
			outW -= 1; outH -= 1;
			auto& px = buffer->GetPixel(static_cast<int>(outW * posV.x), static_cast<int>(outH * posV.y));
			status.Blender(pixelOutput[colorBufferIndex], px);
		}

		pixelOutput.clear();
	}
}

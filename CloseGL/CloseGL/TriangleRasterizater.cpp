#include <array>
#include "TriangleRasterizater.h"
#include "FrameBuffer.h"
#include "PrimitiveSpliter.h"
#include "MathUtils.h"

//Debug
#include "LineRasterizater.h"

using namespace std;
using namespace CloseGL;
using namespace CloseGL::Math;
using namespace CloseGL::PixelPipeline;
using namespace CloseGL::Geometry;

class TriangleRasterizater : public PixelPipeline
{
public:
	void Draw(const CloseGL::Geometry::GeometryPipelineOutput& input, CloseGL::PixelPipeline::FrameBuffer& renderTarget, const Status& status) const override;
private:
	void DrawHalfTriangle(const float* top, const float* v1, const float* v2, const GeometryDataFormat& format, FrameBuffer& renderTarget, const Status& status, Vector2<int> targetSize) const;
	void DrawScanLine(const float* v1, const float* v2, const GeometryDataFormat& format, FrameBuffer& renderTarget, const Status& status, Vector2<int> targetSize) const;
};

std::shared_ptr<CloseGL::PixelPipeline::PixelPipeline> CloseGL::PixelPipeline::CreateTriangleRasterizater()
{
	return std::make_shared<TriangleRasterizater>();
}

void TriangleRasterizater::Draw(const CloseGL::Geometry::GeometryPipelineOutput & input, CloseGL::PixelPipeline::FrameBuffer & renderTarget, const Status & status) const
{
	const auto primitives = Utils::SplitPrimitive(input);

	auto targetSize = renderTarget.GetMaxColorBufferSize();

	std::vector<float> splitVertex;
	splitVertex.resize(input.Format.ElementCount);
	for (auto& task : primitives) 
	{
		for (int head = 0, center = 1, tail = 2; tail < task.StripSize; head++, center++, tail++)
		{
			std::array<const float*,3> verticles =
			{
				task.Data + head * input.Format.ElementCount,
				task.Data + center * input.Format.ElementCount,
				task.Data + tail * input.Format.ElementCount
			};

			std::sort(verticles.begin(), verticles.end(),
				[&input](const float* a,const float* b) 
				{
					return a[input.Format.PositionElementOffset + 1] < b[input.Format.PositionElementOffset + 1];
				}
			);

			const float splitY = verticles[1][input.Format.PositionElementOffset + 1];
			const float splitYPerc = (splitY - verticles[2][input.Format.PositionElementOffset + 1])
				/ (verticles[0][input.Format.PositionElementOffset + 1] - verticles[2][input.Format.PositionElementOffset + 1]);



			for (size_t j = 0; j < input.Format.UsedElementCount; j++)
				splitVertex[j] = Lerp(verticles[0][j], verticles[2][j], splitYPerc);

			for (size_t j = input.Format.UsedElementCount; j < input.Format.ElementCount; ++j)
				splitVertex[j] = verticles[1][j];
			

			DrawHalfTriangle(verticles[0], verticles[1], splitVertex.data(), input.Format, renderTarget, status, targetSize);
			DrawHalfTriangle(verticles[2], verticles[1], splitVertex.data(), input.Format, renderTarget, status, targetSize);
		}
	}
}

void TriangleRasterizater::DrawHalfTriangle(const float * top, const float * v1, const float * v2, const GeometryDataFormat & fmt, FrameBuffer & renderTarget, const Status & status,Vector2<int> targetSize) const
{
	const float stepsY = 1 + static_cast<int>(Abs((v2[fmt.PositionElementOffset + 1] - top[fmt.PositionElementOffset + 1])*targetSize.y));

	std::vector<float> lerpedV1;
	lerpedV1.resize(fmt.ElementCount);

	std::vector<float> lerpedV2;
	lerpedV2.resize(fmt.ElementCount);
	for (size_t i = 0; i < stepsY; ++i)
	{
		const float percY = i/stepsY;

		//Top-V1
		for (size_t j = 0; j < fmt.UsedElementCount; j++)
			lerpedV1[j] = Lerp(top[j], v1[j], percY);

		for (size_t j = fmt.UsedElementCount; j < fmt.ElementCount; ++j)
			lerpedV1[j] = top[j];

		//Top-V2
		for (size_t j = 0; j < fmt.UsedElementCount; j++)
			lerpedV2[j] = Lerp(top[j], v2[j], percY);

		for (size_t j = fmt.UsedElementCount; j < fmt.ElementCount; ++j)
			lerpedV2[j] = top[j];

		DrawScanLine(lerpedV1.data(), lerpedV2.data(), fmt, renderTarget, status, targetSize);
	}
}

void TriangleRasterizater::DrawScanLine(const float * left, const float * right, const GeometryDataFormat & fmt, FrameBuffer & renderTarget, const Status & status,Vector2<int> targetSize) const
{
	if (left[fmt.PositionElementOffset] > right[fmt.PositionElementOffset]) std::swap(left, right);

	const int leftX = left[fmt.PositionElementOffset] * targetSize.x;
	const int rightX = right[fmt.PositionElementOffset] * targetSize.x;

	vector<float> vtxLerped;
	vector<CloseGL::PixelFormats::ColorRGBA<float>> pixelOutput;
	vtxLerped.resize(fmt.ElementCount);
	for (int x = leftX; x <= rightX; ++x)
	{
		const float perc = (x - leftX) / static_cast<float>(rightX - leftX);


		for (size_t j = 0; j < fmt.UsedElementCount; j++)
			vtxLerped[j] = Lerp(left[j], right[j], perc);

		for (size_t j = fmt.UsedElementCount; j < fmt.ElementCount; ++j)
			vtxLerped[j] = left[j];


		Vector2<float> posV = { vtxLerped[fmt.PositionElementOffset],vtxLerped[fmt.PositionElementOffset+1] };

		status.PixelShader(vtxLerped.data(), fmt, pixelOutput);
		for (
			size_t colorBufferIndex = 0;
			colorBufferIndex < pixelOutput.size() && colorBufferIndex < renderTarget.ColorBuffers.size();
			++colorBufferIndex)
		{
			auto& buffer = renderTarget.ColorBuffers[colorBufferIndex];

			auto p = buffer->GetSize();
			auto outW = p.x;
			auto outH = p.y;

			outW -= 1; outH -= 1;
			auto& px = buffer->GetPixel(static_cast<int>(outW * posV.x), static_cast<int>(outH * posV.y));
			status.Blender(pixelOutput[colorBufferIndex], px);
		}

		pixelOutput.clear();
	}
}




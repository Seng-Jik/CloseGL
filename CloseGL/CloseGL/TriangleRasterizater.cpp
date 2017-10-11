#include "TriangleRasterizater.h"
#include "FrameBuffer.h"
#include "PrimitiveSpliter.h"

using namespace std;
using namespace CloseGL;

class TriangleRasterizater : public PixelPipeline::PixelPipeline
{
public:
	void Draw(const CloseGL::Geometry::GeometryPipelineOutput& input, CloseGL::PixelPipeline::FrameBuffer& renderTarget, const Status& status) const override;
};

std::shared_ptr<PixelPipeline::PixelPipeline> CloseGL::PixelPipeline::CreateTriangleRasterizater()
{
	return std::make_shared<TriangleRasterizater>();
}

void TriangleRasterizater::Draw(const CloseGL::Geometry::GeometryPipelineOutput & input, CloseGL::PixelPipeline::FrameBuffer & renderTarget, const Status & status) const
{
	const auto primitives = Utils::SplitPrimitive(input);
}

#include "LineRasterizater.h"

using namespace std;
using namespace CloseGL::PixelPipeline;

class LineRasterizater final :public PixelPipeline
{
public:
	void Draw(const CloseGL::Geometry::GeometryPipelineOutput& input, FrameBuffer& renderTarget, const Status& status) override;
};

std::shared_ptr<PixelPipeline> CloseGL::PixelPipeline::CreateLineRasterizater()
{
	return std::make_shared<LineRasterizater>();
}

void LineRasterizater::Draw(const CloseGL::Geometry::GeometryPipelineOutput & input, FrameBuffer & renderTarget, const Status & status)
{
}

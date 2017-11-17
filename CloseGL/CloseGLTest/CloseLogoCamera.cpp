#include "stdafx.h"
#include "CloseLogoCamera.h"

void CloseGLTest::Toolkit::CloseLogoCamera::Run()
{
	const auto& vtx = logoWorld_.GetVertexData();
	
	//TODO:Transform position

	CloseGL::Geometry::GeometryPipelineOutput pplInput;
	pplInput.Format.ElementCount = 2;
	pplInput.Format.PositionElementCount = 2;
	pplInput.Format.PositionElementOffset = 0;
	pplInput.Format.UsedElementCount = 2;

	pplInput.Outputs.emplace_back();
	pplInput.Outputs.back().VertexData = vtx;
	pplInput.Outputs.back().StripData.resize(vtx.size() / 2);

	auto& strip = pplInput.Outputs.back().StripData;
	for (size_t i = 0; i < strip.size(); ++i)
	{
		strip[i] = i % 2;
	}

	CloseGL::PixelPipeline::PixelPipeline::Status status;
	status.PerspectiveCorrect = false;
	status.PixelShader = 
		[](const float*, const CloseGL::Geometry::GeometryDataFormat&, std::vector<CloseGL::PixelFormats::ColorRGBA<float>>& outputs)
	{
		outputs.push_back({ 1,1,1,1 });
	};

	tv_.SetUpdateFunction(
		[this,&pplInput,&status](float,CloseGL::Surface<CloseGL::PixelFormats::ColorRGBA<float>>& fbSurface) {
		CloseGL::PixelPipeline::FrameBuffer fb;
		fb.ColorBuffers.push_back(&fbSurface);
		ppl_->Draw(pplInput, fb, status);
	});

	tv_.Run();
}

CloseGL::Logo::LogoWorld<>& CloseGLTest::Toolkit::CloseLogoCamera::GetWorld()
{
	return logoWorld_;
}

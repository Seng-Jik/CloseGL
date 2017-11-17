#pragma once

#include <CloseGL.h>
#include <LogoWorld.h>
#include "TestView.h"

namespace CloseGLTest::Toolkit
{
	class CloseLogoCamera final
	{
	public:
		void Run();
		CloseGL::Logo::LogoWorld<>& GetWorld();
	private:
		std::shared_ptr<CloseGL::PixelPipeline::PixelPipeline> ppl_ = 
			CloseGL::PixelPipeline::CreateLineRasterizater();
		TestView tv_;
		CloseGL::Logo::LogoWorld<> logoWorld_;
	};
}
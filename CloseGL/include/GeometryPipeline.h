#pragma once
#include "GeometryDataFormat.h"
#include "GeometryPass.h"
#include <memory>

namespace CloseGL::Geometry
{
	template<typename TData = float>	//TData = double/float

	class GeometryPipeline : GeometryPass<TData>
	{
	public:
		struct GeometryPipelineOutput
		{
			std::vector<TData> VertexData;
			std::vector<bool> StripData;
			GeometryDataFormat Format;
		};

		GeometryPipeline(GeometryDataFormat format);
		void SetThreads(unsigned childThreads);
		GeometryPipelineOutput Process(const std::vector<TData>& inputData) const;

		void AddPass(const std::shared_ptr<const GeometryPass<TData>>& pass);
		void ClearPass();

	private:
		std::vector<std::shared_ptr<GeometryPass<TData>>> passes_;
		GeometryDataFormat format_;
		unsigned childThreads_ = 0;
	};

	template<typename TData>
	inline GeometryPipeline<TData>::GeometryPipeline(GeometryDataFormat format):
		format_(format)
	{}

	template<typename TData>
	inline void GeometryPipeline<TData>::SetThreads(unsigned childThreads)
	{
		childThreads_ = childThreads;
	}

	template<typename TData>
	inline GeometryPipelineOutput GeometryPipeline<TData>::Process(const std::vector<TData>& inputData) const
	{	
		std::vector<TData>* inputVertex = &inputData;
		std::vector<TData>* outputVertex = nullptr;
		std::vector<bool>* inputStrip = nullptr;
		std::vector<bool>* outputStrip = nullptr;

		for (auto& p : passes_)
		{
			GeometryPass::GeometryPassIO mainThreadPassIO;
			mainThreadPassIO.DataFormat = &format_;

		}

		return out;
	}

	template<typename TData>
	inline void GeometryPipeline<TData>::AddPass(const std::shared_ptr<const GeometryPass<TData>>& pass)
	{
		passes_.push_back(pass);
	}

	template<typename TData>
	inline void GeometryPipeline<TData>::ClearPass()
	{
		passes_.clear();
	}
}
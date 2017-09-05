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
		GeometryPipeline(GeometryDataFormat format);
		std::vector<TData> Process(const std::vector<TData>& inputData) const;

		void AddPass(const std::shared_ptr<const GeometryPass<TData>>& pass);
		void ClearPass();

	private:
		std::vector<std::shared_ptr<GeometryPass<TData>>> passes_;
	};
}
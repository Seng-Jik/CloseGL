#pragma once
#include <functional>
#include "GeometryPass.h"

namespace CloseGL::Geometry
{
	template<int VertexPerPrimitive = 4>
	class VertexShader : public GeometryPass<VertexPerPrimitive>
	{
	public:
		VertexShader(const std::function<void(float* attributes, const GeometryDataFormat&)>&);
		void Process(typename GeometryPass<VertexPerPrimitive>::GeometryPassIO& io) const override;

	private:
		std::function<void(float*, const GeometryDataFormat&)> shader_;
	};

	template<int VertexPerPrimitive>
	inline VertexShader<VertexPerPrimitive>::VertexShader(const std::function<void(float*attributes, const GeometryDataFormat&)>& s):
		shader_(s)
	{}

	template<int VertexPerPrimitive>
	inline void VertexShader<VertexPerPrimitive>::Process(typename GeometryPass<VertexPerPrimitive>::GeometryPassIO & io) const
	{
		const size_t vtxCount = io.VertexData.size() / io.Format->ElementCount;
		for (size_t i = 0; i < vtxCount; ++i)
			shader_(io.VertexData.data() + i * io.Format->ElementCount, *io.Format);
	}
}

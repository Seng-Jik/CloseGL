#pragma once

#include "GeometryPass.h"

namespace CloseGL::Geometry
{
	template<int VertexPerPrimitive = 4>
	class PrimitiveStriper : public GeometryPass<VertexPerPrimitive>
	{
	public:
		void Process(typename GeometryPass<VertexPerPrimitive>::GeometryPassIO& io) const override;
	};

	template<int VertexPerPrimitive>
	inline void PrimitiveStriper<VertexPerPrimitive>::Process(typename GeometryPass<VertexPerPrimitive>::GeometryPassIO & io) const
	{
		int vertexNum = 0;

		const size_t vtxCount = io.VertexData.size() / io.Format->ElementCount;
		for (size_t i = 0; i < vtxCount; ++i) 
		{
			if (vertexNum >= VertexPerPrimitive) vertexNum = 0;
			io.StripData.at(i) = vertexNum++ > 0;
			
		}
	}
}

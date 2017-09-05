#pragma once
#include "PrimitiveType.h"
#include "GeometryPass.h"

namespace CloseGL::Geometry
{
	template<typename TData = float>
	class PrimitiveStriper :GeometryPass<TData>
	{
	public:
		PrimitiveStriper();
		PrimitiveStriper(PrimitiveType type);
	};
}

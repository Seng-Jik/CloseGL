#pragma once
#include <vector>
#include "GeometryDataFormat.h"

namespace CloseGL::Geometry
{
	template<int VertexPerPrimitive = 4>
	class GeometryPass
	{
	public:

		struct GeometryPassIO
		{
			const GeometryDataFormat* const Format;
			std::vector<float> VertexData;
			std::vector<bool> StripData;

			GeometryPassIO(const GeometryDataFormat& format) :
				Format(&format) {}
		};

		virtual void Process(GeometryPassIO& io) const = 0;		//Warning:It will call in different threads
	};
}

#pragma once
#include <vector>

namespace CloseGL::Geometry
{
	template<typename TData = float>
	class GeometryPass
	{
	public:

		struct GeometryPassIO
		{
			const GeometryDataFormat* const Format;
			std::vector<TData> VertexData;
			std::vector<bool> StripData;

			GeometryPassIO(const GeometryDataFormat& format) :
				Format(&format) {}
		};

		virtual void Process(GeometryPassIO& io) const = 0;		//Warning:It will call in different threads
	};
}

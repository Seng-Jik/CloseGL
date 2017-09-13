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
			const GeometryDataFormat* DataFormat;
			const std::vector<TData>* InputVertexData;

			std::vector<TData>* OutputVertexData;
			std::vector<bool>* StripInfo;
		};

		virtual void Process(GeometryPassIO& io) const = 0;		//Warning:It will call in different threads if multithread enabled.
	};
}

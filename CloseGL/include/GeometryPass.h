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
			const size_t ThreadSplitOffset, ThreadSplitCount;

			std::vector<TData>* OutputVertexData;
			std::vector<bool>* StripInfo;
			size_t VertexCount;
		};

		virtual void Process(GeometryPassIO& io) const = 0;		//Warning:It will call in different threads if multithread enabled.
		virtual bool OutputStripInfo() const = 0;
		virtual bool OutputVertexInfo() const = 0;
		virtual bool MultiThreadProcessEnabled() const;
	};

	template<typename TData>
	inline bool GeometryPass<TData>::MultiThreadProcessEnabled() const
	{
		return true;
	}
}
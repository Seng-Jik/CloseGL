#pragma once

namespace CloseGL::Geometry
{
	/*	Geometry Data Format
	 *	-----------------------------------------------------------------------
	 *	|used|used|   x|   y|   z|   w|used|    |NextVertex...
	 *	-----------------------------------------------------------------------
	 *	|   0|   1|   2|   3|   4|   5|            <-  PositionElementOffset = 2
	 *	|----------------------------------|       <-  UsedElementCountInOneVertex = 7
	 *  |---------------------------------------|  <-  ElementCountInOneVertex = 8
	 */
	struct GeometryDataFormat
	{
		size_t PositionElementOffset;
		size_t UsedElementCountInOneVertex;
		size_t ElementCountInOneVertex;
	};
}
#pragma once

namespace CloseGL::Geometry
{
	/*	Geometry Data Format
	 *	-----------------------------------------------------------------------
	 *	|used|used|   x|   y|   z|   w|used|    |NextVertex...
	 *	-----------------------------------------------------------------------
	 *	|   0|   1|   2|   3|   4|   5|            <-  PositionElementOffset = 2
	 *	|----------------------------------|       <-  UsedElementCount = 7
	 *  |---------------------------------------|  <-  ElementCount = 8
	 */
	struct GeometryDataFormat
	{
		size_t PositionElementOffset;
		size_t UsedElementCount;
		size_t ElementCount;
	};
}
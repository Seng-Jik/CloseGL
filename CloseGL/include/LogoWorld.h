#pragma once
#include <vector>
#include "Vectors.h"

namespace CloseGL::Logo
{
	template<typename TVertexBase = float>
	class LogoWorld
	{
	public:
		const std::vector<TVertexBase>& GetVertexData();
		void AddLine(Math::Vector2<TVertexBase> p1, Math::Vector2<TVertexBase> p2);
	private:
		std::vector<TVertexBase> lines_;
	};

	template<typename TVertexBase>
	inline const std::vector<TVertexBase>& LogoWorld<TVertexBase>::GetVertexData()
	{
		return lines_;
	}
	template<typename TVertexBase>
	inline void LogoWorld<TVertexBase>::AddLine(Math::Vector2<TVertexBase> p1, Math::Vector2<TVertexBase> p2)
	{
		lines_.push_back(p1.x);
		lines_.push_back(p1.y);
		lines_.push_back(p2.x);
		lines_.push_back(p2.y);
	}
}
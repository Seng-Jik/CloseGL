#pragma once
#include <LogoWorld.h>

namespace CloseGL::Logo
{
	template<typename TVertexBase = float>
	class ClassicLogo
	{
	public:
		ClassicLogo(LogoWorld<TVertexBase>& world) :logoWorld_(&world) {};

		void Move();
		void Resize(TVertexBase factor);
		void Rotate(TVertexBase angle);
		void Forward();

	private:
		LogoWorld<TVertexBase>* logoWorld_;

		Math::Vector2<TVertexBase> position_ = { 0,0 };
		Math::Vector2<TVertexBase> step_ = { 0,1 };
	};

	template<typename TVertexBase>
	inline void ClassicLogo<TVertexBase>::Move()
	{
		auto p1 = position_;
		Forward();
		auto p2 = position_;

		logoWorld_->AddLine(p1, p2);
	}
	template<typename TVertexBase>
	inline void ClassicLogo<TVertexBase>::Resize(TVertexBase factor)
	{
		position_ *= factor;
	}

	template<typename TVertexBase>
	inline void ClassicLogo<TVertexBase>::Rotate(TVertexBase angle)
	{
		//暂时没写Matrix，暂时糊上
		const auto s = step_;
		step_.x = s.x * cos(angle) - s.y * sin(angle);
		step_.y = s.x * sin(angle) + s.y * cos(angle);
	}

	template<typename TVertexBase>
	inline void ClassicLogo<TVertexBase>::Forward()
	{
		position_ += step_;
	}
}
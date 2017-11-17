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
		position_ = position_ * factor;
	}

	template<typename TVertexBase>
	inline void ClassicLogo<TVertexBase>::Rotate(TVertexBase angle)
	{
		//暂时没写Matrix，暂时糊上
		const auto s = step_;
		const auto rad = angle * 3.1415926 / 180;
		step_.x = static_cast<float>(s.x * cos(rad) - s.y * sin(rad));
		step_.y = static_cast<float>(s.x * sin(rad) + s.y * cos(rad));
	}

	template<typename TVertexBase>
	inline void ClassicLogo<TVertexBase>::Forward()
	{
		position_ = position_ + step_;
	}
}
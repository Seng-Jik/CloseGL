#pragma once
#include <functional>
#include <utility>
#include <exception>
#include <typeinfo>
#include <typeindex>

namespace SDL
{
	class Handler final
	{
	public:
		using Deleter = std::function<void(Handler&)>;

		template<typename T>
		inline Handler(T* ptr, Deleter deleter);

		inline const Handler& operator = (Handler&&);
		inline Handler(Handler&& r) noexcept;
		inline ~Handler();

		template<typename T>
		inline operator T() const;
	private:
		void* ptr_;
		Deleter deleter_;

#ifdef _DEBUG
		std::type_index typeInfo_;
#endif
	};

	template<typename T>
	inline Handler::Handler(T * ptr, Deleter deleter) :
		ptr_(ptr),
		deleter_(deleter)
#ifdef _DEBUG
		,typeInfo_(typeid(T*))
#endif
	{
	}

	template<typename T>
	inline Handler::operator T() const
	{
#ifdef _DEBUG
		if (std::type_index(typeid(T)) != typeInfo_)
			throw std::bad_cast();
#endif
		return static_cast<T>(ptr_);
	}


	inline Handler::Handler(Handler && r) noexcept
#ifdef _DEBUG
		:typeInfo_(std::move(r.typeInfo_))
#endif
	{
		deleter_ = std::move(r.deleter_);
		ptr_ = r.ptr_;
		r.ptr_ = nullptr;
	}

	inline const Handler& Handler::operator=(Handler && r)
	{
		ptr_ = r.ptr_;
		deleter_ = std::move(r.deleter_);

		r.ptr_ = nullptr;

#ifdef _DEBUG
		typeInfo_ = std::move(r.typeInfo_);
#endif

		return *this;
	}

	inline Handler::~Handler()
	{
		if (deleter_)
			deleter_(*this);
	}

}



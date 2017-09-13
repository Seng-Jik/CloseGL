#pragma once
#include <functional>
#include "Handler.h"

namespace SDL
{
	class Library final
	{
	private:
		void* loadFunction(const std::string& funcName) const;
	public:
		Library(const std::string& libName);

		template<class FuncType>
		std::function<FuncType> LoadFunction(const std::string& funcName) const
		{
			return static_cast<FuncType*>(loadFunction(funcName));
		}

	private:
		Handler libraryHandle_;
	};
}

#pragma once
#include <string>
#include <cstdint>
#include "Handler.h"

namespace SDL
{
	using std::string;

	class RWops final
	{
	public:
		explicit RWops(void* ptrSDL_RWops);
		explicit RWops(void* mem, int size);
		explicit RWops(const void* mem, int size);
		RWops(const string& filePath, const string& mode);

		bool Available() const;

		const Handler& GetPtrToSDL_RWops();
		
		size_t Read(void* ptr, size_t size, size_t maxnum);
		size_t Write(const void* ptr, size_t size, size_t num);
		int64_t Tell();
	private:
		Handler rwopsHandle_;
	};
}
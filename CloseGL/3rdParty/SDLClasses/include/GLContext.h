#pragma once
#include "Handler.h"

namespace SDL {
	class GLContext final
	{
	public:
	private:
		friend class Window;
		GLContext(Handler& windowHandler);
		Handler contextHandler_;
	};
}

#pragma once
#include <string>
namespace SDL
{
	using std::string;
	class Clipboard final
	{
	public:
		string GetText();
		bool HasText();
		void SetText(const string& text);
	};
}
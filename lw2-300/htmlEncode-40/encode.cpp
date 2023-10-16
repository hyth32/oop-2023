#include <sstream>
#include "encode.h"

std::string HtmlEncode(const std::string& text)
{
	std::istringstream in(text);
	std::ostringstream out;
	HtmlEncode(in, out);
	return out.str();
}

void HtmlEncode(std::istream& in, std::ostream& out)
{
    char charToEncode;
    while (in >> std::noskipws >> charToEncode)
    {
		out << HtmlEncodeChar(charToEncode);
    }
    if (!in.eof() && in.fail())
    {
        throw std::runtime_error("error while reading");
    }
}

std::string HtmlEncodeChar(char charToEncode)
{
	switch (charToEncode)
	{
	case '"':
		return "&quot;";
	case '\'':
		return "&apos;";
	case '>':
		return "&gt;";
	case '<':
		return "&lt;";
	case '&':
		return "&amp;";
	default:
		return std::string(1, charToEncode);
	}
}

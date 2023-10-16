#include <string>

std::string HtmlEncode(const std::string& text);

void HtmlEncode(std::istream& in, std::ostream& out);

std::string HtmlEncodeChar(char charToEncode);
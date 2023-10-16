//htmlencode -- 40
//Разработайте функцию
//std::string HtmlEncode(std::string const& text),
//выполняющую кодирование специальных символов строки text соответствующими сущностями HTML :
//“(двойная кавычка) заменяется на& quot;
//‘(апостроф) заменяется на& apos;
//< (знак меньше) заменяется на& lt;
//> (знак больше) заменяется на& gt;
//&(амперсанд)заменяется на& amp;
//Например, строка Cat < says> "Meow".M & M’s должна быть преобразована в строку
//Cat & lt; says& gt; &quot; Meow& quot; .M& amp; M& apos; s

#include <iostream>
#include "encode.h"

int main()
{
	std::string line;
	while (std::cin.good())
	{
		std::getline(std::cin, line);

		std::string encodedHtml;
		try
		{
			encodedHtml = HtmlEncode(line);
		}
		catch (const std::exception& err)
		{
			std::cout << err.what() << std::endl;
			return 1;
		}
		std::cout << encodedHtml << std::endl;
	}

	return 0;
}
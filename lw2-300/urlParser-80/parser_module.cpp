#include "parser_module.h"

void CheckUrlOnValid(std::istream& inFile, std::ostream& outFile)
{
	std::string line;
	bool isURLValid = false;
	while (inFile >> line)
	{
		auto url = ParseUrl(line);
		if (url.has_value())
		{
			isURLValid = ValidUrl(url.value());
		}

		SendResultMessage(outFile, isURLValid);

		if (isURLValid)
		{
			PrintURLInfo(outFile, url.value());
		}
	}
}

void SendResultMessage(std::ostream& outFile, bool isURLValid)
{
	if (isURLValid)
	{
		outFile << "This is the correct url." << std::endl;
	}
	else
	{
		outFile << "Sorry, this is an invalid url." << std::endl;
	}
}

void PrintURLInfo(std::ostream& outFile, const URL& url)
{
	outFile << url.url << std::endl;
	outFile << "PROTOCOL: " << url.protocol << std::endl;
	outFile << "HOST: " << url.host << std::endl;
	outFile << "PORT: " << url.port << std::endl;
	outFile << "DOCUMENT: " << url.document << std::endl;
}

std::optional<URL> ParseUrl(const std::string& url)
{
	URL resultURL = { "" };

	resultURL.url = url;
	std::regex protocol(R"\w+");
	std::smatch result;

	resultURL.protocol = std::regex_search(url, result, protocol) ? result.str(0) : "";

	std::cout << result.str(0) << std::endl;

	return { resultURL };
}

bool ValidUrl(const URL& url)
{
	return true;
}

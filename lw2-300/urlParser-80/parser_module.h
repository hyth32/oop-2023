#pragma once

#include <iostream>
#include <optional>
#include <regex>
#include <string>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

struct URL
{
	std::string url;
	std::string protocol;
	int port;
	std::string host;
	std::string document;
};

void CheckUrlOnValid(std::istream& inFile, std::ostream& outFile);
std::optional<URL> ParseUrl(const std::string& url);
bool ValidUrl(const URL& url);
void SendResultMessage(std::ostream& outFile, bool isURLValid);
void PrintURLInfo(std::ostream& outfile, const URL& url);
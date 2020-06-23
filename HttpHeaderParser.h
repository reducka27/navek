#pragma once
#include "HttpHeader.h"
#include <string>
#include <optional>

class HttpHeaderParser {
public:
	HttpHeaderParser() {};
	~HttpHeaderParser() {};

	HttpHeader parse(std::string_view header);

private:
    void parseLine(std::string_view line, std::unordered_map<std::string, std::string> &http_request);
    std::tuple<std::string, std::string> parseFirstLine(std::string_view line);
};


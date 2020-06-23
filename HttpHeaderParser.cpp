#include "HttpHeaderParser.h"
#include <algorithm>

inline std::string& trim(std::string& str) {
    str.erase(str.find_last_not_of(' ')+1);             //surfixing spaces
    str.erase(0, str.find_first_not_of(' '));    //prefixing spaces
    return str;
}

std::vector<std::string_view> split(const std::string_view str, const char delim = '\n') {
    std::vector<std::string_view> result;

    int indexCommaToLeftOfColumn = 0;
    int indexCommaToRightOfColumn = -1;
    std::size_t strSize = static_cast<int>(str.size());
    for (int i = 0; i < strSize; i++) {
        if (str[i] == delim) {
            indexCommaToLeftOfColumn = indexCommaToRightOfColumn;
            indexCommaToRightOfColumn = i;
            int index = indexCommaToLeftOfColumn + 1;
            int length = indexCommaToRightOfColumn - index;

            std::string_view column(str.data() + index, length);
            result.push_back(column);
        }
    }
    std::string_view finalColumn(str.data() + indexCommaToRightOfColumn + 1, str.size() - indexCommaToRightOfColumn - 1);
    result.push_back(finalColumn);
    return result;
}

HttpHeader HttpHeaderParser::parse(std::string_view header_str) {
    std::unordered_map<std::string, std::string> m;

    std::vector<std::string_view> lines(split(header_str));

    std::string_view requestType, url;
    bool isFirstLine = true;
    for (const auto & line: lines) {
        if (!isFirstLine) {
            parseLine(line, m);
        } else {
            tie(requestType, url) = parseFirstLine(line);
            isFirstLine = false;
        }
    }
    return HttpHeader(requestType, url, std::move(m));
}

std::tuple<std::string, std::string> HttpHeaderParser::parseFirstLine(std::string_view line) {
    std::size_t pos = 0, lpos = 0;
    pos = line.find(' ');
    std::string reqType(line.substr(0, pos));
    lpos = ++pos;
    pos = line.find(' ', pos);
    std::string url(line.substr(lpos, (pos - lpos)));
    return {reqType, url};
}

void HttpHeaderParser::parseLine(std::string_view line, std::unordered_map<std::string, std::string> &http_request) {
    if(line.size() == 0) return ;

    std::size_t posFirst = line.find(':',0);

    std::string key(line.substr(0, posFirst));
    std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c){ return std::tolower(c); });
    std::string value(line.substr(posFirst + 1));
    http_request.emplace(trim(key), trim(value));
}
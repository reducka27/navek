#include "HttpHeader.h"

std::unordered_map<std::string, HttpHeader::REQUEST_TYPE> const HttpHeader::ReqTypeMatchTable = {
        {"GET",     HttpHeader::REQUEST_TYPE::GET},
        {"POST",    HttpHeader::REQUEST_TYPE::POST},
        {"CONNECT", HttpHeader::REQUEST_TYPE::CONNECT},
        {"PUT",     HttpHeader::REQUEST_TYPE::PUT},
        {"HEAD",    HttpHeader::REQUEST_TYPE::HEAD}
};

HttpHeader::REQUEST_TYPE HttpHeader::getReqType() {
	return requestType;
}

void HttpHeader::setReqType(const HttpHeader::REQUEST_TYPE req) {
    requestType = req;
}
void HttpHeader::setReqType(std::string_view type) {
    auto it = HttpHeader::ReqTypeMatchTable.find(std::string(type));
    if (it != HttpHeader::ReqTypeMatchTable.end()) {
        requestType = it->second;
    } else {
        requestType = REQUEST_TYPE::UNKNOWN;
    }
}

std::string HttpHeader::getUrl() {
	return url;
}

std::string HttpHeader::getHeader(std::string_view key) {
	auto it = this->headers.find(key.data());
	if (it != headers.end()) {
		return it->second;
	} else {
		return nullptr;
	}
}

std::unordered_map<std::string, std::string> HttpHeader::getHeaders() {
	return headers;
}
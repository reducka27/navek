#pragma once
#include <string>
#include <unordered_map>
#include <iostream>

class HttpHeader {
public:
    enum REQUEST_TYPE {
        GET,
        POST,
        CONNECT,
        PUT,
        HEAD,
        UNKNOWN
    };

	HttpHeader(std::string_view reqType, std::string_view url, std::unordered_map <std::string, std::string> &&headers) :
	    url(url),
	    headers(headers) {
            setReqType(reqType);
	    };
	~HttpHeader() {};

	REQUEST_TYPE getReqType();
	std::string getUrl();
	std::string getHeader(std::string_view key);

	std::unordered_map<std::string, std::string> getHeaders();

    friend class HttpHeaderParser;
private:
    REQUEST_TYPE requestType;
	std::string url;
	std::unordered_map<std::string, std::string> headers;

    static std::unordered_map<std::string, REQUEST_TYPE> const ReqTypeMatchTable;

    void setReqType(const HttpHeader::REQUEST_TYPE type);
    void setReqType(std::string_view type);
};
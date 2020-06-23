#include <string>
#include <iostream>
#include "HttpHeaderParser.h"

int main() {
    std::string header = "GET /wiki/http HTTP/1.1\n\
                            Host: ru.wikipedia.org\n\
                            User - Agent : Mozilla / 5.0 (X11; U; Linux i686; ru; rv:1.9b5) Gecko / 2008050509 Firefox / 3.0b5\n\
                            Accept : text / html\n\
                            Connection : close\n\
                            Host2: ru.wikipedia.org\n\
                            User - Agent2 : Mozilla / 5.0 (X11; U; Linux i686; ru; rv:1.9b5) Gecko / 2008050509 Firefox / 3.0b5\n\
                            Accept2 : text / html\n\
                            Connection2 : close\n\
                            Host3: ru.wikipedia.org\n\
                            User - Agent3 : Mozilla / 5.0 (X11; U; Linux i686; ru; rv:1.9b5) Gecko / 2008050509 Firefox / 3.0b5\n\
                            Accept3 : text / html\n\
                            Connection3 : close";

    HttpHeaderParser parser;
    HttpHeader httpHeader(parser.parse(header));
    std::unordered_map<std::string, std::string> headers = httpHeader.getHeaders();

    std::cout << httpHeader.getReqType() << std::endl;
    std::cout << httpHeader.getUrl() << std::endl;
    for (const auto& [key, value]: headers) {
        std::cout << key << ": " << value << std::endl;
    }
}
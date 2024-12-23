#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

// #include "cex/http.hpp"
#include "cex/http.hpp"

// namespace http = ::cex::http;
namespace http = ::cex::http;

int main(int argc, char *argv[]) {
    std::string url;

    if(argc < 2) {
        url = "https://example.com";
    } else {
        url = argv[1];
    }

    auto [ res, err ] = http::get(url);

    if(err != nullptr) {
        std::cerr << err->Error() << std::endl;
        exit(1);
    }

    std::cout << res << std::endl;
}

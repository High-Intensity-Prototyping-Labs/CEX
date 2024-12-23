#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

// #include "cex/http.hpp"
#include "cex/http.hpp"

// namespace http = ::cex::http;
namespace http = ::cex::http;

int main(int argc, char *argv[]) {
    const char *url;

    if(argc < 2) {
        url = "https://google.com";
    } else {
        url = argv[1];
    }

    auto [ res, err ] = http::get(url);

    if(err != nullptr) {
        std::cerr << err->error() << std::endl;
        exit(1);
    }

    std::cout << res->body() << std::endl;
}

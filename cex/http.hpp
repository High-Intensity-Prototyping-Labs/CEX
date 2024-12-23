#ifndef CEX_HTTP
#define CEX_HTTP

// Standard C Dependencies
#include <cstddef>
#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <cstring>

// Standard C++ Dependencies
#include <map>
#include <tuple>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

// CEX Dependencies
#include "cex/errors.hpp"

// External Dependencies
#include <curl/curl.h>

namespace cex {
    namespace errors {
        cex::error New(CURLcode cc) {
            return errors::New(curl_easy_strerror(cc));
        }
    }

    namespace http {
        struct response {
            void*   data_buffer_heap;
            size_t  data_len;
            std::string body(void) {
                return std::string((char*)data_buffer_heap, data_len);
            }
        };

        std::tuple<http::response*, cex::error> get(std::string url) {
            CURL    *curl;
            CURLcode res;

            http::response *response = new http::response;

            curl = curl_easy_init();

            if(curl) {
                // Configure cURL
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
                    (size_t(*)(void*, size_t, size_t, char**))[](
                        void *ptr,
                        size_t size,
                        size_t nmemb,
                        char **out_data)->size_t
                    {
                        *out_data = new char[size*nmemb];
                        memcpy(*out_data, ptr, size * nmemb);
                        return size * nmemb;
                    }
                );
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response->data_buffer_heap);

                // Perform request
                res = curl_easy_perform(curl);

                // C++11
                if(res != CURLE_OK) {
                    return std::make_tuple(nullptr, errors::New(res));
                }

                // Get cURL internals into response
                curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD_T, &response->data_len);
                // curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &response->effective_url); // WARNING: Will be lost
                // curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response->code);
                // curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &response->time);

                // Cleanup cURL
                curl_easy_cleanup(curl);
                // curl_global_cleanup();

                // OK
                return std::make_tuple(response, nullptr); // WHAT does .get() do??
            }

            // FAIL
            return std::make_tuple(nullptr, errors::New(res));
        }
    }
}

#endif // CEX_HTTP

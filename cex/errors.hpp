#ifndef CEX_ERROR
#define CEX_ERROR

// Standard C++ Dependencies
#include <string>

namespace cex {
    namespace {
        struct error_string {
            error_string(std::string text) {
                this->s = text;
            }

            std::string Error(void) {
                return this->s;
            }
        private:
            std::string s;
        };

    }

    typedef error_string* error;

    namespace errors {
        error New(std::string text) {
            return new error_string(text);
        }
    }
}

#endif // CEX_ERROR

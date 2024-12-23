#ifndef CEX_ERROR
#define CEX_ERROR

// Standard C++ Dependencies
#include <string>
#include <memory>

namespace cex {
    namespace {
        struct error_string {
            error_string(std::string text) {
                this->s = text;
            }

            std::string error(void) {
                return this->s;
            }
        private:
            std::string s;
        };

    }

    typedef std::unique_ptr<error_string> error;

    namespace errors {
        error from(std::string text) {
            return std::unique_ptr<error_string>(new error_string(text));
        }
    }
}

#endif // CEX_ERROR

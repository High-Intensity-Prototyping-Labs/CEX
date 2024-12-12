#ifndef CEX_HTTP
#define CEX_HTTP

// Standard C Dependencies
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
        error New(CURLcode cc) {
            error error;

            switch(cc) {
            case CURLE_OK:
                error = nullptr;
                break;
            case CURLE_FAILED_INIT:
                error = errors::New("Early initialization code failed. This is likely to be an internal error or problem, or a resource problem where something fundamental could not get done at init time.");
                break;
            case CURLE_UNSUPPORTED_PROTOCOL:
                error = errors::New("The URL you passed to libcurl used a protocol that this libcurl does not support. The support might be a compile-time option that you did not use, it can be a misspelled protocol string or just a protocol libcurl has no code for.");
                break;
            case CURLE_URL_MALFORMAT:
                error = errors::New("The URL was not properly formatted.");
                break;
            case CURLE_NOT_BUILT_IN:
                error = errors::New("A requested feature, protocol or option was not found built into this libcurl due to a build-time decision. This means that a feature or option was not enabled or explicitly disabled when libcurl was built and in order to get it to function you have to get a rebuilt libcurl.");
                break;
            case CURLE_COULDNT_RESOLVE_PROXY:
                error = errors::New("Could not resolve proxy. The given proxy host could not be resolved.");
                break;
            case CURLE_COULDNT_RESOLVE_HOST:
                error = errors::New("Could not resolve host. The given remote host was not resolved.");
                break;
            case CURLE_COULDNT_CONNECT:
                error = errors::New("Failed to connect() to host or proxy.");
                break;
            case CURLE_WEIRD_SERVER_REPLY:
                error = errors::New("The server sent data libcurl could not parse. This error code was known as CURLE_FTP_WEIRD_SERVER_REPLY before 7.51.0.");
                break;
            case CURLE_REMOTE_ACCESS_DENIED:
                error = errors::New("We were denied access to the resource given in the URL. For FTP, this occurs while trying to change to the remote directory.");
                break;
            case CURLE_FTP_ACCEPT_FAILED:
                error = errors::New("While waiting for the server to connect back when an active FTP session is used, an error code was sent over the control connection or similar.");
                break;
            case CURLE_FTP_WEIRD_PASS_REPLY:
                error = errors::New("After having sent the FTP password to the server, libcurl expects a proper reply. This error code indicates that an unexpected code was returned.");
                break;
            case CURLE_FTP_ACCEPT_TIMEOUT:
                error = errors::New("During an active FTP session while waiting for the server to connect, the CURLOPT_ACCEPTTIMEOUT_MS (or the internal default) timeout expired.");
                break;
            case CURLE_FTP_WEIRD_PASV_REPLY:
                error = errors::New("libcurl failed to get a sensible result back from the server as a response to either a PASV or a EPSV command. The server is flawed.");
                break;
            case CURLE_FTP_WEIRD_227_FORMAT:
                error = errors::New("FTP servers return a 227-line as a response to a PASV command. If libcurl fails to parse that line, this return code is passed back.");
                break;
            case CURLE_FTP_CANT_GET_HOST:
                error = errors::New("An internal failure to lookup the host used for the new connection.");
                break;
            case CURLE_HTTP2:
                error = errors::New("A problem was detected in the HTTP2 framing layer. This is somewhat generic and can be one out of several problems, see the error buffer for details.");
                break;
            case CURLE_FTP_COULDNT_SET_TYPE:
                error = errors::New("Received an error when trying to set the transfer mode to binary or ASCII.");
                break;
            case CURLE_PARTIAL_FILE:
                error = errors::New("A file transfer was shorter or larger than expected. This happens when the server first reports an expected transfer size, and then delivers data that does not match the previously given size.");
                break;
            case CURLE_FTP_COULDNT_RETR_FILE:
                error = errors::New("This was either a weird reply to a 'RETR' command or a zero byte transfer complete.");
                break;
            case CURLE_QUOTE_ERROR:
                error = errors::New("When sending custom \"QUOTE\" commands to the remote server, one of the commands returned an error code that was 400 or higher (for FTP) or otherwise indicated unsuccessful completion of the command.");
                break;
            case CURLE_HTTP_RETURNED_ERROR:
                error = errors::New("This is returned if CURLOPT_FAILONERROR is set TRUE and the HTTP server returns an error code that is >= 400.");
                break;
            case CURLE_WRITE_ERROR:
                error = errors::New("An error occurred when writing received data to a local file, or an error was returned to libcurl from a write callback.");
                break;
            case CURLE_UPLOAD_FAILED:
                error = errors::New("Failed starting the upload. For FTP, the server typically denied the STOR command. The error buffer usually contains the server's explanation for this.");
                break;
            case CURLE_READ_ERROR:
                error = errors::New("There was a problem reading a local file or an error returned by the read callback.");
                break;
            case CURLE_OUT_OF_MEMORY:
                error = errors::New("A memory allocation request failed. This is serious badness and things are severely screwed up if this ever occurs.");
                break;
            case CURLE_OPERATION_TIMEDOUT:
                error = errors::New("Operation timeout. The specified time-out period was reached according to the conditions.");
                break;
            case CURLE_FTP_PORT_FAILED:
                error = errors::New("The FTP PORT command returned error. This mostly happens when you have not specified a good enough address for libcurl to use. See CURLOPT_FTPPORT.");
                break;
            case CURLE_FTP_COULDNT_USE_REST:
                error = errors::New("The FTP REST command returned error. This should never happen if the server is sane.");
                break;
            case CURLE_RANGE_ERROR:
                error = errors::New("The server does not support or accept range requests.");
                break;
            case CURLE_SSL_CONNECT_ERROR:
                error = errors::New("A problem occurred somewhere in the SSL/TLS handshake. You really want the error buffer and read the message there as it pinpoints the problem slightly more. Could be certificates (file formats, paths, permissions), passwords, and others.");
                break;
            case CURLE_BAD_DOWNLOAD_RESUME:
                error = errors::New("The download could not be resumed because the specified offset was out of the file boundary.");
                break;
            case CURLE_FILE_COULDNT_READ_FILE:
                error = errors::New("A file given with FILE:// could not be opened. Most likely because the file path does not identify an existing file. Did you check file permissions?");
                break;
            case CURLE_LDAP_CANNOT_BIND:
                error = errors::New("LDAP cannot bind. LDAP bind operation failed.");
                break;
            case CURLE_LDAP_SEARCH_FAILED:
                error = errors::New("LDAP search failed.");
                break;
            case CURLE_ABORTED_BY_CALLBACK:
                error = errors::New("Aborted by callback. A callback returned \"abort\" to libcurl.");
                break;
            case CURLE_BAD_FUNCTION_ARGUMENT:
                error = errors::New("A function was called with a bad parameter.");
                break;
            case CURLE_INTERFACE_FAILED:
                error = errors::New("Interface error. A specified outgoing interface could not be used. Set which interface to use for outgoing connections' source IP address with CURLOPT_INTERFACE.");
                break;
            case CURLE_TOO_MANY_REDIRECTS:
                error = errors::New("Too many redirects. When following redirects, libcurl hit the maximum amount. Set your limit with CURLOPT_MAXREDIRS.");
                break;
            case CURLE_UNKNOWN_OPTION:
                error = errors::New("An option passed to libcurl is not recognized/known. Refer to the appropriate documentation. This is most likely a problem in the program that uses libcurl. The error buffer might contain more specific information about which exact option it concerns.");
                break;
            case CURLE_SETOPT_OPTION_SYNTAX:
                error = errors::New("An option passed in to a setopt was wrongly formatted. See error message for details about what option.");
                break;
            case CURLE_GOT_NOTHING:
                error = errors::New("Nothing was returned from the server, and under the circumstances, getting nothing is considered an error.");
                break;
            case CURLE_SSL_ENGINE_NOTFOUND:
                error = errors::New("The specified crypto engine was not found.");
                break;
            case CURLE_SSL_ENGINE_SETFAILED:
                error = errors::New("Failed setting the selected SSL crypto engine as default.");
                break;
            case CURLE_SEND_ERROR:
                error = errors::New("Failed sending network data.");
                break;
            case CURLE_RECV_ERROR:
                error = errors::New("Failure with receiving network data.");
                break;
            case CURLE_SSL_CERTPROBLEM:
                error = errors::New("problem with the local client certificate.");
                break;
            case CURLE_SSL_CIPHER:
                error = errors::New("Could not use specified cipher.");
                break;
            case CURLE_PEER_FAILED_VERIFICATION:
                error = errors::New("The remote server's SSL certificate or SSH fingerprint was deemed not OK. This error code has been unified with CURLE_SSL_CACERT since 7.62.0. Its previous value was 51.");
                break;
            case CURLE_BAD_CONTENT_ENCODING:
                error = errors::New("Unrecognized transfer encoding.");
                break;
            case CURLE_FILESIZE_EXCEEDED:
                error = errors::New("Maximum file size exceeded.");
                break;
            case CURLE_USE_SSL_FAILED:
                error = errors::New("Requested FTP SSL level failed.");
                break;
            case CURLE_SEND_FAIL_REWIND:
                error = errors::New("When doing a send operation curl had to rewind the data to retransmit, but the rewinding operation failed.");
                break;
            case CURLE_SSL_ENGINE_INITFAILED:
                error = errors::New("Initiating the SSL Engine failed.");
                break;
            case CURLE_LOGIN_DENIED:
                error = errors::New("The remote server denied curl to login (Added in 7.13.1)");
                break;
            case CURLE_TFTP_NOTFOUND:
                error = errors::New("File not found on TFTP server.");
                break;
            case CURLE_TFTP_PERM:
                error = errors::New("Permission problem on TFTP server.");
                break;
            case CURLE_REMOTE_DISK_FULL:
                error = errors::New("Out of disk space on the server.");
                break;
            case CURLE_TFTP_ILLEGAL:
                error = errors::New("Illegal TFTP operation.");
                break;
            case CURLE_TFTP_UNKNOWNID:
                error = errors::New("Unknown TFTP transfer ID.");
                break;
            case CURLE_REMOTE_FILE_EXISTS:
                error = errors::New("File already exists and is not overwritten.");
                break;
            case CURLE_TFTP_NOSUCHUSER:
                error = errors::New("This error should never be returned by a properly functioning TFTP server.");
                break;
            case CURLE_SSL_CACERT_BADFILE:
                error = errors::New("Problem with reading the SSL CA cert (path? access rights?)");
                break;
            case CURLE_REMOTE_FILE_NOT_FOUND:
                error = errors::New("The resource referenced in the URL does not exist.");
                break;
            case CURLE_SSH:
                error = errors::New("An unspecified error occurred during the SSH session.");
                break;
            case CURLE_SSL_SHUTDOWN_FAILED:
                error = errors::New("Failed to shut down the SSL connection.");
                break;
            case CURLE_AGAIN:
                error = errors::New("Socket is not ready for send/recv. Wait until it is ready and try again. This return code is only returned from curl_easy_recv and curl_easy_send (Added in 7.18.2)");
                break;
            case CURLE_SSL_CRL_BADFILE:
                error = errors::New("Failed to load CRL file (Added in 7.19.0)");
                break;
            case CURLE_SSL_ISSUER_ERROR:
                error = errors::New("Issuer check failed (Added in 7.19.0)");
                break;
            case CURLE_FTP_PRET_FAILED:
                error = errors::New("The FTP server does not understand the PRET command at all or does not support the given argument. Be careful when using CURLOPT_CUSTOMREQUEST, a custom LIST command is sent with the PRET command before PASV as well. (Added in 7.20.0)");
                break;
            case CURLE_RTSP_CSEQ_ERROR:
                error = errors::New("Mismatch of RTSP CSeq numbers.");
                break;
            case CURLE_RTSP_SESSION_ERROR:
                error = errors::New("Mismatch of RTSP Session Identifiers.");
                break;
            case CURLE_FTP_BAD_FILE_LIST:
                error = errors::New("Unable to parse FTP file list (during FTP wildcard downloading).");
                break;
            case CURLE_CHUNK_FAILED:
                error = errors::New("Chunk callback reported error.");
                break;
            case CURLE_NO_CONNECTION_AVAILABLE:
                error = errors::New("(For internal use only, is never returned by libcurl) No connection available, the session is queued. (added in 7.30.0)");
                break;
            case CURLE_SSL_PINNEDPUBKEYNOTMATCH:
                error = errors::New("Failed to match the pinned key specified with CURLOPT_PINNEDPUBLICKEY.");
                break;
            case CURLE_SSL_INVALIDCERTSTATUS:
                error = errors::New("Status returned failure when asked with CURLOPT_SSL_VERIFYSTATUS.");
                break;
            case CURLE_HTTP2_STREAM:
                error = errors::New("Stream error in the HTTP/2 framing layer.");
                break;
            case CURLE_RECURSIVE_API_CALL:
                error = errors::New("An API function was called from inside a callback.");
                break;
            case CURLE_AUTH_ERROR:
                error = errors::New("An authentication function returned an error.");
                break;
            case CURLE_HTTP3:
                error = errors::New("A problem was detected in the HTTP/3 layer. This is somewhat generic and can be one out of several problems, see the error buffer for details.");
                break;
            case CURLE_QUIC_CONNECT_ERROR:
                error = errors::New("QUIC connection error. This error may be caused by an SSL library error. QUIC is the protocol used for HTTP/3 transfers.");
                break;
            case CURLE_PROXY:
                error = errors::New("Proxy handshake error. CURLINFO_PROXY_ERROR provides extra details on the specific problem.");
                break;
            case CURLE_SSL_CLIENTCERT:
                error = errors::New("SSL Client Certificate required.");
                break;
            case CURLE_UNRECOVERABLE_POLL:
                error = errors::New("An internal call to poll() or select() returned error that is not recoverable.");
                break;
            case CURLE_TOO_LARGE:
                error = errors::New("A value or data field grew larger than allowed.");
                break;
            case CURLE_OBSOLETE20:
            case CURLE_OBSOLETE24:
            case CURLE_OBSOLETE29:
            case CURLE_OBSOLETE32:
            case CURLE_HTTP_POST_ERROR:
            case CURLE_OBSOLETE40:
            case CURLE_FUNCTION_NOT_FOUND:
            case CURLE_OBSOLETE44:
            case CURLE_OBSOLETE46:
            case CURLE_OBSOLETE50:
            case CURLE_OBSOLETE51:
            case CURLE_OBSOLETE57:
            case CURLE_OBSOLETE62:
            case CURLE_OBSOLETE75:
            case CURLE_OBSOLETE76:
            case CURL_LAST:
            default:
                error = errors::New("Unknown CURL error: either obsolete or unhandled.");
            }

            return error;
        }
    }

    namespace http {
        typedef std::map<std::string, std::vector<std::string>> header;
        typedef std::map<std::string, std::vector<std::string>> values;

        namespace go {
            struct response;
            struct request;

            struct user_info {
                std::string username;
                std::string password;
                bool isset;
            };

            struct url {
                std::string scheme;
                std::string opaque;
                go::user_info user;
                std::string host;
                std::string path;
                std::string raw_path;
                bool omit_host;
                bool force_query;
                std::string raw_query;
                std::string fragment;
                std::string raw_fragment;
            };

            struct request {
                std::string method;

                go::url *url;

                std::string proto;
                int proto_major;
                int proto_minor;

                http::header header;

                int64_t content_length;

                std::vector<std::string> transfer_encoding;

                bool close;

                std::string host;

                http::values form;

                http::values post_form;

                http::header trailer;

                std::string remote_addr;

                std::string request_uri;

                go::response *response;

                std::string pattern;
            };

            struct response {
                std::string status;
                int         status_code;
                std::string proto;
                int         proto_major;
                int         proto_minor;

                http::header header;

                int64_t content_length;

                std::vector<std::string> transfer_encoding;

                bool close;

                bool uncompressed;

                http::header trailer;

                go::request *request;
            };

        }

        struct response {
            std::string url;
            std::string data;
            long        response_code;
            double      time_elapsed;
        };

        std::ostream& operator<<(std::ostream& out, http::response& res) {
            std::string flat(res.data);
            flat.erase(std::remove(flat.begin(), flat.end(), '\n'), flat.cend());
            flat.erase(std::remove(flat.begin(), flat.end(), ' '), flat.cend());

            out << "{\n"
                << "\turl: \"" << res.url << "\",\n"
                << "\tdata: [\n"
                << "\t\t\"" << flat << "\",\n"
                << "\t],\n"
                << "\tresponse_code: " << res.response_code << ",\n"
                << "\time_elapsed: " << res.time_elapsed << ",\n"
                << "}";

                return out;
        }

        std::tuple<http::response*, error> get(std::string url) {
            CURL    *curl;
            CURLcode res;

            char   *effurlcstr;
            char   *response_data;
            curl_off_t response_length;
            long    response_code;
            double  time_elapsed;

            size_t (*func)(void*, size_t, size_t, char **) = [](
                void *ptr,
                size_t size,
                size_t nmemb,
                char **out_data)->size_t
            {
                *out_data = (char*)malloc(size * nmemb);
                assert(*out_data != NULL);
                memcpy(*out_data, ptr, size * nmemb);
                return size * nmemb;
            };

            curl = curl_easy_init();
            if(curl) {
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_CA_CACHE_TIMEOUT, 604800L);
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, func);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
                res = curl_easy_perform(curl);
                curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD_T, &response_length);
                curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &effurlcstr);
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
                curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &time_elapsed);

                // C++11
                if(res != CURLE_OK) {
                    return std::make_tuple(nullptr, errors::New(res));
                }

                http::response *response = new http::response{
                    .url = std::string(effurlcstr),
                    .data = std::string(response_data, response_length),
                    .response_code = response_code,
                    .time_elapsed = time_elapsed,
                };

                curl_easy_cleanup(curl);
                // curl_global_cleanup();

                // OK
                return std::make_tuple(response, nullptr);
            }

            // FAIL
            return std::make_tuple(nullptr, errors::New(CURLE_FAILED_INIT));
        }
    }
}

#endif // CEX_HTTP

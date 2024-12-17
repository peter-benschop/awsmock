//
// Created by vogje01 on 12/17/24.
//

#ifndef AWSMOCK_SERVICE_FRONTEND_HTTP_WORKER_H
#define AWSMOCK_SERVICE_FRONTEND_HTTP_WORKER_H

// C++ standard includes
#include <string>
#include <utility>

// Boost includes
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core/flat_static_buffer.hpp>
#include <boost/beast/http/parser.hpp>
#include <boost/beast/http/read.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/beast/http/write.hpp>

// AwsMock includes
#include <awsmock/service/frontend/FieldAlloc.h>
#include <boost/beast/http/file_body.hpp>
#include <boost/beast/http/serializer.hpp>

namespace beast = boost::beast;  // from <boost/beast.hpp>
namespace http = beast::http;    // from <boost/beast/http.hpp>
namespace net = boost::asio;     // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;// from <boost/asio/ip/tcp.hpp>

#define DEFAULT_PAGE std::string("/index.html")

// Return a reasonable mime type based on the extension of a file.
inline beast::string_view mime_type(beast::string_view path) {
    using beast::iequals;
    auto const ext = [&path] {
        auto const pos = path.rfind(".");
        if (pos == beast::string_view::npos)
            return beast::string_view{};
        return path.substr(pos);
    }();
    if (iequals(ext, ".htm")) return "text/html";
    if (iequals(ext, ".html")) return "text/html";
    if (iequals(ext, ".php")) return "text/html";
    if (iequals(ext, ".css")) return "text/css";
    if (iequals(ext, ".txt")) return "text/plain";
    if (iequals(ext, ".js")) return "application/javascript";
    if (iequals(ext, ".json")) return "application/json";
    if (iequals(ext, ".xml")) return "application/xml";
    if (iequals(ext, ".swf")) return "application/x-shockwave-flash";
    if (iequals(ext, ".flv")) return "video/x-flv";
    if (iequals(ext, ".png")) return "image/png";
    if (iequals(ext, ".jpe")) return "image/jpeg";
    if (iequals(ext, ".jpeg")) return "image/jpeg";
    if (iequals(ext, ".jpg")) return "image/jpeg";
    if (iequals(ext, ".gif")) return "image/gif";
    if (iequals(ext, ".bmp")) return "image/bmp";
    if (iequals(ext, ".ico")) return "image/vnd.microsoft.icon";
    if (iequals(ext, ".tiff")) return "image/tiff";
    if (iequals(ext, ".tif")) return "image/tiff";
    if (iequals(ext, ".svg")) return "image/svg+xml";
    if (iequals(ext, ".svgz")) return "image/svg+xml";
    return "text/html";
}

namespace AwsMock::Service::Frontend {

    class HttpWorker {

      public:

        /**
         * @brief Constructor
         *
         * @param acceptor request acceptor
         * @param docRoot document root directory
         */
        HttpWorker(boost::asio::ip::tcp::acceptor &acceptor, std::string docRoot) : _acceptor(acceptor), _docRoot(std::move(docRoot)) {}

        /**
         * @brief Copy constructor
         *
         * @param worker worker to copy from
         */
        HttpWorker(HttpWorker const &worker) = delete;

        /**
         * @brief Assignment constructor
         *
         * @param worker worker to assign from
         * @return assigned worker
         */
        HttpWorker &operator=(HttpWorker const &worker) = delete;

        /**
         * @brief Start the server
         */
        void Start();

      private:

        using alloc_t = fields_alloc<char>;

        using request_body_t = http::string_body;

        void Accept();

        void ReadRequest();

        void ProcessRequest(http::request<request_body_t, http::basic_fields<alloc_t>> const &req);

        void SendBadResponse(http::status status, std::string const &error);

        void SendFile(beast::string_view target);

        void CheckDeadline();

        // The acceptor used to listen for incoming connections.
        tcp::acceptor &_acceptor;

        // The path to the root of the document directory.
        std::string _docRoot;

        // The socket for the currently connected client.
        tcp::socket _socket{_acceptor.get_executor()};

        // The buffer for performing reads
        beast::flat_static_buffer<8192> _buffer;

        // The allocator used for the fields in the request and reply.
        alloc_t _alloc{8192};

        // The parser for reading the requests
        boost::optional<http::request_parser<request_body_t, alloc_t>> _parser;

        // The timer putting a time limit on requests.
        net::steady_timer _requestDeadline{_acceptor.get_executor(), (std::chrono::steady_clock::time_point::max) ()};

        // The string-based response message.
        boost::optional<http::response<http::string_body, http::basic_fields<alloc_t>>> _stringResponse;

        // The string-based response serializer.
        boost::optional<http::response_serializer<http::string_body, http::basic_fields<alloc_t>>> _stringSerializer;

        // The file-based response message.
        boost::optional<http::response<http::file_body, http::basic_fields<alloc_t>>> _fileResponse;

        // The file-based response serializer.
        boost::optional<http::response_serializer<http::file_body, http::basic_fields<alloc_t>>> _fileSerializer;
    };

}// namespace AwsMock::Service::Frontend

#endif// AWSMOCK_SERVICE_FRONTEND_HTTP_WORKER_H

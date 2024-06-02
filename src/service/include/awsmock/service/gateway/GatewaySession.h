//
// Created by vogje01 on 5/27/24.
//

#ifndef AWSMOCK_SERVICES_GATEWAY_SESSION_H
#define AWSMOCK_SERVICES_GATEWAY_SESSION_H

// C++ includes
#include <memory>
#include <queue>

// Boost includes
#include <boost/asio/dispatch.hpp>
#include <boost/beast.hpp>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/service/cognito/CognitoHandler.h>
#include <awsmock/service/common/AbstractHandler.h>
#include <awsmock/service/dynamodb/DynamoDbHandler.h>
#include <awsmock/service/gateway/GatewayHandler.h>
#include <awsmock/service/kms/KMSHandler.h>
#include <awsmock/service/lambda/LambdaHandler.h>
#include <awsmock/service/s3/S3Handler.h>
#include <awsmock/service/secretsmanager/SecretsManagerHandler.h>
#include <awsmock/service/sns/SNSHandler.h>
#include <awsmock/service/sqs/SQSHandler.h>
#include <awsmock/service/transfer/TransferHandler.h>

// Maximal body size (10MB)
#define DEFAULT_MAX_BODY_SIZE (10 * 1024 * 1024)
#define DEFAULT_MAX_QUEUE_SIZE 250
#define DEFAULT_TIMEOUT 300

namespace AwsMock::Service {

    namespace http = boost::beast::http;
    namespace ip = boost::asio::ip;

    /**
     * @brief HTTP session manager
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class GatewaySession : public std::enable_shared_from_this<GatewaySession> {

      public:

        /**
         * @brief HTTP session
         *
         * Takes ownership of the socket.
         *
         * @param socket
         */
        explicit GatewaySession(ip::tcp::socket &&socket);

        /**
         * @brief Start the session
         *
         * We need to be executing within a strand to perform async operations on the I/O objects in this session. Although not strictly necessary
         * for single-threaded contexts, this example code is written to be thread-safe by default.
         */
        void Run();

      private:

        /**
         * @brief Read callback
         */
        void DoRead();

        /**
         * @brief On read callback
         */
        void OnRead(boost::beast::error_code ec, std::size_t bytes_transferred);

        /**
         * @brief Queue write callback
         */
        void QueueWrite(http::message_generator response);

        /**
         * @brief Return a response for the given request.
         *
         * The concrete type of the response message (which depends on the request), is type-erased in message_generator.
         *
         * @tparam Body HTTP body
         * @tparam Allocator allocator
         * @param req HTTP request
         * @return
         */
        template<class Body, class Allocator>
        http::message_generator HandleRequest(http::request<Body, http::basic_fields<Allocator>> &&req);

        /**
         * @brief Called to start/continue the write-loop.
         *
         * Should not be called when write_loop is already active.
         */
        void DoWrite();

        /**
         * @brief On read callback
         *
         * @param keep_alive keep alive flag
         * @param ec error code
         * @param bytes_transferred number of bytes transferred
         */
        void OnWrite(bool keep_alive, boost::beast::error_code ec, std::size_t bytes_transferred);

        /**
         * @brief On clas callback
         */
        void DoClose();

        static Core::AuthorizationHeaderKeys GetAuthorizationKeys(const std::string &authorizationHeader, const std::string &secretAccessKey);

        /**
         * TCP stream
         */
        boost::beast::tcp_stream stream_;

        /**
         * Read buffer
         */
        boost::beast::flat_buffer buffer_;

        /**
         * Queue limit
         */
        std::size_t _queueLimit;

        /**
         * Mox body size
         */
        long _bodyLimit;

        /**
         * Request timeout
         */
        int _timeout;

        /**
         * HTTP request queue
         */
        std::queue<http::message_generator> response_queue_;

        /**
         * The parser is stored in an optional container so we can construct it from scratch it at the beginning of each new message.
         */
        boost::optional<http::request_parser<http::dynamic_body>> parser_;

        /**
         * HTTP request handler
         */
        GatewayHandler _handler;

        /**
         * Routine table
         */
        typedef std::map<std::string, std::shared_ptr<AbstractHandler>> RoutingTable;
        static RoutingTable _routingTable;
    };


}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICES_GATEWAY_SESSION_H

//
// Created by vogje01 on 02/09/2022.
//

#ifndef AWS_MOCK_CORE_DATABASE_EXCEPTION_H
#define AWS_MOCK_CORE_DATABASE_EXCEPTION_H

// Boost includes
#include <boost/beast/http.hpp>

namespace AwsMock::Core {

    namespace http = boost::beast::http;

    /**
     * @brief Database exception class.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class DatabaseException final : public std::exception {

      public:

        /**
       * Constructor.
       *
       * @param code exception code, default: 0
       * @param resource exception resource
       * @param requestId exception resource ID
       */
        explicit DatabaseException(http::status code = http::status::internal_server_error, const char *resource = nullptr, const char *requestId = nullptr);

        /**
       * Constructor.
       *
       * @param msg exception message
       * @param code exception code, default: 0
       * @param resource exception resource
       * @param requestId exception resource ID
       */
        explicit DatabaseException(const std::string &msg, http::status code = http::status::internal_server_error, const char *resource = nullptr, const char *requestId = nullptr);

        /**
       * Copy constructor.
       *
       * @param exc parent exception.
       */
        DatabaseException(const DatabaseException &exc);

        /**
       * Destructor
       */
        ~DatabaseException() noexcept override;

        /**
       * Assigment operator.
       */
        DatabaseException &operator=(const DatabaseException &exc);

        /**
       * Returns the exception message.
       */
        [[nodiscard]] std::string message() const noexcept;

        /**
       * Returns the exception message.
       */
        [[nodiscard]] http::status code() const noexcept;

        /**
       * Returns the exception resource.
       */
        [[nodiscard]] const char *resource() const noexcept;

        /**
       * Returns the exception request ID.
       */
        [[nodiscard]] const char *requestId() const noexcept;

      private:

        /**
       * Code
       */
        const http::status _code;

        /**
       * Message
       */
        std::string _message;

        /**
       * Resource
       */
        const char *_resource;

        /**
       * Request ID
       */
        const char *_requestId;
    };

}// namespace AwsMock::Core

#endif//AWS_MOCK_CORE_DATABASE_EXCEPTION_H

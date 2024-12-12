//
// Created by vogje01 on 02/09/2022.
//

#ifndef AWS_MOCK_CORE_CORE_EXCEPTION_H
#define AWS_MOCK_CORE_CORE_EXCEPTION_H

// C++ includes
#include <string>

// Boost includes
#include <boost/beast/http.hpp>
#include <utility>

namespace AwsMock::Core {

    /**
     * @brief Exception class. In case of a COM request failure a COMException is thrown.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class CoreException final : public std::exception {

      public:

        /**
         * Constructor.
         *
         * @param code exception code, default: 0
         */
        explicit CoreException(const boost::beast::http::status code = boost::beast::http::status::internal_server_error) : _code(code) {}

        /**
         * Constructor.
         *
         * @param msg exception message
         * @param code exception code, default: 0
         */
        explicit CoreException(std::string msg, const boost::beast::http::status code = boost::beast::http::status::internal_server_error) : _code(code), _message(std::move(msg)) {}

        /**
         * Copy constructor.
         *
         * @param exc parent exception.
         */
        CoreException(const CoreException &exc);

        /**
         * Destructor
         */
        ~CoreException() noexcept override;

        /**
         * Assigment operator.
         */
        CoreException &operator=(const CoreException &exc);

        /**
         * Return message
         */
        std::string message() const { return _message; }

        /**
         * Return code
         */
        [[nodiscard]] boost::beast::http::status code() const { return _code; }

        /**
         * Http status code
         */
        boost::beast::http::status _code;

        /**
       * Http status code
       */
        std::string _message;
        ;
    };

}// namespace AwsMock::Core

#endif//AWS_MOCK_CORE_CORE_EXCEPTION_H

//
// Created by vogje01 on 02/09/2022.
//

#ifndef AWS_MOCK_CORE_DATABASE_EXCEPTION_H
#define AWS_MOCK_CORE_DATABASE_EXCEPTION_H

#include <Poco/Exception.h>
#include <Poco/Net/HTTPResponse.h>

namespace AwsMock::Core {

    /**
   * Database exception class.
   *
   * @author jens.vogt@opitz-consulting.com
   */
    class DatabaseException : public Poco::Exception {
      public:
        /**
     * Constructor.
     *
     * @param code exception code, default: 0
     */
        explicit DatabaseException(int code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR);

        /**
     * Constructor.
     *
     * @param msg exception message
     * @param code exception code, default: 0
     */
        explicit DatabaseException(const std::string &msg, int code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR);

        /**
     * Constructor.
     *
     * @param msg exception message
     * @param arg exception argument, will be appended to the message, separated with a ':'.
     * @param code exception code, default: 0
     */
        DatabaseException(const std::string &msg, const std::string &arg, int code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR);

        /**
     * Constructor.
     *
     * @param msg exception message
     * @param exc parent exception.
     * @param code exception code, default: 0
     */
        DatabaseException(const std::string &msg, const Poco::Exception &exc, int code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR);

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
     * Returns the exception name.
     */
        [[nodiscard]] const char *name() const noexcept override;

        /**
     * Returns the exception class name.
     */
        [[nodiscard]] const char *className() const noexcept override;

        /**
     * Returns a clone of the exception
     */
        [[nodiscard]] Poco::Exception *clone() const override;

        /**
     * Rethrows the exception.
     */
        void rethrow() const override;
    };

}// namespace AwsMock::Core

#endif//AWS_MOCK_CORE_DATABASE_EXCEPTION_H

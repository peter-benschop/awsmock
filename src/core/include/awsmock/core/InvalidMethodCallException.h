//
// Created by vogje01 on 18/03/2024.
//

#ifndef AWSMOCK_CORE_INVALID_METHOD_CALL_EXCEPTION_H
#define AWSMOCK_CORE_INVALID_METHOD_CALL_EXCEPTION_H

// Poco includes
#include <Poco/Exception.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerResponse.h>

namespace AwsMock::Core {

  /**
   * Invalid method call exception. Can be thrown when a method should not be used anymore.
   *
   * @author jens.vogt@opitz-consulting.com
   */
  class InvalidMethodCallException : public Poco::Exception {

  public:
    /**
     * Constructor.
     *
     * @param code exception code, default: 0
     * @param resource exception resource
     * @param requestId exception resource ID
     */
    explicit InvalidMethodCallException(int code = 0, const char *resource = nullptr, const char *requestId = nullptr);

    /**
     * Constructor.
     *
     * @param msg exception message
     * @param code exception code, default: 0
     * @param resource exception resource
     * @param requestId exception resource ID
     */
    explicit InvalidMethodCallException(const std::string &msg, int code = 0, const char *resource = nullptr, const char *requestId = nullptr);

    /**
     * Constructor.
     *
     * @param msg exception message
     * @param arg exception argument, will be appended to the message, separated with a ':'.
     * @param code exception code, default: 0
     * @param resource exception resource
     * @param requestId exception resource ID
     */
    InvalidMethodCallException(const std::string &msg, const std::string &arg, int code = 0, const char *resource = nullptr, const char *requestId = nullptr);

    /**
     * Constructor.
     *
     * @param msg exception message
     * @param exc parent exception.
     * @param code exception code, default: 0
     * @param resource exception resource
     * @param requestId exception resource ID
     */
    InvalidMethodCallException(const std::string &msg, const Poco::Exception &exc, int code = 0, const char *resource = nullptr, const char *requestId = nullptr);

    /**
     * Copy constructor.
     *
     * @param exc parent exception.
     */
    InvalidMethodCallException(const InvalidMethodCallException &exc);

    /**
     * Destructor
     */
    ~InvalidMethodCallException() noexcept override;

    /**
     * Assigment operator.
     */
    InvalidMethodCallException &operator=(const InvalidMethodCallException &exc);

    /**
     * Returns the exception name.
     */
    [[nodiscard]] const char *name() const noexcept override;

    /**
     * Returns the exception class name.
     */
    [[nodiscard]] const char *className() const noexcept override;

    /**
     * Returns the exception resource.
     */
    [[nodiscard]] const char *resource() const noexcept;

    /**
     * Returns the exception request ID.
     */
    [[nodiscard]] const char *requestId() const noexcept;

    /**
     * Returns a clone of the exception
     */
    [[nodiscard]] Poco::Exception *clone() const override;

    /**
     * Rethrows the exception.
     */
    void rethrow() const override;

  private:

    /**
     * Resource
     */
    const char *_resource;

    /**
     * Request ID
     */
    const char *_requestId;

  };

} // namespace AwsMock::Core

#endif // AWSMOCK_CORE_INVALID_METHOD_CALL_EXCEPTION_H

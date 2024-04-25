//
// Created by vogje01 on 02/09/2022.
//

#include <awsmock/core/InvalidMethodCallException.h>

namespace AwsMock::Core {

    InvalidMethodCallException::InvalidMethodCallException(int code, const char *resource, const char *requestId) : Poco::Exception(code), _resource(resource), _requestId(requestId) {}

    InvalidMethodCallException::InvalidMethodCallException(const std::string &msg, int code, const char *resource, const char *requestId) : Poco::Exception(msg, code), _resource(resource), _requestId(requestId) {}

    InvalidMethodCallException::InvalidMethodCallException(const std::string &msg, const std::string &arg, int code, const char *resource, const char *requestId) : Poco::Exception(msg, arg, code), _resource(resource), _requestId(requestId) {}

    InvalidMethodCallException::InvalidMethodCallException(const std::string &msg, const Poco::Exception &exc, int code, const char *resource, const char *requestId) : Poco::Exception(msg, exc, code), _resource(resource), _requestId(requestId) {}

    InvalidMethodCallException::InvalidMethodCallException(const InvalidMethodCallException &exc) = default;

    InvalidMethodCallException::~InvalidMethodCallException() noexcept = default;

    InvalidMethodCallException &InvalidMethodCallException::operator=(const InvalidMethodCallException &exc) = default;

    const char *InvalidMethodCallException::name() const noexcept { return "InvalidMethodCallException: "; }

    const char *InvalidMethodCallException::className() const noexcept { return typeid(*this).name(); }

    const char *InvalidMethodCallException::resource() const noexcept { return _resource; }

    const char *InvalidMethodCallException::requestId() const noexcept { return _requestId; }

    Poco::Exception *InvalidMethodCallException::clone() const { return new InvalidMethodCallException(*this); }

    void InvalidMethodCallException::rethrow() const { throw *this; }

}// namespace AwsMock::Core
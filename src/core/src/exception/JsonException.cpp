//
// Created by vogje01 on 02/09/2022.
//

#include <awsmock/core/JsonException.h>

namespace AwsMock::Core {

    JsonException::JsonException(int code, const char *resource, const char *requestId) : Poco::Exception(code), _resource(resource), _requestId(requestId) {}

    JsonException::JsonException(const std::string &msg, int code, const char *resource, const char *requestId) : Poco::Exception(msg, code), _resource(resource), _requestId(requestId) {}

    JsonException::JsonException(const std::string &msg, const std::string &arg, int code, const char *resource, const char *requestId) : Poco::Exception(msg, arg, code), _resource(resource), _requestId(requestId) {}

    JsonException::JsonException(const std::string &msg, const Poco::Exception &exc, int code, const char *resource, const char *requestId) : Poco::Exception(msg, exc, code), _resource(resource), _requestId(requestId) {}

    JsonException::JsonException(const JsonException &exc) = default;

    JsonException::~JsonException() noexcept = default;

    JsonException &JsonException::operator=(const JsonException &exc) = default;

    const char *JsonException::name() const noexcept { return "JsonException: "; }

    const char *JsonException::className() const noexcept { return typeid(*this).name(); }

    const char *JsonException::resource() const noexcept { return _resource; }

    const char *JsonException::requestId() const noexcept { return _requestId; }

    Poco::Exception *JsonException::clone() const { return new JsonException(*this); }

    void JsonException::rethrow() const { throw *this; }

}// namespace AwsMock::Core
//
// Created by vogje01 on 02/09/2022.
//

#include "awsmock/core/ServiceException.h"

namespace AwsMock::Core {

    ServiceException::ServiceException(int code, const char *resource, const char *requestId) : Poco::Exception(code), _resource(resource), _requestId(requestId) {}

    ServiceException::ServiceException(const std::string &msg, int code, const char *resource, const char *requestId) : Poco::Exception(msg, code), _resource(resource), _requestId(requestId) {}

    ServiceException::ServiceException(const std::string &msg, const std::string &arg, int code, const char *resource, const char *requestId) : Poco::Exception(msg, arg, code), _resource(resource), _requestId(requestId) {}

    ServiceException::ServiceException(const std::string &msg, const Poco::Exception &exc, int code, const char *resource, const char *requestId) : Poco::Exception(msg, exc, code), _resource(resource), _requestId(requestId) {}

    ServiceException::ServiceException(const ServiceException &exc) = default;

    ServiceException::~ServiceException() noexcept = default;

    ServiceException &ServiceException::operator=(const ServiceException &exc) = default;

    const char *ServiceException::name() const noexcept { return "ServiceException: "; }

    const char *ServiceException::className() const noexcept { return typeid(*this).name(); }

    const char *ServiceException::resource() const noexcept { return _resource; }

    const char *ServiceException::requestId() const noexcept { return _requestId; }

    Poco::Exception *ServiceException::clone() const { return new ServiceException(*this); }

    void ServiceException::rethrow() const { throw *this; }

    Poco::Net::HTTPResponse::HTTPStatus status() { return Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR; }

}// namespace AwsMock::Core
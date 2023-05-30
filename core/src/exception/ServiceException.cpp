//
// Created by vogje01 on 02/09/2022.
//

#include "awsmock/core/ServiceException.h"

namespace AwsMock::Core {

    ServiceException::ServiceException(int code) : Poco::Exception(code) {}

    ServiceException::ServiceException(const std::string &msg, int code) : Poco::Exception(msg, code) {}

    ServiceException::ServiceException(const std::string &msg, const std::string &arg, int code) : Poco::Exception(msg, arg, code) {}

    ServiceException::ServiceException(const std::string &msg, const Poco::Exception &exc, int code) : Poco::Exception(msg, exc, code) {}

    ServiceException::ServiceException(const ServiceException &exc) = default;

    ServiceException::~ServiceException() noexcept = default;

    ServiceException &ServiceException::operator=(const ServiceException &exc) = default;

    const char *ServiceException::name() const noexcept { return "ServiceException: "; }

    const char *ServiceException::className() const noexcept { return typeid(*this).name(); }

    Poco::Exception *ServiceException::clone() const { return new ServiceException(*this); }

    void ServiceException::rethrow() const { throw *this; }

} // namespace Libri::AWS
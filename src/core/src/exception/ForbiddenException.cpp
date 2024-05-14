//
// Created by vogje01 on 02/09/2022.
//

#include "awsmock/core/exception/ForbiddenException.h"

namespace AwsMock::Core {

    ForbiddenException::ForbiddenException(int code) : Poco::Exception(code) {
    }

    ForbiddenException::ForbiddenException(const std::string &msg, int code) : Poco::Exception(msg, code) {
    }

    ForbiddenException::ForbiddenException(const ForbiddenException &exc) = default;

    ForbiddenException::~ForbiddenException() noexcept = default;

    ForbiddenException &ForbiddenException::operator=(const ForbiddenException &exc) {
        Poco::Exception::operator=(exc);
        return *this;
    }

    void ForbiddenException::rethrow() const { throw *this; }

}// namespace AwsMock::Core
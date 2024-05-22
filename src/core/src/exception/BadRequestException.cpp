//
// Created by vogje01 on 02/09/2022.
//

#include <awsmock/core/exception/BadRequestException.h>

namespace AwsMock::Core {

    BadRequestException::BadRequestException(int code) : Poco::Exception(code) {
    }

    BadRequestException::BadRequestException(const std::string &msg, int code) : Poco::Exception(msg, code) {
    }

    BadRequestException::BadRequestException(const BadRequestException &exc) = default;

    BadRequestException::~BadRequestException() noexcept = default;

    BadRequestException &BadRequestException::operator=(const BadRequestException &exc) {
        Poco::Exception::operator=(exc);
        return *this;
    }

    void BadRequestException::rethrow() const { throw *this; }

}// namespace AwsMock::Core
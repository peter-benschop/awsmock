//
// Created by vogje01 on 02/09/2022.
//

#include <awsmock/core/exception/UnauthorizedException.h>

namespace AwsMock::Core {

    UnauthorizedException::UnauthorizedException(int code) : Poco::Exception(code) {
    }

    UnauthorizedException::UnauthorizedException(const std::string &msg, int code) : Poco::Exception(msg, code) {
    }

    UnauthorizedException::UnauthorizedException(const UnauthorizedException &exc) = default;

    UnauthorizedException::~UnauthorizedException() noexcept = default;

    UnauthorizedException &UnauthorizedException::operator=(const UnauthorizedException &exc) {
        Poco::Exception::operator=(exc);
        return *this;
    }

    void UnauthorizedException::rethrow() const { throw *this; }

}// namespace AwsMock::Core
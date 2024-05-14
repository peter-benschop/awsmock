//
// Created by vogje01 on 02/09/2022.
//

#include "awsmock/core/exception/NotFoundException.h"

namespace AwsMock::Core {

    NotFoundException::NotFoundException(int code) : Poco::Exception(code) {
    }

    NotFoundException::NotFoundException(const std::string &msg, int code) : Poco::Exception(msg, code) {
    }

    NotFoundException::NotFoundException(const NotFoundException &exc) = default;

    NotFoundException::~NotFoundException() noexcept = default;

    NotFoundException &NotFoundException::operator=(const NotFoundException &exc) {
        Poco::Exception::operator=(exc);
        return *this;
    }

    void NotFoundException::rethrow() const { throw *this; }

}// namespace AwsMock::Core
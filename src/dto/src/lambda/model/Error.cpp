//
// Created by vogje01 on 4/30/24.
//

#include "awsmock/dto/lambda/model/Error.h"

namespace AwsMock::Dto::Lambda {

    std::string Error::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Error &r) {
        os << "Error={errorCode='" + r.errorCode + "' message='" + r.message + "'}";
        return os;
    }


}// namespace AwsMock::Dto::Lambda

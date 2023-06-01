//
// Created by vogje01 on 30/05/2023.
//

#include "awsmock/dto/s3/GetObjectResponse.h"

namespace AwsMock::Dto::S3 {

    std::string GetObjectResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetObjectResponse &p) {
        os << "GetObjectResponse={bucket='" + p._bucket + "' key='" + p._key + "'}";
        return os;
    }
}
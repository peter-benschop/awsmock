//
// Created by vogje01 on 30/05/2023.
//

#include "awsmock/dto/s3/PutObjectResponse.h"

namespace AwsMock::Dto::S3 {

    std::string PutObjectResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const PutObjectResponse &p) {
        os << "PutObjectResponse={bucket='" + p._bucket + "' key='" + p._key + "' etag='" + p._etag + "''}";
        return os;
    }
}
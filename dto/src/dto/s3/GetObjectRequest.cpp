//
// Created by vogje01 on 30/05/2023.
//

#include "awsmock/dto/s3/GetObjectRequest.h"

namespace AwsMock::Dto::S3 {

    std::string GetObjectRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetObjectRequest &p) {
        os << "GetObjectRequest={bucket='" + p._bucket + "' key='" + p._key + "'}";
        return os;
    }
}
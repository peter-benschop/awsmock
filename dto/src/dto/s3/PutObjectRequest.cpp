//
// Created by vogje01 on 30/05/2023.
//

#include "awsmock/dto/s3/PutObjectRequest.h"

namespace AwsMock::Dto::S3 {

    std::string PutObjectRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const PutObjectRequest &p) {
        os << "PutObjectRequest={bucket='" + p._bucket + "' key='" + p._key + "' md5sum='" + p._md5Sum + "' contentType='" + p._contentType
            + "' size: '" + std::to_string(p._size) + "' owner='" + p._owner + "' region='" + p._region + "'}";
        return os;
    }
}
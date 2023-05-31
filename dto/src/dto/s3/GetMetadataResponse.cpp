//
// Created by vogje01 on 30/05/2023.
//

#include "awsmock/dto/s3/GetMetadataResponse.h"

namespace AwsMock::Dto::S3 {

    std::string GetMetadataResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetMetadataResponse &r) {
        os << "GetMetadataResponse={bucket='" + r._bucket + "' key='" + r._key + "' md5sum='" + r._md5Sum + "' contentType='" + r._contentType
            + "' size='" + std::to_string(r._size) + "'}";
        return os;
    }
}
//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/MoveObjectRequest.h>

namespace AwsMock::Dto::S3 {

    std::string MoveObjectRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const MoveObjectRequest &r) {
        os << "MoveObjectRequest={region='" << r.region << "' user='" << r.user << "' sourceBucket='" << r.sourceBucket << "' sourceKey='" << r.sourceKey
           << "' targetBucket='" << r.targetBucket << "' targetKey='" << r.targetKey << "' metadata={";
        for (const auto &m: r.metadata) {
            os << m.first << "=" << m.second << ", ";
        }
        os << "\b\b"
           << "}}";
        return os;
    }

}// namespace AwsMock::Dto::S3

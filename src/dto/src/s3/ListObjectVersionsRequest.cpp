//
// Created by vogje01 on 31/05/2023.
//

#include <awsmock/dto/s3/ListObjectVersionsRequest.h>

namespace AwsMock::Dto::S3 {

    std::string ListObjectVersionsRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("bucket", bucket);
            rootJson.set("prefix", prefix);
            rootJson.set("delimiter", prefix);
            rootJson.set("encodingType", encodingType);
            rootJson.set("maxKeys", maxKeys);
            rootJson.set("versionIdMarker", versionIdMarker);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListObjectVersionsRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListObjectVersionsRequest &r) {
        os << "ListObjectVersionsRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3

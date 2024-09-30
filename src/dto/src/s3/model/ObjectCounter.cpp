//
// Created by vogje01 on 12/18/23.
//

#include <awsmock/dto/s3/model/ObjectCounter.h>

namespace AwsMock::Dto::S3 {

    std::string ObjectCounter::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("bucketName", bucketName);
            rootJson.set("key", key);
            rootJson.set("size", size);
            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ObjectCounter::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ObjectCounter &c) {
        os << "ObjectCounter=" << c.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3

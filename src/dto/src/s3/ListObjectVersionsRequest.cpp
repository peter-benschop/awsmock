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

            std::ostringstream os;
            rootJson.stringify(os);
            return os.str();

        } catch (Poco::Exception &exc) {
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

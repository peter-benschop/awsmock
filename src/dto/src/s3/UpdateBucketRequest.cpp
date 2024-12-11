//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/UpdateBucketRequest.h>

namespace AwsMock::Dto::S3 {

    UpdateBucketRequest UpdateBucketRequest::FromJson(const std::string &body) {

        try {
            UpdateBucketRequest request;
            if (const value document = bsoncxx::from_json(body); document.view().find("bucket") != document.view().end()) {
                request.bucket.FromDocument(document.view()["bucket"].get_document().value);
            }
            return request;

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string UpdateBucketRequest::ToJson() const {

        try {

            document document;
            document.append(kvp("bucket", bucket.ToDocument()));
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string UpdateBucketRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UpdateBucketRequest &r) {
        os << "UpdateBucketRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3

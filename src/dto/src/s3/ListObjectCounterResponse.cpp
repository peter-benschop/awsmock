
#include <awsmock/dto/s3/ListObjectCounterResponse.h>

namespace AwsMock::Dto::S3 {

    std::string ListObjectCounterResponse::ToJson() const {

        try {

            document rootDocument;
            Core::Bson::BsonUtils::SetLongValue(rootDocument, "total", total);

            // Contents
            if (!objectCounters.empty()) {

                array jsonObjectArray;
                for (const auto &[oid, bucketName, key, contentType, size]: objectCounters) {
                    document jsonObject;
                    Core::Bson::BsonUtils::SetStringValue(rootDocument, "oid", oid);
                    Core::Bson::BsonUtils::SetStringValue(rootDocument, "bucketName", bucketName);
                    Core::Bson::BsonUtils::SetStringValue(rootDocument, "key", key);
                    Core::Bson::BsonUtils::SetLongValue(rootDocument, "size", size);
                    Core::Bson::BsonUtils::SetStringValue(rootDocument, "contentType", contentType);
                    jsonObjectArray.append(jsonObject);
                }
                rootDocument.append(kvp("objectCounters", jsonObjectArray));
            }
            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    [[nodiscard]] std::string ListObjectCounterResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListObjectCounterResponse &r) {
        os << "ListObjectCounterResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
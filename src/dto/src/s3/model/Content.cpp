//
// Created by vogje01 on 12/18/23.
//

#include <awsmock/dto/s3/model/Content.h>

namespace AwsMock::Dto::S3 {

    std::string Content::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "etag", etag);
            Core::Bson::BsonUtils::SetStringValue(document, "key", key);
            Core::Bson::BsonUtils::SetLongValue(document, "size", size);
            Core::Bson::BsonUtils::SetStringValue(document, "storageClass", storageClass);
            Core::Bson::BsonUtils::SetDateValue(document, "modified", modified);

            document.append(kvp("owner", owner.ToDocument()));

            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string Content::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Content &c) {
        os << "Content=" << c.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3

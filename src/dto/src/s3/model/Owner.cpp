//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/model/Owner.h>

namespace AwsMock::Dto::S3 {

    std::string Owner::ToJson() const {

        try {

            document rootDocument;
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "id", id);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "displayName", displayName);
            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> Owner::ToDocument() const {

        try {

            document document;

            Core::Bson::BsonUtils::SetStringValue(document, "id", id);
            Core::Bson::BsonUtils::SetStringValue(document, "displayName", displayName);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string Owner::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Owner &o) {
        os << "Owner=" << o.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3

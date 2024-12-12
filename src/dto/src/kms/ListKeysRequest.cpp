//
// Created by vogje01 on 4/25/24.
//

#include <awsmock/dto/kms/ListKeysRequest.h>

namespace AwsMock::Dto::KMS {

    void ListKeysRequest::FromJson(const std::string &jsonString) {

        try {

            const value document = bsoncxx::from_json(jsonString);
            marker = Core::Bson::BsonUtils::GetStringValue(document, "Marker");
            limit = Core::Bson::BsonUtils::GetIntValue(document, "Limit");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListKeysRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Marker", marker);
            Core::Bson::BsonUtils::SetIntValue(document, "Limit", limit);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListKeysRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListKeysRequest &r) {
        os << "ListKeysRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::KMS

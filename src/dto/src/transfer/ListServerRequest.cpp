//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/transfer/ListServerRequest.h>

namespace AwsMock::Dto::Transfer {

    std::string ListServerRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetIntValue(document, "MaxResults", maxResults);
            Core::Bson::BsonUtils::SetStringValue(document, "NextToken", nextToken);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void ListServerRequest::FromJson(const std::string &jsonString) {

        try {
            const value rootDocument = bsoncxx::from_json(jsonString);
            region = Core::Bson::BsonUtils::GetStringValue(rootDocument, "Region");
            maxResults = Core::Bson::BsonUtils::GetIntValue(rootDocument, "MaxResults");
            nextToken = Core::Bson::BsonUtils::GetIntValue(rootDocument, "NextToken");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListServerRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListServerRequest &r) {
        os << "ListServerRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Transfer

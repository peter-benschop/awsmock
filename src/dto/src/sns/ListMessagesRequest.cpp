//
// Created by vogje01 on 10/9/24.
//

#include <awsmock/dto/sns/ListMessagesRequest.h>

namespace AwsMock::Dto::SNS {

    std::string ListMessagesRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "topicArn", topicArn);
            Core::Bson::BsonUtils::SetIntValue(document, "pageSize", pageSize);
            Core::Bson::BsonUtils::SetIntValue(document, "pageIndex", pageIndex);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void ListMessagesRequest::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);

            region = Core::Bson::BsonUtils::GetStringValue(document, "region");
            topicArn = Core::Bson::BsonUtils::GetStringValue(document, "topicArn");
            pageSize = Core::Bson::BsonUtils::GetIntValue(document, "pageSize");
            pageIndex = Core::Bson::BsonUtils::GetIntValue(document, "pageIndex");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListMessagesRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListMessagesRequest &r) {
        os << "ListMessagesRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS

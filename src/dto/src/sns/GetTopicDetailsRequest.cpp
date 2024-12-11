//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sns/GetTopicDetailsRequest.h>

namespace AwsMock::Dto::SNS {

    void GetTopicDetailsRequest::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);

            region = Core::Bson::BsonUtils::GetStringValue(document, "region");
            topicArn = Core::Bson::BsonUtils::GetStringValue(document, "topicArn");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string GetTopicDetailsRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "topicArn", topicArn);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    [[nodiscard]] std::string GetTopicDetailsRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetTopicDetailsRequest &r) {
        os << "GetTopicDetailsRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS

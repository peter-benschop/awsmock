//
// Created by vogje01 on 03/10/2023.
//

#include <awsmock/dto/sns/PurgeTopicRequest.h>

namespace AwsMock::Dto::SNS {

    void PurgeTopicRequest::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);
            topicArn = Core::Bson::BsonUtils::GetStringValue(document, "topicArn");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string PurgeTopicRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "topicArn", topicArn);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string PurgeTopicRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const PurgeTopicRequest &r) {
        os << "PurgeTopicRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS

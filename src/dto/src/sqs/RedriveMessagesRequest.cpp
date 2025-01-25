//
// Created by vogje01 on 02/10/2023.
//

#include <awsmock/dto/sqs/RedriveMessagesRequest.h>

namespace AwsMock::Dto::SQS {

    void RedriveMessagesRequest::FromJson(const std::string &jsonString) {


        try {

            const value document = bsoncxx::from_json(jsonString);
            queueArn = Core::Bson::BsonUtils::GetStringValue(document, "queueArn");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string RedriveMessagesRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "queueArn", queueArn);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string RedriveMessagesRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const RedriveMessagesRequest &r) {
        os << "RedriveMessagesRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS

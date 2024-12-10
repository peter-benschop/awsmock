//
// Created by vogje01 on 30/09/2023.
//

#include <awsmock/dto/sqs/GetQueueAttributesRequest.h>

namespace AwsMock::Dto::SQS {

    std::string GetQueueAttributesRequest::ToJson() const {

        try {
            document document;
            if (!attributeNames.empty()) {
                array jsonArray;
                for (const auto &name: attributeNames) {
                    jsonArray.append(name);
                }
                document.append(kvp("AttributeName", jsonArray));
            }
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void GetQueueAttributesRequest::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);
            queueUrl = Core::Bson::BsonUtils::GetStringValue(document, "QueueUrl");

            if (document.find("AttributeNames") != document.end()) {
                Core::Bson::FromBsonStringArray(document, "AttributeNames", &attributeNames);
            }

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string GetQueueAttributesRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetQueueAttributesRequest &r) {
        os << "GetQueueAttributesRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS

//
// Created by vogje01 on 30/09/2023.
//

#include <awsmock/dto/sqs/SetQueueAttributesRequest.h>

namespace AwsMock::Dto::SQS {

    void SetQueueAttributesRequest::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);
            queueUrl = Core::Bson::BsonUtils::GetStringValue(document, "QueueUrl");

            if (document.find("AttributeNames") != document.end()) {
                for (const view tagsView = document.view()["attributes"].get_document().value; const bsoncxx::document::element &tagElement: tagsView) {
                    std::string key = bsoncxx::string::to_string(tagElement.key());
                    std::string value = bsoncxx::string::to_string(tagsView[key].get_string().value);
                    attributes.emplace(key, value);
                }
            }

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string SetQueueAttributesRequest::ToJson() const {

        try {
            document rootDocument;
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "QueueUrl", queueUrl);

            if (!attributes.empty()) {
                document jsonObject;
                for (const auto &[fst, snd]: attributes) {
                    jsonObject.append(kvp(fst, snd));
                }
                rootDocument.append(kvp("Attributes", jsonObject));
            }
            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string SetQueueAttributesRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const SetQueueAttributesRequest &r) {
        os << "SetQueueAttributesRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS

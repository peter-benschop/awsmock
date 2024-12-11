//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/TagQueueRequest.h>

namespace AwsMock::Dto::SQS {

    std::string TagQueueRequest::ToJson() const {

        try {

            document rootDocument;
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "QueueUrl", queueUrl);

            if (!tags.empty()) {
                document jsonObject;
                for (const auto &[fst, snd]: tags) {
                    jsonObject.append(kvp(fst, snd));
                }
                rootDocument.append(kvp("Tags", jsonObject));
            }
            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void TagQueueRequest::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);

            // Get queue URL
            queueUrl = Core::Bson::BsonUtils::GetStringValue(document, "QueueUrl");

            // Get the tags
            if (document.find("Tags") != document.end()) {
                for (const view tagsView = document.view()["Tags"].get_document().value; const bsoncxx::document::element &tagElement: tagsView) {
                    std::string key = bsoncxx::string::to_string(tagElement.key());
                    std::string value = bsoncxx::string::to_string(tagsView[key].get_string().value);
                    tags.emplace(key, value);
                }
            }

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string TagQueueRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const TagQueueRequest &r) {
        os << "TagQueueRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS

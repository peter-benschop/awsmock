//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/UntagQueueRequest.h>

namespace AwsMock::Dto::SQS {

    void UntagQueueRequest::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);
            queueUrl = Core::Bson::BsonUtils::GetStringValue(document, "QueueUrl");

            if (document.find("TagKeys") != document.end()) {
                Core::Bson::FromBsonStringArray(document, "TagKeys", &tags);
            }

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string UntagQueueRequest::ToJson() const {

        try {

            document rootDocument;
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "QueueUrl", queueUrl);

            if (!tags.empty()) {
                array tagsArray;
                for (auto tag: tags) {
                    tagsArray.append(tag);
                }
                rootDocument.append(kvp("Tags", tagsArray));
            }
            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string UntagQueueRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UntagQueueRequest &r) {
        os << "UntagQueueRequest=" + r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS

//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/SendMessageBatchRequest.h>

namespace AwsMock::Dto::SQS {

    void SendMessageBatchRequest::FromJson(const std::string &jsonString) {

        try {
            const value rootDocument = bsoncxx::from_json(jsonString);
            region = Core::Bson::BsonUtils::GetStringValue(rootDocument, "Region");
            queueUrl = Core::Bson::BsonUtils::GetStringValue(rootDocument, "QueueUrl");

            // Sanitize
            queueUrl = Core::SanitizeSQSUrl(queueUrl);

            // Entries
            if (rootDocument.find("Entries") != rootDocument.end()) {
                for (const view entriesArray = rootDocument.view()["Entries"].get_array().value; const auto &element: entriesArray) {
                    MessageEntry entry;
                    entry.FromDocument(element.get_document().value);
                    entries.emplace_back(entry);
                }
            }

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string SendMessageBatchRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "QueueUrl", queueUrl);

            // Entries
            if (!entries.empty()) {
                array jsonArray;
                for (const auto &entry: entries) {
                    jsonArray.append(entry.ToDocument());
                }
                document.append(kvp("Entries", jsonArray));
            }
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string SendMessageBatchRequest::ToString() {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, SendMessageBatchRequest &r) {
        os << "SendMessageBatchRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS

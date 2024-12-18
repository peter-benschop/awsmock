//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/DeleteMessageBatchRequest.h>

namespace AwsMock::Dto::SQS {

    std::string DeleteMessageBatchRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "QueueUrl", queueUrl);

            // Entries
            if (!deleteMessageBatchEntries.empty()) {
                array entriesArray;
                for (const auto &e: deleteMessageBatchEntries) {
                    entriesArray.append(e.ToDocument());
                }
                document.append(kvp("DeleteMessageBatchEntries", entriesArray));
            }
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void DeleteMessageBatchRequest::FromJson(const std::string &jsonString) {

        try {

            // Queue
            const value document = bsoncxx::from_json(jsonString);
            queueUrl = Core::Bson::BsonUtils::GetStringValue(document, "QueueUrl");

            // Entries
            if (document.find("Entries") != document.end()) {
                for (const bsoncxx::array::view arrayView{document["Entries"].get_array().value}; const bsoncxx::array::element &element: arrayView) {
                    DeleteMessageBatchEntry entry;
                    entry.id = Core::Bson::BsonUtils::GetStringValue(element.get_document(), "Id");
                    entry.receiptHandle = Core::Bson::BsonUtils::GetStringValue(element.get_document(), "ReceiptHandle");
                    deleteMessageBatchEntries.emplace_back(entry);
                }
            }

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string DeleteMessageBatchRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteMessageBatchRequest &r) {
        os << "DeleteMessageBatchRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS

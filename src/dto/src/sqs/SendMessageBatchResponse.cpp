//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/SendMessageBatchResponse.h>

namespace AwsMock::Dto::SQS {

    std::string SendMessageBatchResponse::ToJson() const {

        try {
            document document;
            if (!failed.empty()) {
                array failedArray;
                for (const auto &fail: failed) {
                    failedArray.append(fail.ToDocument());
                }
                document.append(kvp("Failed", failedArray));
            }

            if (!successful.empty()) {
                array successArray;
                for (const auto &success: successful) {
                    successArray.append(success.ToDocument());
                }
                document.append(kvp("Successful", successArray));
            }

            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void SendMessageBatchResponse::FromJson(const std::string &jsonString) {

        try {

            if (const value documentValue = bsoncxx::from_json(jsonString); documentValue.find("Failed") != documentValue.end()) {
                for (const auto &element: documentValue["Failed"].get_array().value) {
                    MessageFailed failedMessage;
                    failedMessage.FromDocument(element.get_document().view());
                    failed.emplace_back(failedMessage);
                }
            }

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string SendMessageBatchResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const SendMessageBatchResponse &r) {
        os << "SendMessageBatchResponse=" + r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS

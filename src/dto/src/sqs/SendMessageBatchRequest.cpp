//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/SendMessageBatchRequest.h>

namespace AwsMock::Dto::SQS {

    void SendMessageBatchRequest::FromJson(const std::string &jsonString) {

        /* Todo
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // General
            Core::JsonUtils::GetJsonValueString("Region", rootObject, queueUrl);
            Core::JsonUtils::GetJsonValueString("QueueUrl", rootObject, queueUrl);

            // Sanitize
            queueUrl = Core::SanitizeSQSUrl(queueUrl);

            // Entries
            if (rootObject->has("Entries")) {

                Poco::JSON::Array::Ptr entryArray = rootObject->getArray("Entries");

                if (!entryArray.isNull() && !entryArray->empty()) {
                    for (size_t i = 0; i < entryArray->size(); i++) {
                        MessageEntry entry;
                        entry.FromJson(entryArray->getObject(i));
                        entries.emplace_back(entry);
                    }
                }
            }

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }*/
    }

    std::string SendMessageBatchRequest::ToJson() const {

        /* Todo
        try {

            Poco::JSON::Object rootJson;
            rootJson.set("QueueUrl", queueUrl);

            Poco::JSON::Array jsonEntryArray;
            for (const auto &entry: entries) {
                Poco::JSON::Object jsonEntry = entry.ToJsonObject();
                jsonEntryArray.add(entry.ToJsonObject());
            }

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }*/
        return {};
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


#include <awsmock/dto/sqs/model/EventNotification.h>

namespace AwsMock::Dto::SQS {

    std::string EventNotification::ToJson() const {

        try {
            document document;

            if (!records.empty()) {
                array jsonArray;
                for (const auto &item: records) {
                    jsonArray.append(item.ToDocument());
                }
                document.append(kvp("Records", jsonArray));
            }

            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void EventNotification::FromJson(const std::string &jsonString) {

        try {

            if (const value document = bsoncxx::from_json(jsonString); document.find("Records") != document.end()) {
                for (const bsoncxx::array::view arrayView{document["Records"].get_array().value}; const bsoncxx::array::element &tagElement: arrayView) {
                    Record record;
                    record.FromDocument(tagElement.get_document().value);
                    records.emplace_back(record);
                }
            }
        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string EventNotification::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const EventNotification &e) {
        os << "EventNotification=" + e.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS

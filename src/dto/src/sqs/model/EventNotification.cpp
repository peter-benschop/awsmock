
#include <awsmock/dto/sqs/model/EventNotification.h>

namespace AwsMock::Dto::SQS {

    std::string EventNotification::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            Poco::JSON::Array recordsJsonArray;
            for (const auto &record: records) {
                recordsJsonArray.add(record.ToJsonObject());
            }
            rootJson.set("Records", recordsJsonArray);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void EventNotification::FromJson(const std::string &jsonString) {

        try {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(jsonString);
            Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();
            Poco::JSON::Array::Ptr recordArray = rootObject->getArray("Records");

            if (recordArray != nullptr) {
                for (const auto &it: *recordArray) {
                    Record record;
                    record.FromJson(it.extract<Poco::JSON::Object::Ptr>());
                    records.push_back(record);
                }
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
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

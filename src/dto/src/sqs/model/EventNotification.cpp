
#include <awsmock/dto/sqs/model/EventNotification.h>
#include <boost/regex/v5/regex.hpp>
#include <boost/regex/v5/regex_fwd.hpp>

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
            /*
            // AWS SDK C++ bug: "SentTimestamp": "1734439925" need ',' at the end
            const std::string repairJson = Core::Bson::BsonUtils::ToJsonString(document);
            const boost::regex regex(R"(("VisibilityTimeout" : "\d+"))");
            if (boost::smatch what; boost::regex_search(repairJson, what, regex)) {
                return boost::regex_replace(repairJson, regex, what[1] + ",");
            }
*/
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void EventNotification::FromJson(const std::string &jsonString) {

        try {

            if (const value document = bsoncxx::from_json(jsonString); document.find("Records") != document.end()) {
                for (const bsoncxx::array::view arrayView{document["Entries"].get_array().value}; const bsoncxx::array::element &tagElement: arrayView) {
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

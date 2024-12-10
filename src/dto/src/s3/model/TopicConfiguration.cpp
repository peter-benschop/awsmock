//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/dto/s3/model/TopicConfiguration.h>

namespace AwsMock::Dto::S3 {

    view_or_value<view, value> TopicConfiguration::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Id", id);
            Core::Bson::BsonUtils::SetStringValue(document, "Topic", topicArn);

            // Filters
            if (!filterRules.empty()) {
                array jsonArray;
                for (const auto &filter: filterRules) {
                    jsonArray.append(filter.ToDocument());
                }
                document.append(kvp("Filter", jsonArray));
            }

            // Event
            if (!events.empty()) {
                array jsonArray;
                for (const auto &event: events) {
                    jsonArray.append(EventTypeToString(event));
                }
                document.append(kvp("Event", jsonArray));
            }
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string TopicConfiguration::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string TopicConfiguration::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const TopicConfiguration &r) {
        os << "TopicConfiguration=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3

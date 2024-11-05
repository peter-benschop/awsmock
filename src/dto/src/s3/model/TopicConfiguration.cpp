//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/dto/s3/model/TopicConfiguration.h>

namespace AwsMock::Dto::S3 {

    void TopicConfiguration::FromXmlNode(Poco::XML::Node *rootNode) {

        if (rootNode->hasChildNodes()) {
            Poco::XML::NodeList *childNodes = rootNode->childNodes();
            for (int i = 0; i < childNodes->length(); i++) {

                Poco::XML::Node *child = childNodes->item(i);
                if (child->nodeName() == "Id") {

                    id = child->innerText();

                } else if (child->nodeName() == "Topic") {

                    topicArn = child->innerText();

                } else if (child->nodeName() == "Filter") {

                    // Filter
                    if (child->hasChildNodes()) {

                        Poco::XML::Node *filterNode = child->firstChild();
                        Poco::XML::Node *s3KeyNode = filterNode->firstChild();

                        // Filter rules
                        if (s3KeyNode->hasChildNodes()) {
                            Poco::XML::NodeList *filterRulesNodes = s3KeyNode->childNodes();
                            for (int j = 0; j < filterRulesNodes->length(); j++) {
                                FilterRule filterRule;
                                filterRule.FromXmlNode(filterRulesNodes->item(j));
                                filterRules.emplace_back(filterRule);
                            }
                        }
                    }
                } else if (child->nodeName() == "Events") {

                    // Events
                    if (child->hasChildNodes()) {
                        Poco::XML::NodeList *eventNodes = child->childNodes();
                        for (int j = 0; j < eventNodes->length(); j++) {
                            events.emplace_back(EventTypeFromString(eventNodes->item(j)->innerText()));
                        }
                    }
                }
            }
        }
    }

    Poco::JSON::Object TopicConfiguration::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;

            Core::JsonUtils::SetJsonValueString(rootJson, "Id", id);
            Core::JsonUtils::SetJsonValueString(rootJson, "Topic", topicArn);

            // Filters
            if (!filterRules.empty()) {
                Poco::JSON::Array::Ptr jsonArray;
                for (const auto &filter: filterRules) {
                    jsonArray->add(filter.ToJsonObject());
                }
                rootJson.set("Filter", jsonArray);
            }

            // Event
            if (!events.empty()) {
                Poco::JSON::Array::Ptr jsonArray;
                for (const auto &event: events) {
                    jsonArray->add(event);
                }
                rootJson.set("Event", jsonArray);
            }
            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string TopicConfiguration::ToJson() const {
        return Core::JsonUtils::ToJsonString(ToJsonObject());
    }

    std::string TopicConfiguration::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const TopicConfiguration &r) {
        os << "TopicConfiguration=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3

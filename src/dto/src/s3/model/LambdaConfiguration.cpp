//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/dto/s3/model/LambdaConfiguration.h>

namespace AwsMock::Dto::S3 {

    void LambdaConfiguration::FromXmlNode(Poco::XML::Node *rootNode) {

        if (rootNode->hasChildNodes()) {
            Poco::XML::NodeList *childNodes = rootNode->childNodes();
            for (int i = 0; i < childNodes->length(); i++) {

                Poco::XML::Node *child = childNodes->item(i);
                if (child->nodeName() == "Id") {

                    id = child->innerText();

                } else if (child->nodeName() == "CloudFunction") {

                    lambdaArn = child->innerText();

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
                } else if (child->nodeName() == "Event") {

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

    Poco::JSON::Object LambdaConfiguration::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("id", id);
            rootJson.set("lambdaArn", lambdaArn);

            if (!events.empty()) {
                Poco::JSON::Array jsonArray;
                for (const auto &event: events) {
                    jsonArray.add(Dto::S3::EventTypeToString(event));
                }
                rootJson.set("events", jsonArray);
            }

            if (!filterRules.empty()) {
                Poco::JSON::Array jsonArray;
                for (const auto &filterRule: filterRules) {
                    jsonArray.add(filterRule.ToJsonObject());
                }
                rootJson.set("filterRules", jsonArray);
            }
            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string LambdaConfiguration::ToJson() const {
        return Core::JsonUtils::ToJsonString(ToJsonObject());
    }

    std::string LambdaConfiguration::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const LambdaConfiguration &r) {
        os << "LambdaConfiguration=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3

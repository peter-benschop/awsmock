//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/dto/s3/model/QueueConfiguration.h>

namespace AwsMock::Dto::S3 {

    void QueueConfiguration::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        try {

            Core::JsonUtils::GetJsonValueString("id", jsonObject, id);
            Core::JsonUtils::GetJsonValueString("queueArn", jsonObject, queueArn);

            // Events
            if (jsonObject->has("events")) {
                Poco::JSON::Array::Ptr jsonEventArray = jsonObject->getArray("events");
                for (const auto &event: *jsonEventArray) {
                    events.emplace_back(EventTypeFromString(event));
                }
            }

        } catch (Poco::Exception &e) {
            log_error << e.message();
            throw Core::JsonException(e.message());
        }
    }

    void QueueConfiguration::FromXmlNode(Poco::XML::Node *rootNode) {

        if (rootNode->hasChildNodes()) {
            Poco::XML::NodeList *childNodes = rootNode->childNodes();
            for (int i = 0; i < childNodes->length(); i++) {

                Poco::XML::Node *child = childNodes->item(i);
                if (child->nodeName() == "Id") {

                    id = child->innerText();

                } else if (child->nodeName() == "Queue") {

                    queueArn = child->innerText();

                } else if (child->nodeName() == "Filter") {

                    // Filter
                    if (child->hasChildNodes()) {
                        Poco::XML::Node *filterNode = child->firstChild();
                        Poco::XML::Node *s3KeyNode = filterNode->firstChild();

                        // Filter rules
                        if (s3KeyNode->hasChildNodes()) {
                            FilterRule filterRule;
                            filterRule.FromXmlNode(s3KeyNode);
                            filterRules.emplace_back(filterRule);
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

    Poco::JSON::Object QueueConfiguration::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string QueueConfiguration::ToJson() const {
        return Core::JsonUtils::ToJsonString(ToJsonObject());
    }

    std::string QueueConfiguration::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const QueueConfiguration &r) {
        os << "QueueConfiguration=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3

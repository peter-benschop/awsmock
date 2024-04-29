//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/dto/s3/QueueConfiguration.h>

namespace AwsMock::Dto::S3 {

    void QueueConfiguration::FromXmlNode(Poco::XML::Node *rootNode) {

        if (rootNode->hasChildNodes()) {
            Poco::XML::NodeList *childNodes = rootNode->childNodes();
            for (int i = 0; i < childNodes->length(); i++) {

                Poco::XML::Node *child = childNodes->item(i);
                if (child->nodeName() == "Id") {

                    id = child->innerText();

                } else if (child->nodeName() == "Queue") {

                    queue = child->innerText();

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

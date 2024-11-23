//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/lambda/GetFunctionResponse.h>

namespace AwsMock::Dto::Lambda {

    std::string GetFunctionResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("User", user);
            rootJson.set("Configuration", configuration.ToJsonObject());
            rootJson.set("Code", code.ToJson());
            rootJson.set("Timeout", timeout);

            if (!tags.empty()) {
                Poco::JSON::Object jsonTags;
                for (const auto &tag: tags) {
                    jsonTags.set(tag.first, tag.second);
                }
                rootJson.set("Tags", jsonTags);
            }

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string GetFunctionResponse::ToXml() const {

        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("GetFunctionResponse");
        Poco::XML::AutoPtr<Poco::XML::Element> pConfig = pDoc->createElement("Configuration");

        Core::XmlUtils::CreateTextNode(pDoc, pConfig, "Region", region);
        Core::XmlUtils::CreateTextNode(pDoc, pConfig, "FunctionName", configuration.functionName);
        Core::XmlUtils::CreateTextNode(pDoc, pConfig, "FunctionArn", configuration.functionArn);
        Core::XmlUtils::CreateTextNode(pDoc, pConfig, "State", configuration.state);
        Core::XmlUtils::CreateTextNode(pDoc, pConfig, "State", configuration.state);
        pRoot->appendChild(pConfig);
        pDoc->appendChild(pRoot);

        return Core::XmlUtils::ToXmlString(pDoc);
    }

    std::string GetFunctionResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetFunctionResponse &r) {
        os << "GetFunctionResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda

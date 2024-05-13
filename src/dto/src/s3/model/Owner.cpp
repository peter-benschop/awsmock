//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/model/Owner.h>

namespace AwsMock::Dto::S3 {

    std::string Owner::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("id", id);
            rootJson.set("displayName", displayName);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    Poco::JSON::Object Owner::ToJsonObject() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("DisplayName", displayName);
            rootJson.set("Id", id);
            return rootJson;

        } catch (Poco::Exception &exc) {
            throw Core::JsonException(exc.message());
        }
    }

    Poco::XML::AutoPtr<Poco::XML::Element> Owner::ToXmlElement(Poco::XML::AutoPtr<Poco::XML::Document> pDoc) const {

        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("Owner");
        if (!id.empty()) {
            Core::XmlUtils::CreateTextNode(pDoc, pRoot, "ID", id);
        }
        if (!displayName.empty()) {
            Core::XmlUtils::CreateTextNode(pDoc, pRoot, "DisplayName", displayName);
        }
        return pRoot;
    }

    std::string Owner::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Owner &o) {
        os << "Owner=" << o.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3

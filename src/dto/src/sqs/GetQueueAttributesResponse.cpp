//
// Created by vogje01 on 30/09/2023.
//

#include <awsmock/dto/sqs/GetQueueAttributesResponse.h>

namespace AwsMock::Dto::SQS {

    std::string GetQueueAttributesResponse::ToJson() const {

        try {

            Poco::JSON::Object attributeObject;
            for (const auto &attribute: attributes) {
                attributeObject.set(attribute.first, attribute.second);
            }

            Poco::JSON::Object rootJson;
            rootJson.set("Attributes", attributeObject);

            std::ostringstream os;
            rootJson.stringify(os);
            return os.str();

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
    }

    std::string GetQueueAttributesResponse::ToXml() const {

        try {

            // Root
            Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
            Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("GetQueueAttributesResponse");
            pDoc->appendChild(pRoot);

            // Metadata
            Poco::XML::AutoPtr<Poco::XML::Element> pAttributeResult = pDoc->createElement("GetQueueAttributesResult");
            pRoot->appendChild(pAttributeResult);

            for (const auto &attribute: attributes) {

                // UserAttribute
                Poco::XML::AutoPtr<Poco::XML::Element> pAttribute = pDoc->createElement("Attribute");
                pAttributeResult->appendChild(pAttribute);

                // Name
                Poco::XML::AutoPtr<Poco::XML::Element> pName = pDoc->createElement("Name");
                pAttribute->appendChild(pName);
                Poco::XML::AutoPtr<Poco::XML::Text> pNameText = pDoc->createTextNode(attribute.first);
                pName->appendChild(pNameText);

                // Value
                Poco::XML::AutoPtr<Poco::XML::Element> pValue = pDoc->createElement("Value");
                pAttribute->appendChild(pValue);
                Poco::XML::AutoPtr<Poco::XML::Text> pValueText = pDoc->createTextNode(attribute.second);
                pValue->appendChild(pValueText);
            }

            // Metadata
            Poco::XML::AutoPtr<Poco::XML::Element> pMetaData = pDoc->createElement("ResponseMetadata");
            pRoot->appendChild(pMetaData);

            Poco::XML::AutoPtr<Poco::XML::Element> pRequestId = pDoc->createElement("RequestId");
            pMetaData->appendChild(pRequestId);
            Poco::XML::AutoPtr<Poco::XML::Text> pRequestText = pDoc->createTextNode(requestId);
            pRequestId->appendChild(pRequestText);

            std::stringstream output;
            Poco::XML::DOMWriter writer;
            writer.writeNode(output, pDoc);
            return output.str();

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
    }

    std::string GetQueueAttributesResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetQueueAttributesResponse &r) {
        os << "GetQueueAttributesResponse={resource='" << r.resource << "', requestId: '" << r.requestId << "', userAttributes={";
        for (const auto &attribute: r.attributes) {
            os << attribute.first << "='" << attribute.second << "', ";
        }
        os << "\b\b}}";
        return os;
    }

}// namespace AwsMock::Dto::SQS

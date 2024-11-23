//
// Created by vogje01 on 30/09/2023.
//

#include <awsmock/dto/sqs/SetQueueAttributesResponse.h>

namespace AwsMock::Dto::SQS {

    std::string SetQueueAttributesResponse::ToJson() const {

        try {

            Poco::JSON::Object attributeObject;
            Poco::JSON::Object rootJson;
            rootJson.set("Attributes", attributeObject);

            std::ostringstream os;
            rootJson.stringify(os);
            return os.str();

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
    }

    std::string SetQueueAttributesResponse::ToXml() const {

        try {

            // Root
            Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
            Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("SetQueueAttributesResponse");
            pDoc->appendChild(pRoot);

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

    std::string SetQueueAttributesResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const SetQueueAttributesResponse &r) {
        os << "SetQueueAttributesResponse={resource='" << r.resource << "', requestId: '" << r.requestId << std::endl;
        return os;
    }

}// namespace AwsMock::Dto::SQS

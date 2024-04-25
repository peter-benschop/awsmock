//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/DeleteQueueResponse.h>

namespace AwsMock::Dto::SQS {

    std::string DeleteQueueResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("QueueUrl", queueUrl);
            rootJson.set("RequestId", requestId);

            std::ostringstream os;
            rootJson.stringify(os);
            return os.str();

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR);
        }
    }

    std::string DeleteQueueResponse::ToXml() const {

        try {

            // Root
            Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
            Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("DeleteQueueResponse");
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
            throw Core::ServiceException(exc.message(), Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
        }
    }

    std::string DeleteQueueResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteQueueResponse &r) {
        os << "DeleteQueueResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS

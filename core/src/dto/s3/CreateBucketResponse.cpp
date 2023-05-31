//
// Created by vogje01 on 30/05/2023.
//

#include <utility>

#include "awsmock/dto/s3/CreateBucketResponse.h"

namespace AwsMock::Dto::S3 {

    CreateBucketResponse::CreateBucketResponse(std::string location, std::string arn) : _location(std::move(location)), _arn(std::move(arn)) {
    }

    std::string CreateBucketResponse::ToXml() {
        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("CreateBucketResult");
        pDoc->appendChild(pRoot);
        Poco::XML::AutoPtr<Poco::XML::Element> pChild1 = pDoc->createElement("BuckerArn");
        pRoot->appendChild(pChild1);
        Poco::XML::AutoPtr<Poco::XML::Text> pText1 = pDoc->createTextNode(_arn);
        pChild1->appendChild(pText1);

        std::stringstream output;
        Poco::XML::DOMWriter writer;
        writer.setNewLine("\n");
        writer.setOptions(Poco::XML::XMLWriter::WRITE_XML_DECLARATION | Poco::XML::XMLWriter::PRETTY_PRINT);
        writer.writeNode(output, pDoc);

        std::string outStr = output.str();
        return outStr;
    }

    std::string CreateBucketResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateBucketResponse &r) {
        os << "CreateBucketResponse={bucket='" + r._location + "', arn='" + r._arn + "'}";
        return os;
    }

}
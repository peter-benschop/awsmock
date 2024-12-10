//
// Created by vogje01 on 5/10/24.
//

#include <awsmock/dto/s3/model/ObjectVersion.h>

namespace AwsMock::Dto::S3 {

    /*    Poco::XML::AutoPtr<Poco::XML::Element> ObjectVersion::ToXmlElement(Poco::XML::AutoPtr<Poco::XML::Document> pDoc) const {

        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("Version");
        Core::XmlUtils::CreateTextNode(pDoc, pRoot, "Key", key);
        Core::XmlUtils::CreateTextNode(pDoc, pRoot, "ETag", eTag);
        Core::XmlUtils::CreateTextNode(pDoc, pRoot, "VersionId", versionId);
        Core::XmlUtils::CreateTextNode(pDoc, pRoot, "StorageClass", storageClass);
        Core::XmlUtils::CreateTextNode(pDoc, pRoot, "IsLatest", isLatest);
        Core::XmlUtils::CreateTextNode(pDoc, pRoot, "Size", size);
        Core::XmlUtils::CreateTextNode(pDoc, pRoot, "LastModified", Core::DateTimeUtils::ToISO8601(lastModified));
        pRoot->appendChild(owner.ToXmlElement(pDoc));

        // Checksums
        for (const auto &checksum: checksumAlgorithms) {
            Core::XmlUtils::CreateTextNode(pDoc, pRoot, "ChecksumAlgorithm", checksum);
        }

        return pRoot;
    }*/

    view_or_value<view, value> ObjectVersion::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Key", key);
            Core::Bson::BsonUtils::SetStringValue(document, "ETag", eTag);
            Core::Bson::BsonUtils::SetStringValue(document, "VersionId", versionId);
            Core::Bson::BsonUtils::SetStringValue(document, "StorageClass", storageClass);
            Core::Bson::BsonUtils::SetBoolValue(document, "IsLatest", isLatest);
            Core::Bson::BsonUtils::SetIntValue(document, "Size", size);
            //Core::Bson::BsonUtils::SetStringValue(document, "ChecksumAlgorithm", checksumAlgorithms);
            Core::Bson::BsonUtils::SetDateValue(document, "LastModified", lastModified);

            document.append(kvp("Owner", owner.ToDocument()));
            document.append(kvp("RestoreStatus", restoreStatus.ToDocument()));
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ObjectVersion::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string ObjectVersion::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ObjectVersion &r) {
        os << "ObjectVersion=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
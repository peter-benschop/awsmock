//
// Created by vogje01 on 5/10/24.
//

#include <awsmock/dto/s3/model/ObjectVersion.h>

namespace AwsMock::Dto::S3 {

    Poco::XML::AutoPtr<Poco::XML::Element> ObjectVersion::ToXmlElement(Poco::XML::AutoPtr<Poco::XML::Document> pDoc) const {

        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("Version");
        Core::XmlUtils::CreateTextNode(pDoc, pRoot, "Key", key);
        Core::XmlUtils::CreateTextNode(pDoc, pRoot, "ETag", eTag);
        Core::XmlUtils::CreateTextNode(pDoc, pRoot, "VersionId", versionId);
        Core::XmlUtils::CreateTextNode(pDoc, pRoot, "StorageClass", storageClass);
        Core::XmlUtils::CreateTextNode(pDoc, pRoot, "IsLatest", isLatest);
        Core::XmlUtils::CreateTextNode(pDoc, pRoot, "Size", size);
        Core::XmlUtils::CreateTextNode(pDoc, pRoot, "LastModified", lastModified);
        pRoot->appendChild(owner.ToXmlElement(pDoc));

        // Checksums
        for (const auto &checksum: checksumAlgorithms) {
            Core::XmlUtils::CreateTextNode(pDoc, pRoot, "ChecksumAlgorithm", checksum);
        }

        return pRoot;
    }

    Poco::JSON::Object ObjectVersion::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Key", key);
            rootJson.set("ETag", eTag);
            rootJson.set("VersionId", versionId);
            rootJson.set("StorageClass", storageClass);
            rootJson.set("IsLatest", isLatest);
            rootJson.set("Size", size);
            rootJson.set("ChecksumAlgorithm", Core::JsonUtils::GetJsonStringArray(checksumAlgorithms));
            rootJson.set("LastModified", Poco::DateTimeFormatter::format(lastModified, Poco::DateTimeFormat::ISO8601_FORMAT));
            rootJson.set("Owner", owner.ToJsonObject());
            rootJson.set("RestoreStatue", restoreStatue.ToJsonObject());
            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ObjectVersion::ToJson() const {
        return Core::JsonUtils::ToJsonString(ToJsonObject());
    }

    std::string ObjectVersion::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ObjectVersion &r) {
        os << "ObjectVersion=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
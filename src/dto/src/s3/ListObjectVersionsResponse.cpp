//
// Created by vogje01 on 30/05/2023.
//

// AwsMock includes
#include <awsmock/dto/s3/ListObjectVersionsResponse.h>
#include <ranges>

namespace AwsMock::Dto::S3 {

    view_or_value<view, value> DeleteMarker::ToDocument() const {

        try {

            document rootDocument;
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "Key", key);
            Core::Bson::BsonUtils::SetBoolValue(rootDocument, "IsLatest", isLatest);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "LastModified", Core::DateTimeUtils::ToISO8601(lastModified));
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "VersionId", versionId);
            rootDocument.append(kvp("Owner", owner.ToDocument()));
            return rootDocument.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListObjectVersionsResponse::ToJson() const {

        try {

            document rootDocument;
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "Name", name);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "Prefix", prefix);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "Delimiter", delimiter);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "EncodingType", encodingType);
            Core::Bson::BsonUtils::SetIntValue(rootDocument, "MaxKeys", maxKeys);
            Core::Bson::BsonUtils::SetBoolValue(rootDocument, "IsTruncated", isTruncated);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "KeyMarker", keyMarker);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "VersionIdMarker", versionIdMarker);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "NextKeyMarker", keyMarker);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "NextVersionIdMarker", versionIdMarker);

            // Prefixes
            if (!commonPrefixes.empty()) {
                array jsonPrefixArray;
                for (const auto &p: commonPrefixes) {
                    document prefixObject;
                    Core::Bson::BsonUtils::SetStringValue(prefixObject, "prefix", p);
                    jsonPrefixArray.append(prefixObject);
                }
                rootDocument.append(kvp("CommonPrefixes", jsonPrefixArray));
            }

            // Versions
            if (!versions.empty()) {
                array jsonVersionArray;
                for (const auto &v: versions) {
                    jsonVersionArray.append(v.ToDocument());
                }
                rootDocument.append(kvp("Versions", jsonVersionArray));
            }

            // Delete markers
            if (!deleteMarkers.empty()) {
                array jsonDeleteMarkerArray;
                for (const auto &m: deleteMarkers) {
                    jsonDeleteMarkerArray.append(m.ToDocument());
                }
                rootDocument.append(kvp("DeleteMarkers", jsonDeleteMarkerArray));
            }

            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListObjectVersionsResponse::ToXml() const {

        try {

            boost::property_tree::ptree root;
            boost::property_tree::ptree listVersionResult;

            listVersionResult.add("Region", region);
            listVersionResult.add("Name", name);
            listVersionResult.add("Prefix", prefix);
            listVersionResult.add("Delimiter", delimiter);
            listVersionResult.add("EncodingType", encodingType);
            listVersionResult.add("MaxKeys", maxKeys);
            listVersionResult.add("IsTruncated", isTruncated);
            listVersionResult.add("KeyMarker", keyMarker);
            listVersionResult.add("VersionIdMarker", versionIdMarker);
            listVersionResult.add("NextKeyMarker", nextKeyMarker);
            listVersionResult.add("NextVersionIdMarker", nextVersionIdMarker);

            // Prefixes
            if (!commonPrefixes.empty()) {
                boost::property_tree::ptree prefixArray;
                for (const auto &p: commonPrefixes) {
                    prefixArray.push_back(boost::property_tree::basic_ptree<std::string, std::string>::value_type(std::make_pair("", p)));
                }
                listVersionResult.add_child("CommonPrefixes", prefixArray);
            }

            // Versions
            if (!versions.empty()) {
                for (const auto &v: versions) {
                    boost::property_tree::ptree jsonVersionObject;
                    jsonVersionObject.add("Key", v.key);
                    jsonVersionObject.add("ETag", v.eTag);
                    jsonVersionObject.add("VersionId", v.versionId);
                    jsonVersionObject.add("StorageClass", v.storageClass);
                    jsonVersionObject.add("IsLatest", v.isLatest);
                    jsonVersionObject.add("Size", v.size);
                    jsonVersionObject.add("LastModified", Core::DateTimeUtils::ToISO8601(v.lastModified));
                    listVersionResult.add_child("Version", jsonVersionObject);
                }
            }

            // Delete markers
            if (!deleteMarkers.empty()) {
                for (const auto &m: deleteMarkers) {
                    boost::property_tree::ptree jsonDeleteObject;
                    jsonDeleteObject.add("Key", m.key);
                    jsonDeleteObject.add("IsLatest", m.isLatest);
                    jsonDeleteObject.add("VersionId", m.versionId);
                    jsonDeleteObject.add("LastModified", Core::DateTimeUtils::ToISO8601(m.lastModified));
                    listVersionResult.add_child("DeleteMarker", jsonDeleteObject);
                }
            }
            root.add_child("ListVersionResult", listVersionResult);

            std::string tmp = Core::XmlUtils::ToXmlString(root);
            return Core::XmlUtils::ToXmlString(root);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListObjectVersionsResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListObjectVersionsResponse &r) {
        os << "ListObjectVersionsResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3

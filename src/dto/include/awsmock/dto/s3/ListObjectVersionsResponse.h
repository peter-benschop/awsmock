//
// Created by vogje01 on 31/05/2023.
//

#ifndef AWSMOCK_DTO_S3_LIST_OBJECT_VERSIONS_RESPONSE_H
#define AWSMOCK_DTO_S3_LIST_OBJECT_VERSIONS_RESPONSE_H

// C++ Standard includes
#include <sstream>
#include <string>
#include <vector>

// Poco includes
#include <Poco/DOM/AutoPtr.h>
#include <Poco/DOM/DOMWriter.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/Element.h>
#include <Poco/DOM/Text.h>
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/XML/XMLWriter.h>

// AwsMock includes
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/XmlUtils.h>
#include <awsmock/dto/s3/Owner.h>

namespace AwsMock::Dto::S3 {

    struct DeleteMarker {

        /**
     * Is latest
     */
        bool isLatest;

        /**
     * Key
     */
        std::string key;

        /**
     * Last modified
     */
        Poco::DateTime lastModified;

        /**
     * Owner
     */
        Owner owner;

        /**
     * Version ID
     */
        std::string versionId;

        /**
     * Convert to a JSON object
     *
     * @return JSON object
     */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;
    };

    struct RestoreStatus {

        /**
     * Is restore in progress
     */
        bool isRestoreInProgress;

        /**
     * Expiration datetime
     */
        Poco::DateTime restoreExpiryDate;

        /**
     * Convert to a JSON object
     *
     * @return JSON object
     */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;
    };

    struct Version {

        /**
     * Key
     */
        std::string key;

        /**
     * ETag
     */
        std::string eTag;

        /**
     * VersionId
     */
        std::string versionId;

        /**
     * Storage class
     */
        std::string storageClass;

        /**
     * Checksum algorithm
     */
        std::string checksumAlgorithm;

        /**
     * Is latest
     */
        bool isLatest;

        /**
     * Size
     */
        long size;

        /**
     * Is latest
     */
        Poco::DateTime lastModified;

        /**
     * Owner
     */
        Owner owner;

        /**
     * Restore status
     */
        RestoreStatus restoreStatue;

        /**
     * Convert to a JSON object
     *
     * @return JSON object
     */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

        /**
     * Convert to a XML element
     *
     * @param pDoc XML document
     * @return XML element
     */
        [[nodiscard]] Poco::XML::AutoPtr<Poco::XML::Element> ToXmlElement(Poco::XML::AutoPtr<Poco::XML::Document> pDoc) const;
    };

    struct ListObjectVersionsResponse {

        /**
     * Region
     */
        std::string region;

        /**
     * Name
     */
        std::string name;

        /**
     * Prefix
     */
        std::string prefix;

        /**
     * Delimiter
     */
        std::string delimiter;

        /**
     * Encoding type
     */
        std::string encodingType;

        /**
     * Maximal keys
     */
        int maxKeys;

        /**
     * Truncation flag
     */
        bool isTruncated = false;

        /**
     * Key marker
     */
        std::string keyMarker;

        /**
     * Version ID marker
     */
        std::string versionIdMarker;

        /**
     * Next key marker
     */
        std::string nextKeyMarker;

        /**
     * Next version ID marker
     */
        std::string nextVersionIdMarker;

        /**
     * Common prefixes
     */
        std::vector<std::string> commonPrefixes;

        /**
     * Versions
     */
        std::vector<Version> versions;

        /**
     * Delete markers
     */
        std::vector<DeleteMarker> deleteMarkers;

        /**
     * Convert to a JSON string
     *
     * @return JSON string
     */
        [[nodiscard]] std::string ToJson() const;

        /**
     * Convert to XML representation
     *
     * @return XML string
     */
        [[nodiscard]] std::string ToXml() const;

        /**
     * Converts the DTO to a string representation.
     *
     * @return DTO as string for logging.
     */
        [[nodiscard]] std::string ToString() const;

        /**
     * Stream provider.
     *
     * @return output stream
     */
        friend std::ostream &operator<<(std::ostream &os, const ListObjectVersionsResponse &r);
    };

}// namespace AwsMock::Dto::S3

#endif// AWSMOCK_DTO_S3_LIST_OBJECT_VERSIONS_RESPONSE_H

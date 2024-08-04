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
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/XmlUtils.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/s3/model/ObjectVersion.h>
#include <awsmock/dto/s3/model/Owner.h>

namespace AwsMock::Dto::S3 {

    /**
     * @brief List S3 object version response
     *
     * Example:
     * @code{.xml}
     * <ListVersionsResult>
     *   <IsTruncated>boolean</IsTruncated>
     *   <KeyMarker>string</KeyMarker>
     *   <VersionIdMarker>string</VersionIdMarker>
     *   <NextKeyMarker>string</NextKeyMarker>
     *   <NextVersionIdMarker>string</NextVersionIdMarker>
     *   <Version>
     *     <ChecksumAlgorithm>string</ChecksumAlgorithm>
     *     ...
     *     <ETag>string</ETag>
     *     <IsLatest>boolean</IsLatest>
     *     <Key>string</Key>
     *     <LastModified>timestamp</LastModified>
     *     <Owner>
     *       <DisplayName>string</DisplayName>
     *       <ID>string</ID>
     *      </Owner>
     *     <RestoreStatus>
     *       <IsRestoreInProgress>boolean</IsRestoreInProgress>
     *       <RestoreExpiryDate>timestamp</RestoreExpiryDate>
     *     </RestoreStatus>
     *     <Size>long</Size>
     *     <StorageClass>string</StorageClass>
     *     <VersionId>string</VersionId>
     *   </Version>
     *   ...
     *   <DeleteMarker>
     *     <IsLatest>boolean</IsLatest>
     *     <Key>string</Key>
     *     <LastModified>timestamp</LastModified>
     *     <Owner>
     *       <DisplayName>string</DisplayName>
     *       <ID>string</ID>
     *     </Owner>
     *     <VersionId>string</VersionId>
     *   </DeleteMarker>
     *   ...
     *   <Name>string</Name>
     *   <Prefix>string</Prefix>
     *   <Delimiter>string</Delimiter>
     *   <MaxKeys>integer</MaxKeys>
     *   <CommonPrefixes>
     *     <Prefix>string</Prefix>
     *   </CommonPrefixes>
     *   ...
     *   <EncodingType>string</EncodingType>
     * </ListVersionsResult>
     * @endcode
     */
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
        std::vector<ObjectVersion> versions;

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

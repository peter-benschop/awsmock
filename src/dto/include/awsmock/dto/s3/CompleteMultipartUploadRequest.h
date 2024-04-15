//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_CORE_DTO_S3_COMPLETE_MULTIPART_UPLOAD_REQUEST_H
#define AWSMOCK_CORE_DTO_S3_COMPLETE_MULTIPART_UPLOAD_REQUEST_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include <Poco/DOM/AutoPtr.h>
#include <Poco/DOM/DOMParser.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/Element.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

// AwsMock includes
#include <awsmock/core/JsonException.h>

namespace AwsMock::Dto::S3 {

  struct CompleteMultipartUploadRequest {

    /**
     * Bucket location
     */
    std::string region;

    /**
     * Bucket name
     */
    std::string bucket;

    /**
     * Bucket owner
     */
    std::string key;

    /**
     * AWS user
     */
    std::string user;

    /**
     * AWS upload ID
     */
    std::string uploadId;

    /**
     * AWS upload ID
     */
    std::string checksumAlgorithm;

    /**
     * Convert to a JSON string
     *
     * @return JSON string
     */
    [[nodiscard]] std::string ToJson() const;

    /**
     * Convert from XML representation
     *
     * @param xmlString XML string
     */
    void FromXml(const std::string &xmlString);

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
    friend std::ostream &operator<<(std::ostream &os, const CompleteMultipartUploadRequest &r);

  };

} // namespace AwsMock::Dto::s3

#endif // AWSMOCK_CORE_DTO_S3_COMPLETE_MULTIPART_UPLOAD_REQUEST_H

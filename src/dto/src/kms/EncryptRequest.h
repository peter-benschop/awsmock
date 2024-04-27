//
// Created by vogje01 on 4/26/24.
//

#ifndef AWS_MOCK_ENCRYPT_REQUEST_H
#define AWS_MOCK_ENCRYPT_REQUEST_H


// C++ standard includes
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/kms/KeySpec.h>
#include <awsmock/dto/kms/KeyUsage.h>

namespace AwsMock::Dto::KMS {

    /**
     * Create KMS key request
     *
     * Example:
     * <pre>
     * {
     *   "DryRun": boolean,
     *   "EncryptionAlgorithm": "string",
     *   "EncryptionContext": {
     *      "string" : "string"
     *   },
     *   "GrantTokens": [ "string" ],
     *   "KeyId": "string",
     *   "Plaintext": blob
     * }
     * </pre>
     */
    class EncryptRequest {
    };
}// namespace AwsMock::Dto::KMS

#endif// AWS_MOCK_ENCRYPT_REQUEST_H

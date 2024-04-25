//
// Created by vogje01 on 4/8/24.
//

#ifndef AWSMOCK_DTO_SECRETSMANAGER_ADD_REPLICA_REGIONS_H
#define AWSMOCK_DTO_SECRETSMANAGER_ADD_REPLICA_REGIONS_H

// C++ standard includes
#include <sstream>
#include <string>

// Poco includes
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Net/HTTPResponse.h>

// AwsMoc includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::SecretsManager {

    /**
   * Secrets manager replication status.
   *
   * Example:
   * <pre>
   * "AddReplicaRegions": [
   *   {
   *     "KmsKeyId": "string",
   *     "Region": "string"
   *   }
   * ],
   * </pre>
   *
   * @author jens.vogt@opitz-consulting.com
   */
    struct AddReplicaRegions {

        /**
     * Region
     */
        std::string region;

        /**
     * KMS key ID
     */
        std::string kmsKeyId;

        /**
     * Converts the DTO to a JSON object.
     *
     * @return DTO as string for logging.
     */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

        /**
     * Converts the DTO to a JSON representation.
     *
     * @return DTO as string for logging.
     */
        [[nodiscard]] std::string ToJson() const;

        /**
     * Converts a JSON representation to s DTO.
     *
     * @param jsonObject JSON object.
     */
        void FromJson(const Poco::JSON::Object::Ptr &jsonObject);

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
        friend std::ostream &operator<<(std::ostream &os, const AddReplicaRegions &r);
    };

}//namespace AwsMock::Dto::SecretsManager

#endif// AWSMOCK_DTO_SECRETSMANAGER_ADD_REPLICA_REGIONS_H

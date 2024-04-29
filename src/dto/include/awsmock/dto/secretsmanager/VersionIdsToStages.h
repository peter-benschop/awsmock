//
// Created by vogje01 on 4/8/24.
//

#ifndef AWSMOCK_DTO_SECRETSMANAGER_VERSION_IDS_TO_STAGES_H
#define AWSMOCK_DTO_SECRETSMANAGER_VERSION_IDS_TO_STAGES_H

// C++ standard includes
#include <map>
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
   * Secrets manager version ID and stages
   *
   * Example:
   * <pre>
   * "EXAMPLE1-90ab-cdef-fedc-ba987SECRET1": [
   *   "AWSPREVIOUS"
   * ],
   * "EXAMPLE2-90ab-cdef-fedc-ba987SECRET2": [
   *   "AWSCURRENT"
   * ]
   * </pre>
   *
   * @author jens.vogt\@opitz-consulting.com
   */
    struct VersionIdsToStages {

        /**
     * Version/stages map
     */
        std::map<std::string, std::vector<std::string>> versions;

        /**
     * Converts the DTO to a JSON representation.
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
        friend std::ostream &operator<<(std::ostream &os, const VersionIdsToStages &r);
    };

}// namespace AwsMock::Dto::SecretsManager

#endif// AWSMOCK_DTO_SECRETSMANAGER_VERSION_IDS_TO_STAGES_H

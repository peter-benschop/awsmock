//
// Created by vogje01 on 06/06/2023.
//

#ifndef AWSMOCK_DTO_DOCKER_PRUNE_CONTAINER_RESPONSE_H
#define AWSMOCK_DTO_DOCKER_PRUNE_CONTAINER_RESPONSE_H

// C++ includes
#include <sstream>
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>

namespace AwsMock::Dto::Docker {

    /**
     * Prune docker response
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct PruneContainerResponse {

        /**
         * Image ID
         */
        std::vector<std::string> containersDeleted;

        /**
         * Space reclaimed
         */
        long spaceReclaimed;

        /**
         * Convert to a JSON string
         *
         * @return JSON string
         */
        std::string ToJson() const {
            return {};
        }

        /**
         * Convert to a JSON string
         *
         * @param jsonString JSON string
         */
        void FromJson(const std::string &jsonString) {

            /* Todo
            try {
                Poco::JSON::Parser parser;
                const Poco::Dynamic::Var result = parser.parse(jsonString);
                auto rootObject = result.extract<Poco::JSON::Object::Ptr>();

                Core::JsonUtils::GetJsonValueLong("SpaceReclaimed", rootObject, spaceReclaimed);
                if (Poco::JSON::Array::Ptr deletedArray = rootObject->getArray("ContainersDeleted"); deletedArray != nullptr) {
                    for (const auto &nt: *deletedArray) {
                        containersDeleted.push_back(nt.convert<std::string>());
                    }
                }

            } catch (Poco::Exception &exc) {
                throw Core::ServiceException(exc.message());
            }*/
        }

        /**
         * Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string
        ToString() const {
            std::stringstream ss;
            ss << *this;
            return ss.str();
        }

        /**
         * Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const PruneContainerResponse &i) {
            os << "PruneContainerResponse=" << i.ToJson();
            return os;
        }
    };

}// namespace AwsMock::Dto::Docker

#endif// AWSMOCK_DTO_DOCKER_PRUNE_CONTAINER_RESPONSE_H

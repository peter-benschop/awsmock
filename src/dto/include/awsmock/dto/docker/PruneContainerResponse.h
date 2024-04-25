//
// Created by vogje01 on 06/06/2023.
//

#ifndef AWSMOCK_DTO_DOCKER_PRUNECONTAINERRESPONSE_H
#define AWSMOCK_DTO_DOCKER_PRUNECONTAINERRESPONSE_H

// C++ includes
#include <sstream>
#include <string>
#include <vector>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::Docker {

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
     * @param jsonString JSON string
     */
        void FromJson(const std::string &jsonString) {

            try {
                Poco::JSON::Parser parser;
                Poco::Dynamic::Var result = parser.parse(jsonString);
                Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

                Core::JsonUtils::GetJsonValueLong("SpaceReclaimed", rootObject, spaceReclaimed);
                Poco::JSON::Array::Ptr deletedArray = rootObject->getArray("ContainersDeleted");
                if (deletedArray != nullptr) {
                    for (const auto &nt: *deletedArray) {
                        containersDeleted.push_back(nt.convert<std::string>());
                    }
                }

            } catch (Poco::Exception &exc) {
                throw Core::ServiceException(exc.message(), 500);
            }
        }

        /**
     * Converts the DTO to a string representation.
     *
     * @return DTO as string for logging.
     */
        [[nodiscard]] std::string
        ToString() const {
            std::stringstream ss;
            ss << (*this);
            return ss.str();
        }

        /**
     * Stream provider.
     *
     * @return output stream
     */
        friend std::ostream &operator<<(std::ostream &os, const PruneContainerResponse &i) {
            os << "PruneContainerResponse={spaceReclaimed='" << i.spaceReclaimed << "' containersDeleted=[";
            for (auto &it: i.containersDeleted) {
                os << it << ",";
            }
            os.seekp(-1, std::ios_base::end);
            os << "]}";
            return os;
        }
    };

}// namespace AwsMock::Dto::Docker

#endif//AWSMOCK_DTO_DOCKER_PRUNECONTAINERRESPONSE_H

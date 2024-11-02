//
// Created by vogje01 on 06/06/2023.
//

#ifndef AWSMOCK_DTO_DOCKER_PORT_H
#define AWSMOCK_DTO_DOCKER_PORT_H

// C++ includes
#include <sstream>
#include <string>
#include <vector>

// AwsMock includes
#include "awsmock/core/JsonUtils.h"
#include "awsmock/core/LogStream.h"
#include "awsmock/core/exception/JsonException.h"

namespace AwsMock::Dto::Docker {

    /**
     * @brief Docker port
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct Port {

        /**
         * @brief Constructor
         */
        explicit Port(const Poco::JSON::Object::Ptr &object);

        /**
         * Private port, means port inside the container
         */
        int privatePort{};

        /**
         * Public port, means port visible from docker host
         */
        int publicPort{};

        /**
         * Port type (tcp,udp, etc.)
         */
        std::string type;

        /**
         * @brief Convert to a JSON string
         *
         * @param object JSON object
         */
        void FromJson(const Poco::JSON::Object::Ptr &object);

        /**
         * @brief Convert to a JSON string
         *
         * @return object JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const Port &c);
    };

}// namespace AwsMock::Dto::Docker

#endif// AWSMOCK_DTO_DOCKER_PORT_H

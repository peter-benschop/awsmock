//
// Created by vogje01 on 06/06/2023.
//

#ifndef AWSMOCK_DTO_DOCKER_MODEL_PLATFORM_H
#define AWSMOCK_DTO_DOCKER_MODEL_PLATFORM_H

// C++ includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>

namespace AwsMock::Dto::Docker {

    /**
     * Docker platform
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct Platform {

        /**
         * Platform name
         */
        std::string name;

        /**
         * Deserialize from a JSON object
         *
         * @param document JSON object
         */
        void FromDocument(const view_or_value<view, value> &document);
    };

}// namespace AwsMock::Dto::Docker

#endif// AWSMOCK_DTO_DOCKER_MODEL_PLATFORM_H

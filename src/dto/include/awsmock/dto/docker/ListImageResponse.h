//
// Created by vogje01 on 06/06/2023.
//

#ifndef AWSMOCK_DTO_DOCKER_LIST_IMAGE_RESPONSE_H
#define AWSMOCK_DTO_DOCKER_LIST_IMAGE_RESPONSE_H

// C++ includes
#include <sstream>
#include <string>
#include <vector>

// AwsMock includes
#include "awsmock/core/exception/JsonException.h"
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/docker/Image.h>

namespace AwsMock::Dto::Docker {

    /**
     * List container request
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct ListImageResponse {

        /**
         * Image list
         */
        std::vector<Image> imageList;

        /**
         * Constructor
         *
         * @param body HTTP response body
         */
        explicit ListImageResponse(const std::string &body);

        /**
         * Convert to a JSON string
         *
         * @param jsonString JSON string
         */
        void FromJson(const std::string &jsonString);

        /**
         * Convert to a JSON string
         *
         * @param object JSON object
         */
        [[nodiscard]] std::string ToJson() const;

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
        friend std::ostream &operator<<(std::ostream &os, const ListImageResponse &r);
    };

}// namespace AwsMock::Dto::Docker

#endif// AWSMOCK_DTO_DOCKER_LIST_IMAGE_RESPONSE_H

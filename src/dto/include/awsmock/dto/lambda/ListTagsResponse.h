//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_LISTTAGSREQUEST_H
#define AWSMOCK_DTO_LAMBDA_LISTTAGSREQUEST_H

// C++ standard includes
#include <sstream>
#include <string>
#include <vector>

// Poco includes
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>

// AwsMock includes
#include "awsmock/dto/lambda/model/Environment.h"

namespace AwsMock::Dto::Lambda {

    struct ListTagsResponse {

        /**
     * Tags
     */
        std::map<std::string, std::string> tags;

        /**
     * Convert to a JSON string
     *
     * @return JSON string
     */
        [[nodiscard]] std::string ToJson();

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
        friend std::ostream &operator<<(std::ostream &os, const ListTagsResponse &r);
    };

}// namespace AwsMock::Dto::Lambda

#endif// AWSMOCK_DTO_LAMBDA_LISTTAGSREQUEST_H

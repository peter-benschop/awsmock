//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_DELETETAGSREQUEST_H
#define AWSMOCK_DTO_LAMBDA_DELETETAGSREQUEST_H

// C++ standard includes
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// Poco includes
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>

// AwsMock includes
#include "awsmock/dto/lambda/model/Environment.h"
#include "awsmock/dto/lambda/model/EphemeralStorage.h"
#include <awsmock/core/JsonUtils.h>

namespace AwsMock::Dto::Lambda {

    struct DeleteTagsRequest {

        /**
     * ARN
     */
        std::string arn;

        /**
     * Tags
     */
        std::vector<std::string> tags;

        /**
     * Constructor
     */
        DeleteTagsRequest(std::string arn, std::vector<std::string> tags) : arn(std::move(arn)), tags(tags) {}

        /**
     * Converts the DTO to a string representation.
     *
     * @return DTO as string for logging.
     */
        [[nodiscard]] std::string ToString() const {
            std::stringstream ss;
            ss << (*this);
            return ss.str();
        }

        /**
     * Stream provider.
     *
     * @return output stream
     */
        friend std::ostream &operator<<(std::ostream &os, const DeleteTagsRequest &r) {
            os << "DeleteTagsRequest={tags='[";
            for (const auto &it: r.tags) {
                os << " tagKey='" << it << "'";
            }
            os << "]}";
            return os;
        }
    };

}// namespace AwsMock::Dto::Lambda

#endif// AWSMOCK_DTO_LAMBDA_DELETETAGSREQUEST_H

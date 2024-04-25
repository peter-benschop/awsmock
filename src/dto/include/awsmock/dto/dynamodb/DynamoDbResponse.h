//
// Created by vogje01 on 3/23/24.
//

#ifndef AWSMOCK_DTO_DYNAMODB_DYNAMODB_RESPONSE_H
#define AWSMOCK_DTO_DYNAMODB_DYNAMODB_RESPONSE_H

// C++ standard includes
#include <map>
#include <string>

namespace AwsMock::Dto::DynamoDb {

    struct DynamoDbResponse {

        /**
     * Body
     */
        std::string body;

        /**
     * Headers
     */
        std::map<std::string, std::string> headers;

        /**
     * Status from DynamoDb docker image
     */
        Poco::Net::HTTPResponse::HTTPStatus status;
    };

}// namespace AwsMock::Dto::DynamoDb

#endif//AWSMOCK_DTO_DYNAMODB_DYNAMODB_RESPONSE_H

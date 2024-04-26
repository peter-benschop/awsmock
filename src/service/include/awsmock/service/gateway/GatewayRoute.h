//
// Created by vogje01 on 4/13/24.
//

#ifndef AWSMOCK_SERVICE_GATEWAY_GATEWAY_ROUTE_H
#define AWSMOCK_SERVICE_GATEWAY_GATEWAY_ROUTE_H

// C++ standard includes
#include <map>
#include <string>
#include <utility>

// AwsMock includes
#include <awsmock/service/common/AbstractHandler.h>

namespace AwsMock::Service {

    enum HandlerType {
        S3,
        SQS,
        SNS,
        LAMBDA,
        TRANSFER,
        COGNITO,
        DYNAMODB,
        SECRETS_MANAGER,
        KMS
    };

    struct GatewayRoute {

        /**
         * Service name
         */
        std::string _name;

        /**
         * Type
         */
        HandlerType _handlerType;
    };

}// namespace AwsMock::Service

#endif//AWSMOCK_SERVICE_GATEWAY_GATEWAY_ROUTE_H

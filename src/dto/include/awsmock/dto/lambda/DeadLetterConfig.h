//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_DEADLETTERCONFIG_H
#define AWSMOCK_DTO_LAMBDA_DEADLETTERCONFIG_H

// C++ standard includes
#include <string>
#include <sstream>
#include <vector>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

// AwsMock includes
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::Lambda {

  struct DeadLetterConfig {

    /**
     * Target ARN
     */
    std::string targetArn = {};

    /**
     * Converts the DTO to a JSON representation.
     *
     * @return DTO as string for logging.
     */
    [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

  };

} // namespace AwsMock::Dto::lambda

#endif // AWSMOCK_DTO_LAMBDA_DEADLETTERCONFIG_H

//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWSMOCK_DTO_COMMON_COMMON_H
#define AWSMOCK_DTO_COMMON_COMMON_H

// C++ standard includes
#include <string>
#include <utility>

// Poco includes
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"

namespace AwsMock::Dto {

  struct CommonDto {

    /**
     * Constructor
     *
     * @param resource AWS resource
     * @param requestId AWS request ID
     */
    CommonDto(std::string resource, std::string requestId) : resource(std::move(resource)), requestId(std::move(requestId)) {}

    /**
     * Resource
     */
    std::string resource = "Unknown resource";

    /**
     * Resource
     */
    std::string requestId = Poco::UUIDGenerator().createRandom().toString();

  };

} // namespace AwsMock::Dto

#endif //AWS_MOCK_DTO_INCLUDE_AWSMOCK_DTO_COMMON_COMMON_H

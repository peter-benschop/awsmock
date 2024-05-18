//
// Created by vogje01 on 5/18/24.
//

#ifndef AWSMOCK_DTO_COGNITO_BASEREQUEST_H
#define AWSMOCK_DTO_COGNITO_BASEREQUEST_H

namespace AwsMock::Dto::Cognito {

    /**
     * @brief Base request
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct BaseRequest {

        /**
         * Request ID
         */
        std::string requestId;

        /**
         * Region
         */
        std::string region;

        /**
         * User
         */
        std::string user;
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_BASEREQUEST_H

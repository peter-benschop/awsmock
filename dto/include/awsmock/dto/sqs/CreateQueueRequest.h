//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_CREATEQUEUEREQUEST_H
#define AWSMOCK_DTO_SQS_CREATEQUEUEREQUEST_H

// C++ standard includes
#include <string>

namespace AwsMock::Dto::SQS {

    struct CreateQueueRequest {

      /**
       * Name
       */
      std::string name;

      /**
       * AWS region
       */
      std::string region;

      /**
       * Owner
       */
      std::string owner;

      /**
       * URL
       */
      std::string url;
    };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_CREATEQUEUEREQUEST_H

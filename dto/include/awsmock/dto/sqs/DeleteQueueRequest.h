//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_DELETEQUEUEREQUEST_H
#define AWSMOCK_DTO_SQS_DELETEQUEUEREQUEST_H

// C++ standard includes
#include <string>

namespace AwsMock::Dto::SQS {

    struct DeleteQueueRequest {

      /**
       * URL
       */
      std::string url;
    };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_DELETEQUEUEREQUEST_H

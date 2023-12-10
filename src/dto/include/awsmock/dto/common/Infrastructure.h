//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWSMOCK_DTO_COMMON_INFRASTRUCTURE_H
#define AWSMOCK_DTO_COMMON_INFRASTRUCTURE_H

// C++ standard includes
#include <string>
#include <utility>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Array.h>
#include <Poco/UUID.h>
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include <awsmock/core/ServiceException.h>
#include <awsmock/entity/sqs/Queue.h>
#include <awsmock/entity/sqs/Message.h>
#include <awsmock/entity/s3/Bucket.h>
#include <awsmock/entity/s3/Object.h>

namespace AwsMock::Dto::Common {

  struct Infrastructure {

    /**
     * S3 buckets
     */
    Database::Entity::S3::BucketList s3Buckets;

    /**
     * S3 objects
     */
    Database::Entity::S3::ObjectList s3Objects;

    /**
     * SQS queues
     */
    Database::Entity::SQS::QueueList sqsQueues;

    /**
     * SQS messages
     */
    Database::Entity::SQS::MessageList sqsMessages;

    /**
     * JSON representation
     *
     * @return Infrastructure as JSON string
     */
    std::string ToJson();
  };

} // namespace AwsMock::Dto

#endif // AWSMOCK_DTO_COMMON_INFRASTRUCTURE_H

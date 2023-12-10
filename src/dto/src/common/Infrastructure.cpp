//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/Infrastructure.h>

namespace AwsMock::Dto::Common {

  std::string Infrastructure::ToJson() {

    try {

      // S3 Bucket array
      Poco::JSON::Array jsonBucketArray;
      for (const auto &bucket : s3Buckets) {
        jsonBucketArray.add(bucket.ToJsonObject());
      }

      // S3 object array
      Poco::JSON::Array jsonObjectArray;
      for (const auto &object : s3Objects) {
        jsonObjectArray.add(object.ToJsonObject());
      }

      // SQS queue array
      Poco::JSON::Array jsonQueueArray;
      for (const auto &queue : sqsQueues) {
        jsonQueueArray.add(queue.ToJsonObject());
      }

      // SQS message array
      Poco::JSON::Array jsonSqsMessageArray;
      for (const auto &message : sqsMessages) {
        jsonSqsMessageArray.add(message.ToJsonObject());
      }

      // SNS topic array
      Poco::JSON::Array jsonTopicArray;
      for (const auto &topic : snsTopics) {
        jsonTopicArray.add(topic.ToJsonObject());
      }

      // SNS message array
      Poco::JSON::Array jsonSnsMessageArray;
      for (const auto &message : snsMessages) {
        jsonSnsMessageArray.add(message.ToJsonObject());
      }

      // Cognito user pools
      Poco::JSON::Array jsonCognitoUserPoolArray;
      for (const auto &userPool : cognitoUserPools) {
        jsonCognitoUserPoolArray.add(userPool.ToJsonObject());
      }

      // Cognito users
      Poco::JSON::Array jsonCognitoUserArray;
      for (const auto &user : cognitoUsers) {
        jsonCognitoUserArray.add(user.ToJsonObject());
      }

      Poco::JSON::Object infrastructureJson;
      infrastructureJson.set("s3-buckets", jsonBucketArray);
      infrastructureJson.set("s3-objects", jsonObjectArray);
      infrastructureJson.set("sqs-queues", jsonQueueArray);
      infrastructureJson.set("sqs-messages", jsonSqsMessageArray);
      infrastructureJson.set("sns-topics", jsonTopicArray);
      infrastructureJson.set("sns-messages", jsonSnsMessageArray);
      infrastructureJson.set("cognito-user-pools", jsonCognitoUserPoolArray);
      infrastructureJson.set("cognito-users", jsonCognitoUserArray);

      Poco::JSON::Object rootJson;
      rootJson.set("infrastructure", infrastructureJson);

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }
}

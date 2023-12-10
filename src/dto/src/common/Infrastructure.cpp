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
      Poco::JSON::Array jsonMessageArray;
      for (const auto &message : sqsMessages) {
        jsonMessageArray.add(message.ToJsonObject());
      }

      Poco::JSON::Object infrastructureJson;
      infrastructureJson.set("s3-buckets", jsonBucketArray);
      infrastructureJson.set("s3-objects", jsonObjectArray);
      infrastructureJson.set("sqs-queues", jsonQueueArray);
      infrastructureJson.set("sqs-messages", jsonMessageArray);

      Poco::JSON::Object rootJson;
      rootJson.set("infrastructure", infrastructureJson);

      std::ostringstream os;
      rootJson.stringify(os);
      std::string tmp = os.str();
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }
}

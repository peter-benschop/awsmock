//
// Created by vogje01 on 06/06/2023.
//

#ifndef AWSMOCK_CORE_AWSUTILS_H
#define AWSMOCK_CORE_AWSUTILS_H

// C++ standard includes
#include <string>

namespace AwsMock::Core {

    class AwsUtils {

    public:

      /**
       * Create Amazon Resource Names (ARNs)
       *
       * @param service AWS service name
       * @param region AWS region
       * @param accountId AWS accountId
       * @param resourceId AWS resourceId
       */
      static std::string CreateArn(const std::string &service, const std::string &region, const std::string &accountId, const std::string &resourceId);

      /**
       * Create S3 Amazon bucket/key ARN
       *
       * @param region AWS region
       * @param accountId AWS account ID
       * @param bucket bucket name
       * @param key object key
       */
      static std::string CreateS3Arn(const std::string &region, const std::string &accountId, const std::string &bucket, const std::string &key);

      /**
       * Create Lambda function ARN
       *
       * @param region AWS region
       * @param accountId AWS account ID
       * @param function lambda function name
       */
      static std::string CreateLambdaArn(const std::string &region, const std::string &accountId, const std::string &function);

      /**
       * Create SQS queue ARN
       *
       * @param region AWS region
       * @param accountId AWS account ID
       * @param queueName name of the queue
       */
      static std::string CreateSQSArn(const std::string &region, const std::string &accountId, const std::string &queueName);

      /**
       * Create SNS topic ARN
       *
       * @param region AWS region
       * @param accountId AWS account ID
       * @param topicName name of the topic
       */
      static std::string CreateSNSArn(const std::string &region, const std::string &accountId, const std::string &topicName);
    };
}
#endif //AWSMOCK_CORE_AWSUTILS_H

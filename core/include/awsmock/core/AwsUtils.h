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
       * @param service AWS service name
       * @param region AWS region
       * @param bucket bucket name
       * @param key object key
       */
      static std::string CreateS3Arn(const std::string &region, const std::string &accountId, const std::string &bucket, const std::string &key);

      /**
       * Create Lambda function ARN
       *
       * @param service AWS service name
       * @param region AWS region
       * @param bucket bucket name
       * @param key object key
       */
      static std::string CreateLambdaArn(const std::string &region, const std::string &accountId, const std::string &function);

      /**
       * Create Lambda function ARN
       *
       * @param service AWS service name
       * @param region AWS region
       * @param queueName name of the queue
       */
      static std::string CreateSQSArn(const std::string &region, const std::string &accountId, const std::string &queueName);
    };
}
#endif //AWSMOCK_CORE_AWSUTILS_H

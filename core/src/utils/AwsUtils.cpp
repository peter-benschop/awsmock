//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/core/AwsUtils.h>

namespace AwsMock::Core {

    std::string AwsUtils::CreateArn(const std::string &service, const std::string &region, const std::string &accountId, const std::string &resourceId) {

        return "arn:aws:" + service + ":" + region + ":" + accountId + ":" + resourceId;
    }

    std::string AwsUtils::CreateS3Arn(const std::string &region, const std::string &accountId, const std::string &bucket, const std::string &key) {

        return CreateArn("s3", region, accountId, bucket + "/" + key);
    }

    std::string AwsUtils::CreateLambdaArn(const std::string &region, const std::string &accountId, const std::string &function) {

        return CreateArn("lambda", region, accountId, "function:" + function);
    }

    std::string AwsUtils::CreateSQSQueueArn(const std::string &region, const std::string &accountId, const std::string &queueName) {

        return CreateArn("sqs", region, accountId, queueName);
    }

    std::string AwsUtils::ConvertSQSQueueArnToUrl(const std::string &queueArn) {
        std::vector<std::string> parts = StringUtils::Split(queueArn, ':');
        return "http://localhost:4567/000000000000/" + parts[5];
    }

    std::string AwsUtils::CreateSNSTopicArn(const std::string &region, const std::string &accountId, const std::string &topicName) {

        return CreateArn("sns", region, accountId, topicName);
    }

    std::string AwsUtils::CreateSNSSubscriptionArn(const std::string &region, const std::string &accountId, const std::string &topicName) {

        return CreateArn("sns", region, accountId, topicName + ":" + Poco::UUIDGenerator().createRandom().toString());
    }
}

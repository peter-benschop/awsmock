//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/core/AwsUtils.h>

namespace AwsMock::Core {

    std::string AwsUtils::CreateArn(const std::string &service, const std::string &region, const std::string &accountId,
                                    const std::string &resourceId) {

        return "arn:aws:" + service + ":" + region + ":" + accountId + ":" + resourceId;
    }

    std::string
    AwsUtils::CreateS3Arn(const std::string &region, const std::string &accountId, const std::string &bucket,
                          const std::string &key) {

        return CreateArn("s3", region, accountId, bucket + "/" + key);
    }

    std::string
    AwsUtils::CreateLambdaArn(const std::string &region, const std::string &accountId, const std::string &function) {

        return CreateArn("lambda", region, accountId, "function:" + function);
    }

    std::string
    AwsUtils::CreateSQSQueueArn(const std::string &region, const std::string &accountId, const std::string &queueName) {

        return CreateArn("sqs", region, accountId, queueName);
    }

    std::string AwsUtils::ConvertSQSQueueArnToUrl(const std::string &queueArn, const std::string &endpoint) {
        std::vector<std::string> parts = StringUtils::Split(queueArn, ':');
        if (parts.size() < 6) {
            std::cerr << "Error, not enough parts" << std::endl;
            return {};
        }
        std::string accountId = parts[4];
        std::string queueName = parts[5];
        parts.clear();
        return "http://" + endpoint + "/" + accountId + "/" + queueName;
    }

    std::string
    AwsUtils::CreateSNSTopicArn(const std::string &region, const std::string &accountId, const std::string &topicName) {

        return CreateArn("sns", region, accountId, topicName);
    }

    std::string AwsUtils::CreateSNSSubscriptionArn(const std::string &region, const std::string &accountId,
                                                   const std::string &topicName) {

        return CreateArn("sns", region, accountId, topicName + ":" + Poco::UUIDGenerator().createRandom().toString());
    }
}

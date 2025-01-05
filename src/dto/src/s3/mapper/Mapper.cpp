//
// Created by vogje01 on 5/10/24.
//

#include <awsmock/dto/s3/mapper/Mapper.h>

namespace AwsMock::Dto::S3 {

    ListObjectVersionsResponse Mapper::map(const ListObjectVersionsRequest &request, const std::vector<Database::Entity::S3::Object> &objectList) {

        ListObjectVersionsResponse response;
        response.region = request.region;
        response.name = request.bucket;
        response.maxKeys = request.maxKeys;
        for (const auto &object: objectList) {
            ObjectVersion version = {
                    .key = object.key,
                    .eTag = object.md5sum,
                    .versionId = object.versionId,
                    .storageClass = "STANDARD",
                    .isLatest = false,
                    .size = object.size,
                    .lastModified = object.modified,
            };
            version.owner = {.id = object.owner};

            response.versions.emplace_back(version);
        }
        return response;
    }

    GetBucketResponse Mapper::map(const GetBucketRequest &request, Database::Entity::S3::Bucket &bucket) {
        GetBucketResponse response = {
                .id = bucket.oid,
                .region = bucket.region,
                .bucket = bucket.name,
                .arn = bucket.arn,
                .owner = bucket.owner,
                .versionStatus = BucketVersionStatusToString(bucket.versionStatus),
                .size = bucket.size,
                .keys = bucket.keys,
                .lambdaConfigurations = map(bucket.lambdaNotifications),
                .queueConfigurations = map(bucket.queueNotifications),
                .created = bucket.created,
                .modified = bucket.modified};

        return response;
    }

    Database::Entity::S3::Bucket Mapper::map(const Dto::S3::Bucket &bucketDto) {
        Database::Entity::S3::Bucket bucket;
        bucket.region = bucketDto.region;
        bucket.name = bucketDto.bucketName;
        bucket.owner = bucketDto.owner;
        bucket.size = bucketDto.size;
        bucket.keys = bucketDto.keys;
        bucket.versionStatus = Database::Entity::S3::BucketVersionStatusFromString(bucketDto.versionStatus);
        //bucket.lambdaNotifications = map();
        bucket.created = bucketDto.created;
        bucket.modified = bucketDto.modified;
        return bucket;
    }

    auto Mapper::map(const std::vector<Database::Entity::S3::LambdaNotification> &lambdaNotifications) -> std::vector<Dto::S3::LambdaConfiguration> {
        std::vector<LambdaConfiguration> lambdaConfigurations;
        for (const auto &lambdaNotification: lambdaNotifications) {
            LambdaConfiguration lambdaConfiguration;
            lambdaConfiguration.id = lambdaNotification.id;
            lambdaConfiguration.lambdaArn = lambdaNotification.lambdaArn;
            lambdaConfiguration.events = map(lambdaNotification.events);
            lambdaConfigurations.emplace_back(lambdaConfiguration);
        }
        return lambdaConfigurations;
    }

    std::vector<Database::Entity::S3::LambdaNotification> Mapper::map(const std::vector<Dto::S3::LambdaConfiguration> &lambdaConfigurations) {
        std::vector<Database::Entity::S3::LambdaNotification> lambdaNotifications;
        for (const auto &lambdaConfiguration: lambdaConfigurations) {
            Database::Entity::S3::LambdaNotification lambdaNotification;
            lambdaNotification.id = lambdaConfiguration.id;
            lambdaNotification.lambdaArn = lambdaConfiguration.lambdaArn;
            //lambdaNotification.events = map(lambdaConfiguration.events);
            lambdaNotifications.emplace_back(lambdaNotification);
        }
        return lambdaNotifications;
    }

    std::vector<QueueConfiguration> Mapper::map(const std::vector<Database::Entity::S3::QueueNotification> &queueNotifications) {
        std::vector<QueueConfiguration> queueConfigurations;
        for (const auto &queueNotification: queueNotifications) {
            QueueConfiguration queueConfiguration;
            queueConfiguration.id = queueNotification.id;
            queueConfiguration.queueArn = queueNotification.queueArn;
            queueConfiguration.events = map(queueNotification.events);
            queueConfigurations.emplace_back(queueConfiguration);
        }
        return queueConfigurations;
    }

    std::vector<Dto::S3::TopicConfiguration> Mapper::map(const std::vector<Database::Entity::S3::TopicNotification> &topicNotifications) {
        std::vector<TopicConfiguration> topicConfigurations;
        for (const auto &topicNotification: topicNotifications) {
            Dto::S3::TopicConfiguration topicConfiguration;
            topicConfiguration.id = topicNotification.id;
            topicConfiguration.topicArn = topicNotification.topicArn;
            topicConfiguration.events = map(topicNotification.events);
            topicConfigurations.emplace_back(topicConfiguration);
        }
        return topicConfigurations;
    }

    std::vector<NotificationEventType> Mapper::map(const std::vector<std::string> &eventStrs) {
        std::vector<NotificationEventType> events;
        for (const auto &event: eventStrs) {
            events.emplace_back(EventTypeFromString(event));
        }
        return events;
    }
}// namespace AwsMock::Dto::S3
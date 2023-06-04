//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_DTO_S3_EVENTNOTIFICATION_H
#define AWSMOCK_DTO_S3_EVENTNOTIFICATION_H

// C++ standard includes
#include <string>
#include <vector>

// Poco includes
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"

// AwsMock includes
#include <awsmock/core/DateTimeUtils.h>

namespace AwsMock::Dto::S3::EventNotification {

    /**
     * {
     *   "Records":[
     *       {
     *        "eventVersion":"2.2",
     *        "eventSource":"aws:s3",
     *        "awsRegion":"us-west-2",
     *        "eventTime":"The time, in ISO-8601 format, for example, 1970-01-01T00:00:00.000Z, when Amazon S3 finished processing the request",
     *        "eventName":"event-type",
     *        "userIdentity":{
     *           "principalId":"Amazon-customer-ID-of-the-user-who-caused-the-event"
     *        },
     *        "requestParameters":{
     *           "sourceIPAddress":"ip-address-where-request-came-from"
     *        },
     *        "responseElements":{
     *           "x-amz-request-id":"Amazon S3 generated request ID",
     *           "x-amz-id-2":"Amazon S3 host that processed the request"
     *       },
     *        "s3":{
     *           "s3SchemaVersion":"1.0",
     *           "configurationId":"ID found in the bucket notification configuration",
     *           "bucket":{
     *              "name":"bucket-name",
     *              "ownerIdentity":{
     *                 "principalId":"Amazon-customer-ID-of-the-bucket-owner"
     *              },
     *              "arn":"bucket-ARN"
     *           },
     *           "object":{
     *              "key":"object-key",
     *              "size":"object-size in bytes",
     *              "eTag":"object eTag",
     *              "versionId":"object version if bucket is versioning-enabled, otherwise null",
     *              "sequencer": "a string representation of a hexadecimal value used to determine event sequence, only used with PUTs and DELETEs"
     *           }
     *        },
     *        "glacierEventData": {
     *           "restoreEventData": {
     *              "lifecycleRestorationExpiryTime": "The time, in ISO-8601 format, for example, 1970-01-01T00:00:00.000Z, of Restore Expiry",
     *              "lifecycleRestoreStorageClass": "Source storage class for restore"
     *           }
     *        }
     *     }
     *   ]
     * }
     */
    struct UserIdentity {

      std::string principalId;

    };

    struct RequestParameter{

      std::string requestParameters;

      std::string sourceIPAddress;

    };

    struct ResponseElements{

      std::string xAmzRequestId;

      std::string xAmzId2;

    };

    struct OwnerIdentity {

      std::string principalId;

    };

    struct Bucket {

      std::string name;

      OwnerIdentity ownerIdentity;

      std::string arn;

    };

    struct Object {

      std::string key;

      long size;

      std::string etag;

      std::string versionId;

      std::string sequencer;

    };

    struct S3 {

      std::string s3SchemaVersion = "1.0";

      std::string configurationId;

      Bucket bucket;

      Object object;

    };

    struct RestoreEventData {

      std::string lifecycleRestorationExpiryTime;

      std::string lifecycleRestoreStorageClass;

    };

    struct GlacierEventData {

      RestoreEventData restoreEventData;

    };

    struct Record {

      std::string eventVersion = "2.2";

      std::string eventSource = "aws:s3";

      std::string eventTime = Core::DateTimeUtils::AwsDatetimeNow();

      std::string eventName;

      UserIdentity userIdentity;

      RequestParameter requestParameter;

      ResponseElements responseElements;

      S3 s3;

      GlacierEventData glacierEventData;

    };

    struct EventNotification {

      std::vector<Record> records;

    };
}
#endif //AWSMOCK_DTO_S3_EVENTNOTIFICATION_H

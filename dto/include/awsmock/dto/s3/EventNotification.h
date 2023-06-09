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

namespace AwsMock::Dto::S3 {

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

      /**
       * AWS principal ID
       */
      std::string principalId;

      /**
       * Converts the DTO to a JSON representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] Poco::JSON::Object ToJsonObject() const {
          try {
              Poco::JSON::Object rootJson;
              rootJson.set("principalId", principalId);
              return rootJson;
          } catch (Poco::Exception &exc) {
              throw Core::ServiceException(exc.message(), 500);
          }
      }

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const UserIdentity &r) {
          os << "UserIdentity={principalId='" + r.principalId + "'}";
          return os;
      }

    };

    struct RequestParameter {

      /**
       * Request parameters
       */
      std::string requestParameters;

      /**
       * Source IP address
       */
      std::string sourceIPAddress;

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const RequestParameter &r) {
          os << "RequestParameter={requestParameters='" + r.requestParameters + "' sourceIPAddress='" + r.sourceIPAddress + "'}";
          return os;
      }

    };

    struct ResponseElements {

      /**
       * Request ID
       */
      std::string xAmzRequestId;

      /**
       * ID2
       */
      std::string xAmzId2;

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const ResponseElements &r) {
          os << "ResponseElements={xAmzRequestId='" + r.xAmzRequestId + "' xAmzId2='" + r.xAmzId2 + "'}";
          return os;
      }
    };

    struct OwnerIdentity {

      std::string principalId;

      /**
       * Converts the DTO to a JSON representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] Poco::JSON::Object ToJsonObject() const {

          try {

              Poco::JSON::Object rootJson;
              rootJson.set("principalId", principalId);
              return rootJson;

          } catch (Poco::Exception &exc) {
              throw Core::ServiceException(exc.message(), 500);
          }
      }

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const OwnerIdentity &o) {
          os << "OwnerIdentity={principalId='" + o.principalId + "'}";
          return os;
      }

    };

    struct Bucket {

      /**
       * Bucket name
       */
      std::string name;

      /**
       * Owner
       */
      OwnerIdentity ownerIdentity;

      /**
       * ARN
       */
      std::string arn;

      /**
       * Converts the DTO to a JSON representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] Poco::JSON::Object ToJsonObject() const {

          try {

              Poco::JSON::Object rootJson;
              rootJson.set("name", name);
              rootJson.set("ownerIdentity", ownerIdentity.ToJsonObject());
              rootJson.set("arn", arn);
              return rootJson;

          } catch (Poco::Exception &exc) {
              throw Core::ServiceException(exc.message(), 500);
          }
      }

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const Bucket &s) {
          os << "Bucket={name='" + s.name + "' ownerIdentity='" + s.ownerIdentity.ToString() + "' arn='" + s.arn + "'}";
          return os;
      }

    };

    struct Object {

      /**
       * S3 object key
       */
      std::string key;

      /**
       * Object file size
       */
      long size;

      /**
       * Etag
       */
      std::string etag;

      /**
       * Object version
       */
      std::string versionId;

      /**
       * S3 sequencer
       */
      std::string sequencer;

      /**
       * Converts the DTO to a JSON representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] Poco::JSON::Object ToJsonObject() const {

          try {
              Poco::JSON::Object rootJson;

              rootJson.set("key", key);
              rootJson.set("size", size);
              rootJson.set("etag", etag);
              rootJson.set("versionId", versionId);
              rootJson.set("sequencer", sequencer);

              return rootJson;
          } catch (Poco::Exception &exc) {
              throw Core::ServiceException(exc.message(), 500);
          }
      }

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const Object &o) {
          os << "Object={key='" + o.key + "' size='" + std::to_string(o.size) + "' etag='" + o.etag + "' versionId='" + o.versionId +
              "' sequencer='" + o.sequencer + "'}";
          return os;
      }

    };

    struct S3 {

      /**
       * Schema version
       */
      std::string s3SchemaVersion = "1.0";

      /**
       * S3 event configuration ID
       */
      std::string configurationId;

      /**
       * S3 bucket
       */
      Bucket bucket;

      /**
       * S3 object
       */
      Object object;

      /**
       * Converts the DTO to a JSON representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] Poco::JSON::Object ToJsonObject() const {

          try {

              Poco::JSON::Object rootJson;
              rootJson.set("s3SchemaVersion", s3SchemaVersion);
              rootJson.set("configurationId", configurationId);
              rootJson.set("bucket", bucket.ToJsonObject());
              rootJson.set("object", object.ToJsonObject());
              return rootJson;

          } catch (Poco::Exception &exc) {
              throw Core::ServiceException(exc.message(), 500);
          }
      }

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const S3 &s) {
          os << "S3={s3SchemaVersion='" + s.s3SchemaVersion + "' configurationId='" + s.configurationId + "' bucket='" + s.bucket.ToString() +
              "' object='" + s.object.ToString() + "'}";
          return os;
      }

    };

    struct Record {

      /**
       * Record version
       */
      std::string eventVersion = "2.2";

      /**
       * Event source
       */
      std::string eventSource = "aws:s3";

      /**
       * Region
       */
      std::string region;

      /**
       * Event time
       */
      std::string eventTime = Core::DateTimeUtils::AwsDatetimeNow();

      /**
       * Event name
       */
      std::string eventName;

      /**
       * Event user
       */
      UserIdentity userIdentity;

      /**
       * Event request parameter
       */
      RequestParameter requestParameter;

      /**
       * Response element
       */
      ResponseElements responseElements;

      /**
       * S3 event parameter
       */
      S3 s3;

      /**
       * Converts the DTO to a JSON representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] Poco::JSON::Object ToJsonObject() const {

          try {

              Poco::JSON::Object rootJson;
              rootJson.set("eventVersion", eventVersion);
              rootJson.set("eventSource", eventSource);
              rootJson.set("awsRegion", region);
              rootJson.set("eventTime", eventTime);
              rootJson.set("eventName", eventName);
              rootJson.set("userIdentity", userIdentity.ToJsonObject());
              rootJson.set("s3", s3.ToJsonObject());
              return rootJson;

          } catch (Poco::Exception &exc) {
              throw Core::ServiceException(exc.message(), 500);
          }
      }

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const Record &r) {
          os << "Record={eventVersion='" + r.eventVersion + "' eventSource='" + r.eventSource + "' region='" + r.region + "' eventTime='" + r.eventTime +
              "' eventName='" + r.eventName + "' userIdentity='" + r.userIdentity.ToString() + "' requestParameter='" + r.requestParameter.ToString() +
              "' responseElements='" + r.responseElements.ToString() + "' s3='" + r.s3.ToString() + "'}";
          return os;
      }

    };

    struct EventNotification {

      /**
       * S3 event record
       */
      std::vector<Record> records;

      /**
       * Converts the DTO to a JSON representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToJson() const {

          try {
              Poco::JSON::Object rootJson;
              Poco::JSON::Array recordsJsonArray;
              for (const auto &record : records) {
                  recordsJsonArray.add(record.ToJsonObject());
              }
              rootJson.set("Records", recordsJsonArray);

              std::ostringstream os;
              rootJson.stringify(os);
              return os.str();

          } catch (Poco::Exception &exc) {
              throw Core::ServiceException(exc.message(), 500);
          }
      }

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const EventNotification &e) {
          os << "EventNotification={";
          for (const auto &r : e.records) {
              os << r.ToString();
          }
          os << "'}";
          return os;
      }

    };
}
#endif //AWSMOCK_DTO_S3_EVENTNOTIFICATION_H

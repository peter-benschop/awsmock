//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_DTO_S3_EVENT_NOTIFICATION_H
#define AWSMOCK_DTO_S3_EVENT_NOTIFICATION_H

// C++ standard includes
#include <chrono>
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/lambda/model/UserIdentity.h>
#include <awsmock/dto/s3/model/Bucket.h>
#include <awsmock/dto/s3/model/UserIdentity.h>

namespace AwsMock::Dto::S3 {

    using std::chrono::system_clock;

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
     *           "x-amz-request-userPoolId":"Amazon S3 generated request ID",
     *           "x-amz-userPoolId-2":"Amazon S3 host that processed the request"
     *        },
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
     *               "key":"object-key",
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
            ss << *this;
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
            ss << *this;
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

        /**
         * Principal ID
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
                throw Core::JsonException(exc.message());
            }
        }

        /**
         * Converts a JSON representation to s DTO.
         *
         * @param jsonObject JSON object.
         */
        void FromJson(const Poco::JSON::Object::Ptr &jsonObject) {

            try {
                Core::JsonUtils::GetJsonValueString("principalId", jsonObject, principalId);
            } catch (Poco::Exception &exc) {
                log_error << exc.message();
                throw Core::JsonException(exc.message());
            }
        }

        /**
         * Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const {
            std::stringstream ss;
            ss << *this;
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

    struct Object {

        /**
         * S3 object key
         */
        std::string key;

        /**
         * Object file size
         */
        long size = 0;

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
                throw Core::JsonException(exc.message());
            }
        }

        /**
         * Converts a JSON representation to s DTO.
         *
         * @param jsonObject JSON object
         */
        void FromJson(const Poco::JSON::Object::Ptr &jsonObject) {

            try {
                Core::JsonUtils::GetJsonValueString("key", jsonObject, key);
                Core::JsonUtils::GetJsonValueLong("size", jsonObject, size);
                Core::JsonUtils::GetJsonValueString("etag", jsonObject, etag);
                Core::JsonUtils::GetJsonValueString("versionId", jsonObject, versionId);
                Core::JsonUtils::GetJsonValueString("sequencer", jsonObject, sequencer);
            } catch (Poco::Exception &exc) {
                log_error << exc.message();
                throw Core::JsonException(exc.message());
            }
        }

        /**
         * Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const {
            std::stringstream ss;
            ss << *this;
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
                log_error << exc.message();
                throw Core::JsonException(exc.message());
            }
        }

        /**
         * Converts a JSON representation to s DTO.
         *
         * @param jsonObject JSON object.
         */
        void FromJson(Poco::JSON::Object::Ptr jsonObject) {

            try {
                Core::JsonUtils::GetJsonValueString("s3SchemaVersion", jsonObject, s3SchemaVersion);
                Core::JsonUtils::GetJsonValueString("configurationId", jsonObject, configurationId);
                if (jsonObject->has("bucket")) {
                    // TODO: FIx me
                    //bucket.FromJson(jsonObject->getObject("bucket"));
                }
                if (jsonObject->has("object")) {
                    object.FromJson(jsonObject->getObject("object"));
                }

            } catch (Poco::Exception &exc) {
                log_error << exc.message();
                throw Core::JsonException(exc.message());
            }
        }

        /**
         * Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const {
            std::stringstream ss;
            ss << *this;
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
        system_clock::time_point eventTime = system_clock::now();

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
         * @brief Converts the DTO to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const {

            return Core::JsonUtils::ToJsonString(ToJsonObject());
        }

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
                rootJson.set("eventTime", Core::DateTimeUtils::ToISO8601(eventTime));
                rootJson.set("eventName", eventName);
                rootJson.set("userIdentity", userIdentity.ToJsonObject());
                rootJson.set("s3", s3.ToJsonObject());
                return rootJson;

            } catch (Poco::Exception &exc) {
                log_error << exc.message();
                throw Core::JsonException(exc.message());
            }
        }

        /**
         * Converts a JSON representation to s DTO.
         *
         * @param object JSON object.
         */
        void FromJson(Poco::JSON::Object::Ptr object) {

            try {
                Core::JsonUtils::GetJsonValueString("eventVersion", object, eventVersion);
                Core::JsonUtils::GetJsonValueString("eventSource", object, eventSource);
                Core::JsonUtils::GetJsonValueString("awsRegion", object, region);
                Core::JsonUtils::GetJsonValueDate("eventTime", object, eventTime);
                Core::JsonUtils::GetJsonValueString("eventName", object, eventName);
                s3.FromJson(object->getObject("s3"));

            } catch (Poco::Exception &exc) {
                log_error << exc.message();
                throw Core::JsonException(exc.message());
            }
        }

        /**
         * Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const {
            std::stringstream ss;
            ss << *this;
            return ss.str();
        }

        /**
         * Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const Record &r) {
            os << "Record=" << r.ToJson();
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

                if (!records.empty()) {
                    Poco::JSON::Array recordsJsonArray;
                    for (const auto &record: records) {
                        recordsJsonArray.add(record.ToJsonObject());
                    }
                    rootJson.set("Records", recordsJsonArray);
                }

                return Core::JsonUtils::ToJsonString(rootJson);

            } catch (Poco::Exception &exc) {
                log_error << exc.message();
                throw Core::JsonException(exc.message());
            }
        }

        /**
         * Converts a JSON representation to s DTO.
         *
         * @param jsonString JSON string.
         */
        void FromJson(const std::string &jsonString) {

            try {
                Poco::JSON::Parser parser;
                Poco::Dynamic::Var result = parser.parse(jsonString);
                const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

                // Record parsing
                if (rootObject->has("Records")) {
                    Poco::JSON::Array::Ptr recordArray = rootObject->getArray("Records");
                    if (recordArray != nullptr) {
                        for (const auto &it: *recordArray) {
                            Record record;
                            record.FromJson(it.extract<Poco::JSON::Object::Ptr>());
                            records.push_back(record);
                        }
                    }
                }
            } catch (Poco::Exception &exc) {
                log_error << exc.message();
                throw Core::JsonException(exc.message());
            }
        }

        /**
         * Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const {
            std::stringstream ss;
            ss << *this;
            return ss.str();
        }

        /**
         * Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const EventNotification &e) {
            os << "EventNotification={";
            for (const auto &r: e.records) {
                os << r.ToString();
            }
            os << "'}";
            return os;
        }
    };

}// namespace AwsMock::Dto::S3

#endif// AWSMOCK_DTO_S3_EVENT_NOTIFICATION_H

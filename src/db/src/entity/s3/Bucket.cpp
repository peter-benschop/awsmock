//
// Created by vogje01 on 03/09/2023.
//

#include "awsmock/entity/s3/Bucket.h"

namespace AwsMock::Database::Entity::S3 {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;

    bool Bucket::HasNotification(const std::string &eventName) {
        return find_if(notifications.begin(), notifications.end(), [eventName](const BucketNotification &eventNotification) {
                   return eventNotification.event == eventName;
               }) != notifications.end();
    }

    bool Bucket::HasQueueNotification(const std::string &eventName) {
        return find_if(queueNotifications.begin(), queueNotifications.end(), [eventName](const QueueNotification &notification) {
                   return std::find(notification.events.begin(), notification.events.end(), eventName) != notification.events.end();
               }) != queueNotifications.end();
    }

    bool Bucket::HasTopicNotification(const std::string &eventName) {
        return find_if(topicNotifications.begin(), topicNotifications.end(), [eventName](const TopicNotification &notification) {
                   return std::find(notification.events.begin(), notification.events.end(), eventName) != notification.events.end();
               }) != topicNotifications.end();
    }

    bool Bucket::HasLambdaNotification(const std::string &eventName) {
        return find_if(lambdaNotifications.begin(), lambdaNotifications.end(), [eventName](const LambdaNotification &notification) {
                   return std::find(notification.events.begin(), notification.events.end(), eventName) != notification.events.end();
               }) != lambdaNotifications.end();
    }

    BucketNotification Bucket::GetNotification(const std::string &eventName) {
        auto it =
                find_if(notifications.begin(), notifications.end(), [eventName](const BucketNotification &eventNotification) {
                    return eventNotification.event == eventName;
                });
        return *it;
    }

    QueueNotification Bucket::GetQueueNotification(const std::string &eventName) {
        return *find_if(queueNotifications.begin(), queueNotifications.end(), [eventName](const QueueNotification &eventNotification) {
            return std::find(eventNotification.events.begin(), eventNotification.events.end(), eventName) != eventNotification.events.end();
        });
    }

    TopicNotification Bucket::GetTopicNotification(const std::string &eventName) {
        return *find_if(topicNotifications.begin(), topicNotifications.end(), [eventName](const TopicNotification &eventNotification) {
            return std::find(eventNotification.events.begin(), eventNotification.events.end(), eventName) != eventNotification.events.end();
        });
    }

    LambdaNotification Bucket::GetLambdaNotification(const std::string &eventName) {
        return *find_if(lambdaNotifications.begin(), lambdaNotifications.end(), [eventName](const LambdaNotification &eventNotification) {
            return std::find(eventNotification.events.begin(), eventNotification.events.end(), eventName) != eventNotification.events.end();
        });
    }

    bool Bucket::IsVersioned() const {
        return versionStatus == ENABLED;
    }

    view_or_value<view, value> Bucket::ToDocument() const {

        // Bucket notification are deprecated, should be removed at a certain point
        auto notificationsDoc = bsoncxx::builder::basic::array{};
        for (const auto &notification: notifications) {
            notificationsDoc.append(notification.ToDocument());
        }

        // Queue notifications
        auto queueNotificationsDoc = bsoncxx::builder::basic::array{};
        for (const auto &notification: queueNotifications) {
            queueNotificationsDoc.append(notification.ToDocument());
        }

        // Topic notifications
        auto topicNotificationsDoc = bsoncxx::builder::basic::array{};
        for (const auto &notification: topicNotifications) {
            topicNotificationsDoc.append(notification.ToDocument());
        }

        // Lambda notifications
        auto lambdaNotificationsDoc = bsoncxx::builder::basic::array{};
        for (const auto &notification: lambdaNotifications) {
            lambdaNotificationsDoc.append(notification.ToDocument());
        }

        view_or_value<view, value> bucketDoc = make_document(
                kvp("region", region),
                kvp("name", name),
                kvp("owner", owner),
                kvp("notifications", notificationsDoc),
                kvp("queueNotifications", queueNotificationsDoc),
                kvp("topicNotifications", topicNotificationsDoc),
                kvp("lambdaNotifications", lambdaNotificationsDoc),
                kvp("versionStatus", BucketVersionStatusToString(versionStatus)),
                kvp("created", MongoUtils::ToBson(created)),
                kvp("modified", MongoUtils::ToBson(modified)));

        return bucketDoc;
    }

    void Bucket::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        oid = mResult.value()["_id"].get_oid().value.to_string();
        region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
        name = bsoncxx::string::to_string(mResult.value()["name"].get_string().value);
        owner = bsoncxx::string::to_string(mResult.value()["owner"].get_string().value);
        versionStatus = BucketVersionStatusFromString(bsoncxx::string::to_string(mResult.value()["versionStatus"].get_string().value));
        created = MongoUtils::FromBson(bsoncxx::types::b_date(mResult.value()["created"].get_date()));
        modified = MongoUtils::FromBson(bsoncxx::types::b_date(mResult.value()["modified"].get_date()));

        // Deprecated (should be removed)
        if (mResult.value().find("notifications") != mResult.value().end()) {
            bsoncxx::array::view notificationView{mResult.value()["notifications"].get_array().value};
            for (bsoncxx::array::element notificationElement: notificationView) {
                BucketNotification notification{
                        .event = bsoncxx::string::to_string(notificationElement["event"].get_string().value),
                        .notificationId = bsoncxx::string::to_string(notificationElement["notificationId"].get_string().value),
                        .queueArn = bsoncxx::string::to_string(notificationElement["queueArn"].get_string().value),
                        .lambdaArn = bsoncxx::string::to_string(notificationElement["lambdaArn"].get_string().value)};
                notifications.push_back(notification);
            }
        }

        // SQS queue notification configuration
        if (mResult.value().find("queueNotifications") != mResult.value().end()) {
            bsoncxx::array::view notificationView{mResult.value()["queueNotifications"].get_array().value};
            for (bsoncxx::array::element notificationElement: notificationView) {
                QueueNotification notification;
                queueNotifications.emplace_back(notification.FromDocument(notificationElement.get_document()));
            }
        }

        // SNS topic notification configuration
        if (mResult.value().find("topicNotifications") != mResult.value().end()) {
            bsoncxx::array::view notificationView{mResult.value()["topicNotifications"].get_array().value};
            for (bsoncxx::array::element notificationElement: notificationView) {
                TopicNotification notification;
                topicNotifications.emplace_back(notification.FromDocument(notificationElement.get_document()));
            }
        }

        // Lambda function notification configuration
        if (mResult.value().find("lambdaNotifications") != mResult.value().end()) {
            bsoncxx::array::view notificationView{mResult.value()["lambdaNotifications"].get_array().value};
            for (bsoncxx::array::element notificationElement: notificationView) {
                LambdaNotification notification;
                lambdaNotifications.emplace_back(notification.FromDocument(notificationElement.get_document()));
            }
        }
    }

    Poco::JSON::Object Bucket::ToJsonObject() const {

        Poco::JSON::Object jsonObject;
        jsonObject.set("region", region);
        jsonObject.set("name", name);
        jsonObject.set("owner", owner);
        jsonObject.set("versionStatus", BucketVersionStatusToString(versionStatus));

        // Bucket notifications (deprecated)
        if (!notifications.empty()) {
            Poco::JSON::Array jsonArray;
            for (const auto &notification: notifications) {
                jsonArray.add(notification.ToJsonObject());
            }
            jsonObject.set("notifications", jsonArray);
        }

        // Queue notifications
        if (!queueNotifications.empty()) {
            Poco::JSON::Array jsonArray;
            for (const auto &notification: queueNotifications) {
                jsonArray.add(notification.ToJsonObject());
            }
            jsonObject.set("queueNotifications", jsonArray);
        }

        // Topic notifications
        if (!queueNotifications.empty()) {
            Poco::JSON::Array jsonArray;
            for (const auto &notification: topicNotifications) {
                jsonArray.add(notification.ToJsonObject());
            }
            jsonObject.set("topicNotifications", jsonArray);
        }

        // Lambda notifications
        if (!lambdaNotifications.empty()) {
            Poco::JSON::Array jsonArray;
            for (const auto &notification: lambdaNotifications) {
                jsonArray.add(notification.ToJsonObject());
            }
            jsonObject.set("topicNotifications", jsonArray);
        }
        return jsonObject;
    }

    void Bucket::FromJsonObject(Poco::JSON::Object::Ptr jsonObject) {

        Core::JsonUtils::GetJsonValueString("region", jsonObject, region);
        Core::JsonUtils::GetJsonValueString("name", jsonObject, name);
        Core::JsonUtils::GetJsonValueString("owner", jsonObject, owner);
        std::string versionStatusStr;
        Core::JsonUtils::GetJsonValueString("versionStatus", jsonObject, versionStatusStr);
        versionStatus = BucketVersionStatusFromString(versionStatusStr);

        if (jsonObject->has("notifications")) {
            Poco::JSON::Array::Ptr jsonNotificationArray = jsonObject->getArray("notifications");
            for (int i = 0; i < jsonNotificationArray->size(); i++) {
                BucketNotification nofication;
                nofication.FromJsonObject(jsonNotificationArray->getObject(i));
                notifications.emplace_back(nofication);
            }
        }

        if (jsonObject->has("queueNotifications")) {
            Poco::JSON::Array::Ptr jsonNotificationArray = jsonObject->getArray("queueNotifications");
            for (int i = 0; i < jsonNotificationArray->size(); i++) {
                QueueNotification notification;
                notification.FromJsonObject(jsonNotificationArray->getObject(i));
                queueNotifications.emplace_back(notification);
            }
        }
    }

    std::string Bucket::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Bucket &b) {
        os << "Bucket=" << bsoncxx::to_json(b.ToDocument());
        return os;
    }
}// namespace AwsMock::Database::Entity::S3
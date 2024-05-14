//
// Created by vogje01 on 01/06/2023.
//

#include <awsmock/entity/sns/Topic.h>

namespace AwsMock::Database::Entity::SNS {

    bool Topic::HasSubscription(const Subscription &subscription) {
        return find_if(subscriptions.begin(), subscriptions.end(), [subscription](const Subscription &s) {
                   return s.protocol == subscription.protocol && s.endpoint == subscription.endpoint;
               }) != subscriptions.end();
    }

    view_or_value<view, value> Topic::ToDocument() const {

        auto subscriptionDocs = bsoncxx::builder::basic::array{};
        for (const auto &subscription: subscriptions) {
            subscriptionDocs.append(subscription.ToDocument());
        }

        auto tagsDoc = bsoncxx::builder::basic::document{};
        if (!tags.empty()) {
            for (const auto &t: tags) {
                tagsDoc.append(kvp(t.first, t.second));
            }
        }

        view_or_value<view, value> topicDoc = make_document(
                kvp("region", region),
                kvp("topicName", topicName),
                kvp("owner", owner),
                kvp("topicUrl", topicUrl),
                kvp("topicArn", topicArn),
                kvp("subscriptions", subscriptionDocs),
                kvp("attributes", topicAttribute.ToDocument()),
                kvp("tags", tagsDoc),
                kvp("created", MongoUtils::ToBson(created)),
                kvp("modified", MongoUtils::ToBson(modified)));

        return topicDoc;
    }

    void Topic::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        oid = mResult.value()["_id"].get_oid().value.to_string();
        region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
        topicName = bsoncxx::string::to_string(mResult.value()["topicName"].get_string().value);
        owner = bsoncxx::string::to_string(mResult.value()["owner"].get_string().value);
        topicUrl = bsoncxx::string::to_string(mResult.value()["topicUrl"].get_string().value);
        topicArn = bsoncxx::string::to_string(mResult.value()["topicArn"].get_string().value);
        topicAttribute.FromDocument(mResult.value()["attributes"].get_document().view());
        created = MongoUtils::FromBson(bsoncxx::types::b_date(mResult.value()["created"].get_date()));
        modified = MongoUtils::FromBson(bsoncxx::types::b_date(mResult.value()["modified"].get_date()));

        // Subscriptions
        if (mResult.value().find("subscriptions") != mResult.value().end()) {
            bsoncxx::array::view subscriptionsView{mResult.value()["subscriptions"].get_array().value};
            for (const bsoncxx::array::element &subscriptionElement: subscriptionsView) {
                Subscription subscription{
                        .protocol = bsoncxx::string::to_string(subscriptionElement["protocol"].get_string().value),
                        .endpoint = bsoncxx::string::to_string(subscriptionElement["endpoint"].get_string().value),
                        .subscriptionArn = bsoncxx::string::to_string(subscriptionElement["subscriptionArn"].get_string().value)};
                subscriptions.push_back(subscription);
            }
        }

        // Get tags
        if (mResult.value().find("tags") != mResult.value().end()) {
            bsoncxx::document::view tagsView = mResult.value()["tags"].get_document().value;
            for (const bsoncxx::document::element &tagElement: tagsView) {
                std::string key = bsoncxx::string::to_string(tagElement.key());
                std::string value = bsoncxx::string::to_string(tagsView[key].get_string().value);
                tags.emplace(key, value);
            }
        }
    }

    Poco::JSON::Object Topic::ToJsonObject() const {

        try {

            Poco::JSON::Object jsonObject;
            jsonObject.set("region", region);
            jsonObject.set("topicName", topicName);
            jsonObject.set("owner", owner);
            jsonObject.set("topicUrl", topicUrl);
            jsonObject.set("topicArn", topicArn);
            jsonObject.set("topicAttribute", topicAttribute.ToJsonObject());

            // Subscription array
            if (!subscriptions.empty()) {
                Poco::JSON::Array jsonSubscriptionArray;
                for (const auto &subscription: subscriptions) {
                    jsonSubscriptionArray.add(subscription.ToJsonObject());
                }
                jsonObject.set("subscriptions", jsonSubscriptionArray);
            }

            // Tags array
            if (!tags.empty()) {
                Poco::JSON::Array jsonTagArray;
                for (const auto &tag: tags) {
                    Poco::JSON::Object jsonTagObject;
                    jsonTagObject.set(tag.first, tag.second);
                    jsonTagArray.add(jsonTagObject);
                }
                jsonObject.set("tags", jsonTagArray);
            }
            return jsonObject;

        } catch (Poco::Exception &e) {
            log_error << e.message();
            throw Core::JsonException(e.message());
        }
    }

    void Topic::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        try {

            Core::JsonUtils::GetJsonValueString("region", jsonObject, region);
            Core::JsonUtils::GetJsonValueString("topicName", jsonObject, topicName);
            Core::JsonUtils::GetJsonValueString("owner", jsonObject, owner);
            Core::JsonUtils::GetJsonValueString("topicUrl", jsonObject, topicUrl);
            Core::JsonUtils::GetJsonValueString("topicArn", jsonObject, topicArn);

            // Attributes
            if (jsonObject->has("topicAttribute")) {
                Poco::JSON::Object::Ptr attributeObject = jsonObject->getObject("topicAttribute");
                topicAttribute.FromJsonObject(attributeObject);
            }

            // Subscriptions
            if (jsonObject->has("subscriptions")) {
                Poco::JSON::Array::Ptr subscriptionArray = jsonObject->getArray("subscriptions");
                for (int i = 0; i < subscriptionArray->size(); i++) {
                    Poco::JSON::Object::Ptr subscriptionObject = subscriptionArray->getObject(i);
                    Subscription subscription;
                    subscription.FromJsonObject(subscriptionObject);
                    subscriptions.emplace_back(subscription);
                }
            }

            // Tags
            if (jsonObject->has("tags")) {
                Poco::JSON::Array::Ptr tagsArray = jsonObject->getArray("tags");
                for (int i = 0; i < tagsArray->size(); i++) {
                    Poco::JSON::Object::Ptr tagObject = tagsArray->getObject(i);
                    tags[tagObject->getNames().front()] = tagObject->getValue<std::string>(tagObject->getNames().front());
                }
            }

        } catch (Poco::Exception &e) {
            log_error << e.message();
            throw Core::JsonException(e.message());
        }
    }

    std::string Topic::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Topic &t) {
        os << "Topic=" << bsoncxx::to_json(t.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::SNS

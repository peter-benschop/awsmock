//
// Created by vogje01 on 01/06/2023.
//

#include <awsmock/entity/sqs/Queue.h>

namespace AwsMock::Database::Entity::SQS {

    view_or_value<view, value> Queue::ToDocument() const {

        auto tagsDoc = bsoncxx::builder::basic::document{};
        if (!tags.empty()) {
            for (const auto &t: tags) {
                tagsDoc.append(kvp(t.first, t.second));
            }
        }

        view_or_value<view, value> queueDoc = make_document(
                kvp("region", region),
                kvp("name", name),
                kvp("owner", owner),
                kvp("queueUrl", queueUrl),
                kvp("queueArn", queueArn),
                kvp("attributes", attributes.ToDocument()),
                kvp("tags", tagsDoc),
                kvp("created", MongoUtils::ToBson(created)),
                kvp("modified", MongoUtils::ToBson(modified)));

        return queueDoc;
    }

    Entity::SQS::Queue Queue::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        try {
            oid = mResult.value()["_id"].get_oid().value.to_string();
            region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
            name = bsoncxx::string::to_string(mResult.value()["name"].get_string().value);
            owner = bsoncxx::string::to_string(mResult.value()["owner"].get_string().value);
            queueUrl = bsoncxx::string::to_string(mResult.value()["queueUrl"].get_string().value);
            queueArn = bsoncxx::string::to_string(mResult.value()["queueArn"].get_string().value);
            attributes.FromDocument(mResult.value()["attributes"].get_document().value);
            created = MongoUtils::FromBson(bsoncxx::types::b_date(mResult.value()["created"].get_date()));
            modified = MongoUtils::FromBson(bsoncxx::types::b_date(mResult.value()["modified"].get_date()));

            // Get tags
            if (mResult.value().find("tags") != mResult.value().end()) {
                if (mResult.value().find("tags") != mResult.value().end()) {
                    bsoncxx::document::view tagsView = mResult.value()["tags"].get_document().value;
                    for (const bsoncxx::document::element &tagElement: tagsView) {
                        std::string key = bsoncxx::string::to_string(tagElement.key());
                        std::string value = bsoncxx::string::to_string(tagsView[key].get_string().value);
                        tags.emplace(key, value);
                    }
                }
            }

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::DatabaseException(exc.what());
        }
        return *this;
    }

    Poco::JSON::Object Queue::ToJsonObject() const {

        try {
            Poco::JSON::Object jsonObject;
            jsonObject.set("region", region);
            jsonObject.set("name", name);
            jsonObject.set("owner", owner);
            jsonObject.set("queueUrl", queueUrl);
            jsonObject.set("queueArn", queueArn);
            jsonObject.set("attributes", attributes.ToJsonObject());

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

    void Queue::FromJsonObject(Poco::JSON::Object::Ptr jsonObject) {

        try {

            Core::JsonUtils::GetJsonValueString("region", jsonObject, region);
            Core::JsonUtils::GetJsonValueString("name", jsonObject, name);
            Core::JsonUtils::GetJsonValueString("owner", jsonObject, owner);
            Core::JsonUtils::GetJsonValueString("queueUrl", jsonObject, queueUrl);
            Core::JsonUtils::GetJsonValueString("queueArn", jsonObject, queueArn);
            Core::JsonUtils::GetJsonValueString("owner", jsonObject, owner);
            attributes.FromJsonObject(jsonObject->getObject("attributes"));

        } catch (Poco::Exception &e) {
            log_error << e.message();
            throw Core::JsonException(e.message());
        }
    }

    std::string Queue::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Queue &q) {
        os << "Queue=" << bsoncxx::to_json(q.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::SQS

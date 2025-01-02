//
// Created by vogje01 on 01/06/2023.
//

#include <awsmock/entity/sqs/Queue.h>

namespace AwsMock::Database::Entity::SQS {

    view_or_value<view, value> Queue::ToDocument() const {

        auto tagsDoc = document{};
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
                kvp("size", size),
                kvp("isDlq", isDlq),
                kvp("mainQueue", mainQueue),
                kvp("created", bsoncxx::types::b_date(created)),
                kvp("modified", bsoncxx::types::b_date(modified)));

        return queueDoc;
    }

    Queue Queue::FromDocument(const std::optional<view> &mResult) {

        try {
            oid = Core::Bson::BsonUtils::GetOidValue(mResult, "_id");
            region = Core::Bson::BsonUtils::GetStringValue(mResult, "region");
            name = Core::Bson::BsonUtils::GetStringValue(mResult, "name");
            owner = Core::Bson::BsonUtils::GetStringValue(mResult, "owner");
            queueUrl = Core::Bson::BsonUtils::GetStringValue(mResult, "queueUrl");
            queueArn = Core::Bson::BsonUtils::GetStringValue(mResult, "queueArn");
            attributes.FromDocument(mResult.value()["attributes"].get_document().value);
            size = Core::Bson::BsonUtils::GetLongValue(mResult, "size");
            isDlq = Core::Bson::BsonUtils::GetBoolValue(mResult, "isDlq");
            mainQueue = Core::Bson::BsonUtils::GetStringValue(mResult, "mainQueue");
            created = Core::Bson::BsonUtils::GetDateValue(mResult, "created");
            modified = Core::Bson::BsonUtils::GetDateValue(mResult, "modified");

            // Get tags
            if (mResult.value().find("tags") != mResult.value().end()) {
                if (mResult.value().find("tags") != mResult.value().end()) {
                    for (const view tagsView = mResult.value()["tags"].get_document().value; const bsoncxx::document::element &tagElement: tagsView) {
                        std::string key = bsoncxx::string::to_string(tagElement.key());
                        std::string value = bsoncxx::string::to_string(tagsView[key].get_string().value);
                        tags.emplace(key, value);
                    }
                }
            }

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
        return *this;
    }

    std::string Queue::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string Queue::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Queue &q) {
        os << "Queue=" << to_json(q.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::SQS

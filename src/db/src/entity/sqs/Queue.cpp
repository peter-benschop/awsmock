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
                kvp("created", bsoncxx::types::b_date(created)),
                kvp("modified", bsoncxx::types::b_date(modified)));

        return queueDoc;
    }

    Queue Queue::FromDocument(const std::optional<view> &mResult) {

        try {
            oid = Core::Bson::BsonUtils::GetOidValue(mResult, "_id");
            region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
            name = bsoncxx::string::to_string(mResult.value()["name"].get_string().value);
            owner = bsoncxx::string::to_string(mResult.value()["owner"].get_string().value);
            queueUrl = bsoncxx::string::to_string(mResult.value()["queueUrl"].get_string().value);
            queueArn = bsoncxx::string::to_string(mResult.value()["queueArn"].get_string().value);
            attributes.FromDocument(mResult.value()["attributes"].get_document().value);
            created = bsoncxx::types::b_date(mResult.value()["created"].get_date());
            modified = bsoncxx::types::b_date(mResult.value()["modified"].get_date());

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

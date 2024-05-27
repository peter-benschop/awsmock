//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/cognito/UserPool.h>

namespace AwsMock::Database::Entity::Cognito {

    view_or_value<view, value> UserPool::ToDocument() const {

        bsoncxx::builder::basic::document domainDoc{};
        domainDoc.append(kvp("domain", domain.domain));

        view_or_value<view, value> userPoolDocument = make_document(
                kvp("region", region),
                kvp("userPoolId", userPoolId),
                kvp("name", name),
                kvp("clientId", clientId),
                kvp("arn", arn),
                kvp("domain", domainDoc.extract()),
                kvp("created", MongoUtils::ToBson(created)),
                kvp("modified", MongoUtils::ToBson(modified)));
        return userPoolDocument;
    }

    void UserPool::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        try {

            oid = mResult.value()["_id"].get_oid().value.to_string();
            userPoolId = bsoncxx::string::to_string(mResult.value()["userPoolId"].get_string().value);
            region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
            name = bsoncxx::string::to_string(mResult.value()["name"].get_string().value);
            clientId = bsoncxx::string::to_string(mResult.value()["clientId"].get_string().value);
            arn = bsoncxx::string::to_string(mResult.value()["arn"].get_string().value);
            created = MongoUtils::FromBson(bsoncxx::types::b_date(mResult.value()["created"].get_date().value));
            modified = MongoUtils::FromBson(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value));

            // Get domain
            if (mResult.value().find("domain") != mResult.value().end()) {
                bsoncxx::document::view domainView = mResult.value()["domain"].get_document().value;
                domain.domain = bsoncxx::string::to_string(domainView["domain"].get_string().value);
            }

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::DatabaseException(exc.what());
        }
    }

    Poco::JSON::Object UserPool::ToJsonObject() const {

        Poco::JSON::Object jsonObject;
        jsonObject.set("region", region);
        jsonObject.set("userPoolId", userPoolId);
        jsonObject.set("name", name);
        jsonObject.set("clientId", clientId);
        jsonObject.set("arn", arn);
        jsonObject.set("domain", domain.domain);

        return jsonObject;
    }

    void UserPool::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        Core::JsonUtils::GetJsonValueString("region", jsonObject, region);
        Core::JsonUtils::GetJsonValueString("userPoolId", jsonObject, userPoolId);
        Core::JsonUtils::GetJsonValueString("name", jsonObject, name);
        Core::JsonUtils::GetJsonValueString("clientId", jsonObject, clientId);
        Core::JsonUtils::GetJsonValueString("arn", jsonObject, arn);
        Core::JsonUtils::GetJsonValueString("domain", jsonObject, domain.domain);
    }

    std::string UserPool::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UserPool &u) {
        os << "UserPool=" << bsoncxx::to_json(u.ToDocument());
        return os;
    }
}// namespace AwsMock::Database::Entity::Cognito
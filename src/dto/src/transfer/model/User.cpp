//
// Created by vogje01 on 12/18/23.
//

#include <Poco/JSON/Array.h>
#include <awsmock/dto/transfer/model/User.h>

namespace AwsMock::Dto::Transfer {

    view_or_value<view, value> User::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Arn", arn);
            Core::Bson::BsonUtils::SetStringValue(document, "Role", role);
            Core::Bson::BsonUtils::SetStringValue(document, "UserName", userName);
            Core::Bson::BsonUtils::SetStringValue(document, "HomeDirectory", homeDirectory);
            Core::Bson::BsonUtils::SetStringValue(document, "Password", password);
            Core::Bson::BsonUtils::SetIntValue(document, "SshPublicKeyCount", sshPublicKeyCount);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void User::FromDocument(const view_or_value<view, value> &document) {

        try {

            region = Core::Bson::BsonUtils::GetStringValue(document, "Region");
            arn = Core::Bson::BsonUtils::GetStringValue(document, "Arn");
            role = Core::Bson::BsonUtils::GetStringValue(document, "Role");
            userName = Core::Bson::BsonUtils::GetStringValue(document, "UserName");
            password = Core::Bson::BsonUtils::GetStringValue(document, "Password");
            homeDirectory = Core::Bson::BsonUtils::GetStringValue(document, "HomeDirectory");
            sshPublicKeyCount = Core::Bson::BsonUtils::GetIntValue(document, "SshPublicKeyCount");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::vector<User> User::FromJsonList(const std::string &jsonString) {

        try {

            const value document = bsoncxx::from_json(jsonString);

            // Users
            UserList userList;
            if (document.view().find("Users") != document.view().end()) {
                for (const view usersArray = document.view()["Users"].get_array().value; const auto &user: usersArray) {
                    User ftpUser;
                    ftpUser.FromDocument(user.get_document().value);
                    userList.push_back(ftpUser);
                }
            }
            return userList;

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string User::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string User::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const User &r) {
        os << "User=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Transfer

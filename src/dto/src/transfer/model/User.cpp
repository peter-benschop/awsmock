//
// Created by vogje01 on 12/18/23.
//

#include <awsmock/dto/transfer/model/User.h>

namespace AwsMock::Dto::Transfer {

    Poco::JSON::Object User::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Arn", arn);
            rootJson.set("Role", role);
            rootJson.set("UserName", userName);
            rootJson.set("HomeDirectory", homeDirectory);
            rootJson.set("Password", password);
            rootJson.set("SshPublicKeyCount", sshPublicKeyCount);

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string User::ToJson() const {
        return Core::JsonUtils::ToJsonString(ToJsonObject());
    }

    void User::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        Core::JsonUtils::GetJsonValueString("Region", jsonObject, region);
        Core::JsonUtils::GetJsonValueString("Arn", jsonObject, arn);
        Core::JsonUtils::GetJsonValueString("Role", jsonObject, role);
        Core::JsonUtils::GetJsonValueString("UserName", jsonObject, userName);
        Core::JsonUtils::GetJsonValueString("Password", jsonObject, password);
        Core::JsonUtils::GetJsonValueString("HomeDirectory", jsonObject, homeDirectory);
        Core::JsonUtils::GetJsonValueInt("SshPublicKeyCount", jsonObject, sshPublicKeyCount);
    }

    std::vector<User> User::FromJsonList(const std::string &body) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(body);
        Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Users
            UserList userList;
            if (rootObject->has("Users")) {
                Poco::JSON::Array::Ptr usersArray = rootObject->getArray("Users");
                if (usersArray != nullptr) {
                    for (int i = 0; i < usersArray->size(); i++) {
                        User ftpUser;
                        ftpUser.FromJsonObject(usersArray->getObject(i));
                        userList.push_back(ftpUser);
                    }
                }
            }
            return userList;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string User::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const User &r) {
        os << "User=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Transfer

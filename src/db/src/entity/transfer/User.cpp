//
// Created by vogje01 on 13/09/2023.
//

#include <awsmock/entity/transfer/Transfer.h>

namespace AwsMock::Database::Entity::Transfer {

    view_or_value<view, value> User::ToDocument() const {

        view_or_value<view, value> userDoc = make_document(
                kvp("userName", userName),
                kvp("password", password),
                kvp("homeDirectory", homeDirectory));

        return userDoc;
    }

    void User::FromDocument(bsoncxx::document::view mResult) {

        for (auto &v: mResult) {
            userName = bsoncxx::string::to_string(v["userName"].get_string().value);
            password = bsoncxx::string::to_string(v["password"].get_string().value);
            homeDirectory = bsoncxx::string::to_string(v["homeDirectory"].get_string().value);
        }
    }

    std::string User::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const User &u) {
        os << "User=" << bsoncxx::to_json(u.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::Transfer
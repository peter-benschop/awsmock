//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/GlobalSignOutRequest.h>

namespace AwsMock::Dto::Cognito {

    void GlobalSignOutRequest::FromJson(const std::string &jsonString) {

        try {

            const value document = bsoncxx::from_json(jsonString);
            region = Core::Bson::BsonUtils::GetStringValue(document, "Region");
            accessToken = Core::Bson::BsonUtils::GetStringValue(document, "AccessToken");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string GlobalSignOutRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "AccessToken", accessToken);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string GlobalSignOutRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GlobalSignOutRequest &r) {
        os << "GlobalSignOutRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito
//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/ssm/GetParameterRequest.h>

namespace AwsMock::Dto::SSM {

    std::string GetParameterRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Name", name);
            Core::Bson::BsonUtils::SetBoolValue(document, "WithDescription", withDescription);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void GetParameterRequest::FromJson(const std::string &jsonString) {

        try {

            const value document = bsoncxx::from_json(jsonString);
            name = Core::Bson::BsonUtils::GetStringValue(document, "Name");
            withDescription = Core::Bson::BsonUtils::GetBoolValue(document, "WithDescription");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string GetParameterRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetParameterRequest &r) {
        os << "GetParameterRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SSM

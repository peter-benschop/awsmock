//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/ssm/DeleteParameterRequest.h>

namespace AwsMock::Dto::SSM {

    std::string DeleteParameterRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Name", name);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void DeleteParameterRequest::FromJson(const std::string &jsonString) {

        try {

            const value document = bsoncxx::from_json(jsonString);
            name = Core::Bson::BsonUtils::GetStringValue(document, "Name");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string DeleteParameterRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteParameterRequest &r) {
        os << "DeleteParameterRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SSM

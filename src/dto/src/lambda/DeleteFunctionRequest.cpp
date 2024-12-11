
#include <awsmock/dto/lambda/DeleteFunctionRequest.h>

namespace AwsMock::Dto::Lambda {

    std::string DeleteFunctionRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "FunctionName", functionName);
            Core::Bson::BsonUtils::SetStringValue(document, "Qualifier", qualifier);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void DeleteFunctionRequest::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);
            region = Core::Bson::BsonUtils::GetStringValue(document, "Region");
            functionName = Core::Bson::BsonUtils::GetStringValue(document, "FunctionName");
            qualifier = Core::Bson::BsonUtils::GetStringValue(document, "Qualifier");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string DeleteFunctionRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteFunctionRequest &r) {
        os << "DeleteFunctionRequest=" + r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda

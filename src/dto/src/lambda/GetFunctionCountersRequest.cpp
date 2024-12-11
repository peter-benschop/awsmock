//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/lambda/GetFunctionCountersRequest.h>

namespace AwsMock::Dto::Lambda {

    void GetFunctionCountersRequest::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);
            region = Core::Bson::BsonUtils::GetStringValue(document, "region");
            functionName = Core::Bson::BsonUtils::GetStringValue(document, "functionName");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string GetFunctionCountersRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "functionName", functionName);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string GetFunctionCountersRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetFunctionCountersRequest &r) {
        os << "GetFunctionCountersRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda

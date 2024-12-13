//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/ssm/GetParameterResponse.h>

namespace AwsMock::Dto::SSM {

    std::string GetParameterResponse::ToJson() const {


        try {

            document document;
            document.append(kvp("Parameter", parameter.ToDocument()));
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string GetParameterResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetParameterResponse &r) {
        os << "GetParameterResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SSM

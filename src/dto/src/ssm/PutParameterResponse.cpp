//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/ssm/PutParameterResponse.h>

namespace AwsMock::Dto::SSM {

    std::string PutParameterResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Tier", tier);
            rootJson.set("Version", version);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    void PutParameterResponse::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("Tier", rootObject, tier);
            Core::JsonUtils::GetJsonValueInt("Version", rootObject, version);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    std::string PutParameterResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const PutParameterResponse &r) {
        os << "PutParameterResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SSM

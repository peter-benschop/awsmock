//
// Created by vogje01 on 06/09/2023.
//

#include <awsmock/dto/lambda/model/AccountUsage.h>

namespace AwsMock::Dto::Lambda {

    Poco::JSON::Object AccountUsage::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("FunctionCount", functionCount);
            rootJson.set("TotalCodeSize", totalCodeSize);

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string AccountUsage::ToJson() const {
        return Core::JsonUtils::ToJsonString(ToJsonObject());
    }

    std::string AccountUsage::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const AccountUsage &f) {
        os << "AccountLimit=" << f.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Lambda

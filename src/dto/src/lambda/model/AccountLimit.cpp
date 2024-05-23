//
// Created by vogje01 on 06/09/2023.
//

#include <awsmock/dto/lambda/model/AccountLimit.h>

namespace AwsMock::Dto::Lambda {

    Poco::JSON::Object AccountLimit::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("CodeSizeUnzipped", codeSizeUnzipped);
            rootJson.set("CodeSizeZipped", codeSizeZipped);
            rootJson.set("ConcurrentExecutions", concurrentExecutions);
            rootJson.set("TotalCodeSize", totalCodeSize);
            rootJson.set("UnreservedConcurrentExecutions", unreservedConcurrentExecutions);

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string AccountLimit::ToJson() const {
        return Core::JsonUtils::ToJsonString(ToJsonObject());
    }

    std::string AccountLimit::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const AccountLimit &f) {
        os << "AccountLimit=" << f.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Lambda

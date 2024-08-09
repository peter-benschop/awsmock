//
// Created by vogje01 on 4/20/24.
//

#include "awsmock/dto/cognito/model/CustomEmailSender.h"

namespace AwsMock::Dto::Cognito {

    std::string CustomEmailSender::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("lambdaArn", lambdaArn);
            rootJson.set("lambdaVersion", lambdaVersion);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    Poco::JSON::Object CustomEmailSender::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("lambdaArn", lambdaArn);
            rootJson.set("lambdaVersion", lambdaVersion);

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CustomEmailSender::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CustomEmailSender &r) {
        os << "CustomEmailSender=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito
//
// Created by vogje01 on 4/20/24.
//

#include "awsmock/dto/cognito/model/LambdaConfig.h"

namespace AwsMock::Dto::Cognito {

    std::string LambdaConfig::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", createAuthChallenge);
            rootJson.set("CustomMessage", customMessage);
            rootJson.set("CustomEmailSender", customEmailSender.ToJsonObject());
            rootJson.set("CustomSmsSender", customSmsSender.ToJsonObject());
            rootJson.set("DefineAuthChallenge", defineAuthChallenge);
            rootJson.set("KMSKeyID", kmsKeyId);
            rootJson.set("PostAuthentication", postAuthentication);
            rootJson.set("PostConfirmation", postConfirmation);
            rootJson.set("PreAuthentication", preAuthentication);
            rootJson.set("PreSignUp", preSignUp);
            rootJson.set("PreTokenGeneration", preTokenGeneration);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string LambdaConfig::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const LambdaConfig &r) {
        os << "LambdaConfig=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito
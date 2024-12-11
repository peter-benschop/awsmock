//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/InitiateAuthResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string InitiateAuthResponse::ToJson() const {

        // TODO: fix me
        /*
        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("Session", session);
            rootJson.set("AuthenticationResult", authenticationResult.ToJsonObject());
            rootJson.set("ChallengeName", challengeName);

            // Challenge parameters
            Poco::JSON::Object challengeParameterObject;
            for (const auto &challengeParameter: challengeParameters) {
                challengeParameterObject.set(challengeParameter.first, challengeParameter.second);
            }
            rootJson.set("ChallengeParameters", challengeParameterObject);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/
        return {};
    }

    std::string InitiateAuthResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const InitiateAuthResponse &r) {
        os << "InitiateAuthResponse=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito
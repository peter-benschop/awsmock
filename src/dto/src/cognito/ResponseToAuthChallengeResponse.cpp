//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/RespondToAuthChallengeResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string RespondToAuthChallengeResponse::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("Session", session);
            rootJson.set("ChallengeName", ChallengeNameToString(challengeName));
            rootJson.set("AuthenticationResult", authenticationResult.ToJsonObject());

            if (!challengeParameters.empty()) {
                Poco::JSON::Object::Ptr challengeParametersObject;
                for (const auto &challengeParameter: challengeParameters) {
                    challengeParametersObject->set(challengeParameter.first, challengeParameter.second);
                }
                rootJson.set("ChallengeParameters", challengeParametersObject);
            }

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string RespondToAuthChallengeResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const RespondToAuthChallengeResponse &r) {
        os << "RespondToAuthChallengeResponse=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito
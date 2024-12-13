//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/InitiateAuthResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string InitiateAuthResponse::ToJson() const {

        try {

            document rootDocument;
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "Session", session);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "ChallengeName", challengeName);

            rootDocument.append(kvp("AuthenticationResult", authenticationResult.ToDocument()));

            if (!challengeParameters.empty()) {
                document jsonObject;
                for (const auto &[fst, snd]: challengeParameters) {
                    jsonObject.append(kvp(fst, snd));
                }
                rootDocument.append(kvp("ChallengeParameters", jsonObject));
            }
            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
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
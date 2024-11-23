//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/RespondToAuthChallengeRequest.h>

namespace AwsMock::Dto::Cognito {

    std::string RespondToAuthChallengeRequest::GetUserName() {
        return challengeResponses["USERNAME"];
    }

    std::string RespondToAuthChallengeRequest::GetPasswordClaimSecretBlock() {
        return challengeResponses["PASSWORD_CLAIM_SECRET_BLOCK"];
    }

    std::string RespondToAuthChallengeRequest::GetPasswordClaim_Signature() {
        return challengeResponses["PASSWORD_CLAIM_SIGNATURE"];
    }

    void RespondToAuthChallengeRequest::FromJson(const std::string &payload) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(payload);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("ClientId", rootObject, clientId);
            Core::JsonUtils::GetJsonValueString("Session", rootObject, session);

            // Challenge name ENUM
            std::string tmpChallengeName;
            Core::JsonUtils::GetJsonValueString("ChallengeName", rootObject, tmpChallengeName);
            if (!tmpChallengeName.empty()) {
                challengeName = ChallengeNameFromString(tmpChallengeName);
            }

            // Challenge responses
            if (rootObject->has("ChallengeResponses")) {
                Poco::JSON::Object::Ptr authParameterObject = rootObject->getObject("ChallengeResponses");
                for (int i = 0; i < authParameterObject->getNames().size(); i++) {
                    std::string key = authParameterObject->getNames()[i];
                    std::string value = authParameterObject->get(key);
                    challengeResponses[key] = value;
                }
            }

            // Client metadata
            if (rootObject->has("ClientMetadata")) {
                Poco::JSON::Object::Ptr clientMetadataObject = rootObject->getObject("ClientMetadata");
                for (int i = 0; i < clientMetadataObject->getNames().size(); i++) {
                    std::string key = clientMetadataObject->getNames()[i];
                    std::string value = clientMetadataObject->get(key);
                    clientMetaData[key] = value;
                }
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string RespondToAuthChallengeRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("ClientId", clientId);

            // Auth parameters
            Poco::JSON::Object challengeResponsesObject;
            for (const auto &challengeResponse: challengeResponses) {
                challengeResponsesObject.set(challengeResponse.first, challengeResponse.second);
            }
            rootJson.set("ChallengeResponses", challengeResponsesObject);

            // Client metadata
            Poco::JSON::Object clientMetadataObject;
            for (const auto &clientMeta: clientMetaData) {
                clientMetadataObject.set(clientMeta.first, clientMeta.second);
            }
            rootJson.set("ClientMetadata", clientMetadataObject);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string RespondToAuthChallengeRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const RespondToAuthChallengeRequest &r) {
        os << "RespondToAuthChallengeRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito
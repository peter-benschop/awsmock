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

    void RespondToAuthChallengeRequest::FromJson(const std::string &jsonString) {

        try {

            const value rootDocument = bsoncxx::from_json(jsonString);
            region = Core::Bson::BsonUtils::GetStringValue(rootDocument, "Region");
            clientId = Core::Bson::BsonUtils::GetStringValue(rootDocument, "ClientId");
            session = Core::Bson::BsonUtils::GetStringValue(rootDocument, "Session");
            challengeName = ChallengeNameFromString(Core::Bson::BsonUtils::GetStringValue(rootDocument, "ChallengeName"));

            // Challenge responses
            if (rootDocument.view().find("ChallengeResponses") != rootDocument.view().end()) {
                for (const view jsonObject = rootDocument.view()["ChallengeResponses"].get_document().value; const auto &element: jsonObject) {
                    std::string key = bsoncxx::string::to_string(element.key());
                    const std::string value = bsoncxx::string::to_string(element[key].get_string().value);
                    challengeResponses[key] = value;
                }
            }

            // Client metadata
            if (rootDocument.view().find("ClientMetadata") != rootDocument.view().end()) {
                for (const view jsonObject = rootDocument.view()["ClientMetadata"].get_document().value; const auto &element: jsonObject) {
                    std::string key = bsoncxx::string::to_string(element.key());
                    const std::string value = bsoncxx::string::to_string(element[key].get_string().value);
                    clientMetaData[key] = value;
                }
            }
        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string RespondToAuthChallengeRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "ClientId", clientId);

            // Challenge responses
            if (!challengeResponses.empty()) {
                array jsonArray;
                for (const auto &[fst, snd]: challengeResponses) {
                    jsonArray.append(kvp(fst, snd));
                }
                document.append(kvp("ChallengeResponses", jsonArray));
            }

            // Challenge responses
            if (!clientMetaData.empty()) {
                array jsonArray;
                for (const auto &[fst, snd]: clientMetaData) {
                    jsonArray.append(kvp(fst, snd));
                }
                document.append(kvp("ClientMetadata", jsonArray));
            }
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
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
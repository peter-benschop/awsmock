//
// Created by vogje01 on 4/20/24.
//

#include "awsmock/dto/cognito/model/LambdaConfig.h"

namespace AwsMock::Dto::Cognito {

    std::string LambdaConfig::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "CreateAuthChallenge", createAuthChallenge);
            Core::Bson::BsonUtils::SetStringValue(document, "CustomMessage", customMessage);
            Core::Bson::BsonUtils::SetStringValue(document, "DefineAuthChallenge", defineAuthChallenge);
            Core::Bson::BsonUtils::SetStringValue(document, "KMSKeyID", kmsKeyId);
            Core::Bson::BsonUtils::SetStringValue(document, "PostAuthentication", postAuthentication);
            Core::Bson::BsonUtils::SetStringValue(document, "PostConfirmation", postConfirmation);
            Core::Bson::BsonUtils::SetStringValue(document, "PreAuthentication", preAuthentication);
            Core::Bson::BsonUtils::SetStringValue(document, "PreSignUp", preSignUp);
            Core::Bson::BsonUtils::SetStringValue(document, "PreTokenGeneration", preTokenGeneration);

            document.append(kvp("CustomEmailSender", customEmailSender.ToDocument()));
            document.append(kvp("CustomSmsSender", customSmsSender.ToDocument()));

            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
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
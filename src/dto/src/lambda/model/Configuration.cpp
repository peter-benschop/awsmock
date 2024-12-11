//
// Created by vogje01 on 06/09/2023.
//

#include <awsmock/dto/lambda/model/Configuration.h>

namespace AwsMock::Dto::Lambda {

    view_or_value<view, value> Configuration::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "CodeSha256", codeSha256);
            Core::Bson::BsonUtils::SetLongValue(document, "CodeSize", codeSize);
            Core::Bson::BsonUtils::SetStringValue(document, "Description", description);
            Core::Bson::BsonUtils::SetStringValue(document, "FunctionArn", functionArn);
            Core::Bson::BsonUtils::SetStringValue(document, "FunctionName", functionName);
            Core::Bson::BsonUtils::SetStringValue(document, "Handler", handler);
            Core::Bson::BsonUtils::SetStringValue(document, "Runtime", runtime);
            Core::Bson::BsonUtils::SetDateValue(document, "LastModified", lastModified);
            Core::Bson::BsonUtils::SetStringValue(document, "LastUpdateStatus", lastUpdateStatusReason);
            Core::Bson::BsonUtils::SetStringValue(document, "LastUpdateStatusCode", lastUpdateStatusReasonCode);
            Core::Bson::BsonUtils::SetStringValue(document, "State", state);
            Core::Bson::BsonUtils::SetStringValue(document, "StateReasonCode", stateReasonCode);
            Core::Bson::BsonUtils::SetStringValue(document, "Version", version);

            // Architectures
            if (!architectures.empty()) {
                array jsonArray;
                for (const auto &architecture: architectures) {
                    jsonArray.append(architecture);
                }
                document.append(kvp("Architectures", jsonArray));
            }
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string Configuration::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string Configuration::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Configuration &f) {
        os << "Configuration=" << f.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Lambda

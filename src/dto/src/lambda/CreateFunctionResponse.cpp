//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/lambda/CreateFunctionResponse.h>

namespace AwsMock::Dto::Lambda {

    std::string CreateFunctionResponse::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "FunctionArn", functionArn);
            Core::Bson::BsonUtils::SetStringValue(document, "Runtime", runtime);
            Core::Bson::BsonUtils::SetStringValue(document, "Role", role);
            Core::Bson::BsonUtils::SetStringValue(document, "Handler", handler);
            Core::Bson::BsonUtils::SetLongValue(document, "MemorySize", memorySize);
            Core::Bson::BsonUtils::SetLongValue(document, "CodeSize", codeSize);
            Core::Bson::BsonUtils::SetLongValue(document, "Timeout", timeout);
            Core::Bson::BsonUtils::SetStringValue(document, "CodeSha256", codeSha256);
            Core::Bson::BsonUtils::SetStringValue(document, "LastModified", modified);

            // Environment
            document.append(kvp("Environment", environment.ToDocument()));

            // Ephemeral storage
            document.append(kvp("EphemeralStorage", ephemeralStorage.ToDocument()));

            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CreateFunctionResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateFunctionResponse &r) {
        os << "CreateFunctionResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda

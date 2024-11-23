//
// Created by vogje01 on 06/09/2023.
//

#include <awsmock/dto/lambda/model/Configuration.h>

namespace AwsMock::Dto::Lambda {

    Poco::JSON::Object Configuration::ToJsonObject() const {

        try {
            Poco::JSON::Object rootJson;

            // Architectures array
            Poco::JSON::Array architectureArray;
            for (const auto &architecture: architectures) {
                architectureArray.add(architecture);
            }
            rootJson.set("Architectures", architectureArray);

            rootJson.set("CodeSha256", codeSha256);
            rootJson.set("CodeSize", codeSize);
            rootJson.set("DeadLetterConfig", deadLetterConfig.ToJsonObject());
            rootJson.set("Description", description);
            // TODO: Environment, EphemeralStorage, FileSystemConfig
            rootJson.set("FunctionArn", functionArn);
            rootJson.set("FunctionName", functionName);
            rootJson.set("Handler", handler);
            rootJson.set("Runtime", runtime);
            rootJson.set("FunctionName", functionName);
            // TODO: ImageConfig
            rootJson.set("LastModified", Core::DateTimeUtils::ToISO8601(lastModified));
            rootJson.set("LastUpdateStatus", lastUpdateStatusReason);
            rootJson.set("LastUpdateStatusCode", lastUpdateStatusReasonCode);
            rootJson.set("State", state);
            rootJson.set("StateResaon", stateReason);
            rootJson.set("StateReasonCode", stateReasonCode);
            rootJson.set("Timeout", timeout);
            rootJson.set("Environment", environment.ToJsonObject());
            rootJson.set("Version", version);

            return rootJson;

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message(), 500);
        }
    }

    std::string Configuration::ToJson() const {
        return Core::JsonUtils::ToJsonString(ToJsonObject());
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

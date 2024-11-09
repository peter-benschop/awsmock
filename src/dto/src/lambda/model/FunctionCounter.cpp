//
// Created by vogje01 on 06/09/2023.
//

#include <awsmock/dto/lambda/model/FunctionCounter.h>

namespace AwsMock::Dto::Lambda {

    Poco::JSON::Object FunctionCounter::ToJsonObject() const {

        try {
            Poco::JSON::Object rootJson;

            // Architectures array
            Poco::JSON::Array architectureArray;
            for (const auto &architecture: architectures) {
                architectureArray.add(architecture);
            }
            rootJson.set("architectures", architectureArray);

            rootJson.set("codeSha256", codeSha256);
            rootJson.set("codeSize", codeSize);
            rootJson.set("deadLetterConfig", deadLetterConfig.ToJsonObject());
            rootJson.set("description", description);
            // TODO: Environment, EphemeralStorage, FileSystemConfig
            rootJson.set("functionArn", functionArn);
            rootJson.set("functionName", functionName);
            rootJson.set("handler", handler);
            rootJson.set("runtime", runtime);
            rootJson.set("functionName", functionName);
            // TODO: ImageConfig
            rootJson.set("lastModified", Core::DateTimeUtils::ToISO8601(lastModified));
            rootJson.set("lastUpdateStatus", lastUpdateStatusReason);
            rootJson.set("lastUpdateStatusCode", lastUpdateStatusReasonCode);
            rootJson.set("state", state);
            rootJson.set("stateReason", stateReason);
            rootJson.set("stateReasonCode", stateReasonCode);
            rootJson.set("timeout", timeout);
            rootJson.set("environment", environment.ToJsonObject());
            rootJson.set("version", version);
            rootJson.set("invocations", invocations);
            rootJson.set("averageRuntime", averageRuntime);

            return rootJson;

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message(), 500);
        }
    }

    std::string FunctionCounter::ToJson() const {
        return Core::JsonUtils::ToJsonString(ToJsonObject());
    }

    std::string FunctionCounter::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const FunctionCounter &f) {
        os << "FunctionCounter=" << f.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Lambda

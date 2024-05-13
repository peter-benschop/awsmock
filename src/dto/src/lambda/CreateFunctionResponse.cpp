//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/lambda/CreateFunctionResponse.h>

namespace AwsMock::Dto::Lambda {

    [[nodiscard]] std::string CreateFunctionResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("FunctionArn", functionArn);
            rootJson.set("FunctionName", functionName);
            rootJson.set("Runtime", runtime);
            rootJson.set("Role", role);
            rootJson.set("Handler", handler);
            rootJson.set("MemorySize", memorySize);
            rootJson.set("CodeSize", codeSize);
            rootJson.set("Timeout", timeout);
            rootJson.set("CodeSha256", codeSha256);
            rootJson.set("LastModified", modified);
            rootJson.set("Environment", environment.ToJsonObject());
            rootJson.set("EphemeralStorage", ephemeralStorage.ToJsonObject());
            rootJson.set("MemorySize", memorySize);

            std::ostringstream os;
            rootJson.stringify(os);
            return os.str();

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message(), 500);
        }
    }

    std::string CreateFunctionResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateFunctionResponse &r) {
        os << "CreateFunctionResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda

//
// Created by vogje01 on 06/09/2023.
//

#include <awsmock/dto/lambda/ListFunctionResponse.h>

namespace AwsMock::Dto::Lambda {

    std::string ListFunctionResponse::ToJson() {

        for (auto &lambda: lambdaList) {
            Function function = {
                    .codeSha256 = lambda.codeSha256,
                    .codeSize = lambda.memorySize,
                    .functionArn = lambda.arn,
                    .functionName = lambda.function,
                    .handler = lambda.handler,
                    .runtime = lambda.runtime,
                    .lastModified = lambda.modified};
            function.environment.variables = lambda.environment.variables;
            functions.push_back(function);
        }

        try {
            Poco::JSON::Object rootJson;
            Poco::JSON::Array recordsJsonArray;
            for (const auto &function: functions) {
                recordsJsonArray.add(function.ToJsonObject());
            }
            rootJson.set("Functions", recordsJsonArray);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    std::string ListFunctionResponse::ToString() {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, ListFunctionResponse &r) {
        os << "ListFunctionResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda

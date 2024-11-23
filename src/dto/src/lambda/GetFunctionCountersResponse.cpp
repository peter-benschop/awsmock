//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/lambda/GetFunctionCountersResponse.h>

namespace AwsMock::Dto::Lambda {

    std::string GetFunctionCountersResponse::ToJson() const {

        try {

            bsoncxx::builder::basic::document document;

            Core::Bson::BsonUtils::SetStringValue(document, "region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "functionName", functionName);
            Core::Bson::BsonUtils::SetStringValue(document, "handler", handler);
            Core::Bson::BsonUtils::SetStringValue(document, "runtime", runtime);
            Core::Bson::BsonUtils::SetStringValue(document, "user", user);
            Core::Bson::BsonUtils::SetStringValue(document, "role", role);
            Core::Bson::BsonUtils::SetLongValue(document, "size", size);
            Core::Bson::BsonUtils::SetLongValue(document, "concurrency", concurrency);
            Core::Bson::BsonUtils::SetLongValue(document, "invocations", invocations);
            Core::Bson::BsonUtils::SetLongValue(document, "averageRuntime", averageRuntime);
            Core::Bson::BsonUtils::SetDateValue(document, "lastInvocation", lastInvocation);
            Core::Bson::BsonUtils::SetDateValue(document, "lastStarted", lastStarted);
            Core::Bson::BsonUtils::SetDateValue(document, "created", created);
            Core::Bson::BsonUtils::SetDateValue(document, "modified", modified);

            // Environment
            if (!environment.empty()) {
                bsoncxx::builder::basic::document envDoc;
                for (const auto &env: environment) {
                    envDoc.append(bsoncxx::builder::basic::kvp(env.first, env.second));
                }
                document.append(bsoncxx::builder::basic::kvp("environment", envDoc));
            }

            // Tags
            if (!tags.empty()) {
                bsoncxx::builder::basic::document tagDoc;
                for (const auto &tag: tags) {
                    tagDoc.append(bsoncxx::builder::basic::kvp(tag.first, tag.second));
                }
                document.append(bsoncxx::builder::basic::kvp("tags", tagDoc));
            }
            log_info << bsoncxx::to_json(document);

            return bsoncxx::to_json(document);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string GetFunctionCountersResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetFunctionCountersResponse &r) {
        os << "GetFunctionCountersResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda

//
// Created by vogje01 on 06/09/2023.
//

#include <awsmock/dto/lambda/model/AccountLimit.h>

namespace AwsMock::Dto::Lambda {

    view_or_value<view, value> AccountLimit::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetLongValue(document, "CodeSizeUnzipped", codeSizeUnzipped);
            Core::Bson::BsonUtils::SetLongValue(document, "CodeSizeZipped", codeSizeZipped);
            Core::Bson::BsonUtils::SetLongValue(document, "ConcurrentExecutions", concurrentExecutions);
            Core::Bson::BsonUtils::SetLongValue(document, "TotalCodeSize", totalCodeSize);
            Core::Bson::BsonUtils::SetLongValue(document, "UnreservedConcurrentExecutions", unreservedConcurrentExecutions);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string AccountLimit::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string AccountLimit::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const AccountLimit &f) {
        os << "AccountLimit=" << f.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Lambda

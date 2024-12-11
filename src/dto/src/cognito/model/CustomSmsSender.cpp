//
// Created by vogje01 on 4/20/24.
//

#include <awsmock/dto/cognito/model/CustomSmsSender.h>

namespace AwsMock::Dto::Cognito {

    std::string CustomSmsSender::ToJson() const {
        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "lambdaArn", lambdaArn);
            Core::Bson::BsonUtils::SetStringValue(document, "lambdaVersion", lambdaVersion);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> CustomSmsSender::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "lambdaArn", lambdaArn);
            Core::Bson::BsonUtils::SetStringValue(document, "lambdaVersion", lambdaVersion);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CustomSmsSender::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CustomSmsSender &r) {
        os << "CustomSmsSender=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito
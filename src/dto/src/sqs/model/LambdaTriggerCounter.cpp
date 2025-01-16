//
// Created by vogje01 on 23/11/2023.
//

#include <awsmock/dto/sqs/model/LambdaTriggerCounter.h>

namespace AwsMock::Dto::SQS {

    view_or_value<view, value> LambdaTriggerCounter::ToDocument() const {

        try {
            document rootDocument;
            rootDocument.append(kvp("uuid", uuid));
            rootDocument.append(kvp("arn", arn));
            rootDocument.append(kvp("enabled", enabled));
            return rootDocument.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string LambdaTriggerCounter::ToJson() const {

        try {

            return Core::Bson::BsonUtils::ToJsonString(ToDocument());

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string LambdaTriggerCounter::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const LambdaTriggerCounter &r) {
        os << "LambdaTriggerCounter=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::SQS

//
// Created by vogje01 on 23/11/2023.
//

#include <awsmock/dto/sqs/model/AttributeCounter.h>

namespace AwsMock::Dto::SQS {

    view_or_value<view, value> AttributeCounter::ToDocument() const {

        try {
            document rootDocument;
            rootDocument.append(kvp("Key", attributeKey));
            rootDocument.append(kvp("Value", attributeValue));
            return rootDocument.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string AttributeCounter::ToJson() const {

        try {

            return Core::Bson::BsonUtils::ToJsonString(ToDocument());

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string AttributeCounter::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const AttributeCounter &r) {
        os << "AttributeCounter=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::SQS

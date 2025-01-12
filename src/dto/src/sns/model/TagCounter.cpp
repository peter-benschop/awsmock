//
// Created by vogje01 on 23/11/2023.
//

#include <awsmock/dto/sns/model/TagCounter.h>

namespace AwsMock::Dto::SNS {

    view_or_value<view, value> TagCounter::ToDocument() const {

        try {
            document rootDocument;
            rootDocument.append(kvp("Key", tagKey));
            rootDocument.append(kvp("Value", tagValue));
            return rootDocument.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string TagCounter::ToJson() const {

        try {

            return Core::Bson::BsonUtils::ToJsonString(ToDocument());

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string TagCounter::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const TagCounter &r) {
        os << "TagCounter=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::SNS

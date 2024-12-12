//
// Created by vogje01 on 12/18/23.
//

#include <awsmock/dto/transfer/model/Tag.h>

namespace AwsMock::Dto::Transfer {

    std::string Tag::ToJson() const {

        try {
            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "key", key);
            Core::Bson::BsonUtils::SetStringValue(document, "value", value);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string Tag::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Tag &r) {
        os << "Tag=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Transfer

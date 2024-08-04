//
// Created by vogje01 on 12/18/23.
//

#include "awsmock/dto/transfer/model/Tag.h"

namespace AwsMock::Dto::Transfer {

    std::string Tag::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("key", key);
            rootJson.set("value", value);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string Tag::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Tag &r) {
        os << "Tag=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Transfer

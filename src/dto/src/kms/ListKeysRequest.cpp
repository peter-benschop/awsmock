//
// Created by vogje01 on 4/25/24.
//

#include <awsmock/dto/kms/ListKeysRequest.h>

namespace AwsMock::Dto::KMS {

    void ListKeysRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("Marker", rootObject, marker);
            Core::JsonUtils::GetJsonValueLong("Limit", rootObject, limit);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListKeysRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Marker", marker);
            rootJson.set("Limit", limit);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListKeysRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListKeysRequest &r) {
        os << "ListKeysRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::KMS

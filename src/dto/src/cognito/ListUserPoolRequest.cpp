//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/ListUserPoolRequest.h>

namespace AwsMock::Dto::Cognito {

    void ListUserPoolRequest::FromJson(const std::string &payload) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(payload);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueInt("MaxResults", rootObject, maxResults);
            Core::JsonUtils::GetJsonValueInt("PageIndex", rootObject, pageIndex);

            if (rootObject->has("SortColumns")) {
                Poco::JSON::Array::Ptr jsonArray = rootObject->getArray("SortColumns");
                for (const auto &it: *jsonArray) {
                    sortColumns.emplace_back(it.extract<std::string>());
                }
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListUserPoolRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("MaxResults", maxResults);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListUserPoolRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListUserPoolRequest &r) {
        os << "ListUserPoolRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito
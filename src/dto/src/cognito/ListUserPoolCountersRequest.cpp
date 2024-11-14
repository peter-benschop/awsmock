//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/ListUserPoolCountersRequest.h>

namespace AwsMock::Dto::Cognito {

    void ListUserPoolCountersRequest::FromJson(const std::string &payload) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(payload);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("prefix", rootObject, prefix);
            Core::JsonUtils::GetJsonValueInt("pageSize", rootObject, pageSize);
            Core::JsonUtils::GetJsonValueInt("pageIndex", rootObject, pageIndex);

            if (rootObject->has("sortColumns")) {
                Poco::JSON::Array::Ptr jsonArray = rootObject->getArray("sortColumns");
                for (int i = 0; i < jsonArray->size(); i++) {
                    Core::SortColumn sortColumn;
                    sortColumn.FromJsonObject(jsonArray->getObject(i));
                    sortColumns.emplace_back(sortColumn);
                }
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListUserPoolCountersRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("prefix", prefix);
            rootJson.set("pageSize", pageSize);
            rootJson.set("pageIndex", pageIndex);

            if (!sortColumns.empty()) {
                Poco::JSON::Array jsonArray;
                for (const auto &sortColumn: sortColumns) {
                    jsonArray.add(sortColumn.ToJsonObject());
                }
                rootJson.set("sortColumns", jsonArray);
            }

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListUserPoolCountersRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListUserPoolCountersRequest &r) {
        os << "ListUserPoolRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito
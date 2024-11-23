//
// Created by vogje01 on 31/05/2023.
//

#include <awsmock/dto/lambda/ListFunctionCountersRequest.h>

namespace AwsMock::Dto::Lambda {

    ListFunctionCountersRequest ListFunctionCountersRequest::FromJson(const std::string &jsonString) {

        ListFunctionCountersRequest request;

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {
            if (!rootObject->get("region").isEmpty()) {
                request.region = rootObject->get("region").convert<std::string>();
            }
            if (!rootObject->get("prefix").isEmpty()) {
                request.prefix = rootObject->get("prefix").convert<std::string>();
            }
            if (!rootObject->get("skip").isEmpty()) {
                request.skip = rootObject->get("skip").convert<int>();
            }
            if (!rootObject->get("maxResults").isEmpty()) {
                request.maxResults = rootObject->get("maxResults").convert<int>();
            }
            if (!rootObject->get("sortColumns").isEmpty()) {

                Poco::JSON::Array::Ptr sortColumnArray = rootObject->getArray("sortColumns");
                if (sortColumnArray != nullptr) {
                    for (int i = 0; i < sortColumnArray->size(); i++) {
                        Core::SortColumn sortColumn;
                        Poco::JSON::Object::Ptr jsonColumnObject = sortColumnArray->getObject(i);
                        Core::JsonUtils::GetJsonValueString("column", jsonColumnObject, sortColumn.column);
                        Core::JsonUtils::GetJsonValueInt("sortDirection", jsonColumnObject, sortColumn.sortDirection);
                        request.sortColumns.emplace_back(sortColumn);
                    }
                }
            }
            return request;
        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListFunctionCountersRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("maxResults", maxResults);
            rootJson.set("skip", skip);

            if (!sortColumns.empty()) {
                Poco::JSON::Array jsonArray;
                for (const auto &sortColumn: sortColumns) {
                    jsonArray.add(sortColumn);
                }
                rootJson.set("sortColumns", sortColumns);
            }
            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListFunctionCountersRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListFunctionCountersRequest &r) {
        os << "ListFunctionCountersRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda

//
// Created by vogje01 on 23/09/2023.
//

#include <awsmock/dto/sqs/ListMessageCountersRequest.h>

namespace AwsMock::Dto::SQS {

    void ListMessageCountersRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Values
            Core::JsonUtils::GetJsonValueString("queueArn", rootObject, queueArn);
            Core::JsonUtils::GetJsonValueString("prefix", rootObject, prefix);
            Core::JsonUtils::GetJsonValueInt("pageSize", rootObject, pageSize);
            Core::JsonUtils::GetJsonValueInt("pageIndex", rootObject, pageIndex);

            // Sort columns
            if (!rootObject->get("sortColumns").isEmpty()) {

                Poco::JSON::Array::Ptr sortColumnArray = rootObject->getArray("sortColumns");
                if (sortColumnArray != nullptr) {
                    for (int i = 0; i < sortColumnArray->size(); i++) {
                        Core::SortColumn sortColumn;
                        Poco::JSON::Object::Ptr jsonColumnObject = sortColumnArray->getObject(i);
                        Core::JsonUtils::GetJsonValueString("column", jsonColumnObject, sortColumn.column);
                        Core::JsonUtils::GetJsonValueInt("sortDirection", jsonColumnObject, sortColumn.sortDirection);
                        sortColumns.emplace_back(sortColumn);
                    }
                }
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListMessageCountersRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("queueArn", queueArn);
            rootJson.set("prefix", prefix);
            rootJson.set("pageSize", pageSize);
            rootJson.set("pageIndex", pageIndex);

            // Sort columns
            if (!sortColumns.empty()) {
                Poco::JSON::Array jsonArray;
                for (const auto &sortColumn: sortColumns) {
                    jsonArray.add(sortColumn);
                }
                rootJson.set("sortColumns", sortColumns);
            }

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListMessageCountersRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListMessageCountersRequest &r) {
        os << "ListMessageCountersRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS

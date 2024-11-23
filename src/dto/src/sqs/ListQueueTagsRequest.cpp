//
// Created by vogje01 on 23/09/2023.
//

#include <awsmock/dto/sqs/ListQueueTagsRequest.h>

namespace AwsMock::Dto::SQS {

    void ListQueueTagsRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Values
            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("QueueUrl", rootObject, queueUrl);
            Core::JsonUtils::GetJsonValueInt("PageSize", rootObject, pageSize);
            Core::JsonUtils::GetJsonValueInt("PageIndex", rootObject, pageIndex);

            if (!rootObject->get("SortColumns").isEmpty()) {

                Poco::JSON::Array::Ptr sortColumnArray = rootObject->getArray("SortColumns");
                if (sortColumnArray != nullptr) {
                    for (int i = 0; i < sortColumnArray->size(); i++) {
                        Core::SortColumn sortColumn;
                        Poco::JSON::Object::Ptr jsonColumnObject = sortColumnArray->getObject(i);
                        Core::JsonUtils::GetJsonValueString("Column", jsonColumnObject, sortColumn.column);
                        Core::JsonUtils::GetJsonValueInt("SortDirection", jsonColumnObject, sortColumn.sortDirection);
                        sortColumns.emplace_back(sortColumn);
                    }
                }
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListQueueTagsRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("QueueUrl", queueUrl);
            rootJson.set("PageSize", pageSize);
            rootJson.set("PageIndex", pageIndex);

            if (!sortColumns.empty()) {
                Poco::JSON::Array jsonArray;
                for (const auto &sortColumn: sortColumns) {
                    jsonArray.add(sortColumn);
                }
                rootJson.set("SortColumns", sortColumns);
            }

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListQueueTagsRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListQueueTagsRequest &r) {
        os << "ListQueueTagsRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS

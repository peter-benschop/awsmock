//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/secretsmanager/ListSecretsRequest.h>

namespace AwsMock::Dto::SecretsManager {

    std::string ListSecretsRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "SortOrder", sortOrder);
            Core::Bson::BsonUtils::SetStringValue(document, "NextToken", nextToken);
            Core::Bson::BsonUtils::SetIntValue(document, "MaxResults", maxResults);
            Core::Bson::BsonUtils::SetBoolValue(document, "IncludePlannedDeletion", includePlannedDeletion);

            // Filters
            if (!filters.empty()) {
                array jsonFilters;
                for (const auto &filter: filters) {
                    jsonFilters.append(filter.ToDocument());
                }
                document.append(kvp("Filters", jsonFilters));
            }

            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void ListSecretsRequest::FromJson(const std::string &jsonString) {

        try {

            // Queue
            const value document = bsoncxx::from_json(jsonString);
            region = Core::Bson::BsonUtils::GetStringValue(document, "Region");
            sortOrder = Core::Bson::BsonUtils::GetStringValue(document, "SortOrder");
            nextToken = Core::Bson::BsonUtils::GetStringValue(document, "NextToken");
            maxResults = Core::Bson::BsonUtils::GetIntValue(document, "MaxResults");
            includePlannedDeletion = Core::Bson::BsonUtils::GetBoolValue(document, "IncludePlannedDeletion");

            // Filters
            if (document.find("Filters") != document.end()) {
                for (const bsoncxx::array::view arrayView{document["Filters"].get_array().value}; const bsoncxx::array::element &element: arrayView) {
                    Filter filter;
                    filter.FromDocument(element.get_document().value);
                    filters.emplace_back(filter);
                }
            }
        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListSecretsRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListSecretsRequest &r) {
        os << "ListSecretsRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SecretsManager

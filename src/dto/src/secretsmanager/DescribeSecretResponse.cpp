//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/secretsmanager/DescribeSecretResponse.h>

namespace AwsMock::Dto::SecretsManager {

    std::string DescribeSecretResponse::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "Name", name);
            Core::Bson::BsonUtils::SetStringValue(document, "ARN", arn);
            Core::Bson::BsonUtils::SetStringValue(document, "Description", description);

            // Tags
            if (!tags.tags.empty()) {
                array jsonArray;
                for (auto tag: tags) {
                    jsonArray.append(tag.ToDocument());
                }
                document.append(kvp("Tags", jsonArray));
            }

            document.append(kvp("ReplicationsStatus", replicationStatus.ToDocument()));
            document.append(kvp("VersionIdsToStages", versionIdsToStages.ToDocument()));
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void DescribeSecretResponse::FromJson(const std::string &jsonString) {

        try {

            // Queue
            const value document = bsoncxx::from_json(jsonString);
            name = Core::Bson::BsonUtils::GetStringValue(document, "Name");

            // Tags
            if (document.find("Tags") != document.end()) {
                for (const bsoncxx::array::view arrayView{document["Tags"].get_array().value}; const bsoncxx::array::element &element: arrayView) {
                    SecretTags tag;
                    tag.FromDocument(element.get_document().value);
                    //tags.tags[tag].emplace_back(tag);
                }
            }

            // Replication status
            if (document.find("ReplicationsStatus") != document.end()) {
                replicationStatus.FromDocument(document["ReplicationsStatus"].get_document().value);
            }

            // Version ID
            if (document.find("VersionIdsToStages") != document.end()) {
                replicationStatus.FromDocument(document["VersionIdsToStages"].get_document().value);
            }

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string DescribeSecretResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DescribeSecretResponse &r) {
        os << "DescribeSecretResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SecretsManager

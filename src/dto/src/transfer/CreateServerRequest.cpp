//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/transfer/CreateServerRequest.h>

namespace AwsMock::Dto::Transfer {

    std::string CreateServerRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "Domain", domain);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void CreateServerRequest::FromJson(const std::string &jsonString) {

        try {
            const value rootDocument = bsoncxx::from_json(jsonString);
            region = Core::Bson::BsonUtils::GetStringValue(rootDocument, "Region");
            domain = Core::Bson::BsonUtils::GetStringValue(rootDocument, "Domain");

            // Protocols
            if (rootDocument.find("Protocols") != rootDocument.end()) {
                for (const view protocolsArray = rootDocument.view()["Protocols"].get_array().value; const auto &protocol: protocolsArray) {
                    protocols.emplace_back(protocol.get_string().value);
                }
            }

            // Tags
            if (rootDocument.find("Tags") != rootDocument.end()) {
                for (const view tagsObject = rootDocument.view()["Tags"].get_document().value; const auto &tag: tagsObject) {
                    std::string key = bsoncxx::string::to_string(tag.key());
                    const std::string value = bsoncxx::string::to_string(tag[key].get_string().value);
                    tags[key] = value;
                }
            }

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CreateServerRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateServerRequest &r) {
        os << "CreateServerRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Transfer

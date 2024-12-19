//
// Created by vogje01 on 4/8/24.
//

#include <awsmock/dto/secretsmanager/model/SecretTags.h>

namespace AwsMock::Dto::SecretsManager {

    view_or_value<view, value> SecretTags::ToDocument() const {

        try {

            document rootDocument;

            // Entries
            if (!tags.empty()) {
                document entriesArray;
                for (const auto &[fst, snd]: tags) {
                    entriesArray.append(kvp(fst, snd));
                }
                rootDocument.append(kvp("Tags", entriesArray));
            }
            return rootDocument.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string SecretTags::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    void SecretTags::FromDocument(const view_or_value<view, value> &document) {

        try {

            // Tags
            if (document.view().find("Tags") != document.view().end()) {
                for (const bsoncxx::array::view arrayView{document.view()["Tags"].get_array().value}; const bsoncxx::array::element &element: arrayView) {
                    /*SecretTags sTtag;
                    sTtag.FromDocument(element.get_document().value);
                    tags.emplace_back(sTtag);*/
                }
            }

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string SecretTags::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const SecretTags &tags) {
        os << "SecretTags=" << tags.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::SecretsManager
//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/lambda/Tags.h>

namespace AwsMock::Database::Entity::Lambda {

    bool Tags::HasTag(const std::string &key) {
        return find_if(tags.begin(), tags.end(), [key](const std::pair <std::string, std::string> &t) {
            return t.first == key;
        }) != tags.end();
    }

    std::string Tags::GetTagValue(const std::string &key) {
        auto it = find_if(tags.begin(), tags.end(), [key](const std::pair <std::string, std::string> &t) {
            return t.first == key;
        });
        return it->second;
    }

    void Tags::FromDocument(mongocxx::stdx::optional <bsoncxx::document::view> mResult) {

        std::vector <std::string> keys;
        std::transform(mResult->begin(), mResult->end(), std::back_inserter(keys), [](bsoncxx::document::element ele) {
            return bsoncxx::string::to_string(ele.key());
        });

        for (auto &it: keys) {
            tags.emplace_back(it, bsoncxx::string::to_string(mResult.value()[it].get_string().value));
        }
    }

    view_or_value <view, value> Tags::ToDocument() const {

        // Convert environment to document
        auto tagDoc = bsoncxx::builder::basic::array{};
        for (const auto &tag: tags) {
            tagDoc.append(make_document(kvp(tag.first, tag.second)));
        }
        return make_document(kvp("Tags", tagDoc));
    }

    [[nodiscard]] std::string Tags::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Tags &t) {
        os << "Tags=" << bsoncxx::to_json(t.ToDocument());
        return os;
    }
}
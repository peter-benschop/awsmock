//
// Created by vogje01 on 4/30/24.
//

#include <awsmock/dto/lambda/model/Tags.h>

namespace AwsMock::Dto::Lambda {

    bool Tags::HasTag(const std::string &key) {
        return std::ranges::find_if(tags, [key](const std::pair<std::string, std::string> &t) {
                   return t.first == key;
               }) != tags.end();
    }

    std::string Tags::GetTagValue(const std::string &key) {
        const auto it = std::ranges::find_if(tags, [key](const std::pair<std::string, std::string> &t) {
            return t.first == key;
        });
        return it->second;
    }

    void Tags::FromDocument(const view_or_value<view, value> &document) {

        try {

            if (document.view().find("Tags") != document.view().end()) {
                for (const bsoncxx::array::view jsonArray = document.view()["Tags"].get_array().value; const auto &tag: jsonArray) {
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

    array Tags::ToDocument() const {

        try {
            // Tags
            array jsonArray;
            if (!tags.empty()) {
                for (const auto &[fst, snd]: tags) {
                    document tagObject;
                    tagObject.append(kvp(fst, snd));
                    jsonArray.append(tagObject);
                }
            }
            return jsonArray;

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string Tags::ToJson() const {

        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string Tags::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Tags &r) {
        os << "Tags=" << r.ToJson();
        return os;
    }


}// namespace AwsMock::Dto::Lambda

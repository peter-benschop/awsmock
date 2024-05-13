//
// Created by vogje01 on 4/30/24.
//

#include "awsmock/dto/lambda/model/Tags.h"

namespace AwsMock::Dto::Lambda {

    bool Tags::HasTag(const std::string &key) {
        return find_if(tags.begin(), tags.end(), [key](const std::pair<std::string, std::string> &t) {
                   return t.first == key;
               }) != tags.end();
    }

    std::string Tags::GetTagValue(const std::string &key) {
        auto it = find_if(tags.begin(), tags.end(), [key](const std::pair<std::string, std::string> &t) {
            return t.first == key;
        });
        return it->second;
    }

    void Tags::FromJson(Poco::JSON::Object::Ptr object) {

        try {

            Poco::JSON::Object::NameList nameList = object->getNames();
            for (const auto &name: nameList) {
                tags[name] = object->get(name).convert<std::string>();
            }

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message(), 500);
        }
    }

    Poco::JSON::Array Tags::ToJsonObject() const {

        Poco::JSON::Array tagArray;
        try {
            for (const auto &tag: tags) {
                Poco::JSON::Object tagJson;
                tagJson.set(tag.first, tag.second);
                tagArray.add(tagJson);
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
        return tagArray;
    }

    std::string Tags::ToJson() const {

        return Core::JsonUtils::ToJsonString(ToJsonObject());
    }

    std::string Tags::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Tags &r) {
        os << "Tags=" << r.ToJson();
        return os;
    }


}// namespace AwsMock::Dto::Lambda

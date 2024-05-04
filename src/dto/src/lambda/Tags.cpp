//
// Created by vogje01 on 4/30/24.
//

#include <awsmock/dto/lambda/model/Tags.h>

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
                tags.emplace_back(name, object->get(name).convert<std::string>());
            }

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message(), 500);
        }
    }

    std::string Tags::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Tags &r) {
        os << "Tags={tags=['";
        for (const auto &tag: r.tags) {
            os << tag.first << tag.second;
        }
        os << "]}";
        return os;
    }


}// namespace AwsMock::Dto::Lambda

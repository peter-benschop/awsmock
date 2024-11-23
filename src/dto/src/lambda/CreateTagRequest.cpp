//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/lambda/CreateTagRequest.h>

namespace AwsMock::Dto::Lambda {

    void CreateTagRequest::FromJson(const std::string &body) {

        try {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(body);
            Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

            Poco::JSON::Object::Ptr tagsObject = rootObject->getObject("Tags");

            Poco::JSON::Object::NameList nameList = tagsObject->getNames();
            for (const auto &name: nameList) {
                tags[name] = tagsObject->get(name).convert<std::string>();
            }

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
    }

    std::string CreateTagRequest::ToJson() const {

        try {
            Poco::JSON::Object rootObject;

            Poco::JSON::Object tagsJson;
            for (const auto &tag: tags) {
                tagsJson.set(tag.first, tag.second);
            }

            rootObject.set("Tags", tagsJson);
            std::ostringstream os;
            rootObject.stringify(os);
            return os.str();

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
    }

    std::string CreateTagRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateTagRequest &r) {
        os << "CreateTagRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda

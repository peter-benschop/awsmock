//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/CreateUserPoolRequest.h>

namespace AwsMock::Dto::Cognito {

    void CreateUserPoolRequest::FromJson(const std::string &payload) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(payload);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("PoolName", rootObject, name);
            Core::JsonUtils::GetJsonValueString("Domain", rootObject, domain);

            if (rootObject->has("UserPoolTags")) {
                Poco::JSON::Array::Ptr jsonTagsArray = rootObject->getArray("UserPoolTags");
                for (int i = 0; i < jsonTagsArray->size(); i++) {
                    Poco::JSON::Object::Ptr jsonTagObject = jsonTagsArray->getObject(i);
                    std::string key = jsonTagObject->getNames().front();
                    auto value = jsonTagObject->getValue<std::string>(key);
                    tags[key] = value;
                }
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CreateUserPoolRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("PoolName", name);
            rootJson.set("Domain", domain);

            // Tags
            Poco::JSON::Array tagsArray;
            for (const auto &tag: tags) {
                Poco::JSON::Object tagsObject;
                tagsObject.set(tag.first, tag.second);
                tagsArray.add(tagsObject);
            }
            rootJson.set("UserPollTags", tagsArray);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CreateUserPoolRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateUserPoolRequest &r) {
        os << "CreateUserPoolRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito
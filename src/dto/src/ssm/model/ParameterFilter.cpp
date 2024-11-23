//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/ssm/model/ParameterFilter.h>

namespace AwsMock::Dto::SSM {

    std::string ParameterFilter::ToJson() const {

        try {

            Poco::JSON::Object jsonObject = ToJsonObject();
            return Core::JsonUtils::ToJsonString(jsonObject);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    Poco::JSON::Object ParameterFilter::ToJsonObject() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Key", key);
            rootJson.set("Option", option);

            // Parameter filters
            Poco::JSON::Array jsonParameterFilterArray;
            for (const auto parameterFilter: parameterFilters) {
                jsonParameterFilterArray.add(parameterFilter.ToJsonObject());
            }
            rootJson.set("ParameterFilters", jsonParameterFilterArray);

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void ParameterFilter::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("Key", jsonObject, key);
            Core::JsonUtils::GetJsonValueString("Option", jsonObject, option);


            // Parameter filters
            if (jsonObject->has("ParameterFilters")) {
                Poco::JSON::Array::Ptr jsonParameterFilterArray = jsonObject->getArray("ParameterFilters");
                for (int i = 0; i < jsonParameterFilterArray->size(); i++) {
                    ParameterFilter parameterFilter;
                    parameterFilter.FromJsonObject(jsonParameterFilterArray->getObject(i));
                    parameterFilters.emplace_back(parameterFilter);
                }
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ParameterFilter::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ParameterFilter &r) {
        os << "ParameterFilter=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SSM

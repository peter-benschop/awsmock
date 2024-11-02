//
// Created by vogje01 on 1/20/24.
//

#include "awsmock/dto/docker/model/Filters.h"

namespace AwsMock::Dto::Docker {

    std::string Filters::ToJson() const {

        try {

            Poco::JSON::Object rootJson;

            Poco::JSON::Array filterArray;
            for (const auto &filter: filters) {
                Poco::JSON::Object filterObject;
                filterObject.set(filter.name, filter.value);
                filterArray.add(filterObject);
            }

            rootJson.set("reference", filterArray);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string Filters::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Filters &p) {
        os << "Filters=" << p.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Docker
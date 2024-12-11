//
// Created by vogje01 on 1/20/24.
//

#include <awsmock/dto/docker/model/Filters.h>

namespace AwsMock::Dto::Docker {

    std::string Filters::ToJson() const {

        try {

            document rootDocument;
            if (filters.empty()) {
                array jsonArray;
                for (const auto &[name, value]: filters) {
                    document jsonFilter;
                    jsonFilter.append(kvp(name, value));
                    jsonArray.append(jsonFilter);
                }
                rootDocument.append(kvp("reference", jsonArray));
            }
            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string Filters::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Filters &p) {
        os << "Filters=" << p.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Docker
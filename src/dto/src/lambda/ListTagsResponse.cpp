//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/lambda/ListTagsResponse.h>
#include <jwt-cpp/jwt.h>

namespace AwsMock::Dto::Lambda {

    std::string ListTagsResponse::ToJson() const {

        try {

            document rootDocument;
            if (!tags.empty()) {
                document jsonObject;
                for (const auto &t: tags) {
                    jsonObject.append(kvp(t.first, t.second));
                }
                rootDocument.append(kvp("Tags", jsonObject));
            }

            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListTagsResponse::ToString() {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, ListTagsResponse &r) {
        os << "ListTagsResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda

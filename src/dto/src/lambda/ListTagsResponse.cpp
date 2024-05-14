//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/lambda/ListTagsResponse.h>

namespace AwsMock::Dto::Lambda {

    std::string ListTagsResponse::ToJson() {

        try {
            Poco::JSON::Object rootJson;
            Poco::JSON::Object tagsObject;
            for (const auto &t: tags) {
                tagsObject.set(t.first, t.second);
            }
            rootJson.set("Tags", tagsObject);

            std::ostringstream os;
            rootJson.stringify(os);
            return os.str();

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
    }

    std::string ListTagsResponse::ToString() {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, ListTagsResponse &r) {
        os << "ListTagsResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda

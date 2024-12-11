//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/dto/docker/ListContainerResponse.h>

namespace AwsMock::Dto::Docker {

    ListContainerResponse::ListContainerResponse(const std::string &body) {
        FromJson(body);
    }

    void ListContainerResponse::FromJson(const std::string &body) {

        try {
            const value document = bsoncxx::from_json(body);
            for (const auto &element: document.view()) {
                Container container;
                container.FromDocument(element.get_document().value);
                containerList.push_back(container);
            }

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListContainerResponse::ToJson() const {

        try {

            array document;
            if (!containerList.empty()) {
                for (const auto &container: containerList) {
                    document.append(container.ToDocument());
                }
            }
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListContainerResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListContainerResponse &r) {
        os << "ListContainerResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Docker

//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/dto/docker/ListImageResponse.h>

namespace AwsMock::Dto::Docker {

    void ListImageResponse::FromJson(const std::string &jsonString) {

        try {

            const value document = bsoncxx::from_json(jsonString);
            if (const view jsonArray = document.view(); !jsonArray.empty()) {
                for (const auto &item: jsonArray) {
                    Image image;
                    image.FromDocument(item.get_document().value);
                    imageList.emplace_back(image);
                }
            }

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListImageResponse::ToJson() const {

        try {
            if (!imageList.empty()) {
                array jsonArray;
                for (const auto &image: imageList) {
                    jsonArray.append(image.ToDocument());
                }
                return Core::Bson::BsonUtils::ToJsonString(jsonArray);
            }
            return {};

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListImageResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListImageResponse &r) {
        os << "ImageListResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Docker

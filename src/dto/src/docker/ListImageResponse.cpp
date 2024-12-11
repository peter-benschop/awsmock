//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/dto/docker/ListImageResponse.h>

namespace AwsMock::Dto::Docker {

    void ListImageResponse::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);
            if (!document.view().empty()) {
                //array jsonArray = document
            }
            //            topicArn = Core::Bson::BsonUtils::GetStringValue(document, "topicArn");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
        /*
        try {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(jsonString);
            Poco::JSON::Array::Ptr rootArray = result.extract<Poco::JSON::Array::Ptr>();
            if (rootArray != nullptr) {
                for (const auto &it: *rootArray) {
                    Image image;
                    image.FromJson(it.extract<Poco::JSON::Object::Ptr>());
                    imageList.push_back(image);
                }
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/
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

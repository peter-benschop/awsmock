//
// Created by vogje01 on 22/09/2023.
//

#include <awsmock/dto/docker/model/Container.h>

namespace AwsMock::Dto::Docker {

    int Container::GetLambdaPort() {
        if (const auto it = std::ranges::find_if(ports, [](const Port &port) { return port.privatePort == LAMBDA_INTERNAL_PORT; }); it != ports.end()) {
            return it->publicPort;
        }
        return -1;
    }

    void Container::FromDocument(const view_or_value<view, value> &document) {

        try {

            id = Core::Bson::BsonUtils::GetStringValue(document, "Id");
            image = Core::Bson::BsonUtils::GetStringValue(document, "Image");
            imageId = Core::Bson::BsonUtils::GetStringValue(document, "ImageID");
            command = Core::Bson::BsonUtils::GetStringValue(document, "Command");
            state = Core::Bson::BsonUtils::GetStringValue(document, "State");
            status = Core::Bson::BsonUtils::GetStringValue(document, "Status");
            sizeRw = Core::Bson::BsonUtils::GetLongValue(document, "SizeRw");
            sizeRootFs = Core::Bson::BsonUtils::GetLongValue(document, "SizeRootFs");

            // Names array
            if (document.view().find("Names") != document.view().end()) {
                for (const bsoncxx::array::view namesArray = document.view()["Names"].get_array().value; const auto &nt: namesArray) {
                    names.emplace_back(nt.get_string().value);
                }
            }

            // Ports array
            if (document.view().find("Ports") != document.view().end()) {
                for (const bsoncxx::array::view namesArray = document.view()["Ports"].get_array().value; const auto &nt: namesArray) {
                    Port port(nt.get_document().value);
                    ports.emplace_back(port);
                }
            }

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> Container::ToDocument() const {

        try {
            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "id", id);
            Core::Bson::BsonUtils::SetStringValue(document, "image", image);
            Core::Bson::BsonUtils::SetStringValue(document, "imageId", imageId);
            Core::Bson::BsonUtils::SetStringValue(document, "command", command);
            Core::Bson::BsonUtils::SetStringValue(document, "state", state);

            if (!names.empty()) {
                array jsonArray;
                for (const auto &name: names) {
                    jsonArray.append(name);
                }
                document.append(kvp("names", jsonArray));
            }

            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string Container::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string Container::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Container &c) {
        os << "ListContainerResponse=" << c.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Docker

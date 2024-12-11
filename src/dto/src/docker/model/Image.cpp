//
// Created by JVO on 22.04.2024.
//

#include <awsmock/dto/docker/model/Image.h>

namespace AwsMock::Dto::Docker {

    void Image::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);
            FromDocument(document.view());

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void Image::FromDocument(const view_or_value<view, value> &document) {

        try {
            id = Core::Bson::BsonUtils::GetStringValue(document, "Id");
            parentId = Core::Bson::BsonUtils::GetStringValue(document, "ParentId");
            size = Core::Bson::BsonUtils::GetLongValue(document, "Size");
            sharedSize = Core::Bson::BsonUtils::GetLongValue(document, "SharedSize");
            virtualSize = Core::Bson::BsonUtils::GetLongValue(document, "VirtualSize");
            containers = Core::Bson::BsonUtils::GetIntValue(document, "Containers");

            if (document.view().find("RepoTags") != document.view().end()) {
                for (const bsoncxx::array::view repoTagsArray = document.view()["ReproTags"].get_array().value; const auto &tag: repoTagsArray) {
                    repoTags.emplace_back(tag.get_string().value);
                }
            }

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> Image::ToDocument() const {

        try {
            document rootDocument;
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "Id", id);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "ParentId", parentId);
            Core::Bson::BsonUtils::SetLongValue(rootDocument, "Size", size);
            Core::Bson::BsonUtils::SetLongValue(rootDocument, "SharedSize", sharedSize);
            Core::Bson::BsonUtils::SetLongValue(rootDocument, "VirtualSize", virtualSize);
            Core::Bson::BsonUtils::SetLongValue(rootDocument, "Containers", containers);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "ParentId", parentId);

            if (!repoTags.empty()) {
                array jsonArray;
                for (const auto &tag: repoTags) {
                    jsonArray.append(tag);
                }
                rootDocument.append(kvp("RepoTags", jsonArray));
            }
            return rootDocument.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string Image::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string Image::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Image &i) {
        os << "Image=" << i.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Docker

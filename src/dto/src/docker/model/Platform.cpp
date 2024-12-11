//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/dto/docker/model/Platform.h>

namespace AwsMock::Dto::Docker {

    void Platform::FromDocument(const view_or_value<view, value> &document) {

        try {

            name = Core::Bson::BsonUtils::GetStringValue(document, "Name");

        } catch (bsoncxx::exception &e) {
            log_error << e.what();
            throw Core::JsonException(e.what());
        }
    }

}// namespace AwsMock::Dto::Docker

//
// Created by vogje01 on 30/05/2023.
//

#include "awsmock/dto/lambda/model/DeadLetterConfig.h"

namespace AwsMock::Dto::Lambda {

    view_or_value<view, value> DeadLetterConfig::ToDocument() const {

        try {
            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "TargetArn", targetArn);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            throw Core::JsonException(exc.what());
        }
    }

}// namespace AwsMock::Dto::Lambda

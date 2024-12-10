//
// Created by vogje01 on 5/10/24.
//

#include <awsmock/dto/s3/model/RestoreStatus.h>

namespace AwsMock::Dto::S3 {

    view_or_value<view, value> RestoreStatus::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetBoolValue(document, "IsRestoreInProgress", isRestoreInProgress);
            Core::Bson::BsonUtils::SetDateValue(document, "RestoreExpiryDate", restoreExpiryDate);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

}// namespace AwsMock::Dto::S3

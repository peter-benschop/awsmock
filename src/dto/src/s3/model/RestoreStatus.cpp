//
// Created by vogje01 on 5/10/24.
//

#include <awsmock/dto/s3/model/RestoreStatus.h>

namespace AwsMock::Dto::S3 {

    Poco::JSON::Object RestoreStatus::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("IsRestoreInProgress", isRestoreInProgress);
            rootJson.set("RestoreExpiryDate", Poco::DateTimeFormatter::format(restoreExpiryDate, Poco::DateTimeFormat::ISO8601_FORMAT));
            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

}// namespace AwsMock::Dto::S3
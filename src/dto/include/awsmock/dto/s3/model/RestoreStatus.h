//
// Created by vogje01 on 5/10/24.
//

#ifndef AWSMOCK_RESTORESTATUS_H
#define AWSMOCK_RESTORESTATUS_H

// C++ includes
#include <sstream>
#include <string>

// AwsMock includes
#include "awsmock/core/exception/JsonException.h"
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/XmlUtils.h>
#include <awsmock/dto/s3/model/Owner.h>

namespace AwsMock::Dto::S3 {

    struct RestoreStatus {

        /**
         * Is restore in progress
         */
        bool isRestoreInProgress;

        /**
         * Expiration datetime
         */
        Poco::DateTime restoreExpiryDate;

        /**
         * Convert to a JSON object
         *
         * @return JSON object
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;
    };

}// namespace AwsMock::Dto::S3
#endif//AWSMOCK_RESTORESTATUS_H

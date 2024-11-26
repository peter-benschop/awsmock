//
// Created by vogje01 on 9/30/24.
//

#ifndef AWSMOCK_DTO_COMMON_SORT_COLUMN_H
#define AWSMOCK_DTO_COMMON_SORT_COLUMN_H

// C++ includes
#include <string>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>

namespace AwsMock::Core {

    struct SortColumn {

        /**
         * Columns
         */
        std::string column;

        /**
         * Direction, MongoDB style, 1: ascending, -1 descending
         */
        int sortDirection;

        /**
         * @brief Convert from JSON object
         *
         * @param jsonObject JSON object
         */
        void FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject);

        /**
         * @brief Convert to JSON object
         *
         * @return JSON object
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;
    };

}// namespace AwsMock::Core

#endif// AWSMOCK_DTO_COMMON_SORT_COLUMN_H

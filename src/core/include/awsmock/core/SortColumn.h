//
// Created by vogje01 on 9/30/24.
//

#ifndef AWSMOCK_DTO_COMMON_SORT_COLUMN_H
#define AWSMOCK_DTO_COMMON_SORT_COLUMN_H

// C++ includes
#include <string>

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
    };

}// namespace AwsMock::Core

#endif// AWSMOCK_DTO_COMMON_SORT_COLUMN_H

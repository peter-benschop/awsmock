//
// Created by vogje01 on 12/21/23.
//

#ifndef AWSMOCK_DTO_DYNAMODB_TABLE_STATUS_H
#define AWSMOCK_DTO_DYNAMODB_TABLE_STATUS_H

// C++ includes
#include <map>
#include <string>

namespace AwsMock::Dto::DynamoDb {

    /**
     * DynamoDB table status
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    enum class TableStatus {
        CREATING,
        UPDATING,
        DELETING,
        ACTIVE,
        INACCESSIBLE_ENCRYPTION_CREDENTIALS,
        ARCHIVING,
        ARCHIVED,
        UNKNOWN
    };

    static std::map<TableStatus, std::string> TableStatusNames{
            {TableStatus::CREATING, "CREATING"},
            {TableStatus::UPDATING, "UPDATING"},
            {TableStatus::DELETING, "DELETING"},
            {TableStatus::ACTIVE, "ACTIVE"},
            {TableStatus::INACCESSIBLE_ENCRYPTION_CREDENTIALS, "INACCESSIBLE_ENCRYPTION_CREDENTIALS"},
            {TableStatus::ARCHIVING, "ARCHIVING"},
            {TableStatus::ARCHIVED, "ARCHIVED"},
            {TableStatus::UNKNOWN, "UNKNOWN"},
    };

    [[maybe_unused]] static std::string TableStatusToString(TableStatus tableStatus) {
        return TableStatusNames[tableStatus];
    }

    [[maybe_unused]] static TableStatus TableStatusFromString(const std::string &tableStatus) {
        for (auto &it: TableStatusNames) {
            if (it.second == tableStatus) {
                return it.first;
            }
        }
        return TableStatus::UNKNOWN;
    }

}// namespace AwsMock::Dto::DynamoDb

#endif// AWSMOCK_DTO_DYNAMODB_TABLE_STATUS_H

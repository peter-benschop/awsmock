//
// Created by vogje01 on 5/10/24.
//

#ifndef AWSMOCK_DTO_S3_MAPPER_H
#define AWSMOCK_DTO_S3_MAPPER_H

// AwsMock includes
#include <awsmock/dto/s3/ListObjectVersionsRequest.h>
#include <awsmock/dto/s3/ListObjectVersionsResponse.h>
#include <awsmock/entity/s3/Object.h>

namespace AwsMock::Dto::S3 {

    /**
     * @brief Maps an entity to the corresponding DTO
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class Mapper {

      public:

        /**
         * @brief Maps a S3 object entity list to a list version response
         *
         * @param objectList S3 object entity list
         * @return ListObjectVersionsResponse
         * @see ListObjectVersionsResponse
         */
        static Dto::S3::ListObjectVersionsResponse map(const ListObjectVersionsRequest &request, const std::vector<Database::Entity::S3::Object> &objectList);
    };

}// namespace AwsMock::Dto::S3

#endif// AWSMOCK_DTO_S3_MAPPER_H

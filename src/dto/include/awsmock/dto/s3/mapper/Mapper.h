//
// Created by vogje01 on 5/10/24.
//

#ifndef AWSMOCK_DTO_S3_MAPPER_H
#define AWSMOCK_DTO_S3_MAPPER_H

// AwsMock includes
#include <awsmock/dto/s3/ListObjectVersionsResponse.h>
#include <awsmock/entity/s3/Object.h>

namespace AwsMock::Dto::S3 {

    class Mapper {

      public:

        /**
         * Maps a S3 object entity list to a list version response
         *
         * @param objectList S3 object entity list
         * @return ListObjectVersionsResponse
         */
        static Dto::S3::ListObjectVersionsResponse map(const std::string &region, const std::string &bucket, int maxKeys, const std::vector<Database::Entity::S3::Object> &objectList);
    };

}// namespace AwsMock::Dto::S3

#endif// AWSMOCK_DTO_S3_MAPPER_H

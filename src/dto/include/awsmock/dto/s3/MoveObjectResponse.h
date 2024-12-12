//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_S3_MOVEOBJECTSRESPONSE_H
#define AWSMOCK_DTO_S3_MOVEOBJECTSRESPONSE_H

// C++ standard includes
#include <sstream>
#include <string>

namespace AwsMock::Dto::S3 {

    struct MoveObjectResponse {

        /**
         * Etag
         */
        std::string eTag;

        /**
         * Last modified
         */
        std::string lastModified;

        /**
         * Convert to XML representation
         *
         * @return XML string
         */
        [[nodiscard]] std::string ToXml() const;

        /**
         * Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const MoveObjectResponse &r);
    };

}// namespace AwsMock::Dto::S3

#endif// AWSMOCK_DTO_S3_MOVEOBJECTSRESPONSE_H

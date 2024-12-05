//
// Created by vogje01 on 03/09/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_EPHEMERAL_STORAGE_H
#define AWSMOCK_DTO_LAMBDA_EPHEMERAL_STORAGE_H

// C++ standard includes
#include <string>

// AwsMock includes
#include "awsmock/core/exception/ServiceException.h"
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>

namespace AwsMock::Dto::Lambda {

    struct EphemeralStorage {

        /**
         * Temporary disk space in MB. Default: 512 MB, Range: 512 - 10240 MB
         */
        long size = 512;

        /**
         * Convert to a JSON object
         *
         * @return JSON object
         */
        view_or_value<view, value> ToDocument() const {

            try {
                bsoncxx::builder::basic::document document;
                Core::Bson::BsonUtils::SetLongValue(document, "Size", size);
                return view_or_value<view, value>(document);

            } catch (bsoncxx::exception &exc) {
                log_error << exc.what();
                throw Core::JsonException(exc.what());
            }
        }

        /**
         * Convert to a JSON string
         *
         * @param jsonObject JSON string
         */
        void FromJson(const Poco::JSON::Object::Ptr &jsonObject) {

            try {
                Core::JsonUtils::GetJsonValueLong("Size", jsonObject, size);
            } catch (Poco::Exception &exc) {
                log_error << exc.message();
                throw Core::JsonException(exc.message());
            }
        }

        /**
         * Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const {
            std::stringstream ss;
            ss << *this;
            return ss.str();
        }

        /**
         * Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const EphemeralStorage &r) {
            os << "EphemeralStorage=" << to_json(r.ToDocument());
            return os;
        }
    };

}// namespace AwsMock::Dto::Lambda

#endif// AWSMOCK_DTO_LAMBDA_EPHEMERAL_STORAGE_H

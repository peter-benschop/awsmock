//
// Created by vogje01 on 03/09/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_EPHEMERALSTORAGE_H
#define AWSMOCK_DTO_LAMBDA_EPHEMERALSTORAGE_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

// AwsMock includes
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::Lambda {

  struct EphemeralStorage {

    /**
     * Temporary disk space in MB. Default: 512 MB, Range: 512 - 10240 MB
     */
    long size = 512;

    /**
     * Convert to a JSON string
     *
     * @return JSON string
     */
    [[nodiscard]] Poco::JSON::Object ToJson() const {

      Poco::JSON::Object ephemeralStorageJson;
      try {

        Poco::JSON::Object errorJson;
        errorJson.set("Size", size);

      } catch (Poco::Exception &exc) {
        throw Core::ServiceException(exc.message(), 500);
      }
      return ephemeralStorageJson;
    }

    /**
     * Convert to a JSON string
     *
     * @return JSON string
     */
    void FromJson(const Poco::JSON::Object::Ptr &jsonObject) {

      try {
        Core::JsonUtils::GetJsonValueLong("Size", jsonObject, size);
      } catch (Poco::Exception &exc) {
        throw Core::ServiceException(exc.message(), 500);
      }
    }

    /**
     * Converts the DTO to a string representation.
     *
     * @return DTO as string for logging.
     */
    [[nodiscard]] std::string ToString() const {
      std::stringstream ss;
      ss << (*this);
      return ss.str();
    }

    /**
     * Stream provider.
     *
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const EphemeralStorage &r) {
      os << "EphemeralStorage={size={'" << r.size << "'}";
      return os;
    }

  };

} // AwsMock::Dto::lambda
#endif // AWSMOCK_DTO_LAMBDA_EPHEMERALSTORAGE_H

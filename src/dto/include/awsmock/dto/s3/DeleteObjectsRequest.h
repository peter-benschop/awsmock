//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_CORE_DTO_DELETEOBJECTSREQUEST_H
#define AWSMOCK_CORE_DTO_DELETEOBJECTSREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>
#include <vector>

// Poco includes
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/NodeList.h"

namespace AwsMock::Dto::S3 {

    struct DeleteObjectsRequest {

      /**
       * Constructor.
       *
       * @param xmlString XML request structure
       */
      explicit DeleteObjectsRequest(const std::string &xmlString);

      /**
       * Region
       */
      std::string region;

      /**
       * Bucket
       */
      std::string bucket;

      /**
       * Key
       */
      std::vector<std::string> keys;

      /**
       * Parse the delete objects request XML.
       *
       * @param xmlString notification XML string
       */
      void FromXml(const std::string &xmlString);

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
      friend std::ostream &operator<<(std::ostream &os, const DeleteObjectsRequest &r);

    };

} // namespace AwsMock::Dto::S3

#endif //AWSMOCK_CORE_DTO_DELETEOBJECTSREQUEST_H

//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_S3_CREATEBUCKETRESPONSE_H
#define AWSMOCK_DTO_S3_CREATEBUCKETRESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/Text.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/XML/XMLWriter.h"

namespace AwsMock::Dto::S3 {

    class CreateBucketResponse {

    public:

      /**
       * Constructor
       */
      CreateBucketResponse() = default;

      /**
       * Constructor
       *
       * @param location bucket location
       * @param arn bucket ARN
       */
      CreateBucketResponse(const std::string &location, const std::string &arn);

      /**
       * Convert to XML representation
       *
       * @return XML string
       */
      std::string ToXml();

      /**
       * Returns the location
       *
       * @return location name
       */
      std::string GetLocation() { return _location; }

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const;

    private:

      /**
       * Bucket location
       */
      std::string _location;

      /**
       * Bucket ARN
       */
      std::string _arn;

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &, const CreateBucketResponse &);
    };

} // namespace AwsMock::Dto

#endif //AWSMOCK_DTO_S3_CREATEBUCKETRESPONSE_H

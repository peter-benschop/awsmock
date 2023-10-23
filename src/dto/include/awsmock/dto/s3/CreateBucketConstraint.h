//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_S3_CREATEBUCKETCONSTRAINT_H
#define AWSMOCK_DTO_S3_CREATEBUCKETCONSTRAINT_H

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

    struct CreateBucketConstraint {

      /**
       * Bucket location
       */
      std::string location;

      /**
       * Convert to XML representation
       *
       * <CreateBucketConfiguration xmlns="http://s3.amazonaws.com/doc/2006-03-01/">
       *     <LocationConstraint>eu-central-1</LocationConstraint>
       * </CreateBucketConfiguration>
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
      friend std::ostream &operator<<(std::ostream &os, const CreateBucketConstraint &r);

    };

} // namespace AwsMock::Dto

#endif // AWSMOCK_DTO_S3_CREATEBUCKETCONSTRAINT_H

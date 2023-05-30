//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_S3_LISTALLBUCKETRESPONSE_H
#define AWSMOCK_DTO_S3_LISTALLBUCKETRESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/Text.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/XML/XMLWriter.h"

namespace AwsMock::Dto::S3 {

    class BucketRecord {
    public:
      std::string name;
      Poco::DateTime creationDatetime;
    };

    typedef std::vector<BucketRecord> BucketList;

    class ListAllBucketResponse {

    public:

      /**
       * Constructor
       */
      ListAllBucketResponse() = delete;

      /**
       * Constructor
       *
       * @param bucketList list of bucket record.
       */
      ListAllBucketResponse(BucketList bucketList);

      /**
       * Convert to XML representation
       *
       * @return XML string
       */
      std::string ToXml();

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const;

    private:

      /**
       * List of buckets
       */
      BucketList &_bucketList;

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &, const ListAllBucketResponse &);
    };

} // namespace AwsMock::Dto

#endif //AWSMOCK_DTO_S3_LISTALLBUCKETRESPONSE_H

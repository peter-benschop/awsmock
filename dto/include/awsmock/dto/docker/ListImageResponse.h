//
// Created by vogje01 on 06/06/2023.
//

#ifndef AWSMOCK_DTO_DOCKER_IMAGELIST_H
#define AWSMOCK_DTO_DOCKER_IMAGELIST_H

// C++ includes
#include <string>
#include <sstream>
#include <vector>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

namespace AwsMock::Dto::Docker {

    struct ListImageResponse {

      /**
       * Image ID
       */
      std::string id;

      /**
       * Running containers
       */
      int containers;

      /**
       * Labels
       */
      std::string labels;

      /**
       * Parent ID
       */
      std::string parentId;

      /**
       * Repository digest
       */
      std::string repoDigest;

      /**
       * Repo tags
       */
      std::vector<std::string> repoTags;

      /**
       * Shared size
       */
      long sharedSize;

      /**
       * Size
       */
      long size;

      /**
       * Size
       */
      long virtualSize;

      /**
       * Created date time
       */
      Poco::DateTime created;

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
      friend std::ostream &operator<<(std::ostream &os, const ListImageResponse &r) {
          os << "ImageListResponse={id='" + r.id + "' containers='" + std::to_string(r.containers) + "' labels='" + r.labels + "' parentId='" + r.parentId +
              "' repoDigest='" + r.repoDigest + "' repoTags='";
          for(auto &it:r.repoTags) {
              os <<  it + ",";
          }
          os << "' sharedSize='" + std::to_string(r.sharedSize) + "' size='" + std::to_string(r.size)+ "' virtualSize='" + std::to_string(r.virtualSize) +
          Poco::DateTimeFormatter().format(r.created, Poco::DateTimeFormat::HTTP_FORMAT);
          return os;
      }

    };

} // namespace AwsMock::Dto::Docker

#endif //AWSMOCK_DTO_DOCKER_IMAGELIST_H

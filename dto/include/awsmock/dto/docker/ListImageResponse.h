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

    struct Image {

      /**
       * Image ID
       */
      std::string id;

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
      long sharedSize = 0;

      /**
       * Size
       */
      long size = 0;

      /**
       * Size
       */
      long virtualSize = 0;

      /**
       * Created date time
       */
      Poco::DateTime created;

      /**
       * Repo tags
       */
      std::vector<std::string> labels;

      /**
       * Convert to a JSON string
       *
       * @return JSON string
       */
      void FromJson(Poco::JSON::Object::Ptr object) {

          try {
              id = object->get("Id").convert<std::string>();
              parentId = object->get("ParentId").convert<std::string>();
              size = object->get("Size").convert<long>();
              sharedSize = object->get("SharedSize").convert<long>();
              virtualSize = object->get("VirtualSize").convert<long>();

              Poco::JSON::Array::Ptr reproTagsArray = object->getArray("RepoTags");
              for (Poco::JSON::Array::ConstIterator nt = reproTagsArray->begin(); nt != reproTagsArray->end(); ++nt) {
                  repoTags.push_back(nt->convert<std::string>());
              }

              object->clear();

          } catch (Poco::Exception &exc) {
              std::cerr << exc.message() << std::endl;
              throw Core::ServiceException(exc.message(), 500);
          }
      }

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string
      ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const Image &i) {
          os << "Image={id='" + i.id + "' parentId='" + i.parentId + "' size='" + std::to_string(i.size) + "' sharedSize='" + std::to_string(i.sharedSize) +
              "' virtualSize='" + std::to_string(i.virtualSize) + "' labels='";
          for (auto &it : i.labels) {
              os << it + ",";
          }
          os << "'}";
          return os;
      }
    };

    struct ListImageResponse {

      /**
       * Image list
       */
      std::vector<Image> imageList;

      /**
       * Convert to a JSON string
       *
       * @return JSON string
       */
      void FromJson(const std::string &body) {

          try {
              Poco::JSON::Parser parser;
              Poco::Dynamic::Var result = parser.parse(body);
              Poco::JSON::Array::Ptr rootArray = result.extract<Poco::JSON::Array::Ptr>();

              for (Poco::JSON::Array::ConstIterator it = rootArray->begin(); it != rootArray->end(); ++it) {
                  Image image;
                  image.FromJson(it->extract<Poco::JSON::Object::Ptr>());
                  imageList.push_back(image);
              }

              // Cleanup
              rootArray->clear();
              parser.reset();

          } catch (Poco::Exception &exc) {
              std::cerr << exc.message() << std::endl;
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
      friend std::ostream &operator<<(std::ostream &os, const ListImageResponse &r) {
          os << "ImageListResponse={";
          for(auto &it:r.imageList) {
              os <<  it.ToString() + ",";
          }
          return os;
      }

    };

} // namespace AwsMock::Dto::Docker

#endif //AWSMOCK_DTO_DOCKER_IMAGELIST_H

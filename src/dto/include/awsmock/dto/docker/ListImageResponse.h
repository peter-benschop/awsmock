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
     * Number of containers using this image
     */
    int containers = 0;

    /**
     * Convert to a JSON string
     *
     * @param jsonString JSON string
     */
    void FromJson(const std::string &jsonString) {

      try {
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);

        this->FromJson(result.extract<Poco::JSON::Object::Ptr>());

      } catch (Poco::Exception &exc) {
        throw Core::ServiceException(exc.message(), 500);
      }
    }

    /**
     * Convert to a JSON string
     *
     * @param jsonObject JSON object
     */
    void FromJson(Poco::JSON::Object::Ptr jsonObject) {

      try {
        Core::JsonUtils::GetJsonValueString("Id", jsonObject, id);
        Core::JsonUtils::GetJsonValueString("ParentId", jsonObject, parentId);
        Core::JsonUtils::GetJsonValueLong("Size", jsonObject, size);
        Core::JsonUtils::GetJsonValueLong("SharedSize", jsonObject, sharedSize);
        Core::JsonUtils::GetJsonValueLong("VirtualSize", jsonObject, virtualSize);
        Core::JsonUtils::GetJsonValueInt("Containers", jsonObject, containers);

        Poco::JSON::Array::Ptr reproTagsArray = jsonObject->getArray("RepoTags");
        if (reproTagsArray != nullptr) {
          for (Poco::JSON::Array::ConstIterator nt = reproTagsArray->begin(); nt != reproTagsArray->end(); ++nt) {
            repoTags.push_back(nt->convert<std::string>());
          }
        }

      } catch (Poco::Exception &exc) {
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
      os << "Image={id='" << i.id << "' parentId='" << i.parentId << "' size='" << i.size << "' sharedSize='" << i.sharedSize << "' virtualSize='" << i.virtualSize
         << "' labels='";
      for (auto &it : i.labels) {
        os << it << ",";
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
     * Constructor
     *
     * @param body HTTP response body
     */
    explicit ListImageResponse(const std::string &body) {
      FromJson(body);
    }

    /**
     * Convert to a JSON string
     *
     * @param jsonString JSON string
     */
    void FromJson(const std::string &jsonString) {

      try {
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        Poco::JSON::Array::Ptr rootArray = result.extract<Poco::JSON::Array::Ptr>();
        if (rootArray != nullptr) {
          for (Poco::JSON::Array::ConstIterator it = rootArray->begin(); it != rootArray->end(); ++it) {
            Image image;
            image.FromJson(it->extract<Poco::JSON::Object::Ptr>());
            imageList.push_back(image);
          }
        }

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
    friend std::ostream &operator<<(std::ostream &os, const ListImageResponse &r) {
      os << "ImageListResponse={";
      for (auto &it : r.imageList) {
        os << it.ToString() + ",";
      }
      return os;
    }

  };

} // namespace AwsMock::Dto::Docker

#endif //AWSMOCK_DTO_DOCKER_IMAGELIST_H

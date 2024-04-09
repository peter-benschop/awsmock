//
// Created by vogje01 on 4/8/24.
//

#include <awsmock/dto/secretsmanager/VersionIdsToStages.h>

namespace AwsMock::Dto::SecretsManager {

  /**
   * Converts the DTO to a JSON representation.
   *
   * @return DTO as string for logging.
   */
  Poco::JSON::Object VersionIdsToStages::ToJsonObject() const {

    try {

      Poco::JSON::Object rootJson;
      for (const auto &version : versions) {

        Poco::JSON::Object versionObject;
        Poco::JSON::Array stagesArray;
        for (const auto &stage : version.second) {
          stagesArray.add(stage);
        }
        rootJson.set(version.first, stagesArray);
      }
      return rootJson;

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  /**
   * Converts a JSON representation to s DTO.
   *
   * @param jsonObject JSON object.
   */
  void VersionIdsToStages::FromJson(const Poco::JSON::Object::Ptr &jsonObject) {

    try {

      //Core::JsonUtils::GetJsonValueString("Region", jsonObject, region);
      //Core::JsonUtils::GetJsonValueString("ARN", jsonObject, arn);

    } catch (Poco::Exception &exc) {
      std::cerr << exc.message() << std::endl;
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string VersionIdsToStages::ToJson() const {

    std::ostringstream os;
    ToJsonObject().stringify(os);
    return os.str();
  }

  std::string VersionIdsToStages::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  /**
   * Stream provider.
   *
   * @return output stream
   */
  std::ostream &operator<<(std::ostream &os, const VersionIdsToStages &r) {
    os << "VersionIdToStages=" + r.ToJson();
    return os;
  }

} // namespace AwsMock::Dto::SecretsManager

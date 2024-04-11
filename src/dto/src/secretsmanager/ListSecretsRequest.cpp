//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/secretsmanager/ListSecretsRequest.h>

namespace AwsMock::Dto::SecretsManager {

  std::string ListSecretsRequest::ToJson() const {

    try {

      Poco::JSON::Object rootJson;
      rootJson.set("Region", region);
      rootJson.set("SortOrder", sortOrder);
      rootJson.set("NextToken", nextToken);
      rootJson.set("MaxResults", maxResults);
      rootJson.set("IncludePlannedDeletion", includePlannedDeletion);

      // Filters
      Poco::JSON::Array jsonFiltersArray;
      for (const auto &f : filters) {
        jsonFiltersArray.add(f.ToJsonObject());
      }
      rootJson.set("Filters", jsonFiltersArray);

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::JsonException(exc.message());
    }
  }

  void ListSecretsRequest::FromJson(const std::string &jsonString) {

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(jsonString);
    const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {

      Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
      Core::JsonUtils::GetJsonValueString("SortOrder", rootObject, sortOrder);
      Core::JsonUtils::GetJsonValueString("NextToken", rootObject, nextToken);
      Core::JsonUtils::GetJsonValueInt("MaxResults", rootObject, maxResults);
      Core::JsonUtils::GetJsonValueBool("IncludePlannedDeletion", rootObject, includePlannedDeletion);

      if(rootObject->has("Filters")) {
        Poco::JSON::Array::Ptr jsonTagsArray = rootObject->getArray("Filters");
        for (int i = 0; i < jsonTagsArray->size(); i++) {
          Filter filter;
          filter.FromJsonObject(jsonTagsArray->getObject(i));
          filters.emplace_back(filter);
        }
      }

    } catch (Poco::Exception &exc) {
      throw Core::JsonException(exc.message());
    }
  }

  std::string ListSecretsRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const ListSecretsRequest &r) {
    os << "ListSecretsRequest=" << r.ToJson();
    return os;
  }

} // namespace AwsMock::Dto::S3

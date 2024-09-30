
#include <awsmock/dto/s3/ListObjectCounterResponse.h>

namespace AwsMock::Dto::S3 {

    std::string ListObjectCounterResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("total", total);

            // Contents
            if (!objectCounters.empty()) {

                Poco::JSON::Array jsonObjectArray;
                for (auto &object: objectCounters) {
                    Poco::JSON::Object jsonObject;
                    jsonObject.set("keys", object.key);
                    jsonObject.set("size", object.size);
                    jsonObjectArray.add(jsonObject);
                }

                rootJson.set("objectCounters", jsonObjectArray);
            }

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    [[nodiscard]] std::string ListObjectCounterResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListObjectCounterResponse &r) {
        os << "ListObjectCounterResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3

#include <awsmock/core/SortColumn.h>

namespace AwsMock::Core {

    void SortColumn::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        Core::JsonUtils::GetJsonValueString("column", jsonObject, column);
        Core::JsonUtils::GetJsonValueInt("sortDirection", jsonObject, sortDirection);
    }

    Poco::JSON::Object SortColumn::ToJsonObject() const {

        try {
            Poco::JSON::Object rootJson;

            rootJson.set("column", column);
            rootJson.set("sortDirection", sortDirection);

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

}// namespace AwsMock::Core
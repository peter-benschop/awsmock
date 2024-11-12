
#include <awsmock/core/SortColumn.h>

namespace AwsMock::Core {

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
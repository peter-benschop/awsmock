//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/lambda/EphemeralStorage.h>

namespace AwsMock::Database::Entity::Lambda {

    void EphemeralStorage::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {
        size = static_cast<long>(mResult.value()["size"].get_int64());
    }

    view_or_value<view, value> EphemeralStorage::ToDocument() const {

        view_or_value<view, value> ephemeralStorageDocument = make_document(kvp("size", static_cast<bsoncxx::types::b_int64>(size)));
        return ephemeralStorageDocument;
    }

    void EphemeralStorage::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        try {

            Core::JsonUtils::GetJsonValueLong("size", jsonObject, size);

        } catch (Poco::Exception &e) {
            log_error << "JSON Exception" << e.message();
            throw Core::JsonException(e.message());
        }
    }

    Poco::JSON::Object EphemeralStorage::ToJsonObject() const {

        try {

            Poco::JSON::Object jsonObject;
            jsonObject.set("size", size);
            return jsonObject;

        } catch (Poco::Exception &e) {
            log_error << "JSON Exception" << e.message();
            throw Core::JsonException(e.message());
        }
    }

    std::string EphemeralStorage::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const EphemeralStorage &m) {
        os << "EphemeralStorage=" << bsoncxx::to_json(m.ToDocument());
        return os;
    }
}// namespace AwsMock::Database::Entity::Lambda
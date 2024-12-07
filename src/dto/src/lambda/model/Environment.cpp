//
// Created by vogje01 on 21/06/2023.
//

#include "awsmock/dto/lambda/model/Environment.h"

#include <bsoncxx/builder/basic/helpers.hpp>
#include <bsoncxx/json.hpp>

namespace AwsMock::Dto::Lambda {

    view_or_value<view, value> EnvironmentVariables::ToDocument() const {

        try {

            bsoncxx::builder::basic::document document;
            if (!variables.empty()) {
                bsoncxx::builder::basic::document variablesDocument;
                for (const auto &[fst, snd]: variables) {
                    variablesDocument.append(kvp(fst, snd));
                }
                document.append(kvp("Variables", variablesDocument));
            }

            bsoncxx::builder::basic::document errorDocument;
            errorDocument.append(kvp("ErrorCode", error.errorCode));
            errorDocument.append(kvp("Message", error.message));
            document.append(kvp("Error", errorDocument));

            return document.extract();

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::ServiceException(exc.what());
        }
    }

    void EnvironmentVariables::FromJson(Poco::JSON::Object::Ptr object) {

        try {

            Poco::JSON::Object::Ptr varObject = object->getObject("Variables");
            for (Poco::JSON::Object::NameList nameList = varObject->getNames(); const auto &name: nameList) {
                variables[name] = varObject->get(name).convert<std::string>();
            }

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
    }

    std::string EnvironmentVariables::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const EnvironmentVariables &r) {
        os << "EnvironmentVariables=" << to_json(r.ToDocument());
        return os;
    }

}// namespace AwsMock::Dto::Lambda

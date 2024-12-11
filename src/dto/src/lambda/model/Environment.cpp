//
// Created by vogje01 on 21/06/2023.
//

#include <awsmock/dto/lambda/model/Environment.h>

namespace AwsMock::Dto::Lambda {

    view_or_value<view, value> EnvironmentVariables::ToDocument() const {

        try {

            document document;
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

    void EnvironmentVariables::FromDocument(const view_or_value<view, value> &document) {

        try {
            if (document.view().find("Variables") != document.view().end()) {
                for (const bsoncxx::array::view jsonArray = document.view()["Variables"].get_array().value; const auto &element: jsonArray) {
                    std::string key = bsoncxx::string::to_string(element.key());
                    const std::string value = bsoncxx::string::to_string(element[key].get_string().value);
                    variables[key] = value;
                }
            }
        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::ServiceException(exc.what());
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

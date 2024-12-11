//
// Created by vogje01 on 22/08/2022.
//

#ifndef AWSMOCK_CORE_XML_UTILS_H
#define AWSMOCK_CORE_XML_UTILS_H

// Standard C++ includes
#include <string>

// Boost includes
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace AwsMock::Core {

    /**
     * @brief XML utilities.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class XmlUtils {

      public:

        /**
         * @brief Returns the XML string for the document.
         *
         * @param rootTree property tree
         * @return XML string
         */
        static std::string ToXmlString(const boost::property_tree::ptree &rootTree);
    };

}// namespace AwsMock::Core

#endif// AWSMOCK_CORE_XML_UTILS_H

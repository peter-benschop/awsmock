//
// Created by vogje01 on 22/08/2022.
//

#ifndef AWSMOCK_CORE_XML_UTILS_H
#define AWSMOCK_CORE_XML_UTILS_H

// Standard C++ includes
#include <sstream>
#include <string>

// Poco includes
#include <Poco/DOM/AutoPtr.h>
#include <Poco/DOM/DOMParser.h>
#include <Poco/DOM/DOMWriter.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/Element.h>
#include <Poco/DOM/NodeList.h>
#include <Poco/DOM/Text.h>
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/XML/XMLWriter.h>

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
         * @brief Creates a new XML document
         *
         * @return XML document pointer
         */
        static Poco::XML::AutoPtr<Poco::XML::Document> CreateDocument();

        /**
         * @brief Create root node.
         *
         * @param document XML document
         * @param name root node name
         */
        static Poco::XML::AutoPtr<Poco::XML::Element> CreateRootNode(Poco::XML::AutoPtr<Poco::XML::Document> &document, const std::string &name);

        /**
         * @brief Create node.
         *
         * @param document XML document
         * @param parent XML node parent
         * @param name root node name
         */
        static Poco::XML::AutoPtr<Poco::XML::Element> CreateNode(Poco::XML::AutoPtr<Poco::XML::Document> &document, Poco::XML::AutoPtr<Poco::XML::Element> &parent, const std::string &name);

        /**
         * @brief Creates a new text node, from a string value.
         *
         * @code{.xml}
         * <parent>
         *   <name>value</name>
         * </parent>
         * @endcode
         *
         * @param document XML document
         * @param parent parent node
         * @param name node
         * @param value node value
         */
        static void CreateTextNode(const Poco::XML::AutoPtr<Poco::XML::Document> &document, Poco::XML::AutoPtr<Poco::XML::Element> &parent, const std::string &name, const std::string &value);

        /**
         * @brief Creates a new text node from a integer value.
         *
         * @code{.xml}
         * <parent>
         *   <name>value</name>
         * </parent>
         * @endcode
         *
         * @param document XML document
         * @param parent parent node
         * @param name node
         * @param value node value
         */
        static void CreateTextNode(const Poco::XML::AutoPtr<Poco::XML::Document> &document, Poco::XML::AutoPtr<Poco::XML::Element> &parent, const std::string &name, int value);

        /**
         * @brief Creates a new text node from a long integer value.
         *
         * @code{.xml}
         * <parent>
         *   <name>value</name>
         * </parent>
         * @endcode
         *
         * @param document XML document
         * @param parent parent node
         * @param name node
         * @param value node value
         */
        static void CreateTextNode(const Poco::XML::AutoPtr<Poco::XML::Document> &document, Poco::XML::AutoPtr<Poco::XML::Element> &parent, const std::string &name, long value);

        /**
         * @brief Creates a new text node from a date time value.
         *
         * <p>
         * The value will be formatted as a ISO-8601 datetime string
         * </p>
         *
         * @code{.xml}
         * <parent>
         *   <name>value</name>
         * </parent>
         * @endcode
         *
         * @param document XML document
         * @param parent parent node
         * @param name node
         * @param value node value
         */
        static void CreateTextNode(const Poco::XML::AutoPtr<Poco::XML::Document> &document, Poco::XML::AutoPtr<Poco::XML::Element> &parent, const std::string &name, const Poco::DateTime &value);

        /**
         * @brief Creates a new text node from a boolean value.
         *
         * @code{.xml}
         * <parent>
         *   <name>value</name>
         * </parent>
         * @endcode
         *
         * @param document XML document
         * @param parent parent node
         * @param name node name
         * @param value node value
         */
        static void CreateTextNode(const Poco::XML::AutoPtr<Poco::XML::Document> &document, Poco::XML::AutoPtr<Poco::XML::Element> &parent, const std::string &name, bool value);

        /**
         * @brief Creates a simple XML string array.
         *
         * Example:
         * @code{.xml}
         *  <parentName>
         *    <elementName>element</elementName>
         *     ....
         * </parentName>
         * @endcode
         *
         * @param document XML document
         * @param parent parent node
         * @param parentName parent node name
         * @param elementName element node name
         * @param elements vector of strings
         */
        static void CreateTextArray(const Poco::XML::AutoPtr<Poco::XML::Document> &document, Poco::XML::AutoPtr<Poco::XML::Element> &parent, const std::string &parentName, const std::string &elementName, const std::vector<std::string> &elements);

        /**
         * @brief Check existence of specific child node
         *
         * @param node XML node
         * @param name child name
         * @return true if child exists
         */
        static bool HasChild(const Poco::XML::AutoPtr<Poco::XML::Node> &node, const std::string &name);

        /**
         * @brief Returns the XML string for the document.
         *
         * @param document XML document
         * @return XML string
         */
        static std::string ToXmlString(const Poco::XML::AutoPtr<Poco::XML::Document> &document);

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

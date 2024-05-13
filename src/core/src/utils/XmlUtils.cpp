
#include <awsmock/core/XmlUtils.h>

namespace AwsMock::Core {

    Poco::XML::AutoPtr<Poco::XML::Document> XmlUtils::CreateDocument() {
        return new Poco::XML::Document;
    }

    Poco::XML::AutoPtr<Poco::XML::Element> XmlUtils::CreateRootNode(Poco::XML::AutoPtr<Poco::XML::Document> &document,
                                                                    const std::string &name) {
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = document->createElement(name);
        document->appendChild(pRoot);
        return pRoot;
    }

    Poco::XML::AutoPtr<Poco::XML::Element> XmlUtils::CreateNode(Poco::XML::AutoPtr<Poco::XML::Document> &document,
                                                                Poco::XML::AutoPtr<Poco::XML::Element> &parent,
                                                                const std::string &name) {
        Poco::XML::AutoPtr<Poco::XML::Element> pNode = document->createElement(name);
        parent->appendChild(pNode);
        return pNode;
    }

    void XmlUtils::CreateTextNode(const Poco::XML::AutoPtr<Poco::XML::Document> &document,
                                  Poco::XML::AutoPtr<Poco::XML::Element> &parent,
                                  const std::string &name,
                                  const std::string &value) {

        auto pElement = document->createElement(name);
        parent->appendChild(pElement);
        auto pElementText = document->createTextNode(value);
        pElement->appendChild(pElementText);
    }

    void XmlUtils::CreateTextNode(const Poco::XML::AutoPtr<Poco::XML::Document> &document,
                                  Poco::XML::AutoPtr<Poco::XML::Element> &parent,
                                  const std::string &name,
                                  int value) {

        auto pElement = document->createElement(name);
        parent->appendChild(pElement);
        auto pElementText = document->createTextNode(std::to_string(value));
        pElement->appendChild(pElementText);
    }

    void XmlUtils::CreateTextNode(const Poco::XML::AutoPtr<Poco::XML::Document> &document,
                                  Poco::XML::AutoPtr<Poco::XML::Element> &parent,
                                  const std::string &name,
                                  long value) {

        auto pElement = document->createElement(name);
        parent->appendChild(pElement);
        auto pElementText = document->createTextNode(std::to_string(value));
        pElement->appendChild(pElementText);
    }

    void XmlUtils::CreateTextNode(const Poco::XML::AutoPtr<Poco::XML::Document> &document,
                                  Poco::XML::AutoPtr<Poco::XML::Element> &parent,
                                  const std::string &name,
                                  const Poco::DateTime &value) {

        auto pElement = document->createElement(name);
        parent->appendChild(pElement);
        auto pElementText =
                document->createTextNode(Poco::DateTimeFormatter::format(value, Poco::DateTimeFormat::ISO8601_FORMAT));
        pElement->appendChild(pElementText);
    }

    void XmlUtils::CreateTextNode(const Poco::XML::AutoPtr<Poco::XML::Document> &document,
                                  Poco::XML::AutoPtr<Poco::XML::Element> &parent,
                                  const std::string &name,
                                  bool value) {

        auto pElement = document->createElement(name);
        parent->appendChild(pElement);
        auto pElementText = document->createTextNode(std::to_string(value));
        pElement->appendChild(pElementText);
    }

    void XmlUtils::CreateTextArray(const Poco::XML::AutoPtr<Poco::XML::Document> &document,
                                   Poco::XML::AutoPtr<Poco::XML::Element> &parent,
                                   const std::string &parentName,
                                   const std::string &elementName,
                                   const std::vector<std::string> &elements) {

        Poco::XML::AutoPtr<Poco::XML::Element> array;
        array = document->createElement(parentName);
        parent->appendChild(array);

        for (const auto &element: elements) {
            CreateTextNode(document, array, elementName, element);
        }
    }

    std::string XmlUtils::ToXmlString(const Poco::XML::AutoPtr<Poco::XML::Document> &document) {

        std::stringstream output;
        Poco::XML::DOMWriter writer;
        writer.setOptions(Poco::XML::XMLWriter::WRITE_XML_DECLARATION);
        writer.writeNode(output, document);
        return output.str();
    }

}// namespace AwsMock::Core
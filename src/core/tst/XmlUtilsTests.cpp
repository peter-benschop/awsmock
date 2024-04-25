//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_CORE_XML_UTILS_TEST_H
#define AWMOCK_CORE_XML_UTILS_TEST_H

// GTest includes
#include <gtest/gtest.h>

// Poco includes
#include <Poco/DOM/DOMWriter.h>
#include <Poco/DOM/Document.h>
#include <Poco/Path.h>

// Local includes
#include <awsmock/core/XmlUtils.h>

namespace AwsMock::Core {

    class XmlUtilsTest : public ::testing::Test {};

    TEST_F(XmlUtilsTest, CreateTextNodeTest) {

        // arrange
        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("Root");
        pDoc->appendChild(pRoot);

        // act
        XmlUtils::CreateTextNode(pDoc, pRoot, "Test", "TestValue");
        std::string result = XmlUtils::ToXmlString(pDoc);

        // assert
        EXPECT_TRUE(result == "<?xml version=\"1.0\" encoding=\"UTF-8\"?><Root><Test>TestValue</Test></Root>");
    }

    TEST_F(XmlUtilsTest, CreateTextArrayTest) {

        // arrange
        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("Root");
        pDoc->appendChild(pRoot);
        std::vector<std::string> values = {"Value1", "Value2", "Value3"};

        // act
        XmlUtils::CreateTextArray(pDoc, pRoot, "Test", "TestValue", values);
        std::string result = XmlUtils::ToXmlString(pDoc);

        // assert
        EXPECT_TRUE(result == "<?xml version=\"1.0\" encoding=\"UTF-8\"?><Root><Test><TestValue>Value1</TestValue><TestValue>Value2</TestValue><TestValue>Value3</TestValue></Test></Root>");
    }

}// namespace AwsMock::Core

#endif// AWMOCK_CORE_XML_UTILS_TEST_H
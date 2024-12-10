
#include <awsmock/core/XmlUtils.h>

namespace AwsMock::Core {

    std::string XmlUtils::ToXmlString(const boost::property_tree::ptree &rootTree) {
        std::stringstream os;
        write_xml(os, rootTree);
        return os.str();
    }

}// namespace AwsMock::Core
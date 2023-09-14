//
// Created by vogje01 on 05/01/2023.
//

#include <awsmock/core/JsonLogFormatter.h>

namespace AwsMock::Core {

    const Poco::Net::HostEntry &hostEntry = Poco::Net::DNS::thisHost();

    JsonLogFormatter::JsonLogFormatter() = default;

    JsonLogFormatter::~JsonLogFormatter() = default;

    void JsonLogFormatter::format(const Poco::Message &msg, std::string &text) {

        Poco::JSON::Object jsonMessage;

        jsonMessage.set("level", priorityToString(msg.getPriority()));
        jsonMessage.set("timestamp", msg.getTime());
        jsonMessage.set("date", Poco::DateTime(msg.getTime()));
        jsonMessage.set("classname", msg.getSource());
        jsonMessage.set("filename", msg.getSourceFile() != nullptr ? getFilename(msg.getSourceFile()) : "null");
        jsonMessage.set("linenumber", msg.getSourceLine());
        jsonMessage.set("message", msg.getText());
        jsonMessage.set("methodname", msg.getSource());
        jsonMessage.set("hostname", hostEntry.name());
        jsonMessage.set("username", "root");
        jsonMessage.set("pid", msg.getPid());
        jsonMessage.set("tid", msg.getTid());
        jsonMessage.set("thread", msg.getThread());

        for (auto const &[key, val]: _properties) {
            jsonMessage.set(key, val);
        }

        std::ostringstream os;
        jsonMessage.stringify(os);
        text = os.str();
    }

    void JsonLogFormatter::setProperty(const std::string &name, const std::string &value) {
        _properties[name] = value;
    }

    std::string JsonLogFormatter::getProperty(const std::string &name) const {
        for (const auto &[key, value]: _properties) {
            if (key == name) {
                return value;
            }
        }
        return "";
    }

    /**
     * Convert log priority enum to string
     *
     * @param p logging priority
     * @return string representation
     */
    std::string JsonLogFormatter::priorityToString(Poco::Message::Priority p) {
        switch (p) {
            case Poco::Message::Priority::PRIO_FATAL:
                return PRIORITY_STR_FATAL;
            case Poco::Message::Priority::PRIO_CRITICAL:
                return PRIORITY_STR_CRITIAL;
            case Poco::Message::Priority::PRIO_ERROR:
                return PRIORITY_STR_ERROR;
            case Poco::Message::Priority::PRIO_WARNING:
                return PRIORITY_STR_WARNING;
            case Poco::Message::Priority::PRIO_NOTICE:
                return PRIORITY_STR_NOTICE;
            case Poco::Message::Priority::PRIO_INFORMATION:
                return PRIORITY_STR_INFORMATION;
            case Poco::Message::Priority::PRIO_DEBUG:
                return PRIORITY_STR_DEBUG;
            case Poco::Message::Priority::PRIO_TRACE:
                return PRIORITY_STR_TRACE;
            default:
                return PRIORITY_STR_NOTICE;
        }
    }

    std::string JsonLogFormatter::getFilename(const std::string &filename) {
        return filename.find_last_of("src") != filename.npos ? filename.substr(filename.find("src") + 4) : filename;
    }
}
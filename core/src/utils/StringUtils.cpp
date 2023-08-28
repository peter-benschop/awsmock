
#include "awsmock/core/StringUtils.h"

static const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

namespace AwsMock::Core {

    template<typename T = std::mt19937>
    auto RandomGenerator() -> T {
        auto constexpr seed_bytes = sizeof(typename T::result_type) * T::state_size;
        auto constexpr seed_len = seed_bytes / sizeof(std::seed_seq::result_type);
        auto seed = std::array<std::seed_seq::result_type, seed_len>();
        auto dev = std::random_device();
        std::generate_n(begin(seed), seed_len, std::ref(dev));
        auto seed_seq = std::seed_seq(begin(seed), end(seed));
        return T{seed_seq};
    }

    auto randomString(std::size_t len) -> std::string {
        static constexpr auto chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        thread_local auto rng = RandomGenerator<>();
        auto dist = std::uniform_int_distribution{{}, std::strlen(chars) - 1};
        auto result = std::string(len, '\0');
        std::generate_n(begin(result), len, [&]() { return chars[dist(rng)]; });
        return result;
    }

    std::string StringUtils::GenerateRandomString(int length) {
        return randomString(length);
    }

    auto randomHexString(std::size_t len) -> std::string {
        static constexpr auto chars = "0123456789abcdef";
        thread_local auto rng = RandomGenerator<>();
        auto dist = std::uniform_int_distribution{{}, std::strlen(chars) - 1};
        auto result = std::string(len, '\0');
        std::generate_n(begin(result), len, [&]() { return chars[dist(rng)]; });
        return result;
    }

    std::string StringUtils::GenerateRandomHexString(int length) {
        return randomHexString(length);
    }

    auto randomPasswordString(std::size_t len) -> std::string {
        static constexpr auto chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@$%&<>+";
        thread_local auto rng = RandomGenerator<>();
        auto dist = std::uniform_int_distribution{{}, std::strlen(chars) - 1};
        auto result = std::string(len, '\0');
        std::generate_n(begin(result), len, [&]() { return chars[dist(rng)]; });
        return result;
    }

    std::string StringUtils::GenerateRandomPassword(int length) {
        return randomPasswordString(length);
    }

    bool StringUtils::IsNumeric(const std::string &value) {
        return !value.empty() && std::find_if(value.begin(), value.end(), [](unsigned char c) { return !std::isdigit(c); }) == value.end();
    }

    bool StringUtils::IsUuid(const std::string &value) {
        std::regex regex("[[:xdigit:]]{8}(-[[:xdigit:]]{4}){3}-[[:xdigit:]]{12}", std::regex_constants::icase);
        return std::regex_match(value, regex);
    }

    std::vector<std::string> StringUtils::Split(const std::string &s, char delimiter) {
        std::vector<std::string> elems;
        size_t pos_start = 0, pos_end;
        std::string token;
        while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
            token = s.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + 1;
            elems.push_back (token);
        }
        elems.push_back (s.substr (pos_start));
        return elems;
    }

    std::string StringUtils::StripWhiteSpaces(const std::string &str) {
        if (str.find_first_not_of(" \t\n\v\f\r") == std::string::npos) {
            return "";
        }
        return str;
    }

    bool StringUtils::Equals(const std::string &s1, const std::string &s2) {
        if (s1.empty() || s2.empty()) {
            return false;
        }
        return s1.compare(s2) == 0;
    }

    bool StringUtils::EqualsIgnoreCase(const std::string &s1, const std::string &s2) {
        return Poco::icompare(s1, s2) == 0;
    }

    bool StringUtils::IsNullOrEmpty(const std::string *s1) {
        return s1 == nullptr || s1->empty();
    }

    bool StringUtils::Contains(const std::string &s1, const std::string &s2) {
        return s1.find(s2) != std::string::npos;
    }

    bool StringUtils::ContainsIgnoreCase(const std::string &s1, const std::string &s2) {
        return Poco::toLower(s1).find(Poco::toLower(s2)) != std::string::npos;
    }

    bool StringUtils::StartsWith(const std::string &s1, const std::string &s2) {
        return s1.rfind(s2, 0) == 0;
    }

    std::string StringUtils::SubString(const std::string &string, int beginIndex, int endIndex) {
        int size = (int) string.size();
        if (beginIndex < 0 || beginIndex > size - 1)
            return "-1"; // Index out of bounds
        if (endIndex < 0 || endIndex > size - 1)
            return "-1"; // Index out of bounds
        if (beginIndex > endIndex)
            return "-1"; // Begin index should not be bigger that end.

        std::string substr;
        for (int i = 0; i < size; i++)
            if (i >= beginIndex && i <= endIndex)
                substr += (char) string[i];
        return substr;
    }

    std::string StringUtils::UrlEncode(const std::string &input) {
        std::string encoded;
        Poco::URI::encode(input, "!*'();:@&=+$,?#[] ", encoded);
        return encoded;
    }

    std::string StringUtils::UrlDecode(const std::string &input) {
        std::string decoded;
        Poco::URI::decode(input, decoded, true);
        return Poco::replace(decoded, '+', ' ');
    }

    std::string StringUtils::ToHexString(unsigned char *input, size_t length) {
        std::stringstream ss;
        for (size_t i = 0; i < length; i++) {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(input[i]);
        }
        return ss.str();
    }
}
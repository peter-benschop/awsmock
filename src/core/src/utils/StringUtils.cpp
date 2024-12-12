
#include <awsmock/core/StringUtils.h>
#include <boost/bind/bind.hpp>
#include <jwt-cpp/base.h>

namespace AwsMock::Core {

    /* Converts a hex character to its integer value */
    char from_hex(const char ch) {
        return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
    }

    /* Converts an integer value to its hex character*/
    char to_hex(const char code) {
        static char hex[] = "0123456789abcdef";
        return hex[code & 15];
    }

    /* Returns a url-encoded version of str */
    /* IMPORTANT: be sure to free() the returned string after use */
    char *url_encode(char *str) {
        char *pstr = str, *buf = static_cast<char *>(malloc(strlen(str) * 3 + 1)), *pbuf = buf;
        while (*pstr) {
            if (isalnum(*pstr) || *pstr == '-' || *pstr == '_' || *pstr == '.' || *pstr == '~')
                *pbuf++ = *pstr;
            else if (*pstr == ' ')
                *pbuf++ = '+';
            else
                *pbuf++ = '%', *pbuf++ = to_hex(*pstr >> 4), *pbuf++ = to_hex(*pstr & 15);
            pstr++;
        }
        *pbuf = '\0';
        return buf;
    }

    /* Returns a url-decoded version of str */
    /* IMPORTANT: be sure to free() the returned string after use */
    char *url_decode(char *str) {
        char *pstr = str, *buf = static_cast<char *>(malloc(strlen(str) + 1)), *pbuf = buf;
        while (*pstr) {
            if (*pstr == '%') {
                if (pstr[1] && pstr[2]) {
                    *pbuf++ = from_hex(pstr[1]) << 4 | from_hex(pstr[2]);
                    pstr += 2;
                }
            } else if (*pstr == '+') {
                *pbuf++ = ' ';
            } else {
                *pbuf++ = *pstr;
            }
            pstr++;
        }
        *pbuf = '\0';
        return buf;
    }

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

    auto randomString(const std::size_t len) -> std::string {
        static constexpr auto chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        thread_local auto rng = RandomGenerator<>();
        auto dist = std::uniform_int_distribution{{}, std::strlen(chars) - 1};
        auto result = std::string(len, '\0');
        std::generate_n(begin(result), len, [&]() { return chars[dist(rng)]; });
        return result;
    }

    std::string StringUtils::GenerateRandomString(const int length) {
        return randomString(length);
    }

    std::string StringUtils::GenerateRandomAlphanumericString(const int length) {
        return ToLower(randomString(length));
    }

    auto randomHexString(const std::size_t len) -> std::string {
        static constexpr auto chars = "0123456789abcdef";
        thread_local auto rng = RandomGenerator<>();
        auto dist = std::uniform_int_distribution{{}, std::strlen(chars) - 1};
        auto result = std::string(len, '\0');
        std::generate_n(begin(result), len, [&]() { return chars[dist(rng)]; });
        return result;
    }

    std::string StringUtils::GenerateRandomHexString(const int length) {
        return randomHexString(length);
    }

    auto randomPasswordString(const std::size_t len) -> std::string {
        static constexpr auto chars = R"(0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~)";
        thread_local auto rng = RandomGenerator<>();
        auto dist = std::uniform_int_distribution{{}, std::strlen(chars) - 1};
        auto result = std::string(len, '\0');
        std::generate_n(begin(result), len, [&]() { return chars[dist(rng)]; });
        return result;
    }

    std::string StringUtils::GenerateRandomPassword(const int length) {
        return randomPasswordString(length);
    }

    auto randomVersionString(const std::size_t len) -> std::string {
        static constexpr auto chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        thread_local auto rng = RandomGenerator<>();
        auto dist = std::uniform_int_distribution{{}, std::strlen(chars) - 1};
        auto result = std::string(len, '\0');
        std::generate_n(begin(result), len, [&]() { return chars[dist(rng)]; });
        return result;
    }

    std::string StringUtils::GenerateRandomVersion(const int length) {
        return randomVersionString(length);
    }

    bool StringUtils::IsNumeric(const std::string &value) {
        return !value.empty() && std::ranges::find_if(value, [](unsigned char c) { return !std::isdigit(c); }) == value.end();
    }

    bool StringUtils::IsUuid(const std::string &value) {
        const std::regex regex("[[:xdigit:]]{8}(-[[:xdigit:]]{4}){3}-[[:xdigit:]]{12}", std::regex_constants::icase);
        return std::regex_match(value, regex);
    }

    std::string StringUtils::CreateRandomUuid() {
        return to_string(boost::uuids::random_generator()());
    }

    std::vector<std::string> StringUtils::Split(const std::string &s, char delimiter) {
        std::vector<std::string> tokens;
        std::stringstream check1(s);
        std::string intermediate;
        while (getline(check1, intermediate, delimiter)) {
            tokens.push_back(intermediate);
        }
        return tokens;
    }

    std::string StringUtils::Join(const std::vector<std::string> &vec, const int startIndex) {
        std::string result;
        for (int i = startIndex; i < vec.size(); i++) {
            result += vec[i];
            if (i != vec.size() - 1) {
                result += "/";
            }
        }
        return result;
    }

    std::string StringUtils::StripWhiteSpaces(std::string &str) {
        const std::string &chars = "\t\n\r\v\f ";
        str.erase(std::ranges::remove_if(str, [&chars](const char &c) {
                      return chars.find(c) != std::string::npos;
                  }).begin(),
                  str.end());
        return str;
    }

    std::string StringUtils::StripLineEndings(std::basic_string<char> str) {
        const std::string &chars = "\n\r";
        str.erase(std::ranges::remove_if(str, [&chars](const char &c) {
                      return chars.find(c) != std::string::npos;
                  }).begin(),
                  str.end());
        return str;
    }

    std::string StringUtils::StripBeginning(const std::string &s1, const std::string &s2) {
        return s1.substr(s2.length());
    }

    bool StringUtils::Equals(const std::string &s1, const std::string &s2) {
        if (s1.empty() || s2.empty()) {
            return false;
        }
        return s1 == s2;
    }

    bool StringUtils::EqualsIgnoreCase(const std::string &s1, const std::string &s2) {
        return boost::beast::iequals(s1, s2);
    }

    bool StringUtils::IsNullOrEmpty(const std::string *s1) {
        return s1 == nullptr || s1->empty();
    }

    bool StringUtils::Contains(const std::string &s1, const std::string &s2) {
        return s1.find(s2) != std::string::npos;
    }

    bool StringUtils::ContainsIgnoreCase(const std::string &s1, const std::string &s2) {
        return boost::algorithm::to_lower_copy(s1).find(ToLower(s2)) != std::string::npos;
    }

    bool StringUtils::StartsWith(const std::string &s1, const std::string &s2) {
        return s1.starts_with(s2);
    }

    bool StringUtils::StartsWithIgnoringCase(const std::string &s1, const std::string &s2) {
        return boost::algorithm::to_lower_copy(s1).starts_with(boost::algorithm::to_lower_copy(s2));
    }

    bool StringUtils::EndsWith(const std::string &s1, const std::string &s2) {
        return s1.ends_with(s2);
    }

    std::string StringUtils::SubString(const std::string &string, const int beginIndex, const int endIndex) {
        const int size = static_cast<int>(string.size());
        if (beginIndex < 0 || beginIndex > size - 1)
            return "-1";// Index out of bounds
        if (endIndex < 0 || endIndex > size - 1)
            return "-1";// Index out of bounds
        if (beginIndex > endIndex)
            return "-1";// Begin index should not be bigger that end.

        std::string substr;
        for (int i = 0; i < size; i++)
            if (i >= beginIndex && i <= endIndex)
                substr += (char) string[i];
        return substr;
    }

    std::string StringUtils::SubStringUntil(const std::string &string, const std::string &delimiter) {
        if (Contains(string, delimiter)) {
            return string.substr(0, string.find(delimiter));
        }
        return string;
    }

    std::string StringUtils::SubStringAfter(const std::string &string, const std::string &delimiter) {
        if (Contains(string, delimiter)) {
            return string.substr(string.find(delimiter) + 1);
        }
        return {};
    }

    std::string StringUtils::UrlEncode(const std::string &input) {
        std::ostringstream escaped;
        escaped.fill('0');
        escaped << std::hex;

        for (const char c: input) {
            // Keep alphanumeric and other accepted characters intact
            if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
                escaped << c;
                continue;
            }

            // Any other characters are percent-encoded
            escaped << std::uppercase;
            escaped << '%' << std::setw(2) << static_cast<int>(static_cast<unsigned char>(c));
            escaped << std::nouppercase;
        }

        return escaped.str();
    }

    char *StringUtils::Replace(const char *original, char const *const pattern, char const *const replacement) {
        size_t const replen = strlen(replacement);
        size_t const patlen = strlen(pattern);
        size_t const orilen = strlen(original);

        size_t patcnt = 0;
        const char *oriptr;

        // find how many times the pattern occurs in the original string
        const char *patloc = strstr(original, pattern);
        for (oriptr = original; patloc; oriptr = patloc + patlen) {
            patcnt++;
            patloc = strstr(oriptr, pattern);
        }
        {
            // allocate memory for the new string
            size_t const retlen = orilen + patcnt * (replen - patlen);
            const auto returned = static_cast<char *>(malloc(sizeof(char) * (retlen + 1)));

            if (returned != nullptr) {

                // copy the original string,
                // replacing all the instances of the pattern
                char *retptr = returned;
                for (oriptr = original; patloc = strstr(oriptr, pattern); oriptr = patloc + patlen) {

                    size_t const skplen = patloc - oriptr;
                    // copy the section until the occurrence of the pattern
                    strncpy(retptr, oriptr, skplen);
                    retptr += skplen;
                    // copy the replacement
                    strncpy(retptr, replacement, replen);
                    retptr += replen;
                }
                // copy the rest of the string.
                strcpy(retptr, oriptr);
            }
            return returned;
        }
    }

    std::string StringUtils::UrlDecode(const std::string &input) {
        return boost::to_string(boost::urls::decode_view(input));
    }

    std::string StringUtils::Quoted(const std::string &input) {
        std::stringstream escaped;
        escaped << std::quoted(input);
        return escaped.str();
    }

    std::string StringUtils::ToHexString(const unsigned char *input, const size_t length) {
        std::stringstream ss;
        for (size_t i = 0; i < length; i++) {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(input[i]);
        }
        return ss.str();
    }

    std::string StringUtils::ToString(const bool value) {
        return value ? "true" : "false";
    }

    std::string StringUtils::StripChunkSignature(const std::string &input) {
        const std::regex regex("(^|\r\n)[0-9a-fA-F]+;chunk-signature=[0-9a-f]{64}(\r\n)(\r\n$)?", std::regex_constants::icase);
        return std::regex_replace(input, regex, "");
    }

    std::string StringUtils::ToSnakeCase(const std::string &in) {

        // Empty result string
        std::string result;

        // Append first character(in lower case) to result string
        const char c = static_cast<char>(tolower(in[0]));
        result += c;

        // Traverse the string from first index to last index
        for (int i = 1; i < in.length(); i++) {

            // Check if the character is upper case then append '-' and such character (in lower case) to result string
            if (const char ch = in[i]; isupper(ch)) {
                result += '-';
                result += char(tolower(ch));
            } else {
                // If the character is lower case then add such character into result string
                result += ch;
            }
        }

        // Return the result
        return result;
    }
}// namespace AwsMock::Core
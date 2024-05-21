//
// Created by vogje01 on 22/08/2022.
//

#ifndef AWSMOCK_CORE_STRING_UTILS_H
#define AWSMOCK_CORE_STRING_UTILS_H

// C++ standard includes
#include <algorithm>
#include <array>
#include <iomanip>
#include <iterator>
#include <random>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

// Iconv includes
#ifndef _WIN32
#include <iconv.h>
#endif

// Poco includes
#include <Poco/RegularExpression.h>
#include <Poco/String.h>
#include <Poco/URI.h>

namespace AwsMock::Core {

    /**
     * String utilities.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class StringUtils {

      public:

        /**
         * Generates a random string with the given length.
         *
         * @param length length of the string
         * @return generated random string with the given length.
         */
        static std::string GenerateRandomString(int length);

        /**
         * Generates a random hexadecimal string with the given length.
         *
         * @param length length of the string
         * @return generated random hexadecimal string with the given length.
         */
        static std::string GenerateRandomHexString(int length);

        /**
         * Generates a random password string with the given length.
         *
         * @param length length of the string
         * @return generated random password string with the given length.
         */
        static std::string GenerateRandomPassword(int length);

        /**
         * Generates a random version string with the given length.
         *
         * @param length length of the string
         * @return generated random password string with the given length.
         */
        static std::string GenerateRandomVersion(int length);

        /**
         * Check whether the provided string is a number.
         *
         * @param value string value
         * @return true in case the provided string is numeric, otherwise false.
         */
        static bool IsNumeric(const std::string &value);

        /**
         * Check whether the provided string is a UUID.
         *
         * @param value string value
         * @return true in case the provided string is a UUID, otherwise false.
         */
        static bool IsUuid(const std::string &value);

        /**
         * Splits a string into pieces using the provided delimiter char.
         *
         * @param s string to split
         * @param delim delimiter
         * @return vector os strings.
         */
        static std::vector<std::string> Split(const std::string &s, char delim);

        /**
         * Joins a string array to a string using the given delimiter.
         *
         * @param vec vector of strings
         * @param delimiter delimiter character
         * @param startIndex starting index default = 0
         * @return joined string
         */
        static std::string Join(const std::vector<std::string> &vec, char delimiter, int startIndex = 0);

        /**
         * Strip whitespaces
         *
         * @param s string to split
         * @return string having all whitespaces removed
         */
        static std::string StripWhiteSpaces(std::string &s);

        /**
         * Strip line endings
         *
         * @param s string to split
         * @return string having all line endings removed
         */
        static std::string StripLineEndings(std::basic_string<char, std::char_traits<char>, std::allocator<char>> s);

        /**
         * Strip beginning of string
         *
         * @param s1 string to strip
         * @param s2 substring to strip
         * @return string with beginning
         */
        static std::string StripBeginning(const std::string &s1, const std::string &s2);

        /**
         * Return true if s1 and s2 are equal.
         *
         * @param s1 first input string
         * @param s2 second input string
         * @return true if s11 and s2 are equal
         */
        static bool Equals(const std::string &s1, const std::string &s2);

        /**
         * Return true if s1 and s2 are not case sensitive equal.
         *
         * @param s1 first input string
         * @param s2 second input string
         * @return true if s11 and s2 are equal
         */
        static bool EqualsIgnoreCase(const std::string &s1, const std::string &s2);

        /**
         * Returns true in case the string is either null or empty
         *
         * @param s1 pointer to the string to check
         * @return true if the string is null or empty.
         */
        static bool IsNullOrEmpty(const std::string *s1);

        /**
         * Returns true in case the string s1 contains string s1
         *
         * @param s1 string to check
         * @param s2 probe string
         * @return true if the string s1 contains string s2.
         */
        static bool Contains(const std::string &s1, const std::string &s2);

        /**
         * Returns true in case the string s1 contains string s1, both string are compares case insensitive
         *
         * @param s1 string to check
         * @param s2 probe string
         * @return true if the string s1 contains string s2.
         */
        static bool ContainsIgnoreCase(const std::string &s1, const std::string &s2);

        /**
         * @brief Check whether the given string starts with the given prefix
         *
         * @param s1 string to check
         * @param s2 probe string
         * @return true if the string s1 starts with s2.
         */
        static bool StartsWith(const std::string &s1, const std::string &s2);

        /**
         * @brief Check whether the given string starts with the given prefix, ignoring the case
         *
         * Both string are converted to lowercase before compared.
         *
         * @param s1 string to check
         * @param s2 probe string
         * @return true if the string s1 starts with s2.
         */
        static bool StartsWithIgnoringCase(const std::string &s1, const std::string &s2);

        /**
         * @brief Check whether the given string StartServer with the given suffix
         *
         * @param s1 string to check
         * @param s2 probe string
         * @return true if the string s1 ends with s2.
         */
        static bool EndsWith(const std::string &s1, const std::string &s2);

        /**
         * @brief Returns a substring by index.
         *
         * @param string string to process
         * @param beginIndex begin index
         * @param endIndex end index
         * @return substring
         */
        static std::string SubString(const std::string &string, int beginIndex, int endIndex);

        /**
         * @brief Returns a substring by from 0 until a certain character.
         *
         * @param string string to process
         * @param delimiter delimiter character
         * @return substring
         */
        static std::string SubStringUntil(const std::string &string, const std::string &delimiter);

        /**
         * @brief Return the substring starting at delimiter.
         *
         * @param string string to test
         * @param delimiter delimiter
         * @return substring after delimiter
         */
        static std::string SubStringAfter(const std::string &string, const std::string &delimiter);

        /**
         * @brief Replace in C-string.
         *
         * @param original original
         * @param pattern pattern
         * @param replacement replacement string
         * @return
         */
        static char *Replace(char const *original, char const *pattern, char const *replacement);

        /**
         * @brief Left trim a string.
         *
         * @param s input string
         * @return trimmed string
         */
        static inline std::string Ltrim(std::string s) {
            s.erase(s.find_last_not_of(' ') + 1);
            return s;
        }

        /**
         * @brief Right trim a string.
         *
         * @param s input string
         * @return trimmed string
         */
        static inline std::string Rtrim(std::string s) {
            s.erase(0, s.find_first_not_of(' '));
            return s;
        }

        /**
         * @brief Trim a string.
         *
         * @param s input string
         * @return trimmed string
         */
        static inline std::string Trim(std::basic_string<char> s) {
            s = Rtrim(s);
            s = Ltrim(s);
            return s;
        }

        /**
         * @brief Returns the string in URL encoding format.
         *
         * @param input input string
         * @return URL encoded string.
         */
        static std::string UrlEncode(const std::string &input);

        /**
         * @brief Returns a decoded string as plain text.
         *
         * @param input input string
         * @return URL decoded string.
         */
        static std::string UrlDecode(const std::string &input);

        /**
         * @brief Returns a escaped string.
         *
         * @param input input string
         * @return escaped string.
         */
        static std::string Quoted(const std::string &input);

        /**
         * @brief Convert the given string to a hex encoded string.
         *
         * @param input input byte array
         * @param length length of the byte array
         * @return hex encoded string
         */
        static std::string ToHexString(unsigned char *input, size_t length);

        /**
         * @brief Sanitizes the string and removes Convert the given string to a hex encoded string.
         *
         * @param input input byte array
         * @return hex encoded string
         */
        static std::string SanitizeUtf8(std::string &input);

        /**
         * @brief Strip any chunk signatures from the input string
         *
         * @param input input string
         * @return stripped input string
         */
        static std::string StripChunkSignature(std::string &input);

        /**
         * @brief Converts a bool variable to a string.
         *
         * @param value bool value
         * @return string representation
         */
        static std::string ToString(bool value);

        /**
         * @brief Convert the string to snake case
         *
         * @param in in string
         * @return string in snake case
         */
        static std::string ToSnakeCase(const std::string &in);
    };

}// namespace AwsMock::Core

#endif// AWSMOCK_CORE_STRING_UTILS_H

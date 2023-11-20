//
// Created by vogje01 on 30/10/2023.
//

#ifndef AWSMOCK_CORE_NUMBERUTILS_H
#define AWSMOCK_CORE_NUMBERUTILS_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/String.h>

namespace AwsMock::Core {

  /**
   * Number utilities.
   *
   * @author jens.vogt@opitz-consulting.com
   */
  class NumberUtils {

  public:

    /**
     * Return a string with the value in kilobytes.
     *
     * @param value value to print
     * @return value string
     */
    static std::string ToKilobytesStr(long value);

    /**
     * Converts the given number to kilobytes.
     *
     * @param value value to convert
     * @return value in kilobytes
     */
    static long ToKilobytes(long value);

    /**
     * Return a string with the value in megabytes.
     *
     * @param value value to print
     * @return value string
     */
    static std::string ToMegabytesStr(long value);

    /**
     * Converts the given number to megabytes.
     *
     * @param value value to convert
     * @return value in kilobytes
     */
    static long ToMegabytes(long value);

    /**
     * Returns a byte array from an integer
     *
     * @param n integer value
     * @param bytes output bytes
     * @param offset offset
     */
    static void GetIntAsByteArray(int n, unsigned char *bytes, int offset);
  };

} // namespace AwsMock::Core

#endif // AWSMOCK_CORE_NUMBERUTILS_H

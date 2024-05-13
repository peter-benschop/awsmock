//
// Created by vogje01 on 05/05/2024.
//

#ifndef AWSMOCK_CORE_WIN32_UTILS_H
#define AWSMOCK_CORE_WIN32_UTILS_H

#ifdef _WIN32

// C++ includes
#include <string>

#define WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h> // IWYU pragma: keep

namespace AwsMock::Core {

    std::string WideToAnsi(const std::wstring& wstr);

    std::wstring AnsiToWide(const std::string& str);

    std::string WideToUtf8(const std::wstring& wstr);

    std::wstring Utf8ToWide(const std::string& str);

    std::string AnsiToUtf8(const std::string& str);

    std::string Utf8ToAnsi(const std::string& str);

}// namespace AwsMock::Core

#endif// _WIN32

#endif//AWSMOCK_CORE_WIN32UTILS_H

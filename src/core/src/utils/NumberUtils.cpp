//
//
//

#include <awsmock/core/NumberUtils.h>

namespace AwsMock::Core {

  std::string NumberUtils::ToKilobytesStr(long value) {
    return std::to_string(ToKilobytes(value)) + "k";
  }

  long NumberUtils::ToKilobytes(long value) {
    return value / 1024;
  }

  std::string NumberUtils::ToMegabytesStr(long value) {
    return std::to_string(ToMegabytes(value)) + "m";
  }

  long NumberUtils::ToMegabytes(long value) {
    return value / 1024 / 1024;
  }

}
#include "awsmock/resource/HandlerException.h"

namespace AwsMock {

  HandlerException::HandlerException(std::string type, std::string message, int statusCode) : _statusCode(statusCode), _type(std::move(type)), _message(std::move(message)) {}

  int HandlerException::code() const {
    return _statusCode;
  }

  std::string HandlerException::type() const {
    return _type;
  }

  std::string HandlerException::message() const {
    return _message;
  }
}

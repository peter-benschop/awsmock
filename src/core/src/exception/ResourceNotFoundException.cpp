//
// Created by vogje01 on 02/09/2022.
//

#include <awsmock/core/ResourceNotFoundException.h>

namespace AwsMock::Core {

  ResourceNotFoundException::ResourceNotFoundException(int code) : Poco::Exception(code) {
  }

  ResourceNotFoundException::ResourceNotFoundException(const std::string &msg, int code) : Poco::Exception(msg, code) {
  }

  ResourceNotFoundException::ResourceNotFoundException(const std::string &msg, const std::string &arg, int code) : Poco::Exception(msg, arg, code) {
  }

  ResourceNotFoundException::ResourceNotFoundException(const std::string &msg, const Poco::Exception &exc, int code) : Poco::Exception(msg, exc, code) {
  }

  ResourceNotFoundException::ResourceNotFoundException(const ResourceNotFoundException &exc) = default;

  ResourceNotFoundException::~ResourceNotFoundException() noexcept = default;

  ResourceNotFoundException &ResourceNotFoundException::operator=(const ResourceNotFoundException &exc) {
    Poco::Exception::operator=(exc);
    return *this;
  }

  const char *ResourceNotFoundException::name() const noexcept { return "ResourceNotFoundException: "; }

  const char *ResourceNotFoundException::className() const noexcept { return typeid(*this).name(); }

  Poco::Exception *ResourceNotFoundException::clone() const { return new ResourceNotFoundException(*this); }

  void ResourceNotFoundException::rethrow() const { throw *this; }

} // namespace AwsMock::Core
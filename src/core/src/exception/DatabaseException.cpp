//
// Created by vogje01 on 02/09/2022.
//

#include "awsmock/core/DatabaseException.h"

namespace AwsMock::Core {

  DatabaseException::DatabaseException(int code) : Poco::Exception(code) {}

  DatabaseException::DatabaseException(const std::string &msg, int code) : Poco::Exception(msg, code) {}

  DatabaseException::DatabaseException(const std::string &msg, const std::string &arg, int code) : Poco::Exception(msg, arg, code) {}

  DatabaseException::DatabaseException(const std::string &msg, const Poco::Exception &exc, int code) : Poco::Exception(msg, exc, code) {}

  DatabaseException::DatabaseException(const DatabaseException &exc) = default;

  DatabaseException::~DatabaseException() noexcept = default;

  DatabaseException &DatabaseException::operator=(const DatabaseException &exc) = default;

  const char *DatabaseException::name() const noexcept { return "ServiceException: "; }

  const char *DatabaseException::className() const noexcept { return typeid(*this).name(); }

  Poco::Exception *DatabaseException::clone() const { return new DatabaseException(*this); }

  void DatabaseException::rethrow() const { throw *this; }

} // namespace AwsMock::Core
//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/common/AbstractServer.h>

namespace AwsMock::Service {

    AbstractServer::AbstractServer(std::string name, int timeout) : Timer(name, timeout), _moduleDatabase(Database::ModuleDatabase::instance()), _name(std::move(name)) {
    }

    AbstractServer::AbstractServer(std::string name) : Timer(name), _moduleDatabase(Database::ModuleDatabase::instance()), _name(std::move(name)) {
    }

    bool AbstractServer::IsActive(const std::string &name) {
        return _moduleDatabase.IsActive(name);
    }

    void AbstractServer::SetRunning() {
        _moduleDatabase.SetState(_name, Database::Entity::Module::ModuleState::RUNNING);
    }

}// namespace AwsMock::Service

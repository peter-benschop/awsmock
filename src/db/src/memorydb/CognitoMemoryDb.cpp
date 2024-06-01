//
// Created by vogje01 on 11/19/23.
//

#include <awsmock/memorydb/CognitoMemoryDb.h>

namespace AwsMock::Database {

    Poco::Mutex CognitoMemoryDb::_userPoolMutex;
    Poco::Mutex CognitoMemoryDb::_userMutex;
    Poco::Mutex CognitoMemoryDb::_groupMutex;

    bool CognitoMemoryDb::UserPoolExists(const std::string &region, const std::string &name) {

        return find_if(_userPools.begin(),
                       _userPools.end(),
                       [region, name](const std::pair<std::string, Entity::Cognito::UserPool> &userPool) {
                           return userPool.second.region == region && userPool.second.name == name;
                       }) != _userPools.end();
    }

    bool CognitoMemoryDb::UserPoolExists(const std::string &userPoolId) {

        return find_if(_userPools.begin(),
                       _userPools.end(),
                       [userPoolId](const std::pair<std::string, Entity::Cognito::UserPool> &userPool) {
                           return userPool.second.userPoolId == userPoolId;
                       }) != _userPools.end();
    }

    Entity::Cognito::UserPoolList CognitoMemoryDb::ListUserPools(const std::string &region) {

        Entity::Cognito::UserPoolList userPoolList;
        if (region.empty()) {
            for (const auto &userPool: _userPools) {
                userPoolList.emplace_back(userPool.second);
            }
        } else {
            for (const auto &userPool: _userPools) {
                if (userPool.second.region == region) {
                    userPoolList.emplace_back(userPool.second);
                }
            }
        }

        log_trace << "Got user pool list, size: " << userPoolList.size();
        return userPoolList;
    }

    Entity::Cognito::UserPool CognitoMemoryDb::CreateUserPool(const Entity::Cognito::UserPool &userPool) {
        Poco::ScopedLock lock(_userPoolMutex);

        std::string oid = Poco::UUIDGenerator().createRandom().toString();
        _userPools[oid] = userPool;
        log_trace << "Cognito user pool created, oid: " << oid;
        return GetUserPoolByOid(oid);
    }

    Entity::Cognito::UserPool CognitoMemoryDb::GetUserPoolByOid(const std::string &oid) {

        auto it = find_if(_userPools.begin(),
                          _userPools.end(),
                          [oid](const std::pair<std::string, Entity::Cognito::UserPool> &userPool) {
                              return userPool.first == oid;
                          });

        if (it == _userPools.end()) {
            log_error << "Get cognito user pool by oid failed, oid: " << oid;
            throw Core::DatabaseException("Get cognito user pool by oid failed, oid: " + oid);
        }

        it->second.oid = oid;
        return it->second;
    }

    Entity::Cognito::UserPool CognitoMemoryDb::GetUserPoolByUserPoolId(const std::string &userPoolId) {

        auto it = find_if(_userPools.begin(),
                          _userPools.end(),
                          [userPoolId](const std::pair<std::string, Entity::Cognito::UserPool> &userPool) {
                              return userPool.second.userPoolId == userPoolId;
                          });

        if (it == _userPools.end()) {
            log_error << "Get cognito user pool by userPoolId failed, region: " << userPoolId;
            throw Core::DatabaseException("Get cognito user pool by userPoolId failed, userPoolId: " + userPoolId);
        }

        it->second.oid = it->first;
        return it->second;
    }

    Entity::Cognito::UserPool CognitoMemoryDb::GetUserPoolByRegionName(const std::string &region, const std::string &name) {

        auto it = find_if(_userPools.begin(),
                          _userPools.end(),
                          [region, name](const std::pair<std::string, Entity::Cognito::UserPool> &userPool) {
                              return userPool.second.region == region && userPool.second.name == name;
                          });

        if (it == _userPools.end()) {
            log_error << "Get cognito user pool by region and name failed, region: " << region << " name: " << name;
            throw Core::DatabaseException("Get cognito user pool by region and name failed, region: " + region + " name: " + name);
        }

        it->second.oid = it->first;
        return it->second;
    }

    long CognitoMemoryDb::CountUserPools(const std::string &region) {
        long count = 0;
        if (region.empty()) {
            count = static_cast<long>(_userPools.size());
        } else {
            for (const auto &userPool: _userPools) {
                if (userPool.second.region == region) {
                    count++;
                }
            }
        }

        log_trace << "Count user pools, size: " << count;
        return count;
    }

    Entity::Cognito::UserPool CognitoMemoryDb::UpdateUserPool(const Entity::Cognito::UserPool &userPool) {

        Poco::ScopedLock lock(_userPoolMutex);

        std::string region = userPool.region;
        std::string name = userPool.name;
        auto it = find_if(_userPools.begin(),
                          _userPools.end(),
                          [region, name](const std::pair<std::string, Entity::Cognito::UserPool> &userPool) {
                              return userPool.second.region == region && userPool.second.name == name;
                          });

        if (it == _userPools.end()) {
            log_error << "Update user pool failed, region: " << userPool.region << " name: " << userPool.name;
            throw Core::DatabaseException("Update cognito user pool failed, region: " + userPool.region + " name: " + userPool.name);
        }
        _userPools[it->first] = userPool;
        return _userPools[it->first];
    }

    void CognitoMemoryDb::DeleteUserPool(const std::string &userPoolId) {
        Poco::ScopedLock lock(_userPoolMutex);

        const auto count = std::erase_if(_userPools, [userPoolId](const auto &item) {
            auto const &[key, value] = item;
            return value.userPoolId == userPoolId;
        });
        log_debug << "Cognito user pool deleted, count: " << count;
    }

    void CognitoMemoryDb::DeleteAllUserPools() {
        Poco::ScopedLock lock(_userPoolMutex);

        log_debug << "All cognito user pools deleted, count: " << _userPools.size();
        _userPools.clear();
    }

    bool CognitoMemoryDb::UserExists(const std::string &region, const std::string &userPoolId, const std::string &userName) {

        return find_if(_users.begin(),
                       _users.end(),
                       [region, userPoolId, userName](const std::pair<std::string, Entity::Cognito::User> &user) {
                           return user.second.region == region && user.second.userPoolId == userPoolId && user.second.userName == userName;
                       }) != _users.end();
    }

    Entity::Cognito::User CognitoMemoryDb::CreateUser(const Entity::Cognito::User &user) {
        Poco::ScopedLock lock(_userMutex);

        std::string oid = Poco::UUIDGenerator().createRandom().toString();
        _users[oid] = user;
        log_trace << "Cognito user created, oid: " << oid;
        return GetUserByOid(oid);
    }

    Entity::Cognito::User CognitoMemoryDb::GetUserByOid(const std::string &oid) {

        auto it = find_if(_users.begin(), _users.end(), [oid](const std::pair<std::string, Entity::Cognito::User> &user) {
            return user.first == oid;
        });

        if (it == _users.end()) {
            log_error << "Get cognito user by oid failed, oid: " << oid;
            throw Core::DatabaseException("Get cognito user by oid failed, oid: " + oid);
        }

        it->second.oid = oid;
        return it->second;
    }

    Entity::Cognito::User CognitoMemoryDb::GetUserByUserName(const std::string &region, const std::string &userPoolId, const std::string &userName) {

        auto it = find_if(_users.begin(),
                          _users.end(),
                          [region, userPoolId, userName](const std::pair<std::string, Entity::Cognito::User> &user) {
                              return user.second.region == region && user.second.userPoolId == userPoolId && user.second.userName == userName;
                          });

        if (it == _users.end()) {
            log_error << "Get cognito user by user name failed, userName: " << userName;
            throw Core::DatabaseException("Get cognito user by user name failed, userName: " + userName);
        }

        it->second.oid = it->first;
        return it->second;
    }

    long CognitoMemoryDb::CountUsers(const std::string &region, const std::string &userPoolId) {

        long count = 0;
        if (!region.empty() && !userPoolId.empty()) {

            for (const auto &user: _users) {
                if (user.second.region == region && user.second.userPoolId == userPoolId) {
                    count++;
                }
            }

        } else if (!region.empty()) {

            for (const auto &user: _users) {
                if (user.second.region == region) {
                    count++;
                }
            }

        } else {

            count = static_cast<long>(_users.size());
        }

        log_trace << "Count user pools, size: " << count;
        return count;
    }

    std::vector<Entity::Cognito::User> CognitoMemoryDb::ListUsers(const std::string &region, const std::string &userPoolId) {

        Entity::Cognito::UserList userList;
        if (!region.empty() && !userPoolId.empty()) {

            for (const auto &user: _users) {
                if (user.second.region == region && user.second.userPoolId == userPoolId) {
                    userList.emplace_back(user.second);
                }
            }

        } else if (!region.empty()) {

            for (const auto &user: _users) {
                if (user.second.region == region) {
                    userList.emplace_back(user.second);
                }
            }

        } else {

            for (const auto &user: _users) {
                userList.emplace_back(user.second);
            }
        }

        log_trace << "Got user list, size: " << userList.size();
        return userList;
    }

    std::vector<Entity::Cognito::User> CognitoMemoryDb::ListUsersInGroup(const std::string &region, const std::string &userPoolId, const std::string &groupName) {

        Entity::Cognito::UserList userList;

        for (const auto &user: _users) {
            if (user.second.region == region && user.second.userPoolId == userPoolId && std::find_if(user.second.groups.begin(), user.second.groups.end(), [&groupName](const Entity::Cognito::Group &g) {
                                                                                            return g.groupName == groupName;
                                                                                        }) != user.second.groups.end()) {
                userList.emplace_back(user.second);
            }
        }

        log_trace << "Got user in group list, size: " << userList.size();
        return userList;
    }

    Entity::Cognito::User CognitoMemoryDb::UpdateUser(const Entity::Cognito::User &user) {

        Poco::ScopedLock lock(_userMutex);

        std::string region = user.region;
        std::string userPoolId = user.userPoolId;
        std::string userName = user.userName;
        auto it = find_if(_users.begin(),
                          _users.end(),
                          [region, userPoolId, userName](const std::pair<std::string, Entity::Cognito::User> &user) {
                              return user.second.region == region && user.second.userPoolId == userPoolId && user.second.userName == userName;
                          });

        if (it == _users.end()) {
            log_error << "Update user failed, region: " << user.region << " name: " << user.userName;
            throw Core::DatabaseException("Update cognito user failed, region: " + user.region + " name: " + user.userName);
        }
        _users[it->first] = user;
        return _users[it->first];
    }

    void CognitoMemoryDb::DeleteUser(const Entity::Cognito::User &user) {
        Poco::ScopedLock lock(_userMutex);

        const auto count = std::erase_if(_users, [user](const std::pair<std::string, Entity::Cognito::User> &u) {
            return u.second.region == user.region && u.second.userPoolId == user.userPoolId && u.second.userName == user.userName;
        });
        log_debug << "Cognito user deleted, count: " << count;
    }

    void CognitoMemoryDb::DeleteAllUsers() {
        Poco::ScopedLock lock(_userMutex);

        log_debug << "All cognito users deleted, count: " << _userPools.size();
        _users.clear();
    }

    bool CognitoMemoryDb::GroupExists(const std::string &region, const std::string &groupName) {

        return find_if(_groups.begin(),
                       _groups.end(),
                       [region, groupName](const std::pair<std::string, Entity::Cognito::Group> &group) {
                           return group.second.region == region && group.second.groupName == groupName;
                       }) != _groups.end();
    }

    Entity::Cognito::Group CognitoMemoryDb::GetGroupByGroupName(const std::string &region, const std::string &groupPoolId, const std::string &groupName) {

        auto it = find_if(_groups.begin(),
                          _groups.end(),
                          [region, groupPoolId, groupName](const std::pair<std::string, Entity::Cognito::Group> &group) {
                              return group.second.region == region && group.second.userPoolId == groupPoolId && group.second.groupName == groupName;
                          });

        if (it == _groups.end()) {
            log_error << "Get cognito group by group name failed, groupName: " << groupName;
            throw Core::DatabaseException("Get cognito group by group name failed, groupName: " + groupName);
        }

        it->second.oid = it->first;
        return it->second;
    }

    Entity::Cognito::Group CognitoMemoryDb::CreateGroup(const Entity::Cognito::Group &group) {
        Poco::ScopedLock lock(_groupMutex);

        std::string oid = Poco::UUIDGenerator().createRandom().toString();
        _groups[oid] = group;
        log_trace << "Cognito user pool created, oid: " << oid;
        return _groups[oid];
    }

    std::vector<Entity::Cognito::Group> CognitoMemoryDb::ListGroups(const std::string &region, const std::string &userPoolId) {

        Entity::Cognito::GroupList groupList;
        if (!region.empty() && !userPoolId.empty()) {

            for (const auto &group: _groups) {
                if (group.second.region == region && group.second.userPoolId == userPoolId) {
                    groupList.emplace_back(group.second);
                }
            }

        } else if (!region.empty()) {

            for (const auto &group: _groups) {
                if (group.second.region == region) {
                    groupList.emplace_back(group.second);
                }
            }

        } else {

            for (const auto &group: _groups) {
                groupList.emplace_back(group.second);
            }
        }

        log_trace << "Got group list, size: " << groupList.size();
        return groupList;
    }

    void CognitoMemoryDb::DeleteGroup(const std::string &region, const std::string &userPoolId, const std::string &groupName) {
        Poco::ScopedLock lock(_groupMutex);

        const auto count = std::erase_if(_groups, [region, userPoolId, groupName](const std::pair<std::string, Entity::Cognito::Group> &g) {
            return g.second.region == region && g.second.userPoolId == userPoolId && g.second.groupName == groupName;
        });
        log_debug << "Cognito group deleted, groupName: " << groupName << " count: " << count;
    }

}// namespace AwsMock::Database
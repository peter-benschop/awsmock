//
// Created by vogje01 on 29/05/2023.
//

#include <awsmock/repository/CognitoDatabase.h>

namespace AwsMock::Database {

    bool CognitoDatabase::UserPoolExists(const std::string &region, const std::string &name) {

        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _userPoolCollection = (*client)[_databaseName][_userpoolCollectionName];
                int64_t count = _userPoolCollection.count_documents(make_document(kvp("region", region), kvp("name", name)));
                log_trace << "Cognito user pool exists: " << std::boolalpha << count;
                return count > 0;

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            return _memoryDb.UserPoolExists(region, name);
        }
    }

    bool CognitoDatabase::UserPoolExists(const std::string &userPoolId) {

        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _userPoolCollection = (*client)[_databaseName][_userpoolCollectionName];
                int64_t count = _userPoolCollection.count_documents(make_document(kvp("userPoolId", userPoolId)));
                log_trace << "Cognito user pool exists: " << std::boolalpha << count;
                return count > 0;

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            return _memoryDb.UserPoolExists(userPoolId);
        }
    }

    Entity::Cognito::UserPool CognitoDatabase::CreateUserPool(const Entity::Cognito::UserPool &userPool) {

        if (HasDatabase()) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _userPoolCollection = (*client)[_databaseName][_userpoolCollectionName];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto result = _userPoolCollection.insert_one(userPool.ToDocument());
                session.commit_transaction();
                log_trace << "User pool created, oid: " << result->inserted_id().get_oid().value.to_string();
                return GetUserPoolById(result->inserted_id().get_oid().value);

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            return _memoryDb.CreateUserPool(userPool);
        }
    }

    Entity::Cognito::UserPool CognitoDatabase::GetUserPoolById(bsoncxx::oid oid) {

        try {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _userPoolCollection = (*client)[_databaseName][_userpoolCollectionName];
            mongocxx::stdx::optional<bsoncxx::document::value> mResult = _userPoolCollection.find_one(make_document(kvp("_id", oid)));
            if (!mResult) {
                log_error << "Database exception: Cognito not found ";
                throw Core::DatabaseException("Database exception, Cognito not found ");
            }

            Entity::Cognito::UserPool result;
            result.FromDocument(mResult->view());
            return result;

        } catch (const mongocxx::exception &exc) {
            log_error << "Database exception " << exc.what();
            throw Core::DatabaseException("Database exception " + std::string(exc.what()));
        }
    }

    Entity::Cognito::UserPool CognitoDatabase::GetUserPoolByUserPoolId(const std::string &userPoolId) {

        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _userPoolCollection = (*client)[_databaseName][_userpoolCollectionName];
                mongocxx::stdx::optional<bsoncxx::document::value> mResult = _userPoolCollection.find_one(make_document(kvp("userPoolId", userPoolId)));
                if (!mResult) {
                    log_error << "Database exception: user pool not found ";
                    throw Core::DatabaseException("Database exception, user pool not found ");
                }

                Entity::Cognito::UserPool result;
                result.FromDocument(mResult->view());
                return result;

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            return _memoryDb.GetUserPoolByUserPoolId(userPoolId);
        }
    }

    Entity::Cognito::UserPool CognitoDatabase::GetUserPoolByClientId(const std::string &clientId) {

        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _userPoolCollection = (*client)[_databaseName][_userpoolCollectionName];
                mongocxx::stdx::optional<bsoncxx::document::value> mResult = _userPoolCollection.find_one(make_document(
                        kvp("userPoolClients",
                            make_document(kvp("$elemMatch",
                                              make_document(kvp("clientId", clientId)))))));
                if (!mResult) {
                    log_error << "Database exception: user pool not found ";
                    throw Core::DatabaseException("Database exception, user pool not found ");
                }

                Entity::Cognito::UserPool result;
                result.FromDocument(mResult->view());
                return result;

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            return _memoryDb.GetUserPoolByClientId(clientId);
        }
    }

    Entity::Cognito::UserPool CognitoDatabase::GetUserPoolByRegionName(const std::string &region, const std::string &name) {

        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _userPoolCollection = (*client)[_databaseName][_userpoolCollectionName];
                mongocxx::stdx::optional<bsoncxx::document::value> mResult = _userPoolCollection.find_one(make_document(kvp("region", region), kvp("name", name)));
                if (!mResult) {
                    log_error << "Database exception: Cognito not found ";
                    throw Core::DatabaseException("Database exception, Cognito not found ");
                }

                Entity::Cognito::UserPool result;
                result.FromDocument(mResult->view());
                return result;

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            return _memoryDb.GetUserPoolByRegionName(region, name);
        }
    }

    Entity::Cognito::UserPool CognitoDatabase::CreateOrUpdateUserPool(Entity::Cognito::UserPool &userPool) {

        if (UserPoolExists(userPool.region, userPool.name)) {

            return UpdateUserPool(userPool);

        } else {

            return CreateUserPool(userPool);
        }
    }

    Entity::Cognito::UserPool CognitoDatabase::UpdateUserPool(const Entity::Cognito::UserPool &userPool) {

        if (HasDatabase()) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _userPoolCollection = (*client)[_databaseName][_userpoolCollectionName];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto result = _userPoolCollection.replace_one(make_document(kvp("region", userPool.region), kvp("name", userPool.name)), userPool.ToDocument());
                session.commit_transaction();

                log_trace << "Cognito user pool updated: " << userPool.ToString();
                return GetUserPoolByRegionName(userPool.region, userPool.name);

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            return _memoryDb.UpdateUserPool(userPool);
        }
    }

    std::vector<Entity::Cognito::UserPool> CognitoDatabase::ListUserPools(const std::string &region) {

        std::vector<Entity::Cognito::UserPool> userPools;
        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _userPoolCollection = (*client)[_databaseName][_userpoolCollectionName];
                if (region.empty()) {

                    auto userPoolCursor = _userPoolCollection.find(make_document());
                    for (auto userPool: userPoolCursor) {
                        Entity::Cognito::UserPool result;
                        result.FromDocument(userPool);
                        userPools.push_back(result);
                    }

                } else {

                    auto userPoolCursor = _userPoolCollection.find(make_document(kvp("region", region)));
                    for (auto userPool: userPoolCursor) {
                        Entity::Cognito::UserPool result;
                        result.FromDocument(userPool);
                        userPools.push_back(result);
                    }
                }
            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            userPools = _memoryDb.ListUserPools(region);
        }

        log_trace << "Got user pool list, size:" << userPools.size();
        return userPools;
    }

    long CognitoDatabase::CountUserPools(const std::string &region) {

        if (HasDatabase()) {

            try {
                long count = 0;
                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _userPoolCollection = (*client)[_databaseName][_userpoolCollectionName];
                if (region.empty()) {
                    count = _userPoolCollection.count_documents(make_document());
                } else {
                    count = _userPoolCollection.count_documents(make_document(kvp("region", region)));
                }
                log_trace << "User pool count: " << count;
                return count;

            } catch (mongocxx::exception::system_error &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            return _memoryDb.CountUserPools(region);
        }
    }

    void CognitoDatabase::DeleteUserPool(const std::string &id) {

        if (HasDatabase()) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _userPoolCollection = (*client)[_databaseName][_userpoolCollectionName];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto result = _userPoolCollection.delete_many(make_document(kvp("userPoolId", id)));
                session.commit_transaction();
                log_debug << "User pool deleted, userPoolId: " << id << " count: " << result->deleted_count();

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            _memoryDb.DeleteUserPool(id);
        }
    }

    void CognitoDatabase::DeleteAllUserPools() {

        if (HasDatabase()) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _userPoolCollection = (*client)[_databaseName][_userpoolCollectionName];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto result = _userPoolCollection.delete_many({});
                session.commit_transaction();
                log_debug << "All cognito user pools deleted, count: " << result->deleted_count();

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            _memoryDb.DeleteAllUserPools();
        }
    }

    bool CognitoDatabase::UserExists(const std::string &region, const std::string &userPoolId, const std::string &userName) {

        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _userCollection = (*client)[_databaseName][_userCollectionName];
                int64_t count = _userCollection.count_documents(make_document(kvp("region", region),
                                                                              kvp("userPoolId", userPoolId),
                                                                              kvp("userName", userName)));
                log_trace << "Cognito user exists: " << std::boolalpha << count;
                return count > 0;

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            return _memoryDb.UserExists(region, userPoolId, userName);
        }
    }

    bool CognitoDatabase::UserExists(const std::string &region, const std::string &userName) {

        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _userCollection = (*client)[_databaseName][_userCollectionName];
                int64_t count = _userCollection.count_documents(make_document(kvp("region", region), kvp("userName", userName)));
                log_trace << "Cognito user exists: " << std::boolalpha << count;
                return count > 0;

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            return _memoryDb.UserExists(region, userName);
        }
    }

    Entity::Cognito::User CognitoDatabase::CreateUser(const Entity::Cognito::User &user) {

        if (HasDatabase()) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _userCollection = (*client)[_databaseName][_userCollectionName];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto result = _userCollection.insert_one(user.ToDocument());
                session.commit_transaction();
                log_trace << "User created, oid: " << result->inserted_id().get_oid().value.to_string();
                return GetUserById(result->inserted_id().get_oid().value);

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            return _memoryDb.CreateUser(user);
        }
    }

    Entity::Cognito::User CognitoDatabase::GetUserById(bsoncxx::oid oid) {

        try {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _userCollection = (*client)[_databaseName][_userCollectionName];
            mongocxx::stdx::optional<bsoncxx::document::value>
                    mResult = _userCollection.find_one(make_document(kvp("_id", oid)));
            if (!mResult) {
                log_error << "Database exception: user not found ";
                throw Core::DatabaseException("Database exception, user not found ");
            }

            Entity::Cognito::User result;
            result.FromDocument(mResult->view());
            return result;

        } catch (const mongocxx::exception &exc) {
            log_error << "Database exception " << exc.what();
            throw Core::DatabaseException("Database exception " + std::string(exc.what()));
        }
    }

    Entity::Cognito::User CognitoDatabase::GetUserByUserName(const std::string &region, const std::string &userPoolId, const std::string &userName) {

        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _userCollection = (*client)[_databaseName][_userCollectionName];
                auto mResult = _userCollection.find_one(make_document(kvp("region", region), kvp("userPoolId", userPoolId), kvp("userName", userName)));
                if (!mResult) {
                    log_error << "Database exception: user not found ";
                    throw Core::DatabaseException("Database exception, user not found ");
                }

                Entity::Cognito::User result;
                result.FromDocument(mResult->view());
                return result;

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            return _memoryDb.GetUserByUserName(region, userPoolId, userName);
        }
    }

    Entity::Cognito::User CognitoDatabase::GetUserById(const std::string &oid) {

        if (HasDatabase()) {

            return GetUserById(bsoncxx::oid(oid));

        } else {

            return _memoryDb.GetUserByOid(oid);
        }
    }

    long CognitoDatabase::CountUsers(const std::string &region, const std::string &userPoolId) {

        if (HasDatabase()) {

            try {

                long count = 0;
                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _userCollection = (*client)[_databaseName][_userCollectionName];
                if (!region.empty() && !userPoolId.empty()) {
                    count = _userCollection.count_documents(make_document(kvp("region", region), kvp("userPoolId", userPoolId)));
                } else if (!region.empty()) {
                    count = _userCollection.count_documents(make_document(kvp("region", region)));
                } else {
                    count = _userCollection.count_documents(make_document());
                }
                log_trace << "User count: " << count;
                return count;

            } catch (mongocxx::exception::system_error &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            return _memoryDb.CountUsers(region);
        }
    }

    std::vector<Entity::Cognito::User> CognitoDatabase::ListUsers(const std::string &region, const std::string &userPoolId) {

        std::vector<Entity::Cognito::User> users;
        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _userCollection = (*client)[_databaseName][_userCollectionName];
                if (!region.empty() && !userPoolId.empty()) {

                    auto userCursor = _userCollection.find(make_document(kvp("region", region), kvp("userPoolId", userPoolId)));
                    for (auto user: userCursor) {
                        Entity::Cognito::User result;
                        result.FromDocument(user);
                        users.push_back(result);
                    }

                } else if (!region.empty()) {

                    auto userCursor = _userCollection.find(make_document(kvp("region", region)));
                    for (auto user: userCursor) {
                        Entity::Cognito::User result;
                        result.FromDocument(user);
                        users.push_back(result);
                    }

                } else {

                    auto userCursor = _userCollection.find(make_document());
                    for (auto user: userCursor) {
                        Entity::Cognito::User result;
                        result.FromDocument(user);
                        users.push_back(result);
                    }
                }

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            users = _memoryDb.ListUsers(region, userPoolId);
        }

        log_trace << "Got user list, size:" << users.size();
        return users;
    }

    std::vector<Entity::Cognito::User> CognitoDatabase::ListUsersInGroup(const std::string &region, const std::string &userPoolId, const std::string &groupName) {

        std::vector<Entity::Cognito::User> users;
        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _userCollection = (*client)[_databaseName][_userCollectionName];

                auto userCursor = _userCollection.find(make_document(kvp("region", region), kvp("userPoolId", userPoolId),
                                                                     kvp("groups",
                                                                         make_document(kvp("$elemMatch", make_document(kvp("groupName", groupName)))))));
                for (auto user: userCursor) {
                    Entity::Cognito::User result;
                    result.FromDocument(user);
                    users.push_back(result);
                }

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            users = _memoryDb.ListUsersInGroup(region, userPoolId, groupName);
        }

        log_trace << "Got users in group, size:" << users.size();
        return users;
    }

    Entity::Cognito::User CognitoDatabase::UpdateUser(const Entity::Cognito::User &user) {

        if (HasDatabase()) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _userCollection = (*client)[_databaseName][_userCollectionName];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto result = _userCollection.replace_one(make_document(kvp("region", user.region), kvp("userPoolId", user.userPoolId), kvp("userName", user.userName)), user.ToDocument());
                session.commit_transaction();
                log_trace << "Cognito user updated: " << user.ToString();
                return GetUserByUserName(user.region, user.userPoolId, user.userName);

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            return _memoryDb.UpdateUser(user);
        }
    }

    Entity::Cognito::User CognitoDatabase::CreateOrUpdateUser(Entity::Cognito::User &user) {

        if (UserExists(user.region, user.userPoolId, user.userName)) {

            return UpdateUser(user);

        } else {

            return CreateUser(user);
        }
    }

    void CognitoDatabase::DeleteUser(const Entity::Cognito::User &user) {

        if (HasDatabase()) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _userCollection = (*client)[_databaseName][_userCollectionName];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto result = _userCollection.delete_many(make_document(kvp("region", user.region), kvp("userPoolId", user.userPoolId), kvp("userName", user.userName)));
                session.commit_transaction();
                log_debug << "User deleted, userName: " << user.userName << " count: " << result->deleted_count();

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            _memoryDb.DeleteUser(user);
        }
    }

    void CognitoDatabase::DeleteAllUsers() {

        if (HasDatabase()) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _userCollection = (*client)[_databaseName][_userCollectionName];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto result = _userCollection.delete_many({});
                session.commit_transaction();
                log_debug << "All cognito users deleted, count: " << result->deleted_count();

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            _memoryDb.DeleteAllUsers();
        }
    }

    bool CognitoDatabase::GroupExists(const std::string &region, const std::string &groupName) {

        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _groupCollection = (*client)[_databaseName][_groupCollectionName];
                int64_t count = _groupCollection.count_documents(make_document(kvp("region", region), kvp("groupName", groupName)));
                log_trace << "Cognito group exists: " << std::boolalpha << count;
                return count > 0;

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            return _memoryDb.GroupExists(region, groupName);
        }
    }

    Entity::Cognito::Group CognitoDatabase::GetGroupById(bsoncxx::oid oid) {

        try {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _groupCollection = (*client)[_databaseName][_groupCollectionName];
            mongocxx::stdx::optional<bsoncxx::document::value> mResult = _groupCollection.find_one(make_document(kvp("_id", oid)));
            if (!mResult) {
                log_error << "Database exception: Cognito not found ";
                throw Core::DatabaseException("Database exception, Cognito not found ");
            }

            Entity::Cognito::Group result;
            result.FromDocument(mResult->view());
            return result;

        } catch (const mongocxx::exception &exc) {
            log_error << "Database exception " << exc.what();
            throw Core::DatabaseException("Database exception " + std::string(exc.what()));
        }
    }

    Entity::Cognito::Group CognitoDatabase::GetGroupByGroupName(const std::string &region, const std::string &userPoolId, const std::string &groupName) {

        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _userCollection = (*client)[_databaseName][_groupCollectionName];
                auto mResult = _userCollection.find_one(make_document(kvp("region", region), kvp("userPoolId", userPoolId), kvp("groupName", groupName)));
                if (!mResult) {
                    log_error << "Database exception: group not found ";
                    throw Core::DatabaseException("Database exception, group not found ");
                }

                Entity::Cognito::Group result;
                result.FromDocument(mResult->view());
                return result;

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            return _memoryDb.GetGroupByGroupName(region, userPoolId, groupName);
        }
    }

    Entity::Cognito::Group CognitoDatabase::CreateGroup(const Entity::Cognito::Group &group) {

        if (HasDatabase()) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _groupCollection = (*client)[_databaseName][_groupCollectionName];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto result = _groupCollection.insert_one(group.ToDocument());
                session.commit_transaction();
                log_trace << "Cognito group created, oid: " << result->inserted_id().get_oid().value.to_string();
                return GetGroupById(result->inserted_id().get_oid().value);

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            return _memoryDb.CreateGroup(group);
        }
    }

    std::vector<Entity::Cognito::Group> CognitoDatabase::ListGroups(const std::string &region, const std::string &userPoolId) {

        std::vector<Entity::Cognito::Group> groups;
        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _groupCollection = (*client)[_databaseName][_groupCollectionName];
                if (!region.empty() && !userPoolId.empty()) {

                    auto groupCursor = _groupCollection.find(make_document(kvp("region", region), kvp("userPoolId", userPoolId)));
                    for (auto group: groupCursor) {
                        Entity::Cognito::Group result;
                        result.FromDocument(group);
                        groups.push_back(result);
                    }

                } else if (!region.empty()) {

                    auto groupCursor = _groupCollection.find(make_document(kvp("region", region)));
                    for (auto group: groupCursor) {
                        Entity::Cognito::Group result;
                        result.FromDocument(group);
                        groups.push_back(result);
                    }

                } else {

                    auto groupCursor = _groupCollection.find(make_document());
                    for (auto group: groupCursor) {
                        Entity::Cognito::Group result;
                        result.FromDocument(group);
                        groups.push_back(result);
                    }
                }

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            groups = _memoryDb.ListGroups(region, userPoolId);
        }

        log_trace << "Got group list, size:" << groups.size();
        return groups;
    }

    void CognitoDatabase::DeleteGroup(const std::string &region, const std::string &userPoolId, const std::string &groupName) {

        if (HasDatabase()) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _groupCollection = (*client)[_databaseName][_groupCollectionName];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto result = _groupCollection.delete_many(make_document(kvp("region", region), kvp("userPoolId", userPoolId), kvp("groupName", groupName)));
                session.commit_transaction();
                log_debug << "Group deleted, groupName: " << groupName << " count: " << result->deleted_count();

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            _memoryDb.DeleteGroup(region, userPoolId, groupName);
        }
    }

    void CognitoDatabase::DeleteAllGroups(const std::string &region) {

        if (HasDatabase()) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _groupCollection = (*client)[_databaseName][_groupCollectionName];
            auto session = client->start_session();

            try {

                session.start_transaction();
                if (region.empty()) {
                    auto result = _groupCollection.delete_many({});
                    log_debug << "All groups deleted, count: " << result->deleted_count();
                } else {
                    auto result = _groupCollection.delete_many(make_document(kvp("region", region)));
                    log_debug << "All groups deleted, region: " << region << " count: " << result->deleted_count();
                }
                session.commit_transaction();

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            _memoryDb.DeleteAllGroups(region);
        }
    }

}// namespace AwsMock::Database

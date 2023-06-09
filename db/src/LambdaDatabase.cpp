//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/db/LambdaDatabase.h"

namespace AwsMock::Database {

    using namespace Poco::Data::Keywords;

    LambdaDatabase::LambdaDatabase(const Core::Configuration &configuration) : Database(configuration), _logger(Poco::Logger::get("LambdaDatabase")) {
        Core::Logger::SetDefaultConsoleLogger("LambdaDatabase");
    }

    bool LambdaDatabase::LambdaExists(const std::string &function, const std::string &runtime) {

        int count = 0;
        Poco::Data::Session session = GetSession();

        session << "SELECT COUNT(*) FROM lambda WHERE function=? AND runtime=?", bind(function), bind(runtime), into(count), now;

        session.close();
        poco_trace(_logger, "Lambda exists: " + std::to_string(count));

        return count > 0;
    }

    bool LambdaDatabase::LambdaExists(const Entity::Lambda::Lambda &lambda) {

        return LambdaExists(lambda.function, lambda.runtime);
    }

    Entity::Lambda::Lambda LambdaDatabase::CreateLambda(const Entity::Lambda::Lambda &lambda) {

        long id = 0;
        Entity::Lambda::Lambda result;
        try {
            Poco::Data::Session session = GetSession();
            session.begin();
            session
                << "INSERT INTO lambda(function,runtime,role,handler,size,image_id,container_id,tag,arn,host_port,last_started) VALUES(?,?,?,?,?,?,?,?,?,?,?) returning id",
                bind(lambda.function), bind(lambda.runtime), bind(lambda.role), bind(lambda.handler), bind(lambda.size), bind(lambda.imageId), bind(lambda.containerId),
                bind(lambda.tag), bind(lambda.arn), bind(lambda.hostPort), bind(lambda.lastStarted), into(id), now;
            session.commit();

            poco_trace(_logger, "Lambda created: " + lambda.ToString());

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
            throw Core::DatabaseException(exc.message());
        }
        return GetLambdaById(id);
    }

    Entity::Lambda::Lambda LambdaDatabase::CreateOrUpdateLambda(const Entity::Lambda::Lambda &lambda) {

        if (LambdaExists(lambda)) {
            return UpdateLambda(lambda);
        } else {
            return CreateLambda(lambda);
        }
    }

    Entity::Lambda::Lambda LambdaDatabase::UpdateLambda(const Entity::Lambda::Lambda &lambda) {

        int id = 0;
        try {
            Poco::Data::Session session = GetSession();
            session.begin();
            session << "UPDATE lambda SET role=?,handler=?,size=?,image_id=?,container_id=?,tag=?,arn=?,host_port=?,last_started=?,modified=CURRENT_TIMESTAMP "
                       "WHERE function=? AND runtime=? returning id",
                bind(lambda.role), bind(lambda.handler), bind(lambda.size), bind(lambda.imageId), bind(lambda.containerId), bind(lambda.tag), bind(lambda.arn),
                bind(lambda.hostPort), bind(lambda.lastStarted), bind(lambda.function), bind(lambda.runtime), into(id), now;
            session.commit();

            poco_trace(_logger, "Lambda updated, lambda: " + lambda.ToString());

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
            throw Core::DatabaseException(exc.message(), 500);
        }
        return GetLambdaById(id);
    }

    Entity::Lambda::Lambda LambdaDatabase::GetLambdaById(long id) {

        Entity::Lambda::Lambda result;
        try {
            Poco::Data::Session session = GetSession();
            session.begin();
            session << "SELECT id,function,runtime,role,handler,size,image_id,container_id,tag,arn,host_port,last_started,created,modified FROM lambda WHERE id=?",
                bind(id), into(result.id), into(result.function), into(result.runtime), into(result.role), into(result.handler), into(result.size),
                into(result.imageId), into(result.containerId), into(result.tag), into(result.arn), into(result.hostPort), into(result.lastStarted),
                into(result.created), into(result.modified), now;
            session.commit();

            poco_trace(_logger, "Got lambda: " + result.ToString());

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }
        return result;
    }

    Entity::Lambda::Lambda LambdaDatabase::GetLambdaByArn(const std::string &arn) {

        Entity::Lambda::Lambda result;
        try {
            Poco::Data::Session session = GetSession();
            session.begin();
            session << "SELECT id,function,runtime,role,handler,size,image_id,container_id,tag,arn,host_port,last_started,created,modified FROM lambda WHERE arn=?",
                bind(arn), into(result.id), into(result.function), into(result.runtime), into(result.role), into(result.handler), into(result.size),
                into(result.imageId), into(result.containerId), into(result.tag), into(result.arn), into(result.hostPort), into(result.lastStarted),
                into(result.created), into(result.modified), now;
            session.commit();

            poco_trace(_logger, "Got lambda: " + result.ToString());

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }
        return result;
    }
} // namespace AwsMock::Database

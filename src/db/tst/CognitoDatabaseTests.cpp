//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_CORE_COGNITODATABASETEST_H
#define AWMOCK_CORE_COGNITODATABASETEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/TestUtils.h>
#include <awsmock/repository/CognitoDatabase.h>

#define USER_POOL "test-user-pool"

namespace AwsMock::Database {

  class CognitoDatabaseTest : public ::testing::Test {

  protected:

    void SetUp() override {
      _region = _configuration.getString("awsmock.region");
      _accountId = _configuration.getString("awsmock.account.id");
    }

    void TearDown() override {
      //_cognitoDatabase.DeleteAllUserPools();
    }

    std::string _region;
    std::string _accountId;
    Core::Configuration _configuration = Core::TestUtils::GetTestConfiguration();
    CognitoDatabase _cognitoDatabase = CognitoDatabase(_configuration);
  };

  TEST_F(CognitoDatabaseTest, CognitoUserPoolExistsTest) {

    // arrange
    Entity::Cognito::UserPool userPool = {.region=_region, .name=USER_POOL};
    _cognitoDatabase.CreateUserPool(userPool);

    // act
    bool result = _cognitoDatabase.UserPoolExists(_region, USER_POOL);

    // assert
    EXPECT_TRUE(result);
  }

  /*TEST_F(CognitoDatabaseTest, CognitoCountTest) {

    // arrange
    Entity::Cognito::Cognito cognito = {.region=_region, .function=FUNCTION, .runtime=RUNTIME, .role=ROLE, .handler=HANDLER, .codeSize=1000};
    _cognitoDatabase.CreateCognito(cognito);

    // act
    long result = _cognitoDatabase.CognitoCount(cognito.region);

    // assert
    EXPECT_EQ(1, result);
  }

  TEST_F(CognitoDatabaseTest, CognitoExistsTest) {

    // arrange
    Entity::Cognito::Cognito cognito = {.region=_region, .function=FUNCTION, .runtime=RUNTIME, .role=ROLE, .handler=HANDLER, .codeSize=1000};
    _cognitoDatabase.CreateCognito(cognito);

    // act
    bool result = _cognitoDatabase.CognitoExists(_region, FUNCTION, RUNTIME);

    // assert
    EXPECT_TRUE(result);
  }

  TEST_F(CognitoDatabaseTest, CognitoGetByIdTest) {

    // arrange
    Entity::Cognito::Cognito cognito = {.region=_region, .function=FUNCTION, .runtime=RUNTIME, .role=ROLE, .handler=HANDLER, .codeSize=1000};
    cognito = _cognitoDatabase.CreateCognito(cognito);

    // act
    Entity::Cognito::Cognito result = _cognitoDatabase.GetCognitoById(cognito.oid);

    // assert
    EXPECT_EQ(result.oid, cognito.oid);
  }

  TEST_F(CognitoDatabaseTest, CognitoGetByArnTest) {

    // arrange
    std::string arn = Core::AwsUtils::CreateCognitoArn(_region, _accountId, FUNCTION);
    Entity::Cognito::Cognito cognito = {.region=_region, .function=FUNCTION, .runtime=RUNTIME, .role=ROLE, .handler=HANDLER, .arn=arn};
    cognito = _cognitoDatabase.CreateCognito(cognito);

    // act
    Entity::Cognito::Cognito result = _cognitoDatabase.GetCognitoByArn(arn);

    // assert
    EXPECT_EQ(result.arn, cognito.arn);
  }

  TEST_F(CognitoDatabaseTest, CognitoUpdateTest) {

    // arrange
    std::string arn = Core::AwsUtils::CreateCognitoArn(_region, _accountId, FUNCTION);
    Entity::Cognito::Cognito cognito = {.region=_region, .function=FUNCTION, .runtime=RUNTIME, .role=ROLE, .handler=HANDLER, .arn=arn};
    cognito = _cognitoDatabase.CreateCognito(cognito);

    // act
    cognito.role = "new_role";
    Entity::Cognito::Cognito result = _cognitoDatabase.UpdateCognito(cognito);

    // assert
    EXPECT_EQ(result.role, cognito.role);
  }

  TEST_F(CognitoDatabaseTest, CognitoListTest) {

    // arrange
    Entity::Cognito::Cognito cognito = {.region=_region, .function=FUNCTION, .runtime=RUNTIME, .role=ROLE, .handler=HANDLER, .codeSize=1000};
    cognito = _cognitoDatabase.CreateCognito(cognito);

    // act
    std::vector<Entity::Cognito::Cognito> result = _cognitoDatabase.ListCognitos(cognito.region);

    // assert
    EXPECT_EQ(1, result.size());
    EXPECT_TRUE(result[0].runtime == RUNTIME);
    EXPECT_TRUE(result[0].role == ROLE);
    EXPECT_TRUE(result[0].handler == HANDLER);
  }

  TEST_F(CognitoDatabaseTest, CognitoDeleteTest) {

    // arrange
    std::string arn = Core::AwsUtils::CreateCognitoArn(_region, _accountId, FUNCTION);
    Entity::Cognito::Cognito cognito = {.region=_region, .function=FUNCTION, .runtime=RUNTIME, .role=ROLE, .handler=HANDLER, .arn=arn};
    cognito = _cognitoDatabase.CreateCognito(cognito);

    // act
    _cognitoDatabase.DeleteCognito(cognito.function);
    bool result = _cognitoDatabase.CognitoExists(_region, FUNCTION, RUNTIME);

    // assert
    EXPECT_FALSE(result);
  }*/

} // namespace AwsMock::Core

#endif // AWMOCK_CORE_COGNITODATABASETEST_H
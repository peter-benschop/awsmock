FROM amazon/dynamodb-local:latest

VOLUME ./dynamodbdata /home/dynamodblocal/data

WORKDIR /home/dynamodblocal

EXPOSE 8000 8000

ENTRYPOINT ["java", "-Djava.library.path=./DynamoDBLocal_lib", "-jar", "DynamoDBLocal.jar", "-sharedDb"]

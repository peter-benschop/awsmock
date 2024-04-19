---
title: awsmockcfg(1)
section: 1
header: awsmockcfg AwsMock configuration
footer: awsmockcfg 0.5.210
date: December 18, 2023
---

## NAME
```awsmockcfg``` AwsMock configuration

## DESCRIPTION

AwsMock can be configured in several ways. First of all is the default configuration file: ```/etc/aws-mock.properties```.
It define the main configuration for all AwsMock modules. The default configuration file can be changed using the 
```--config``` options of the ```awsmockmgr```.

Each of the values can be overwritten by environment variables, whereas the environment variable has the same name 
written in capital letters and the dots replaced by underscores:
```
awsmock.log.level=debug
```
becomes:
```
AWSMOCK_LOG_LEVEL=debug
```

## VARIABLES

The following lists shows all variables in the properties file, the corresponding environment variable and the meaning 
of the variable.

### General variables
```
awsmock.region                          AWSMOCK_REGION                      AWS region
awsmock.account.userPoolId                      AMWSMOCK_ACCOUNT_ID                 AWS account ID, default 000000000000
awsmock.client.userPoolId                       AWSMOCK_CLIENT_ID                   AWS client ID, default 00000000
awsmock.user                            AWSMOCK_USER                        AWS user default none
awsmock.data.dir                        AWSMOCK_DATA_DIR                    AwsMock base data dir
awsmock.pretty                          AWSMOCK_PRETTY                      Pretty print output for XML and JSON
```

### AwsMock manager variables
```
awsmock.manager.host                    AWSMOCK_MANAGER_HOST                manager host, default localhost
awsmock.manager.port                    AWSMOCK_MANAGER_PORT                manager port, default 4567
awsmock.manager.max.queue               AWSMOCK_MANAGER_MAX_QUEUE           manager maximal HTTP queue length, default 250
awsmock.manager.max.threads             AWSMOCK_MANAGER_MAX_THREADS         manager maximal HTTP threads, default 50
```

### AwsMock gateway variables
```
awsmock.service.gateway.active          AWSMOCK_SERVICE_GATEWAY_ACTIVE      activation flag
awsmock.gateway.host                    AWSMOCK_SERVICE_GATEWAY_HOST        gateway host, default localhost
awsmock.gateway.port                    AWSMOCK_SERVICE_GATEWAY_PORT        gateway port, default 4566
awsmock.gateway.max.queue               AWSMOCK_SERVICE_GATEWAY_MAX_QUEUE   gateway maximal queue length, default 250
awsmock.gateway.max.threads             AWSMOCK_SERVICE_GATEWAY_MAX_THREADS gateway maximal threads, default 50
awsmock.gateway.timeout                 AWSMOCK_SERVICE_GATEWAY_TIMEOUT     gateway HTTP request timeout in seconds, default 900
```

### S3 module variables
```
awsmock.service.s3.active               AWSMOCK_SERVICE_S3_ACTIVE           activation flag
awsmock.service.s3.host                 AWSMOCK_SERVICE_S3_HOST             S3 host, default: localhost
awsmock.service.s3.port                 AWSMOCK_SERVICE_S3_PORT             S3 port, default: 9500
awsmock.service.s3.max.queue            AWSMOCK_SERVICE_S3_MAX_QUEUE        S3 maximal queue length, default: 250
awsmock.service.s3.max.threads          AWSMOCK_SERVICE_S3_MAX_THREADS      S3 maximal threads, default: 50
awsmock.service.s3.timeout              AWSMOCK_SERVICE_S3_TIMEOUT          S3 request timeout in seconds, default: 900
awsmock.monitoring.s3.periodq           AWSMOCK_SERVICE_S3_PERIOS           S3 monitoring timeout period in milliseconds, default: 60sec.
```

### SQS module variables
```
awsmock.service.sqs.active              AWSMOCK_SERVICE_SQS_ACTIVE          activation flag
awsmock.service.sqs.host                AWSMOCK_SERVICE_SQS_HOST            SQS host, default: localhost
awsmock.service.sqs.port                AWSMOCK_SERVICE_SQS_PORT            SQS port, default: 9501
awsmock.service.sqs.max.queue           AWSMOCK_SERVICE_SQS_MAX_QUEUE       SQS maximal queue length, default: 250
awsmock.service.sqs.max.threads         AWSMOCK_SERVICE_SQS_MAX_THREADS     SQS maximal threads, default: 50
awsmock.service.sqs.timeout             AWSMOCK_SERVICE_SQS_TIMEOUT         SQS request timeout in seconds, default: 900
awsmock.monitoring.sqs.period           AWSMOCK_SERVICE_SQS_PERIOD          SQS monitoring timeout period in milliseconds, default: 60sec.
```

### SNS module variables
```
awsmock.service.sns.active              AWSMOCK_SERVICE_SNS_ACTIVE          activation flag
awsmock.service.sns.host                AWSMOCK_SERVICE_SNS_HOST            SNS host, default: localhost
awsmock.service.sns.port                AWSMOCK_SERVICE_SNS_PORT            SNS port, default: 9502
awsmock.service.sns.max.queue           AWSMOCK_SERVICE_SNS_MAX_QUEUE       SNS maximal queue length, default: 250
awsmock.service.sns.max.threads         AWSMOCK_SERVICE_SNS_MAX_THREADS     SNS maximal threads, default: 50
awsmock.service.sns.timeout             AWSMOCK_SERVICE_SNS_TIMEOUT         SNS request timeout in seconds, default: 900
awsmock.monitoring.sns.period           AWSMOCK_SERVICE_SNS_PERIOD          SNS monitoring timeout period in milliseconds, default: 60sec.
```

### Lambda module variables  
```
awsmock.service.lambda.active           AWSMOCK_SERVICE_LAMBDA_ACTIVE        activation flag
awsmock.service.lambda.host             AWSMOCK_SERVICE_LAMBDA_HOST          Lambda host, default: localhost
awsmock.service.lambda.port             AWSMOCK_SERVICE_LAMBDA_PORT          Lambda port, default: 9503
awsmock.service.lambda.max.queue        AWSMOCK_SERVICE_LAMBDA_MAX_QUEUE     Lambda maximal queue length, default: 250
awsmock.service.lambda.max.threads      AWSMOCK_SERVICE_LAMBDA_MAX_THREADS   Lambda maximal threads, default: 50
awsmock.service.lambda.timeout          AWSMOCK_SERVICE_LAMBDA_TIMEOUT       Lambda request timeout in seconds, default: 900
awsmock.monitoring.lambda.period        AWSMOCK_SERVICE_LAMBDA_PERIOD        Lambda monitoring timeout period in milliseconds, default: 60sec.
```

### Transfer server module variables
```
awsmock.service.transfer.active         AWSMOCK_SERVICE_TRANSFER_ACTIVE         module activation
awsmock.service.transfer.host           AWSMOCK_SERVICE_TRANSFER_HOST           hostname of the FTP server
awsmock.service.transfer.port           AWSMOCK_SERVICE_TRANSFER_PORT           port for the internal communication
awsmock.service.transfer.max.queue      AWSMOCK_SERVICE_TRANSFER_MAX_QUEUE      maximal queue length, default: 250
awsmock.service.transfer.max.threads    AWSMOCK_SERVICE_TRANSFER_MAX_THREADS    maximal threads, default: 50
awsmock.service.transfer.timeout        AWSMOCK_SERVICE_TRANSFER_TIMEOUT        request timeout in seconds, default: 900
awsmock.service.transfer.ftp.port       AWSMOCK_SERVICE_TRANSFER_FTP_PORT       port for the transfer FTP server, default 2121
awsmock.worker.transfer.period          AWSMOCK_SERVICE_TRANSFER_PERIOD         polling period
awsmock.worker.transfer.bucket          AWSMOCK_SERVICE_TRANSFER_BUCKET         S3 bucket for the transfer server
```

### Cognito module variables
```
awsmock.service.cognito.active          AWSMOCK_SERVICE_COGNITO_ACTIVE          activation flag
awsmock.service.cognito.host            AWSMOCK_SERVICE_COGNITO_HOST            Cognito host, default: localhost
awsmock.service.cognito.port            AWSMOCK_SERVICE_COGNITO_PORT            Cognito port, default: 9503
awsmock.service.cognito.max.queue       AWSMOCK_SERVICE_COGNITO_MAX_QUEUE       Cognito maximal queue length, default: 250
awsmock.service.cognito.max.threads     AWSMOCK_SERVICE_COGNITO_MAX_THREADS     Cognito maximal threads, default: 50
awsmock.service.cognito.timeout         AWSMOCK_SERVICE_COGNITO_TIMEOUT         Cognito request timeout in seconds, default: 900
awsmock.monitoring.cognito.period       AWSMOCK_SERVICE_COGNITO_PERIOD          Cognito monitoring timeout period in milliseconds, default: 60sec.
```

### DynamoDB mofule variables
```
awsmock.service.dynamodb.active          AWSMOCK_SERVICE_DYNAMODB_ACTIVE          activation flag
awsmock.service.dynamodb.host            AWSMOCK_SERVICE_DYNAMODB_HOST            DynamoDB host, default: localhost
awsmock.service.dynamodb.port            AWSMOCK_SERVICE_DYNAMODB_PORT            DynamoDB port, default: 9503
awsmock.service.dynamodb.max.queue       AWSMOCK_SERVICE_DYNAMODB_MAX_QUEUE       DynamoDB maximal queue length, default: 250
awsmock.service.dynamodb.max.threads     AWSMOCK_SERVICE_DYNAMODB_MAX_THREADS     DynamoDB maximal threads, default: 50
awsmock.service.dynamodb.timeout         AWSMOCK_SERVICE_DYNAMODB_TIMEOUT         DynamoDB request timeout in seconds, default: 900
awsmock.monitoring.dynamodb.period       AWSMOCK_SERVICE_DYNAMODB_PERIOD          DynamoDB monitoring timeout period in milliseconds, default: 60sec.
```

## EXAMPLES

To switch of the database support:
```
export AWSMOCK_MONGODB_ACTIVE=false
/usr/bin/awsmockmgr --config ./awsmock-properties
```
this will take the value from the given properties file, but the log level will be overwritten by the environment 
variable. Finally, the log level will be set to ```debug```.

## AUTHOR

Jens Vogt <jens.vogt@opitz-consulting.com>

## VERSION
0.5.210

## BUGS

Bugs and enhancement requests can be reported and filed at https://github.com/jensvogt/aws-mock/issues

## SEE ALSO

```awsmockctl(1)```, ```awsmockmgr(1)```, ```awslocal(1)```, ```awsmocks3(1)```, ```awsmocksqs(1)```, ```awsmocksns(1)```,
```awsmocklambda(1)```, ```awsmockdynamodb(1)```, ```awsmockcognito(1)```, ```awsmocktransfer(1)```, 
```awsmocksecretsmanager(1)```
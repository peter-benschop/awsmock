---
title: awsmockctl(1)
section: 1
header: awsmockctl AwsMock Controller
footer: awsmockctl 0.5.210
date: December 18, 2023
---

## NAME
```awsmockctl``` AwsMock controller

## SYNOPSIS
awsmockctl [OPTIONS] [COMMAND]

## DESCRIPTION
awsmockctl controls and show some insides of the AwsMock AWS cloud simulation. Supported AWS modules are: SQS, SNS
S3, Cognito, TransferServer, Lambda. AwsMock is written in C++ and has a module structure, using different modules for
each AWS service plus a API gateway, which routes the requests to the different modules.

Per default the gateway runs on port 4566, but can be changed in the configuration file. The default configuration file
```/etc/aws-mock.properties```, which can be changed on the command using the ```--config <config-file-path>``` option.

awsmockctl provides a series of commands, which control the different modules. It allows to start/stop different modules
as well as to show the current configuration.

## OPTIONS

```--config <config-file-path>```:  
&nbsp;&nbsp;&nbsp;&nbsp;starts the controller with a given configuration file. Per default the configuration file ```/etc/aws-mock.properties``` will 
be used. The path should be the absolute path to the configuration file.

```--help```    
&nbsp;&nbsp;&nbsp;&nbsp;shows the usage screen and exists

```--version```    
&nbsp;&nbsp;&nbsp;&nbsp;shows the current version and exists.

## COMMANDS

```list```  
&nbsp;&nbsp;&nbsp;&nbsp;lists the currently running AwsMock modules like S3, SQS, SNS etc. Each line has the format:
```
SQS         RUNNING
SNS         STOPPED
...
```

```stop <module>```  
&nbsp;&nbsp;&nbsp;&nbsp;stops the given module. Modules are S3, SQS, SNS, Transfer, Cognito. Modules names can be given case-insensitive.

```start <module>```  
&nbsp;&nbsp;&nbsp;&nbsp;starts the given module.

```restart <module>```  
&nbsp;&nbsp;&nbsp;&nbsp;restarts the given module.

```logs```  
&nbsp;&nbsp;&nbsp;&nbsp;shows the console logs of the AwsMock manager application ```awsmockmgr```. See ```awsmockmgr(1)``` for 
details of the manager.

```loglevel```  
&nbsp;&nbsp;&nbsp;&nbsp;sets the log level of the AwsMock manager ```awsmockmgr```. ```<loglevel>``` can be one of: 
trace, debug, information, warning, error, critical or fatal.

```config```  
&nbsp;&nbsp;&nbsp;&nbsp;shows the configuration of the AwsMock API gateway.

```export [modules]```  
&nbsp;&nbsp;&nbsp;&nbsp;export the current infrastructure to stdout in JSON format. ```modules``` can be space separated
list of AwsMock modules. If no modules are given or the module list contains ```all```, all modules will be exported.

```import```  
&nbsp;&nbsp;&nbsp;&nbsp;import the infrastructure from stdin in JSON format.

```clean```  
&nbsp;&nbsp;&nbsp;&nbsp;cleans the infrastructure. This means all SQS queues plus messages, SNS topics plus messages, S3 
buckets with all objects, transfer servers, and lambda functions will be deleted. ALl modules will be still running, but
all AwsMock objects will be emptied

## EXAMPLES

In oder to show the current running modules:
```
/usr/bin/awsmockctl list
SQS         RUNNING
SNS         RUNNING
S3          RUNNING
```

Stop the SNS module:
```
/usr/bin/awsmockctl stop SNS
/usr/bin/awsmockctl list
SQS         RUNNING
SNS         STOPPED
S3          RUNNING
```

Start the SNS module:
```
/usr/bin/awsmockctl start SNS
/usr/bin/awsmockctl list
SQS         RUNNING
SNS         RUNNING
S3          RUNNING
```

Show the manager logs
```
/usr/bin/awsmockctl logs
08-11-2023 20:02:58.800 [I] 125 S3ServiceHandler:57 - Requested multipart download range: 9667870720-9673113599
10-11-2023 13:31:57.053 [T] 55 AbstractHandler:559 - Getting header values, name: RequestId
10-11-2023 14:19:51.902 [T] 17 SNSServer:94 - Queue updated, nametextannotation-result-queue
10-11-2023 15:11:42.215 [T] 17 SQSDatabase:266 - Message reset, visibility: 30 updated: 0 queue: http://localhost:4566/000000000000/ftp-file-distribution-image-dlqueue
10-11-2023 16:05:42.347 [T] 17 SQSDatabase:331 - Count messages, region: eu-central-1 url: http://localhost:4566/000000000000/ftp-file-distribution-vlb-preisreferenz-queue result: 0
10-11-2023 16:56:51.429 [T] 17 SNSServer:94 - Queue updated, nametextannotation-result-queue
```

Export the S3 infrastructure:
```
/usr/bin/awsmockctl export s3 sqs
{
    "infrastructure": {
     "s3-buckets": [
            {
                "name": "transfer-server",
                "notifications": [
                    {
                        "event": "s3:ObjectCreated:Put",
                        "lambdaArn": "arn:aws:lambda:eu-central-1:000000000000:function:ftp-file-copy",
                        "notificationId": "1234567890123",
                        "queueArn": ""
                    },
                    ....
```

Export the S3 infrastructure to a file ```infrastrcture.json```:
```
/usr/bin/awsmockctl export s3 sqs > infrastrcture.json
```

## AUTHOR

Jens Vogt <jens.vogt@opitz-consulting.com>

## VERSION
0.5.210

## BUGS

Bugs and enhancement requests can be reported and filed at https://github.com/jensvogt/aws-mock/issues

## SEE ALSO

```awsmockmgr(1)```, ```awsmocksqs(1)```, ```awslocal(1)```, ```awsmocksqs(1)```, ```awsmocksns(1)```, ```awsmocklambda(1)```,
```awsmockdynamodb(1)```, ```awsmockcognito(1)```, ```awsmocktransfer(1)```, ```awsmocksecretsmanager(1)```
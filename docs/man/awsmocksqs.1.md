---
title: awsmocksqs(1)
section: 1
header: awsmocksqs AwsMock SQS module
footer: awsmocksqs VERSION_STRING
date: December 18, 2023
---

## NAME
```awsmocksqs``` AwsMock SQS module

## DESCRIPTION
Simple Queue Service (SQS) is a managed messaging service offered by AWS. It allows you to decouple different components
of your applications by enabling asynchronous communication through message queues. SQS allows you to reliably send, store,
and receive messages with support for standard and FIFO queues.

AwsMock allows you to use the SQS APIs in your local environment to integrate and decouple distributed systems via
hosted queues. The supported APIs are available on our API coverage page, which provides information on the extent of
SQS’s integration with AwsMock.

The SQS module can be configured using the ```awslocal``` command. For details of the ```awslocal``` command see the 
corresponding man page ```awslocal(1)```.

## COMMANDS

```"awslocal sqs create-queue --queue-name <queue-name>```
&nbsp;&nbsp;&nbsp;&nbsp;creates a new queue

## EXAMPLES

To get a list of all currently available quques:
```
/usr/bin/awslocal sqs list-queues"
{
    "QueueUrls": [
        "http://localhost:4566/000000000000/test-dlqueue",
        "http://localhost:4566/000000000000/test-queue-queue",
        "http://localhost:4566/000000000000/test-result-dlqueue",
        "http://localhost:4566/000000000000/test-result-queue",
        ...
}
```

To get a list of all SQS queue attributes:
```
/usr/bin/awslocal sqs get-queue-attributes --queue-url http://localhost:4566/000000000000/test-queue --attribute-name All
{
    "Attributes": {
        "ApproximateNumberOfMessages": "0",
        "ApproximateNumberOfMessagesDelayed": "0",
        "ApproximateNumberOfMessagesNotVisible": "0",
        "CreatedTimestamp": "1702377771",
        "DelaySeconds": "0",
        "LastModifiedTimestamp": "1702377771",
        "MaximumMessageSize": "262144",
        "MessageRetentionPeriod": "345600",
        "Policy": "",
        "QueueArn": "arn:aws:sqs:eu-central-1:000000000000:test-queue",
        "ReceiveMessageWaitTimeSeconds": "20",
        "VisibilityTimeout": "30"
    }
}
```

## AUTHOR

Jens Vogt <jens.vogt@opitz-consulting.com>

## VERSION
&nbsp;&nbsp;&nbsp;&nbsp; VERSION_STRING

## BUGS

Bugs and enhancement requests can be reported and filed at https://github.com/jensvogt/aws-mock/issues

## SEE ALSO

```awsmockctl(1)```, ```awsmockmgr(1)```, ```awslocal(1)```
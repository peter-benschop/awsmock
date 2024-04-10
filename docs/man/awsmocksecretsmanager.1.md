---
title: awsmockdynamodb(1)
section: 1
header: awsmockdynamodb AwsMock DynamoDB module
footer: awsmockdynamodb 0.5.167
date: December 18, 2023
---

## NAME
```awsmocksecretsmanager``` AwsMock Secrets Manager module

## DESCRIPTION
AWS Secrets Manager helps you manage, retrieve, and rotate database credentials, application credentials, OAuth tokens, 
API keys, and other secrets throughout their lifecycles. Many AWS services store and use secrets in Secrets Manager.

Secrets Manager helps you improve your security posture, because you no longer need hard-coded credentials in application
source code. Storing the credentials in Secrets Manager helps avoid possible compromise by anyone who can inspect your 
application or the components. You replace hard-coded credentials with a runtime call to the Secrets Manager service 
to retrieve credentials dynamically when you need them.

With Secrets Manager, you can configure an automatic rotation schedule for your secrets. This enables you to replace 
long-term secrets with short-term ones, significantly reducing the risk of compromise. Since the credentials are no 
longer stored with the application, rotating credentials no longer requires updating your applications and deploying 
changes to application clients.

The SecretManager module can be configured using the ```awslocal``` command. For details of the ```awslocal``` command 
see the corresponding man page ```awslocal(1)```.

## COMMANDS

```awslocal secretsmanager create-secret <name>```  
&nbsp;&nbsp;&nbsp;&nbsp;creates a new secret.

```awslocal dynamodb delete-secret --secret-userPoolId```  
&nbsp;&nbsp;&nbsp;&nbsp;deletes a secret

## EXAMPLES

To create a new secret:
```
awslocal secretmanager create-secret --name test-table
{
    "ARN": "arn:aws:secretsmanager:eu-central-1:000000000000:secret:test-4f5h1d",
    "Name": "test",
    "VersionId": "c7ebfa48-1f4e-47af-830e-261d12b72e35"
}
```

To delete a secret:
```
awslocal secretmanager delete-secret --secret-userPoolId test-4f5h1d
```

## AUTHOR

Jens Vogt <jens.vogt@opitz-consulting.com>

## VERSION
0.5.267

## BUGS

Bugs and enhancement requests can be reported and filed at https://github.com/jensvogt/aws-mock/issues

## SEE ALSO

```awsmockctl(1)```, ```awsmockmgr(1)```, ```awslocal(1)```, ```awsmocks3(1)```, ```awsmocksqs(1)```, ```awsmocksns(1)```, 
```awsmocklambda(1)```, ```awsmockdynamodb(1)```, ```awsmockcognito(1)```, ```awsmocktransfer(1)```
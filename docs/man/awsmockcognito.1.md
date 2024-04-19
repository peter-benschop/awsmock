---
title: awsmockcognito(1)
section: 1
header: awsmockcognito AwsMock Cognito module
footer: awsmockcognito 0.5.210
date: December 22, 2023
---

## NAME
```awsmockcognito``` AwsMock Cognito module

## DESCRIPTION
Cognito is a managed identity service provided by AWS that is used for securing user authentication, authorization, and 
managing user identities in web and mobile applications. Cognito enables developers to add user sign-up, sign-in, and 
access control functionalities to their applications. Cognito supports various authentication methods, including social 
identity providers, SAML-based identity providers, and custom authentication flows.

AwsMock supports Cognito, allowing you to use the Cognito APIs in your local environment to manage authentication and 
access control for your local application and resources. The supported APIs are available on our Cognito Identity 
coverage page and Cognito User Pools coverage page, which provides information on the extent of Cognito’s integration 
with AwsMock.

The Cognito module can be configured using the ```awslocal``` command. For details of the ```awslocal``` command see the 
corresponding man page ```awslocal(1)```.

## COMMANDS

```awslocal cognito-idp create-user-pool --pool-name <user-pool-name>```  
&nbsp;&nbsp;&nbsp;&nbsp;creates a new Cognito user pool.

```awslocal cognito-idp list-user-pools```  
&nbsp;&nbsp;&nbsp;&nbsp;lists all available Cognito user pools.

```awslocal cognito-idp user-pool --user-pool-userPoolId <user-pool-userPoolId>```  
&nbsp;&nbsp;&nbsp;&nbsp;delete a Cognito user pool.

## EXAMPLES

To create a new Cognito user pools:
```
awslocal cognito-idp create-function --create-user-pool --pool-name test-user-pool
```

To get a list of all currently available Cognito user pools:
```
awslocal cognito-idp list-user-pools --max-results 10
{
    "UserPools": [
        {
            "Id": "eu-central-1_6g67LGPzz",
            "Name": "test-user-pool",
            "LastModifiedDate": "2023-12-22T17:40:26+01:00",
            "CreationDate": "2023-12-22T17:40:26+01:00"
        }
    ]
}
```

To delete a Cognito user pool:
```
awslocal cognito-idp delete-user-pool --user-pool-userPoolId eu-central-1_6g67LGPzz
```

## AUTHOR

Jens Vogt <jens.vogt@opitz-consulting.com>

## VERSION
0.5.210

## BUGS

Bugs and enhancement requests can be reported and filed at https://github.com/jensvogt/aws-mock/issues

## SEE ALSO

```awsmockctl(1)```, ```awsmockmgr(1)```, ```awslocal(1)```, ```awsmocks3(1)```, ```awsmocksqs(1)```, ```awsmocksns(1)```,
```awsmockdynamodb(1)```, ```awsmockcognito(1)```, ```awsmocktransfer(1)```, ```awsmocksecretsmanager(1)```
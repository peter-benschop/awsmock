---
title: awsmocktransfer(1)
section: 1
version: 1.0.1
builddate: 1.0.1
date: $builddate$
header: awsmocktransfer AwsMock Transfer Server module
footer: awsmocktransfer $version$
---

## NAME

```awsmocktransfer``` AwsMock Transfer Server module

## DESCRIPTION

The AWS Transfer API is a powerful tool that empowers users to establish FTP(S) servers with ease. These servers serve
as gateways, allowing direct access to files residing in Amazon S3 buckets. This functionality streamlines file
management processes, making it simpler and more efficient to handle data stored in S3 by providing a familiar FTP
interface for users to interact with their files securely. Whether you’re looking to facilitate file transfers or
enhance your data access capabilities, the AWS Transfer API simplifies the process and extends the versatility of
your cloud storage infrastructure.

The SQS module can be configured using the ```awslocal``` command. For details of the ```awslocal``` command see the
corresponding man page ```awslocal(1)```.

## COMMANDS

```awslocal transfer create-server --protocols <protocols>```  
&nbsp;&nbsp;&nbsp;&nbsp;creates a new transfer server

```awslocal transfer list-servers```  
&nbsp;&nbsp;&nbsp;&nbsp;lists all available transfer servers

```awslocal transfer list-users```  
&nbsp;&nbsp;&nbsp;&nbsp;lists all available transfer servers

```awslocal transfer delete-server --server-id <server-id>```  
&nbsp;&nbsp;&nbsp;&nbsp;deletes a transfer server

## EXAMPLES

To create a new transfer server:

```
awslocal transfer create-server --protocols ftp
{
    "ServerId": "s-27134679b31c0a9833ee"
}
```

To get a list of all currently available transfer servers:

```
awslocal transfer list-servers
{
    "Servers": [
        {
            "Arn": "arn:aws:transfer:eu-central-1:000000000000:manager/s-27134679b31c0a9833ee",
            "Domain": "",
            "IdentityProviderType": "",
            "EndpointType": "",
            "LoggingRole": "",
            "ServerId": "s-27134679b31c0a9833ee",
            "State": "OFFLINE",
            "UserCount": 1
        }
    ]
}

```

To delete a transfer server:

```
awslocal transfer delete-server --server-userPoolId s-27134679b31c0a9833ee
```

Show a list of all users

```
{
    "Users": [
        {
            "Arn": "arn:aws:transfer:us-east-1:176354371281:user/s-27134679b31c0a9833ee/anonymous",
            "HomeDirectory": "/",
            "Role": "anonymous",
            "SshPublicKeyCount": 0,
            "UserName": "anonymous"
        },
        {
            "Arn": "arn:aws:transfer:us-east-1:176354371281:user/s-27134679b31c0a9833ee/ftpuser1",
            "HomeDirectory": "ftpuser1",
            "Role": "user",
            "SshPublicKeyCount": 0,
            "UserName": "ftpuser1"
        }
    ],
    "ServerId": ""
}
```

## AUTHOR

Jens Vogt <jens.vogt@opitz-consulting.com>

## VERSION

$version$ ($builddate$)

## BUGS

Bugs and enhancement requests can be reported and filed at https://github.com/jensvogt/aws-mock/issues

## SEE ALSO

```awsmockctl(1)```, ```awsmockmgr(1)```, ```awslocal(1)```, ```awsmocks3(1)```, ```awsmocksns(1)```, ```awsmocklambda(1)```,
```awsmockdynamodb(1)```, ```awsmockcognito(1)```, ```awsmocksecretsmanager(1)```, ```awsmocksqs(1)```, ```awsmockkms(1)```
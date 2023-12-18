---
title: awsmocks3(1)
section: 1
header: awsmocks3 AwsMock S3 module
footer: awsmocks3 0.5.154
date: December 18, 2023
---

## NAME
```awsmocks3``` AwsMock S3 module

## DESCRIPTION
S3 (Simple Storage Service) is an object storage service that provides a highly scalable and durable solution for 
storing and retrieving data. In S3, a bucket represents a directory, while an object corresponds to a file. Each object 
or file within S3 encompasses essential attributes such as a unique key denoting its name, the actual content it holds, 
a version ID for versioning support, and accompanying metadata. S3 can store unlimited objects, allowing you to store, 
retrieve, and manage your data in a highly adaptable and reliable manner.

AwsMock supports S3, allowing you to use the S3 APIs in your local environment to create new buckets, manage your S3 
objects, and test your S3 configurations locally. The supported APIs are available in the example section, which 
provides information on the extent of S3’s integration with AwsMock.

The S3 module can be configured using the ```awslocal``` command. For details of the ```awslocal``` command see the 
corresponding man page ```awslocal(1)```.

## COMMANDS

```awslocal s3 mb s3://test-bucket```  
&nbsp;&nbsp;&nbsp;&nbsp;creates a new bucket

```awslocal s3 rm s3://test-bucket```  
&nbsp;&nbsp;&nbsp;&nbsp;removes an existing bucket

```awslocal s3 ls```  
&nbsp;&nbsp;&nbsp;&nbsp;list all available buckets

```awslocal s3 ls s3://test-bucket --recursive```  
&nbsp;&nbsp;&nbsp;&nbsp;recursively lists all objects in the bucket

## EXAMPLES

To get a list of all currently available buckets:
```
awslocal s3 ls
2023-12-11 17:37:08 test-bucket-1
2023-12-11 17:37:08 test-bucket-2
2023-12-11 17:37:08 test-result-bucket-1
2023-12-11 17:37:08 test-result-bucket-2
```

To upload a local file to a S3 bucket ```s3://test-bucket-1```
```
awslocal s3 cp README.md s3://test-bucket-1/test/README.md
```

To get a list of all S3 objects in the ```s3://test-bucket-1```
```
awslocal s3 ls s3://test-bucket-1 --recursive
2023-12-16 16:01:41       6248 test/README.md
```

To download a S3 object from a S3 bucket ```s3://test-bucket-1```
```
awslocal s3 cp s3://test-bucket-1/test/README.md test.md
```

## AUTHOR

Jens Vogt <jens.vogt@opitz-consulting.com>

## VERSION
&nbsp;&nbsp;&nbsp;&nbsp; 0.5.154

## BUGS

Bugs and enhancement requests can be reported and filed at https://github.com/jensvogt/aws-mock/issues

## SEE ALSO

```awsmockctl(1)```, ```awsmockmgr(1)```, ```awslocal(1)```
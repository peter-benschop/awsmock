---
title: awsmockcfg(1)
section: 1
header: awsmockcfg AwsMock configuration
footer: awsmockcfg 0.5.154
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
&nbsp;&nbsp;&nbsp;&nbsp; 0.5.154

## BUGS

Bugs and enhancement requests can be reported and filed at https://github.com/jensvogt/aws-mock/issues

## SEE ALSO

```awsmockctl(1)```, ```awsmockmgr(1)```, ```awslocal(1)```, ```awsmocks3(1)```
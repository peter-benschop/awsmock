import {HttpHeaders} from "./chunk-LGOS2CJL.js";

// src/app/services/awsmock-http-config.ts
var S3Config = class {
    constructor() {
        this.s3HttpOptions = {
            headers: new HttpHeaders({
                "Content-Type": "application/json",
                "Authorization": "AWS4-HMAC-SHA256 Credential=none/20240928/eu-central-1/s3/aws4_request, SignedHeaders=content-type;host;x-amz-date;x-amz-security-token;x-amz-target, Signature=01316d694335ec0e0bf68b08570490f1b0bae0b130ecbe13ebad511b3ece8a41"
            })
        };
    }
};
var SnsConfig = class {
    constructor() {
        this.snsHttpOptions = {
            headers: new HttpHeaders({
                "Content-Type": "application/json",
                "Authorization": "AWS4-HMAC-SHA256 Credential=none/20240928/eu-central-1/sns/aws4_request, SignedHeaders=content-type;host;x-amz-date;x-amz-security-token;x-amz-target, Signature=01316d694335ec0e0bf68b08570490f1b0bae0b130ecbe13ebad511b3ece8a41"
            })
        };
    }
};
var SqsConfig = class {
    constructor() {
        this.sqsHttpOptions = {
            headers: new HttpHeaders({
                "Content-Type": "application/json",
                "Authorization": "AWS4-HMAC-SHA256 Credential=none/20240928/eu-central-1/sqs/aws4_request, SignedHeaders=content-type;host;x-amz-date;x-amz-security-token;x-amz-target, Signature=01316d694335ec0e0bf68b08570490f1b0bae0b130ecbe13ebad511b3ece8a41"
            })
        };
    }
};
var CognitoConfig = class {
    constructor() {
        this.cognitoOptions = {
            headers: new HttpHeaders({
                "Content-Type": "application/json",
                "Authorization": "AWS4-HMAC-SHA256 Credential=none/20240928/eu-central-1/cognito-idp/aws4_request, SignedHeaders=content-type;host;x-amz-date;x-amz-security-token;x-amz-target, Signature=01316d694335ec0e0bf68b08570490f1b0bae0b130ecbe13ebad511b3ece8a41"
            })
        };
    }
};
var MonitoringConfig = class {
    constructor() {
        this.monitoringHttpOptions = {
            headers: new HttpHeaders({
                "Content-Type": "application/json",
                "Authorization": "AWS4-HMAC-SHA256 Credential=none/20240928/eu-central-1/monitoring/aws4_request, SignedHeaders=content-type;host;x-amz-date;x-amz-security-token;x-amz-target, Signature=01316d694335ec0e0bf68b08570490f1b0bae0b130ecbe13ebad511b3ece8a41"
            })
        };
    }
};
var ManagerConfig = class {
    constructor() {
        this.managerHttpOptions = {
            headers: new HttpHeaders({
                "Content-Type": "application/json"
            })
        };
    }
};

export {
    S3Config,
    SnsConfig,
    SqsConfig,
    CognitoConfig,
    MonitoringConfig,
    ManagerConfig
};
//# sourceMappingURL=chunk-4IO3RYFH.js.map

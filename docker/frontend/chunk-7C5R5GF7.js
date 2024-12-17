import {Md5} from "./chunk-4VAYYVT5.js";
import {loadRestJsonErrorCode, parseJsonBody, parseJsonErrorBody} from "./chunk-HK7D4W5I.js";
import {
    _json,
    awsEndpointFunctions,
    AwsSdkSigV4Signer,
    calculateBodyLength,
    Client,
    collectBody,
    Command,
    createDefaultUserAgentProvider,
    customEndpointFunctions,
    decorateServiceException,
    DEFAULT_MAX_ATTEMPTS,
    DEFAULT_RETRY_MODE,
    DEFAULT_USE_DUALSTACK_ENDPOINT,
    DEFAULT_USE_FIPS_ENDPOINT,
    DefaultIdentityProviderConfig,
    EndpointCache,
    FetchHttpHandler,
    fromBase64,
    fromUtf8,
    getAwsRegionExtensionConfiguration,
    getContentLengthPlugin,
    getDefaultExtensionConfiguration,
    getEndpointPlugin,
    getHostHeaderPlugin,
    getHttpAuthSchemeEndpointRuleSetPlugin,
    getHttpHandlerExtensionConfiguration,
    getHttpSigningPlugin,
    getLoggerPlugin,
    getRecursionDetectionPlugin,
    getRetryPlugin,
    getSerdePlugin,
    getSmithyContext,
    getUserAgentPlugin,
    HttpRequest,
    invalidProvider,
    loadConfigsForDefaultMode,
    NoOpLogger,
    normalizeProvider,
    parseUrl,
    resolveAwsRegionExtensionConfiguration,
    resolveAwsSdkSigV4Config,
    resolveDefaultRuntimeConfig,
    resolveDefaultsModeConfig,
    resolveEndpoint,
    resolveEndpointConfig,
    resolveHostHeaderConfig,
    resolveHttpHandlerRuntimeConfig,
    resolveRegionConfig,
    resolveRetryConfig,
    resolveUserAgentConfig,
    ServiceException,
    Sha256,
    streamCollector,
    take,
    toBase64,
    toHex,
    toUint8Array,
    toUtf8,
    withBaseException
} from "./chunk-5F2IFVYA.js";
import {environment, HttpClient, HttpHeaders} from "./chunk-LGOS2CJL.js";
import {__async, __spreadProps, __spreadValues} from "./chunk-G42SKTPL.js";

// node_modules/@aws-sdk/middleware-sdk-sqs/dist-es/queue-url.js
var resolveQueueUrlConfig = (config) => {
    return __spreadProps(__spreadValues({}, config), {
        useQueueUrlAsEndpoint: config.useQueueUrlAsEndpoint ?? true
    });
};

function queueUrlMiddleware({
                                useQueueUrlAsEndpoint,
                                endpoint
                            }) {
    return (next, context) => {
        return (args) => __async(this, null, function* () {
            const {
                input
            } = args;
            const resolvedEndpoint = context.endpointV2;
            if (!endpoint && input.QueueUrl && resolvedEndpoint && useQueueUrlAsEndpoint) {
                const logger = context.logger instanceof NoOpLogger || !context.logger?.warn ? console : context.logger;
                try {
                    const queueUrl = new URL(input.QueueUrl);
                    const queueUrlOrigin = new URL(queueUrl.origin);
                    if (resolvedEndpoint.url.origin !== queueUrlOrigin.origin) {
                        logger.warn(`QueueUrl=${input.QueueUrl} differs from SQSClient resolved endpoint=${resolvedEndpoint.url.toString()}, using QueueUrl host as endpoint.
Set [endpoint=string] or [useQueueUrlAsEndpoint=false] on the SQSClient.`);
                        context.endpointV2 = __spreadProps(__spreadValues({}, resolvedEndpoint), {
                            url: queueUrlOrigin
                        });
                    }
                } catch (e2) {
                    logger.warn(e2);
                }
            }
            return next(args);
        });
    };
}

var queueUrlMiddlewareOptions = {
    name: "queueUrlMiddleware",
    relation: "after",
    toMiddleware: "endpointV2Middleware",
    override: true
};
var getQueueUrlPlugin = (config) => ({
    applyToStack: (clientStack) => {
        clientStack.addRelativeTo(queueUrlMiddleware(config), queueUrlMiddlewareOptions);
    }
});

// node_modules/@aws-sdk/middleware-sdk-sqs/dist-es/send-message.js
var sendMessageMiddleware = (options) => (next) => (args) => __async(void 0, null, function* () {
    const resp = yield next(__spreadValues({}, args));
    if (options.md5 === false) {
        return resp;
    }
    const output = resp.output;
    const hash = new options.md5();
    hash.update(toUint8Array(args.input.MessageBody || ""));
    if (output.MD5OfMessageBody !== toHex(yield hash.digest())) {
        throw new Error("InvalidChecksumError");
    }
    return resp;
});
var sendMessageMiddlewareOptions = {
    step: "initialize",
    tags: ["VALIDATE_BODY_MD5"],
    name: "sendMessageMiddleware",
    override: true
};
var getSendMessagePlugin = (config) => ({
    applyToStack: (clientStack) => {
        clientStack.add(sendMessageMiddleware(config), sendMessageMiddlewareOptions);
    }
});

// node_modules/@aws-sdk/core/dist-es/submodules/protocols/coercing-serializers.js
var _toStr = (val) => {
    if (val == null) {
        return val;
    }
    if (typeof val === "number" || typeof val === "bigint") {
        const warning = new Error(`Received number ${val} where a string was expected.`);
        warning.name = "Warning";
        console.warn(warning);
        return String(val);
    }
    if (typeof val === "boolean") {
        const warning = new Error(`Received boolean ${val} where a string was expected.`);
        warning.name = "Warning";
        console.warn(warning);
        return String(val);
    }
    return val;
};
var _toNum = (val) => {
    if (val == null) {
        return val;
    }
    if (typeof val === "boolean") {
    }
    if (typeof val === "string") {
        const num = Number(val);
        if (num.toString() !== val) {
            const warning = new Error(`Received string "${val}" where a number was expected.`);
            warning.name = "Warning";
            console.warn(warning);
            return val;
        }
        return num;
    }
    return val;
};

// node_modules/@aws-sdk/client-sqs/dist-es/auth/httpAuthSchemeProvider.js
var defaultSQSHttpAuthSchemeParametersProvider = (config, context, input) => __async(void 0, null, function* () {
    return {
        operation: getSmithyContext(context).operation,
        region: (yield normalizeProvider(config.region)()) || (() => {
            throw new Error("expected `region` to be configured for `aws.auth#sigv4`");
        })()
    };
});

function createAwsAuthSigv4HttpAuthOption(authParameters) {
    return {
        schemeId: "aws.auth#sigv4",
        signingProperties: {
            name: "sqs",
            region: authParameters.region
        },
        propertiesExtractor: (config, context) => ({
            signingProperties: {
                config,
                context
            }
        })
    };
}

var defaultSQSHttpAuthSchemeProvider = (authParameters) => {
    const options = [];
    switch (authParameters.operation) {
        default: {
            options.push(createAwsAuthSigv4HttpAuthOption(authParameters));
        }
    }
    return options;
};
var resolveHttpAuthSchemeConfig = (config) => {
    const config_0 = resolveAwsSdkSigV4Config(config);
    return __spreadValues({}, config_0);
};

// node_modules/@aws-sdk/client-sqs/dist-es/endpoint/EndpointParameters.js
var resolveClientEndpointParameters = (options) => {
    return __spreadProps(__spreadValues({}, options), {
        useDualstackEndpoint: options.useDualstackEndpoint ?? false,
        useFipsEndpoint: options.useFipsEndpoint ?? false,
        defaultSigningName: "sqs"
    });
};
var commonParams = {
    UseFIPS: {
        type: "builtInParams",
        name: "useFipsEndpoint"
    },
    Endpoint: {
        type: "builtInParams",
        name: "endpoint"
    },
    Region: {
        type: "builtInParams",
        name: "region"
    },
    UseDualStack: {
        type: "builtInParams",
        name: "useDualstackEndpoint"
    }
};

// node_modules/@aws-sdk/client-sqs/package.json
var package_default = {
    name: "@aws-sdk/client-sqs",
    description: "AWS SDK for JavaScript Sqs Client for Node.js, Browser and React Native",
    version: "3.693.0",
    scripts: {
        build: "concurrently 'yarn:build:cjs' 'yarn:build:es' 'yarn:build:types'",
        "build:cjs": "node ../../scripts/compilation/inline client-sqs",
        "build:es": "tsc -p tsconfig.es.json",
        "build:include:deps": "lerna run --scope $npm_package_name --include-dependencies build",
        "build:types": "tsc -p tsconfig.types.json",
        "build:types:downlevel": "downlevel-dts dist-types dist-types/ts3.4",
        clean: "rimraf ./dist-* && rimraf *.tsbuildinfo",
        "extract:docs": "api-extractor run --local",
        "generate:client": "node ../../scripts/generate-clients/single-service --solo sqs"
    },
    main: "./dist-cjs/index.js",
    types: "./dist-types/index.d.ts",
    module: "./dist-es/index.js",
    sideEffects: false,
    dependencies: {
        "@aws-crypto/sha256-browser": "5.2.0",
        "@aws-crypto/sha256-js": "5.2.0",
        "@aws-sdk/client-sso-oidc": "3.693.0",
        "@aws-sdk/client-sts": "3.693.0",
        "@aws-sdk/core": "3.693.0",
        "@aws-sdk/credential-provider-node": "3.693.0",
        "@aws-sdk/middleware-host-header": "3.693.0",
        "@aws-sdk/middleware-logger": "3.693.0",
        "@aws-sdk/middleware-recursion-detection": "3.693.0",
        "@aws-sdk/middleware-sdk-sqs": "3.693.0",
        "@aws-sdk/middleware-user-agent": "3.693.0",
        "@aws-sdk/region-config-resolver": "3.693.0",
        "@aws-sdk/types": "3.692.0",
        "@aws-sdk/util-endpoints": "3.693.0",
        "@aws-sdk/util-user-agent-browser": "3.693.0",
        "@aws-sdk/util-user-agent-node": "3.693.0",
        "@smithy/config-resolver": "^3.0.11",
        "@smithy/core": "^2.5.2",
        "@smithy/fetch-http-handler": "^4.1.0",
        "@smithy/hash-node": "^3.0.9",
        "@smithy/invalid-dependency": "^3.0.9",
        "@smithy/md5-js": "^3.0.9",
        "@smithy/middleware-content-length": "^3.0.11",
        "@smithy/middleware-endpoint": "^3.2.2",
        "@smithy/middleware-retry": "^3.0.26",
        "@smithy/middleware-serde": "^3.0.9",
        "@smithy/middleware-stack": "^3.0.9",
        "@smithy/node-config-provider": "^3.1.10",
        "@smithy/node-http-handler": "^3.3.0",
        "@smithy/protocol-http": "^4.1.6",
        "@smithy/smithy-client": "^3.4.3",
        "@smithy/types": "^3.7.0",
        "@smithy/url-parser": "^3.0.9",
        "@smithy/util-base64": "^3.0.0",
        "@smithy/util-body-length-browser": "^3.0.0",
        "@smithy/util-body-length-node": "^3.0.0",
        "@smithy/util-defaults-mode-browser": "^3.0.26",
        "@smithy/util-defaults-mode-node": "^3.0.26",
        "@smithy/util-endpoints": "^2.1.5",
        "@smithy/util-middleware": "^3.0.9",
        "@smithy/util-retry": "^3.0.9",
        "@smithy/util-utf8": "^3.0.0",
        tslib: "^2.6.2"
    },
    devDependencies: {
        "@tsconfig/node16": "16.1.3",
        "@types/node": "^16.18.96",
        concurrently: "7.0.0",
        "downlevel-dts": "0.10.1",
        rimraf: "3.0.2",
        typescript: "~4.9.5"
    },
    engines: {
        node: ">=16.0.0"
    },
    typesVersions: {
        "<4.0": {
            "dist-types/*": [
                "dist-types/ts3.4/*"
            ]
        }
    },
    files: [
        "dist-*/**"
    ],
    author: {
        name: "AWS SDK for JavaScript Team",
        url: "https://aws.amazon.com/javascript/"
    },
    license: "Apache-2.0",
    browser: {
        "./dist-es/runtimeConfig": "./dist-es/runtimeConfig.browser"
    },
    "react-native": {
        "./dist-es/runtimeConfig": "./dist-es/runtimeConfig.native"
    },
    homepage: "https://github.com/aws/aws-sdk-js-v3/tree/main/clients/client-sqs",
    repository: {
        type: "git",
        url: "https://github.com/aws/aws-sdk-js-v3.git",
        directory: "clients/client-sqs"
    }
};

// node_modules/@aws-sdk/client-sqs/dist-es/endpoint/ruleset.js
var u = "required";
var v = "fn";
var w = "argv";
var x = "ref";
var a = true;
var b = "isSet";
var c = "booleanEquals";
var d = "error";
var e = "endpoint";
var f = "tree";
var g = "PartitionResult";
var h = "getAttr";
var i = {
    [u]: false,
    "type": "String"
};
var j = {
    [u]: true,
    "default": false,
    "type": "Boolean"
};
var k = {
    [x]: "Endpoint"
};
var l = {
    [v]: c,
    [w]: [{
        [x]: "UseFIPS"
    }, true]
};
var m = {
    [v]: c,
    [w]: [{
        [x]: "UseDualStack"
    }, true]
};
var n = {};
var o = {
    [v]: h,
    [w]: [{
        [x]: g
    }, "supportsFIPS"]
};
var p = {
    [x]: g
};
var q = {
    [v]: c,
    [w]: [true, {
        [v]: h,
        [w]: [p, "supportsDualStack"]
    }]
};
var r = [l];
var s = [m];
var t = [{
    [x]: "Region"
}];
var _data = {
    version: "1.0",
    parameters: {
        Region: i,
        UseDualStack: j,
        UseFIPS: j,
        Endpoint: i
    },
    rules: [{
        conditions: [{
            [v]: b,
            [w]: [k]
        }],
        rules: [{
            conditions: r,
            error: "Invalid Configuration: FIPS and custom endpoint are not supported",
            type: d
        }, {
            conditions: s,
            error: "Invalid Configuration: Dualstack and custom endpoint are not supported",
            type: d
        }, {
            endpoint: {
                url: k,
                properties: n,
                headers: n
            },
            type: e
        }],
        type: f
    }, {
        conditions: [{
            [v]: b,
            [w]: t
        }],
        rules: [{
            conditions: [{
                [v]: "aws.partition",
                [w]: t,
                assign: g
            }],
            rules: [{
                conditions: [l, m],
                rules: [{
                    conditions: [{
                        [v]: c,
                        [w]: [a, o]
                    }, q],
                    rules: [{
                        endpoint: {
                            url: "https://sqs-fips.{Region}.{PartitionResult#dualStackDnsSuffix}",
                            properties: n,
                            headers: n
                        },
                        type: e
                    }],
                    type: f
                }, {
                    error: "FIPS and DualStack are enabled, but this partition does not support one or both",
                    type: d
                }],
                type: f
            }, {
                conditions: r,
                rules: [{
                    conditions: [{
                        [v]: c,
                        [w]: [o, a]
                    }],
                    rules: [{
                        conditions: [{
                            [v]: "stringEquals",
                            [w]: [{
                                [v]: h,
                                [w]: [p, "name"]
                            }, "aws-us-gov"]
                        }],
                        endpoint: {
                            url: "https://sqs.{Region}.amazonaws.com",
                            properties: n,
                            headers: n
                        },
                        type: e
                    }, {
                        endpoint: {
                            url: "https://sqs-fips.{Region}.{PartitionResult#dnsSuffix}",
                            properties: n,
                            headers: n
                        },
                        type: e
                    }],
                    type: f
                }, {
                    error: "FIPS is enabled but this partition does not support FIPS",
                    type: d
                }],
                type: f
            }, {
                conditions: s,
                rules: [{
                    conditions: [q],
                    rules: [{
                        endpoint: {
                            url: "https://sqs.{Region}.{PartitionResult#dualStackDnsSuffix}",
                            properties: n,
                            headers: n
                        },
                        type: e
                    }],
                    type: f
                }, {
                    error: "DualStack is enabled but this partition does not support DualStack",
                    type: d
                }],
                type: f
            }, {
                endpoint: {
                    url: "https://sqs.{Region}.{PartitionResult#dnsSuffix}",
                    properties: n,
                    headers: n
                },
                type: e
            }],
            type: f
        }],
        type: f
    }, {
        error: "Invalid Configuration: Missing Region",
        type: d
    }]
};
var ruleSet = _data;

// node_modules/@aws-sdk/client-sqs/dist-es/endpoint/endpointResolver.js
var cache = new EndpointCache({
    size: 50,
    params: ["Endpoint", "Region", "UseDualStack", "UseFIPS"]
});
var defaultEndpointResolver = (endpointParams, context = {}) => {
    return cache.get(endpointParams, () => resolveEndpoint(ruleSet, {
        endpointParams,
        logger: context.logger
    }));
};
customEndpointFunctions.aws = awsEndpointFunctions;

// node_modules/@aws-sdk/client-sqs/dist-es/runtimeConfig.shared.js
var getRuntimeConfig = (config) => {
    return {
        apiVersion: "2012-11-05",
        base64Decoder: config?.base64Decoder ?? fromBase64,
        base64Encoder: config?.base64Encoder ?? toBase64,
        disableHostPrefix: config?.disableHostPrefix ?? false,
        endpointProvider: config?.endpointProvider ?? defaultEndpointResolver,
        extensions: config?.extensions ?? [],
        httpAuthSchemeProvider: config?.httpAuthSchemeProvider ?? defaultSQSHttpAuthSchemeProvider,
        httpAuthSchemes: config?.httpAuthSchemes ?? [{
            schemeId: "aws.auth#sigv4",
            identityProvider: (ipc) => ipc.getIdentityProvider("aws.auth#sigv4"),
            signer: new AwsSdkSigV4Signer()
        }],
        logger: config?.logger ?? new NoOpLogger(),
        serviceId: config?.serviceId ?? "SQS",
        urlParser: config?.urlParser ?? parseUrl,
        utf8Decoder: config?.utf8Decoder ?? fromUtf8,
        utf8Encoder: config?.utf8Encoder ?? toUtf8
    };
};

// node_modules/@aws-sdk/client-sqs/dist-es/runtimeConfig.browser.js
var getRuntimeConfig2 = (config) => {
    const defaultsMode = resolveDefaultsModeConfig(config);
    const defaultConfigProvider = () => defaultsMode().then(loadConfigsForDefaultMode);
    const clientSharedValues = getRuntimeConfig(config);
    return __spreadProps(__spreadValues(__spreadValues({}, clientSharedValues), config), {
        runtime: "browser",
        defaultsMode,
        bodyLengthChecker: config?.bodyLengthChecker ?? calculateBodyLength,
        credentialDefaultProvider: config?.credentialDefaultProvider ?? ((_) => () => Promise.reject(new Error("Credential is missing"))),
        defaultUserAgentProvider: config?.defaultUserAgentProvider ?? createDefaultUserAgentProvider({
            serviceId: clientSharedValues.serviceId,
            clientVersion: package_default.version
        }),
        maxAttempts: config?.maxAttempts ?? DEFAULT_MAX_ATTEMPTS,
        md5: config?.md5 ?? Md5,
        region: config?.region ?? invalidProvider("Region is missing"),
        requestHandler: FetchHttpHandler.create(config?.requestHandler ?? defaultConfigProvider),
        retryMode: config?.retryMode ?? (() => __async(void 0, null, function* () {
            return (yield defaultConfigProvider()).retryMode || DEFAULT_RETRY_MODE;
        })),
        sha256: config?.sha256 ?? Sha256,
        streamCollector: config?.streamCollector ?? streamCollector,
        useDualstackEndpoint: config?.useDualstackEndpoint ?? (() => Promise.resolve(DEFAULT_USE_DUALSTACK_ENDPOINT)),
        useFipsEndpoint: config?.useFipsEndpoint ?? (() => Promise.resolve(DEFAULT_USE_FIPS_ENDPOINT))
    });
};

// node_modules/@aws-sdk/client-sqs/dist-es/auth/httpAuthExtensionConfiguration.js
var getHttpAuthExtensionConfiguration = (runtimeConfig) => {
    const _httpAuthSchemes = runtimeConfig.httpAuthSchemes;
    let _httpAuthSchemeProvider = runtimeConfig.httpAuthSchemeProvider;
    let _credentials = runtimeConfig.credentials;
    return {
        setHttpAuthScheme(httpAuthScheme) {
            const index = _httpAuthSchemes.findIndex((scheme) => scheme.schemeId === httpAuthScheme.schemeId);
            if (index === -1) {
                _httpAuthSchemes.push(httpAuthScheme);
            } else {
                _httpAuthSchemes.splice(index, 1, httpAuthScheme);
            }
        },
        httpAuthSchemes() {
            return _httpAuthSchemes;
        },
        setHttpAuthSchemeProvider(httpAuthSchemeProvider) {
            _httpAuthSchemeProvider = httpAuthSchemeProvider;
        },
        httpAuthSchemeProvider() {
            return _httpAuthSchemeProvider;
        },
        setCredentials(credentials) {
            _credentials = credentials;
        },
        credentials() {
            return _credentials;
        }
    };
};
var resolveHttpAuthRuntimeConfig = (config) => {
    return {
        httpAuthSchemes: config.httpAuthSchemes(),
        httpAuthSchemeProvider: config.httpAuthSchemeProvider(),
        credentials: config.credentials()
    };
};

// node_modules/@aws-sdk/client-sqs/dist-es/runtimeExtensions.js
var asPartial = (t2) => t2;
var resolveRuntimeExtensions = (runtimeConfig, extensions) => {
    const extensionConfiguration = __spreadValues(__spreadValues(__spreadValues(__spreadValues({}, asPartial(getAwsRegionExtensionConfiguration(runtimeConfig))), asPartial(getDefaultExtensionConfiguration(runtimeConfig))), asPartial(getHttpHandlerExtensionConfiguration(runtimeConfig))), asPartial(getHttpAuthExtensionConfiguration(runtimeConfig)));
    extensions.forEach((extension) => extension.configure(extensionConfiguration));
    return __spreadValues(__spreadValues(__spreadValues(__spreadValues(__spreadValues({}, runtimeConfig), resolveAwsRegionExtensionConfiguration(extensionConfiguration)), resolveDefaultRuntimeConfig(extensionConfiguration)), resolveHttpHandlerRuntimeConfig(extensionConfiguration)), resolveHttpAuthRuntimeConfig(extensionConfiguration));
};

// node_modules/@aws-sdk/client-sqs/dist-es/SQSClient.js
var SQSClient = class extends Client {
    constructor(...[configuration]) {
        const _config_0 = getRuntimeConfig2(configuration || {});
        const _config_1 = resolveClientEndpointParameters(_config_0);
        const _config_2 = resolveUserAgentConfig(_config_1);
        const _config_3 = resolveRetryConfig(_config_2);
        const _config_4 = resolveRegionConfig(_config_3);
        const _config_5 = resolveHostHeaderConfig(_config_4);
        const _config_6 = resolveEndpointConfig(_config_5);
        const _config_7 = resolveQueueUrlConfig(_config_6);
        const _config_8 = resolveHttpAuthSchemeConfig(_config_7);
        const _config_9 = resolveRuntimeExtensions(_config_8, configuration?.extensions || []);
        super(_config_9);
        this.config = _config_9;
        this.middlewareStack.use(getUserAgentPlugin(this.config));
        this.middlewareStack.use(getRetryPlugin(this.config));
        this.middlewareStack.use(getContentLengthPlugin(this.config));
        this.middlewareStack.use(getHostHeaderPlugin(this.config));
        this.middlewareStack.use(getLoggerPlugin(this.config));
        this.middlewareStack.use(getRecursionDetectionPlugin(this.config));
        this.middlewareStack.use(getQueueUrlPlugin(this.config));
        this.middlewareStack.use(getHttpAuthSchemeEndpointRuleSetPlugin(this.config, {
            httpAuthSchemeParametersProvider: defaultSQSHttpAuthSchemeParametersProvider,
            identityProviderConfigProvider: (config) => __async(this, null, function* () {
                return new DefaultIdentityProviderConfig({
                    "aws.auth#sigv4": config.credentials
                });
            })
        }));
        this.middlewareStack.use(getHttpSigningPlugin(this.config));
    }

    destroy() {
        super.destroy();
    }
};

// node_modules/@aws-sdk/client-sqs/dist-es/models/SQSServiceException.js
var SQSServiceException = class _SQSServiceException extends ServiceException {
    constructor(options) {
        super(options);
        Object.setPrototypeOf(this, _SQSServiceException.prototype);
    }
};

// node_modules/@aws-sdk/client-sqs/dist-es/models/models_0.js
var InvalidAddress = class _InvalidAddress extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "InvalidAddress",
            $fault: "client"
        }, opts));
        this.name = "InvalidAddress";
        this.$fault = "client";
        Object.setPrototypeOf(this, _InvalidAddress.prototype);
    }
};
var InvalidSecurity = class _InvalidSecurity extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "InvalidSecurity",
            $fault: "client"
        }, opts));
        this.name = "InvalidSecurity";
        this.$fault = "client";
        Object.setPrototypeOf(this, _InvalidSecurity.prototype);
    }
};
var OverLimit = class _OverLimit extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "OverLimit",
            $fault: "client"
        }, opts));
        this.name = "OverLimit";
        this.$fault = "client";
        Object.setPrototypeOf(this, _OverLimit.prototype);
    }
};
var QueueDoesNotExist = class _QueueDoesNotExist extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "QueueDoesNotExist",
            $fault: "client"
        }, opts));
        this.name = "QueueDoesNotExist";
        this.$fault = "client";
        Object.setPrototypeOf(this, _QueueDoesNotExist.prototype);
    }
};
var RequestThrottled = class _RequestThrottled extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "RequestThrottled",
            $fault: "client"
        }, opts));
        this.name = "RequestThrottled";
        this.$fault = "client";
        Object.setPrototypeOf(this, _RequestThrottled.prototype);
    }
};
var UnsupportedOperation = class _UnsupportedOperation extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "UnsupportedOperation",
            $fault: "client"
        }, opts));
        this.name = "UnsupportedOperation";
        this.$fault = "client";
        Object.setPrototypeOf(this, _UnsupportedOperation.prototype);
    }
};
var ResourceNotFoundException = class _ResourceNotFoundException extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "ResourceNotFoundException",
            $fault: "client"
        }, opts));
        this.name = "ResourceNotFoundException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _ResourceNotFoundException.prototype);
    }
};
var MessageNotInflight = class _MessageNotInflight extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "MessageNotInflight",
            $fault: "client"
        }, opts));
        this.name = "MessageNotInflight";
        this.$fault = "client";
        Object.setPrototypeOf(this, _MessageNotInflight.prototype);
    }
};
var ReceiptHandleIsInvalid = class _ReceiptHandleIsInvalid extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "ReceiptHandleIsInvalid",
            $fault: "client"
        }, opts));
        this.name = "ReceiptHandleIsInvalid";
        this.$fault = "client";
        Object.setPrototypeOf(this, _ReceiptHandleIsInvalid.prototype);
    }
};
var BatchEntryIdsNotDistinct = class _BatchEntryIdsNotDistinct extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "BatchEntryIdsNotDistinct",
            $fault: "client"
        }, opts));
        this.name = "BatchEntryIdsNotDistinct";
        this.$fault = "client";
        Object.setPrototypeOf(this, _BatchEntryIdsNotDistinct.prototype);
    }
};
var EmptyBatchRequest = class _EmptyBatchRequest extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "EmptyBatchRequest",
            $fault: "client"
        }, opts));
        this.name = "EmptyBatchRequest";
        this.$fault = "client";
        Object.setPrototypeOf(this, _EmptyBatchRequest.prototype);
    }
};
var InvalidBatchEntryId = class _InvalidBatchEntryId extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "InvalidBatchEntryId",
            $fault: "client"
        }, opts));
        this.name = "InvalidBatchEntryId";
        this.$fault = "client";
        Object.setPrototypeOf(this, _InvalidBatchEntryId.prototype);
    }
};
var TooManyEntriesInBatchRequest = class _TooManyEntriesInBatchRequest extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "TooManyEntriesInBatchRequest",
            $fault: "client"
        }, opts));
        this.name = "TooManyEntriesInBatchRequest";
        this.$fault = "client";
        Object.setPrototypeOf(this, _TooManyEntriesInBatchRequest.prototype);
    }
};
var QueueAttributeName = {
    All: "All",
    ApproximateNumberOfMessages: "ApproximateNumberOfMessages",
    ApproximateNumberOfMessagesDelayed: "ApproximateNumberOfMessagesDelayed",
    ApproximateNumberOfMessagesNotVisible: "ApproximateNumberOfMessagesNotVisible",
    ContentBasedDeduplication: "ContentBasedDeduplication",
    CreatedTimestamp: "CreatedTimestamp",
    DeduplicationScope: "DeduplicationScope",
    DelaySeconds: "DelaySeconds",
    FifoQueue: "FifoQueue",
    FifoThroughputLimit: "FifoThroughputLimit",
    KmsDataKeyReusePeriodSeconds: "KmsDataKeyReusePeriodSeconds",
    KmsMasterKeyId: "KmsMasterKeyId",
    LastModifiedTimestamp: "LastModifiedTimestamp",
    MaximumMessageSize: "MaximumMessageSize",
    MessageRetentionPeriod: "MessageRetentionPeriod",
    Policy: "Policy",
    QueueArn: "QueueArn",
    ReceiveMessageWaitTimeSeconds: "ReceiveMessageWaitTimeSeconds",
    RedriveAllowPolicy: "RedriveAllowPolicy",
    RedrivePolicy: "RedrivePolicy",
    SqsManagedSseEnabled: "SqsManagedSseEnabled",
    VisibilityTimeout: "VisibilityTimeout"
};
var InvalidAttributeName = class _InvalidAttributeName extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "InvalidAttributeName",
            $fault: "client"
        }, opts));
        this.name = "InvalidAttributeName";
        this.$fault = "client";
        Object.setPrototypeOf(this, _InvalidAttributeName.prototype);
    }
};
var InvalidAttributeValue = class _InvalidAttributeValue extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "InvalidAttributeValue",
            $fault: "client"
        }, opts));
        this.name = "InvalidAttributeValue";
        this.$fault = "client";
        Object.setPrototypeOf(this, _InvalidAttributeValue.prototype);
    }
};
var QueueDeletedRecently = class _QueueDeletedRecently extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "QueueDeletedRecently",
            $fault: "client"
        }, opts));
        this.name = "QueueDeletedRecently";
        this.$fault = "client";
        Object.setPrototypeOf(this, _QueueDeletedRecently.prototype);
    }
};
var QueueNameExists = class _QueueNameExists extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "QueueNameExists",
            $fault: "client"
        }, opts));
        this.name = "QueueNameExists";
        this.$fault = "client";
        Object.setPrototypeOf(this, _QueueNameExists.prototype);
    }
};
var InvalidIdFormat = class _InvalidIdFormat extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "InvalidIdFormat",
            $fault: "client"
        }, opts));
        this.name = "InvalidIdFormat";
        this.$fault = "client";
        Object.setPrototypeOf(this, _InvalidIdFormat.prototype);
    }
};
var PurgeQueueInProgress = class _PurgeQueueInProgress extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "PurgeQueueInProgress",
            $fault: "client"
        }, opts));
        this.name = "PurgeQueueInProgress";
        this.$fault = "client";
        Object.setPrototypeOf(this, _PurgeQueueInProgress.prototype);
    }
};
var KmsAccessDenied = class _KmsAccessDenied extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "KmsAccessDenied",
            $fault: "client"
        }, opts));
        this.name = "KmsAccessDenied";
        this.$fault = "client";
        Object.setPrototypeOf(this, _KmsAccessDenied.prototype);
    }
};
var KmsDisabled = class _KmsDisabled extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "KmsDisabled",
            $fault: "client"
        }, opts));
        this.name = "KmsDisabled";
        this.$fault = "client";
        Object.setPrototypeOf(this, _KmsDisabled.prototype);
    }
};
var KmsInvalidKeyUsage = class _KmsInvalidKeyUsage extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "KmsInvalidKeyUsage",
            $fault: "client"
        }, opts));
        this.name = "KmsInvalidKeyUsage";
        this.$fault = "client";
        Object.setPrototypeOf(this, _KmsInvalidKeyUsage.prototype);
    }
};
var KmsInvalidState = class _KmsInvalidState extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "KmsInvalidState",
            $fault: "client"
        }, opts));
        this.name = "KmsInvalidState";
        this.$fault = "client";
        Object.setPrototypeOf(this, _KmsInvalidState.prototype);
    }
};
var KmsNotFound = class _KmsNotFound extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "KmsNotFound",
            $fault: "client"
        }, opts));
        this.name = "KmsNotFound";
        this.$fault = "client";
        Object.setPrototypeOf(this, _KmsNotFound.prototype);
    }
};
var KmsOptInRequired = class _KmsOptInRequired extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "KmsOptInRequired",
            $fault: "client"
        }, opts));
        this.name = "KmsOptInRequired";
        this.$fault = "client";
        Object.setPrototypeOf(this, _KmsOptInRequired.prototype);
    }
};
var KmsThrottled = class _KmsThrottled extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "KmsThrottled",
            $fault: "client"
        }, opts));
        this.name = "KmsThrottled";
        this.$fault = "client";
        Object.setPrototypeOf(this, _KmsThrottled.prototype);
    }
};
var InvalidMessageContents = class _InvalidMessageContents extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "InvalidMessageContents",
            $fault: "client"
        }, opts));
        this.name = "InvalidMessageContents";
        this.$fault = "client";
        Object.setPrototypeOf(this, _InvalidMessageContents.prototype);
    }
};
var BatchRequestTooLong = class _BatchRequestTooLong extends SQSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "BatchRequestTooLong",
            $fault: "client"
        }, opts));
        this.name = "BatchRequestTooLong";
        this.$fault = "client";
        Object.setPrototypeOf(this, _BatchRequestTooLong.prototype);
    }
};

// node_modules/@aws-sdk/client-sqs/dist-es/protocols/Aws_json1_0.js
var se_CreateQueueCommand = (input, context) => __async(void 0, null, function* () {
    const headers = sharedHeaders("CreateQueue");
    let body;
    body = JSON.stringify(se_CreateQueueRequest(input, context));
    return buildHttpRpcRequest(context, headers, "/", void 0, body);
});
var se_DeleteMessageCommand = (input, context) => __async(void 0, null, function* () {
    const headers = sharedHeaders("DeleteMessage");
    let body;
    body = JSON.stringify(se_DeleteMessageRequest(input, context));
    return buildHttpRpcRequest(context, headers, "/", void 0, body);
});
var se_DeleteQueueCommand = (input, context) => __async(void 0, null, function* () {
    const headers = sharedHeaders("DeleteQueue");
    let body;
    body = JSON.stringify(se_DeleteQueueRequest(input, context));
    return buildHttpRpcRequest(context, headers, "/", void 0, body);
});
var se_GetQueueAttributesCommand = (input, context) => __async(void 0, null, function* () {
    const headers = sharedHeaders("GetQueueAttributes");
    let body;
    body = JSON.stringify(se_GetQueueAttributesRequest(input, context));
    return buildHttpRpcRequest(context, headers, "/", void 0, body);
});
var se_GetQueueUrlCommand = (input, context) => __async(void 0, null, function* () {
    const headers = sharedHeaders("GetQueueUrl");
    let body;
    body = JSON.stringify(se_GetQueueUrlRequest(input, context));
    return buildHttpRpcRequest(context, headers, "/", void 0, body);
});
var se_ListQueuesCommand = (input, context) => __async(void 0, null, function* () {
    const headers = sharedHeaders("ListQueues");
    let body;
    body = JSON.stringify(se_ListQueuesRequest(input, context));
    return buildHttpRpcRequest(context, headers, "/", void 0, body);
});
var se_PurgeQueueCommand = (input, context) => __async(void 0, null, function* () {
    const headers = sharedHeaders("PurgeQueue");
    let body;
    body = JSON.stringify(se_PurgeQueueRequest(input, context));
    return buildHttpRpcRequest(context, headers, "/", void 0, body);
});
var se_SendMessageCommand = (input, context) => __async(void 0, null, function* () {
    const headers = sharedHeaders("SendMessage");
    let body;
    body = JSON.stringify(se_SendMessageRequest(input, context));
    return buildHttpRpcRequest(context, headers, "/", void 0, body);
});
var de_CreateQueueCommand = (output, context) => __async(void 0, null, function* () {
    if (output.statusCode >= 300) {
        return de_CommandError(output, context);
    }
    const data = yield parseJsonBody(output.body, context);
    let contents = {};
    contents = _json(data);
    const response = __spreadValues({
        $metadata: deserializeMetadata(output)
    }, contents);
    return response;
});
var de_DeleteMessageCommand = (output, context) => __async(void 0, null, function* () {
    if (output.statusCode >= 300) {
        return de_CommandError(output, context);
    }
    yield collectBody(output.body, context);
    const response = {
        $metadata: deserializeMetadata(output)
    };
    return response;
});
var de_DeleteQueueCommand = (output, context) => __async(void 0, null, function* () {
    if (output.statusCode >= 300) {
        return de_CommandError(output, context);
    }
    yield collectBody(output.body, context);
    const response = {
        $metadata: deserializeMetadata(output)
    };
    return response;
});
var de_GetQueueAttributesCommand = (output, context) => __async(void 0, null, function* () {
    if (output.statusCode >= 300) {
        return de_CommandError(output, context);
    }
    const data = yield parseJsonBody(output.body, context);
    let contents = {};
    contents = _json(data);
    const response = __spreadValues({
        $metadata: deserializeMetadata(output)
    }, contents);
    return response;
});
var de_GetQueueUrlCommand = (output, context) => __async(void 0, null, function* () {
    if (output.statusCode >= 300) {
        return de_CommandError(output, context);
    }
    const data = yield parseJsonBody(output.body, context);
    let contents = {};
    contents = _json(data);
    const response = __spreadValues({
        $metadata: deserializeMetadata(output)
    }, contents);
    return response;
});
var de_ListQueuesCommand = (output, context) => __async(void 0, null, function* () {
    if (output.statusCode >= 300) {
        return de_CommandError(output, context);
    }
    const data = yield parseJsonBody(output.body, context);
    let contents = {};
    contents = _json(data);
    const response = __spreadValues({
        $metadata: deserializeMetadata(output)
    }, contents);
    return response;
});
var de_PurgeQueueCommand = (output, context) => __async(void 0, null, function* () {
    if (output.statusCode >= 300) {
        return de_CommandError(output, context);
    }
    yield collectBody(output.body, context);
    const response = {
        $metadata: deserializeMetadata(output)
    };
    return response;
});
var de_SendMessageCommand = (output, context) => __async(void 0, null, function* () {
    if (output.statusCode >= 300) {
        return de_CommandError(output, context);
    }
    const data = yield parseJsonBody(output.body, context);
    let contents = {};
    contents = _json(data);
    const response = __spreadValues({
        $metadata: deserializeMetadata(output)
    }, contents);
    return response;
});
var de_CommandError = (output, context) => __async(void 0, null, function* () {
    const parsedOutput = __spreadProps(__spreadValues({}, output), {
        body: yield parseJsonErrorBody(output.body, context)
    });
    populateBodyWithQueryCompatibility(parsedOutput, output.headers);
    const errorCode = loadRestJsonErrorCode(output, parsedOutput.body);
    switch (errorCode) {
        case "InvalidAddress":
        case "com.amazonaws.sqs#InvalidAddress":
            throw yield de_InvalidAddressRes(parsedOutput, context);
        case "InvalidSecurity":
        case "com.amazonaws.sqs#InvalidSecurity":
            throw yield de_InvalidSecurityRes(parsedOutput, context);
        case "OverLimit":
        case "com.amazonaws.sqs#OverLimit":
            throw yield de_OverLimitRes(parsedOutput, context);
        case "QueueDoesNotExist":
        case "com.amazonaws.sqs#QueueDoesNotExist":
            throw yield de_QueueDoesNotExistRes(parsedOutput, context);
        case "RequestThrottled":
        case "com.amazonaws.sqs#RequestThrottled":
            throw yield de_RequestThrottledRes(parsedOutput, context);
        case "UnsupportedOperation":
        case "com.amazonaws.sqs#UnsupportedOperation":
            throw yield de_UnsupportedOperationRes(parsedOutput, context);
        case "ResourceNotFoundException":
        case "com.amazonaws.sqs#ResourceNotFoundException":
            throw yield de_ResourceNotFoundExceptionRes(parsedOutput, context);
        case "MessageNotInflight":
        case "com.amazonaws.sqs#MessageNotInflight":
            throw yield de_MessageNotInflightRes(parsedOutput, context);
        case "ReceiptHandleIsInvalid":
        case "com.amazonaws.sqs#ReceiptHandleIsInvalid":
            throw yield de_ReceiptHandleIsInvalidRes(parsedOutput, context);
        case "BatchEntryIdsNotDistinct":
        case "com.amazonaws.sqs#BatchEntryIdsNotDistinct":
            throw yield de_BatchEntryIdsNotDistinctRes(parsedOutput, context);
        case "EmptyBatchRequest":
        case "com.amazonaws.sqs#EmptyBatchRequest":
            throw yield de_EmptyBatchRequestRes(parsedOutput, context);
        case "InvalidBatchEntryId":
        case "com.amazonaws.sqs#InvalidBatchEntryId":
            throw yield de_InvalidBatchEntryIdRes(parsedOutput, context);
        case "TooManyEntriesInBatchRequest":
        case "com.amazonaws.sqs#TooManyEntriesInBatchRequest":
            throw yield de_TooManyEntriesInBatchRequestRes(parsedOutput, context);
        case "InvalidAttributeName":
        case "com.amazonaws.sqs#InvalidAttributeName":
            throw yield de_InvalidAttributeNameRes(parsedOutput, context);
        case "InvalidAttributeValue":
        case "com.amazonaws.sqs#InvalidAttributeValue":
            throw yield de_InvalidAttributeValueRes(parsedOutput, context);
        case "QueueDeletedRecently":
        case "com.amazonaws.sqs#QueueDeletedRecently":
            throw yield de_QueueDeletedRecentlyRes(parsedOutput, context);
        case "QueueNameExists":
        case "com.amazonaws.sqs#QueueNameExists":
            throw yield de_QueueNameExistsRes(parsedOutput, context);
        case "InvalidIdFormat":
        case "com.amazonaws.sqs#InvalidIdFormat":
            throw yield de_InvalidIdFormatRes(parsedOutput, context);
        case "PurgeQueueInProgress":
        case "com.amazonaws.sqs#PurgeQueueInProgress":
            throw yield de_PurgeQueueInProgressRes(parsedOutput, context);
        case "KmsAccessDenied":
        case "com.amazonaws.sqs#KmsAccessDenied":
            throw yield de_KmsAccessDeniedRes(parsedOutput, context);
        case "KmsDisabled":
        case "com.amazonaws.sqs#KmsDisabled":
            throw yield de_KmsDisabledRes(parsedOutput, context);
        case "KmsInvalidKeyUsage":
        case "com.amazonaws.sqs#KmsInvalidKeyUsage":
            throw yield de_KmsInvalidKeyUsageRes(parsedOutput, context);
        case "KmsInvalidState":
        case "com.amazonaws.sqs#KmsInvalidState":
            throw yield de_KmsInvalidStateRes(parsedOutput, context);
        case "KmsNotFound":
        case "com.amazonaws.sqs#KmsNotFound":
            throw yield de_KmsNotFoundRes(parsedOutput, context);
        case "KmsOptInRequired":
        case "com.amazonaws.sqs#KmsOptInRequired":
            throw yield de_KmsOptInRequiredRes(parsedOutput, context);
        case "KmsThrottled":
        case "com.amazonaws.sqs#KmsThrottled":
            throw yield de_KmsThrottledRes(parsedOutput, context);
        case "InvalidMessageContents":
        case "com.amazonaws.sqs#InvalidMessageContents":
            throw yield de_InvalidMessageContentsRes(parsedOutput, context);
        case "BatchRequestTooLong":
        case "com.amazonaws.sqs#BatchRequestTooLong":
            throw yield de_BatchRequestTooLongRes(parsedOutput, context);
        default:
            const parsedBody = parsedOutput.body;
            return throwDefaultError({
                output,
                parsedBody,
                errorCode
            });
    }
});
var de_BatchEntryIdsNotDistinctRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new BatchEntryIdsNotDistinct(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_BatchRequestTooLongRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new BatchRequestTooLong(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_EmptyBatchRequestRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new EmptyBatchRequest(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_InvalidAddressRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new InvalidAddress(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_InvalidAttributeNameRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new InvalidAttributeName(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_InvalidAttributeValueRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new InvalidAttributeValue(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_InvalidBatchEntryIdRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new InvalidBatchEntryId(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_InvalidIdFormatRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new InvalidIdFormat(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_InvalidMessageContentsRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new InvalidMessageContents(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_InvalidSecurityRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new InvalidSecurity(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_KmsAccessDeniedRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new KmsAccessDenied(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_KmsDisabledRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new KmsDisabled(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_KmsInvalidKeyUsageRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new KmsInvalidKeyUsage(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_KmsInvalidStateRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new KmsInvalidState(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_KmsNotFoundRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new KmsNotFound(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_KmsOptInRequiredRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new KmsOptInRequired(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_KmsThrottledRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new KmsThrottled(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_MessageNotInflightRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new MessageNotInflight(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_OverLimitRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new OverLimit(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_PurgeQueueInProgressRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new PurgeQueueInProgress(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_QueueDeletedRecentlyRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new QueueDeletedRecently(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_QueueDoesNotExistRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new QueueDoesNotExist(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_QueueNameExistsRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new QueueNameExists(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_ReceiptHandleIsInvalidRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new ReceiptHandleIsInvalid(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_RequestThrottledRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new RequestThrottled(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_ResourceNotFoundExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new ResourceNotFoundException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_TooManyEntriesInBatchRequestRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new TooManyEntriesInBatchRequest(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_UnsupportedOperationRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = _json(body);
    const exception = new UnsupportedOperation(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var se_AttributeNameList = (input, context) => {
    return input.filter((e2) => e2 != null).map((entry) => {
        return _toStr(entry);
    });
};
var se_BinaryList = (input, context) => {
    return input.filter((e2) => e2 != null).map((entry) => {
        return context.base64Encoder(entry);
    });
};
var se_CreateQueueRequest = (input, context) => {
    return take(input, {
        Attributes: (_) => se_QueueAttributeMap(_, context),
        QueueName: _toStr,
        tags: (_) => se_TagMap(_, context)
    });
};
var se_DeleteMessageRequest = (input, context) => {
    return take(input, {
        QueueUrl: _toStr,
        ReceiptHandle: _toStr
    });
};
var se_DeleteQueueRequest = (input, context) => {
    return take(input, {
        QueueUrl: _toStr
    });
};
var se_GetQueueAttributesRequest = (input, context) => {
    return take(input, {
        AttributeNames: (_) => se_AttributeNameList(_, context),
        QueueUrl: _toStr
    });
};
var se_GetQueueUrlRequest = (input, context) => {
    return take(input, {
        QueueName: _toStr,
        QueueOwnerAWSAccountId: _toStr
    });
};
var se_ListQueuesRequest = (input, context) => {
    return take(input, {
        MaxResults: _toNum,
        NextToken: _toStr,
        QueueNamePrefix: _toStr
    });
};
var se_MessageAttributeValue = (input, context) => {
    return take(input, {
        BinaryListValues: (_) => se_BinaryList(_, context),
        BinaryValue: context.base64Encoder,
        DataType: _toStr,
        StringListValues: (_) => se_StringList(_, context),
        StringValue: _toStr
    });
};
var se_MessageBodyAttributeMap = (input, context) => {
    return Object.entries(input).reduce((acc, [key, value]) => {
        if (value === null) {
            return acc;
        }
        acc[key] = se_MessageAttributeValue(value, context);
        return acc;
    }, {});
};
var se_MessageBodySystemAttributeMap = (input, context) => {
    return Object.entries(input).reduce((acc, [key, value]) => {
        if (value === null) {
            return acc;
        }
        acc[key] = se_MessageSystemAttributeValue(value, context);
        return acc;
    }, {});
};
var se_MessageSystemAttributeValue = (input, context) => {
    return take(input, {
        BinaryListValues: (_) => se_BinaryList(_, context),
        BinaryValue: context.base64Encoder,
        DataType: _toStr,
        StringListValues: (_) => se_StringList(_, context),
        StringValue: _toStr
    });
};
var se_PurgeQueueRequest = (input, context) => {
    return take(input, {
        QueueUrl: _toStr
    });
};
var se_QueueAttributeMap = (input, context) => {
    return Object.entries(input).reduce((acc, [key, value]) => {
        if (value === null) {
            return acc;
        }
        acc[key] = _toStr(value);
        return acc;
    }, {});
};
var se_SendMessageRequest = (input, context) => {
    return take(input, {
        DelaySeconds: _toNum,
        MessageAttributes: (_) => se_MessageBodyAttributeMap(_, context),
        MessageBody: _toStr,
        MessageDeduplicationId: _toStr,
        MessageGroupId: _toStr,
        MessageSystemAttributes: (_) => se_MessageBodySystemAttributeMap(_, context),
        QueueUrl: _toStr
    });
};
var se_StringList = (input, context) => {
    return input.filter((e2) => e2 != null).map((entry) => {
        return _toStr(entry);
    });
};
var se_TagMap = (input, context) => {
    return Object.entries(input).reduce((acc, [key, value]) => {
        if (value === null) {
            return acc;
        }
        acc[key] = _toStr(value);
        return acc;
    }, {});
};
var deserializeMetadata = (output) => ({
    httpStatusCode: output.statusCode,
    requestId: output.headers["x-amzn-requestid"] ?? output.headers["x-amzn-request-id"] ?? output.headers["x-amz-request-id"],
    extendedRequestId: output.headers["x-amz-id-2"],
    cfId: output.headers["x-amz-cf-id"]
});
var throwDefaultError = withBaseException(SQSServiceException);
var buildHttpRpcRequest = (context, headers, path, resolvedHostname, body) => __async(void 0, null, function* () {
    const {
        hostname,
        protocol = "https",
        port,
        path: basePath
    } = yield context.endpoint();
    const contents = {
        protocol,
        hostname,
        port,
        method: "POST",
        path: basePath.endsWith("/") ? basePath.slice(0, -1) + path : basePath + path,
        headers
    };
    if (resolvedHostname !== void 0) {
        contents.hostname = resolvedHostname;
    }
    if (body !== void 0) {
        contents.body = body;
    }
    return new HttpRequest(contents);
});

function sharedHeaders(operation) {
    return {
        "content-type": "application/x-amz-json-1.0",
        "x-amz-target": `AmazonSQS.${operation}`,
        "x-amzn-query-mode": "true"
    };
}

var populateBodyWithQueryCompatibility = (parsedOutput, headers) => {
    const queryErrorHeader = headers["x-amzn-query-error"];
    if (parsedOutput.body !== void 0 && queryErrorHeader != null) {
        const codeAndType = queryErrorHeader.split(";");
        parsedOutput.body.Code = codeAndType[0];
        parsedOutput.body.Type = codeAndType[1];
    }
};

// node_modules/@aws-sdk/client-sqs/dist-es/commands/CreateQueueCommand.js
var CreateQueueCommand = class extends Command.classBuilder().ep(commonParams).m(function (Command2, cs, config, o2) {
    return [getSerdePlugin(config, this.serialize, this.deserialize), getEndpointPlugin(config, Command2.getEndpointParameterInstructions())];
}).s("AmazonSQS", "CreateQueue", {}).n("SQSClient", "CreateQueueCommand").f(void 0, void 0).ser(se_CreateQueueCommand).de(de_CreateQueueCommand).build() {
};

// node_modules/@aws-sdk/client-sqs/dist-es/commands/DeleteMessageCommand.js
var DeleteMessageCommand = class extends Command.classBuilder().ep(commonParams).m(function (Command2, cs, config, o2) {
    return [getSerdePlugin(config, this.serialize, this.deserialize), getEndpointPlugin(config, Command2.getEndpointParameterInstructions())];
}).s("AmazonSQS", "DeleteMessage", {}).n("SQSClient", "DeleteMessageCommand").f(void 0, void 0).ser(se_DeleteMessageCommand).de(de_DeleteMessageCommand).build() {
};

// node_modules/@aws-sdk/client-sqs/dist-es/commands/DeleteQueueCommand.js
var DeleteQueueCommand = class extends Command.classBuilder().ep(commonParams).m(function (Command2, cs, config, o2) {
    return [getSerdePlugin(config, this.serialize, this.deserialize), getEndpointPlugin(config, Command2.getEndpointParameterInstructions())];
}).s("AmazonSQS", "DeleteQueue", {}).n("SQSClient", "DeleteQueueCommand").f(void 0, void 0).ser(se_DeleteQueueCommand).de(de_DeleteQueueCommand).build() {
};

// node_modules/@aws-sdk/client-sqs/dist-es/commands/GetQueueAttributesCommand.js
var GetQueueAttributesCommand = class extends Command.classBuilder().ep(commonParams).m(function (Command2, cs, config, o2) {
    return [getSerdePlugin(config, this.serialize, this.deserialize), getEndpointPlugin(config, Command2.getEndpointParameterInstructions())];
}).s("AmazonSQS", "GetQueueAttributes", {}).n("SQSClient", "GetQueueAttributesCommand").f(void 0, void 0).ser(se_GetQueueAttributesCommand).de(de_GetQueueAttributesCommand).build() {
};

// node_modules/@aws-sdk/client-sqs/dist-es/commands/GetQueueUrlCommand.js
var GetQueueUrlCommand = class extends Command.classBuilder().ep(commonParams).m(function (Command2, cs, config, o2) {
    return [getSerdePlugin(config, this.serialize, this.deserialize), getEndpointPlugin(config, Command2.getEndpointParameterInstructions())];
}).s("AmazonSQS", "GetQueueUrl", {}).n("SQSClient", "GetQueueUrlCommand").f(void 0, void 0).ser(se_GetQueueUrlCommand).de(de_GetQueueUrlCommand).build() {
};

// node_modules/@aws-sdk/client-sqs/dist-es/commands/ListQueuesCommand.js
var ListQueuesCommand = class extends Command.classBuilder().ep(commonParams).m(function (Command2, cs, config, o2) {
    return [getSerdePlugin(config, this.serialize, this.deserialize), getEndpointPlugin(config, Command2.getEndpointParameterInstructions())];
}).s("AmazonSQS", "ListQueues", {}).n("SQSClient", "ListQueuesCommand").f(void 0, void 0).ser(se_ListQueuesCommand).de(de_ListQueuesCommand).build() {
};

// node_modules/@aws-sdk/client-sqs/dist-es/commands/PurgeQueueCommand.js
var PurgeQueueCommand = class extends Command.classBuilder().ep(commonParams).m(function (Command2, cs, config, o2) {
    return [getSerdePlugin(config, this.serialize, this.deserialize), getEndpointPlugin(config, Command2.getEndpointParameterInstructions())];
}).s("AmazonSQS", "PurgeQueue", {}).n("SQSClient", "PurgeQueueCommand").f(void 0, void 0).ser(se_PurgeQueueCommand).de(de_PurgeQueueCommand).build() {
};

// node_modules/@aws-sdk/client-sqs/dist-es/commands/SendMessageCommand.js
var SendMessageCommand = class extends Command.classBuilder().ep(commonParams).m(function (Command2, cs, config, o2) {
    return [getSerdePlugin(config, this.serialize, this.deserialize), getEndpointPlugin(config, Command2.getEndpointParameterInstructions()), getSendMessagePlugin(config)];
}).s("AmazonSQS", "SendMessage", {}).n("SQSClient", "SendMessageCommand").f(void 0, void 0).ser(se_SendMessageCommand).de(de_SendMessageCommand).build() {
};

// src/app/modules/sqs/service/sqs-service.component.ts
var SqsService = class _SqsService {
    constructor(http) {
        this.http = http;
        this.client = new SQSClient({
            region: environment.awsmockRegion,
            endpoint: environment.gatewayEndpoint,
            credentials: {
                accessKeyId: "test",
                secretAccessKey: "test"
            },
            requestHandler: {
                requestTimeout: 3e4,
                httpsAgent: {maxSockets: 25}
            }
        });
        this.headers = new HttpHeaders({
            "Content-Type": "application/json",
            "Authorization": "AWS4-HMAC-SHA256 Credential=none/20240928/eu-central-1/s3/aws4_request, SignedHeaders=content-type;host;x-amz-date;x-amz-security-token;x-amz-target, Signature=01316d694335ec0e0bf68b08570490f1b0bae0b130ecbe13ebad511b3ece8a41"
        });
        this.url = environment.gatewayEndpoint + "/";
    }

    listQueues(pageIndex, pageSize, prefix) {
        const input = {
            QueueNamePrefix: prefix,
            NextToken: (pageIndex * pageSize).toString(),
            MaxResults: pageSize
        };
        return this.client.send(new ListQueuesCommand(input));
    }

    purgeQueue(queueName) {
        const input = {
            QueueUrl: queueName
        };
        return this.client.send(new PurgeQueueCommand(input));
    }

    getQueueAttributes(queueUrl) {
        const input = {
            QueueUrl: queueUrl,
            AttributeNames: [QueueAttributeName.All]
        };
        return this.client.send(new GetQueueAttributesCommand(input));
    }

    getQueueArn(queueUrl) {
        const input = {
            QueueUrl: queueUrl,
            AttributeNames: [QueueAttributeName.QueueArn]
        };
        return this.client.send(new GetQueueAttributesCommand(input));
    }

    getQueueUrl(queueName) {
        const input = {
            QueueName: queueName
        };
        return this.client.send(new GetQueueUrlCommand(input));
    }

    saveQueue(queueName) {
        const input = {
            QueueName: queueName
        };
        return this.client.send(new CreateQueueCommand(input));
    }

    deleteQueue(queueUrl) {
        const input = {
            QueueUrl: queueUrl
        };
        return this.client.send(new DeleteQueueCommand(input));
    }

    sendMessage(queueUrl, message) {
        const input = {
            QueueUrl: queueUrl,
            MessageBody: message,
            DelaySeconds: 0
        };
        return this.client.send(new SendMessageCommand(input));
    }

    deleteMessage(queueUrl, receiptHandle) {
        const input = {
            QueueUrl: queueUrl,
            ReceiptHandle: receiptHandle
        };
        return this.client.send(new DeleteMessageCommand(input));
    }

    cleanup() {
        this.client.destroy();
    }

    /**
     * @brief List all queue ARNs
     *
     * @par
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     */
    listQueueArns() {
        let headers = this.headers.set("x-awsmock-target", "sqs").set("x-awsmock-action", "ListQueueArns");
        return this.http.post(this.url, {}, {headers});
    }

    /**
     * @brief List all queues
     *
     * @par
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     *
     * @param prefix bucket name prefix
     * @param pageSize page size
     * @param pageIndex page index
     * @param sortColumns sorting columns
     */
    listQueueCounters(prefix, pageSize, pageIndex, sortColumns) {
        let headers = this.headers.set("x-awsmock-target", "sqs").set("x-awsmock-action", "ListQueueCounters");
        return this.http.post(this.url, {prefix, pageSize, pageIndex, sortColumns}, {headers});
    }

    /**
     * @brief List all messages for a queues
     *
     * @par
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     *
     * @param queueArn queue ARN
     * @param pageSize page size
     * @param pageIndex page index
     * @param sortColumns sorting columns
     */
    listSqsMessages(queueArn, pageSize, pageIndex, sortColumns) {
        let headers = this.headers.set("x-awsmock-target", "sqs").set("x-awsmock-action", "ListMessages");
        return this.http.post(this.url, {
            queueArn,
            pageSize,
            pageIndex,
            sortColumns
        }, {headers});
    }

    /**
     * @brief List queue details
     *
     * @par
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     *
     * @param queueArn SQS queue ARN
     */
    getQueueDetails(queueArn) {
        let headers = this.headers.set("x-awsmock-target", "sqs").set("x-awsmock-action", "GetQueueDetails");
        return this.http.post(this.url, {QueueArn: queueArn}, {headers});
    }

    /**
     * @brief List all queues
     *
     * @par
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     *
     * @param queueArn SQS queue ARN
     * @param prefix SQS message prefix
     * @param pageSize page size
     * @param pageIndex page index
     * @param sortColumns sorting columns
     */
    listMessageCounters(queueArn, prefix, pageSize, pageIndex, sortColumns) {
        let headers = this.headers.set("x-awsmock-target", "sqs").set("x-awsmock-action", "ListMessageCounters");
        return this.http.post(this.url, {queueArn, prefix, pageSize, pageIndex, sortColumns}, {headers});
    }

    /**
     * @brief Delete message
     *
     * @par
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     *
     * @param queueUrl SQS queue URL
     * @param receiptHandle SQS receipt handle
     */
    deleteMessageAws(queueUrl, receiptHandle) {
        let headers = this.headers.set("x-awsmock-target", "sqs").set("x-awsmock-action", "DeleteMessage");
        return this.http.post(this.url, {QueueUrl: queueUrl, ReceiptHandle: receiptHandle}, {headers});
    }

    static {
        this.\u0275fac = function SqsService_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _SqsService)(\u0275\u0275inject(HttpClient));
        };
    }
    static {
        this.\u0275prov = /* @__PURE__ */ \u0275\u0275defineInjectable({token: _SqsService, factory: _SqsService.\u0275fac, providedIn: "root"});
    }
};

export {
    SqsService
};
//# sourceMappingURL=chunk-7C5R5GF7.js.map

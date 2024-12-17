import {loadRestJsonErrorCode, parseJsonErrorBody} from "./chunk-HK7D4W5I.js";
import {eventStreamSerdeProvider, resolveEventStreamSerdeConfig} from "./chunk-XT3UHRHO.js";
import {
    awsEndpointFunctions,
    AwsSdkSigV4Signer,
    byteConversion,
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
    expectString,
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
    invalidProvider,
    loadConfigsForDefaultMode,
    map as map2,
    NoOpLogger,
    normalizeProvider,
    parseUrl,
    requestBuilder,
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
    toUtf8,
    withBaseException
} from "./chunk-5F2IFVYA.js";
import {MatTab, MatTabGroup} from "./chunk-GTOJ5AYX.js";
import {
    Actions,
    ActionsSubject,
    ActivatedRoute,
    AsyncPipe,
    catchError,
    createAction,
    createEffect,
    createFeatureSelector,
    createReducer,
    createSelector,
    DatePipe,
    debounceTime,
    DefaultValueAccessor,
    distinctUntilChanged,
    EffectsModule,
    environment,
    filter,
    FormsModule,
    HttpClient,
    HttpHeaders,
    inject,
    interval,
    LiveAnnouncer,
    Location,
    map,
    MatButton,
    MatCard,
    MatCardActions,
    MatCardContent,
    MatCardHeader,
    MatCardTitle,
    MatCell,
    MatCellDef,
    MatColumnDef,
    MatDialog,
    MatFormField,
    MatGridList,
    MatGridTile,
    MatHeaderCell,
    MatHeaderCellDef,
    MatHeaderRow,
    MatHeaderRowDef,
    MatIcon,
    MatIconButton,
    MatInput,
    MatLabel,
    MatList,
    MatListItem,
    MatNavList,
    MatNoDataRow,
    MatPaginator,
    MatRow,
    MatRowDef,
    MatSnackBar,
    MatSort,
    MatSortHeader,
    MatSortModule,
    MatSuffix,
    MatTable,
    MatTableDataSource,
    MatTooltip,
    merge,
    mergeMap,
    NgControlStatus,
    NgIf,
    NgModel,
    of,
    ofType,
    on,
    props,
    ReactiveFormsModule,
    Router,
    RouterLink,
    RouterModule,
    select,
    State,
    Store,
    StoreModule,
    Subject,
    Subscription,
    tap
} from "./chunk-LGOS2CJL.js";
import {__async, __spreadProps, __spreadValues} from "./chunk-G42SKTPL.js";

// src/app/modules/lambda/function-list/state/lambda-function-list.actions.ts
var lambdaFunctionListActions = {
    initialize: createAction("[lambda-function-list] initialize"),
    // Load functions
    loadFunctions: createAction("[lambda-function-list] Load functions", props()),
    loadFunctionsSuccess: createAction("[lambda-function-list] Load functions success", props()),
    loadFunctionsFailure: createAction("[lambda-function-list] Load functions error", props()),
    // Add function
    addFunction: createAction("[lambda-function-list] Add functions", props()),
    addFunctionSuccess: createAction("[lambda-function-list] Add functions success"),
    addFunctionFailure: createAction("[lambda-function-list] Add functions Error", props()),
    // ResetCounters
    resetCounters: createAction("[lambda-function-list] Reset counters", props()),
    resetCountersSuccess: createAction("[lambda-function-list] Reset counters success"),
    resetCountersFailure: createAction("[lambda-function-list] Reset counters error", props()),
    // Delete function
    deleteFunction: createAction("[lambda-function-list] Delete function", props()),
    deleteFunctionSuccess: createAction("[lambda-function-list] Delete function success"),
    deleteFunctionFailure: createAction("[lambda-function-list] Delete function error", props())
};

// src/app/modules/lambda/function-list/state/lambda-function-list.reducer.ts
var lambdaFunctionListFeatureKey = "lambda-function-list";
var initialState = {
    functionCounters: {total: 0, functionCounters: []},
    name: "",
    prefix: "",
    pageSize: 10,
    pageIndex: 0,
    loading: false,
    sortColumns: [{column: "name", sortDirection: -1}],
    total: 0,
    error: {}
};
var lambdaFunctionListReducer = createReducer(
    initialState,
    // Initialize
    on(lambdaFunctionListActions.initialize, (state) => __spreadProps(__spreadValues({}, state), {pageIndex: 0, pageSize: 10, loading: true})),
    // Function list
    on(lambdaFunctionListActions.loadFunctions, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(lambdaFunctionListActions.loadFunctionsSuccess, (state, {functions}) => __spreadProps(__spreadValues({}, state), {functionCounters: functions, loading: false})),
    on(lambdaFunctionListActions.loadFunctionsFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false})),
    // Add function
    on(lambdaFunctionListActions.addFunction, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(lambdaFunctionListActions.addFunctionSuccess, (state) => __spreadProps(__spreadValues({}, state), {loading: false})),
    on(lambdaFunctionListActions.addFunctionFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false})),
    // Reset counters
    on(lambdaFunctionListActions.resetCounters, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(lambdaFunctionListActions.resetCountersSuccess, (state) => __spreadProps(__spreadValues({}, state), {loading: false})),
    on(lambdaFunctionListActions.resetCountersFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false}))
);

// src/app/modules/lambda/function-list/state/lambda-function-list.selectors.ts
var selectFunctionListFeature = createFeatureSelector(lambdaFunctionListFeatureKey);
var selectIsLoading = createSelector(selectFunctionListFeature, (state) => state.loading);
var selectTotal = createSelector(selectFunctionListFeature, (state) => state.total);
var selectPrefix = createSelector(selectFunctionListFeature, (state) => state?.prefix);
var selectPageSize = createSelector(selectFunctionListFeature, (state) => state?.pageSize);
var selectPageIndex = createSelector(selectFunctionListFeature, (state) => state?.pageIndex);
var selectFunctionCounters = createSelector(selectFunctionListFeature, (state) => state?.functionCounters);

// node_modules/@aws-sdk/client-lambda/dist-es/auth/httpAuthSchemeProvider.js
var defaultLambdaHttpAuthSchemeParametersProvider = (config, context, input) => __async(void 0, null, function* () {
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
            name: "lambda",
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

var defaultLambdaHttpAuthSchemeProvider = (authParameters) => {
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

// node_modules/@aws-sdk/client-lambda/dist-es/endpoint/EndpointParameters.js
var resolveClientEndpointParameters = (options) => {
    return __spreadProps(__spreadValues({}, options), {
        useDualstackEndpoint: options.useDualstackEndpoint ?? false,
        useFipsEndpoint: options.useFipsEndpoint ?? false,
        defaultSigningName: "lambda"
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

// node_modules/@aws-sdk/client-lambda/package.json
var package_default = {
    name: "@aws-sdk/client-lambda",
    description: "AWS SDK for JavaScript Lambda Client for Node.js, Browser and React Native",
    version: "3.693.0",
    scripts: {
        build: "concurrently 'yarn:build:cjs' 'yarn:build:es' 'yarn:build:types'",
        "build:cjs": "node ../../scripts/compilation/inline client-lambda",
        "build:es": "tsc -p tsconfig.es.json",
        "build:include:deps": "lerna run --scope $npm_package_name --include-dependencies build",
        "build:types": "tsc -p tsconfig.types.json",
        "build:types:downlevel": "downlevel-dts dist-types dist-types/ts3.4",
        clean: "rimraf ./dist-* && rimraf *.tsbuildinfo",
        "extract:docs": "api-extractor run --local",
        "generate:client": "node ../../scripts/generate-clients/single-service --solo lambda"
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
        "@aws-sdk/middleware-user-agent": "3.693.0",
        "@aws-sdk/region-config-resolver": "3.693.0",
        "@aws-sdk/types": "3.692.0",
        "@aws-sdk/util-endpoints": "3.693.0",
        "@aws-sdk/util-user-agent-browser": "3.693.0",
        "@aws-sdk/util-user-agent-node": "3.693.0",
        "@smithy/config-resolver": "^3.0.11",
        "@smithy/core": "^2.5.2",
        "@smithy/eventstream-serde-browser": "^3.0.12",
        "@smithy/eventstream-serde-config-resolver": "^3.0.9",
        "@smithy/eventstream-serde-node": "^3.0.11",
        "@smithy/fetch-http-handler": "^4.1.0",
        "@smithy/hash-node": "^3.0.9",
        "@smithy/invalid-dependency": "^3.0.9",
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
        "@smithy/util-stream": "^3.3.0",
        "@smithy/util-utf8": "^3.0.0",
        "@smithy/util-waiter": "^3.1.8",
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
    homepage: "https://github.com/aws/aws-sdk-js-v3/tree/main/clients/client-lambda",
    repository: {
        type: "git",
        url: "https://github.com/aws/aws-sdk-js-v3.git",
        directory: "clients/client-lambda"
    }
};

// node_modules/@aws-sdk/client-lambda/dist-es/endpoint/ruleset.js
var s = "required";
var t = "fn";
var u = "argv";
var v = "ref";
var a = true;
var b = "isSet";
var c = "booleanEquals";
var d = "error";
var e = "endpoint";
var f = "tree";
var g = "PartitionResult";
var h = {
    [s]: false,
    "type": "String"
};
var i = {
    [s]: true,
    "default": false,
    "type": "Boolean"
};
var j = {
    [v]: "Endpoint"
};
var k = {
    [t]: c,
    [u]: [{
        [v]: "UseFIPS"
    }, true]
};
var l = {
    [t]: c,
    [u]: [{
        [v]: "UseDualStack"
    }, true]
};
var m = {};
var n = {
    [t]: "getAttr",
    [u]: [{
        [v]: g
    }, "supportsFIPS"]
};
var o = {
    [t]: c,
    [u]: [true, {
        [t]: "getAttr",
        [u]: [{
            [v]: g
        }, "supportsDualStack"]
    }]
};
var p = [k];
var q = [l];
var r = [{
    [v]: "Region"
}];
var _data = {
    version: "1.0",
    parameters: {
        Region: h,
        UseDualStack: i,
        UseFIPS: i,
        Endpoint: h
    },
    rules: [{
        conditions: [{
            [t]: b,
            [u]: [j]
        }],
        rules: [{
            conditions: p,
            error: "Invalid Configuration: FIPS and custom endpoint are not supported",
            type: d
        }, {
            conditions: q,
            error: "Invalid Configuration: Dualstack and custom endpoint are not supported",
            type: d
        }, {
            endpoint: {
                url: j,
                properties: m,
                headers: m
            },
            type: e
        }],
        type: f
    }, {
        conditions: [{
            [t]: b,
            [u]: r
        }],
        rules: [{
            conditions: [{
                [t]: "aws.partition",
                [u]: r,
                assign: g
            }],
            rules: [{
                conditions: [k, l],
                rules: [{
                    conditions: [{
                        [t]: c,
                        [u]: [a, n]
                    }, o],
                    rules: [{
                        endpoint: {
                            url: "https://lambda-fips.{Region}.{PartitionResult#dualStackDnsSuffix}",
                            properties: m,
                            headers: m
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
                conditions: p,
                rules: [{
                    conditions: [{
                        [t]: c,
                        [u]: [n, a]
                    }],
                    rules: [{
                        endpoint: {
                            url: "https://lambda-fips.{Region}.{PartitionResult#dnsSuffix}",
                            properties: m,
                            headers: m
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
                conditions: q,
                rules: [{
                    conditions: [o],
                    rules: [{
                        endpoint: {
                            url: "https://lambda.{Region}.{PartitionResult#dualStackDnsSuffix}",
                            properties: m,
                            headers: m
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
                    url: "https://lambda.{Region}.{PartitionResult#dnsSuffix}",
                    properties: m,
                    headers: m
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

// node_modules/@aws-sdk/client-lambda/dist-es/endpoint/endpointResolver.js
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

// node_modules/@aws-sdk/client-lambda/dist-es/runtimeConfig.shared.js
var getRuntimeConfig = (config) => {
    return {
        apiVersion: "2015-03-31",
        base64Decoder: config?.base64Decoder ?? fromBase64,
        base64Encoder: config?.base64Encoder ?? toBase64,
        disableHostPrefix: config?.disableHostPrefix ?? false,
        endpointProvider: config?.endpointProvider ?? defaultEndpointResolver,
        extensions: config?.extensions ?? [],
        httpAuthSchemeProvider: config?.httpAuthSchemeProvider ?? defaultLambdaHttpAuthSchemeProvider,
        httpAuthSchemes: config?.httpAuthSchemes ?? [{
            schemeId: "aws.auth#sigv4",
            identityProvider: (ipc) => ipc.getIdentityProvider("aws.auth#sigv4"),
            signer: new AwsSdkSigV4Signer()
        }],
        logger: config?.logger ?? new NoOpLogger(),
        serviceId: config?.serviceId ?? "Lambda",
        urlParser: config?.urlParser ?? parseUrl,
        utf8Decoder: config?.utf8Decoder ?? fromUtf8,
        utf8Encoder: config?.utf8Encoder ?? toUtf8
    };
};

// node_modules/@aws-sdk/client-lambda/dist-es/runtimeConfig.browser.js
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
        eventStreamSerdeProvider: config?.eventStreamSerdeProvider ?? eventStreamSerdeProvider,
        maxAttempts: config?.maxAttempts ?? DEFAULT_MAX_ATTEMPTS,
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

// node_modules/@aws-sdk/client-lambda/dist-es/auth/httpAuthExtensionConfiguration.js
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

// node_modules/@aws-sdk/client-lambda/dist-es/runtimeExtensions.js
var asPartial = (t2) => t2;
var resolveRuntimeExtensions = (runtimeConfig, extensions) => {
    const extensionConfiguration = __spreadValues(__spreadValues(__spreadValues(__spreadValues({}, asPartial(getAwsRegionExtensionConfiguration(runtimeConfig))), asPartial(getDefaultExtensionConfiguration(runtimeConfig))), asPartial(getHttpHandlerExtensionConfiguration(runtimeConfig))), asPartial(getHttpAuthExtensionConfiguration(runtimeConfig)));
    extensions.forEach((extension) => extension.configure(extensionConfiguration));
    return __spreadValues(__spreadValues(__spreadValues(__spreadValues(__spreadValues({}, runtimeConfig), resolveAwsRegionExtensionConfiguration(extensionConfiguration)), resolveDefaultRuntimeConfig(extensionConfiguration)), resolveHttpHandlerRuntimeConfig(extensionConfiguration)), resolveHttpAuthRuntimeConfig(extensionConfiguration));
};

// node_modules/@aws-sdk/client-lambda/dist-es/LambdaClient.js
var LambdaClient = class extends Client {
    constructor(...[configuration]) {
        const _config_0 = getRuntimeConfig2(configuration || {});
        const _config_1 = resolveClientEndpointParameters(_config_0);
        const _config_2 = resolveUserAgentConfig(_config_1);
        const _config_3 = resolveRetryConfig(_config_2);
        const _config_4 = resolveRegionConfig(_config_3);
        const _config_5 = resolveHostHeaderConfig(_config_4);
        const _config_6 = resolveEndpointConfig(_config_5);
        const _config_7 = resolveEventStreamSerdeConfig(_config_6);
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
        this.middlewareStack.use(getHttpAuthSchemeEndpointRuleSetPlugin(this.config, {
            httpAuthSchemeParametersProvider: defaultLambdaHttpAuthSchemeParametersProvider,
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

// node_modules/@aws-sdk/client-lambda/dist-es/models/LambdaServiceException.js
var LambdaServiceException = class _LambdaServiceException extends ServiceException {
    constructor(options) {
        super(options);
        Object.setPrototypeOf(this, _LambdaServiceException.prototype);
    }
};

// node_modules/@aws-sdk/client-lambda/dist-es/models/models_0.js
var InvalidParameterValueException = class _InvalidParameterValueException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "InvalidParameterValueException",
            $fault: "client"
        }, opts));
        this.name = "InvalidParameterValueException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _InvalidParameterValueException.prototype);
        this.Type = opts.Type;
    }
};
var PolicyLengthExceededException = class _PolicyLengthExceededException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "PolicyLengthExceededException",
            $fault: "client"
        }, opts));
        this.name = "PolicyLengthExceededException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _PolicyLengthExceededException.prototype);
        this.Type = opts.Type;
    }
};
var PreconditionFailedException = class _PreconditionFailedException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "PreconditionFailedException",
            $fault: "client"
        }, opts));
        this.name = "PreconditionFailedException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _PreconditionFailedException.prototype);
        this.Type = opts.Type;
    }
};
var ResourceConflictException = class _ResourceConflictException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "ResourceConflictException",
            $fault: "client"
        }, opts));
        this.name = "ResourceConflictException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _ResourceConflictException.prototype);
        this.Type = opts.Type;
    }
};
var ResourceNotFoundException = class _ResourceNotFoundException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "ResourceNotFoundException",
            $fault: "client"
        }, opts));
        this.name = "ResourceNotFoundException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _ResourceNotFoundException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var ServiceException2 = class _ServiceException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "ServiceException",
            $fault: "server"
        }, opts));
        this.name = "ServiceException";
        this.$fault = "server";
        Object.setPrototypeOf(this, _ServiceException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var TooManyRequestsException = class _TooManyRequestsException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "TooManyRequestsException",
            $fault: "client"
        }, opts));
        this.name = "TooManyRequestsException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _TooManyRequestsException.prototype);
        this.retryAfterSeconds = opts.retryAfterSeconds;
        this.Type = opts.Type;
        this.Reason = opts.Reason;
    }
};
var CodeSigningConfigNotFoundException = class _CodeSigningConfigNotFoundException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "CodeSigningConfigNotFoundException",
            $fault: "client"
        }, opts));
        this.name = "CodeSigningConfigNotFoundException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _CodeSigningConfigNotFoundException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var CodeStorageExceededException = class _CodeStorageExceededException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "CodeStorageExceededException",
            $fault: "client"
        }, opts));
        this.name = "CodeStorageExceededException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _CodeStorageExceededException.prototype);
        this.Type = opts.Type;
    }
};
var CodeVerificationFailedException = class _CodeVerificationFailedException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "CodeVerificationFailedException",
            $fault: "client"
        }, opts));
        this.name = "CodeVerificationFailedException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _CodeVerificationFailedException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var InvalidCodeSignatureException = class _InvalidCodeSignatureException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "InvalidCodeSignatureException",
            $fault: "client"
        }, opts));
        this.name = "InvalidCodeSignatureException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _InvalidCodeSignatureException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var ResourceInUseException = class _ResourceInUseException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "ResourceInUseException",
            $fault: "client"
        }, opts));
        this.name = "ResourceInUseException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _ResourceInUseException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var ProvisionedConcurrencyConfigNotFoundException = class _ProvisionedConcurrencyConfigNotFoundException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "ProvisionedConcurrencyConfigNotFoundException",
            $fault: "client"
        }, opts));
        this.name = "ProvisionedConcurrencyConfigNotFoundException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _ProvisionedConcurrencyConfigNotFoundException.prototype);
        this.Type = opts.Type;
    }
};
var EC2AccessDeniedException = class _EC2AccessDeniedException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "EC2AccessDeniedException",
            $fault: "server"
        }, opts));
        this.name = "EC2AccessDeniedException";
        this.$fault = "server";
        Object.setPrototypeOf(this, _EC2AccessDeniedException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var EC2ThrottledException = class _EC2ThrottledException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "EC2ThrottledException",
            $fault: "server"
        }, opts));
        this.name = "EC2ThrottledException";
        this.$fault = "server";
        Object.setPrototypeOf(this, _EC2ThrottledException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var EC2UnexpectedException = class _EC2UnexpectedException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "EC2UnexpectedException",
            $fault: "server"
        }, opts));
        this.name = "EC2UnexpectedException";
        this.$fault = "server";
        Object.setPrototypeOf(this, _EC2UnexpectedException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
        this.EC2ErrorCode = opts.EC2ErrorCode;
    }
};
var EFSIOException = class _EFSIOException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "EFSIOException",
            $fault: "client"
        }, opts));
        this.name = "EFSIOException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _EFSIOException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var EFSMountConnectivityException = class _EFSMountConnectivityException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "EFSMountConnectivityException",
            $fault: "client"
        }, opts));
        this.name = "EFSMountConnectivityException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _EFSMountConnectivityException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var EFSMountFailureException = class _EFSMountFailureException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "EFSMountFailureException",
            $fault: "client"
        }, opts));
        this.name = "EFSMountFailureException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _EFSMountFailureException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var EFSMountTimeoutException = class _EFSMountTimeoutException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "EFSMountTimeoutException",
            $fault: "client"
        }, opts));
        this.name = "EFSMountTimeoutException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _EFSMountTimeoutException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var ENILimitReachedException = class _ENILimitReachedException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "ENILimitReachedException",
            $fault: "server"
        }, opts));
        this.name = "ENILimitReachedException";
        this.$fault = "server";
        Object.setPrototypeOf(this, _ENILimitReachedException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var InvalidRequestContentException = class _InvalidRequestContentException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "InvalidRequestContentException",
            $fault: "client"
        }, opts));
        this.name = "InvalidRequestContentException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _InvalidRequestContentException.prototype);
        this.Type = opts.Type;
    }
};
var InvalidRuntimeException = class _InvalidRuntimeException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "InvalidRuntimeException",
            $fault: "server"
        }, opts));
        this.name = "InvalidRuntimeException";
        this.$fault = "server";
        Object.setPrototypeOf(this, _InvalidRuntimeException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var InvalidSecurityGroupIDException = class _InvalidSecurityGroupIDException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "InvalidSecurityGroupIDException",
            $fault: "server"
        }, opts));
        this.name = "InvalidSecurityGroupIDException";
        this.$fault = "server";
        Object.setPrototypeOf(this, _InvalidSecurityGroupIDException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var InvalidSubnetIDException = class _InvalidSubnetIDException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "InvalidSubnetIDException",
            $fault: "server"
        }, opts));
        this.name = "InvalidSubnetIDException";
        this.$fault = "server";
        Object.setPrototypeOf(this, _InvalidSubnetIDException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var InvalidZipFileException = class _InvalidZipFileException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "InvalidZipFileException",
            $fault: "server"
        }, opts));
        this.name = "InvalidZipFileException";
        this.$fault = "server";
        Object.setPrototypeOf(this, _InvalidZipFileException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var KMSAccessDeniedException = class _KMSAccessDeniedException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "KMSAccessDeniedException",
            $fault: "server"
        }, opts));
        this.name = "KMSAccessDeniedException";
        this.$fault = "server";
        Object.setPrototypeOf(this, _KMSAccessDeniedException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var KMSDisabledException = class _KMSDisabledException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "KMSDisabledException",
            $fault: "server"
        }, opts));
        this.name = "KMSDisabledException";
        this.$fault = "server";
        Object.setPrototypeOf(this, _KMSDisabledException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var KMSInvalidStateException = class _KMSInvalidStateException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "KMSInvalidStateException",
            $fault: "server"
        }, opts));
        this.name = "KMSInvalidStateException";
        this.$fault = "server";
        Object.setPrototypeOf(this, _KMSInvalidStateException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var KMSNotFoundException = class _KMSNotFoundException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "KMSNotFoundException",
            $fault: "server"
        }, opts));
        this.name = "KMSNotFoundException";
        this.$fault = "server";
        Object.setPrototypeOf(this, _KMSNotFoundException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var RecursiveInvocationException = class _RecursiveInvocationException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "RecursiveInvocationException",
            $fault: "client"
        }, opts));
        this.name = "RecursiveInvocationException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _RecursiveInvocationException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var RequestTooLargeException = class _RequestTooLargeException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "RequestTooLargeException",
            $fault: "client"
        }, opts));
        this.name = "RequestTooLargeException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _RequestTooLargeException.prototype);
        this.Type = opts.Type;
    }
};
var ResourceNotReadyException = class _ResourceNotReadyException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "ResourceNotReadyException",
            $fault: "server"
        }, opts));
        this.name = "ResourceNotReadyException";
        this.$fault = "server";
        Object.setPrototypeOf(this, _ResourceNotReadyException.prototype);
        this.Type = opts.Type;
    }
};
var SnapStartException = class _SnapStartException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "SnapStartException",
            $fault: "client"
        }, opts));
        this.name = "SnapStartException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _SnapStartException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var SnapStartNotReadyException = class _SnapStartNotReadyException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "SnapStartNotReadyException",
            $fault: "client"
        }, opts));
        this.name = "SnapStartNotReadyException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _SnapStartNotReadyException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var SnapStartTimeoutException = class _SnapStartTimeoutException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "SnapStartTimeoutException",
            $fault: "client"
        }, opts));
        this.name = "SnapStartTimeoutException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _SnapStartTimeoutException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var SubnetIPAddressLimitReachedException = class _SubnetIPAddressLimitReachedException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "SubnetIPAddressLimitReachedException",
            $fault: "server"
        }, opts));
        this.name = "SubnetIPAddressLimitReachedException";
        this.$fault = "server";
        Object.setPrototypeOf(this, _SubnetIPAddressLimitReachedException.prototype);
        this.Type = opts.Type;
        this.Message = opts.Message;
    }
};
var UnsupportedMediaTypeException = class _UnsupportedMediaTypeException extends LambdaServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "UnsupportedMediaTypeException",
            $fault: "client"
        }, opts));
        this.name = "UnsupportedMediaTypeException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _UnsupportedMediaTypeException.prototype);
        this.Type = opts.Type;
    }
};
var InvokeWithResponseStreamResponseEvent;
(function (InvokeWithResponseStreamResponseEvent2) {
    InvokeWithResponseStreamResponseEvent2.visit = (value, visitor) => {
        if (value.PayloadChunk !== void 0) return visitor.PayloadChunk(value.PayloadChunk);
        if (value.InvokeComplete !== void 0) return visitor.InvokeComplete(value.InvokeComplete);
        return visitor._(value.$unknown[0], value.$unknown[1]);
    };
})(InvokeWithResponseStreamResponseEvent || (InvokeWithResponseStreamResponseEvent = {}));

// node_modules/@aws-sdk/client-lambda/dist-es/protocols/Aws_restJson1.js
var se_DeleteFunctionCommand = (input, context) => __async(void 0, null, function* () {
    const b2 = requestBuilder(input, context);
    const headers = {};
    b2.bp("/2015-03-31/functions/{FunctionName}");
    b2.p("FunctionName", () => input.FunctionName, "{FunctionName}", false);
    const query = map2({
        [_Q]: [, input[_Q]]
    });
    let body;
    b2.m("DELETE").h(headers).q(query).b(body);
    return b2.build();
});
var de_DeleteFunctionCommand = (output, context) => __async(void 0, null, function* () {
    if (output.statusCode !== 204 && output.statusCode >= 300) {
        return de_CommandError(output, context);
    }
    const contents = map2({
        $metadata: deserializeMetadata(output)
    });
    yield collectBody(output.body, context);
    return contents;
});
var de_CommandError = (output, context) => __async(void 0, null, function* () {
    const parsedOutput = __spreadProps(__spreadValues({}, output), {
        body: yield parseJsonErrorBody(output.body, context)
    });
    const errorCode = loadRestJsonErrorCode(output, parsedOutput.body);
    switch (errorCode) {
        case "InvalidParameterValueException":
        case "com.amazonaws.lambda#InvalidParameterValueException":
            throw yield de_InvalidParameterValueExceptionRes(parsedOutput, context);
        case "PolicyLengthExceededException":
        case "com.amazonaws.lambda#PolicyLengthExceededException":
            throw yield de_PolicyLengthExceededExceptionRes(parsedOutput, context);
        case "PreconditionFailedException":
        case "com.amazonaws.lambda#PreconditionFailedException":
            throw yield de_PreconditionFailedExceptionRes(parsedOutput, context);
        case "ResourceConflictException":
        case "com.amazonaws.lambda#ResourceConflictException":
            throw yield de_ResourceConflictExceptionRes(parsedOutput, context);
        case "ResourceNotFoundException":
        case "com.amazonaws.lambda#ResourceNotFoundException":
            throw yield de_ResourceNotFoundExceptionRes(parsedOutput, context);
        case "ServiceException":
        case "com.amazonaws.lambda#ServiceException":
            throw yield de_ServiceExceptionRes(parsedOutput, context);
        case "TooManyRequestsException":
        case "com.amazonaws.lambda#TooManyRequestsException":
            throw yield de_TooManyRequestsExceptionRes(parsedOutput, context);
        case "CodeSigningConfigNotFoundException":
        case "com.amazonaws.lambda#CodeSigningConfigNotFoundException":
            throw yield de_CodeSigningConfigNotFoundExceptionRes(parsedOutput, context);
        case "CodeStorageExceededException":
        case "com.amazonaws.lambda#CodeStorageExceededException":
            throw yield de_CodeStorageExceededExceptionRes(parsedOutput, context);
        case "CodeVerificationFailedException":
        case "com.amazonaws.lambda#CodeVerificationFailedException":
            throw yield de_CodeVerificationFailedExceptionRes(parsedOutput, context);
        case "InvalidCodeSignatureException":
        case "com.amazonaws.lambda#InvalidCodeSignatureException":
            throw yield de_InvalidCodeSignatureExceptionRes(parsedOutput, context);
        case "ResourceInUseException":
        case "com.amazonaws.lambda#ResourceInUseException":
            throw yield de_ResourceInUseExceptionRes(parsedOutput, context);
        case "ProvisionedConcurrencyConfigNotFoundException":
        case "com.amazonaws.lambda#ProvisionedConcurrencyConfigNotFoundException":
            throw yield de_ProvisionedConcurrencyConfigNotFoundExceptionRes(parsedOutput, context);
        case "EC2AccessDeniedException":
        case "com.amazonaws.lambda#EC2AccessDeniedException":
            throw yield de_EC2AccessDeniedExceptionRes(parsedOutput, context);
        case "EC2ThrottledException":
        case "com.amazonaws.lambda#EC2ThrottledException":
            throw yield de_EC2ThrottledExceptionRes(parsedOutput, context);
        case "EC2UnexpectedException":
        case "com.amazonaws.lambda#EC2UnexpectedException":
            throw yield de_EC2UnexpectedExceptionRes(parsedOutput, context);
        case "EFSIOException":
        case "com.amazonaws.lambda#EFSIOException":
            throw yield de_EFSIOExceptionRes(parsedOutput, context);
        case "EFSMountConnectivityException":
        case "com.amazonaws.lambda#EFSMountConnectivityException":
            throw yield de_EFSMountConnectivityExceptionRes(parsedOutput, context);
        case "EFSMountFailureException":
        case "com.amazonaws.lambda#EFSMountFailureException":
            throw yield de_EFSMountFailureExceptionRes(parsedOutput, context);
        case "EFSMountTimeoutException":
        case "com.amazonaws.lambda#EFSMountTimeoutException":
            throw yield de_EFSMountTimeoutExceptionRes(parsedOutput, context);
        case "ENILimitReachedException":
        case "com.amazonaws.lambda#ENILimitReachedException":
            throw yield de_ENILimitReachedExceptionRes(parsedOutput, context);
        case "InvalidRequestContentException":
        case "com.amazonaws.lambda#InvalidRequestContentException":
            throw yield de_InvalidRequestContentExceptionRes(parsedOutput, context);
        case "InvalidRuntimeException":
        case "com.amazonaws.lambda#InvalidRuntimeException":
            throw yield de_InvalidRuntimeExceptionRes(parsedOutput, context);
        case "InvalidSecurityGroupIDException":
        case "com.amazonaws.lambda#InvalidSecurityGroupIDException":
            throw yield de_InvalidSecurityGroupIDExceptionRes(parsedOutput, context);
        case "InvalidSubnetIDException":
        case "com.amazonaws.lambda#InvalidSubnetIDException":
            throw yield de_InvalidSubnetIDExceptionRes(parsedOutput, context);
        case "InvalidZipFileException":
        case "com.amazonaws.lambda#InvalidZipFileException":
            throw yield de_InvalidZipFileExceptionRes(parsedOutput, context);
        case "KMSAccessDeniedException":
        case "com.amazonaws.lambda#KMSAccessDeniedException":
            throw yield de_KMSAccessDeniedExceptionRes(parsedOutput, context);
        case "KMSDisabledException":
        case "com.amazonaws.lambda#KMSDisabledException":
            throw yield de_KMSDisabledExceptionRes(parsedOutput, context);
        case "KMSInvalidStateException":
        case "com.amazonaws.lambda#KMSInvalidStateException":
            throw yield de_KMSInvalidStateExceptionRes(parsedOutput, context);
        case "KMSNotFoundException":
        case "com.amazonaws.lambda#KMSNotFoundException":
            throw yield de_KMSNotFoundExceptionRes(parsedOutput, context);
        case "RecursiveInvocationException":
        case "com.amazonaws.lambda#RecursiveInvocationException":
            throw yield de_RecursiveInvocationExceptionRes(parsedOutput, context);
        case "RequestTooLargeException":
        case "com.amazonaws.lambda#RequestTooLargeException":
            throw yield de_RequestTooLargeExceptionRes(parsedOutput, context);
        case "ResourceNotReadyException":
        case "com.amazonaws.lambda#ResourceNotReadyException":
            throw yield de_ResourceNotReadyExceptionRes(parsedOutput, context);
        case "SnapStartException":
        case "com.amazonaws.lambda#SnapStartException":
            throw yield de_SnapStartExceptionRes(parsedOutput, context);
        case "SnapStartNotReadyException":
        case "com.amazonaws.lambda#SnapStartNotReadyException":
            throw yield de_SnapStartNotReadyExceptionRes(parsedOutput, context);
        case "SnapStartTimeoutException":
        case "com.amazonaws.lambda#SnapStartTimeoutException":
            throw yield de_SnapStartTimeoutExceptionRes(parsedOutput, context);
        case "SubnetIPAddressLimitReachedException":
        case "com.amazonaws.lambda#SubnetIPAddressLimitReachedException":
            throw yield de_SubnetIPAddressLimitReachedExceptionRes(parsedOutput, context);
        case "UnsupportedMediaTypeException":
        case "com.amazonaws.lambda#UnsupportedMediaTypeException":
            throw yield de_UnsupportedMediaTypeExceptionRes(parsedOutput, context);
        default:
            const parsedBody = parsedOutput.body;
            return throwDefaultError({
                output,
                parsedBody,
                errorCode
            });
    }
});
var throwDefaultError = withBaseException(LambdaServiceException);
var de_CodeSigningConfigNotFoundExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new CodeSigningConfigNotFoundException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_CodeStorageExceededExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Type: expectString,
        message: expectString
    });
    Object.assign(contents, doc);
    const exception = new CodeStorageExceededException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_CodeVerificationFailedExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new CodeVerificationFailedException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_EC2AccessDeniedExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new EC2AccessDeniedException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_EC2ThrottledExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new EC2ThrottledException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_EC2UnexpectedExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        EC2ErrorCode: expectString,
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new EC2UnexpectedException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_EFSIOExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new EFSIOException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_EFSMountConnectivityExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new EFSMountConnectivityException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_EFSMountFailureExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new EFSMountFailureException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_EFSMountTimeoutExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new EFSMountTimeoutException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_ENILimitReachedExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new ENILimitReachedException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_InvalidCodeSignatureExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new InvalidCodeSignatureException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_InvalidParameterValueExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Type: expectString,
        message: expectString
    });
    Object.assign(contents, doc);
    const exception = new InvalidParameterValueException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_InvalidRequestContentExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Type: expectString,
        message: expectString
    });
    Object.assign(contents, doc);
    const exception = new InvalidRequestContentException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_InvalidRuntimeExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new InvalidRuntimeException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_InvalidSecurityGroupIDExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new InvalidSecurityGroupIDException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_InvalidSubnetIDExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new InvalidSubnetIDException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_InvalidZipFileExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new InvalidZipFileException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_KMSAccessDeniedExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new KMSAccessDeniedException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_KMSDisabledExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new KMSDisabledException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_KMSInvalidStateExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new KMSInvalidStateException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_KMSNotFoundExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new KMSNotFoundException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_PolicyLengthExceededExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Type: expectString,
        message: expectString
    });
    Object.assign(contents, doc);
    const exception = new PolicyLengthExceededException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_PreconditionFailedExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Type: expectString,
        message: expectString
    });
    Object.assign(contents, doc);
    const exception = new PreconditionFailedException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_ProvisionedConcurrencyConfigNotFoundExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Type: expectString,
        message: expectString
    });
    Object.assign(contents, doc);
    const exception = new ProvisionedConcurrencyConfigNotFoundException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_RecursiveInvocationExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new RecursiveInvocationException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_RequestTooLargeExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Type: expectString,
        message: expectString
    });
    Object.assign(contents, doc);
    const exception = new RequestTooLargeException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_ResourceConflictExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Type: expectString,
        message: expectString
    });
    Object.assign(contents, doc);
    const exception = new ResourceConflictException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_ResourceInUseExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new ResourceInUseException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_ResourceNotFoundExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new ResourceNotFoundException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_ResourceNotReadyExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Type: expectString,
        message: expectString
    });
    Object.assign(contents, doc);
    const exception = new ResourceNotReadyException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_ServiceExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new ServiceException2(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_SnapStartExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new SnapStartException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_SnapStartNotReadyExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new SnapStartNotReadyException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_SnapStartTimeoutExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new SnapStartTimeoutException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_SubnetIPAddressLimitReachedExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Message: expectString,
        Type: expectString
    });
    Object.assign(contents, doc);
    const exception = new SubnetIPAddressLimitReachedException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_TooManyRequestsExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({
        [_rAS]: [, parsedOutput.headers[_ra]]
    });
    const data = parsedOutput.body;
    const doc = take(data, {
        Reason: expectString,
        Type: expectString,
        message: expectString
    });
    Object.assign(contents, doc);
    const exception = new TooManyRequestsException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_UnsupportedMediaTypeExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const doc = take(data, {
        Type: expectString,
        message: expectString
    });
    Object.assign(contents, doc);
    const exception = new UnsupportedMediaTypeException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var deserializeMetadata = (output) => ({
    httpStatusCode: output.statusCode,
    requestId: output.headers["x-amzn-requestid"] ?? output.headers["x-amzn-request-id"] ?? output.headers["x-amz-request-id"],
    extendedRequestId: output.headers["x-amz-id-2"],
    cfId: output.headers["x-amz-cf-id"]
});
var _Q = "Qualifier";
var _rAS = "retryAfterSeconds";
var _ra = "retry-after";

// node_modules/@aws-sdk/client-lambda/dist-es/commands/DeleteFunctionCommand.js
var DeleteFunctionCommand = class extends Command.classBuilder().ep(commonParams).m(function (Command2, cs, config, o2) {
    return [getSerdePlugin(config, this.serialize, this.deserialize), getEndpointPlugin(config, Command2.getEndpointParameterInstructions())];
}).s("AWSGirApiService", "DeleteFunction", {}).n("LambdaClient", "DeleteFunctionCommand").f(void 0, void 0).ser(se_DeleteFunctionCommand).de(de_DeleteFunctionCommand).build() {
};

// src/app/modules/lambda/service/lambda-service.component.ts
var LambdaService = class _LambdaService {
    constructor(http) {
        this.http = http;
        this.client = new LambdaClient({
            region: environment.awsmockRegion,
            endpoint: environment.gatewayEndpoint,
            credentials: {
                accessKeyId: "none",
                secretAccessKey: "none"
            },
            requestHandler: {
                requestTimeout: 3e3,
                httpsAgent: {maxSockets: 25, keepAlive: false}
            }
        });
        this.headers = new HttpHeaders({
            "Content-Type": "application/json",
            "Authorization": "AWS4-HMAC-SHA256 Credential=none/20240928/eu-central-1/s3/aws4_request, SignedHeaders=content-type;host;x-amz-date;x-amz-security-token;x-amz-target, Signature=01316d694335ec0e0bf68b08570490f1b0bae0b130ecbe13ebad511b3ece8a41"
        });
        this.url = environment.gatewayEndpoint + "/";
    }

    /**
     * @brief List all function counters
     *
     * @par
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     *
     * @param prefix bucket name prefix
     * @param pageSize page size
     * @param pageIndex page index
     * @param sortColumns sorting columns
     */
    listFunctionCounters(prefix, pageSize, pageIndex, sortColumns) {
        let headers = this.headers.set("x-awsmock-target", "lambda").set("x-awsmock-action", "ListFunctionCounters");
        const body = {
            region: environment.awsmockRegion,
            prefix,
            maxResults: pageSize,
            skip: pageSize * pageIndex,
            sortColumns
        };
        return this.http.post(this.url, body, {headers});
    }

    /**
     * @brief Get a single function counter
     *
     * @par
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     *
     * @param name function name
     */
    getFunction(name) {
        let headers = this.headers.set("x-awsmock-target", "lambda").set("x-awsmock-action", "GetFunctionCounters");
        const body = {
            region: environment.awsmockRegion,
            functionName: name
        };
        return this.http.post(this.url, body, {headers});
    }

    /**
     * @brief Reset the function counters
     *
     * @par
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     *
     * @param name function name
     */
    resetCounters(name) {
        let headers = this.headers.set("x-awsmock-target", "lambda").set("x-awsmock-action", "ResetFunctionCounters");
        const body = {
            region: environment.awsmockRegion,
            functionName: name
        };
        return this.http.post(this.url, body, {headers});
    }

    /**
     * @brief Get a single function counter
     *
     * @par
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     *
     * @param functionName function name
     */
    deleteFunction(functionName) {
        const input = {
            FunctionName: functionName
        };
        return this.client.send(new DeleteFunctionCommand(input));
    }

    static {
        this.\u0275fac = function LambdaService_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _LambdaService)(\u0275\u0275inject(HttpClient));
        };
    }
    static {
        this.\u0275prov = /* @__PURE__ */ \u0275\u0275defineInjectable({token: _LambdaService, factory: _LambdaService.\u0275fac, providedIn: "root"});
    }
};

// src/app/modules/lambda/function-list/function-list.component.ts
var _c0 = () => [];

function LambdaFunctionListComponent_button_18_Template(rf, ctx) {
    if (rf & 1) {
        const _r1 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "button", 12);
        \u0275\u0275listener("click", function LambdaFunctionListComponent_button_18_Template_button_click_0_listener() {
            \u0275\u0275restoreView(_r1);
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.setPrefix());
        });
        \u0275\u0275elementStart(1, "mat-icon", 13);
        \u0275\u0275text(2, "search");
        \u0275\u0275elementEnd()();
    }
}

function LambdaFunctionListComponent_button_19_Template(rf, ctx) {
    if (rf & 1) {
        const _r3 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "button", 12);
        \u0275\u0275listener("click", function LambdaFunctionListComponent_button_19_Template_button_click_0_listener() {
            \u0275\u0275restoreView(_r3);
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.unsetPrefix());
        });
        \u0275\u0275elementStart(1, "mat-icon", 13);
        \u0275\u0275text(2, "close");
        \u0275\u0275elementEnd()();
    }
}

function LambdaFunctionListComponent_div_21_th_3_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 30);
        \u0275\u0275text(1, "Name");
        \u0275\u0275elementEnd();
    }
}

function LambdaFunctionListComponent_div_21_td_4_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 31)(1, "mat-nav-list")(2, "a", 32);
        \u0275\u0275text(3);
        \u0275\u0275elementEnd()()();
    }
    if (rf & 2) {
        const element_r5 = ctx.$implicit;
        \u0275\u0275advance(2);
        \u0275\u0275propertyInterpolate1("routerLink", "./details/", element_r5.functionName, "");
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r5.functionName, "");
    }
}

function LambdaFunctionListComponent_div_21_th_6_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 33);
        \u0275\u0275text(1, "Runtime");
        \u0275\u0275elementEnd();
    }
}

function LambdaFunctionListComponent_div_21_td_7_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 31);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r6 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r6.runtime, "");
    }
}

function LambdaFunctionListComponent_div_21_th_9_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 34);
        \u0275\u0275text(1, "Invocations");
        \u0275\u0275elementEnd();
    }
}

function LambdaFunctionListComponent_div_21_td_10_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 31);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r7 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r7.invocations, "");
    }
}

function LambdaFunctionListComponent_div_21_th_12_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 35);
        \u0275\u0275text(1, "Execution Time (ms) ");
        \u0275\u0275elementEnd();
    }
}

function LambdaFunctionListComponent_div_21_td_13_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 31);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r8 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r8.averageRuntime, "");
    }
}

function LambdaFunctionListComponent_div_21_th_15_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 36);
        \u0275\u0275text(1, "Actions");
        \u0275\u0275elementEnd();
    }
}

function LambdaFunctionListComponent_div_21_td_16_Template(rf, ctx) {
    if (rf & 1) {
        const _r9 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "td", 31)(1, "button", 37);
        \u0275\u0275listener("click", function LambdaFunctionListComponent_div_21_td_16_Template_button_click_1_listener() {
            const row_r10 = \u0275\u0275restoreView(_r9).$implicit;
            const ctx_r1 = \u0275\u0275nextContext(2);
            return \u0275\u0275resetView(ctx_r1.resetCounters(row_r10.functionName));
        });
        \u0275\u0275elementStart(2, "mat-icon");
        \u0275\u0275text(3, "history");
        \u0275\u0275elementEnd()();
        \u0275\u0275elementStart(4, "button", 38);
        \u0275\u0275listener("click", function LambdaFunctionListComponent_div_21_td_16_Template_button_click_4_listener() {
            const row_r10 = \u0275\u0275restoreView(_r9).$implicit;
            const ctx_r1 = \u0275\u0275nextContext(2);
            return \u0275\u0275resetView(ctx_r1.deleteFunction(row_r10.functionName));
        });
        \u0275\u0275elementStart(5, "mat-icon");
        \u0275\u0275text(6, "delete");
        \u0275\u0275elementEnd()()();
    }
}

function LambdaFunctionListComponent_div_21_tr_17_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 39);
    }
}

function LambdaFunctionListComponent_div_21_tr_18_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 40);
    }
}

function LambdaFunctionListComponent_div_21_tr_19_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "tr", 41)(1, "td", 42);
        \u0275\u0275text(2, " No data matching the filter. ");
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const ctx_r1 = \u0275\u0275nextContext(2);
        \u0275\u0275advance();
        \u0275\u0275attribute("colspan", ctx_r1.columns.length);
    }
}

function LambdaFunctionListComponent_div_21_Template(rf, ctx) {
    if (rf & 1) {
        const _r4 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "div", 14)(1, "table", 15);
        \u0275\u0275listener("matSortChange", function LambdaFunctionListComponent_div_21_Template_table_matSortChange_1_listener($event) {
            \u0275\u0275restoreView(_r4);
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.sortChange($event));
        });
        \u0275\u0275elementContainerStart(2, 16);
        \u0275\u0275template(3, LambdaFunctionListComponent_div_21_th_3_Template, 2, 0, "th", 17)(4, LambdaFunctionListComponent_div_21_td_4_Template, 4, 3, "td", 18);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(5, 19);
        \u0275\u0275template(6, LambdaFunctionListComponent_div_21_th_6_Template, 2, 0, "th", 20)(7, LambdaFunctionListComponent_div_21_td_7_Template, 2, 1, "td", 18);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(8, 21);
        \u0275\u0275template(9, LambdaFunctionListComponent_div_21_th_9_Template, 2, 0, "th", 22)(10, LambdaFunctionListComponent_div_21_td_10_Template, 2, 1, "td", 18);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(11, 23);
        \u0275\u0275template(12, LambdaFunctionListComponent_div_21_th_12_Template, 2, 0, "th", 24)(13, LambdaFunctionListComponent_div_21_td_13_Template, 2, 1, "td", 18);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(14, 25);
        \u0275\u0275template(15, LambdaFunctionListComponent_div_21_th_15_Template, 2, 0, "th", 26)(16, LambdaFunctionListComponent_div_21_td_16_Template, 7, 0, "td", 18);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275template(17, LambdaFunctionListComponent_div_21_tr_17_Template, 1, 0, "tr", 27)(18, LambdaFunctionListComponent_div_21_tr_18_Template, 1, 0, "tr", 28)(19, LambdaFunctionListComponent_div_21_tr_19_Template, 3, 1, "tr", 29);
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const ctx_r1 = \u0275\u0275nextContext();
        \u0275\u0275advance();
        \u0275\u0275property("dataSource", ctx_r1.dataSource)("matSortActive", ctx_r1.defaultSort.active)("matSortDirection", ctx_r1.defaultSort.direction);
        \u0275\u0275advance(16);
        \u0275\u0275property("matHeaderRowDef", ctx_r1.columns);
        \u0275\u0275advance();
        \u0275\u0275property("matRowDefColumns", ctx_r1.columns);
    }
}

var LambdaFunctionListComponent = class _LambdaFunctionListComponent {
    constructor(snackBar, dialog, router, state, store, actionsSubj$, location) {
        this.snackBar = snackBar;
        this.dialog = dialog;
        this.router = router;
        this.state = state;
        this.store = store;
        this.actionsSubj$ = actionsSubj$;
        this.location = location;
        this.lastUpdate = /* @__PURE__ */ new Date();
        this.loading = false;
        this.noData = [{}];
        this.pageSize$ = this.store.select(selectPageSize);
        this.prefix$ = this.store.select(selectPrefix);
        this.pageIndex$ = this.store.select(selectPageIndex);
        this.columns = ["name", "runtime", "invocations", "averageRuntime", "actions"];
        this.dataSource = new MatTableDataSource();
        this.defaultSort = {active: "name", direction: "asc"};
        this.filterSubject = new Subject();
        this.updateSubscription = new Subscription();
        this.tableSubscription = new Subscription();
        this.prefixSet = false;
        this.prefixValue = "";
        this.total = 0;
        this.pageSizeOptions = [5, 10, 20, 50, 100];
        this.hidePageSize = false;
        this.showPageSizeOptions = true;
        this.showFirstLastButtons = true;
        this.disabled = false;
        this.byteConversion = byteConversion;
        this.filter = "";
        this.actionsSubj$.pipe(filter((action) => action.type === lambdaFunctionListActions.addFunctionSuccess.type || action.type === lambdaFunctionListActions.resetCountersSuccess.type || action.type === lambdaFunctionListActions.deleteFunctionSuccess.type)).subscribe(() => {
            console.log("Action Subscription");
            this.loadFunctions();
        });
        this.prefix$.subscribe((data) => {
            this.prefixSet = false;
            if (data && data.length) {
                this.prefixValue = data;
                this.prefixSet = true;
            }
        });
    }

    ngOnInit() {
        this.store.pipe(select(selectFunctionCounters)).subscribe((functionCounters) => this.initializeData(functionCounters.functionCounters));
        this.store.pipe(select(selectTotal)).subscribe((total) => this.total = total);
        this.tableSubscription.add(this.store.pipe(select(selectIsLoading)).subscribe((loading) => {
            if (loading) {
                this.dataSource = new MatTableDataSource(this.noData);
            }
            this.loading = loading;
        }));
        this.updateSubscription = interval(6e4).subscribe(() => this.loadFunctions());
    }

    ngAfterViewInit() {
        this.loadFunctions();
        let filter$ = this.filterSubject.pipe(debounceTime(150), distinctUntilChanged(), tap((value) => {
            if (this.paginator) {
                this.paginator.pageIndex = 0;
            }
            this.filter = value;
        }));
        if (this.sort) {
            let sort$ = this.sort.sortChange.pipe(tap(() => {
                if (this.paginator) {
                    this.paginator.pageIndex = 0;
                }
            }));
            if (this.paginator) {
                this.tableSubscription.add(merge(filter$, sort$, this.paginator.page).pipe(tap(() => this.loadFunctions())).subscribe());
            }
        }
    }

    ngOnDestroy() {
        this.actionsSubj$?.unsubscribe();
        this.tableSubscription.unsubscribe();
        this.updateSubscription?.unsubscribe();
    }

    back() {
        this.location.back();
    }

    refresh() {
        this.loadFunctions();
    }

    setPrefix() {
        this.prefixSet = true;
        this.state.value["lambda-function-list"].prefix = this.prefixValue;
        this.loadFunctions();
    }

    unsetPrefix() {
        this.prefixValue = "";
        this.prefixSet = false;
        this.state.value["lambda-function-list"].prefix = "";
        this.loadFunctions();
    }

    handlePageEvent(e2) {
        this.state.value["lambda-function-list"].pageSize = e2.pageSize;
        this.state.value["lambda-function-list"].pageIndex = e2.pageIndex;
        this.loadFunctions();
    }

    sortChange(sortState) {
        this.state.value["lambda-function-list"].sortColumns = [];
        let direction = 1;
        let column = "keys";
        if (sortState.active === "size") {
            column = "size";
        } else if (sortState.active === "name") {
            column = "name";
        }
        if (sortState.direction === "asc") {
            direction = 1;
        } else {
            direction = -1;
        }
        this.state.value["lambda-function-list"].sortColumns = [{column, sortDirection: direction}];
        this.loadFunctions();
    }

    loadFunctions() {
        this.store.dispatch(lambdaFunctionListActions.loadFunctions({
            prefix: this.state.value["lambda-function-list"].prefix,
            pageSize: this.state.value["lambda-function-list"].pageSize,
            pageIndex: this.state.value["lambda-function-list"].pageIndex,
            sortColumns: this.state.value["lambda-function-list"].sortColumns
        }));
    }

    deleteFunction(functionName) {
        this.store.dispatch(lambdaFunctionListActions.deleteFunction({functionName}));
    }

    resetCounters(functionName) {
        this.store.dispatch(lambdaFunctionListActions.resetCounters({functionName}));
    }

    initializeData(functions) {
        this.total = 0;
        if (functions.length && functions.length > 0) {
            this.dataSource = new MatTableDataSource(functions);
            this.total = this.dataSource.data.length;
        }
    }

    static {
        this.\u0275fac = function LambdaFunctionListComponent_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _LambdaFunctionListComponent)(\u0275\u0275directiveInject(MatSnackBar), \u0275\u0275directiveInject(MatDialog), \u0275\u0275directiveInject(Router), \u0275\u0275directiveInject(State), \u0275\u0275directiveInject(Store), \u0275\u0275directiveInject(ActionsSubject), \u0275\u0275directiveInject(Location));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _LambdaFunctionListComponent,
            selectors: [["lambda-function-list"]],
            viewQuery: function LambdaFunctionListComponent_Query(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275viewQuery(MatSort, 5);
                    \u0275\u0275viewQuery(MatPaginator, 5);
                }
                if (rf & 2) {
                    let _t;
                    \u0275\u0275queryRefresh(_t = \u0275\u0275loadQuery()) && (ctx.sort = _t.first);
                    \u0275\u0275queryRefresh(_t = \u0275\u0275loadQuery()) && (ctx.paginator = _t.first);
                }
            },
            features: [\u0275\u0275ProvidersFeature([LambdaService])],
            decls: 28,
            vars: 20,
            consts: [["appearance", "outlined", 2, "margin", "3px"], ["aria-label", "Back", "mat-icon-button", "", 1, "head-buttons-left", 3, "click"], [1, "fill-remaining-space"], ["aria-label", "Refresh", "mat-icon-button", "", 3, "click"], ["appearance", "outlined", 2, "margin", "-10px"], ["align", "start"], [2, "width", "100%"], ["matInput", "", "name", "search", "placeholder", "Search", "type", "text", 3, "ngModelChange", "ngModel"], ["mat-icon-button", "", "matSuffix", "", "style", "float: right", 3, "click", 4, "ngIf"], ["class", "table-container", 4, "ngIf"], ["aria-label", "Select page", 2, "width", "99%", "margin-left", "15px", 3, "page", "disabled", "hidePageSize", "length", "pageIndex", "pageSizeOptions", "pageSize", "showFirstLastButtons"], [1, "footer"], ["mat-icon-button", "", "matSuffix", "", 2, "float", "right", 3, "click"], ["matSuffix", ""], [1, "table-container"], ["mat-table", "", "matSort", "", "matSortDisableClear", "false", 3, "matSortChange", "dataSource", "matSortActive", "matSortDirection"], ["matColumnDef", "name"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Function name", "sortActionDescription", "Sort by name", 4, "matHeaderCellDef"], ["mat-cell", "", 4, "matCellDef"], ["matColumnDef", "runtime"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Runtime", "sortActionDescription", "Sort by runtime", 4, "matHeaderCellDef"], ["matColumnDef", "invocations"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Invocations", "sortActionDescription", "Sort by invocations", 4, "matHeaderCellDef"], ["matColumnDef", "averageRuntime"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Average runtime in milliseconds", "sortActionDescription", "Sort by average runtime", 4, "matHeaderCellDef"], ["matColumnDef", "actions"], ["mat-header-cell", "", "style", "width:120px", 4, "matHeaderCellDef"], ["mat-header-row", "", 4, "matHeaderRowDef"], ["mat-row", "", 4, "matRowDef", "matRowDefColumns"], ["class", "mat-row", 4, "matNoDataRow"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Function name", "sortActionDescription", "Sort by name"], ["mat-cell", ""], ["mat-list-item", "", 3, "routerLink"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Runtime", "sortActionDescription", "Sort by runtime"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Invocations", "sortActionDescription", "Sort by invocations"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Average runtime in milliseconds", "sortActionDescription", "Sort by average runtime"], ["mat-header-cell", "", 2, "width", "120px"], ["aria-label", "Reset counters", "mat-icon-button", "", "matTooltip", "Reset counters", 3, "click"], ["aria-label", "delete function", "mat-icon-button", "", "matTooltip", "Delete function", 3, "click"], ["mat-header-row", ""], ["mat-row", ""], [1, "mat-row"], [1, "mat-cell", 2, "padding-left", "20px", "padding-top", "10px"]],
            template: function LambdaFunctionListComponent_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "mat-card", 0)(1, "mat-card-header")(2, "button", 1);
                    \u0275\u0275listener("click", function LambdaFunctionListComponent_Template_button_click_2_listener() {
                        return ctx.back();
                    });
                    \u0275\u0275elementStart(3, "mat-icon");
                    \u0275\u0275text(4, "arrow_back");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(5, "span", 2)(6, "h4");
                    \u0275\u0275text(7, "Lambda Functions");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(8, "button", 3);
                    \u0275\u0275listener("click", function LambdaFunctionListComponent_Template_button_click_8_listener() {
                        return ctx.refresh();
                    });
                    \u0275\u0275elementStart(9, "mat-icon");
                    \u0275\u0275text(10, "refresh");
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(11, "mat-card-content")(12, "mat-card", 4)(13, "mat-card-actions", 5)(14, "mat-form-field", 6)(15, "mat-label");
                    \u0275\u0275text(16, "Prefix");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(17, "input", 7);
                    \u0275\u0275twoWayListener("ngModelChange", function LambdaFunctionListComponent_Template_input_ngModelChange_17_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.prefixValue, $event) || (ctx.prefixValue = $event);
                        return $event;
                    });
                    \u0275\u0275elementEnd();
                    \u0275\u0275template(18, LambdaFunctionListComponent_button_18_Template, 3, 0, "button", 8)(19, LambdaFunctionListComponent_button_19_Template, 3, 0, "button", 8);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(20, "mat-card-content");
                    \u0275\u0275template(21, LambdaFunctionListComponent_div_21_Template, 20, 5, "div", 9);
                    \u0275\u0275elementStart(22, "mat-paginator", 10);
                    \u0275\u0275pipe(23, "async");
                    \u0275\u0275pipe(24, "async");
                    \u0275\u0275listener("page", function LambdaFunctionListComponent_Template_mat_paginator_page_22_listener($event) {
                        return ctx.handlePageEvent($event);
                    });
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(25, "div", 11);
                    \u0275\u0275text(26);
                    \u0275\u0275pipe(27, "date");
                    \u0275\u0275elementEnd()()();
                }
                if (rf & 2) {
                    \u0275\u0275advance(17);
                    \u0275\u0275twoWayProperty("ngModel", ctx.prefixValue);
                    \u0275\u0275advance();
                    \u0275\u0275property("ngIf", !ctx.prefixSet);
                    \u0275\u0275advance();
                    \u0275\u0275property("ngIf", ctx.prefixSet);
                    \u0275\u0275advance(2);
                    \u0275\u0275property("ngIf", ctx.total > 0);
                    \u0275\u0275advance();
                    \u0275\u0275property("disabled", ctx.disabled)("hidePageSize", ctx.hidePageSize)("length", ctx.total)("pageIndex", \u0275\u0275pipeBind1(23, 12, ctx.pageIndex$))("pageSizeOptions", ctx.showPageSizeOptions ? ctx.pageSizeOptions : \u0275\u0275pureFunction0(19, _c0))("pageSize", \u0275\u0275pipeBind1(24, 14, ctx.pageSize$))("showFirstLastButtons", ctx.showFirstLastButtons);
                    \u0275\u0275advance(4);
                    \u0275\u0275textInterpolate1(" Last update: ", \u0275\u0275pipeBind2(27, 16, ctx.lastUpdate, "HH:mm:ss"), " ");
                }
            },
            dependencies: [MatCard, MatCardHeader, MatCardContent, MatCardActions, MatTable, MatHeaderCellDef, MatCellDef, MatColumnDef, MatIcon, MatHeaderCell, MatCell, MatHeaderRowDef, MatHeaderRow, MatSortHeader, MatRowDef, MatNoDataRow, MatIconButton, MatRow, MatPaginator, MatSort, MatTooltip, RouterLink, MatListItem, MatNavList, MatFormField, MatInput, MatLabel, MatSuffix, NgIf, DefaultValueAccessor, NgControlStatus, NgModel, DatePipe, AsyncPipe],
            styles: ["\n\n[_nghost-%COMP%] {\n  position: relative;\n  width: 100%;\n  height: 30%;\n  margin-top: 0;\n  padding-bottom: 33%;\n}\n.head-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  justify-content: flex-end;\n}\n.head-buttons-left[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: start;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  justify-content: start;\n}\n.fill-remaining-space[_ngcontent-%COMP%] {\n  flex: 1 1 auto;\n}\n.table-container[_ngcontent-%COMP%] {\n  max-height: calc(100vh - 10px);\n  overflow: auto;\n}\n.footer-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  width: 50%;\n  justify-content: flex-end;\n}\n.footer[_ngcontent-%COMP%] {\n  display: flex;\n  width: 50%;\n  font-size: x-small;\n  color: black;\n  padding-top: 15px;\n}\n/*# sourceMappingURL=function-list.component.css.map */"]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(LambdaFunctionListComponent, {
        className: "LambdaFunctionListComponent",
        filePath: "src/app/modules/lambda/function-list/function-list.component.ts",
        lineNumber: 24
    });
})();

// src/app/modules/lambda/function-details/state/lambda-function-details.actions.ts
var lambdaFunctionDetailsActions = {
    initialize: createAction("[lambda-function-details] initialize"),
    // Load functions
    loadFunction: createAction("[lambda-function-details] Load function", props()),
    loadFunctionSuccess: createAction("[lambda-function-details] Load function success", props()),
    loadFunctionFailure: createAction("[lambda-function-details] Load function error", props())
};

// src/app/modules/lambda/function-details/state/lambda-function-details.reducer.ts
var lambdaFunctionDetailsFeatureKey = "lambda-function-details";
var initialState2 = {
    functionItem: {},
    loading: false,
    error: {}
};
var lambdaFunctionDetailsReducer = createReducer(
    initialState2,
    // LambdaFunctionDetailsState
    on(lambdaFunctionDetailsActions.initialize, (state) => __spreadProps(__spreadValues({}, state), {
        loading: true
    })),
    // Function list
    on(lambdaFunctionDetailsActions.loadFunction, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(lambdaFunctionDetailsActions.loadFunctionSuccess, (state, {functionItem}) => __spreadProps(__spreadValues({}, state), {
        functionItem,
        loading: false
    })),
    on(lambdaFunctionDetailsActions.loadFunctionFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false}))
);

// src/app/modules/lambda/function-details/state/lambda-function-details.selectors.ts
var selectFunctionListFeature2 = createFeatureSelector(lambdaFunctionDetailsFeatureKey);
var selectIsLoading2 = createSelector(selectFunctionListFeature2, (state) => state.loading);
var selectFunctionItem = createSelector(selectFunctionListFeature2, (state) => state?.functionItem);

// src/app/modules/lambda/function-details/function-detail.component.ts
function LambdaFunctionDetailsComponent_th_112_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 31);
        \u0275\u0275text(1, "Name");
        \u0275\u0275elementEnd();
    }
}

function LambdaFunctionDetailsComponent_td_113_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 32);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r1 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r1.key, "");
    }
}

function LambdaFunctionDetailsComponent_th_115_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 33);
        \u0275\u0275text(1, "Value ");
        \u0275\u0275elementEnd();
    }
}

function LambdaFunctionDetailsComponent_td_116_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 32);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r2 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r2.value, "");
    }
}

function LambdaFunctionDetailsComponent_th_118_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 34);
        \u0275\u0275text(1, "Actions");
        \u0275\u0275elementEnd();
    }
}

function LambdaFunctionDetailsComponent_td_119_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "td", 32);
    }
}

function LambdaFunctionDetailsComponent_tr_120_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 35);
    }
}

function LambdaFunctionDetailsComponent_tr_121_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 36);
    }
}

function LambdaFunctionDetailsComponent_tr_122_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "tr", 37)(1, "td", 38);
        \u0275\u0275text(2, " No data matching the filter. ");
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const ctx_r2 = \u0275\u0275nextContext();
        \u0275\u0275advance();
        \u0275\u0275attribute("colspan", ctx_r2.environmentColumns.length);
    }
}

function LambdaFunctionDetailsComponent_th_126_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 39);
        \u0275\u0275text(1, "Name");
        \u0275\u0275elementEnd();
    }
}

function LambdaFunctionDetailsComponent_td_127_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 32);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r4 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r4.key, "");
    }
}

function LambdaFunctionDetailsComponent_th_129_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 40);
        \u0275\u0275text(1, "Value ");
        \u0275\u0275elementEnd();
    }
}

function LambdaFunctionDetailsComponent_td_130_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 32);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r5 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r5.value, "");
    }
}

function LambdaFunctionDetailsComponent_th_132_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 34);
        \u0275\u0275text(1, "Actions");
        \u0275\u0275elementEnd();
    }
}

function LambdaFunctionDetailsComponent_td_133_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "td", 32);
    }
}

function LambdaFunctionDetailsComponent_tr_134_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 35);
    }
}

function LambdaFunctionDetailsComponent_tr_135_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 36);
    }
}

function LambdaFunctionDetailsComponent_tr_136_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "tr", 37)(1, "td", 38);
        \u0275\u0275text(2, " No data matching the filter. ");
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const ctx_r2 = \u0275\u0275nextContext();
        \u0275\u0275advance();
        \u0275\u0275attribute("colspan", ctx_r2.environmentColumns.length);
    }
}

var LambdaFunctionDetailsComponent = class _LambdaFunctionDetailsComponent {
    constructor(location, route, state, store) {
        this.location = location;
        this.route = route;
        this.state = state;
        this.store = store;
        this.lastUpdate = /* @__PURE__ */ new Date();
        this.functionItem = {};
        this.functionName = "";
        this.functionItem$ = this.store.select(selectFunctionItem);
        this.environmentColumns = ["name", "value"];
        this.environmentDataSource = new MatTableDataSource();
        this.tagsDataSource = new MatTableDataSource();
        this.sortedEnvData = [];
        this.byteConversion = byteConversion;
        this._liveAnnouncer = inject(LiveAnnouncer);
    }

    ngOnInit() {
        this.routerSubscription = this.route.params.subscribe((params) => {
            this.functionName = params["functionName"];
        });
        this.functionItem$?.subscribe((data) => {
            this.lastUpdate = /* @__PURE__ */ new Date();
            this.functionItem = data;
            this.environmentDataSource = this.convertEnvironment(data);
            this.tagsDataSource = this.convertTags(data);
            console.log(data);
        });
        this.loadFunction();
    }

    ngOnDestroy() {
        this.routerSubscription.unsubscribe();
    }

    back() {
        this.location.back();
    }

    refresh() {
        this.loadFunction();
    }

    loadFunction() {
        this.store.dispatch(lambdaFunctionDetailsActions.loadFunction({
            name: this.functionName
        }));
    }

    save() {
        this.location.back();
    }

    environmentSortChanged(sortState) {
    }

    tagsSortChanged(sortState) {
        if (sortState.direction) {
        } else {
        }
    }

    convertEnvironment(data) {
        let i2 = 0;
        let env = [];
        for (let t2 in data.environment) {
            env[i2++] = {key: t2, value: data.environment[t2]};
        }
        return new MatTableDataSource(env);
    }

    convertTags(data) {
        let i2 = 0;
        let tags = [];
        for (let t2 in data.tags) {
            tags[i2++] = {key: t2, value: data.tags[t2]};
        }
        return new MatTableDataSource(tags);
    }

    static {
        this.\u0275fac = function LambdaFunctionDetailsComponent_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _LambdaFunctionDetailsComponent)(\u0275\u0275directiveInject(Location), \u0275\u0275directiveInject(ActivatedRoute), \u0275\u0275directiveInject(State), \u0275\u0275directiveInject(Store));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _LambdaFunctionDetailsComponent,
            selectors: [["lambda-function-detail-component"]],
            features: [\u0275\u0275ProvidersFeature([LambdaService])],
            decls: 145,
            vars: 39,
            consts: [["appearance", "outlined", 2, "margin", "3px"], ["aria-label", "Back", "mat-icon-button", "", 1, "head-buttons-left", 3, "click"], [1, "fill-remaining-space"], ["aria-label", "Refresh", "mat-icon-button", "", 3, "click"], ["cols", "3", "rowHeight", "420px"], [3, "colspan", "rowspan"], [2, "width", "100%", "display", "flex", "align-items", "flex-start", "align-content", "flex-start"], [2, "height", "80px"], ["matListItemTitle", "", 1, "mat-list-span-title"], ["matListItemLine", "", 1, "mat-list-span-value"], [2, "height", "60px"], ["appearance", "outlined", 2, "margin-top", "5px"], ["label", "Environment"], [1, "head-buttons"], ["mat-table", "", "matSort", "", 1, "mat-elevation-z8", 3, "matSortChange", "dataSource"], ["matColumnDef", "name"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Environment variable name", "sortActionDescription", "Sort by name", 4, "matHeaderCellDef"], ["mat-cell", "", 4, "matCellDef"], ["matColumnDef", "value"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Environment variable value", "sortActionDescription", "Sort by value", 4, "matHeaderCellDef"], ["matColumnDef", "actions"], ["mat-header-cell", "", "style", "width:120px", 4, "matHeaderCellDef"], ["mat-header-row", "", 4, "matHeaderRowDef"], ["mat-row", "", 4, "matRowDef", "matRowDefColumns"], ["class", "mat-row", 4, "matNoDataRow"], ["label", "Tags"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Tag name", "sortActionDescription", "Sort by name", 4, "matHeaderCellDef"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Tag value", "sortActionDescription", "Sort by value", 4, "matHeaderCellDef"], ["align", "end"], ["mat-button", "", 3, "click"], [1, "footer"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Environment variable name", "sortActionDescription", "Sort by name"], ["mat-cell", ""], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Environment variable value", "sortActionDescription", "Sort by value"], ["mat-header-cell", "", 2, "width", "120px"], ["mat-header-row", ""], ["mat-row", ""], [1, "mat-row"], [1, "mat-cell"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Tag name", "sortActionDescription", "Sort by name"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Tag value", "sortActionDescription", "Sort by value"]],
            template: function LambdaFunctionDetailsComponent_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "mat-card", 0)(1, "mat-card-header")(2, "span")(3, "button", 1);
                    \u0275\u0275listener("click", function LambdaFunctionDetailsComponent_Template_button_click_3_listener() {
                        return ctx.back();
                    });
                    \u0275\u0275elementStart(4, "mat-icon");
                    \u0275\u0275text(5, "arrow_back");
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(6, "span", 2)(7, "h4");
                    \u0275\u0275text(8);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(9, "span")(10, "button", 3);
                    \u0275\u0275listener("click", function LambdaFunctionDetailsComponent_Template_button_click_10_listener() {
                        return ctx.refresh();
                    });
                    \u0275\u0275elementStart(11, "mat-icon");
                    \u0275\u0275text(12, "refresh");
                    \u0275\u0275elementEnd()()()();
                    \u0275\u0275elementStart(13, "mat-card", 0)(14, "mat-card-header")(15, "mat-card-title");
                    \u0275\u0275text(16, "Details");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(17, "mat-card-content")(18, "mat-grid-list", 4)(19, "mat-grid-tile", 5)(20, "div", 6)(21, "mat-list")(22, "mat-list-item", 7)(23, "p", 8);
                    \u0275\u0275text(24, "Region: ");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(25, "p", 9);
                    \u0275\u0275text(26);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(27, "mat-list-item", 7)(28, "p", 8);
                    \u0275\u0275text(29, "Function name: ");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(30, "p", 9);
                    \u0275\u0275text(31);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(32, "mat-list-item", 7)(33, "p", 8);
                    \u0275\u0275text(34, "Handler: ");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(35, "p", 9);
                    \u0275\u0275text(36);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(37, "mat-list-item", 7)(38, "p", 8);
                    \u0275\u0275text(39, "Role: ");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(40, "p", 9);
                    \u0275\u0275text(41);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(42, "mat-list-item", 7)(43, "p", 8);
                    \u0275\u0275text(44, "User: ");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(45, "p", 9);
                    \u0275\u0275text(46);
                    \u0275\u0275elementEnd()()()()();
                    \u0275\u0275elementStart(47, "mat-grid-tile", 5)(48, "div", 6)(49, "mat-list")(50, "mat-list-item", 7)(51, "p", 8);
                    \u0275\u0275text(52, "Runtime: ");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(53, "p", 9);
                    \u0275\u0275text(54);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(55, "mat-list-item", 7)(56, "p", 8);
                    \u0275\u0275text(57, "Size:");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(58, "p", 9);
                    \u0275\u0275text(59);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(60, "mat-list-item", 7)(61, "p", 8);
                    \u0275\u0275text(62, "Concurrency:");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(63, "p", 9);
                    \u0275\u0275text(64);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(65, "mat-list-item", 7);
                    \u0275\u0275element(66, "p", 8)(67, "p", 9);
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(68, "mat-list-item", 10);
                    \u0275\u0275element(69, "p", 8)(70, "p", 9);
                    \u0275\u0275elementEnd()()()();
                    \u0275\u0275elementStart(71, "mat-grid-tile", 5)(72, "div", 6)(73, "mat-list")(74, "mat-list-item", 7)(75, "p", 8);
                    \u0275\u0275text(76, "Number of invocation:");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(77, "p", 9);
                    \u0275\u0275text(78);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(79, "mat-list-item", 7)(80, "p", 8);
                    \u0275\u0275text(81, "Average Execution time:");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(82, "p", 9);
                    \u0275\u0275text(83);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(84, "mat-list-item", 7)(85, "p", 8);
                    \u0275\u0275text(86, "Last invocation:");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(87, "p", 9);
                    \u0275\u0275text(88);
                    \u0275\u0275pipe(89, "date");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(90, "mat-list-item", 7)(91, "p", 8);
                    \u0275\u0275text(92, "Created:");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(93, "p", 9);
                    \u0275\u0275text(94);
                    \u0275\u0275pipe(95, "date");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(96, "mat-list-item", 7)(97, "p", 8);
                    \u0275\u0275text(98, "Modified:");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(99, "p", 9);
                    \u0275\u0275text(100);
                    \u0275\u0275pipe(101, "date");
                    \u0275\u0275elementEnd()()()()()()()();
                    \u0275\u0275elementStart(102, "mat-card", 11)(103, "mat-card-header")(104, "mat-card-title");
                    \u0275\u0275text(105, "Info");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(106, "mat-card-content")(107, "mat-tab-group")(108, "mat-tab", 12);
                    \u0275\u0275element(109, "mat-card-actions", 13);
                    \u0275\u0275elementStart(110, "table", 14);
                    \u0275\u0275listener("matSortChange", function LambdaFunctionDetailsComponent_Template_table_matSortChange_110_listener($event) {
                        return ctx.environmentSortChanged($event);
                    });
                    \u0275\u0275elementContainerStart(111, 15);
                    \u0275\u0275template(112, LambdaFunctionDetailsComponent_th_112_Template, 2, 0, "th", 16)(113, LambdaFunctionDetailsComponent_td_113_Template, 2, 1, "td", 17);
                    \u0275\u0275elementContainerEnd();
                    \u0275\u0275elementContainerStart(114, 18);
                    \u0275\u0275template(115, LambdaFunctionDetailsComponent_th_115_Template, 2, 0, "th", 19)(116, LambdaFunctionDetailsComponent_td_116_Template, 2, 1, "td", 17);
                    \u0275\u0275elementContainerEnd();
                    \u0275\u0275elementContainerStart(117, 20);
                    \u0275\u0275template(118, LambdaFunctionDetailsComponent_th_118_Template, 2, 0, "th", 21)(119, LambdaFunctionDetailsComponent_td_119_Template, 1, 0, "td", 17);
                    \u0275\u0275elementContainerEnd();
                    \u0275\u0275template(120, LambdaFunctionDetailsComponent_tr_120_Template, 1, 0, "tr", 22)(121, LambdaFunctionDetailsComponent_tr_121_Template, 1, 0, "tr", 23)(122, LambdaFunctionDetailsComponent_tr_122_Template, 3, 1, "tr", 24);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(123, "mat-tab", 25)(124, "table", 14);
                    \u0275\u0275listener("matSortChange", function LambdaFunctionDetailsComponent_Template_table_matSortChange_124_listener($event) {
                        return ctx.tagsSortChanged($event);
                    });
                    \u0275\u0275elementContainerStart(125, 15);
                    \u0275\u0275template(126, LambdaFunctionDetailsComponent_th_126_Template, 2, 0, "th", 26)(127, LambdaFunctionDetailsComponent_td_127_Template, 2, 1, "td", 17);
                    \u0275\u0275elementContainerEnd();
                    \u0275\u0275elementContainerStart(128, 18);
                    \u0275\u0275template(129, LambdaFunctionDetailsComponent_th_129_Template, 2, 0, "th", 27)(130, LambdaFunctionDetailsComponent_td_130_Template, 2, 1, "td", 17);
                    \u0275\u0275elementContainerEnd();
                    \u0275\u0275elementContainerStart(131, 20);
                    \u0275\u0275template(132, LambdaFunctionDetailsComponent_th_132_Template, 2, 0, "th", 21)(133, LambdaFunctionDetailsComponent_td_133_Template, 1, 0, "td", 17);
                    \u0275\u0275elementContainerEnd();
                    \u0275\u0275template(134, LambdaFunctionDetailsComponent_tr_134_Template, 1, 0, "tr", 22)(135, LambdaFunctionDetailsComponent_tr_135_Template, 1, 0, "tr", 23)(136, LambdaFunctionDetailsComponent_tr_136_Template, 3, 1, "tr", 24);
                    \u0275\u0275elementEnd()()()()();
                    \u0275\u0275elementStart(137, "mat-card-actions", 28)(138, "button", 29);
                    \u0275\u0275listener("click", function LambdaFunctionDetailsComponent_Template_button_click_138_listener() {
                        return ctx.back();
                    });
                    \u0275\u0275text(139, "Close");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(140, "button", 29);
                    \u0275\u0275listener("click", function LambdaFunctionDetailsComponent_Template_button_click_140_listener() {
                        return ctx.save();
                    });
                    \u0275\u0275text(141, "Save");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(142, "div", 30);
                    \u0275\u0275text(143);
                    \u0275\u0275pipe(144, "date");
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    \u0275\u0275advance(8);
                    \u0275\u0275textInterpolate1("Lambda Function Details: ", ctx.functionName, "");
                    \u0275\u0275advance(11);
                    \u0275\u0275property("colspan", 1)("rowspan", 1);
                    \u0275\u0275advance(7);
                    \u0275\u0275textInterpolate(ctx.functionItem.region);
                    \u0275\u0275advance(5);
                    \u0275\u0275textInterpolate(ctx.functionItem.functionName);
                    \u0275\u0275advance(5);
                    \u0275\u0275textInterpolate(ctx.functionItem.handler);
                    \u0275\u0275advance(5);
                    \u0275\u0275textInterpolate(ctx.functionItem.role);
                    \u0275\u0275advance(5);
                    \u0275\u0275textInterpolate(ctx.functionItem.user);
                    \u0275\u0275advance();
                    \u0275\u0275property("colspan", 1)("rowspan", 1);
                    \u0275\u0275advance(7);
                    \u0275\u0275textInterpolate(ctx.functionItem.runtime);
                    \u0275\u0275advance(5);
                    \u0275\u0275textInterpolate(ctx.byteConversion(ctx.functionItem.size));
                    \u0275\u0275advance(5);
                    \u0275\u0275textInterpolate(ctx.functionItem.concurrency);
                    \u0275\u0275advance(7);
                    \u0275\u0275property("colspan", 1)("rowspan", 1);
                    \u0275\u0275advance(7);
                    \u0275\u0275textInterpolate(ctx.functionItem.invocations);
                    \u0275\u0275advance(5);
                    \u0275\u0275textInterpolate1("", ctx.functionItem.averageRuntime, " ms");
                    \u0275\u0275advance(5);
                    \u0275\u0275textInterpolate(\u0275\u0275pipeBind2(89, 27, ctx.functionItem.lastInvocation, "yyyy-MM-dd HH:mm:ss"));
                    \u0275\u0275advance(6);
                    \u0275\u0275textInterpolate(\u0275\u0275pipeBind2(95, 30, ctx.functionItem.created, "yyyy-MM-dd HH:mm:ss"));
                    \u0275\u0275advance(6);
                    \u0275\u0275textInterpolate(\u0275\u0275pipeBind2(101, 33, ctx.functionItem.modified, "yyyy-MM-dd HH:mm:ss"));
                    \u0275\u0275advance(10);
                    \u0275\u0275property("dataSource", ctx.environmentDataSource);
                    \u0275\u0275advance(10);
                    \u0275\u0275property("matHeaderRowDef", ctx.environmentColumns);
                    \u0275\u0275advance();
                    \u0275\u0275property("matRowDefColumns", ctx.environmentColumns);
                    \u0275\u0275advance(3);
                    \u0275\u0275property("dataSource", ctx.tagsDataSource);
                    \u0275\u0275advance(10);
                    \u0275\u0275property("matHeaderRowDef", ctx.environmentColumns);
                    \u0275\u0275advance();
                    \u0275\u0275property("matRowDefColumns", ctx.environmentColumns);
                    \u0275\u0275advance(8);
                    \u0275\u0275textInterpolate1(" Last update: ", \u0275\u0275pipeBind2(144, 36, ctx.lastUpdate, "HH:mm:ss"), " ");
                }
            },
            dependencies: [MatCard, MatCardHeader, MatCardContent, MatCardActions, MatCardTitle, MatTable, MatHeaderCellDef, MatCellDef, MatColumnDef, MatIcon, MatHeaderCell, MatCell, MatHeaderRowDef, MatHeaderRow, MatSortHeader, MatRowDef, MatNoDataRow, MatIconButton, MatRow, MatSort, MatTooltip, MatListItem, MatGridTile, MatGridList, MatList, MatTabGroup, MatTab, MatButton, DatePipe],
            styles: ["\n\nbody[_ngcontent-%COMP%] {\n  margin: 40px;\n}\n.container[_ngcontent-%COMP%] {\n  width: 100%;\n}\n.form[_ngcontent-%COMP%] {\n  min-width: 150px;\n  width: 100%;\n  margin-right: 10px;\n}\n.form-full-width[_ngcontent-%COMP%] {\n  width: 100%;\n}\n.head-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  justify-content: flex-end;\n}\n.footer[_ngcontent-%COMP%] {\n  display: flex;\n  width: 50%;\n  font-size: x-small;\n  color: black;\n  padding-top: 15px;\n  padding-left: 10px;\n}\n.fill-remaining-space[_ngcontent-%COMP%] {\n  flex: 1 1 auto;\n}\n/*# sourceMappingURL=function-detail.component.css.map */"]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(LambdaFunctionDetailsComponent, {
        className: "LambdaFunctionDetailsComponent",
        filePath: "src/app/modules/lambda/function-details/function-detail.component.ts",
        lineNumber: 23
    });
})();

// src/app/modules/lambda/lambda-routing.module.ts
var routes = [
    {
        path: "",
        title: "LambdaFunctionList",
        component: LambdaFunctionListComponent
    },
    {
        path: "details/:functionName",
        title: "LambdaFunctionDetails",
        component: LambdaFunctionDetailsComponent
    }
];
var LambdaRoutingModule = class _LambdaRoutingModule {
    static {
        this.\u0275fac = function LambdaRoutingModule_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _LambdaRoutingModule)();
        };
    }
    static {
        this.\u0275mod = /* @__PURE__ */ \u0275\u0275defineNgModule({type: _LambdaRoutingModule});
    }
    static {
        this.\u0275inj = /* @__PURE__ */ \u0275\u0275defineInjector({imports: [RouterModule.forChild(routes), RouterModule]});
    }
};

// src/app/modules/lambda/function-list/state/lambda-function-list.effects.ts
var LambdaFunctionListEffects = class _LambdaFunctionListEffects {
    constructor(actions$, lambdaService) {
        this.actions$ = actions$;
        this.lambdaService = lambdaService;
        this.loadFunctionCounters$ = createEffect(() => this.actions$.pipe(ofType(lambdaFunctionListActions.loadFunctions), mergeMap((action) => this.lambdaService.listFunctionCounters(action.prefix, action.pageSize, action.pageIndex, action.sortColumns).pipe(map((functions) => lambdaFunctionListActions.loadFunctionsSuccess({functions})), catchError((error) => of(lambdaFunctionListActions.loadFunctionsFailure({error: error.message})))))));
        this.resetCounters$ = createEffect(() => this.actions$.pipe(ofType(lambdaFunctionListActions.resetCounters), mergeMap((action) => this.lambdaService.resetCounters(action.functionName).pipe(map(() => lambdaFunctionListActions.resetCountersSuccess()), catchError((error) => of(lambdaFunctionListActions.resetCountersFailure({error: error.message})))))));
        this.deleteFunction$ = createEffect(() => this.actions$.pipe(ofType(lambdaFunctionListActions.deleteFunction), mergeMap((action) => this.lambdaService.deleteFunction(action.functionName).then(() => lambdaFunctionListActions.deleteFunctionSuccess()).catch((reason) => lambdaFunctionListActions.deleteFunctionFailure(reason)))));
    }

    static {
        this.\u0275fac = function LambdaFunctionListEffects_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _LambdaFunctionListEffects)(\u0275\u0275inject(Actions), \u0275\u0275inject(LambdaService));
        };
    }
    static {
        this.\u0275prov = /* @__PURE__ */ \u0275\u0275defineInjectable({token: _LambdaFunctionListEffects, factory: _LambdaFunctionListEffects.\u0275fac});
    }
};

// src/app/modules/lambda/function-details/state/lambda-function-details.effects.ts
var LambdaFunctionDetailsEffects = class _LambdaFunctionDetailsEffects {
    constructor(actions$, lambdaService) {
        this.actions$ = actions$;
        this.lambdaService = lambdaService;
        this.loadFunction$ = createEffect(() => this.actions$.pipe(ofType(lambdaFunctionDetailsActions.loadFunction), mergeMap((action) => this.lambdaService.getFunction(action.name).pipe(map((functionItem) => lambdaFunctionDetailsActions.loadFunctionSuccess({functionItem})), catchError((error) => of(lambdaFunctionDetailsActions.loadFunctionFailure({error: error.message})))))));
    }

    static {
        this.\u0275fac = function LambdaFunctionDetailsEffects_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _LambdaFunctionDetailsEffects)(\u0275\u0275inject(Actions), \u0275\u0275inject(LambdaService));
        };
    }
    static {
        this.\u0275prov = /* @__PURE__ */ \u0275\u0275defineInjectable({token: _LambdaFunctionDetailsEffects, factory: _LambdaFunctionDetailsEffects.\u0275fac});
    }
};

// src/app/modules/lambda/lambda.module.ts
var LambdaModule = class _LambdaModule {
    static {
        this.\u0275fac = function LambdaModule_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _LambdaModule)();
        };
    }
    static {
        this.\u0275mod = /* @__PURE__ */ \u0275\u0275defineNgModule({type: _LambdaModule});
    }
    static {
        this.\u0275inj = /* @__PURE__ */ \u0275\u0275defineInjector({
            providers: [LambdaService], imports: [
                MatCard,
                MatCardHeader,
                MatTable,
                MatIcon,
                MatHeaderRow,
                MatSortHeader,
                MatIconButton,
                MatRow,
                MatPaginator,
                MatSortModule,
                MatListItem,
                MatNavList,
                MatFormField,
                MatGridTile,
                MatGridList,
                MatList,
                MatTabGroup,
                MatTab,
                MatButton,
                ReactiveFormsModule,
                FormsModule,
                LambdaRoutingModule,
                StoreModule.forFeature(lambdaFunctionListFeatureKey, lambdaFunctionListReducer),
                StoreModule.forFeature(lambdaFunctionDetailsFeatureKey, lambdaFunctionDetailsReducer),
                EffectsModule.forFeature([LambdaFunctionListEffects, LambdaFunctionDetailsEffects])
            ]
        });
    }
};
export {
    LambdaModule
};
//# sourceMappingURL=chunk-5LN7EYYT.js.map

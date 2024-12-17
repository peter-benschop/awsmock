import {SqsService} from "./chunk-7C5R5GF7.js";
import {parseXmlBody, parseXmlErrorBody} from "./chunk-XLK3LOTB.js";
import {MatSlideToggle} from "./chunk-4VAYYVT5.js";
import {CdkDrag, CdkDragHandle} from "./chunk-L5B3QUPF.js";
import "./chunk-HK7D4W5I.js";
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
    extendedEncodeURIComponent,
    FetchHttpHandler,
    fromBase64,
    fromUtf8,
    getArrayIfSingleItem,
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
    SENSITIVE_STRING,
    ServiceException,
    Sha256,
    streamCollector,
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
    CdkTextareaAutosize,
    createAction,
    createEffect,
    createFeatureSelector,
    createReducer,
    createSelector,
    DatePipe,
    DefaultValueAccessor,
    EffectsModule,
    environment,
    filter,
    FormBuilder,
    FormsModule,
    HttpClient,
    HttpHeaders,
    interval,
    Location,
    map,
    MAT_DIALOG_DATA,
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
    MatDialogActions,
    MatDialogClose,
    MatDialogConfig,
    MatDialogContent,
    MatDialogRef,
    MatDialogTitle,
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
    MatOption,
    MatPaginator,
    MatRow,
    MatRowDef,
    MatSelect,
    MatSnackBar,
    MatSort,
    MatSortHeader,
    MatSuffix,
    MatTable,
    MatTooltip,
    mergeMap,
    NgControlStatus,
    NgIf,
    NgModel,
    of,
    ofType,
    on,
    props,
    ReactiveFormsModule,
    RouterLink,
    RouterModule,
    State,
    Store,
    StoreModule
} from "./chunk-LGOS2CJL.js";
import {__async, __spreadProps, __spreadValues} from "./chunk-G42SKTPL.js";

// src/app/modules/sns/topic-add/topic-add.component.ts
var TopicAddComponentDialog = class _TopicAddComponentDialog {
    constructor(fb, dialogRef, portList) {
        this.fb = fb;
        this.dialogRef = dialogRef;
        this.portList = portList;
        this.topicName = "";
    }

    ngOnInit() {
    }

    save() {
        this.dialogRef.close(this.topicName);
    }

    close() {
        this.dialogRef.close(false);
    }

    static {
        this.\u0275fac = function TopicAddComponentDialog_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _TopicAddComponentDialog)(\u0275\u0275directiveInject(FormBuilder), \u0275\u0275directiveInject(MatDialogRef), \u0275\u0275directiveInject(MAT_DIALOG_DATA));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _TopicAddComponentDialog,
            selectors: [["add-connection-dialog"]],
            standalone: true,
            features: [\u0275\u0275StandaloneFeature],
            decls: 12,
            vars: 1,
            consts: [["mat-dialog-title", ""], [1, "mat-typography", 2, "width", "500px"], [2, "width", "100%"], ["matInput", "", "value", "", 3, "ngModelChange", "ngModel"], ["align", "end"], ["mat-button", "", "mat-dialog-close", ""], ["cdkFocusInitial", "", "mat-button", "", 3, "click"]],
            template: function TopicAddComponentDialog_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "h2", 0);
                    \u0275\u0275text(1, "Add SNS Topic");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(2, "mat-dialog-content", 1)(3, "mat-form-field", 2)(4, "mat-label");
                    \u0275\u0275text(5, "Topic Name");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(6, "input", 3);
                    \u0275\u0275twoWayListener("ngModelChange", function TopicAddComponentDialog_Template_input_ngModelChange_6_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.topicName, $event) || (ctx.topicName = $event);
                        return $event;
                    });
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(7, "mat-dialog-actions", 4)(8, "button", 5);
                    \u0275\u0275text(9, "Cancel");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(10, "button", 6);
                    \u0275\u0275listener("click", function TopicAddComponentDialog_Template_button_click_10_listener() {
                        return ctx.save();
                    });
                    \u0275\u0275text(11, "Add");
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    \u0275\u0275advance(6);
                    \u0275\u0275twoWayProperty("ngModel", ctx.topicName);
                }
            },
            dependencies: [
                MatDialogContent,
                MatDialogTitle,
                MatDialogActions,
                MatButton,
                MatDialogClose,
                MatFormField,
                MatLabel,
                FormsModule,
                DefaultValueAccessor,
                NgControlStatus,
                NgModel,
                MatInput,
                ReactiveFormsModule
            ],
            styles: ["\n\n.head-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  justify-content: flex-end;\n}\n/*# sourceMappingURL=topic-add.component.css.map */"]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(TopicAddComponentDialog, {
        className: "TopicAddComponentDialog",
        filePath: "src/app/modules/sns/topic-add/topic-add.component.ts",
        lineNumber: 38
    });
})();

// node_modules/@aws-sdk/client-sns/dist-es/auth/httpAuthSchemeProvider.js
var defaultSNSHttpAuthSchemeParametersProvider = (config, context, input) => __async(void 0, null, function* () {
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
            name: "sns",
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

var defaultSNSHttpAuthSchemeProvider = (authParameters) => {
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

// node_modules/@aws-sdk/client-sns/dist-es/endpoint/EndpointParameters.js
var resolveClientEndpointParameters = (options) => {
    return __spreadProps(__spreadValues({}, options), {
        useDualstackEndpoint: options.useDualstackEndpoint ?? false,
        useFipsEndpoint: options.useFipsEndpoint ?? false,
        defaultSigningName: "sns"
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

// node_modules/@aws-sdk/client-sns/package.json
var package_default = {
    name: "@aws-sdk/client-sns",
    description: "AWS SDK for JavaScript Sns Client for Node.js, Browser and React Native",
    version: "3.693.0",
    scripts: {
        build: "concurrently 'yarn:build:cjs' 'yarn:build:es' 'yarn:build:types'",
        "build:cjs": "node ../../scripts/compilation/inline client-sns",
        "build:es": "tsc -p tsconfig.es.json",
        "build:include:deps": "lerna run --scope $npm_package_name --include-dependencies build",
        "build:types": "tsc -p tsconfig.types.json",
        "build:types:downlevel": "downlevel-dts dist-types dist-types/ts3.4",
        clean: "rimraf ./dist-* && rimraf *.tsbuildinfo",
        "extract:docs": "api-extractor run --local",
        "generate:client": "node ../../scripts/generate-clients/single-service --solo sns"
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
    homepage: "https://github.com/aws/aws-sdk-js-v3/tree/main/clients/client-sns",
    repository: {
        type: "git",
        url: "https://github.com/aws/aws-sdk-js-v3.git",
        directory: "clients/client-sns"
    }
};

// node_modules/@aws-sdk/client-sns/dist-es/endpoint/ruleset.js
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
var h = "stringEquals";
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
    [x]: "Region"
};
var p = {
    [v]: "getAttr",
    [w]: [{
        [x]: g
    }, "supportsFIPS"]
};
var q = {
    [v]: c,
    [w]: [true, {
        [v]: "getAttr",
        [w]: [{
            [x]: g
        }, "supportsDualStack"]
    }]
};
var r = [l];
var s = [m];
var t = [o];
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
                        [w]: [a, p]
                    }, q],
                    rules: [{
                        endpoint: {
                            url: "https://sns-fips.{Region}.{PartitionResult#dualStackDnsSuffix}",
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
                        [w]: [p, a]
                    }],
                    rules: [{
                        conditions: [{
                            [v]: h,
                            [w]: [o, "us-gov-east-1"]
                        }],
                        endpoint: {
                            url: "https://sns.us-gov-east-1.amazonaws.com",
                            properties: n,
                            headers: n
                        },
                        type: e
                    }, {
                        conditions: [{
                            [v]: h,
                            [w]: [o, "us-gov-west-1"]
                        }],
                        endpoint: {
                            url: "https://sns.us-gov-west-1.amazonaws.com",
                            properties: n,
                            headers: n
                        },
                        type: e
                    }, {
                        endpoint: {
                            url: "https://sns-fips.{Region}.{PartitionResult#dnsSuffix}",
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
                            url: "https://sns.{Region}.{PartitionResult#dualStackDnsSuffix}",
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
                    url: "https://sns.{Region}.{PartitionResult#dnsSuffix}",
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

// node_modules/@aws-sdk/client-sns/dist-es/endpoint/endpointResolver.js
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

// node_modules/@aws-sdk/client-sns/dist-es/runtimeConfig.shared.js
var getRuntimeConfig = (config) => {
    return {
        apiVersion: "2010-03-31",
        base64Decoder: config?.base64Decoder ?? fromBase64,
        base64Encoder: config?.base64Encoder ?? toBase64,
        disableHostPrefix: config?.disableHostPrefix ?? false,
        endpointProvider: config?.endpointProvider ?? defaultEndpointResolver,
        extensions: config?.extensions ?? [],
        httpAuthSchemeProvider: config?.httpAuthSchemeProvider ?? defaultSNSHttpAuthSchemeProvider,
        httpAuthSchemes: config?.httpAuthSchemes ?? [{
            schemeId: "aws.auth#sigv4",
            identityProvider: (ipc) => ipc.getIdentityProvider("aws.auth#sigv4"),
            signer: new AwsSdkSigV4Signer()
        }],
        logger: config?.logger ?? new NoOpLogger(),
        serviceId: config?.serviceId ?? "SNS",
        urlParser: config?.urlParser ?? parseUrl,
        utf8Decoder: config?.utf8Decoder ?? fromUtf8,
        utf8Encoder: config?.utf8Encoder ?? toUtf8
    };
};

// node_modules/@aws-sdk/client-sns/dist-es/runtimeConfig.browser.js
var getRuntimeConfig2 = (config) => {
    const defaultsMode = resolveDefaultsModeConfig(config);
    const defaultConfigProvider = () => defaultsMode().then(loadConfigsForDefaultMode);
    const clientSharedValues = getRuntimeConfig(config);
    return __spreadProps(__spreadValues(__spreadValues({}, clientSharedValues), config), {
        runtime: "browser",
        defaultsMode,
        bodyLengthChecker: config?.bodyLengthChecker ?? calculateBodyLength,
        credentialDefaultProvider: config?.credentialDefaultProvider ?? ((_2) => () => Promise.reject(new Error("Credential is missing"))),
        defaultUserAgentProvider: config?.defaultUserAgentProvider ?? createDefaultUserAgentProvider({
            serviceId: clientSharedValues.serviceId,
            clientVersion: package_default.version
        }),
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

// node_modules/@aws-sdk/client-sns/dist-es/auth/httpAuthExtensionConfiguration.js
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

// node_modules/@aws-sdk/client-sns/dist-es/runtimeExtensions.js
var asPartial = (t2) => t2;
var resolveRuntimeExtensions = (runtimeConfig, extensions) => {
    const extensionConfiguration = __spreadValues(__spreadValues(__spreadValues(__spreadValues({}, asPartial(getAwsRegionExtensionConfiguration(runtimeConfig))), asPartial(getDefaultExtensionConfiguration(runtimeConfig))), asPartial(getHttpHandlerExtensionConfiguration(runtimeConfig))), asPartial(getHttpAuthExtensionConfiguration(runtimeConfig)));
    extensions.forEach((extension) => extension.configure(extensionConfiguration));
    return __spreadValues(__spreadValues(__spreadValues(__spreadValues(__spreadValues({}, runtimeConfig), resolveAwsRegionExtensionConfiguration(extensionConfiguration)), resolveDefaultRuntimeConfig(extensionConfiguration)), resolveHttpHandlerRuntimeConfig(extensionConfiguration)), resolveHttpAuthRuntimeConfig(extensionConfiguration));
};

// node_modules/@aws-sdk/client-sns/dist-es/SNSClient.js
var SNSClient = class extends Client {
    constructor(...[configuration]) {
        const _config_0 = getRuntimeConfig2(configuration || {});
        const _config_1 = resolveClientEndpointParameters(_config_0);
        const _config_2 = resolveUserAgentConfig(_config_1);
        const _config_3 = resolveRetryConfig(_config_2);
        const _config_4 = resolveRegionConfig(_config_3);
        const _config_5 = resolveHostHeaderConfig(_config_4);
        const _config_6 = resolveEndpointConfig(_config_5);
        const _config_7 = resolveHttpAuthSchemeConfig(_config_6);
        const _config_8 = resolveRuntimeExtensions(_config_7, configuration?.extensions || []);
        super(_config_8);
        this.config = _config_8;
        this.middlewareStack.use(getUserAgentPlugin(this.config));
        this.middlewareStack.use(getRetryPlugin(this.config));
        this.middlewareStack.use(getContentLengthPlugin(this.config));
        this.middlewareStack.use(getHostHeaderPlugin(this.config));
        this.middlewareStack.use(getLoggerPlugin(this.config));
        this.middlewareStack.use(getRecursionDetectionPlugin(this.config));
        this.middlewareStack.use(getHttpAuthSchemeEndpointRuleSetPlugin(this.config, {
            httpAuthSchemeParametersProvider: defaultSNSHttpAuthSchemeParametersProvider,
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

// node_modules/@aws-sdk/client-sns/dist-es/models/SNSServiceException.js
var SNSServiceException = class _SNSServiceException extends ServiceException {
    constructor(options) {
        super(options);
        Object.setPrototypeOf(this, _SNSServiceException.prototype);
    }
};

// node_modules/@aws-sdk/client-sns/dist-es/models/models_0.js
var AuthorizationErrorException = class _AuthorizationErrorException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "AuthorizationErrorException",
            $fault: "client"
        }, opts));
        this.name = "AuthorizationErrorException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _AuthorizationErrorException.prototype);
    }
};
var InternalErrorException = class _InternalErrorException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "InternalErrorException",
            $fault: "server"
        }, opts));
        this.name = "InternalErrorException";
        this.$fault = "server";
        Object.setPrototypeOf(this, _InternalErrorException.prototype);
    }
};
var InvalidParameterException = class _InvalidParameterException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "InvalidParameterException",
            $fault: "client"
        }, opts));
        this.name = "InvalidParameterException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _InvalidParameterException.prototype);
    }
};
var NotFoundException = class _NotFoundException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "NotFoundException",
            $fault: "client"
        }, opts));
        this.name = "NotFoundException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _NotFoundException.prototype);
    }
};
var ThrottledException = class _ThrottledException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "ThrottledException",
            $fault: "client"
        }, opts));
        this.name = "ThrottledException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _ThrottledException.prototype);
    }
};
var FilterPolicyLimitExceededException = class _FilterPolicyLimitExceededException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "FilterPolicyLimitExceededException",
            $fault: "client"
        }, opts));
        this.name = "FilterPolicyLimitExceededException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _FilterPolicyLimitExceededException.prototype);
    }
};
var ReplayLimitExceededException = class _ReplayLimitExceededException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "ReplayLimitExceededException",
            $fault: "client"
        }, opts));
        this.name = "ReplayLimitExceededException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _ReplayLimitExceededException.prototype);
    }
};
var SubscriptionLimitExceededException = class _SubscriptionLimitExceededException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "SubscriptionLimitExceededException",
            $fault: "client"
        }, opts));
        this.name = "SubscriptionLimitExceededException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _SubscriptionLimitExceededException.prototype);
    }
};
var OptedOutException = class _OptedOutException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "OptedOutException",
            $fault: "client"
        }, opts));
        this.name = "OptedOutException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _OptedOutException.prototype);
    }
};
var UserErrorException = class _UserErrorException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "UserErrorException",
            $fault: "client"
        }, opts));
        this.name = "UserErrorException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _UserErrorException.prototype);
    }
};
var ConcurrentAccessException = class _ConcurrentAccessException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "ConcurrentAccessException",
            $fault: "client"
        }, opts));
        this.name = "ConcurrentAccessException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _ConcurrentAccessException.prototype);
    }
};
var InvalidSecurityException = class _InvalidSecurityException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "InvalidSecurityException",
            $fault: "client"
        }, opts));
        this.name = "InvalidSecurityException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _InvalidSecurityException.prototype);
    }
};
var StaleTagException = class _StaleTagException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "StaleTagException",
            $fault: "client"
        }, opts));
        this.name = "StaleTagException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _StaleTagException.prototype);
    }
};
var TagLimitExceededException = class _TagLimitExceededException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "TagLimitExceededException",
            $fault: "client"
        }, opts));
        this.name = "TagLimitExceededException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _TagLimitExceededException.prototype);
    }
};
var TagPolicyException = class _TagPolicyException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "TagPolicyException",
            $fault: "client"
        }, opts));
        this.name = "TagPolicyException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _TagPolicyException.prototype);
    }
};
var TopicLimitExceededException = class _TopicLimitExceededException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "TopicLimitExceededException",
            $fault: "client"
        }, opts));
        this.name = "TopicLimitExceededException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _TopicLimitExceededException.prototype);
    }
};
var ResourceNotFoundException = class _ResourceNotFoundException extends SNSServiceException {
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
var InvalidStateException = class _InvalidStateException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "InvalidStateException",
            $fault: "client"
        }, opts));
        this.name = "InvalidStateException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _InvalidStateException.prototype);
    }
};
var ValidationException = class _ValidationException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "ValidationException",
            $fault: "client"
        }, opts));
        this.name = "ValidationException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _ValidationException.prototype);
        this.Message = opts.Message;
    }
};
var EndpointDisabledException = class _EndpointDisabledException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "EndpointDisabledException",
            $fault: "client"
        }, opts));
        this.name = "EndpointDisabledException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _EndpointDisabledException.prototype);
    }
};
var InvalidParameterValueException = class _InvalidParameterValueException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "InvalidParameterValueException",
            $fault: "client"
        }, opts));
        this.name = "InvalidParameterValueException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _InvalidParameterValueException.prototype);
    }
};
var KMSAccessDeniedException = class _KMSAccessDeniedException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "KMSAccessDeniedException",
            $fault: "client"
        }, opts));
        this.name = "KMSAccessDeniedException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _KMSAccessDeniedException.prototype);
    }
};
var KMSDisabledException = class _KMSDisabledException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "KMSDisabledException",
            $fault: "client"
        }, opts));
        this.name = "KMSDisabledException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _KMSDisabledException.prototype);
    }
};
var KMSInvalidStateException = class _KMSInvalidStateException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "KMSInvalidStateException",
            $fault: "client"
        }, opts));
        this.name = "KMSInvalidStateException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _KMSInvalidStateException.prototype);
    }
};
var KMSNotFoundException = class _KMSNotFoundException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "KMSNotFoundException",
            $fault: "client"
        }, opts));
        this.name = "KMSNotFoundException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _KMSNotFoundException.prototype);
    }
};
var KMSOptInRequired = class _KMSOptInRequired extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "KMSOptInRequired",
            $fault: "client"
        }, opts));
        this.name = "KMSOptInRequired";
        this.$fault = "client";
        Object.setPrototypeOf(this, _KMSOptInRequired.prototype);
    }
};
var KMSThrottlingException = class _KMSThrottlingException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "KMSThrottlingException",
            $fault: "client"
        }, opts));
        this.name = "KMSThrottlingException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _KMSThrottlingException.prototype);
    }
};
var PlatformApplicationDisabledException = class _PlatformApplicationDisabledException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "PlatformApplicationDisabledException",
            $fault: "client"
        }, opts));
        this.name = "PlatformApplicationDisabledException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _PlatformApplicationDisabledException.prototype);
    }
};
var BatchEntryIdsNotDistinctException = class _BatchEntryIdsNotDistinctException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "BatchEntryIdsNotDistinctException",
            $fault: "client"
        }, opts));
        this.name = "BatchEntryIdsNotDistinctException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _BatchEntryIdsNotDistinctException.prototype);
    }
};
var BatchRequestTooLongException = class _BatchRequestTooLongException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "BatchRequestTooLongException",
            $fault: "client"
        }, opts));
        this.name = "BatchRequestTooLongException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _BatchRequestTooLongException.prototype);
    }
};
var EmptyBatchRequestException = class _EmptyBatchRequestException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "EmptyBatchRequestException",
            $fault: "client"
        }, opts));
        this.name = "EmptyBatchRequestException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _EmptyBatchRequestException.prototype);
    }
};
var InvalidBatchEntryIdException = class _InvalidBatchEntryIdException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "InvalidBatchEntryIdException",
            $fault: "client"
        }, opts));
        this.name = "InvalidBatchEntryIdException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _InvalidBatchEntryIdException.prototype);
    }
};
var TooManyEntriesInBatchRequestException = class _TooManyEntriesInBatchRequestException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "TooManyEntriesInBatchRequestException",
            $fault: "client"
        }, opts));
        this.name = "TooManyEntriesInBatchRequestException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _TooManyEntriesInBatchRequestException.prototype);
    }
};
var VerificationException = class _VerificationException extends SNSServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "VerificationException",
            $fault: "client"
        }, opts));
        this.name = "VerificationException";
        this.$fault = "client";
        Object.setPrototypeOf(this, _VerificationException.prototype);
        this.Message = opts.Message;
        this.Status = opts.Status;
    }
};
var PublishInputFilterSensitiveLog = (obj) => __spreadValues(__spreadValues({}, obj), obj.PhoneNumber && {
    PhoneNumber: SENSITIVE_STRING
});

// node_modules/@aws-sdk/client-sns/dist-es/protocols/Aws_query.js
var se_CreateTopicCommand = (input, context) => __async(void 0, null, function* () {
    const headers = SHARED_HEADERS;
    let body;
    body = buildFormUrlencodedString(__spreadProps(__spreadValues({}, se_CreateTopicInput(input, context)), {
        [_A]: _CT,
        [_V]: _
    }));
    return buildHttpRpcRequest(context, headers, "/", void 0, body);
});
var se_DeleteTopicCommand = (input, context) => __async(void 0, null, function* () {
    const headers = SHARED_HEADERS;
    let body;
    body = buildFormUrlencodedString(__spreadProps(__spreadValues({}, se_DeleteTopicInput(input, context)), {
        [_A]: _DT,
        [_V]: _
    }));
    return buildHttpRpcRequest(context, headers, "/", void 0, body);
});
var se_ListTopicsCommand = (input, context) => __async(void 0, null, function* () {
    const headers = SHARED_HEADERS;
    let body;
    body = buildFormUrlencodedString(__spreadProps(__spreadValues({}, se_ListTopicsInput(input, context)), {
        [_A]: _LT,
        [_V]: _
    }));
    return buildHttpRpcRequest(context, headers, "/", void 0, body);
});
var se_PublishCommand = (input, context) => __async(void 0, null, function* () {
    const headers = SHARED_HEADERS;
    let body;
    body = buildFormUrlencodedString(__spreadProps(__spreadValues({}, se_PublishInput(input, context)), {
        [_A]: _P,
        [_V]: _
    }));
    return buildHttpRpcRequest(context, headers, "/", void 0, body);
});
var se_SubscribeCommand = (input, context) => __async(void 0, null, function* () {
    const headers = SHARED_HEADERS;
    let body;
    body = buildFormUrlencodedString(__spreadProps(__spreadValues({}, se_SubscribeInput(input, context)), {
        [_A]: _S,
        [_V]: _
    }));
    return buildHttpRpcRequest(context, headers, "/", void 0, body);
});
var de_CreateTopicCommand = (output, context) => __async(void 0, null, function* () {
    if (output.statusCode >= 300) {
        return de_CommandError(output, context);
    }
    const data = yield parseXmlBody(output.body, context);
    let contents = {};
    contents = de_CreateTopicResponse(data.CreateTopicResult, context);
    const response = __spreadValues({
        $metadata: deserializeMetadata(output)
    }, contents);
    return response;
});
var de_DeleteTopicCommand = (output, context) => __async(void 0, null, function* () {
    if (output.statusCode >= 300) {
        return de_CommandError(output, context);
    }
    yield collectBody(output.body, context);
    const response = {
        $metadata: deserializeMetadata(output)
    };
    return response;
});
var de_ListTopicsCommand = (output, context) => __async(void 0, null, function* () {
    if (output.statusCode >= 300) {
        return de_CommandError(output, context);
    }
    const data = yield parseXmlBody(output.body, context);
    let contents = {};
    contents = de_ListTopicsResponse(data.ListTopicsResult, context);
    const response = __spreadValues({
        $metadata: deserializeMetadata(output)
    }, contents);
    return response;
});
var de_PublishCommand = (output, context) => __async(void 0, null, function* () {
    if (output.statusCode >= 300) {
        return de_CommandError(output, context);
    }
    const data = yield parseXmlBody(output.body, context);
    let contents = {};
    contents = de_PublishResponse(data.PublishResult, context);
    const response = __spreadValues({
        $metadata: deserializeMetadata(output)
    }, contents);
    return response;
});
var de_SubscribeCommand = (output, context) => __async(void 0, null, function* () {
    if (output.statusCode >= 300) {
        return de_CommandError(output, context);
    }
    const data = yield parseXmlBody(output.body, context);
    let contents = {};
    contents = de_SubscribeResponse(data.SubscribeResult, context);
    const response = __spreadValues({
        $metadata: deserializeMetadata(output)
    }, contents);
    return response;
});
var de_CommandError = (output, context) => __async(void 0, null, function* () {
    const parsedOutput = __spreadProps(__spreadValues({}, output), {
        body: yield parseXmlErrorBody(output.body, context)
    });
    const errorCode = loadQueryErrorCode(output, parsedOutput.body);
    switch (errorCode) {
        case "AuthorizationError":
        case "com.amazonaws.sns#AuthorizationErrorException":
            throw yield de_AuthorizationErrorExceptionRes(parsedOutput, context);
        case "InternalError":
        case "com.amazonaws.sns#InternalErrorException":
            throw yield de_InternalErrorExceptionRes(parsedOutput, context);
        case "InvalidParameter":
        case "com.amazonaws.sns#InvalidParameterException":
            throw yield de_InvalidParameterExceptionRes(parsedOutput, context);
        case "NotFound":
        case "com.amazonaws.sns#NotFoundException":
            throw yield de_NotFoundExceptionRes(parsedOutput, context);
        case "Throttled":
        case "com.amazonaws.sns#ThrottledException":
            throw yield de_ThrottledExceptionRes(parsedOutput, context);
        case "FilterPolicyLimitExceeded":
        case "com.amazonaws.sns#FilterPolicyLimitExceededException":
            throw yield de_FilterPolicyLimitExceededExceptionRes(parsedOutput, context);
        case "ReplayLimitExceeded":
        case "com.amazonaws.sns#ReplayLimitExceededException":
            throw yield de_ReplayLimitExceededExceptionRes(parsedOutput, context);
        case "SubscriptionLimitExceeded":
        case "com.amazonaws.sns#SubscriptionLimitExceededException":
            throw yield de_SubscriptionLimitExceededExceptionRes(parsedOutput, context);
        case "OptedOut":
        case "com.amazonaws.sns#OptedOutException":
            throw yield de_OptedOutExceptionRes(parsedOutput, context);
        case "UserError":
        case "com.amazonaws.sns#UserErrorException":
            throw yield de_UserErrorExceptionRes(parsedOutput, context);
        case "ConcurrentAccess":
        case "com.amazonaws.sns#ConcurrentAccessException":
            throw yield de_ConcurrentAccessExceptionRes(parsedOutput, context);
        case "InvalidSecurity":
        case "com.amazonaws.sns#InvalidSecurityException":
            throw yield de_InvalidSecurityExceptionRes(parsedOutput, context);
        case "StaleTag":
        case "com.amazonaws.sns#StaleTagException":
            throw yield de_StaleTagExceptionRes(parsedOutput, context);
        case "TagLimitExceeded":
        case "com.amazonaws.sns#TagLimitExceededException":
            throw yield de_TagLimitExceededExceptionRes(parsedOutput, context);
        case "TagPolicy":
        case "com.amazonaws.sns#TagPolicyException":
            throw yield de_TagPolicyExceptionRes(parsedOutput, context);
        case "TopicLimitExceeded":
        case "com.amazonaws.sns#TopicLimitExceededException":
            throw yield de_TopicLimitExceededExceptionRes(parsedOutput, context);
        case "ResourceNotFound":
        case "com.amazonaws.sns#ResourceNotFoundException":
            throw yield de_ResourceNotFoundExceptionRes(parsedOutput, context);
        case "InvalidState":
        case "com.amazonaws.sns#InvalidStateException":
            throw yield de_InvalidStateExceptionRes(parsedOutput, context);
        case "ValidationException":
        case "com.amazonaws.sns#ValidationException":
            throw yield de_ValidationExceptionRes(parsedOutput, context);
        case "EndpointDisabled":
        case "com.amazonaws.sns#EndpointDisabledException":
            throw yield de_EndpointDisabledExceptionRes(parsedOutput, context);
        case "KMSAccessDenied":
        case "com.amazonaws.sns#KMSAccessDeniedException":
            throw yield de_KMSAccessDeniedExceptionRes(parsedOutput, context);
        case "KMSDisabled":
        case "com.amazonaws.sns#KMSDisabledException":
            throw yield de_KMSDisabledExceptionRes(parsedOutput, context);
        case "KMSInvalidState":
        case "com.amazonaws.sns#KMSInvalidStateException":
            throw yield de_KMSInvalidStateExceptionRes(parsedOutput, context);
        case "KMSNotFound":
        case "com.amazonaws.sns#KMSNotFoundException":
            throw yield de_KMSNotFoundExceptionRes(parsedOutput, context);
        case "KMSOptInRequired":
        case "com.amazonaws.sns#KMSOptInRequired":
            throw yield de_KMSOptInRequiredRes(parsedOutput, context);
        case "KMSThrottling":
        case "com.amazonaws.sns#KMSThrottlingException":
            throw yield de_KMSThrottlingExceptionRes(parsedOutput, context);
        case "ParameterValueInvalid":
        case "com.amazonaws.sns#InvalidParameterValueException":
            throw yield de_InvalidParameterValueExceptionRes(parsedOutput, context);
        case "PlatformApplicationDisabled":
        case "com.amazonaws.sns#PlatformApplicationDisabledException":
            throw yield de_PlatformApplicationDisabledExceptionRes(parsedOutput, context);
        case "BatchEntryIdsNotDistinct":
        case "com.amazonaws.sns#BatchEntryIdsNotDistinctException":
            throw yield de_BatchEntryIdsNotDistinctExceptionRes(parsedOutput, context);
        case "BatchRequestTooLong":
        case "com.amazonaws.sns#BatchRequestTooLongException":
            throw yield de_BatchRequestTooLongExceptionRes(parsedOutput, context);
        case "EmptyBatchRequest":
        case "com.amazonaws.sns#EmptyBatchRequestException":
            throw yield de_EmptyBatchRequestExceptionRes(parsedOutput, context);
        case "InvalidBatchEntryId":
        case "com.amazonaws.sns#InvalidBatchEntryIdException":
            throw yield de_InvalidBatchEntryIdExceptionRes(parsedOutput, context);
        case "TooManyEntriesInBatchRequest":
        case "com.amazonaws.sns#TooManyEntriesInBatchRequestException":
            throw yield de_TooManyEntriesInBatchRequestExceptionRes(parsedOutput, context);
        case "VerificationException":
        case "com.amazonaws.sns#VerificationException":
            throw yield de_VerificationExceptionRes(parsedOutput, context);
        default:
            const parsedBody = parsedOutput.body;
            return throwDefaultError({
                output,
                parsedBody: parsedBody.Error,
                errorCode
            });
    }
});
var de_AuthorizationErrorExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_AuthorizationErrorException(body.Error, context);
    const exception = new AuthorizationErrorException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_BatchEntryIdsNotDistinctExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_BatchEntryIdsNotDistinctException(body.Error, context);
    const exception = new BatchEntryIdsNotDistinctException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_BatchRequestTooLongExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_BatchRequestTooLongException(body.Error, context);
    const exception = new BatchRequestTooLongException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_ConcurrentAccessExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_ConcurrentAccessException(body.Error, context);
    const exception = new ConcurrentAccessException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_EmptyBatchRequestExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_EmptyBatchRequestException(body.Error, context);
    const exception = new EmptyBatchRequestException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_EndpointDisabledExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_EndpointDisabledException(body.Error, context);
    const exception = new EndpointDisabledException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_FilterPolicyLimitExceededExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_FilterPolicyLimitExceededException(body.Error, context);
    const exception = new FilterPolicyLimitExceededException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_InternalErrorExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_InternalErrorException(body.Error, context);
    const exception = new InternalErrorException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_InvalidBatchEntryIdExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_InvalidBatchEntryIdException(body.Error, context);
    const exception = new InvalidBatchEntryIdException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_InvalidParameterExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_InvalidParameterException(body.Error, context);
    const exception = new InvalidParameterException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_InvalidParameterValueExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_InvalidParameterValueException(body.Error, context);
    const exception = new InvalidParameterValueException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_InvalidSecurityExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_InvalidSecurityException(body.Error, context);
    const exception = new InvalidSecurityException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_InvalidStateExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_InvalidStateException(body.Error, context);
    const exception = new InvalidStateException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_KMSAccessDeniedExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_KMSAccessDeniedException(body.Error, context);
    const exception = new KMSAccessDeniedException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_KMSDisabledExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_KMSDisabledException(body.Error, context);
    const exception = new KMSDisabledException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_KMSInvalidStateExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_KMSInvalidStateException(body.Error, context);
    const exception = new KMSInvalidStateException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_KMSNotFoundExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_KMSNotFoundException(body.Error, context);
    const exception = new KMSNotFoundException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_KMSOptInRequiredRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_KMSOptInRequired(body.Error, context);
    const exception = new KMSOptInRequired(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_KMSThrottlingExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_KMSThrottlingException(body.Error, context);
    const exception = new KMSThrottlingException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_NotFoundExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_NotFoundException(body.Error, context);
    const exception = new NotFoundException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_OptedOutExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_OptedOutException(body.Error, context);
    const exception = new OptedOutException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_PlatformApplicationDisabledExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_PlatformApplicationDisabledException(body.Error, context);
    const exception = new PlatformApplicationDisabledException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_ReplayLimitExceededExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_ReplayLimitExceededException(body.Error, context);
    const exception = new ReplayLimitExceededException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_ResourceNotFoundExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_ResourceNotFoundException(body.Error, context);
    const exception = new ResourceNotFoundException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_StaleTagExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_StaleTagException(body.Error, context);
    const exception = new StaleTagException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_SubscriptionLimitExceededExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_SubscriptionLimitExceededException(body.Error, context);
    const exception = new SubscriptionLimitExceededException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_TagLimitExceededExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_TagLimitExceededException(body.Error, context);
    const exception = new TagLimitExceededException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_TagPolicyExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_TagPolicyException(body.Error, context);
    const exception = new TagPolicyException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_ThrottledExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_ThrottledException(body.Error, context);
    const exception = new ThrottledException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_TooManyEntriesInBatchRequestExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_TooManyEntriesInBatchRequestException(body.Error, context);
    const exception = new TooManyEntriesInBatchRequestException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_TopicLimitExceededExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_TopicLimitExceededException(body.Error, context);
    const exception = new TopicLimitExceededException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_UserErrorExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_UserErrorException(body.Error, context);
    const exception = new UserErrorException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_ValidationExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_ValidationException(body.Error, context);
    const exception = new ValidationException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var de_VerificationExceptionRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const body = parsedOutput.body;
    const deserialized = de_VerificationException(body.Error, context);
    const exception = new VerificationException(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, deserialized));
    return decorateServiceException(exception, body);
});
var se_CreateTopicInput = (input, context) => {
    const entries = {};
    if (input[_N] != null) {
        entries[_N] = input[_N];
    }
    if (input[_At] != null) {
        const memberEntries = se_TopicAttributesMap(input[_At], context);
        Object.entries(memberEntries).forEach(([key, value]) => {
            const loc = `Attributes.${key}`;
            entries[loc] = value;
        });
    }
    if (input[_Ta] != null) {
        const memberEntries = se_TagList(input[_Ta], context);
        if (input[_Ta]?.length === 0) {
            entries.Tags = [];
        }
        Object.entries(memberEntries).forEach(([key, value]) => {
            const loc = `Tags.${key}`;
            entries[loc] = value;
        });
    }
    if (input[_DPP] != null) {
        entries[_DPP] = input[_DPP];
    }
    return entries;
};
var se_DeleteTopicInput = (input, context) => {
    const entries = {};
    if (input[_TA] != null) {
        entries[_TA] = input[_TA];
    }
    return entries;
};
var se_ListTopicsInput = (input, context) => {
    const entries = {};
    if (input[_NT] != null) {
        entries[_NT] = input[_NT];
    }
    return entries;
};
var se_MessageAttributeMap = (input, context) => {
    const entries = {};
    let counter = 1;
    Object.keys(input).filter((key) => input[key] != null).forEach((key) => {
        entries[`entry.${counter}.Name`] = key;
        const memberEntries = se_MessageAttributeValue(input[key], context);
        Object.entries(memberEntries).forEach(([key2, value]) => {
            entries[`entry.${counter}.Value.${key2}`] = value;
        });
        counter++;
    });
    return entries;
};
var se_MessageAttributeValue = (input, context) => {
    const entries = {};
    if (input[_DTa] != null) {
        entries[_DTa] = input[_DTa];
    }
    if (input[_SV] != null) {
        entries[_SV] = input[_SV];
    }
    if (input[_BV] != null) {
        entries[_BV] = context.base64Encoder(input[_BV]);
    }
    return entries;
};
var se_PublishInput = (input, context) => {
    const entries = {};
    if (input[_TA] != null) {
        entries[_TA] = input[_TA];
    }
    if (input[_TAa] != null) {
        entries[_TAa] = input[_TAa];
    }
    if (input[_PN] != null) {
        entries[_PN] = input[_PN];
    }
    if (input[_M] != null) {
        entries[_M] = input[_M];
    }
    if (input[_Su] != null) {
        entries[_Su] = input[_Su];
    }
    if (input[_MS] != null) {
        entries[_MS] = input[_MS];
    }
    if (input[_MA] != null) {
        const memberEntries = se_MessageAttributeMap(input[_MA], context);
        Object.entries(memberEntries).forEach(([key, value]) => {
            const loc = `MessageAttributes.${key}`;
            entries[loc] = value;
        });
    }
    if (input[_MDI] != null) {
        entries[_MDI] = input[_MDI];
    }
    if (input[_MGI] != null) {
        entries[_MGI] = input[_MGI];
    }
    return entries;
};
var se_SubscribeInput = (input, context) => {
    const entries = {};
    if (input[_TA] != null) {
        entries[_TA] = input[_TA];
    }
    if (input[_Pr] != null) {
        entries[_Pr] = input[_Pr];
    }
    if (input[_E] != null) {
        entries[_E] = input[_E];
    }
    if (input[_At] != null) {
        const memberEntries = se_SubscriptionAttributesMap(input[_At], context);
        Object.entries(memberEntries).forEach(([key, value]) => {
            const loc = `Attributes.${key}`;
            entries[loc] = value;
        });
    }
    if (input[_RSA] != null) {
        entries[_RSA] = input[_RSA];
    }
    return entries;
};
var se_SubscriptionAttributesMap = (input, context) => {
    const entries = {};
    let counter = 1;
    Object.keys(input).filter((key) => input[key] != null).forEach((key) => {
        entries[`entry.${counter}.key`] = key;
        entries[`entry.${counter}.value`] = input[key];
        counter++;
    });
    return entries;
};
var se_Tag = (input, context) => {
    const entries = {};
    if (input[_K] != null) {
        entries[_K] = input[_K];
    }
    if (input[_Va] != null) {
        entries[_Va] = input[_Va];
    }
    return entries;
};
var se_TagList = (input, context) => {
    const entries = {};
    let counter = 1;
    for (const entry of input) {
        if (entry === null) {
            continue;
        }
        const memberEntries = se_Tag(entry, context);
        Object.entries(memberEntries).forEach(([key, value]) => {
            entries[`member.${counter}.${key}`] = value;
        });
        counter++;
    }
    return entries;
};
var se_TopicAttributesMap = (input, context) => {
    const entries = {};
    let counter = 1;
    Object.keys(input).filter((key) => input[key] != null).forEach((key) => {
        entries[`entry.${counter}.key`] = key;
        entries[`entry.${counter}.value`] = input[key];
        counter++;
    });
    return entries;
};
var de_AuthorizationErrorException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_BatchEntryIdsNotDistinctException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_BatchRequestTooLongException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_ConcurrentAccessException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_CreateTopicResponse = (output, context) => {
    const contents = {};
    if (output[_TA] != null) {
        contents[_TA] = expectString(output[_TA]);
    }
    return contents;
};
var de_EmptyBatchRequestException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_EndpointDisabledException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_FilterPolicyLimitExceededException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_InternalErrorException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_InvalidBatchEntryIdException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_InvalidParameterException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_InvalidParameterValueException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_InvalidSecurityException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_InvalidStateException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_KMSAccessDeniedException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_KMSDisabledException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_KMSInvalidStateException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_KMSNotFoundException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_KMSOptInRequired = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_KMSThrottlingException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_ListTopicsResponse = (output, context) => {
    const contents = {};
    if (output.Topics === "") {
        contents[_To] = [];
    } else if (output[_To] != null && output[_To][_me] != null) {
        contents[_To] = de_TopicsList(getArrayIfSingleItem(output[_To][_me]), context);
    }
    if (output[_NT] != null) {
        contents[_NT] = expectString(output[_NT]);
    }
    return contents;
};
var de_NotFoundException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_OptedOutException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_PlatformApplicationDisabledException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_PublishResponse = (output, context) => {
    const contents = {};
    if (output[_MI] != null) {
        contents[_MI] = expectString(output[_MI]);
    }
    if (output[_SN] != null) {
        contents[_SN] = expectString(output[_SN]);
    }
    return contents;
};
var de_ReplayLimitExceededException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_ResourceNotFoundException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_StaleTagException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_SubscribeResponse = (output, context) => {
    const contents = {};
    if (output[_SA] != null) {
        contents[_SA] = expectString(output[_SA]);
    }
    return contents;
};
var de_SubscriptionLimitExceededException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_TagLimitExceededException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_TagPolicyException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_ThrottledException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_TooManyEntriesInBatchRequestException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_Topic = (output, context) => {
    const contents = {};
    if (output[_TA] != null) {
        contents[_TA] = expectString(output[_TA]);
    }
    return contents;
};
var de_TopicLimitExceededException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_TopicsList = (output, context) => {
    return (output || []).filter((e2) => e2 != null).map((entry) => {
        return de_Topic(entry, context);
    });
};
var de_UserErrorException = (output, context) => {
    const contents = {};
    if (output[_m] != null) {
        contents[_m] = expectString(output[_m]);
    }
    return contents;
};
var de_ValidationException = (output, context) => {
    const contents = {};
    if (output[_M] != null) {
        contents[_M] = expectString(output[_M]);
    }
    return contents;
};
var de_VerificationException = (output, context) => {
    const contents = {};
    if (output[_M] != null) {
        contents[_M] = expectString(output[_M]);
    }
    if (output[_St] != null) {
        contents[_St] = expectString(output[_St]);
    }
    return contents;
};
var deserializeMetadata = (output) => ({
    httpStatusCode: output.statusCode,
    requestId: output.headers["x-amzn-requestid"] ?? output.headers["x-amzn-request-id"] ?? output.headers["x-amz-request-id"],
    extendedRequestId: output.headers["x-amz-id-2"],
    cfId: output.headers["x-amz-cf-id"]
});
var throwDefaultError = withBaseException(SNSServiceException);
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
var SHARED_HEADERS = {
    "content-type": "application/x-www-form-urlencoded"
};
var _ = "2010-03-31";
var _A = "Action";
var _At = "Attributes";
var _BV = "BinaryValue";
var _CT = "CreateTopic";
var _DPP = "DataProtectionPolicy";
var _DT = "DeleteTopic";
var _DTa = "DataType";
var _E = "Endpoint";
var _K = "Key";
var _LT = "ListTopics";
var _M = "Message";
var _MA = "MessageAttributes";
var _MDI = "MessageDeduplicationId";
var _MGI = "MessageGroupId";
var _MI = "MessageId";
var _MS = "MessageStructure";
var _N = "Name";
var _NT = "NextToken";
var _P = "Publish";
var _PN = "PhoneNumber";
var _Pr = "Protocol";
var _RSA = "ReturnSubscriptionArn";
var _S = "Subscribe";
var _SA = "SubscriptionArn";
var _SN = "SequenceNumber";
var _SV = "StringValue";
var _St = "Status";
var _Su = "Subject";
var _TA = "TopicArn";
var _TAa = "TargetArn";
var _Ta = "Tags";
var _To = "Topics";
var _V = "Version";
var _Va = "Value";
var _m = "message";
var _me = "member";
var buildFormUrlencodedString = (formEntries) => Object.entries(formEntries).map(([key, value]) => extendedEncodeURIComponent(key) + "=" + extendedEncodeURIComponent(value)).join("&");
var loadQueryErrorCode = (output, data) => {
    if (data.Error?.Code !== void 0) {
        return data.Error.Code;
    }
    if (output.statusCode == 404) {
        return "NotFound";
    }
};

// node_modules/@aws-sdk/client-sns/dist-es/commands/CreateTopicCommand.js
var CreateTopicCommand = class extends Command.classBuilder().ep(commonParams).m(function (Command2, cs, config, o2) {
    return [getSerdePlugin(config, this.serialize, this.deserialize), getEndpointPlugin(config, Command2.getEndpointParameterInstructions())];
}).s("AmazonSimpleNotificationService", "CreateTopic", {}).n("SNSClient", "CreateTopicCommand").f(void 0, void 0).ser(se_CreateTopicCommand).de(de_CreateTopicCommand).build() {
};

// node_modules/@aws-sdk/client-sns/dist-es/commands/DeleteTopicCommand.js
var DeleteTopicCommand = class extends Command.classBuilder().ep(commonParams).m(function (Command2, cs, config, o2) {
    return [getSerdePlugin(config, this.serialize, this.deserialize), getEndpointPlugin(config, Command2.getEndpointParameterInstructions())];
}).s("AmazonSimpleNotificationService", "DeleteTopic", {}).n("SNSClient", "DeleteTopicCommand").f(void 0, void 0).ser(se_DeleteTopicCommand).de(de_DeleteTopicCommand).build() {
};

// node_modules/@aws-sdk/client-sns/dist-es/commands/ListTopicsCommand.js
var ListTopicsCommand = class extends Command.classBuilder().ep(commonParams).m(function (Command2, cs, config, o2) {
    return [getSerdePlugin(config, this.serialize, this.deserialize), getEndpointPlugin(config, Command2.getEndpointParameterInstructions())];
}).s("AmazonSimpleNotificationService", "ListTopics", {}).n("SNSClient", "ListTopicsCommand").f(void 0, void 0).ser(se_ListTopicsCommand).de(de_ListTopicsCommand).build() {
};

// node_modules/@aws-sdk/client-sns/dist-es/commands/PublishCommand.js
var PublishCommand = class extends Command.classBuilder().ep(commonParams).m(function (Command2, cs, config, o2) {
    return [getSerdePlugin(config, this.serialize, this.deserialize), getEndpointPlugin(config, Command2.getEndpointParameterInstructions())];
}).s("AmazonSimpleNotificationService", "Publish", {}).n("SNSClient", "PublishCommand").f(PublishInputFilterSensitiveLog, void 0).ser(se_PublishCommand).de(de_PublishCommand).build() {
};

// node_modules/@aws-sdk/client-sns/dist-es/commands/SubscribeCommand.js
var SubscribeCommand = class extends Command.classBuilder().ep(commonParams).m(function (Command2, cs, config, o2) {
    return [getSerdePlugin(config, this.serialize, this.deserialize), getEndpointPlugin(config, Command2.getEndpointParameterInstructions())];
}).s("AmazonSimpleNotificationService", "Subscribe", {}).n("SNSClient", "SubscribeCommand").f(void 0, void 0).ser(se_SubscribeCommand).de(de_SubscribeCommand).build() {
};

// src/app/modules/sns/service/sns-service.component.ts
var SnsService = class _SnsService {
    constructor(http) {
        this.http = http;
        this.client = new SNSClient({
            region: environment.awsmockRegion,
            endpoint: environment.gatewayEndpoint,
            maxAttempts: 1,
            credentials: {
                accessKeyId: "test",
                secretAccessKey: "test"
            },
            requestHandler: {
                requestTimeout: 3e3,
                httpsAgent: {maxSockets: 25, keepAlive: true}
            }
        });
        this.headers = new HttpHeaders({
            "Content-Type": "application/json",
            "Authorization": "AWS4-HMAC-SHA256 Credential=none/20240928/eu-central-1/s3/aws4_request, SignedHeaders=content-type;host;x-amz-date;x-amz-security-token;x-amz-target, Signature=01316d694335ec0e0bf68b08570490f1b0bae0b130ecbe13ebad511b3ece8a41"
        });
        this.url = environment.gatewayEndpoint + "/";
    }

    listTopics(pageIndex, pageSize) {
        const input = {
            NextToken: (pageIndex * pageSize).toString(),
            MaxResults: pageSize
        };
        return this.client.send(new ListTopicsCommand(input));
    }

    addTopic(topicName) {
        const input = {
            Name: topicName
        };
        return this.client.send(new CreateTopicCommand(input));
    }

    deleteTopic(topicArn) {
        const input = {
            TopicArn: topicArn
        };
        return this.client.send(new DeleteTopicCommand(input));
    }

    subscribe(topicArn, endpoint, protocol) {
        const input = {
            TopicArn: topicArn,
            Protocol: protocol,
            Endpoint: endpoint,
            ReturnSubscriptionArn: true
        };
        return this.client.send(new SubscribeCommand(input));
    }

    publishMessage(topicArn, message) {
        const input = {
            TopicArn: topicArn,
            Message: message
        };
        return this.client.send(new PublishCommand(input));
    }

    cleanup() {
        this.client.destroy();
    }

    /**
     * @brief Purges a topic, this will delete all the messages in the SNS topic.
     *
     * @par
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     *
     * @param prefix topic name prefix
     * @param pageSize page size
     * @param pageIndex page index
     * @param sortColumns sorting columns
     */
    listTopicCounters(prefix, pageSize, pageIndex, sortColumns) {
        let headers = this.headers.set("x-awsmock-target", "sns").set("x-awsmock-action", "ListTopicCounters");
        return this.http.post(this.url, {prefix, pageSize, pageIndex, sortColumns}, {headers});
    }

    /**
     * @brief Purges a topic, this will delete all the messages in the SNS topic.
     *
     * @par
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     *
     * @param topicArn topic ARN
     * @param pageSize page size
     * @param pageIndex page index
     * @param sortColumns sorting columns
     */
    listMessageCounters(topicArn, pageSize, pageIndex, sortColumns) {
        let headers = this.headers.set("x-awsmock-target", "sns").set("x-awsmock-action", "ListMessages");
        return this.http.post(this.url, {
            topicArn,
            pageSize,
            pageIndex,
            sortColumns
        }, {headers});
    }

    /**
     * @brief Purges a topic, this will delete all the messages in the SNS topic.
     *
     * @par
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     *
     * @param topicArn AWS topic ARN
     */
    purgeTopic(topicArn) {
        let headers = this.headers.set("x-awsmock-target", "sns").set("x-awsmock-action", "PurgeTopic");
        return this.http.post(this.url, {topicArn}, {headers});
    }

    /**
     * @brief Purges a topic, this will delete all the messages in the SNS topic.
     *
     * @par
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     *
     * @param topicArn SNS topic ARN
     * @param messageId SNS message ID
     */
    deleteMessage(topicArn, messageId) {
        let headers = this.headers.set("x-awsmock-target", "sns").set("x-awsmock-action", "DeleteMessage");
        return this.http.post(this.url, {topicArn, messageId}, {headers});
    }

    /**
     * @brief Returns the topic details
     *
     * @par
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     *
     * @param topicArn AWS topic ARN
     */
    getTopicDetails(topicArn) {
        let headers = this.headers.set("x-awsmock-target", "sns").set("x-awsmock-action", "GetTopicDetails");
        return this.http.post(this.url, {topicArn}, {headers});
    }

    /**
     * @brief Gets a list of subscriptions for a topic
     *
     * @par
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     *
     * @param topicArn topic ARN
     * @param pageSize page size
     * @param pageIndex page index
     * @param sortColumns sorting columns
     */
    listSubscriptionsCounters(topicArn, pageSize, pageIndex, sortColumns) {
        let headers = this.headers.set("x-awsmock-target", "sns").set("x-awsmock-action", "ListSubscriptionCounters");
        return this.http.post(this.url, {
            topicArn,
            pageSize,
            pageIndex,
            sortColumns
        }, {headers});
    }

    static {
        this.\u0275fac = function SnsService_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _SnsService)(\u0275\u0275inject(HttpClient));
        };
    }
    static {
        this.\u0275prov = /* @__PURE__ */ \u0275\u0275defineInjectable({token: _SnsService, factory: _SnsService.\u0275fac});
    }
};

// src/app/modules/sns/message-list/publish-message/publish-message.component.ts
var PublishMessageComponentDialog = class _PublishMessageComponentDialog {
    constructor(dialogRef, data) {
        this.dialogRef = dialogRef;
        this.data = data;
        this.topicArn = "";
        this.topicName = "";
        this.message = "";
        this.topicArn = data.topicArn;
        this.topicName = data.topicArn.substring(this.topicArn.lastIndexOf(":") + 1);
    }

    sendMessage() {
        this.dialogRef.close(this.message);
    }

    close() {
        this.dialogRef.close(false);
    }

    static {
        this.\u0275fac = function PublishMessageComponentDialog_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _PublishMessageComponentDialog)(\u0275\u0275directiveInject(MatDialogRef), \u0275\u0275directiveInject(MAT_DIALOG_DATA));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _PublishMessageComponentDialog,
            selectors: [["sns-publish-message-dialog"]],
            standalone: true,
            features: [\u0275\u0275StandaloneFeature],
            decls: 12,
            vars: 2,
            consts: [["cdkDrag", "", "cdkDragHandle", "", "cdkDragRootElement", ".cdk-overlay-pane", "mat-dialog-title", ""], [1, "mat-typography"], [2, "width", "100%", "height", "100%"], ["cdkAutosizeMinRows", "70", "cdkTextareaAutosize", "", "matInput", "", "placeholder", "Message", 2, "width", "100%", "height", "100%", 3, "ngModelChange", "ngModel"], ["align", "end"], ["mat-button", "", "mat-dialog-close", ""], ["cdkFocusInitial", "", "mat-button", "", 3, "click"]],
            template: function PublishMessageComponentDialog_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "h2", 0);
                    \u0275\u0275text(1);
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(2, "mat-dialog-content", 1)(3, "mat-form-field", 2)(4, "mat-label");
                    \u0275\u0275text(5, "Message:");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(6, "textarea", 3);
                    \u0275\u0275twoWayListener("ngModelChange", function PublishMessageComponentDialog_Template_textarea_ngModelChange_6_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.message, $event) || (ctx.message = $event);
                        return $event;
                    });
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(7, "mat-dialog-actions", 4)(8, "button", 5);
                    \u0275\u0275text(9, "Cancel");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(10, "button", 6);
                    \u0275\u0275listener("click", function PublishMessageComponentDialog_Template_button_click_10_listener() {
                        return ctx.sendMessage();
                    });
                    \u0275\u0275text(11, "Send");
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    \u0275\u0275advance();
                    \u0275\u0275textInterpolate1("Publish SNS Message: ", ctx.topicName, "");
                    \u0275\u0275advance(5);
                    \u0275\u0275twoWayProperty("ngModel", ctx.message);
                }
            },
            dependencies: [
                MatDialogContent,
                MatDialogTitle,
                MatDialogActions,
                MatButton,
                MatDialogClose,
                MatFormField,
                MatLabel,
                FormsModule,
                DefaultValueAccessor,
                NgControlStatus,
                NgModel,
                MatInput,
                ReactiveFormsModule,
                CdkDrag,
                CdkDragHandle,
                CdkTextareaAutosize
            ]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(PublishMessageComponentDialog, {
        className: "PublishMessageComponentDialog",
        filePath: "src/app/modules/sns/message-list/publish-message/publish-message.component.ts",
        lineNumber: 36
    });
})();

// src/app/modules/sns/topic-list/state/sns-topic-list.actions.ts
var snsTopicListActions = {
    initialize: createAction("[sns-topic-list] initialize"),
    // Load topic
    loadTopics: createAction("[sns-topic-list] Load Topics", props()),
    loadTopicsSuccess: createAction("[sns-topic-list] Load Topics Success", props()),
    loadTopicsFailure: createAction("[sns-topic-list] Load Topics Error", props()),
    // Add topic
    addTopic: createAction("[sns-topic-list] Add Topic", props()),
    addTopicSuccess: createAction("[sns-topic-list] Add Topic Success"),
    addTopicFailure: createAction("[sns-topic-list] Add Topic Error", props()),
    // Publish message
    publishMessage: createAction("[sns-topic-list] Publish message", props()),
    publishMessageSuccess: createAction("[sns-topic-list] Publish message success"),
    publishMessageFailure: createAction("[sns-topic-list] Publish message error", props()),
    // Purge topic
    purgeTopic: createAction("[sns-topic-list] Purge Topic", props()),
    purgeTopicSuccess: createAction("[sns-topic-list] Purge Topic Success"),
    purgeTopicFailure: createAction("[sns-topic-list] Purge Topic Error", props()),
    // Delete topic
    deleteTopic: createAction("[sns-topic-list] Delete Topic", props()),
    deleteTopicSuccess: createAction("[sns-topic-list] Delete Topic Success"),
    deleteTopicFailure: createAction("[sns-topic-list] Delete Topic Error", props())
};

// src/app/modules/sns/topic-list/state/sns-topic-list.reducer.ts
var snsTopicListFeatureKey = "sns-topic-list";
var initialState = {
    listTopicResponse: {Total: 0, TopicCounters: []},
    prefix: "",
    pageSize: 10,
    pageIndex: 0,
    loading: false,
    sortColumns: [{column: "attributes.availableMessages", sortDirection: -1}],
    error: {}
};
var snsTopicListReducer = createReducer(
    initialState,
    // Initialize
    on(snsTopicListActions.initialize, (state) => __spreadProps(__spreadValues({}, state), {pageIndex: 0, pageSize: 10, loading: true})),
    // Topic list
    on(snsTopicListActions.loadTopics, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(snsTopicListActions.loadTopicsSuccess, (state, {topics}) => __spreadProps(__spreadValues({}, state), {listTopicResponse: topics, loading: false})),
    on(snsTopicListActions.loadTopicsFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false})),
    // Add topic
    on(snsTopicListActions.addTopic, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(snsTopicListActions.addTopicSuccess, (state) => __spreadProps(__spreadValues({}, state), {loading: false})),
    on(snsTopicListActions.addTopicFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false})),
    // Purge topic
    on(snsTopicListActions.purgeTopic, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(snsTopicListActions.purgeTopicSuccess, (state) => __spreadProps(__spreadValues({}, state), {loading: false})),
    on(snsTopicListActions.purgeTopicFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false})),
    // Publish message
    on(snsTopicListActions.publishMessage, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(snsTopicListActions.publishMessageSuccess, (state) => __spreadProps(__spreadValues({}, state), {loading: false})),
    on(snsTopicListActions.publishMessageFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false})),
    // Delete topic
    on(snsTopicListActions.deleteTopic, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(snsTopicListActions.deleteTopicSuccess, (state) => __spreadProps(__spreadValues({}, state), {loading: false})),
    on(snsTopicListActions.deleteTopicFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false}))
);

// src/app/modules/sns/topic-list/state/sns-topic-list.selectors.ts
var selectQueueListFeature = createFeatureSelector(snsTopicListFeatureKey);
var selectIsLoading = createSelector(selectQueueListFeature, (state) => state.loading);
var selectPrefix = createSelector(selectQueueListFeature, (state) => state?.prefix);
var selectPageSize = createSelector(selectQueueListFeature, (state) => state?.pageSize);
var selectPageIndex = createSelector(selectQueueListFeature, (state) => state?.pageIndex);
var selectSortColumns = createSelector(selectQueueListFeature, (state) => state?.sortColumns);
var selectTopicCounters = createSelector(selectQueueListFeature, (state) => state?.listTopicResponse);
var selectTopicError = createSelector(selectQueueListFeature, (state) => state?.error);

// src/app/modules/sns/topic-list/topic-list.component.ts
var _c0 = () => [];

function SnsTopicListComponent_button_21_Template(rf, ctx) {
    if (rf & 1) {
        const _r1 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "button", 13);
        \u0275\u0275listener("click", function SnsTopicListComponent_button_21_Template_button_click_0_listener() {
            \u0275\u0275restoreView(_r1);
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.setPrefix());
        });
        \u0275\u0275elementStart(1, "mat-icon", 14);
        \u0275\u0275text(2, "search");
        \u0275\u0275elementEnd()();
    }
}

function SnsTopicListComponent_button_22_Template(rf, ctx) {
    if (rf & 1) {
        const _r3 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "button", 13);
        \u0275\u0275listener("click", function SnsTopicListComponent_button_22_Template_button_click_0_listener() {
            \u0275\u0275restoreView(_r3);
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.unsetPrefix());
        });
        \u0275\u0275elementStart(1, "mat-icon", 14);
        \u0275\u0275text(2, "close");
        \u0275\u0275elementEnd()();
    }
}

function SnsTopicListComponent_div_24_th_3_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 32);
        \u0275\u0275text(1, "Name");
        \u0275\u0275elementEnd();
    }
}

function SnsTopicListComponent_div_24_td_4_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 33)(1, "mat-nav-list")(2, "a", 34);
        \u0275\u0275text(3);
        \u0275\u0275elementEnd()()();
    }
    if (rf & 2) {
        const element_r5 = ctx.$implicit;
        \u0275\u0275advance(2);
        \u0275\u0275propertyInterpolate1("routerLink", "./messages/", element_r5.topicArn, "");
        \u0275\u0275advance();
        \u0275\u0275textInterpolate(element_r5.topicName);
    }
}

function SnsTopicListComponent_div_24_th_6_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 35);
        \u0275\u0275text(1, " Available ");
        \u0275\u0275elementEnd();
    }
}

function SnsTopicListComponent_div_24_td_7_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 33);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r6 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r6.availableMessages, " ");
    }
}

function SnsTopicListComponent_div_24_th_9_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 36);
        \u0275\u0275text(1, " Size ");
        \u0275\u0275elementEnd();
    }
}

function SnsTopicListComponent_div_24_td_10_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 33);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r7 = ctx.$implicit;
        const ctx_r1 = \u0275\u0275nextContext(2);
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", ctx_r1.byteConversion(element_r7.size), " ");
    }
}

function SnsTopicListComponent_div_24_th_12_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 37);
        \u0275\u0275text(1, " Created ");
        \u0275\u0275elementEnd();
    }
}

function SnsTopicListComponent_div_24_td_13_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 33);
        \u0275\u0275text(1);
        \u0275\u0275pipe(2, "date");
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r8 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", \u0275\u0275pipeBind2(2, 1, element_r8.created, "dd-MM-yyyy HH:mm:ss"), " ");
    }
}

function SnsTopicListComponent_div_24_th_15_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 32);
        \u0275\u0275text(1, "Modified");
        \u0275\u0275elementEnd();
    }
}

function SnsTopicListComponent_div_24_td_16_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 33);
        \u0275\u0275text(1);
        \u0275\u0275pipe(2, "date");
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r9 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", \u0275\u0275pipeBind2(2, 1, element_r9.modified, "dd-MM-yyyy HH:mm:ss"), " ");
    }
}

function SnsTopicListComponent_div_24_th_18_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 38);
        \u0275\u0275text(1, "Actions");
        \u0275\u0275elementEnd();
    }
}

function SnsTopicListComponent_div_24_td_19_Template(rf, ctx) {
    if (rf & 1) {
        const _r10 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "td", 33)(1, "button", 39);
        \u0275\u0275listener("click", function SnsTopicListComponent_div_24_td_19_Template_button_click_1_listener() {
            const row_r11 = \u0275\u0275restoreView(_r10).$implicit;
            const ctx_r1 = \u0275\u0275nextContext(2);
            return \u0275\u0275resetView(ctx_r1.publishMessage(row_r11.topicArn));
        });
        \u0275\u0275elementStart(2, "mat-icon");
        \u0275\u0275text(3, "send");
        \u0275\u0275elementEnd()();
        \u0275\u0275elementStart(4, "button", 40)(5, "mat-icon");
        \u0275\u0275text(6, "edit");
        \u0275\u0275elementEnd()();
        \u0275\u0275elementStart(7, "button", 41);
        \u0275\u0275listener("click", function SnsTopicListComponent_div_24_td_19_Template_button_click_7_listener() {
            const row_r11 = \u0275\u0275restoreView(_r10).$implicit;
            const ctx_r1 = \u0275\u0275nextContext(2);
            return \u0275\u0275resetView(ctx_r1.purgeTopic(row_r11.topicArn));
        });
        \u0275\u0275elementStart(8, "mat-icon");
        \u0275\u0275text(9, "clear_all");
        \u0275\u0275elementEnd()();
        \u0275\u0275elementStart(10, "button", 42);
        \u0275\u0275listener("click", function SnsTopicListComponent_div_24_td_19_Template_button_click_10_listener() {
            const row_r11 = \u0275\u0275restoreView(_r10).$implicit;
            const ctx_r1 = \u0275\u0275nextContext(2);
            return \u0275\u0275resetView(ctx_r1.deleteTopic(row_r11.topicArn));
        });
        \u0275\u0275elementStart(11, "mat-icon");
        \u0275\u0275text(12, "delete");
        \u0275\u0275elementEnd()()();
    }
    if (rf & 2) {
        const row_r11 = ctx.$implicit;
        \u0275\u0275advance(4);
        \u0275\u0275propertyInterpolate1("routerLink", "./details/", row_r11.topicArn, "");
    }
}

function SnsTopicListComponent_div_24_tr_20_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 43);
    }
}

function SnsTopicListComponent_div_24_tr_21_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 44);
    }
}

function SnsTopicListComponent_div_24_tr_22_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "tr", 45)(1, "td", 46);
        \u0275\u0275text(2, " No data matching the filter. ");
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const ctx_r1 = \u0275\u0275nextContext(2);
        \u0275\u0275advance();
        \u0275\u0275attribute("colspan", ctx_r1.columns.length);
    }
}

function SnsTopicListComponent_div_24_Template(rf, ctx) {
    if (rf & 1) {
        const _r4 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "div", 15)(1, "table", 16);
        \u0275\u0275listener("matSortChange", function SnsTopicListComponent_div_24_Template_table_matSortChange_1_listener($event) {
            \u0275\u0275restoreView(_r4);
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.sortChange($event));
        });
        \u0275\u0275elementContainerStart(2, 17);
        \u0275\u0275template(3, SnsTopicListComponent_div_24_th_3_Template, 2, 0, "th", 18)(4, SnsTopicListComponent_div_24_td_4_Template, 4, 3, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(5, 20);
        \u0275\u0275template(6, SnsTopicListComponent_div_24_th_6_Template, 2, 0, "th", 21)(7, SnsTopicListComponent_div_24_td_7_Template, 2, 1, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(8, 22);
        \u0275\u0275template(9, SnsTopicListComponent_div_24_th_9_Template, 2, 0, "th", 23)(10, SnsTopicListComponent_div_24_td_10_Template, 2, 1, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(11, 24);
        \u0275\u0275template(12, SnsTopicListComponent_div_24_th_12_Template, 2, 0, "th", 25)(13, SnsTopicListComponent_div_24_td_13_Template, 3, 4, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(14, 26);
        \u0275\u0275template(15, SnsTopicListComponent_div_24_th_15_Template, 2, 0, "th", 18)(16, SnsTopicListComponent_div_24_td_16_Template, 3, 4, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(17, 27);
        \u0275\u0275template(18, SnsTopicListComponent_div_24_th_18_Template, 2, 0, "th", 28)(19, SnsTopicListComponent_div_24_td_19_Template, 13, 2, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275template(20, SnsTopicListComponent_div_24_tr_20_Template, 1, 0, "tr", 29)(21, SnsTopicListComponent_div_24_tr_21_Template, 1, 0, "tr", 30)(22, SnsTopicListComponent_div_24_tr_22_Template, 3, 1, "tr", 31);
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const topicCounters_r12 = ctx.ngIf;
        const ctx_r1 = \u0275\u0275nextContext();
        \u0275\u0275advance();
        \u0275\u0275property("dataSource", topicCounters_r12.TopicCounters);
        \u0275\u0275advance(19);
        \u0275\u0275property("matHeaderRowDef", ctx_r1.columns);
        \u0275\u0275advance();
        \u0275\u0275property("matRowDefColumns", ctx_r1.columns);
    }
}

var SnsTopicListComponent = class _SnsTopicListComponent {
    constructor(snackBar, dialog, location, state, store, actionsSubj$) {
        this.snackBar = snackBar;
        this.dialog = dialog;
        this.location = location;
        this.state = state;
        this.store = store;
        this.actionsSubj$ = actionsSubj$;
        this.lastUpdate = /* @__PURE__ */ new Date();
        this.pageSize$ = this.store.select(selectPageSize);
        this.pageIndex$ = this.store.select(selectPageIndex);
        this.listTopicCountersResponse$ = this.store.select(selectTopicCounters);
        this.columns = ["topicName", "availableMessages", "size", "created", "modified", "actions"];
        this.pageSizeOptions = [5, 10, 20, 50, 100];
        this.hidePageSize = false;
        this.showPageSizeOptions = true;
        this.showFirstLastButtons = true;
        this.disabled = false;
        this.prefixSet = false;
        this.prefix = "";
        this.sortColumns = [{column: "name", sortDirection: -1}];
        this.byteConversion = byteConversion;
        this.actionsSubj$.pipe(filter((action) => action.type === snsTopicListActions.addTopicSuccess.type || action.type === snsTopicListActions.publishMessageSuccess.type || action.type === snsTopicListActions.purgeTopicSuccess.type || action.type === snsTopicListActions.deleteTopicSuccess.type)).subscribe(() => {
            this.lastUpdate = /* @__PURE__ */ new Date();
            this.loadTopics();
        });
    }

    ngOnInit() {
        this.loadTopics();
        this.updateSubscription = interval(6e4).subscribe(() => this.loadTopics());
    }

    ngOnDestroy() {
        this.updateSubscription?.unsubscribe();
    }

    back() {
        this.location.back();
    }

    refresh() {
        this.loadTopics();
    }

    setPrefix() {
        this.prefixSet = true;
        this.state.value["sns-topic-list"].pageIndex = 0;
        this.state.value["sns-topic-list"].prefix = this.prefix;
        this.loadTopics();
    }

    unsetPrefix() {
        this.prefix = "";
        this.prefixSet = false;
        this.state.value["sns-topic-list"].prefix = "";
        this.loadTopics();
    }

    handlePageEvent(e2) {
        this.state.value["sns-topic-list"].pageSize = e2.pageSize;
        this.state.value["sns-topic-list"].pageIndex = e2.pageIndex;
        this.loadTopics();
    }

    sortChange(sortState) {
        this.state.value["sns-topic-list"].sortColumns = [];
        let direction;
        let column = "topicName";
        if (sortState.active === "availableMessages") {
            column = "attributes.availableMessages";
        }
        if (sortState.direction === "asc") {
            direction = 1;
        } else {
            direction = -1;
        }
        this.state.value["sns-topic-list"].sortColumns = [{column, sortDirection: direction}];
        this.loadTopics();
    }

    loadTopics() {
        this.store.dispatch(snsTopicListActions.loadTopics({
            prefix: this.state.value["sns-topic-list"].prefix,
            pageSize: this.state.value["sns-topic-list"].pageSize,
            pageIndex: this.state.value["sns-topic-list"].pageIndex,
            sortColumns: this.state.value["sns-topic-list"].sortColumns
        }));
    }

    addTopic() {
        const dialogConfig = new MatDialogConfig();
        dialogConfig.disableClose = true;
        dialogConfig.autoFocus = true;
        this.dialog.open(TopicAddComponentDialog, dialogConfig).afterClosed().subscribe((result) => {
            if (result) {
                this.store.dispatch(snsTopicListActions.addTopic({name: result}));
            }
        });
    }

    publishMessage(topicArn) {
        const dialogConfig = new MatDialogConfig();
        dialogConfig.disableClose = true;
        dialogConfig.autoFocus = true;
        dialogConfig.data = {topicArn};
        dialogConfig.maxWidth = "100vw";
        dialogConfig.maxHeight = "100vh";
        dialogConfig.panelClass = "full-screen-modal";
        dialogConfig.width = "90%";
        this.dialog.open(PublishMessageComponentDialog, dialogConfig).afterClosed().subscribe((result) => {
            if (result) {
                this.store.dispatch(snsTopicListActions.publishMessage({topicArn, message: result}));
            }
        });
    }

    purgeTopic(topicArn) {
        this.store.dispatch(snsTopicListActions.purgeTopic({topicArn}));
    }

    deleteTopic(topicArn) {
        this.store.dispatch(snsTopicListActions.deleteTopic({topicArn}));
    }

    static {
        this.\u0275fac = function SnsTopicListComponent_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _SnsTopicListComponent)(\u0275\u0275directiveInject(MatSnackBar), \u0275\u0275directiveInject(MatDialog), \u0275\u0275directiveInject(Location), \u0275\u0275directiveInject(State), \u0275\u0275directiveInject(Store), \u0275\u0275directiveInject(ActionsSubject));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _SnsTopicListComponent,
            selectors: [["app-home"]],
            features: [\u0275\u0275ProvidersFeature([SnsService])],
            decls: 33,
            vars: 24,
            consts: [["appearance", "outlined", 2, "margin", "3px"], ["aria-label", "Back", "mat-icon-button", "", 1, "head-buttons-left", 3, "click"], [1, "fill-remaining-space"], ["aria-label", "Refresh", "mat-icon-button", "", 3, "click"], ["appearance", "outlined", 2, "margin", "-10px"], ["align", "start"], [2, "width", "100%"], ["matInput", "", "name", "search", "placeholder", "Search", "type", "text", 3, "ngModelChange", "ngModel"], ["mat-icon-button", "", "matSuffix", "", "style", "float: right", 3, "click", 4, "ngIf"], [1, "table-container"], ["class", "row", 4, "ngIf"], ["aria-label", "Select page", 2, "width", "99%", "margin-left", "15px", 3, "page", "disabled", "hidePageSize", "length", "pageIndex", "pageSizeOptions", "pageSize", "showFirstLastButtons"], [1, "footer"], ["mat-icon-button", "", "matSuffix", "", 2, "float", "right", 3, "click"], ["matSuffix", ""], [1, "row"], ["mat-table", "", "matSort", "", 1, "mat-elevation-z8", "queue-table", 3, "matSortChange", "dataSource"], ["matColumnDef", "topicName"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Topic name", "sortActionDescription", "Sort by queueUrl", 4, "matHeaderCellDef"], ["mat-cell", "", 4, "matCellDef"], ["matColumnDef", "availableMessages"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Available messages in topic", "sortActionDescription", "Sort by created", 4, "matHeaderCellDef"], ["matColumnDef", "size"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "SIze of all messages in bytes", "sortActionDescription", "Sort by size", 4, "matHeaderCellDef"], ["matColumnDef", "created"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Topic creation timestamp", "sortActionDescription", "Sort by created", 4, "matHeaderCellDef"], ["matColumnDef", "modified"], ["matColumnDef", "actions"], ["mat-header-cell", "", "style", "width:200px", 4, "matHeaderCellDef"], ["mat-header-row", "", 4, "matHeaderRowDef"], ["mat-row", "", 4, "matRowDef", "matRowDefColumns"], ["class", "mat-row", 4, "matNoDataRow"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Topic name", "sortActionDescription", "Sort by queueUrl"], ["mat-cell", ""], ["mat-list-item", "", 3, "routerLink"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Available messages in topic", "sortActionDescription", "Sort by created"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "SIze of all messages in bytes", "sortActionDescription", "Sort by size"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Topic creation timestamp", "sortActionDescription", "Sort by created"], ["mat-header-cell", "", 2, "width", "200px"], ["aria-label", "Send", "mat-icon-button", "", "matTooltip", "Send a message", 3, "click"], ["aria-label", "Details", "mat-icon-button", "", "matTooltip", "Edit topic", 3, "routerLink"], ["aria-label", "Purge", "mat-icon-button", "", "matTooltip", "Purge the topic", 3, "click"], ["aria-label", "Delete", "mat-icon-button", "", "matTooltip", "Delete the topic", 3, "click"], ["mat-header-row", ""], ["mat-row", ""], [1, "mat-row"], [1, "mat-cell", 2, "padding-left", "20px", "padding-top", "10px"]],
            template: function SnsTopicListComponent_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "mat-card", 0)(1, "mat-card-header")(2, "button", 1);
                    \u0275\u0275listener("click", function SnsTopicListComponent_Template_button_click_2_listener() {
                        return ctx.back();
                    });
                    \u0275\u0275elementStart(3, "mat-icon");
                    \u0275\u0275text(4, "arrow_back");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(5, "span", 2)(6, "h4");
                    \u0275\u0275text(7, "SNS Topics");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(8, "button", 3);
                    \u0275\u0275listener("click", function SnsTopicListComponent_Template_button_click_8_listener() {
                        return ctx.addTopic();
                    });
                    \u0275\u0275elementStart(9, "mat-icon");
                    \u0275\u0275text(10, "add");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(11, "button", 3);
                    \u0275\u0275listener("click", function SnsTopicListComponent_Template_button_click_11_listener() {
                        return ctx.refresh();
                    });
                    \u0275\u0275elementStart(12, "mat-icon");
                    \u0275\u0275text(13, "refresh");
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(14, "mat-card-content")(15, "mat-card", 4)(16, "mat-card-actions", 5)(17, "mat-form-field", 6)(18, "mat-label");
                    \u0275\u0275text(19, "Prefix");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(20, "input", 7);
                    \u0275\u0275twoWayListener("ngModelChange", function SnsTopicListComponent_Template_input_ngModelChange_20_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.prefix, $event) || (ctx.prefix = $event);
                        return $event;
                    });
                    \u0275\u0275elementEnd();
                    \u0275\u0275template(21, SnsTopicListComponent_button_21_Template, 3, 0, "button", 8)(22, SnsTopicListComponent_button_22_Template, 3, 0, "button", 8);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(23, "div", 9);
                    \u0275\u0275template(24, SnsTopicListComponent_div_24_Template, 23, 3, "div", 10);
                    \u0275\u0275pipe(25, "async");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(26, "mat-paginator", 11);
                    \u0275\u0275pipe(27, "async");
                    \u0275\u0275pipe(28, "async");
                    \u0275\u0275pipe(29, "async");
                    \u0275\u0275listener("page", function SnsTopicListComponent_Template_mat_paginator_page_26_listener($event) {
                        return ctx.handlePageEvent($event);
                    });
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(30, "div", 12);
                    \u0275\u0275text(31);
                    \u0275\u0275pipe(32, "date");
                    \u0275\u0275elementEnd()()();
                }
                if (rf & 2) {
                    let tmp_6_0;
                    \u0275\u0275advance(20);
                    \u0275\u0275twoWayProperty("ngModel", ctx.prefix);
                    \u0275\u0275advance();
                    \u0275\u0275property("ngIf", !ctx.prefixSet);
                    \u0275\u0275advance();
                    \u0275\u0275property("ngIf", ctx.prefixSet);
                    \u0275\u0275advance(2);
                    \u0275\u0275property("ngIf", \u0275\u0275pipeBind1(25, 12, ctx.listTopicCountersResponse$));
                    \u0275\u0275advance(2);
                    \u0275\u0275property("disabled", ctx.disabled)("hidePageSize", ctx.hidePageSize)("length", (tmp_6_0 = \u0275\u0275pipeBind1(27, 14, ctx.listTopicCountersResponse$)) == null ? null : tmp_6_0.Total)("pageIndex", \u0275\u0275pipeBind1(28, 16, ctx.pageIndex$))("pageSizeOptions", ctx.showPageSizeOptions ? ctx.pageSizeOptions : \u0275\u0275pureFunction0(23, _c0))("pageSize", \u0275\u0275pipeBind1(29, 18, ctx.pageSize$))("showFirstLastButtons", ctx.showFirstLastButtons);
                    \u0275\u0275advance(5);
                    \u0275\u0275textInterpolate1(" Last update: ", \u0275\u0275pipeBind2(32, 20, ctx.lastUpdate, "HH:mm:ss"), " ");
                }
            },
            dependencies: [MatCard, MatCardHeader, MatCardContent, MatCardActions, MatTable, MatHeaderCellDef, MatCellDef, MatColumnDef, MatIcon, MatHeaderCell, MatCell, MatHeaderRowDef, MatHeaderRow, MatSortHeader, MatRowDef, MatNoDataRow, MatIconButton, MatRow, MatPaginator, MatSort, MatTooltip, RouterLink, MatListItem, MatNavList, MatFormField, MatInput, MatLabel, MatSuffix, NgIf, DefaultValueAccessor, NgControlStatus, NgModel, DatePipe, AsyncPipe],
            styles: ['\n\n.head-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  justify-content: flex-end;\n}\n.footer-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  width: 50%;\n  justify-content: flex-end;\n}\n.fill-remaining-space[_ngcontent-%COMP%] {\n  flex: 1 1 auto;\n}\n.table-container[_ngcontent-%COMP%] {\n  max-height: calc(100vh - 10px);\n  overflow: auto;\n}\n.full-screen-modal[_ngcontent-%COMP%]   .mat-dialog-container[_ngcontent-%COMP%] {\n  padding: 1em;\n  width: 90%;\n  height: 80%;\n  overflow-y: scroll;\n}\n.cdk-global-overlay-wrapper[_ngcontent-%COMP%] {\n  pointer-events: auto;\n  display: block;\n  position: relative;\n  overflow: auto;\n  text-align: center;\n}\n.cdk-global-overlay-wrapper[_ngcontent-%COMP%]::before {\n  content: "";\n  display: inline-block;\n  height: 100%;\n  white-space: nowrap;\n}\n.cdk-overlay-pane[_ngcontent-%COMP%] {\n  display: inline-block;\n  position: relative;\n  text-align: left;\n  white-space: normal;\n}\n.footer[_ngcontent-%COMP%] {\n  display: flex;\n  width: 50%;\n  font-size: x-small;\n  color: black;\n  padding-top: 15px;\n}\n/*# sourceMappingURL=topic-list.component.css.map */']
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(SnsTopicListComponent, {
        className: "SnsTopicListComponent",
        filePath: "src/app/modules/sns/topic-list/topic-list.component.ts",
        lineNumber: 25
    });
})();

// src/app/modules/sns/topic-detail/subscription-add/subscription-add.component.ts
function SubscriptionAddComponentDialog_For_12_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "mat-option", 5);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const protocol_r1 = ctx.$implicit;
        \u0275\u0275property("value", protocol_r1);
        \u0275\u0275advance();
        \u0275\u0275textInterpolate(protocol_r1);
    }
}

function SubscriptionAddComponentDialog_mat_form_field_13_For_5_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "mat-option", 5);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const arn_r4 = ctx.$implicit;
        \u0275\u0275property("value", arn_r4);
        \u0275\u0275advance();
        \u0275\u0275textInterpolate(arn_r4);
    }
}

function SubscriptionAddComponentDialog_mat_form_field_13_Template(rf, ctx) {
    if (rf & 1) {
        const _r2 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "mat-form-field", 2)(1, "mat-label");
        \u0275\u0275text(2, "Endpoint");
        \u0275\u0275elementEnd();
        \u0275\u0275elementStart(3, "mat-select", 10);
        \u0275\u0275twoWayListener("ngModelChange", function SubscriptionAddComponentDialog_mat_form_field_13_Template_mat_select_ngModelChange_3_listener($event) {
            \u0275\u0275restoreView(_r2);
            const ctx_r2 = \u0275\u0275nextContext();
            \u0275\u0275twoWayBindingSet(ctx_r2.endpoint, $event) || (ctx_r2.endpoint = $event);
            return \u0275\u0275resetView($event);
        });
        \u0275\u0275repeaterCreate(4, SubscriptionAddComponentDialog_mat_form_field_13_For_5_Template, 2, 2, "mat-option", 5, \u0275\u0275repeaterTrackByIndex);
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const ctx_r2 = \u0275\u0275nextContext();
        \u0275\u0275advance(3);
        \u0275\u0275twoWayProperty("ngModel", ctx_r2.endpoint);
        \u0275\u0275advance();
        \u0275\u0275repeater(ctx_r2.queueArnData);
    }
}

function SubscriptionAddComponentDialog_mat_form_field_14_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "mat-form-field", 2)(1, "mat-label");
        \u0275\u0275text(2, "Not supported yet");
        \u0275\u0275elementEnd();
        \u0275\u0275element(3, "input", 11);
        \u0275\u0275elementEnd();
    }
}

var Protocols = [
    "http",
    "https",
    "email",
    "email-json",
    "sms",
    "sqs",
    "application",
    "lambda",
    "firehose"
];
var SubscriptionAddComponentDialog = class _SubscriptionAddComponentDialog {
    constructor(sqsService, fb, dialogRef, data) {
        this.sqsService = sqsService;
        this.fb = fb;
        this.dialogRef = dialogRef;
        this.data = data;
        this.topicArn = "";
        this.topicName = "";
        this.endpoint = "";
        this.protocol = "sqs";
        this.queueArnData = [];
        this.Protocols = Protocols;
        this.topicArn = data.topicArn;
        this.topicName = data.topicName;
    }

    ngOnInit() {
        this.form = this.fb.group({
            topicArn: [""],
            endpoint: [""],
            protocol: [""]
        });
        this.loadQueueArns();
    }

    protocolSelectionChanged() {
        this.queueArnData = [];
        if (this.protocol == "sqs") {
            this.loadQueueArns();
        }
    }

    loadQueueArns() {
        this.sqsService.listQueueArns().subscribe((data) => {
            this.queueArnData = data.QueueArns;
        });
    }

    save() {
        this.dialogRef.close({topicArn: this.topicArn, endpoint: this.endpoint, protocol: this.protocol});
    }

    close() {
        this.dialogRef.close(false);
    }

    static {
        this.\u0275fac = function SubscriptionAddComponentDialog_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _SubscriptionAddComponentDialog)(\u0275\u0275directiveInject(SqsService), \u0275\u0275directiveInject(FormBuilder), \u0275\u0275directiveInject(MatDialogRef), \u0275\u0275directiveInject(MAT_DIALOG_DATA));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _SubscriptionAddComponentDialog,
            selectors: [["subscription-add-dialog"]],
            standalone: true,
            features: [\u0275\u0275ProvidersFeature([SqsService]), \u0275\u0275StandaloneFeature],
            decls: 20,
            vars: 4,
            consts: [["mat-dialog-title", ""], [1, "mat-typography", 2, "width", "500px"], [2, "width", "100%"], ["matInput", "", "readonly", "", "value", "", 3, "ngModelChange", "ngModel"], [2, "width", "100%", 3, "selectionChange", "ngModelChange", "ngModel"], [3, "value"], ["style", "width: 100%", 4, "ngIf"], ["align", "end"], ["mat-button", "", "mat-dialog-close", ""], ["cdkFocusInitial", "", "mat-button", "", 3, "click"], [2, "width", "100%", 3, "ngModelChange", "ngModel"], ["matInput", "", "readonly", "", "value", ""]],
            template: function SubscriptionAddComponentDialog_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "h2", 0);
                    \u0275\u0275text(1, "Add Topic Subscription");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(2, "mat-dialog-content", 1)(3, "mat-form-field", 2)(4, "mat-label");
                    \u0275\u0275text(5, "Topic ARN");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(6, "input", 3);
                    \u0275\u0275twoWayListener("ngModelChange", function SubscriptionAddComponentDialog_Template_input_ngModelChange_6_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.topicArn, $event) || (ctx.topicArn = $event);
                        return $event;
                    });
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(7, "mat-form-field", 2)(8, "mat-label");
                    \u0275\u0275text(9, "Protocol");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(10, "mat-select", 4);
                    \u0275\u0275listener("selectionChange", function SubscriptionAddComponentDialog_Template_mat_select_selectionChange_10_listener() {
                        return ctx.protocolSelectionChanged();
                    });
                    \u0275\u0275twoWayListener("ngModelChange", function SubscriptionAddComponentDialog_Template_mat_select_ngModelChange_10_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.protocol, $event) || (ctx.protocol = $event);
                        return $event;
                    });
                    \u0275\u0275repeaterCreate(11, SubscriptionAddComponentDialog_For_12_Template, 2, 2, "mat-option", 5, \u0275\u0275repeaterTrackByIdentity);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275template(13, SubscriptionAddComponentDialog_mat_form_field_13_Template, 6, 1, "mat-form-field", 6)(14, SubscriptionAddComponentDialog_mat_form_field_14_Template, 4, 0, "mat-form-field", 6);
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(15, "mat-dialog-actions", 7)(16, "button", 8);
                    \u0275\u0275text(17, "Cancel");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(18, "button", 9);
                    \u0275\u0275listener("click", function SubscriptionAddComponentDialog_Template_button_click_18_listener() {
                        return ctx.save();
                    });
                    \u0275\u0275text(19, "Add");
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    \u0275\u0275advance(6);
                    \u0275\u0275twoWayProperty("ngModel", ctx.topicArn);
                    \u0275\u0275advance(4);
                    \u0275\u0275twoWayProperty("ngModel", ctx.protocol);
                    \u0275\u0275advance();
                    \u0275\u0275repeater(ctx.Protocols);
                    \u0275\u0275advance(2);
                    \u0275\u0275property("ngIf", ctx.protocol == "sqs");
                    \u0275\u0275advance();
                    \u0275\u0275property("ngIf", ctx.protocol != "sqs");
                }
            },
            dependencies: [
                MatDialogContent,
                MatDialogTitle,
                MatDialogActions,
                MatButton,
                MatDialogClose,
                MatFormField,
                MatSelect,
                MatOption,
                MatLabel,
                FormsModule,
                DefaultValueAccessor,
                NgControlStatus,
                NgModel,
                MatInput,
                ReactiveFormsModule,
                NgIf
            ]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(SubscriptionAddComponentDialog, {
        className: "SubscriptionAddComponentDialog",
        filePath: "src/app/modules/sns/topic-detail/subscription-add/subscription-add.component.ts",
        lineNumber: 47
    });
})();

// src/app/modules/sns/topic-detail/state/sns-topic-detail.actions.ts
var snsTopicDetailsActions = {
    initialize: createAction("[sns-topic-details] initialize"),
    // Load details
    loadDetails: createAction("[sns-topic-details] Load topics details", props()),
    loadDetailsSuccess: createAction("[sns-topic-details] Load topics details success", props()),
    loadDetailsFailure: createAction("[sns-topic-details] Load topics details error", props()),
    // Load attributes
    loadAttributes: createAction("[sns-topic-details] Load topics attributes", props()),
    loadAttributesSuccess: createAction("[sns-topic-details] Load topics attributes success", props()),
    loadAttributesFailure: createAction("[sns-topic-details] Load topics attributes error", props()),
    // Load subscriptions
    loadSubscriptions: createAction("[sns-topic-details] Load topics subscriptions", props()),
    loadSubscriptionsSuccess: createAction("[sns-topic-details] Load topics subscriptions success", props()),
    loadSubscriptionsFailure: createAction("[sns-topic-details] Load topics subscriptions error", props()),
    // Load tags
    loadTags: createAction("[sns-topic-details] Load topics tags", props()),
    loadTagsSuccess: createAction("[sns-topic-details] Load topics tags success", props()),
    loadTagsFailure: createAction("[sns-topic-details] Load topics tags error", props())
};

// src/app/modules/sns/topic-detail/state/sns-topic-detail.reducer.ts
var snsTopicDetailsFeatureKey = "sns-topic-details";
var initialState2 = {
    snsTopicDetails: {},
    snsTopicSubscriptions: {},
    subscriptionPageSize: 10,
    subscriptionPageIndex: 0,
    subscriptionSortColumns: [{column: "endpoint", sortDirection: -1}],
    loading: false,
    error: {}
};
var snsTopicDetailReducer = createReducer(
    initialState2,
    // Initialize
    on(snsTopicDetailsActions.initialize, (state) => __spreadProps(__spreadValues({}, state), {loading: false})),
    // Topic details
    on(snsTopicDetailsActions.loadDetails, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(snsTopicDetailsActions.loadDetailsSuccess, (state, {topicDetails}) => __spreadProps(__spreadValues({}, state), {snsTopicDetails: topicDetails, loading: false})),
    on(snsTopicDetailsActions.loadDetailsFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false})),
    // Topic subscriptions
    on(snsTopicDetailsActions.loadSubscriptions, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(snsTopicDetailsActions.loadSubscriptionsSuccess, (state, {subscriptions}) => __spreadProps(__spreadValues({}, state), {
        snsTopicSubscriptions: subscriptions,
        loading: false
    })),
    on(snsTopicDetailsActions.loadSubscriptionsFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false}))
);

// src/app/modules/sns/topic-detail/state/sns-topic-detail.selectors.ts
var selectTopicDetailsFeature = createFeatureSelector(snsTopicDetailsFeatureKey);
var selectDetails = createSelector(selectTopicDetailsFeature, (state) => state?.snsTopicDetails);
var selectSubscriptions = createSelector(selectTopicDetailsFeature, (state) => state?.snsTopicSubscriptions);
var selectSubscriptionPageSize = createSelector(selectTopicDetailsFeature, (state) => state?.subscriptionPageSize);
var selectSubscriptionPageIndex = createSelector(selectTopicDetailsFeature, (state) => state?.subscriptionPageIndex);
var selectError = createSelector(selectTopicDetailsFeature, (state) => state?.error);

// src/app/modules/sns/topic-detail/topic-detail.component.ts
function SnsTopicDetailComponent_div_15_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "div")(1, "mat-card-content")(2, "mat-grid-list", 16)(3, "mat-grid-tile", 17)(4, "mat-list")(5, "mat-list-item", 18)(6, "p", 19);
        \u0275\u0275text(7, "Topic Name: ");
        \u0275\u0275elementEnd();
        \u0275\u0275elementStart(8, "p", 20);
        \u0275\u0275text(9);
        \u0275\u0275elementEnd()();
        \u0275\u0275elementStart(10, "mat-list-item", 18)(11, "p", 19);
        \u0275\u0275text(12, "ARN: ");
        \u0275\u0275elementEnd();
        \u0275\u0275elementStart(13, "p", 20);
        \u0275\u0275text(14);
        \u0275\u0275elementEnd()();
        \u0275\u0275elementStart(15, "mat-list-item", 18)(16, "p", 19);
        \u0275\u0275text(17, "URL: ");
        \u0275\u0275elementEnd();
        \u0275\u0275elementStart(18, "p", 20);
        \u0275\u0275text(19);
        \u0275\u0275elementEnd()()()();
        \u0275\u0275elementStart(20, "mat-grid-tile", 17)(21, "div", 21)(22, "mat-list")(23, "mat-list-item", 18)(24, "p", 19);
        \u0275\u0275text(25, "Owner: ");
        \u0275\u0275elementEnd();
        \u0275\u0275elementStart(26, "p", 20);
        \u0275\u0275text(27);
        \u0275\u0275elementEnd()();
        \u0275\u0275elementStart(28, "mat-list-item", 18)(29, "p", 19);
        \u0275\u0275text(30, "Messages: ");
        \u0275\u0275elementEnd();
        \u0275\u0275elementStart(31, "p", 20);
        \u0275\u0275text(32);
        \u0275\u0275elementEnd()();
        \u0275\u0275elementStart(33, "mat-list-item", 18)(34, "p", 19);
        \u0275\u0275text(35, "Size (kB): ");
        \u0275\u0275elementEnd();
        \u0275\u0275elementStart(36, "p", 20);
        \u0275\u0275text(37);
        \u0275\u0275elementEnd()()()()();
        \u0275\u0275elementStart(38, "mat-grid-tile", 17)(39, "div", 21)(40, "mat-list")(41, "mat-list-item", 18)(42, "p", 19);
        \u0275\u0275text(43, "Created: ");
        \u0275\u0275elementEnd();
        \u0275\u0275elementStart(44, "p", 20);
        \u0275\u0275text(45);
        \u0275\u0275pipe(46, "date");
        \u0275\u0275elementEnd()();
        \u0275\u0275elementStart(47, "mat-list-item", 18)(48, "p", 19);
        \u0275\u0275text(49, "Modified: ");
        \u0275\u0275elementEnd();
        \u0275\u0275elementStart(50, "p", 20);
        \u0275\u0275text(51);
        \u0275\u0275pipe(52, "date");
        \u0275\u0275elementEnd()();
        \u0275\u0275element(53, "mat-list-item", 18);
        \u0275\u0275elementEnd()()()()()();
    }
    if (rf & 2) {
        const topicDetails_r1 = ctx.ngIf;
        \u0275\u0275advance(3);
        \u0275\u0275property("colspan", 2)("rowspan", 1);
        \u0275\u0275advance(6);
        \u0275\u0275textInterpolate(topicDetails_r1.topicName);
        \u0275\u0275advance(5);
        \u0275\u0275textInterpolate(topicDetails_r1.topicArn);
        \u0275\u0275advance(5);
        \u0275\u0275textInterpolate(topicDetails_r1.topicUrl);
        \u0275\u0275advance();
        \u0275\u0275property("colspan", 1)("rowspan", 1);
        \u0275\u0275advance(7);
        \u0275\u0275textInterpolate(topicDetails_r1.owner);
        \u0275\u0275advance(5);
        \u0275\u0275textInterpolate(topicDetails_r1.messageCount);
        \u0275\u0275advance(5);
        \u0275\u0275textInterpolate(topicDetails_r1.size);
        \u0275\u0275advance();
        \u0275\u0275property("colspan", 1)("rowspan", 1);
        \u0275\u0275advance(7);
        \u0275\u0275textInterpolate(\u0275\u0275pipeBind2(46, 14, topicDetails_r1.created, "yyyy-MM-dd HH:mm:ss"));
        \u0275\u0275advance(6);
        \u0275\u0275textInterpolate(\u0275\u0275pipeBind2(52, 17, topicDetails_r1.modified, "yyyy-MM-dd HH:mm:ss"));
    }
}

function SnsTopicDetailComponent_div_31_th_3_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 38);
        \u0275\u0275text(1, "ID");
        \u0275\u0275elementEnd();
    }
}

function SnsTopicDetailComponent_div_31_td_4_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 39);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r4 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r4.id, "");
    }
}

function SnsTopicDetailComponent_div_31_th_6_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 40);
        \u0275\u0275text(1, "Endpoint");
        \u0275\u0275elementEnd();
    }
}

function SnsTopicDetailComponent_div_31_td_7_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 39);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r5 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r5.endpoint, "");
    }
}

function SnsTopicDetailComponent_div_31_th_9_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 41);
        \u0275\u0275text(1, "Protocol");
        \u0275\u0275elementEnd();
    }
}

function SnsTopicDetailComponent_div_31_td_10_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 39);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r6 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r6.protocol, "");
    }
}

function SnsTopicDetailComponent_div_31_th_12_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 42);
        \u0275\u0275text(1, "Owner");
        \u0275\u0275elementEnd();
    }
}

function SnsTopicDetailComponent_div_31_td_13_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 39);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r7 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r7.owner, "");
    }
}

function SnsTopicDetailComponent_div_31_th_15_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 43);
        \u0275\u0275text(1, "Actions");
        \u0275\u0275elementEnd();
    }
}

function SnsTopicDetailComponent_div_31_td_16_Template(rf, ctx) {
    if (rf & 1) {
        const _r8 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "td", 39)(1, "button", 44);
        \u0275\u0275listener("click", function SnsTopicDetailComponent_div_31_td_16_Template_button_click_1_listener() {
            const row_r9 = \u0275\u0275restoreView(_r8).$implicit;
            const ctx_r2 = \u0275\u0275nextContext(2);
            return \u0275\u0275resetView(ctx_r2.editSubscription(row_r9.subscriptionArn));
        });
        \u0275\u0275elementStart(2, "mat-icon");
        \u0275\u0275text(3, "edit");
        \u0275\u0275elementEnd()();
        \u0275\u0275elementStart(4, "button", 45);
        \u0275\u0275listener("click", function SnsTopicDetailComponent_div_31_td_16_Template_button_click_4_listener() {
            const row_r9 = \u0275\u0275restoreView(_r8).$implicit;
            const ctx_r2 = \u0275\u0275nextContext(2);
            return \u0275\u0275resetView(ctx_r2.unsubscribe(row_r9.subscriptionArn));
        });
        \u0275\u0275elementStart(5, "mat-icon");
        \u0275\u0275text(6, "unsubscribe");
        \u0275\u0275elementEnd()()();
    }
}

function SnsTopicDetailComponent_div_31_tr_17_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 46);
    }
}

function SnsTopicDetailComponent_div_31_tr_18_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 47);
    }
}

function SnsTopicDetailComponent_div_31_tr_19_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "tr", 48)(1, "td", 49);
        \u0275\u0275text(2, " No data matching the filter. ");
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const ctx_r2 = \u0275\u0275nextContext(2);
        \u0275\u0275advance();
        \u0275\u0275attribute("colspan", ctx_r2.subscriptionColumns.length);
    }
}

function SnsTopicDetailComponent_div_31_Template(rf, ctx) {
    if (rf & 1) {
        const _r2 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "div", 22)(1, "table", 23);
        \u0275\u0275listener("matSortChange", function SnsTopicDetailComponent_div_31_Template_table_matSortChange_1_listener($event) {
            \u0275\u0275restoreView(_r2);
            const ctx_r2 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r2.subscriptionSortChange($event));
        });
        \u0275\u0275elementContainerStart(2, 24);
        \u0275\u0275template(3, SnsTopicDetailComponent_div_31_th_3_Template, 2, 0, "th", 25)(4, SnsTopicDetailComponent_div_31_td_4_Template, 2, 1, "td", 26);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(5, 27);
        \u0275\u0275template(6, SnsTopicDetailComponent_div_31_th_6_Template, 2, 0, "th", 28)(7, SnsTopicDetailComponent_div_31_td_7_Template, 2, 1, "td", 26);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(8, 29);
        \u0275\u0275template(9, SnsTopicDetailComponent_div_31_th_9_Template, 2, 0, "th", 30)(10, SnsTopicDetailComponent_div_31_td_10_Template, 2, 1, "td", 26);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(11, 31);
        \u0275\u0275template(12, SnsTopicDetailComponent_div_31_th_12_Template, 2, 0, "th", 32)(13, SnsTopicDetailComponent_div_31_td_13_Template, 2, 1, "td", 26);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(14, 33);
        \u0275\u0275template(15, SnsTopicDetailComponent_div_31_th_15_Template, 2, 0, "th", 34)(16, SnsTopicDetailComponent_div_31_td_16_Template, 7, 0, "td", 26);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275template(17, SnsTopicDetailComponent_div_31_tr_17_Template, 1, 0, "tr", 35)(18, SnsTopicDetailComponent_div_31_tr_18_Template, 1, 0, "tr", 36)(19, SnsTopicDetailComponent_div_31_tr_19_Template, 3, 1, "tr", 37);
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const topicSubscriptions_r10 = ctx.ngIf;
        const ctx_r2 = \u0275\u0275nextContext();
        \u0275\u0275advance();
        \u0275\u0275property("dataSource", topicSubscriptions_r10.SubscriptionCounters);
        \u0275\u0275advance(16);
        \u0275\u0275property("matHeaderRowDef", ctx_r2.subscriptionColumns);
        \u0275\u0275advance();
        \u0275\u0275property("matRowDefColumns", ctx_r2.subscriptionColumns);
    }
}

var SnsTopicDetailComponent = class _SnsTopicDetailComponent {
    constructor(snackBar, snsService, route, dialog, location, store, state) {
        this.snackBar = snackBar;
        this.snsService = snsService;
        this.route = route;
        this.dialog = dialog;
        this.location = location;
        this.store = store;
        this.state = state;
        this.lastUpdate = /* @__PURE__ */ new Date();
        this.topicArn = "";
        this.topicDetails$ = this.store.select(selectDetails);
        this.topicDetailsError$ = this.store.select(selectError);
        this.topicSubscriptions$ = this.store.select(selectSubscriptions);
        this.subscriptionPageSize$ = this.store.select(selectSubscriptionPageSize);
        this.subscriptionPageIndex$ = this.store.select(selectSubscriptionPageIndex);
        this.subscriptionColumns = ["id", "endpoint", "protocol", "owner", "actions"];
        this.subscriptionPageSizeOptions = [5, 10, 20, 50, 100];
    }

    ngOnInit() {
        this.sub = this.route.params.subscribe((params) => {
            this.topicArn = params["topicArn"];
            this.loadTopicDetails();
            this.loadSubscriptions();
        });
        this.topicDetailsError$.subscribe((msg) => {
            if (msg && msg.length) {
                this.snackBar.open("ErrorMessage: " + msg.toString());
            }
        });
    }

    ngOnDestroy() {
        this.sub.unsubscribe();
    }

    back() {
        this.location.back();
    }

    refresh() {
        this.loadTopicDetails();
        this.loadSubscriptions();
    }

    // ===================================================================================================================
    // Details
    // ===================================================================================================================
    loadTopicDetails() {
        this.store.dispatch(snsTopicDetailsActions.loadDetails({topicArn: this.topicArn}));
    }

    save() {
    }

    close() {
        this.location.back();
    }

    // ===================================================================================================================
    // Subscriptions
    // ===================================================================================================================
    handleSubscriptionPageEvent(e2) {
        this.state.value["sns-topic-details"].subscriptionPageSize = e2.pageSize;
        this.state.value["sns-topic-details"].subscriptionPageIndex = e2.pageIndex;
        this.loadSubscriptions();
    }

    loadSubscriptions() {
        this.store.dispatch(snsTopicDetailsActions.loadSubscriptions({
            topicArn: this.topicArn,
            pageSize: this.state.value["sns-topic-details"].subscriptionPageSize,
            pageIndex: this.state.value["sns-topic-details"].subscriptionPageIndex,
            sortColumns: this.state.value["sns-topic-details"].sortColumns
        }));
    }

    subscriptionSortChange(sortState) {
        this.state.value["sns-topic-details"].sortColumns = [];
        let column = sortState.active;
        let direction = sortState.direction === "asc" ? 1 : -1;
        this.state.value["sns-topic-details"].sortColumns = [{column, sortDirection: direction}];
        this.loadSubscriptions();
    }

    refreshSubscriptions() {
        this.loadSubscriptions();
    }

    unsubscribe(subscriptionArn) {
    }

    editSubscription(topicArn) {
    }

    addSubscription() {
        const dialogConfig = new MatDialogConfig();
        dialogConfig.disableClose = true;
        dialogConfig.autoFocus = true;
        this.dialog.open(SubscriptionAddComponentDialog, dialogConfig).afterClosed().subscribe((result) => {
            if (result) {
                this.subscribe(result);
            }
        });
    }

    subscribe(subscription) {
        this.snsService.subscribe(subscription.topicArn, subscription.endpoint, subscription.protocol).then((data) => {
            this.loadSubscriptions();
            this.snackBar.open("Subscription saved, subscription ARN:" + data.SubscriptionArn, "Dismiss", {duration: 5e3});
        }).catch((error) => console.error(error)).finally(() => {
        });
    }

    static {
        this.\u0275fac = function SnsTopicDetailComponent_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _SnsTopicDetailComponent)(\u0275\u0275directiveInject(MatSnackBar), \u0275\u0275directiveInject(SnsService), \u0275\u0275directiveInject(ActivatedRoute), \u0275\u0275directiveInject(MatDialog), \u0275\u0275directiveInject(Location), \u0275\u0275directiveInject(Store), \u0275\u0275directiveInject(State));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _SnsTopicDetailComponent,
            selectors: [["add-connection-dialog"]],
            features: [\u0275\u0275ProvidersFeature([SnsService])],
            decls: 51,
            vars: 26,
            consts: [["appearance", "outlined", 2, "margin", "3px"], ["aria-label", "Back", "mat-icon-button", "", 1, "head-buttons-left", 3, "click"], [1, "fill-remaining-space"], ["aria-label", "Refresh", "mat-icon-button", "", 3, "click"], ["appearance", "outlined", 2, "margin-top", "5px"], [4, "ngIf"], ["label", "Subscriptions"], [1, "head-buttons"], ["class", "row", 4, "ngIf"], ["aria-label", "Select page", 3, "page", "disabled", "hidePageSize", "length", "pageIndex", "pageSizeOptions", "pageSize", "showFirstLastButtons"], ["label", "Access Policy"], ["label", "Tags"], ["label", "Attributes"], ["align", "end"], ["mat-button", "", 3, "click"], [1, "footer"], ["cols", "4", "rowHeight", "400px"], [3, "colspan", "rowspan"], [2, "height", "80px"], ["matListItemTitle", ""], ["matListItemLine", ""], [2, "width", "100%", "display", "flex", "align-items", "flex-start", "align-content", "flex-start"], [1, "row"], ["mat-table", "", "matSort", "", 1, "mat-elevation-z8", 3, "matSortChange", "dataSource"], ["matColumnDef", "id"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "ID", "sortActionDescription", "Sort by subscriptionArn", 4, "matHeaderCellDef"], ["mat-cell", "", 4, "matCellDef"], ["matColumnDef", "endpoint"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Endpoint", "sortActionDescription", "Sort by endpoint", 4, "matHeaderCellDef"], ["matColumnDef", "protocol"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Protocol", "sortActionDescription", "Sort by endpoint", 4, "matHeaderCellDef"], ["matColumnDef", "owner"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Owner", "sortActionDescription", "Sort by endpoint", 4, "matHeaderCellDef"], ["matColumnDef", "actions"], ["mat-header-cell", "", "style", "width:120px", 4, "matHeaderCellDef"], ["mat-header-row", "", 4, "matHeaderRowDef"], ["mat-row", "", 4, "matRowDef", "matRowDefColumns"], ["class", "mat-row", 4, "matNoDataRow"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "ID", "sortActionDescription", "Sort by subscriptionArn"], ["mat-cell", ""], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Endpoint", "sortActionDescription", "Sort by endpoint"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Protocol", "sortActionDescription", "Sort by endpoint"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Owner", "sortActionDescription", "Sort by endpoint"], ["mat-header-cell", "", 2, "width", "120px"], ["aria-label", "Edit", "mat-icon-button", "", "matTooltip", "Edit the subscription", 3, "click"], ["aria-label", "Delete", "mat-icon-button", "", "matTooltip", "Unsubscribe from the topic", 3, "click"], ["mat-header-row", ""], ["mat-row", ""], [1, "mat-row"], [1, "mat-cell"]],
            template: function SnsTopicDetailComponent_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "mat-card", 0)(1, "mat-card-header")(2, "span")(3, "button", 1);
                    \u0275\u0275listener("click", function SnsTopicDetailComponent_Template_button_click_3_listener() {
                        return ctx.back();
                    });
                    \u0275\u0275elementStart(4, "mat-icon");
                    \u0275\u0275text(5, "arrow_back");
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(6, "span", 2)(7, "h4");
                    \u0275\u0275text(8);
                    \u0275\u0275pipe(9, "async");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(10, "span")(11, "button", 3);
                    \u0275\u0275listener("click", function SnsTopicDetailComponent_Template_button_click_11_listener() {
                        return ctx.refresh();
                    });
                    \u0275\u0275elementStart(12, "mat-icon");
                    \u0275\u0275text(13, "refresh");
                    \u0275\u0275elementEnd()()()();
                    \u0275\u0275elementStart(14, "mat-card", 4);
                    \u0275\u0275template(15, SnsTopicDetailComponent_div_15_Template, 54, 20, "div", 5);
                    \u0275\u0275pipe(16, "async");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(17, "mat-card", 4)(18, "mat-card-header")(19, "mat-card-title");
                    \u0275\u0275text(20, "Attributes");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(21, "mat-card-content")(22, "mat-tab-group")(23, "mat-tab", 6)(24, "mat-card-actions", 7)(25, "button", 3);
                    \u0275\u0275listener("click", function SnsTopicDetailComponent_Template_button_click_25_listener() {
                        return ctx.addSubscription();
                    });
                    \u0275\u0275elementStart(26, "mat-icon");
                    \u0275\u0275text(27, "add");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(28, "button", 3);
                    \u0275\u0275listener("click", function SnsTopicDetailComponent_Template_button_click_28_listener() {
                        return ctx.refreshSubscriptions();
                    });
                    \u0275\u0275elementStart(29, "mat-icon");
                    \u0275\u0275text(30, "refresh");
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275template(31, SnsTopicDetailComponent_div_31_Template, 20, 3, "div", 8);
                    \u0275\u0275pipe(32, "async");
                    \u0275\u0275elementStart(33, "mat-paginator", 9);
                    \u0275\u0275pipe(34, "async");
                    \u0275\u0275pipe(35, "async");
                    \u0275\u0275pipe(36, "async");
                    \u0275\u0275listener("page", function SnsTopicDetailComponent_Template_mat_paginator_page_33_listener($event) {
                        return ctx.handleSubscriptionPageEvent($event);
                    });
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(37, "mat-tab", 10);
                    \u0275\u0275text(38, " Access Control ");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(39, "mat-tab", 11);
                    \u0275\u0275text(40, " Tags ");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(41, "mat-tab", 12);
                    \u0275\u0275text(42, " Attributes ");
                    \u0275\u0275elementEnd()()()();
                    \u0275\u0275elementStart(43, "mat-card-actions", 13)(44, "button", 14);
                    \u0275\u0275listener("click", function SnsTopicDetailComponent_Template_button_click_44_listener() {
                        return ctx.close();
                    });
                    \u0275\u0275text(45, "Close");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(46, "button", 14);
                    \u0275\u0275listener("click", function SnsTopicDetailComponent_Template_button_click_46_listener() {
                        return ctx.save();
                    });
                    \u0275\u0275text(47, "Save");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(48, "div", 15);
                    \u0275\u0275text(49);
                    \u0275\u0275pipe(50, "date");
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    let tmp_0_0;
                    let tmp_5_0;
                    \u0275\u0275advance(8);
                    \u0275\u0275textInterpolate1("Topic: ", (tmp_0_0 = \u0275\u0275pipeBind1(9, 11, ctx.topicDetails$)) == null ? null : tmp_0_0.topicName, "");
                    \u0275\u0275advance(7);
                    \u0275\u0275property("ngIf", \u0275\u0275pipeBind1(16, 13, ctx.topicDetails$));
                    \u0275\u0275advance(16);
                    \u0275\u0275property("ngIf", \u0275\u0275pipeBind1(32, 15, ctx.topicSubscriptions$));
                    \u0275\u0275advance(2);
                    \u0275\u0275property("disabled", false)("hidePageSize", false)("length", (tmp_5_0 = \u0275\u0275pipeBind1(34, 17, ctx.topicSubscriptions$)) == null ? null : tmp_5_0.Total)("pageIndex", \u0275\u0275pipeBind1(35, 19, ctx.subscriptionPageIndex$))("pageSizeOptions", ctx.subscriptionPageSizeOptions)("pageSize", \u0275\u0275pipeBind1(36, 21, ctx.subscriptionPageSize$))("showFirstLastButtons", true);
                    \u0275\u0275advance(16);
                    \u0275\u0275textInterpolate1(" Last update: ", \u0275\u0275pipeBind2(50, 23, ctx.lastUpdate, "HH:mm:ss"), " ");
                }
            },
            dependencies: [MatCard, MatCardHeader, MatCardContent, MatCardActions, MatCardTitle, MatTable, MatHeaderCellDef, MatCellDef, MatColumnDef, MatIcon, MatHeaderCell, MatCell, MatHeaderRowDef, MatHeaderRow, MatSortHeader, MatRowDef, MatNoDataRow, MatIconButton, MatRow, MatPaginator, MatSort, MatTooltip, MatListItem, MatGridTile, MatGridList, MatList, MatTabGroup, MatTab, MatButton, NgIf, DatePipe, AsyncPipe],
            styles: ["\n\nbody[_ngcontent-%COMP%] {\n  margin: 40px;\n}\n.container[_ngcontent-%COMP%] {\n  width: 100%;\n}\n.form[_ngcontent-%COMP%] {\n  min-width: 150px;\n  width: 100%;\n  margin-right: 10px;\n}\n.form-full-width[_ngcontent-%COMP%] {\n  width: 100%;\n}\n.head-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding-right: 30px;\n  justify-content: flex-end;\n}\n.footer[_ngcontent-%COMP%] {\n  display: flex;\n  width: 50%;\n  font-size: x-small;\n  color: black;\n  padding-left: 10px;\n}\n.fill-remaining-space[_ngcontent-%COMP%] {\n  flex: 1 1 auto;\n}\n.my-nav-list[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n}\n/*# sourceMappingURL=topic-detail.component.css.map */"]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(SnsTopicDetailComponent, {
        className: "SnsTopicDetailComponent",
        filePath: "src/app/modules/sns/topic-detail/topic-detail.component.ts",
        lineNumber: 24
    });
})();

// src/app/modules/sns/message-list/state/sns-message-list.actions.ts
var snsMessageListActions = {
    initialize: createAction("[sns-message-list] initialize"),
    // Load topic
    loadMessages: createAction("[sns-message-list] Load messages", props()),
    loadMessagesSuccess: createAction("[sns-message-list] Load messages success", props()),
    loadMessagesFailure: createAction("[sns-message-list] Load messages failure", props()),
    // Publish message
    publishMessage: createAction("[sns-message-list] Publish message", props()),
    publishMessageSuccess: createAction("[sns-message-list] Publish message success"),
    publishMessageFailure: createAction("[sns-message-list] Publish message error", props()),
    // Delete topic
    deleteMessage: createAction("[sns-message-list] Delete message", props()),
    deleteMessageSuccess: createAction("[sns-message-list] Delete message success"),
    deleteMessageFailure: createAction("[sns-message-list] Delete message error", props())
};

// src/app/modules/sns/message-list/state/sns-message-list.reducer.ts
var snsMessageListFeatureKey = "sns-message-list";
var initialState3 = {
    snsMessageCountersResponse: {total: 0, messages: []},
    pageSize: 10,
    pageIndex: 0,
    loading: false,
    sortColumns: [{column: "attributes.availableMessages", sortDirection: -1}],
    error: {}
};
var snsMessageListReducer = createReducer(
    initialState3,
    // Initialize
    on(snsMessageListActions.initialize, (state) => __spreadProps(__spreadValues({}, state), {pageIndex: 0, pageSize: 10, loading: true})),
    // Message list
    on(snsMessageListActions.loadMessages, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(snsMessageListActions.loadMessagesSuccess, (state, {messages}) => __spreadProps(__spreadValues({}, state), {
        snsMessageCountersResponse: messages,
        loading: false
    })),
    on(snsMessageListActions.loadMessagesFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false})),
    // Publish message
    on(snsMessageListActions.publishMessage, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(snsMessageListActions.publishMessageSuccess, (state) => __spreadProps(__spreadValues({}, state), {loading: false})),
    on(snsMessageListActions.publishMessageFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false})),
    // Delete message
    on(snsMessageListActions.deleteMessage, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(snsMessageListActions.deleteMessageSuccess, (state) => __spreadProps(__spreadValues({}, state), {loading: false})),
    on(snsMessageListActions.deleteMessageFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false}))
);

// src/app/modules/sns/message-list/state/sns-message-list.selectors.ts
var selectMessageListFeature = createFeatureSelector(snsMessageListFeatureKey);
var selectIsLoading2 = createSelector(selectMessageListFeature, (state) => state.loading);
var selectPageSize2 = createSelector(selectMessageListFeature, (state) => state?.pageSize);
var selectPageIndex2 = createSelector(selectMessageListFeature, (state) => state?.pageIndex);
var selectMessageCounters = createSelector(selectMessageListFeature, (state) => state?.snsMessageCountersResponse);

// src/app/modules/sns/message-list/view-message/sns-view-message.component.ts
var SnsViewMessageDialog = class _SnsViewMessageDialog {
    constructor(dialogRef, data) {
        this.dialogRef = dialogRef;
        this.data = data;
        this.body = "";
        this.rawMessage = "";
        this.messageId = "";
        this.prettyPrint = true;
        this.message = data.message;
        this.rawMessage = this.message?.message;
        this.messageId = this.message?.messageId;
        if (this.prettyPrint) {
            this.body = JSON.stringify(JSON.parse(data.message.message), null, 2);
        } else {
            this.body = data.message.message;
        }
    }

    ngOnInit() {
    }

    sendMessage() {
        this.dialogRef.close(true);
    }

    changePrettyPrint(event) {
        if (this.message?.message !== void 0) {
            if (event.checked) {
                this.body = JSON.stringify(JSON.parse(this.message?.message), null, 2);
            } else {
                this.body = this.message?.message;
            }
        }
    }

    close() {
        this.dialogRef.close(false);
    }

    static {
        this.\u0275fac = function SnsViewMessageDialog_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _SnsViewMessageDialog)(\u0275\u0275directiveInject(MatDialogRef), \u0275\u0275directiveInject(MAT_DIALOG_DATA));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _SnsViewMessageDialog,
            selectors: [["sns-edit-message-dialog"]],
            standalone: true,
            features: [\u0275\u0275StandaloneFeature],
            decls: 14,
            vars: 4,
            consts: [["cdkDrag", "", "cdkDragHandle", "", "cdkDragRootElement", ".cdk-overlay-pane", "mat-dialog-title", ""], ["labelPosition", "before", 3, "change", "checked"], [1, "mat-typography"], [2, "width", "100%", "height", "100%"], ["cdkAutosizeMinRows", "20", "cdkTextareaAutosize", "", "matInput", "", "placeholder", "Message", "readonly", "", 2, "width", "100%", "height", "100%", 3, "ngModelChange", "ngModel"], ["align", "end"], ["mat-button", "", "mat-dialog-close", ""]],
            template: function SnsViewMessageDialog_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "h2", 0);
                    \u0275\u0275text(1);
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(2, "mat-dialog-actions")(3, "mat-slide-toggle", 1);
                    \u0275\u0275listener("change", function SnsViewMessageDialog_Template_mat_slide_toggle_change_3_listener($event) {
                        return ctx.changePrettyPrint($event);
                    });
                    \u0275\u0275text(4, " Pretty Print: ");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(5, "mat-dialog-content", 2)(6, "mat-form-field", 3)(7, "mat-label");
                    \u0275\u0275text(8, "Message:");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(9, "textarea", 4);
                    \u0275\u0275twoWayListener("ngModelChange", function SnsViewMessageDialog_Template_textarea_ngModelChange_9_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.body, $event) || (ctx.body = $event);
                        return $event;
                    });
                    \u0275\u0275text(10);
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(11, "mat-dialog-actions", 5)(12, "button", 6);
                    \u0275\u0275text(13, "Close");
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    \u0275\u0275advance();
                    \u0275\u0275textInterpolate1("Edit SNS message: ", ctx.messageId, "");
                    \u0275\u0275advance(2);
                    \u0275\u0275property("checked", ctx.prettyPrint);
                    \u0275\u0275advance(6);
                    \u0275\u0275twoWayProperty("ngModel", ctx.body);
                    \u0275\u0275advance();
                    \u0275\u0275textInterpolate1("            ", ctx.body, "\n        ");
                }
            },
            dependencies: [
                MatDialogContent,
                MatDialogTitle,
                MatDialogActions,
                MatButton,
                MatDialogClose,
                MatFormField,
                MatLabel,
                FormsModule,
                DefaultValueAccessor,
                NgControlStatus,
                NgModel,
                MatInput,
                ReactiveFormsModule,
                CdkDrag,
                CdkDragHandle,
                CdkTextareaAutosize,
                MatSlideToggle
            ]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(SnsViewMessageDialog, {
        className: "SnsViewMessageDialog",
        filePath: "src/app/modules/sns/message-list/view-message/sns-view-message.component.ts",
        lineNumber: 39
    });
})();

// src/app/modules/sns/message-list/sns-message-list.component.ts
var _c02 = () => [];

function SnsMessageListComponent_div_17_th_3_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 25);
        \u0275\u0275text(1, "Message ID");
        \u0275\u0275elementEnd();
    }
}

function SnsMessageListComponent_div_17_td_4_Template(rf, ctx) {
    if (rf & 1) {
        const _r3 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "td", 26)(1, "mat-nav-list")(2, "a", 27);
        \u0275\u0275listener("click", function SnsMessageListComponent_div_17_td_4_Template_a_click_2_listener() {
            const element_r4 = \u0275\u0275restoreView(_r3).$implicit;
            const ctx_r1 = \u0275\u0275nextContext(2);
            return \u0275\u0275resetView(ctx_r1.editMessage(element_r4));
        });
        \u0275\u0275text(3);
        \u0275\u0275elementEnd()()();
    }
    if (rf & 2) {
        const element_r4 = ctx.$implicit;
        \u0275\u0275advance(3);
        \u0275\u0275textInterpolate1(" ", element_r4.messageId, "");
    }
}

function SnsMessageListComponent_div_17_th_6_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 28);
        \u0275\u0275text(1, "Region");
        \u0275\u0275elementEnd();
    }
}

function SnsMessageListComponent_div_17_td_7_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 26);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r5 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r5.region, "");
    }
}

function SnsMessageListComponent_div_17_th_9_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 29);
        \u0275\u0275text(1, "Created");
        \u0275\u0275elementEnd();
    }
}

function SnsMessageListComponent_div_17_td_10_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 26);
        \u0275\u0275text(1);
        \u0275\u0275pipe(2, "date");
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r6 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", \u0275\u0275pipeBind2(2, 1, element_r6.created, "dd-MM-yyyy HH:mm:ss"), "");
    }
}

function SnsMessageListComponent_div_17_th_12_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 30);
        \u0275\u0275text(1, "Modified");
        \u0275\u0275elementEnd();
    }
}

function SnsMessageListComponent_div_17_td_13_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 26);
        \u0275\u0275text(1);
        \u0275\u0275pipe(2, "date");
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r7 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", \u0275\u0275pipeBind2(2, 1, element_r7.modified, "dd-MM-yyyy HH:mm:ss"), "");
    }
}

function SnsMessageListComponent_div_17_th_15_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 31);
        \u0275\u0275text(1, "Actions");
        \u0275\u0275elementEnd();
    }
}

function SnsMessageListComponent_div_17_td_16_Template(rf, ctx) {
    if (rf & 1) {
        const _r8 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "td", 26)(1, "button", 32);
        \u0275\u0275listener("click", function SnsMessageListComponent_div_17_td_16_Template_button_click_1_listener() {
            const row_r9 = \u0275\u0275restoreView(_r8).$implicit;
            const ctx_r1 = \u0275\u0275nextContext(2);
            return \u0275\u0275resetView(ctx_r1.deleteMessage(row_r9.messageId));
        });
        \u0275\u0275elementStart(2, "mat-icon");
        \u0275\u0275text(3, "delete");
        \u0275\u0275elementEnd()()();
    }
}

function SnsMessageListComponent_div_17_tr_17_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 33);
    }
}

function SnsMessageListComponent_div_17_tr_18_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 34);
    }
}

function SnsMessageListComponent_div_17_tr_19_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "tr", 35)(1, "td", 36);
        \u0275\u0275text(2, " No data matching the filter. ");
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const ctx_r1 = \u0275\u0275nextContext(2);
        \u0275\u0275advance();
        \u0275\u0275attribute("colspan", ctx_r1.columns.length);
    }
}

function SnsMessageListComponent_div_17_Template(rf, ctx) {
    if (rf & 1) {
        const _r1 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "div", 9)(1, "table", 10);
        \u0275\u0275listener("matSortChange", function SnsMessageListComponent_div_17_Template_table_matSortChange_1_listener($event) {
            \u0275\u0275restoreView(_r1);
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.sortChange($event));
        });
        \u0275\u0275elementContainerStart(2, 11);
        \u0275\u0275template(3, SnsMessageListComponent_div_17_th_3_Template, 2, 0, "th", 12)(4, SnsMessageListComponent_div_17_td_4_Template, 4, 1, "td", 13);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(5, 14);
        \u0275\u0275template(6, SnsMessageListComponent_div_17_th_6_Template, 2, 0, "th", 15)(7, SnsMessageListComponent_div_17_td_7_Template, 2, 1, "td", 13);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(8, 16);
        \u0275\u0275template(9, SnsMessageListComponent_div_17_th_9_Template, 2, 0, "th", 17)(10, SnsMessageListComponent_div_17_td_10_Template, 3, 4, "td", 13);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(11, 18);
        \u0275\u0275template(12, SnsMessageListComponent_div_17_th_12_Template, 2, 0, "th", 19)(13, SnsMessageListComponent_div_17_td_13_Template, 3, 4, "td", 13);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(14, 20);
        \u0275\u0275template(15, SnsMessageListComponent_div_17_th_15_Template, 2, 0, "th", 21)(16, SnsMessageListComponent_div_17_td_16_Template, 4, 0, "td", 13);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275template(17, SnsMessageListComponent_div_17_tr_17_Template, 1, 0, "tr", 22)(18, SnsMessageListComponent_div_17_tr_18_Template, 1, 0, "tr", 23)(19, SnsMessageListComponent_div_17_tr_19_Template, 3, 1, "tr", 24);
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const messageCounters_r10 = ctx.ngIf;
        const ctx_r1 = \u0275\u0275nextContext();
        \u0275\u0275advance();
        \u0275\u0275property("dataSource", messageCounters_r10.messages);
        \u0275\u0275advance(16);
        \u0275\u0275property("matHeaderRowDef", ctx_r1.columns);
        \u0275\u0275advance();
        \u0275\u0275property("matRowDefColumns", ctx_r1.columns);
    }
}

var SnsMessageListComponent = class _SnsMessageListComponent {
    constructor(route, location, dialog, store, state, actionsSubj$) {
        this.route = route;
        this.location = location;
        this.dialog = dialog;
        this.store = store;
        this.state = state;
        this.actionsSubj$ = actionsSubj$;
        this.lastUpdate = /* @__PURE__ */ new Date();
        this.topicArn = "";
        this.pageSize$ = this.store.select(selectPageSize2);
        this.pageIndex$ = this.store.select(selectPageIndex2);
        this.listMessageCountersResponse$ = this.store.select(selectMessageCounters);
        this.columns = ["messageId", "region", "created", "modified", "actions"];
        this.pageSizeOptions = [5, 10, 20, 50, 100];
        this.hidePageSize = false;
        this.showPageSizeOptions = true;
        this.showFirstLastButtons = true;
        this.disabled = false;
        this.topicName = "";
        this.actionsSubj$.pipe(filter((action) => action.type === snsMessageListActions.publishMessageSuccess.type || action.type === snsMessageListActions.deleteMessageSuccess.type)).subscribe(() => {
            this.lastUpdate = /* @__PURE__ */ new Date();
            this.loadMessages();
        });
    }

    ngOnInit() {
        this.routerSubscription = this.route.params.subscribe((params) => {
            this.topicArn = decodeURI(params["topicArn"]);
            this.topicName = this.topicArn.substring(this.topicArn.lastIndexOf(":") + 1);
        });
        this.updateSubscription = interval(6e4).subscribe(() => this.loadMessages());
        this.loadMessages();
    }

    ngOnDestroy() {
        this.routerSubscription?.unsubscribe();
        this.updateSubscription?.unsubscribe();
    }

    back() {
        this.location.back();
    }

    refresh() {
        this.loadMessages();
    }

    sortChange(sortState) {
        this.state.value["sns-message-list"].sortColumns = [];
        let direction;
        let column = "messageId";
        if (sortState.active === "availableMessages") {
            column = "attributes.availableMessages";
        }
        if (sortState.direction === "asc") {
            direction = 1;
        } else {
            direction = -1;
        }
        this.state.value["sns-message-list"].sortColumns = [{column, sortDirection: direction}];
        this.loadMessages();
    }

    handlePageEvent(e2) {
        this.state.value["sns-message-list"].pageSize = e2.pageSize;
        this.state.value["sns-message-list"].pageIndex = e2.pageIndex;
        this.loadMessages();
    }

    loadMessages() {
        this.store.dispatch(snsMessageListActions.loadMessages({
            topicArn: this.topicArn,
            pageSize: this.state.value["sns-message-list"].pageSize,
            pageIndex: this.state.value["sns-message-list"].pageIndex,
            sortColumns: this.state.value["sns-message-list"].sortColumns
        }));
    }

    editMessage(message) {
        const dialogConfig = new MatDialogConfig();
        dialogConfig.disableClose = true;
        dialogConfig.autoFocus = true;
        dialogConfig.data = {message};
        dialogConfig.maxWidth = "100vw";
        dialogConfig.maxHeight = "100vh";
        dialogConfig.panelClass = "full-screen-modal";
        dialogConfig.width = "70%";
        this.dialog.open(SnsViewMessageDialog, dialogConfig).afterClosed().subscribe(() => {
        });
    }

    deleteMessage(messageId) {
        this.store.dispatch(snsMessageListActions.deleteMessage({topicArn: this.topicArn, messageId}));
    }

    publishMessage() {
        const dialogConfig = new MatDialogConfig();
        dialogConfig.disableClose = true;
        dialogConfig.autoFocus = true;
        dialogConfig.data = {topicArn: this.topicArn};
        dialogConfig.maxWidth = "100vw";
        dialogConfig.maxHeight = "100vh";
        dialogConfig.panelClass = "full-screen-modal";
        dialogConfig.width = "90%";
        this.dialog.open(PublishMessageComponentDialog, dialogConfig).afterClosed().subscribe((result) => {
            if (result) {
                this.store.dispatch(snsMessageListActions.publishMessage({topicArn: this.topicArn, message: result}));
            }
        });
    }

    static {
        this.\u0275fac = function SnsMessageListComponent_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _SnsMessageListComponent)(\u0275\u0275directiveInject(ActivatedRoute), \u0275\u0275directiveInject(Location), \u0275\u0275directiveInject(MatDialog), \u0275\u0275directiveInject(Store), \u0275\u0275directiveInject(State), \u0275\u0275directiveInject(ActionsSubject));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _SnsMessageListComponent,
            selectors: [["sns-message-list"]],
            features: [\u0275\u0275ProvidersFeature([SnsService])],
            decls: 26,
            vars: 22,
            consts: [["appearance", "outlined", 2, "margin", "3px"], ["aria-label", "Back", "mat-icon-button", "", 1, "head-buttons-left", 3, "click"], [1, "fill-remaining-space"], ["aria-label", "Refresh", "mat-icon-button", "", 3, "click"], ["appearance", "outlined", 2, "margin", "-10px"], [1, "table-container"], ["class", "row", 4, "ngIf"], ["aria-label", "Select page", 2, "width", "99%", "margin-left", "15px", 3, "page", "disabled", "hidePageSize", "length", "pageIndex", "pageSizeOptions", "pageSize", "showFirstLastButtons"], [1, "footer"], [1, "row"], ["mat-table", "", "matSort", "", 1, "mat-elevation-z8", "queue-table", 3, "matSortChange", "dataSource"], ["matColumnDef", "messageId"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Message ID", "sortActionDescription", "Sort by id", 4, "matHeaderCellDef"], ["mat-cell", "", 4, "matCellDef"], ["matColumnDef", "region"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Region", "sortActionDescription", "Sort by region", 4, "matHeaderCellDef"], ["matColumnDef", "created"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Created", "sortActionDescription", "Sort by created", 4, "matHeaderCellDef"], ["matColumnDef", "modified"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Modified", "sortActionDescription", "Sort by modified", 4, "matHeaderCellDef"], ["matColumnDef", "actions"], ["mat-header-cell", "", "style", "width:80px", 4, "matHeaderCellDef"], ["mat-header-row", "", 4, "matHeaderRowDef"], ["mat-row", "", 4, "matRowDef", "matRowDefColumns"], ["class", "mat-row", 4, "matNoDataRow"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Message ID", "sortActionDescription", "Sort by id"], ["mat-cell", ""], ["mat-list-item", "", 3, "click"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Region", "sortActionDescription", "Sort by region"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Created", "sortActionDescription", "Sort by created"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Modified", "sortActionDescription", "Sort by modified"], ["mat-header-cell", "", 2, "width", "80px"], ["aria-label", "Delete", "mat-icon-button", "", "matTooltip", "Delete the message", 3, "click"], ["mat-header-row", ""], ["mat-row", ""], [1, "mat-row"], [1, "mat-cell", 2, "padding-left", "20px", "padding-top", "10px"]],
            template: function SnsMessageListComponent_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "mat-card", 0)(1, "mat-card-header")(2, "button", 1);
                    \u0275\u0275listener("click", function SnsMessageListComponent_Template_button_click_2_listener() {
                        return ctx.back();
                    });
                    \u0275\u0275elementStart(3, "mat-icon");
                    \u0275\u0275text(4, "arrow_back");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(5, "span", 2)(6, "h4");
                    \u0275\u0275text(7);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(8, "button", 3);
                    \u0275\u0275listener("click", function SnsMessageListComponent_Template_button_click_8_listener() {
                        return ctx.publishMessage();
                    });
                    \u0275\u0275elementStart(9, "mat-icon");
                    \u0275\u0275text(10, "add");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(11, "button", 3);
                    \u0275\u0275listener("click", function SnsMessageListComponent_Template_button_click_11_listener() {
                        return ctx.refresh();
                    });
                    \u0275\u0275elementStart(12, "mat-icon");
                    \u0275\u0275text(13, "refresh");
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(14, "mat-card-content")(15, "mat-card", 4)(16, "div", 5);
                    \u0275\u0275template(17, SnsMessageListComponent_div_17_Template, 20, 3, "div", 6);
                    \u0275\u0275pipe(18, "async");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(19, "mat-paginator", 7);
                    \u0275\u0275pipe(20, "async");
                    \u0275\u0275pipe(21, "async");
                    \u0275\u0275pipe(22, "async");
                    \u0275\u0275listener("page", function SnsMessageListComponent_Template_mat_paginator_page_19_listener($event) {
                        return ctx.handlePageEvent($event);
                    });
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(23, "div", 8);
                    \u0275\u0275text(24);
                    \u0275\u0275pipe(25, "date");
                    \u0275\u0275elementEnd()()();
                }
                if (rf & 2) {
                    let tmp_4_0;
                    \u0275\u0275advance(7);
                    \u0275\u0275textInterpolate1("SNS Messages: ", ctx.topicName, "");
                    \u0275\u0275advance(10);
                    \u0275\u0275property("ngIf", \u0275\u0275pipeBind1(18, 10, ctx.listMessageCountersResponse$));
                    \u0275\u0275advance(2);
                    \u0275\u0275property("disabled", ctx.disabled)("hidePageSize", ctx.hidePageSize)("length", (tmp_4_0 = \u0275\u0275pipeBind1(20, 12, ctx.listMessageCountersResponse$)) == null ? null : tmp_4_0.total)("pageIndex", \u0275\u0275pipeBind1(21, 14, ctx.pageIndex$))("pageSizeOptions", ctx.showPageSizeOptions ? ctx.pageSizeOptions : \u0275\u0275pureFunction0(21, _c02))("pageSize", \u0275\u0275pipeBind1(22, 16, ctx.pageSize$))("showFirstLastButtons", ctx.showFirstLastButtons);
                    \u0275\u0275advance(5);
                    \u0275\u0275textInterpolate1(" Last update: ", \u0275\u0275pipeBind2(25, 18, ctx.lastUpdate, "HH:mm:ss"), " ");
                }
            },
            dependencies: [MatCard, MatCardHeader, MatCardContent, MatTable, MatHeaderCellDef, MatCellDef, MatColumnDef, MatIcon, MatHeaderCell, MatCell, MatHeaderRowDef, MatHeaderRow, MatSortHeader, MatRowDef, MatNoDataRow, MatIconButton, MatRow, MatPaginator, MatSort, MatTooltip, MatListItem, MatNavList, NgIf, DatePipe, AsyncPipe],
            styles: ['\n\n.topic-table[_ngcontent-%COMP%] {\n  width: 100%;\n  height: 100%;\n}\n.head-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  justify-content: flex-end;\n}\n.fill-remaining-space[_ngcontent-%COMP%] {\n  flex: 1 1 auto;\n}\n.full-screen-modal[_ngcontent-%COMP%]   .mat-dialog-container[_ngcontent-%COMP%] {\n  padding: 1em;\n  width: 90%;\n  height: 80%;\n  overflow-y: scroll;\n}\n.cdk-global-overlay-wrapper[_ngcontent-%COMP%] {\n  pointer-events: auto;\n  display: block;\n  position: relative;\n  overflow: auto;\n  text-align: center;\n}\n.cdk-global-overlay-wrapper[_ngcontent-%COMP%]::before {\n  content: "";\n  display: inline-block;\n  height: 100%;\n  white-space: nowrap;\n}\n.cdk-overlay-pane[_ngcontent-%COMP%] {\n  display: inline-block;\n  position: relative;\n  text-align: left;\n  white-space: normal;\n}\n.table-container[_ngcontent-%COMP%] {\n  max-height: calc(100vh - 10px);\n  overflow: auto;\n}\n.footer-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  width: 50%;\n  justify-content: flex-end;\n}\n.footer[_ngcontent-%COMP%] {\n  display: flex;\n  width: 50%;\n  font-size: x-small;\n  color: black;\n  padding-top: 15px;\n}\n/*# sourceMappingURL=sns-message-list.component.css.map */']
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(SnsMessageListComponent, {
        className: "SnsMessageListComponent",
        filePath: "src/app/modules/sns/message-list/sns-message-list.component.ts",
        lineNumber: 23
    });
})();

// src/app/modules/sns/sns-routing.module.ts
var routes = [
    {
        path: "",
        title: "SNSTopicList",
        component: SnsTopicListComponent
    },
    {
        path: "details/:topicArn",
        title: "SNSTopicDetails",
        component: SnsTopicDetailComponent
    },
    {
        path: "messages/:topicArn",
        title: "SNSMessages",
        component: SnsMessageListComponent
    }
];
var SnsRoutingModule = class _SnsRoutingModule {
    static {
        this.\u0275fac = function SnsRoutingModule_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _SnsRoutingModule)();
        };
    }
    static {
        this.\u0275mod = /* @__PURE__ */ \u0275\u0275defineNgModule({type: _SnsRoutingModule});
    }
    static {
        this.\u0275inj = /* @__PURE__ */ \u0275\u0275defineInjector({imports: [RouterModule.forChild(routes), RouterModule]});
    }
};

// src/app/modules/sns/topic-list/state/sns-topic-list.effects.ts
var SnsTopicListEffects = class _SnsTopicListEffects {
    constructor(actions$, snsService) {
        this.actions$ = actions$;
        this.snsService = snsService;
        this.sortColumns = [];
        this.loadTopics$ = createEffect(() => this.actions$.pipe(ofType(snsTopicListActions.loadTopics), mergeMap((action) => this.snsService.listTopicCounters(action.prefix, action.pageSize, action.pageIndex, action.sortColumns).pipe(map((topics) => snsTopicListActions.loadTopicsSuccess({topics})), catchError((error) => of(snsTopicListActions.loadTopicsFailure({error: error.message})))))));
        this.addTopic$ = createEffect(() => this.actions$.pipe(ofType(snsTopicListActions.addTopic), mergeMap((action) => this.snsService.addTopic(action.name).then(() => snsTopicListActions.addTopicSuccess()))));
        this.publishMessage$ = createEffect(() => this.actions$.pipe(ofType(snsTopicListActions.publishMessage), mergeMap((action) => this.snsService.publishMessage(action.topicArn, action.message).then(() => snsTopicListActions.publishMessageSuccess()).catch((error) => snsTopicListActions.publishMessageFailure({error})).finally(() => this.snsService.cleanup))));
        this.purgeTopic$ = createEffect(() => this.actions$.pipe(ofType(snsTopicListActions.purgeTopic), mergeMap((action) => this.snsService.purgeTopic(action.topicArn).pipe(map(() => snsTopicListActions.purgeTopicSuccess()), catchError((error) => of(snsTopicListActions.purgeTopicFailure({error: error.message})))))));
        this.deleteTopic$ = createEffect(() => this.actions$.pipe(ofType(snsTopicListActions.deleteTopic), mergeMap((action) => this.snsService.deleteTopic(action.topicArn).then(() => snsTopicListActions.addTopicSuccess()))));
    }

    static {
        this.\u0275fac = function SnsTopicListEffects_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _SnsTopicListEffects)(\u0275\u0275inject(Actions), \u0275\u0275inject(SnsService));
        };
    }
    static {
        this.\u0275prov = /* @__PURE__ */ \u0275\u0275defineInjectable({token: _SnsTopicListEffects, factory: _SnsTopicListEffects.\u0275fac});
    }
};

// src/app/modules/sns/topic-detail/state/sns-topic-detail.effects.ts
var SnsTopicDetailEffects = class _SnsTopicDetailEffects {
    constructor(actions$, snsService) {
        this.actions$ = actions$;
        this.snsService = snsService;
        this.loadTopicDetails$ = createEffect(() => this.actions$.pipe(ofType(snsTopicDetailsActions.loadDetails), mergeMap((action) => this.snsService.getTopicDetails(action.topicArn).pipe(map((topicDetails) => snsTopicDetailsActions.loadDetailsSuccess({topicDetails})), catchError((error) => of(snsTopicDetailsActions.loadDetailsFailure({error: error.message})))))));
        this.loadTopicSubscriptions$ = createEffect(() => this.actions$.pipe(ofType(snsTopicDetailsActions.loadSubscriptions), mergeMap((action) => this.snsService.listSubscriptionsCounters(action.topicArn, action.pageSize, action.pageIndex, action.sortColumns).pipe(map((subscriptions) => snsTopicDetailsActions.loadSubscriptionsSuccess({subscriptions})), catchError((error) => of(snsTopicDetailsActions.loadSubscriptionsFailure({error: error.message})))))));
    }

    static {
        this.\u0275fac = function SnsTopicDetailEffects_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _SnsTopicDetailEffects)(\u0275\u0275inject(Actions), \u0275\u0275inject(SnsService));
        };
    }
    static {
        this.\u0275prov = /* @__PURE__ */ \u0275\u0275defineInjectable({token: _SnsTopicDetailEffects, factory: _SnsTopicDetailEffects.\u0275fac});
    }
};

// src/app/modules/sns/message-list/state/sns-message-list.effects.ts
var SnsMessageListEffects = class _SnsMessageListEffects {
    constructor(actions$, snsService) {
        this.actions$ = actions$;
        this.snsService = snsService;
        this.loadMessages$ = createEffect(() => this.actions$.pipe(ofType(snsMessageListActions.loadMessages), mergeMap((action) => this.snsService.listMessageCounters(action.topicArn, action.pageSize, action.pageIndex, action.sortColumns).pipe(map((messages) => snsMessageListActions.loadMessagesSuccess({messages})), catchError((error) => of(snsMessageListActions.loadMessagesFailure({error: error.message})))))));
        this.publishMessage$ = createEffect(() => this.actions$.pipe(ofType(snsMessageListActions.publishMessage), mergeMap((action) => this.snsService.publishMessage(action.topicArn, action.message).then(() => snsMessageListActions.publishMessageSuccess()).catch((error) => snsMessageListActions.publishMessageFailure({error})).finally(() => this.snsService.cleanup))));
        this.deleteMessage$ = createEffect(() => this.actions$.pipe(ofType(snsMessageListActions.deleteMessage), mergeMap((action) => this.snsService.deleteMessage(action.topicArn, action.messageId).pipe(map(() => snsMessageListActions.deleteMessageSuccess()), catchError((error) => of(snsMessageListActions.deleteMessageFailure({error: error.message})))))));
    }

    static {
        this.\u0275fac = function SnsMessageListEffects_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _SnsMessageListEffects)(\u0275\u0275inject(Actions), \u0275\u0275inject(SnsService));
        };
    }
    static {
        this.\u0275prov = /* @__PURE__ */ \u0275\u0275defineInjectable({token: _SnsMessageListEffects, factory: _SnsMessageListEffects.\u0275fac});
    }
};

// src/app/modules/sns/sns.module.ts
var SnsModule = class _SnsModule {
    static {
        this.\u0275fac = function SnsModule_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _SnsModule)();
        };
    }
    static {
        this.\u0275mod = /* @__PURE__ */ \u0275\u0275defineNgModule({type: _SnsModule});
    }
    static {
        this.\u0275inj = /* @__PURE__ */ \u0275\u0275defineInjector({
            providers: [SnsService], imports: [
                MatCard,
                MatCardHeader,
                MatTable,
                MatIcon,
                MatHeaderRow,
                MatSortHeader,
                MatIconButton,
                MatRow,
                MatPaginator,
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
                SnsRoutingModule,
                StoreModule.forFeature(snsTopicListFeatureKey, snsTopicListReducer),
                StoreModule.forFeature(snsTopicDetailsFeatureKey, snsTopicDetailReducer),
                StoreModule.forFeature(snsMessageListFeatureKey, snsMessageListReducer),
                EffectsModule.forFeature([SnsTopicListEffects, SnsTopicDetailEffects, SnsMessageListEffects])
            ]
        });
    }
};
export {
    SnsModule
};
//# sourceMappingURL=chunk-NHPFKNWR.js.map

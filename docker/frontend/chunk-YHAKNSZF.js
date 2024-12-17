import {require_FileSaver_min} from "./chunk-MHNP2PIU.js";
import {loadRestXmlErrorCode, parseXmlBody, parseXmlErrorBody} from "./chunk-XLK3LOTB.js";
import {MatSlideToggle, Md5} from "./chunk-4VAYYVT5.js";
import {CdkDrag, CdkDragHandle} from "./chunk-L5B3QUPF.js";
import {S3Config, SnsConfig, SqsConfig} from "./chunk-4IO3RYFH.js";
import {AwsCrc32, eventStreamSerdeProvider, resolveEventStreamSerdeConfig} from "./chunk-XT3UHRHO.js";
import {
    awsEndpointFunctions,
    AwsSdkSigV4ASigner,
    AwsSdkSigV4Signer,
    byteConversion,
    calculateBodyLength,
    Client,
    collectBody,
    Command,
    convertToBuffer,
    createChecksumStream,
    createDefaultUserAgentProvider,
    customEndpointFunctions,
    dateToUtcString,
    decorateServiceException,
    DEFAULT_MAX_ATTEMPTS,
    DEFAULT_RETRY_MODE,
    DEFAULT_USE_DUALSTACK_ENDPOINT,
    DEFAULT_USE_FIPS_ENDPOINT,
    DefaultIdentityProviderConfig,
    EndpointCache,
    expectNonNull,
    expectObject,
    expectString,
    FetchHttpHandler,
    fromBase64,
    fromUtf8,
    getArrayIfSingleItem,
    getAwsChunkedEncodingStream,
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
    headStream,
    HttpRequest,
    HttpResponse,
    httpSigningMiddlewareOptions,
    invalidProvider,
    isArrayBuffer,
    isEmptyData,
    isSerializableHeaderValue,
    loadConfigsForDefaultMode,
    locateWindow,
    map as map2,
    NoOpLogger,
    normalizeProvider,
    numToUint8,
    parseBoolean,
    parseRfc3339DateTimeWithOffset,
    parseRfc7231DateTime,
    parseUrl,
    quoteHeader,
    requestBuilder,
    resolveAwsRegionExtensionConfiguration,
    resolveAwsSdkSigV4AConfig,
    resolveAwsSdkSigV4Config,
    resolveDefaultRuntimeConfig,
    resolveDefaultsModeConfig,
    resolveEndpoint,
    resolveEndpointConfig,
    resolveHostHeaderConfig,
    resolveHttpHandlerRuntimeConfig,
    resolveParams,
    resolveRegionConfig,
    resolveRetryConfig,
    resolveUserAgentConfig,
    sdkStreamMixin,
    SENSITIVE_STRING,
    serializeDateTime,
    ServiceException,
    setFeature,
    Sha256,
    SignatureV4,
    splitStream,
    streamCollector,
    strictParseInt32,
    strictParseLong,
    supportsWebCrypto,
    toBase64,
    toUint8Array,
    toUtf8,
    uint32ArrayFrom,
    withBaseException
} from "./chunk-5F2IFVYA.js";
import {MatTab, MatTabGroup} from "./chunk-GTOJ5AYX.js";
import {
    __awaiter,
    __generator,
    __values,
    Actions,
    ActionsSubject,
    ActivatedRoute,
    ANIMATION_MODULE_TYPE,
    AsyncPipe,
    catchError,
    CdkTextareaAutosize,
    ChangeDetectionStrategy,
    ChangeDetectorRef,
    Component,
    createAction,
    createEffect,
    createFeatureSelector,
    createReducer,
    createSelector,
    DatePipe,
    debounceTime,
    DefaultValueAccessor,
    distinctUntilChanged,
    DOCUMENT,
    EffectsModule,
    ElementRef,
    environment,
    EventEmitter,
    filter,
    FormsModule,
    HttpClient,
    HttpHeaders,
    Inject,
    inject,
    InjectionToken,
    Input,
    interval,
    LiveAnnouncer,
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
    MatCommonModule,
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
    NgModule,
    NgZone,
    numberAttribute,
    of,
    ofType,
    on,
    Optional,
    Output,
    props,
    ReactiveFormsModule,
    Router,
    RouterLink,
    RouterModule,
    select,
    setClassMetadata,
    signal,
    State,
    Store,
    StoreModule,
    Subject,
    Subscription,
    tap,
    ViewEncapsulation$1
} from "./chunk-LGOS2CJL.js";
import {__async, __objRest, __spreadProps, __spreadValues, __toESM} from "./chunk-G42SKTPL.js";

// src/app/services/awsmock-http.service.ts
var AwsMockHttpService = class _AwsMockHttpService {
    constructor(http) {
        this.http = http;
        this.S3Config = new S3Config();
        this.SqsConfig = new SqsConfig();
        this.SnsConfig = new SnsConfig();
        this.url = environment.gatewayEndpoint + "/";
    }

    static {
        this.\u0275fac = function AwsMockHttpService_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _AwsMockHttpService)(\u0275\u0275inject(HttpClient));
        };
    }
    static {
        this.\u0275prov = /* @__PURE__ */ \u0275\u0275defineInjectable({token: _AwsMockHttpService, factory: _AwsMockHttpService.\u0275fac});
    }
};

// src/app/modules/s3/bucket-list/state/s3-bucket-list.actions.ts
var s3BucketListActions = {
    initialize: createAction("[s3-bucket-list] initialize"),
    // Load buckets
    loadBuckets: createAction("[s3-bucket-list] Load Buckets", props()),
    loadBucketsSuccess: createAction("[s3-bucket-list] Load Buckets Success", props()),
    loadBucketsFailure: createAction("[s3-bucket-list] Load Buckets Error", props()),
    // Add bucket
    addBucket: createAction("[s3-bucket-list] Add Bucket", props()),
    addBucketSuccess: createAction("[s3-bucket-list] Add Bucket Success"),
    addBucketFailure: createAction("[s3-bucket-list] Add Bucket Error", props()),
    // Delete bucket
    deleteBucket: createAction("[s3-bucket-list] Delete Bucket", props()),
    deleteBucketSuccess: createAction("[s3-bucket-list] Delete Bucket Success"),
    deleteBucketFailure: createAction("[s3-bucket-list] Delete Bucket Error", props()),
    // Purge bucket
    purgeBucket: createAction("[s3-bucket-list] Purge Bucket", props()),
    purgeBucketSuccess: createAction("[s3-bucket-list] Purge Bucket Success"),
    purgeBucketFailure: createAction("[s3-bucket-list] Purge Bucket Error", props())
};

// src/app/modules/s3/bucket-list/state/s3-bucket-list.reducer.ts
var s3BucketListFeatureKey = "s3-bucket-list";
var initialState = {
    s3BucketCounters: {total: 0, bucketCounters: []},
    bucketName: "",
    prefix: "",
    pageSize: 10,
    pageIndex: 0,
    loading: false,
    sortColumns: [{column: "keys", sortDirection: -1}],
    total: 0,
    error: {}
};
var s3BucketListReducer = createReducer(
    initialState,
    // Initialize
    on(s3BucketListActions.initialize, (state) => __spreadProps(__spreadValues({}, state), {pageIndex: 0, pageSize: 10, loading: true})),
    // Bucket list
    on(s3BucketListActions.loadBuckets, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(s3BucketListActions.loadBucketsSuccess, (state, {buckets}) => __spreadProps(__spreadValues({}, state), {s3BucketCounters: buckets, loading: false})),
    on(s3BucketListActions.loadBucketsFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false})),
    // Add bucket
    on(s3BucketListActions.addBucket, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(s3BucketListActions.addBucketSuccess, (state) => __spreadProps(__spreadValues({}, state), {loading: false})),
    on(s3BucketListActions.addBucketFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false}))
);

// node_modules/@aws-sdk/middleware-expect-continue/dist-es/index.js
function addExpectContinueMiddleware(options) {
    return (next) => (args) => __async(this, null, function* () {
        const {
            request
        } = args;
        if (HttpRequest.isInstance(request) && request.body && options.runtime === "node") {
            if (options.requestHandler?.constructor?.name !== "FetchHttpHandler") {
                request.headers = __spreadProps(__spreadValues({}, request.headers), {
                    Expect: "100-continue"
                });
            }
        }
        return next(__spreadProps(__spreadValues({}, args), {
            request
        }));
    });
}

var addExpectContinueMiddlewareOptions = {
    step: "build",
    tags: ["SET_EXPECT_HEADER", "EXPECT_HEADER"],
    name: "addExpectContinueMiddleware",
    override: true
};
var getAddExpectContinuePlugin = (options) => ({
    applyToStack: (clientStack) => {
        clientStack.add(addExpectContinueMiddleware(options), addExpectContinueMiddlewareOptions);
    }
});

// node_modules/@aws-sdk/middleware-flexible-checksums/dist-es/constants.js
var RequestChecksumCalculation = {
    WHEN_SUPPORTED: "WHEN_SUPPORTED",
    WHEN_REQUIRED: "WHEN_REQUIRED"
};
var DEFAULT_REQUEST_CHECKSUM_CALCULATION = RequestChecksumCalculation.WHEN_SUPPORTED;
var DEFAULT_RESPONSE_CHECKSUM_VALIDATION = RequestChecksumCalculation.WHEN_SUPPORTED;
var ChecksumAlgorithm;
(function (ChecksumAlgorithm2) {
    ChecksumAlgorithm2["MD5"] = "MD5";
    ChecksumAlgorithm2["CRC32"] = "CRC32";
    ChecksumAlgorithm2["CRC32C"] = "CRC32C";
    ChecksumAlgorithm2["SHA1"] = "SHA1";
    ChecksumAlgorithm2["SHA256"] = "SHA256";
})(ChecksumAlgorithm || (ChecksumAlgorithm = {}));
var ChecksumLocation;
(function (ChecksumLocation2) {
    ChecksumLocation2["HEADER"] = "header";
    ChecksumLocation2["TRAILER"] = "trailer";
})(ChecksumLocation || (ChecksumLocation = {}));
var DEFAULT_CHECKSUM_ALGORITHM = ChecksumAlgorithm.MD5;
var S3_EXPRESS_DEFAULT_CHECKSUM_ALGORITHM = ChecksumAlgorithm.CRC32;

// node_modules/@aws-sdk/middleware-flexible-checksums/dist-es/stringUnionSelector.js
var SelectorType;
(function (SelectorType3) {
    SelectorType3["ENV"] = "env";
    SelectorType3["CONFIG"] = "shared config entry";
})(SelectorType || (SelectorType = {}));

// node_modules/@aws-sdk/middleware-flexible-checksums/dist-es/types.js
var CLIENT_SUPPORTED_ALGORITHMS = [ChecksumAlgorithm.CRC32, ChecksumAlgorithm.CRC32C, ChecksumAlgorithm.SHA1, ChecksumAlgorithm.SHA256];
var PRIORITY_ORDER_ALGORITHMS = [ChecksumAlgorithm.SHA256, ChecksumAlgorithm.SHA1, ChecksumAlgorithm.CRC32, ChecksumAlgorithm.CRC32C];

// node_modules/@aws-sdk/middleware-flexible-checksums/dist-es/getChecksumAlgorithmForRequest.js
var getChecksumAlgorithmForRequest = (input, {
    requestChecksumRequired,
    requestAlgorithmMember
}, isS3Express) => {
    const defaultAlgorithm = isS3Express ? S3_EXPRESS_DEFAULT_CHECKSUM_ALGORITHM : DEFAULT_CHECKSUM_ALGORITHM;
    if (!requestAlgorithmMember || !input[requestAlgorithmMember]) {
        return requestChecksumRequired ? defaultAlgorithm : void 0;
    }
    const checksumAlgorithm = input[requestAlgorithmMember];
    if (!CLIENT_SUPPORTED_ALGORITHMS.includes(checksumAlgorithm)) {
        throw new Error(`The checksum algorithm "${checksumAlgorithm}" is not supported by the client. Select one of ${CLIENT_SUPPORTED_ALGORITHMS}.`);
    }
    return checksumAlgorithm;
};

// node_modules/@aws-sdk/middleware-flexible-checksums/dist-es/getChecksumLocationName.js
var getChecksumLocationName = (algorithm) => algorithm === ChecksumAlgorithm.MD5 ? "content-md5" : `x-amz-checksum-${algorithm.toLowerCase()}`;

// node_modules/@aws-sdk/middleware-flexible-checksums/dist-es/hasHeader.js
var hasHeader = (header, headers) => {
    const soughtHeader = header.toLowerCase();
    for (const headerName of Object.keys(headers)) {
        if (soughtHeader === headerName.toLowerCase()) {
            return true;
        }
    }
    return false;
};

// node_modules/@aws-sdk/middleware-flexible-checksums/dist-es/isStreaming.js
var isStreaming = (body) => body !== void 0 && typeof body !== "string" && !ArrayBuffer.isView(body) && !isArrayBuffer(body);

// node_modules/@aws-crypto/crc32c/build/module/aws_crc32c.js
var AwsCrc32c = (
    /** @class */
    function () {
        function AwsCrc32c2() {
            this.crc32c = new Crc32c();
        }

        AwsCrc32c2.prototype.update = function (toHash) {
            if (isEmptyData(toHash)) return;
            this.crc32c.update(convertToBuffer(toHash));
        };
        AwsCrc32c2.prototype.digest = function () {
            return __awaiter(this, void 0, void 0, function () {
                return __generator(this, function (_a) {
                    return [2, numToUint8(this.crc32c.digest())];
                });
            });
        };
        AwsCrc32c2.prototype.reset = function () {
            this.crc32c = new Crc32c();
        };
        return AwsCrc32c2;
    }()
);

// node_modules/@aws-crypto/crc32c/build/module/index.js
var Crc32c = (
    /** @class */
    function () {
        function Crc32c2() {
            this.checksum = 4294967295;
        }

        Crc32c2.prototype.update = function (data) {
            var e_1, _a;
            try {
                for (var data_1 = __values(data), data_1_1 = data_1.next(); !data_1_1.done; data_1_1 = data_1.next()) {
                    var byte = data_1_1.value;
                    this.checksum = this.checksum >>> 8 ^ lookupTable[(this.checksum ^ byte) & 255];
                }
            } catch (e_1_1) {
                e_1 = {
                    error: e_1_1
                };
            } finally {
                try {
                    if (data_1_1 && !data_1_1.done && (_a = data_1.return)) _a.call(data_1);
                } finally {
                    if (e_1) throw e_1.error;
                }
            }
            return this;
        };
        Crc32c2.prototype.digest = function () {
            return (this.checksum ^ 4294967295) >>> 0;
        };
        return Crc32c2;
    }()
);
var a_lookupTable = [0, 4067132163, 3778769143, 324072436, 3348797215, 904991772, 648144872, 3570033899, 2329499855, 2024987596, 1809983544, 2575936315, 1296289744, 3207089363, 2893594407, 1578318884, 274646895, 3795141740, 4049975192, 51262619, 3619967088, 632279923, 922689671, 3298075524, 2592579488, 1760304291, 2075979607, 2312596564, 1562183871, 2943781820, 3156637768, 1313733451, 549293790, 3537243613, 3246849577, 871202090, 3878099393, 357341890, 102525238, 4101499445, 2858735121, 1477399826, 1264559846, 3107202533, 1845379342, 2677391885, 2361733625, 2125378298, 820201905, 3263744690, 3520608582, 598981189, 4151959214, 85089709, 373468761, 3827903834, 3124367742, 1213305469, 1526817161, 2842354314, 2107672161, 2412447074, 2627466902, 1861252501, 1098587580, 3004210879, 2688576843, 1378610760, 2262928035, 1955203488, 1742404180, 2511436119, 3416409459, 969524848, 714683780, 3639785095, 205050476, 4266873199, 3976438427, 526918040, 1361435347, 2739821008, 2954799652, 1114974503, 2529119692, 1691668175, 2005155131, 2247081528, 3690758684, 697762079, 986182379, 3366744552, 476452099, 3993867776, 4250756596, 255256311, 1640403810, 2477592673, 2164122517, 1922457750, 2791048317, 1412925310, 1197962378, 3037525897, 3944729517, 427051182, 170179418, 4165941337, 746937522, 3740196785, 3451792453, 1070968646, 1905808397, 2213795598, 2426610938, 1657317369, 3053634322, 1147748369, 1463399397, 2773627110, 4215344322, 153784257, 444234805, 3893493558, 1021025245, 3467647198, 3722505002, 797665321, 2197175160, 1889384571, 1674398607, 2443626636, 1164749927, 3070701412, 2757221520, 1446797203, 137323447, 4198817972, 3910406976, 461344835, 3484808360, 1037989803, 781091935, 3705997148, 2460548119, 1623424788, 1939049696, 2180517859, 1429367560, 2807687179, 3020495871, 1180866812, 410100952, 3927582683, 4182430767, 186734380, 3756733383, 763408580, 1053836080, 3434856499, 2722870694, 1344288421, 1131464017, 2971354706, 1708204729, 2545590714, 2229949006, 1988219213, 680717673, 3673779818, 3383336350, 1002577565, 4010310262, 493091189, 238226049, 4233660802, 2987750089, 1082061258, 1395524158, 2705686845, 1972364758, 2279892693, 2494862625, 1725896226, 952904198, 3399985413, 3656866545, 731699698, 4283874585, 222117402, 510512622, 3959836397, 3280807620, 837199303, 582374963, 3504198960, 68661723, 4135334616, 3844915500, 390545967, 1230274059, 3141532936, 2825850620, 1510247935, 2395924756, 2091215383, 1878366691, 2644384480, 3553878443, 565732008, 854102364, 3229815391, 340358836, 3861050807, 4117890627, 119113024, 1493875044, 2875275879, 3090270611, 1247431312, 2660249211, 1828433272, 2141937292, 2378227087, 3811616794, 291187481, 34330861, 4032846830, 615137029, 3603020806, 3314634738, 939183345, 1776939221, 2609017814, 2295496738, 2058945313, 2926798794, 1545135305, 1330124605, 3173225534, 4084100981, 17165430, 307568514, 3762199681, 888469610, 3332340585, 3587147933, 665062302, 2042050490, 2346497209, 2559330125, 1793573966, 3190661285, 1279665062, 1595330642, 2910671697];
var lookupTable = uint32ArrayFrom(a_lookupTable);

// node_modules/@aws-sdk/middleware-flexible-checksums/dist-es/getCrc32ChecksumAlgorithmFunction.browser.js
var getCrc32ChecksumAlgorithmFunction = () => AwsCrc32;

// node_modules/@aws-sdk/middleware-flexible-checksums/dist-es/selectChecksumAlgorithmFunction.js
var selectChecksumAlgorithmFunction = (checksumAlgorithm, config) => ({
    [ChecksumAlgorithm.MD5]: config.md5,
    [ChecksumAlgorithm.CRC32]: getCrc32ChecksumAlgorithmFunction(),
    [ChecksumAlgorithm.CRC32C]: AwsCrc32c,
    [ChecksumAlgorithm.SHA1]: config.sha1,
    [ChecksumAlgorithm.SHA256]: config.sha256
})[checksumAlgorithm];

// node_modules/@aws-sdk/middleware-flexible-checksums/dist-es/stringHasher.js
var stringHasher = (checksumAlgorithmFn, body) => {
    const hash = new checksumAlgorithmFn();
    hash.update(toUint8Array(body || ""));
    return hash.digest();
};

// node_modules/@aws-sdk/middleware-flexible-checksums/dist-es/flexibleChecksumsMiddleware.js
var flexibleChecksumsMiddlewareOptions = {
    name: "flexibleChecksumsMiddleware",
    step: "build",
    tags: ["BODY_CHECKSUM"],
    override: true
};
var flexibleChecksumsMiddleware = (config, middlewareConfig) => (next, context) => (args) => __async(void 0, null, function* () {
    if (!HttpRequest.isInstance(args.request)) {
        return next(args);
    }
    const {
        request
    } = args;
    const {
        body: requestBody,
        headers
    } = request;
    const {
        base64Encoder,
        streamHasher
    } = config;
    const {
        input,
        requestChecksumRequired,
        requestAlgorithmMember
    } = middlewareConfig;
    const checksumAlgorithm = getChecksumAlgorithmForRequest(input, {
        requestChecksumRequired,
        requestAlgorithmMember
    }, !!context.isS3ExpressBucket);
    let updatedBody = requestBody;
    let updatedHeaders = headers;
    if (checksumAlgorithm) {
        switch (checksumAlgorithm) {
            case ChecksumAlgorithm.CRC32:
                setFeature(context, "FLEXIBLE_CHECKSUMS_REQ_CRC32", "U");
                break;
            case ChecksumAlgorithm.CRC32C:
                setFeature(context, "FLEXIBLE_CHECKSUMS_REQ_CRC32C", "V");
                break;
            case ChecksumAlgorithm.SHA1:
                setFeature(context, "FLEXIBLE_CHECKSUMS_REQ_SHA1", "X");
                break;
            case ChecksumAlgorithm.SHA256:
                setFeature(context, "FLEXIBLE_CHECKSUMS_REQ_SHA256", "Y");
                break;
        }
        const checksumLocationName = getChecksumLocationName(checksumAlgorithm);
        const checksumAlgorithmFn = selectChecksumAlgorithmFunction(checksumAlgorithm, config);
        if (isStreaming(requestBody)) {
            const {
                getAwsChunkedEncodingStream: getAwsChunkedEncodingStream2,
                bodyLengthChecker
            } = config;
            updatedBody = getAwsChunkedEncodingStream2(requestBody, {
                base64Encoder,
                bodyLengthChecker,
                checksumLocationName,
                checksumAlgorithmFn,
                streamHasher
            });
            updatedHeaders = __spreadProps(__spreadValues({}, headers), {
                "content-encoding": headers["content-encoding"] ? `${headers["content-encoding"]},aws-chunked` : "aws-chunked",
                "transfer-encoding": "chunked",
                "x-amz-decoded-content-length": headers["content-length"],
                "x-amz-content-sha256": "STREAMING-UNSIGNED-PAYLOAD-TRAILER",
                "x-amz-trailer": checksumLocationName
            });
            delete updatedHeaders["content-length"];
        } else if (!hasHeader(checksumLocationName, headers)) {
            const rawChecksum = yield stringHasher(checksumAlgorithmFn, requestBody);
            updatedHeaders = __spreadProps(__spreadValues({}, headers), {
                [checksumLocationName]: base64Encoder(rawChecksum)
            });
        }
    }
    const result = yield next(__spreadProps(__spreadValues({}, args), {
        request: __spreadProps(__spreadValues({}, request), {
            headers: updatedHeaders,
            body: updatedBody
        })
    }));
    return result;
});

// node_modules/@aws-sdk/middleware-flexible-checksums/dist-es/getChecksumAlgorithmListForResponse.js
var getChecksumAlgorithmListForResponse = (responseAlgorithms = []) => {
    const validChecksumAlgorithms = [];
    for (const algorithm of PRIORITY_ORDER_ALGORITHMS) {
        if (!responseAlgorithms.includes(algorithm) || !CLIENT_SUPPORTED_ALGORITHMS.includes(algorithm)) {
            continue;
        }
        validChecksumAlgorithms.push(algorithm);
    }
    return validChecksumAlgorithms;
};

// node_modules/@aws-sdk/middleware-flexible-checksums/dist-es/isChecksumWithPartNumber.js
var isChecksumWithPartNumber = (checksum) => {
    const lastHyphenIndex = checksum.lastIndexOf("-");
    if (lastHyphenIndex !== -1) {
        const numberPart = checksum.slice(lastHyphenIndex + 1);
        if (!numberPart.startsWith("0")) {
            const number = parseInt(numberPart, 10);
            if (!isNaN(number) && number >= 1 && number <= 1e4) {
                return true;
            }
        }
    }
    return false;
};

// node_modules/@aws-sdk/middleware-flexible-checksums/dist-es/streams/create-read-stream-on-buffer.browser.js
function createReadStreamOnBuffer(buffer) {
    return new Blob([buffer]).stream();
}

// node_modules/@aws-sdk/middleware-flexible-checksums/dist-es/getChecksum.js
var getChecksum = (_0, _1) => __async(void 0, [_0, _1], function* (body, {
    checksumAlgorithmFn,
    base64Encoder
}) {
    return base64Encoder(yield stringHasher(checksumAlgorithmFn, body));
});

// node_modules/@aws-sdk/middleware-flexible-checksums/dist-es/validateChecksumFromResponse.js
var validateChecksumFromResponse = (_0, _1) => __async(void 0, [_0, _1], function* (response, {
    config,
    responseAlgorithms
}) {
    const checksumAlgorithms = getChecksumAlgorithmListForResponse(responseAlgorithms);
    const {
        body: responseBody,
        headers: responseHeaders
    } = response;
    for (const algorithm of checksumAlgorithms) {
        const responseHeader = getChecksumLocationName(algorithm);
        const checksumFromResponse = responseHeaders[responseHeader];
        if (checksumFromResponse) {
            const checksumAlgorithmFn = selectChecksumAlgorithmFunction(algorithm, config);
            const {
                base64Encoder
            } = config;
            if (isStreaming(responseBody)) {
                response.body = createChecksumStream({
                    expectedChecksum: checksumFromResponse,
                    checksumSourceLocation: responseHeader,
                    checksum: new checksumAlgorithmFn(),
                    source: responseBody,
                    base64Encoder
                });
                return;
            }
            const checksum = yield getChecksum(responseBody, {
                checksumAlgorithmFn,
                base64Encoder
            });
            if (checksum === checksumFromResponse) {
                break;
            }
            throw new Error(`Checksum mismatch: expected "${checksum}" but received "${checksumFromResponse}" in response header "${responseHeader}".`);
        }
    }
});

// node_modules/@aws-sdk/middleware-flexible-checksums/dist-es/flexibleChecksumsResponseMiddleware.js
var flexibleChecksumsResponseMiddlewareOptions = {
    name: "flexibleChecksumsResponseMiddleware",
    toMiddleware: "deserializerMiddleware",
    relation: "after",
    tags: ["BODY_CHECKSUM"],
    override: true
};
var flexibleChecksumsResponseMiddleware = (config, middlewareConfig) => (next, context) => (args) => __async(void 0, null, function* () {
    if (!HttpRequest.isInstance(args.request)) {
        return next(args);
    }
    const input = args.input;
    const result = yield next(args);
    const response = result.response;
    let collectedStream = void 0;
    const {
        requestValidationModeMember,
        responseAlgorithms
    } = middlewareConfig;
    if (requestValidationModeMember && input[requestValidationModeMember] === "ENABLED") {
        const {
            clientName,
            commandName
        } = context;
        const isS3WholeObjectMultipartGetResponseChecksum = clientName === "S3Client" && commandName === "GetObjectCommand" && getChecksumAlgorithmListForResponse(responseAlgorithms).every((algorithm) => {
            const responseHeader = getChecksumLocationName(algorithm);
            const checksumFromResponse = response.headers[responseHeader];
            return !checksumFromResponse || isChecksumWithPartNumber(checksumFromResponse);
        });
        if (isS3WholeObjectMultipartGetResponseChecksum) {
            return result;
        }
        const isStreamingBody = isStreaming(response.body);
        if (isStreamingBody) {
            collectedStream = yield config.streamCollector(response.body);
            response.body = createReadStreamOnBuffer(collectedStream);
        }
        yield validateChecksumFromResponse(result.response, {
            config,
            responseAlgorithms
        });
        if (isStreamingBody && collectedStream) {
            response.body = createReadStreamOnBuffer(collectedStream);
        }
    }
    return result;
});

// node_modules/@aws-sdk/middleware-flexible-checksums/dist-es/getFlexibleChecksumsPlugin.js
var getFlexibleChecksumsPlugin = (config, middlewareConfig) => ({
    applyToStack: (clientStack) => {
        clientStack.add(flexibleChecksumsMiddleware(config, middlewareConfig), flexibleChecksumsMiddlewareOptions);
        clientStack.addRelativeTo(flexibleChecksumsResponseMiddleware(config, middlewareConfig), flexibleChecksumsResponseMiddlewareOptions);
    }
});

// node_modules/@aws-sdk/middleware-flexible-checksums/dist-es/resolveFlexibleChecksumsConfig.js
var resolveFlexibleChecksumsConfig = (input) => __spreadProps(__spreadValues({}, input), {
    requestChecksumCalculation: normalizeProvider(input.requestChecksumCalculation ?? DEFAULT_REQUEST_CHECKSUM_CALCULATION),
    responseChecksumValidation: normalizeProvider(input.responseChecksumValidation ?? DEFAULT_RESPONSE_CHECKSUM_VALIDATION)
});

// node_modules/@aws-sdk/middleware-sdk-s3/dist-es/check-content-length-header.js
var CONTENT_LENGTH_HEADER = "content-length";

function checkContentLengthHeader() {
    return (next, context) => (args) => __async(this, null, function* () {
        const {
            request
        } = args;
        if (HttpRequest.isInstance(request)) {
            if (!(CONTENT_LENGTH_HEADER in request.headers)) {
                const message = `Are you using a Stream of unknown length as the Body of a PutObject request? Consider using Upload instead from @aws-sdk/lib-storage.`;
                if (typeof context?.logger?.warn === "function" && !(context.logger instanceof NoOpLogger)) {
                    context.logger.warn(message);
                } else {
                    console.warn(message);
                }
            }
        }
        return next(__spreadValues({}, args));
    });
}

var checkContentLengthHeaderMiddlewareOptions = {
    step: "finalizeRequest",
    tags: ["CHECK_CONTENT_LENGTH_HEADER"],
    name: "getCheckContentLengthHeaderPlugin",
    override: true
};
var getCheckContentLengthHeaderPlugin = (unused) => ({
    applyToStack: (clientStack) => {
        clientStack.add(checkContentLengthHeader(), checkContentLengthHeaderMiddlewareOptions);
    }
});

// node_modules/@aws-sdk/middleware-sdk-s3/dist-es/region-redirect-endpoint-middleware.js
var regionRedirectEndpointMiddleware = (config) => {
    return (next, context) => (args) => __async(void 0, null, function* () {
        const originalRegion = yield config.region();
        const regionProviderRef = config.region;
        let unlock = () => {
        };
        if (context.__s3RegionRedirect) {
            Object.defineProperty(config, "region", {
                writable: false,
                value: () => __async(void 0, null, function* () {
                    return context.__s3RegionRedirect;
                })
            });
            unlock = () => Object.defineProperty(config, "region", {
                writable: true,
                value: regionProviderRef
            });
        }
        try {
            const result = yield next(args);
            if (context.__s3RegionRedirect) {
                unlock();
                const region = yield config.region();
                if (originalRegion !== region) {
                    throw new Error("Region was not restored following S3 region redirect.");
                }
            }
            return result;
        } catch (e2) {
            unlock();
            throw e2;
        }
    });
};
var regionRedirectEndpointMiddlewareOptions = {
    tags: ["REGION_REDIRECT", "S3"],
    name: "regionRedirectEndpointMiddleware",
    override: true,
    relation: "before",
    toMiddleware: "endpointV2Middleware"
};

// node_modules/@aws-sdk/middleware-sdk-s3/dist-es/region-redirect-middleware.js
function regionRedirectMiddleware(clientConfig) {
    return (next, context) => (args) => __async(this, null, function* () {
        try {
            return yield next(args);
        } catch (err) {
            if (clientConfig.followRegionRedirects) {
                if (err?.$metadata?.httpStatusCode === 301 || err?.$metadata?.httpStatusCode === 400 && err?.name === "IllegalLocationConstraintException") {
                    try {
                        const actualRegion = err.$response.headers["x-amz-bucket-region"];
                        context.logger?.debug(`Redirecting from ${yield clientConfig.region()} to ${actualRegion}`);
                        context.__s3RegionRedirect = actualRegion;
                    } catch (e2) {
                        throw new Error("Region redirect failed: " + e2);
                    }
                    return next(args);
                }
            }
            throw err;
        }
    });
}

var regionRedirectMiddlewareOptions = {
    step: "initialize",
    tags: ["REGION_REDIRECT", "S3"],
    name: "regionRedirectMiddleware",
    override: true
};
var getRegionRedirectMiddlewarePlugin = (clientConfig) => ({
    applyToStack: (clientStack) => {
        clientStack.add(regionRedirectMiddleware(clientConfig), regionRedirectMiddlewareOptions);
        clientStack.addRelativeTo(regionRedirectEndpointMiddleware(clientConfig), regionRedirectEndpointMiddlewareOptions);
    }
});

// node_modules/@aws-sdk/middleware-sdk-s3/dist-es/s3-expires-middleware.js
var s3ExpiresMiddleware = (config) => {
    return (next, context) => (args) => __async(void 0, null, function* () {
        const result = yield next(args);
        const {
            response
        } = result;
        if (HttpResponse.isInstance(response)) {
            if (response.headers.expires) {
                response.headers.expiresstring = response.headers.expires;
                try {
                    parseRfc7231DateTime(response.headers.expires);
                } catch (e2) {
                    context.logger?.warn(`AWS SDK Warning for ${context.clientName}::${context.commandName} response parsing (${response.headers.expires}): ${e2}`);
                    delete response.headers.expires;
                }
            }
        }
        return result;
    });
};
var s3ExpiresMiddlewareOptions = {
    tags: ["S3"],
    name: "s3ExpiresMiddleware",
    override: true,
    relation: "after",
    toMiddleware: "deserializerMiddleware"
};
var getS3ExpiresMiddlewarePlugin = (clientConfig) => ({
    applyToStack: (clientStack) => {
        clientStack.addRelativeTo(s3ExpiresMiddleware(clientConfig), s3ExpiresMiddlewareOptions);
    }
});

// node_modules/@aws-sdk/middleware-sdk-s3/dist-es/s3-express/classes/S3ExpressIdentityCache.js
var S3ExpressIdentityCache = class _S3ExpressIdentityCache {
    constructor(data = {}) {
        this.data = data;
        this.lastPurgeTime = Date.now();
    }

    get(key) {
        const entry = this.data[key];
        if (!entry) {
            return;
        }
        return entry;
    }

    set(key, entry) {
        this.data[key] = entry;
        return entry;
    }

    delete(key) {
        delete this.data[key];
    }

    purgeExpired() {
        return __async(this, null, function* () {
            const now = Date.now();
            if (this.lastPurgeTime + _S3ExpressIdentityCache.EXPIRED_CREDENTIAL_PURGE_INTERVAL_MS > now) {
                return;
            }
            for (const key in this.data) {
                const entry = this.data[key];
                if (!entry.isRefreshing) {
                    const credential = yield entry.identity;
                    if (credential.expiration) {
                        if (credential.expiration.getTime() < now) {
                            delete this.data[key];
                        }
                    }
                }
            }
        });
    }
};
S3ExpressIdentityCache.EXPIRED_CREDENTIAL_PURGE_INTERVAL_MS = 3e4;

// node_modules/@aws-sdk/middleware-sdk-s3/dist-es/s3-express/classes/S3ExpressIdentityCacheEntry.js
var S3ExpressIdentityCacheEntry = class {
    constructor(_identity, isRefreshing = false, accessed = Date.now()) {
        this._identity = _identity;
        this.isRefreshing = isRefreshing;
        this.accessed = accessed;
    }

    get identity() {
        this.accessed = Date.now();
        return this._identity;
    }
};

// node_modules/@aws-sdk/middleware-sdk-s3/dist-es/s3-express/classes/S3ExpressIdentityProviderImpl.js
var S3ExpressIdentityProviderImpl = class _S3ExpressIdentityProviderImpl {
    constructor(createSessionFn, cache2 = new S3ExpressIdentityCache()) {
        this.createSessionFn = createSessionFn;
        this.cache = cache2;
    }

    getS3ExpressIdentity(awsIdentity, identityProperties) {
        return __async(this, null, function* () {
            const key = identityProperties.Bucket;
            const {
                cache: cache2
            } = this;
            const entry = cache2.get(key);
            if (entry) {
                return entry.identity.then((identity) => {
                    const isExpired = (identity.expiration?.getTime() ?? 0) < Date.now();
                    if (isExpired) {
                        return cache2.set(key, new S3ExpressIdentityCacheEntry(this.getIdentity(key))).identity;
                    }
                    const isExpiringSoon = (identity.expiration?.getTime() ?? 0) < Date.now() + _S3ExpressIdentityProviderImpl.REFRESH_WINDOW_MS;
                    if (isExpiringSoon && !entry.isRefreshing) {
                        entry.isRefreshing = true;
                        this.getIdentity(key).then((id) => {
                            cache2.set(key, new S3ExpressIdentityCacheEntry(Promise.resolve(id)));
                        });
                    }
                    return identity;
                });
            }
            return cache2.set(key, new S3ExpressIdentityCacheEntry(this.getIdentity(key))).identity;
        });
    }

    getIdentity(key) {
        return __async(this, null, function* () {
            yield this.cache.purgeExpired().catch((error) => {
                console.warn("Error while clearing expired entries in S3ExpressIdentityCache: \n" + error);
            });
            const session = yield this.createSessionFn(key);
            if (!session.Credentials?.AccessKeyId || !session.Credentials?.SecretAccessKey) {
                throw new Error("s3#createSession response credential missing AccessKeyId or SecretAccessKey.");
            }
            const identity = {
                accessKeyId: session.Credentials.AccessKeyId,
                secretAccessKey: session.Credentials.SecretAccessKey,
                sessionToken: session.Credentials.SessionToken,
                expiration: session.Credentials.Expiration ? new Date(session.Credentials.Expiration) : void 0
            };
            return identity;
        });
    }
};
S3ExpressIdentityProviderImpl.REFRESH_WINDOW_MS = 6e4;

// node_modules/@aws-sdk/middleware-sdk-s3/dist-es/s3-express/constants.js
var S3_EXPRESS_BUCKET_TYPE = "Directory";
var S3_EXPRESS_BACKEND = "S3Express";
var S3_EXPRESS_AUTH_SCHEME = "sigv4-s3express";
var SESSION_TOKEN_QUERY_PARAM = "X-Amz-S3session-Token";
var SESSION_TOKEN_HEADER = SESSION_TOKEN_QUERY_PARAM.toLowerCase();

// node_modules/@aws-sdk/middleware-sdk-s3/dist-es/s3-express/classes/SignatureV4S3Express.js
var SignatureV4S3Express = class extends SignatureV4 {
    signWithCredentials(requestToSign, credentials, options) {
        return __async(this, null, function* () {
            const credentialsWithoutSessionToken = getCredentialsWithoutSessionToken(credentials);
            requestToSign.headers[SESSION_TOKEN_HEADER] = credentials.sessionToken;
            const privateAccess = this;
            setSingleOverride(privateAccess, credentialsWithoutSessionToken);
            return privateAccess.signRequest(requestToSign, options ?? {});
        });
    }

    presignWithCredentials(requestToSign, credentials, options) {
        return __async(this, null, function* () {
            const credentialsWithoutSessionToken = getCredentialsWithoutSessionToken(credentials);
            delete requestToSign.headers[SESSION_TOKEN_HEADER];
            requestToSign.headers[SESSION_TOKEN_QUERY_PARAM] = credentials.sessionToken;
            requestToSign.query = requestToSign.query ?? {};
            requestToSign.query[SESSION_TOKEN_QUERY_PARAM] = credentials.sessionToken;
            const privateAccess = this;
            setSingleOverride(privateAccess, credentialsWithoutSessionToken);
            return this.presign(requestToSign, options);
        });
    }
};

function getCredentialsWithoutSessionToken(credentials) {
    const credentialsWithoutSessionToken = {
        accessKeyId: credentials.accessKeyId,
        secretAccessKey: credentials.secretAccessKey,
        expiration: credentials.expiration
    };
    return credentialsWithoutSessionToken;
}

function setSingleOverride(privateAccess, credentialsWithoutSessionToken) {
    const id = setTimeout(() => {
        throw new Error("SignatureV4S3Express credential override was created but not called.");
    }, 10);
    const currentCredentialProvider = privateAccess.credentialProvider;
    const overrideCredentialsProviderOnce = () => {
        clearTimeout(id);
        privateAccess.credentialProvider = currentCredentialProvider;
        return Promise.resolve(credentialsWithoutSessionToken);
    };
    privateAccess.credentialProvider = overrideCredentialsProviderOnce;
}

// node_modules/@aws-sdk/middleware-sdk-s3/dist-es/s3-express/functions/s3ExpressMiddleware.js
var s3ExpressMiddleware = (options) => {
    return (next, context) => (args) => __async(void 0, null, function* () {
        if (context.endpointV2) {
            const endpoint = context.endpointV2;
            const isS3ExpressAuth = endpoint.properties?.authSchemes?.[0]?.name === S3_EXPRESS_AUTH_SCHEME;
            const isS3ExpressBucket = endpoint.properties?.backend === S3_EXPRESS_BACKEND || endpoint.properties?.bucketType === S3_EXPRESS_BUCKET_TYPE;
            if (isS3ExpressBucket) {
                setFeature(context, "S3_EXPRESS_BUCKET", "J");
                context.isS3ExpressBucket = true;
            }
            if (isS3ExpressAuth) {
                const requestBucket = args.input.Bucket;
                if (requestBucket) {
                    const s3ExpressIdentity = yield options.s3ExpressIdentityProvider.getS3ExpressIdentity(yield options.credentials(), {
                        Bucket: requestBucket
                    });
                    context.s3ExpressIdentity = s3ExpressIdentity;
                    if (HttpRequest.isInstance(args.request) && s3ExpressIdentity.sessionToken) {
                        args.request.headers[SESSION_TOKEN_HEADER] = s3ExpressIdentity.sessionToken;
                    }
                }
            }
        }
        return next(args);
    });
};
var s3ExpressMiddlewareOptions = {
    name: "s3ExpressMiddleware",
    step: "build",
    tags: ["S3", "S3_EXPRESS"],
    override: true
};
var getS3ExpressPlugin = (options) => ({
    applyToStack: (clientStack) => {
        clientStack.add(s3ExpressMiddleware(options), s3ExpressMiddlewareOptions);
    }
});

// node_modules/@aws-sdk/middleware-sdk-s3/dist-es/s3-express/functions/signS3Express.js
var signS3Express = (s3ExpressIdentity, signingOptions, request, sigV4MultiRegionSigner) => __async(void 0, null, function* () {
    const signedRequest = yield sigV4MultiRegionSigner.signWithCredentials(request, s3ExpressIdentity, {});
    if (signedRequest.headers["X-Amz-Security-Token"] || signedRequest.headers["x-amz-security-token"]) {
        throw new Error("X-Amz-Security-Token must not be set for s3-express requests.");
    }
    return signedRequest;
});

// node_modules/@aws-sdk/middleware-sdk-s3/dist-es/s3-express/functions/s3ExpressHttpSigningMiddleware.js
var defaultErrorHandler = (signingProperties) => (error) => {
    throw error;
};
var defaultSuccessHandler = (httpResponse, signingProperties) => {
};
var s3ExpressHttpSigningMiddleware = (config) => (next, context) => (args) => __async(void 0, null, function* () {
    if (!HttpRequest.isInstance(args.request)) {
        return next(args);
    }
    const smithyContext = getSmithyContext(context);
    const scheme = smithyContext.selectedHttpAuthScheme;
    if (!scheme) {
        throw new Error(`No HttpAuthScheme was selected: unable to sign request`);
    }
    const {
        httpAuthOption: {
            signingProperties = {}
        },
        identity,
        signer
    } = scheme;
    let request;
    if (context.s3ExpressIdentity) {
        request = yield signS3Express(context.s3ExpressIdentity, signingProperties, args.request, yield config.signer());
    } else {
        request = yield signer.sign(args.request, identity, signingProperties);
    }
    const output = yield next(__spreadProps(__spreadValues({}, args), {
        request
    })).catch((signer.errorHandler || defaultErrorHandler)(signingProperties));
    (signer.successHandler || defaultSuccessHandler)(output.response, signingProperties);
    return output;
});
var getS3ExpressHttpSigningPlugin = (config) => ({
    applyToStack: (clientStack) => {
        clientStack.addRelativeTo(s3ExpressHttpSigningMiddleware(config), httpSigningMiddlewareOptions);
    }
});

// node_modules/@aws-sdk/middleware-sdk-s3/dist-es/s3Configuration.js
var resolveS3Config = (input, {
    session
}) => {
    const [s3ClientProvider, CreateSessionCommandCtor] = session;
    return __spreadProps(__spreadValues({}, input), {
        forcePathStyle: input.forcePathStyle ?? false,
        useAccelerateEndpoint: input.useAccelerateEndpoint ?? false,
        disableMultiregionAccessPoints: input.disableMultiregionAccessPoints ?? false,
        followRegionRedirects: input.followRegionRedirects ?? false,
        s3ExpressIdentityProvider: input.s3ExpressIdentityProvider ?? new S3ExpressIdentityProviderImpl((key) => __async(void 0, null, function* () {
            return s3ClientProvider().send(new CreateSessionCommandCtor({
                Bucket: key,
                SessionMode: "ReadWrite"
            }));
        })),
        bucketEndpoint: input.bucketEndpoint ?? false
    });
};

// node_modules/@aws-sdk/middleware-sdk-s3/dist-es/throw-200-exceptions.js
var THROW_IF_EMPTY_BODY = {
    CopyObjectCommand: true,
    UploadPartCopyCommand: true,
    CompleteMultipartUploadCommand: true
};
var MAX_BYTES_TO_INSPECT = 3e3;
var throw200ExceptionsMiddleware = (config) => (next, context) => (args) => __async(void 0, null, function* () {
    const result = yield next(args);
    const {
        response
    } = result;
    if (!HttpResponse.isInstance(response)) {
        return result;
    }
    const {
        statusCode,
        body: sourceBody
    } = response;
    if (statusCode < 200 || statusCode >= 300) {
        return result;
    }
    const isSplittableStream = typeof sourceBody?.stream === "function" || typeof sourceBody?.pipe === "function" || typeof sourceBody?.tee === "function";
    if (!isSplittableStream) {
        return result;
    }
    let bodyCopy = sourceBody;
    let body = sourceBody;
    if (sourceBody && typeof sourceBody === "object" && !(sourceBody instanceof Uint8Array)) {
        [bodyCopy, body] = yield splitStream(sourceBody);
    }
    response.body = body;
    const bodyBytes = yield collectBody2(bodyCopy, {
        streamCollector: (stream) => __async(void 0, null, function* () {
            return headStream(stream, MAX_BYTES_TO_INSPECT);
        })
    });
    if (typeof bodyCopy?.destroy === "function") {
        bodyCopy.destroy();
    }
    const bodyStringTail = config.utf8Encoder(bodyBytes.subarray(bodyBytes.length - 16));
    if (bodyBytes.length === 0 && THROW_IF_EMPTY_BODY[context.commandName]) {
        const err = new Error("S3 aborted request");
        err.name = "InternalError";
        throw err;
    }
    if (bodyStringTail && bodyStringTail.endsWith("</Error>")) {
        response.statusCode = 400;
    }
    return result;
});
var collectBody2 = (streamBody = new Uint8Array(), context) => {
    if (streamBody instanceof Uint8Array) {
        return Promise.resolve(streamBody);
    }
    return context.streamCollector(streamBody) || Promise.resolve(new Uint8Array());
};
var throw200ExceptionsMiddlewareOptions = {
    relation: "after",
    toMiddleware: "deserializerMiddleware",
    tags: ["THROW_200_EXCEPTIONS", "S3"],
    name: "throw200ExceptionsMiddleware",
    override: true
};
var getThrow200ExceptionsPlugin = (config) => ({
    applyToStack: (clientStack) => {
        clientStack.addRelativeTo(throw200ExceptionsMiddleware(config), throw200ExceptionsMiddlewareOptions);
    }
});

// node_modules/@aws-sdk/util-arn-parser/dist-es/index.js
var validate = (str) => typeof str === "string" && str.indexOf("arn:") === 0 && str.split(":").length >= 6;

// node_modules/@aws-sdk/middleware-sdk-s3/dist-es/bucket-endpoint-middleware.js
function bucketEndpointMiddleware(options) {
    return (next, context) => (args) => __async(this, null, function* () {
        if (options.bucketEndpoint) {
            const endpoint = context.endpointV2;
            if (endpoint) {
                const bucket = args.input.Bucket;
                if (typeof bucket === "string") {
                    try {
                        const bucketEndpointUrl = new URL(bucket);
                        context.endpointV2 = __spreadProps(__spreadValues({}, endpoint), {
                            url: bucketEndpointUrl
                        });
                    } catch (e2) {
                        const warning = `@aws-sdk/middleware-sdk-s3: bucketEndpoint=true was set but Bucket=${bucket} could not be parsed as URL.`;
                        if (context.logger?.constructor?.name === "NoOpLogger") {
                            console.warn(warning);
                        } else {
                            context.logger?.warn?.(warning);
                        }
                        throw e2;
                    }
                }
            }
        }
        return next(args);
    });
}

var bucketEndpointMiddlewareOptions = {
    name: "bucketEndpointMiddleware",
    override: true,
    relation: "after",
    toMiddleware: "endpointV2Middleware"
};

// node_modules/@aws-sdk/middleware-sdk-s3/dist-es/validate-bucket-name.js
function validateBucketNameMiddleware({
                                          bucketEndpoint
                                      }) {
    return (next) => (args) => __async(this, null, function* () {
        const {
            input: {
                Bucket
            }
        } = args;
        if (!bucketEndpoint && typeof Bucket === "string" && !validate(Bucket) && Bucket.indexOf("/") >= 0) {
            const err = new Error(`Bucket name shouldn't contain '/', received '${Bucket}'`);
            err.name = "InvalidBucketName";
            throw err;
        }
        return next(__spreadValues({}, args));
    });
}

var validateBucketNameMiddlewareOptions = {
    step: "initialize",
    tags: ["VALIDATE_BUCKET_NAME"],
    name: "validateBucketNameMiddleware",
    override: true
};
var getValidateBucketNamePlugin = (options) => ({
    applyToStack: (clientStack) => {
        clientStack.add(validateBucketNameMiddleware(options), validateBucketNameMiddlewareOptions);
        clientStack.addRelativeTo(bucketEndpointMiddleware(options), bucketEndpointMiddlewareOptions);
    }
});

// node_modules/@aws-sdk/signature-v4-multi-region/dist-es/signature-v4-crt-container.js
var signatureV4CrtContainer = {
    CrtSignerV4: null
};

// node_modules/@aws-sdk/signature-v4-multi-region/dist-es/SignatureV4MultiRegion.js
var SignatureV4MultiRegion = class {
    constructor(options) {
        this.sigv4Signer = new SignatureV4S3Express(options);
        this.signerOptions = options;
    }

    sign(_0) {
        return __async(this, arguments, function* (requestToSign, options = {}) {
            if (options.signingRegion === "*") {
                if (this.signerOptions.runtime !== "node") throw new Error("This request requires signing with SigV4Asymmetric algorithm. It's only available in Node.js");
                return this.getSigv4aSigner().sign(requestToSign, options);
            }
            return this.sigv4Signer.sign(requestToSign, options);
        });
    }

    signWithCredentials(_0, _1) {
        return __async(this, arguments, function* (requestToSign, credentials, options = {}) {
            if (options.signingRegion === "*") {
                if (this.signerOptions.runtime !== "node") throw new Error("This request requires signing with SigV4Asymmetric algorithm. It's only available in Node.js");
                return this.getSigv4aSigner().signWithCredentials(requestToSign, credentials, options);
            }
            return this.sigv4Signer.signWithCredentials(requestToSign, credentials, options);
        });
    }

    presign(_0) {
        return __async(this, arguments, function* (originalRequest, options = {}) {
            if (options.signingRegion === "*") {
                if (this.signerOptions.runtime !== "node") throw new Error("This request requires signing with SigV4Asymmetric algorithm. It's only available in Node.js");
                return this.getSigv4aSigner().presign(originalRequest, options);
            }
            return this.sigv4Signer.presign(originalRequest, options);
        });
    }

    presignWithCredentials(_0, _1) {
        return __async(this, arguments, function* (originalRequest, credentials, options = {}) {
            if (options.signingRegion === "*") {
                throw new Error("Method presignWithCredentials is not supported for [signingRegion=*].");
            }
            return this.sigv4Signer.presignWithCredentials(originalRequest, credentials, options);
        });
    }

    getSigv4aSigner() {
        if (!this.sigv4aSigner) {
            let CrtSignerV4 = null;
            try {
                CrtSignerV4 = signatureV4CrtContainer.CrtSignerV4;
                if (typeof CrtSignerV4 !== "function") throw new Error();
            } catch (e2) {
                e2.message = `${e2.message}
Please check whether you have installed the "@aws-sdk/signature-v4-crt" package explicitly. 
You must also register the package by calling [require("@aws-sdk/signature-v4-crt");] or an ESM equivalent such as [import "@aws-sdk/signature-v4-crt";]. 
For more information please go to https://github.com/aws/aws-sdk-js-v3#functionality-requiring-aws-common-runtime-crt`;
                throw e2;
            }
            this.sigv4aSigner = new CrtSignerV4(__spreadProps(__spreadValues({}, this.signerOptions), {
                signingAlgorithm: 1
            }));
        }
        return this.sigv4aSigner;
    }
};

// node_modules/@aws-sdk/client-s3/dist-es/endpoint/ruleset.js
var ce = "required";
var cf = "type";
var cg = "conditions";
var ch = "fn";
var ci = "argv";
var cj = "ref";
var ck = "assign";
var cl = "url";
var cm = "properties";
var cn = "backend";
var co = "authSchemes";
var cp = "disableDoubleEncoding";
var cq = "signingName";
var cr = "signingRegion";
var cs = "headers";
var ct = "signingRegionSet";
var a = false;
var b = true;
var c = "isSet";
var d = "booleanEquals";
var e = "error";
var f = "aws.partition";
var g = "stringEquals";
var h = "getAttr";
var i = "name";
var j = "substring";
var k = "bucketSuffix";
var l = "parseURL";
var m = "{url#scheme}://{url#authority}/{uri_encoded_bucket}{url#path}";
var n = "endpoint";
var o = "tree";
var p = "aws.isVirtualHostableS3Bucket";
var q = "{url#scheme}://{Bucket}.{url#authority}{url#path}";
var r = "not";
var s = "{url#scheme}://{url#authority}{url#path}";
var t = "hardwareType";
var u = "regionPrefix";
var v = "bucketAliasSuffix";
var w = "outpostId";
var x = "isValidHostLabel";
var y = "sigv4a";
var z = "s3-outposts";
var A = "s3";
var B = "{url#scheme}://{url#authority}{url#normalizedPath}{Bucket}";
var C = "https://{Bucket}.s3-accelerate.{partitionResult#dnsSuffix}";
var D = "https://{Bucket}.s3.{partitionResult#dnsSuffix}";
var E = "aws.parseArn";
var F = "bucketArn";
var G = "arnType";
var H = "";
var I = "s3-object-lambda";
var J = "accesspoint";
var K = "accessPointName";
var L = "{url#scheme}://{accessPointName}-{bucketArn#accountId}.{url#authority}{url#path}";
var M = "mrapPartition";
var N = "outpostType";
var O = "arnPrefix";
var P = "{url#scheme}://{url#authority}{url#normalizedPath}{uri_encoded_bucket}";
var Q = "https://s3.{partitionResult#dnsSuffix}/{uri_encoded_bucket}";
var R = "https://s3.{partitionResult#dnsSuffix}";
var S = {
    [ce]: false,
    [cf]: "String"
};
var T = {
    [ce]: true,
    "default": false,
    [cf]: "Boolean"
};
var U = {
    [ce]: false,
    [cf]: "Boolean"
};
var V = {
    [ch]: d,
    [ci]: [{
        [cj]: "Accelerate"
    }, true]
};
var W = {
    [ch]: d,
    [ci]: [{
        [cj]: "UseFIPS"
    }, true]
};
var X = {
    [ch]: d,
    [ci]: [{
        [cj]: "UseDualStack"
    }, true]
};
var Y = {
    [ch]: c,
    [ci]: [{
        [cj]: "Endpoint"
    }]
};
var Z = {
    [ch]: f,
    [ci]: [{
        [cj]: "Region"
    }],
    [ck]: "partitionResult"
};
var aa = {
    [ch]: g,
    [ci]: [{
        [ch]: h,
        [ci]: [{
            [cj]: "partitionResult"
        }, i]
    }, "aws-cn"]
};
var ab = {
    [ch]: c,
    [ci]: [{
        [cj]: "Bucket"
    }]
};
var ac = {
    [cj]: "Bucket"
};
var ad = {
    [ch]: l,
    [ci]: [{
        [cj]: "Endpoint"
    }],
    [ck]: "url"
};
var ae = {
    [ch]: d,
    [ci]: [{
        [ch]: h,
        [ci]: [{
            [cj]: "url"
        }, "isIp"]
    }, true]
};
var af = {
    [cj]: "url"
};
var ag = {
    [ch]: "uriEncode",
    [ci]: [ac],
    [ck]: "uri_encoded_bucket"
};
var ah = {
    [cn]: "S3Express",
    [co]: [{
        [cp]: true,
        [i]: "sigv4",
        [cq]: "s3express",
        [cr]: "{Region}"
    }]
};
var ai = {};
var aj = {
    [ch]: p,
    [ci]: [ac, false]
};
var ak = {
    [e]: "S3Express bucket name is not a valid virtual hostable name.",
    [cf]: e
};
var al = {
    [cn]: "S3Express",
    [co]: [{
        [cp]: true,
        [i]: "sigv4-s3express",
        [cq]: "s3express",
        [cr]: "{Region}"
    }]
};
var am = {
    [ch]: c,
    [ci]: [{
        [cj]: "UseS3ExpressControlEndpoint"
    }]
};
var an = {
    [ch]: d,
    [ci]: [{
        [cj]: "UseS3ExpressControlEndpoint"
    }, true]
};
var ao = {
    [ch]: r,
    [ci]: [Y]
};
var ap = {
    [e]: "Unrecognized S3Express bucket name format.",
    [cf]: e
};
var aq = {
    [ch]: r,
    [ci]: [ab]
};
var ar = {
    [cj]: t
};
var as = {
    [cg]: [ao],
    [e]: "Expected a endpoint to be specified but no endpoint was found",
    [cf]: e
};
var at = {
    [co]: [{
        [cp]: true,
        [i]: y,
        [cq]: z,
        [ct]: ["*"]
    }, {
        [cp]: true,
        [i]: "sigv4",
        [cq]: z,
        [cr]: "{Region}"
    }]
};
var au = {
    [ch]: d,
    [ci]: [{
        [cj]: "ForcePathStyle"
    }, false]
};
var av = {
    [cj]: "ForcePathStyle"
};
var aw = {
    [ch]: d,
    [ci]: [{
        [cj]: "Accelerate"
    }, false]
};
var ax = {
    [ch]: g,
    [ci]: [{
        [cj]: "Region"
    }, "aws-global"]
};
var ay = {
    [co]: [{
        [cp]: true,
        [i]: "sigv4",
        [cq]: A,
        [cr]: "us-east-1"
    }]
};
var az = {
    [ch]: r,
    [ci]: [ax]
};
var aA = {
    [ch]: d,
    [ci]: [{
        [cj]: "UseGlobalEndpoint"
    }, true]
};
var aB = {
    [cl]: "https://{Bucket}.s3-fips.dualstack.{Region}.{partitionResult#dnsSuffix}",
    [cm]: {
        [co]: [{
            [cp]: true,
            [i]: "sigv4",
            [cq]: A,
            [cr]: "{Region}"
        }]
    },
    [cs]: {}
};
var aC = {
    [co]: [{
        [cp]: true,
        [i]: "sigv4",
        [cq]: A,
        [cr]: "{Region}"
    }]
};
var aD = {
    [ch]: d,
    [ci]: [{
        [cj]: "UseGlobalEndpoint"
    }, false]
};
var aE = {
    [ch]: d,
    [ci]: [{
        [cj]: "UseDualStack"
    }, false]
};
var aF = {
    [cl]: "https://{Bucket}.s3-fips.{Region}.{partitionResult#dnsSuffix}",
    [cm]: aC,
    [cs]: {}
};
var aG = {
    [ch]: d,
    [ci]: [{
        [cj]: "UseFIPS"
    }, false]
};
var aH = {
    [cl]: "https://{Bucket}.s3-accelerate.dualstack.{partitionResult#dnsSuffix}",
    [cm]: aC,
    [cs]: {}
};
var aI = {
    [cl]: "https://{Bucket}.s3.dualstack.{Region}.{partitionResult#dnsSuffix}",
    [cm]: aC,
    [cs]: {}
};
var aJ = {
    [ch]: d,
    [ci]: [{
        [ch]: h,
        [ci]: [af, "isIp"]
    }, false]
};
var aK = {
    [cl]: B,
    [cm]: aC,
    [cs]: {}
};
var aL = {
    [cl]: q,
    [cm]: aC,
    [cs]: {}
};
var aM = {
    [n]: aL,
    [cf]: n
};
var aN = {
    [cl]: C,
    [cm]: aC,
    [cs]: {}
};
var aO = {
    [cl]: "https://{Bucket}.s3.{Region}.{partitionResult#dnsSuffix}",
    [cm]: aC,
    [cs]: {}
};
var aP = {
    [e]: "Invalid region: region was not a valid DNS name.",
    [cf]: e
};
var aQ = {
    [cj]: F
};
var aR = {
    [cj]: G
};
var aS = {
    [ch]: h,
    [ci]: [aQ, "service"]
};
var aT = {
    [cj]: K
};
var aU = {
    [cg]: [X],
    [e]: "S3 Object Lambda does not support Dual-stack",
    [cf]: e
};
var aV = {
    [cg]: [V],
    [e]: "S3 Object Lambda does not support S3 Accelerate",
    [cf]: e
};
var aW = {
    [cg]: [{
        [ch]: c,
        [ci]: [{
            [cj]: "DisableAccessPoints"
        }]
    }, {
        [ch]: d,
        [ci]: [{
            [cj]: "DisableAccessPoints"
        }, true]
    }],
    [e]: "Access points are not supported for this operation",
    [cf]: e
};
var aX = {
    [cg]: [{
        [ch]: c,
        [ci]: [{
            [cj]: "UseArnRegion"
        }]
    }, {
        [ch]: d,
        [ci]: [{
            [cj]: "UseArnRegion"
        }, false]
    }, {
        [ch]: r,
        [ci]: [{
            [ch]: g,
            [ci]: [{
                [ch]: h,
                [ci]: [aQ, "region"]
            }, "{Region}"]
        }]
    }],
    [e]: "Invalid configuration: region from ARN `{bucketArn#region}` does not match client region `{Region}` and UseArnRegion is `false`",
    [cf]: e
};
var aY = {
    [ch]: h,
    [ci]: [{
        [cj]: "bucketPartition"
    }, i]
};
var aZ = {
    [ch]: h,
    [ci]: [aQ, "accountId"]
};
var ba = {
    [co]: [{
        [cp]: true,
        [i]: "sigv4",
        [cq]: I,
        [cr]: "{bucketArn#region}"
    }]
};
var bb = {
    [e]: "Invalid ARN: The access point name may only contain a-z, A-Z, 0-9 and `-`. Found: `{accessPointName}`",
    [cf]: e
};
var bc = {
    [e]: "Invalid ARN: The account id may only contain a-z, A-Z, 0-9 and `-`. Found: `{bucketArn#accountId}`",
    [cf]: e
};
var bd = {
    [e]: "Invalid region in ARN: `{bucketArn#region}` (invalid DNS name)",
    [cf]: e
};
var be = {
    [e]: "Client was configured for partition `{partitionResult#name}` but ARN (`{Bucket}`) has `{bucketPartition#name}`",
    [cf]: e
};
var bf = {
    [e]: "Invalid ARN: The ARN may only contain a single resource component after `accesspoint`.",
    [cf]: e
};
var bg = {
    [e]: "Invalid ARN: Expected a resource of the format `accesspoint:<accesspoint name>` but no name was provided",
    [cf]: e
};
var bh = {
    [co]: [{
        [cp]: true,
        [i]: "sigv4",
        [cq]: A,
        [cr]: "{bucketArn#region}"
    }]
};
var bi = {
    [co]: [{
        [cp]: true,
        [i]: y,
        [cq]: z,
        [ct]: ["*"]
    }, {
        [cp]: true,
        [i]: "sigv4",
        [cq]: z,
        [cr]: "{bucketArn#region}"
    }]
};
var bj = {
    [ch]: E,
    [ci]: [ac]
};
var bk = {
    [cl]: "https://s3-fips.dualstack.{Region}.{partitionResult#dnsSuffix}/{uri_encoded_bucket}",
    [cm]: aC,
    [cs]: {}
};
var bl = {
    [cl]: "https://s3-fips.{Region}.{partitionResult#dnsSuffix}/{uri_encoded_bucket}",
    [cm]: aC,
    [cs]: {}
};
var bm = {
    [cl]: "https://s3.dualstack.{Region}.{partitionResult#dnsSuffix}/{uri_encoded_bucket}",
    [cm]: aC,
    [cs]: {}
};
var bn = {
    [cl]: P,
    [cm]: aC,
    [cs]: {}
};
var bo = {
    [cl]: "https://s3.{Region}.{partitionResult#dnsSuffix}/{uri_encoded_bucket}",
    [cm]: aC,
    [cs]: {}
};
var bp = {
    [cj]: "UseObjectLambdaEndpoint"
};
var bq = {
    [co]: [{
        [cp]: true,
        [i]: "sigv4",
        [cq]: I,
        [cr]: "{Region}"
    }]
};
var br = {
    [cl]: "https://s3-fips.dualstack.{Region}.{partitionResult#dnsSuffix}",
    [cm]: aC,
    [cs]: {}
};
var bs = {
    [cl]: "https://s3-fips.{Region}.{partitionResult#dnsSuffix}",
    [cm]: aC,
    [cs]: {}
};
var bt = {
    [cl]: "https://s3.dualstack.{Region}.{partitionResult#dnsSuffix}",
    [cm]: aC,
    [cs]: {}
};
var bu = {
    [cl]: s,
    [cm]: aC,
    [cs]: {}
};
var bv = {
    [cl]: "https://s3.{Region}.{partitionResult#dnsSuffix}",
    [cm]: aC,
    [cs]: {}
};
var bw = [{
    [cj]: "Region"
}];
var bx = [{
    [cj]: "Endpoint"
}];
var by = [ac];
var bz = [X];
var bA = [V];
var bB = [Y, ad];
var bC = [{
    [ch]: c,
    [ci]: [{
        [cj]: "DisableS3ExpressSessionAuth"
    }]
}, {
    [ch]: d,
    [ci]: [{
        [cj]: "DisableS3ExpressSessionAuth"
    }, true]
}];
var bD = [ae];
var bE = [ag];
var bF = [aj];
var bG = [W];
var bH = [{
    [ch]: j,
    [ci]: [ac, 6, 14, true],
    [ck]: "s3expressAvailabilityZoneId"
}, {
    [ch]: j,
    [ci]: [ac, 14, 16, true],
    [ck]: "s3expressAvailabilityZoneDelim"
}, {
    [ch]: g,
    [ci]: [{
        [cj]: "s3expressAvailabilityZoneDelim"
    }, "--"]
}];
var bI = [{
    [cg]: [W],
    [n]: {
        [cl]: "https://{Bucket}.s3express-fips-{s3expressAvailabilityZoneId}.{Region}.amazonaws.com",
        [cm]: ah,
        [cs]: {}
    },
    [cf]: n
}, {
    [n]: {
        [cl]: "https://{Bucket}.s3express-{s3expressAvailabilityZoneId}.{Region}.amazonaws.com",
        [cm]: ah,
        [cs]: {}
    },
    [cf]: n
}];
var bJ = [{
    [ch]: j,
    [ci]: [ac, 6, 15, true],
    [ck]: "s3expressAvailabilityZoneId"
}, {
    [ch]: j,
    [ci]: [ac, 15, 17, true],
    [ck]: "s3expressAvailabilityZoneDelim"
}, {
    [ch]: g,
    [ci]: [{
        [cj]: "s3expressAvailabilityZoneDelim"
    }, "--"]
}];
var bK = [{
    [cg]: [W],
    [n]: {
        [cl]: "https://{Bucket}.s3express-fips-{s3expressAvailabilityZoneId}.{Region}.amazonaws.com",
        [cm]: al,
        [cs]: {}
    },
    [cf]: n
}, {
    [n]: {
        [cl]: "https://{Bucket}.s3express-{s3expressAvailabilityZoneId}.{Region}.amazonaws.com",
        [cm]: al,
        [cs]: {}
    },
    [cf]: n
}];
var bL = [ab];
var bM = [{
    [ch]: x,
    [ci]: [{
        [cj]: w
    }, false]
}];
var bN = [{
    [ch]: g,
    [ci]: [{
        [cj]: u
    }, "beta"]
}];
var bO = ["*"];
var bP = [Z];
var bQ = [{
    [ch]: x,
    [ci]: [{
        [cj]: "Region"
    }, false]
}];
var bR = [{
    [ch]: g,
    [ci]: [{
        [cj]: "Region"
    }, "us-east-1"]
}];
var bS = [{
    [ch]: g,
    [ci]: [aR, J]
}];
var bT = [{
    [ch]: h,
    [ci]: [aQ, "resourceId[1]"],
    [ck]: K
}, {
    [ch]: r,
    [ci]: [{
        [ch]: g,
        [ci]: [aT, H]
    }]
}];
var bU = [aQ, "resourceId[1]"];
var bV = [{
    [ch]: r,
    [ci]: [{
        [ch]: g,
        [ci]: [{
            [ch]: h,
            [ci]: [aQ, "region"]
        }, H]
    }]
}];
var bW = [{
    [ch]: r,
    [ci]: [{
        [ch]: c,
        [ci]: [{
            [ch]: h,
            [ci]: [aQ, "resourceId[2]"]
        }]
    }]
}];
var bX = [aQ, "resourceId[2]"];
var bY = [{
    [ch]: f,
    [ci]: [{
        [ch]: h,
        [ci]: [aQ, "region"]
    }],
    [ck]: "bucketPartition"
}];
var bZ = [{
    [ch]: g,
    [ci]: [aY, {
        [ch]: h,
        [ci]: [{
            [cj]: "partitionResult"
        }, i]
    }]
}];
var ca = [{
    [ch]: x,
    [ci]: [{
        [ch]: h,
        [ci]: [aQ, "region"]
    }, true]
}];
var cb = [{
    [ch]: x,
    [ci]: [aZ, false]
}];
var cc = [{
    [ch]: x,
    [ci]: [aT, false]
}];
var cd = [{
    [ch]: x,
    [ci]: [{
        [cj]: "Region"
    }, true]
}];
var _data = {
    version: "1.0",
    parameters: {
        Bucket: S,
        Region: S,
        UseFIPS: T,
        UseDualStack: T,
        Endpoint: S,
        ForcePathStyle: T,
        Accelerate: T,
        UseGlobalEndpoint: T,
        UseObjectLambdaEndpoint: U,
        Key: S,
        Prefix: S,
        CopySource: S,
        DisableAccessPoints: U,
        DisableMultiRegionAccessPoints: T,
        UseArnRegion: U,
        UseS3ExpressControlEndpoint: U,
        DisableS3ExpressSessionAuth: U
    },
    rules: [{
        [cg]: [{
            [ch]: c,
            [ci]: bw
        }],
        rules: [{
            [cg]: [V, W],
            error: "Accelerate cannot be used with FIPS",
            [cf]: e
        }, {
            [cg]: [X, Y],
            error: "Cannot set dual-stack in combination with a custom endpoint.",
            [cf]: e
        }, {
            [cg]: [Y, W],
            error: "A custom endpoint cannot be combined with FIPS",
            [cf]: e
        }, {
            [cg]: [Y, V],
            error: "A custom endpoint cannot be combined with S3 Accelerate",
            [cf]: e
        }, {
            [cg]: [W, Z, aa],
            error: "Partition does not support FIPS",
            [cf]: e
        }, {
            [cg]: [ab, {
                [ch]: j,
                [ci]: [ac, 0, 6, b],
                [ck]: k
            }, {
                [ch]: g,
                [ci]: [{
                    [cj]: k
                }, "--x-s3"]
            }],
            rules: [{
                [cg]: bz,
                error: "S3Express does not support Dual-stack.",
                [cf]: e
            }, {
                [cg]: bA,
                error: "S3Express does not support S3 Accelerate.",
                [cf]: e
            }, {
                [cg]: bB,
                rules: [{
                    [cg]: bC,
                    rules: [{
                        [cg]: bD,
                        rules: [{
                            [cg]: bE,
                            rules: [{
                                endpoint: {
                                    [cl]: m,
                                    [cm]: ah,
                                    [cs]: ai
                                },
                                [cf]: n
                            }],
                            [cf]: o
                        }],
                        [cf]: o
                    }, {
                        [cg]: bF,
                        rules: [{
                            endpoint: {
                                [cl]: q,
                                [cm]: ah,
                                [cs]: ai
                            },
                            [cf]: n
                        }],
                        [cf]: o
                    }, ak],
                    [cf]: o
                }, {
                    [cg]: bD,
                    rules: [{
                        [cg]: bE,
                        rules: [{
                            endpoint: {
                                [cl]: m,
                                [cm]: al,
                                [cs]: ai
                            },
                            [cf]: n
                        }],
                        [cf]: o
                    }],
                    [cf]: o
                }, {
                    [cg]: bF,
                    rules: [{
                        endpoint: {
                            [cl]: q,
                            [cm]: al,
                            [cs]: ai
                        },
                        [cf]: n
                    }],
                    [cf]: o
                }, ak],
                [cf]: o
            }, {
                [cg]: [am, an],
                rules: [{
                    [cg]: [ag, ao],
                    rules: [{
                        [cg]: bG,
                        endpoint: {
                            [cl]: "https://s3express-control-fips.{Region}.amazonaws.com/{uri_encoded_bucket}",
                            [cm]: ah,
                            [cs]: ai
                        },
                        [cf]: n
                    }, {
                        endpoint: {
                            [cl]: "https://s3express-control.{Region}.amazonaws.com/{uri_encoded_bucket}",
                            [cm]: ah,
                            [cs]: ai
                        },
                        [cf]: n
                    }],
                    [cf]: o
                }],
                [cf]: o
            }, {
                [cg]: bF,
                rules: [{
                    [cg]: bC,
                    rules: [{
                        [cg]: bH,
                        rules: bI,
                        [cf]: o
                    }, {
                        [cg]: bJ,
                        rules: bI,
                        [cf]: o
                    }, ap],
                    [cf]: o
                }, {
                    [cg]: bH,
                    rules: bK,
                    [cf]: o
                }, {
                    [cg]: bJ,
                    rules: bK,
                    [cf]: o
                }, ap],
                [cf]: o
            }, ak],
            [cf]: o
        }, {
            [cg]: [aq, am, an],
            rules: [{
                [cg]: bB,
                endpoint: {
                    [cl]: s,
                    [cm]: ah,
                    [cs]: ai
                },
                [cf]: n
            }, {
                [cg]: bG,
                endpoint: {
                    [cl]: "https://s3express-control-fips.{Region}.amazonaws.com",
                    [cm]: ah,
                    [cs]: ai
                },
                [cf]: n
            }, {
                endpoint: {
                    [cl]: "https://s3express-control.{Region}.amazonaws.com",
                    [cm]: ah,
                    [cs]: ai
                },
                [cf]: n
            }],
            [cf]: o
        }, {
            [cg]: [ab, {
                [ch]: j,
                [ci]: [ac, 49, 50, b],
                [ck]: t
            }, {
                [ch]: j,
                [ci]: [ac, 8, 12, b],
                [ck]: u
            }, {
                [ch]: j,
                [ci]: [ac, 0, 7, b],
                [ck]: v
            }, {
                [ch]: j,
                [ci]: [ac, 32, 49, b],
                [ck]: w
            }, {
                [ch]: f,
                [ci]: bw,
                [ck]: "regionPartition"
            }, {
                [ch]: g,
                [ci]: [{
                    [cj]: v
                }, "--op-s3"]
            }],
            rules: [{
                [cg]: bM,
                rules: [{
                    [cg]: [{
                        [ch]: g,
                        [ci]: [ar, "e"]
                    }],
                    rules: [{
                        [cg]: bN,
                        rules: [as, {
                            [cg]: bB,
                            endpoint: {
                                [cl]: "https://{Bucket}.ec2.{url#authority}",
                                [cm]: at,
                                [cs]: ai
                            },
                            [cf]: n
                        }],
                        [cf]: o
                    }, {
                        endpoint: {
                            [cl]: "https://{Bucket}.ec2.s3-outposts.{Region}.{regionPartition#dnsSuffix}",
                            [cm]: at,
                            [cs]: ai
                        },
                        [cf]: n
                    }],
                    [cf]: o
                }, {
                    [cg]: [{
                        [ch]: g,
                        [ci]: [ar, "o"]
                    }],
                    rules: [{
                        [cg]: bN,
                        rules: [as, {
                            [cg]: bB,
                            endpoint: {
                                [cl]: "https://{Bucket}.op-{outpostId}.{url#authority}",
                                [cm]: at,
                                [cs]: ai
                            },
                            [cf]: n
                        }],
                        [cf]: o
                    }, {
                        endpoint: {
                            [cl]: "https://{Bucket}.op-{outpostId}.s3-outposts.{Region}.{regionPartition#dnsSuffix}",
                            [cm]: at,
                            [cs]: ai
                        },
                        [cf]: n
                    }],
                    [cf]: o
                }, {
                    error: 'Unrecognized hardware type: "Expected hardware type o or e but got {hardwareType}"',
                    [cf]: e
                }],
                [cf]: o
            }, {
                error: "Invalid ARN: The outpost Id must only contain a-z, A-Z, 0-9 and `-`.",
                [cf]: e
            }],
            [cf]: o
        }, {
            [cg]: bL,
            rules: [{
                [cg]: [Y, {
                    [ch]: r,
                    [ci]: [{
                        [ch]: c,
                        [ci]: [{
                            [ch]: l,
                            [ci]: bx
                        }]
                    }]
                }],
                error: "Custom endpoint `{Endpoint}` was not a valid URI",
                [cf]: e
            }, {
                [cg]: [au, aj],
                rules: [{
                    [cg]: bP,
                    rules: [{
                        [cg]: bQ,
                        rules: [{
                            [cg]: [V, aa],
                            error: "S3 Accelerate cannot be used in this region",
                            [cf]: e
                        }, {
                            [cg]: [X, W, aw, ao, ax],
                            endpoint: {
                                [cl]: "https://{Bucket}.s3-fips.dualstack.us-east-1.{partitionResult#dnsSuffix}",
                                [cm]: ay,
                                [cs]: ai
                            },
                            [cf]: n
                        }, {
                            [cg]: [X, W, aw, ao, az, aA],
                            rules: [{
                                endpoint: aB,
                                [cf]: n
                            }],
                            [cf]: o
                        }, {
                            [cg]: [X, W, aw, ao, az, aD],
                            endpoint: aB,
                            [cf]: n
                        }, {
                            [cg]: [aE, W, aw, ao, ax],
                            endpoint: {
                                [cl]: "https://{Bucket}.s3-fips.us-east-1.{partitionResult#dnsSuffix}",
                                [cm]: ay,
                                [cs]: ai
                            },
                            [cf]: n
                        }, {
                            [cg]: [aE, W, aw, ao, az, aA],
                            rules: [{
                                endpoint: aF,
                                [cf]: n
                            }],
                            [cf]: o
                        }, {
                            [cg]: [aE, W, aw, ao, az, aD],
                            endpoint: aF,
                            [cf]: n
                        }, {
                            [cg]: [X, aG, V, ao, ax],
                            endpoint: {
                                [cl]: "https://{Bucket}.s3-accelerate.dualstack.us-east-1.{partitionResult#dnsSuffix}",
                                [cm]: ay,
                                [cs]: ai
                            },
                            [cf]: n
                        }, {
                            [cg]: [X, aG, V, ao, az, aA],
                            rules: [{
                                endpoint: aH,
                                [cf]: n
                            }],
                            [cf]: o
                        }, {
                            [cg]: [X, aG, V, ao, az, aD],
                            endpoint: aH,
                            [cf]: n
                        }, {
                            [cg]: [X, aG, aw, ao, ax],
                            endpoint: {
                                [cl]: "https://{Bucket}.s3.dualstack.us-east-1.{partitionResult#dnsSuffix}",
                                [cm]: ay,
                                [cs]: ai
                            },
                            [cf]: n
                        }, {
                            [cg]: [X, aG, aw, ao, az, aA],
                            rules: [{
                                endpoint: aI,
                                [cf]: n
                            }],
                            [cf]: o
                        }, {
                            [cg]: [X, aG, aw, ao, az, aD],
                            endpoint: aI,
                            [cf]: n
                        }, {
                            [cg]: [aE, aG, aw, Y, ad, ae, ax],
                            endpoint: {
                                [cl]: B,
                                [cm]: ay,
                                [cs]: ai
                            },
                            [cf]: n
                        }, {
                            [cg]: [aE, aG, aw, Y, ad, aJ, ax],
                            endpoint: {
                                [cl]: q,
                                [cm]: ay,
                                [cs]: ai
                            },
                            [cf]: n
                        }, {
                            [cg]: [aE, aG, aw, Y, ad, ae, az, aA],
                            rules: [{
                                [cg]: bR,
                                endpoint: aK,
                                [cf]: n
                            }, {
                                endpoint: aK,
                                [cf]: n
                            }],
                            [cf]: o
                        }, {
                            [cg]: [aE, aG, aw, Y, ad, aJ, az, aA],
                            rules: [{
                                [cg]: bR,
                                endpoint: aL,
                                [cf]: n
                            }, aM],
                            [cf]: o
                        }, {
                            [cg]: [aE, aG, aw, Y, ad, ae, az, aD],
                            endpoint: aK,
                            [cf]: n
                        }, {
                            [cg]: [aE, aG, aw, Y, ad, aJ, az, aD],
                            endpoint: aL,
                            [cf]: n
                        }, {
                            [cg]: [aE, aG, V, ao, ax],
                            endpoint: {
                                [cl]: C,
                                [cm]: ay,
                                [cs]: ai
                            },
                            [cf]: n
                        }, {
                            [cg]: [aE, aG, V, ao, az, aA],
                            rules: [{
                                [cg]: bR,
                                endpoint: aN,
                                [cf]: n
                            }, {
                                endpoint: aN,
                                [cf]: n
                            }],
                            [cf]: o
                        }, {
                            [cg]: [aE, aG, V, ao, az, aD],
                            endpoint: aN,
                            [cf]: n
                        }, {
                            [cg]: [aE, aG, aw, ao, ax],
                            endpoint: {
                                [cl]: D,
                                [cm]: ay,
                                [cs]: ai
                            },
                            [cf]: n
                        }, {
                            [cg]: [aE, aG, aw, ao, az, aA],
                            rules: [{
                                [cg]: bR,
                                endpoint: {
                                    [cl]: D,
                                    [cm]: aC,
                                    [cs]: ai
                                },
                                [cf]: n
                            }, {
                                endpoint: aO,
                                [cf]: n
                            }],
                            [cf]: o
                        }, {
                            [cg]: [aE, aG, aw, ao, az, aD],
                            endpoint: aO,
                            [cf]: n
                        }],
                        [cf]: o
                    }, aP],
                    [cf]: o
                }],
                [cf]: o
            }, {
                [cg]: [Y, ad, {
                    [ch]: g,
                    [ci]: [{
                        [ch]: h,
                        [ci]: [af, "scheme"]
                    }, "http"]
                }, {
                    [ch]: p,
                    [ci]: [ac, b]
                }, au, aG, aE, aw],
                rules: [{
                    [cg]: bP,
                    rules: [{
                        [cg]: bQ,
                        rules: [aM],
                        [cf]: o
                    }, aP],
                    [cf]: o
                }],
                [cf]: o
            }, {
                [cg]: [au, {
                    [ch]: E,
                    [ci]: by,
                    [ck]: F
                }],
                rules: [{
                    [cg]: [{
                        [ch]: h,
                        [ci]: [aQ, "resourceId[0]"],
                        [ck]: G
                    }, {
                        [ch]: r,
                        [ci]: [{
                            [ch]: g,
                            [ci]: [aR, H]
                        }]
                    }],
                    rules: [{
                        [cg]: [{
                            [ch]: g,
                            [ci]: [aS, I]
                        }],
                        rules: [{
                            [cg]: bS,
                            rules: [{
                                [cg]: bT,
                                rules: [aU, aV, {
                                    [cg]: bV,
                                    rules: [aW, {
                                        [cg]: bW,
                                        rules: [aX, {
                                            [cg]: bY,
                                            rules: [{
                                                [cg]: bP,
                                                rules: [{
                                                    [cg]: bZ,
                                                    rules: [{
                                                        [cg]: ca,
                                                        rules: [{
                                                            [cg]: [{
                                                                [ch]: g,
                                                                [ci]: [aZ, H]
                                                            }],
                                                            error: "Invalid ARN: Missing account id",
                                                            [cf]: e
                                                        }, {
                                                            [cg]: cb,
                                                            rules: [{
                                                                [cg]: cc,
                                                                rules: [{
                                                                    [cg]: bB,
                                                                    endpoint: {
                                                                        [cl]: L,
                                                                        [cm]: ba,
                                                                        [cs]: ai
                                                                    },
                                                                    [cf]: n
                                                                }, {
                                                                    [cg]: bG,
                                                                    endpoint: {
                                                                        [cl]: "https://{accessPointName}-{bucketArn#accountId}.s3-object-lambda-fips.{bucketArn#region}.{bucketPartition#dnsSuffix}",
                                                                        [cm]: ba,
                                                                        [cs]: ai
                                                                    },
                                                                    [cf]: n
                                                                }, {
                                                                    endpoint: {
                                                                        [cl]: "https://{accessPointName}-{bucketArn#accountId}.s3-object-lambda.{bucketArn#region}.{bucketPartition#dnsSuffix}",
                                                                        [cm]: ba,
                                                                        [cs]: ai
                                                                    },
                                                                    [cf]: n
                                                                }],
                                                                [cf]: o
                                                            }, bb],
                                                            [cf]: o
                                                        }, bc],
                                                        [cf]: o
                                                    }, bd],
                                                    [cf]: o
                                                }, be],
                                                [cf]: o
                                            }],
                                            [cf]: o
                                        }],
                                        [cf]: o
                                    }, bf],
                                    [cf]: o
                                }, {
                                    error: "Invalid ARN: bucket ARN is missing a region",
                                    [cf]: e
                                }],
                                [cf]: o
                            }, bg],
                            [cf]: o
                        }, {
                            error: "Invalid ARN: Object Lambda ARNs only support `accesspoint` arn types, but found: `{arnType}`",
                            [cf]: e
                        }],
                        [cf]: o
                    }, {
                        [cg]: bS,
                        rules: [{
                            [cg]: bT,
                            rules: [{
                                [cg]: bV,
                                rules: [{
                                    [cg]: bS,
                                    rules: [{
                                        [cg]: bV,
                                        rules: [aW, {
                                            [cg]: bW,
                                            rules: [aX, {
                                                [cg]: bY,
                                                rules: [{
                                                    [cg]: bP,
                                                    rules: [{
                                                        [cg]: [{
                                                            [ch]: g,
                                                            [ci]: [aY, "{partitionResult#name}"]
                                                        }],
                                                        rules: [{
                                                            [cg]: ca,
                                                            rules: [{
                                                                [cg]: [{
                                                                    [ch]: g,
                                                                    [ci]: [aS, A]
                                                                }],
                                                                rules: [{
                                                                    [cg]: cb,
                                                                    rules: [{
                                                                        [cg]: cc,
                                                                        rules: [{
                                                                            [cg]: bA,
                                                                            error: "Access Points do not support S3 Accelerate",
                                                                            [cf]: e
                                                                        }, {
                                                                            [cg]: [W, X],
                                                                            endpoint: {
                                                                                [cl]: "https://{accessPointName}-{bucketArn#accountId}.s3-accesspoint-fips.dualstack.{bucketArn#region}.{bucketPartition#dnsSuffix}",
                                                                                [cm]: bh,
                                                                                [cs]: ai
                                                                            },
                                                                            [cf]: n
                                                                        }, {
                                                                            [cg]: [W, aE],
                                                                            endpoint: {
                                                                                [cl]: "https://{accessPointName}-{bucketArn#accountId}.s3-accesspoint-fips.{bucketArn#region}.{bucketPartition#dnsSuffix}",
                                                                                [cm]: bh,
                                                                                [cs]: ai
                                                                            },
                                                                            [cf]: n
                                                                        }, {
                                                                            [cg]: [aG, X],
                                                                            endpoint: {
                                                                                [cl]: "https://{accessPointName}-{bucketArn#accountId}.s3-accesspoint.dualstack.{bucketArn#region}.{bucketPartition#dnsSuffix}",
                                                                                [cm]: bh,
                                                                                [cs]: ai
                                                                            },
                                                                            [cf]: n
                                                                        }, {
                                                                            [cg]: [aG, aE, Y, ad],
                                                                            endpoint: {
                                                                                [cl]: L,
                                                                                [cm]: bh,
                                                                                [cs]: ai
                                                                            },
                                                                            [cf]: n
                                                                        }, {
                                                                            [cg]: [aG, aE],
                                                                            endpoint: {
                                                                                [cl]: "https://{accessPointName}-{bucketArn#accountId}.s3-accesspoint.{bucketArn#region}.{bucketPartition#dnsSuffix}",
                                                                                [cm]: bh,
                                                                                [cs]: ai
                                                                            },
                                                                            [cf]: n
                                                                        }],
                                                                        [cf]: o
                                                                    }, bb],
                                                                    [cf]: o
                                                                }, bc],
                                                                [cf]: o
                                                            }, {
                                                                error: "Invalid ARN: The ARN was not for the S3 service, found: {bucketArn#service}",
                                                                [cf]: e
                                                            }],
                                                            [cf]: o
                                                        }, bd],
                                                        [cf]: o
                                                    }, be],
                                                    [cf]: o
                                                }],
                                                [cf]: o
                                            }],
                                            [cf]: o
                                        }, bf],
                                        [cf]: o
                                    }],
                                    [cf]: o
                                }],
                                [cf]: o
                            }, {
                                [cg]: [{
                                    [ch]: x,
                                    [ci]: [aT, b]
                                }],
                                rules: [{
                                    [cg]: bz,
                                    error: "S3 MRAP does not support dual-stack",
                                    [cf]: e
                                }, {
                                    [cg]: bG,
                                    error: "S3 MRAP does not support FIPS",
                                    [cf]: e
                                }, {
                                    [cg]: bA,
                                    error: "S3 MRAP does not support S3 Accelerate",
                                    [cf]: e
                                }, {
                                    [cg]: [{
                                        [ch]: d,
                                        [ci]: [{
                                            [cj]: "DisableMultiRegionAccessPoints"
                                        }, b]
                                    }],
                                    error: "Invalid configuration: Multi-Region Access Point ARNs are disabled.",
                                    [cf]: e
                                }, {
                                    [cg]: [{
                                        [ch]: f,
                                        [ci]: bw,
                                        [ck]: M
                                    }],
                                    rules: [{
                                        [cg]: [{
                                            [ch]: g,
                                            [ci]: [{
                                                [ch]: h,
                                                [ci]: [{
                                                    [cj]: M
                                                }, i]
                                            }, {
                                                [ch]: h,
                                                [ci]: [aQ, "partition"]
                                            }]
                                        }],
                                        rules: [{
                                            endpoint: {
                                                [cl]: "https://{accessPointName}.accesspoint.s3-global.{mrapPartition#dnsSuffix}",
                                                [cm]: {
                                                    [co]: [{
                                                        [cp]: b,
                                                        name: y,
                                                        [cq]: A,
                                                        [ct]: bO
                                                    }]
                                                },
                                                [cs]: ai
                                            },
                                            [cf]: n
                                        }],
                                        [cf]: o
                                    }, {
                                        error: "Client was configured for partition `{mrapPartition#name}` but bucket referred to partition `{bucketArn#partition}`",
                                        [cf]: e
                                    }],
                                    [cf]: o
                                }],
                                [cf]: o
                            }, {
                                error: "Invalid Access Point Name",
                                [cf]: e
                            }],
                            [cf]: o
                        }, bg],
                        [cf]: o
                    }, {
                        [cg]: [{
                            [ch]: g,
                            [ci]: [aS, z]
                        }],
                        rules: [{
                            [cg]: bz,
                            error: "S3 Outposts does not support Dual-stack",
                            [cf]: e
                        }, {
                            [cg]: bG,
                            error: "S3 Outposts does not support FIPS",
                            [cf]: e
                        }, {
                            [cg]: bA,
                            error: "S3 Outposts does not support S3 Accelerate",
                            [cf]: e
                        }, {
                            [cg]: [{
                                [ch]: c,
                                [ci]: [{
                                    [ch]: h,
                                    [ci]: [aQ, "resourceId[4]"]
                                }]
                            }],
                            error: "Invalid Arn: Outpost Access Point ARN contains sub resources",
                            [cf]: e
                        }, {
                            [cg]: [{
                                [ch]: h,
                                [ci]: bU,
                                [ck]: w
                            }],
                            rules: [{
                                [cg]: bM,
                                rules: [aX, {
                                    [cg]: bY,
                                    rules: [{
                                        [cg]: bP,
                                        rules: [{
                                            [cg]: bZ,
                                            rules: [{
                                                [cg]: ca,
                                                rules: [{
                                                    [cg]: cb,
                                                    rules: [{
                                                        [cg]: [{
                                                            [ch]: h,
                                                            [ci]: bX,
                                                            [ck]: N
                                                        }],
                                                        rules: [{
                                                            [cg]: [{
                                                                [ch]: h,
                                                                [ci]: [aQ, "resourceId[3]"],
                                                                [ck]: K
                                                            }],
                                                            rules: [{
                                                                [cg]: [{
                                                                    [ch]: g,
                                                                    [ci]: [{
                                                                        [cj]: N
                                                                    }, J]
                                                                }],
                                                                rules: [{
                                                                    [cg]: bB,
                                                                    endpoint: {
                                                                        [cl]: "https://{accessPointName}-{bucketArn#accountId}.{outpostId}.{url#authority}",
                                                                        [cm]: bi,
                                                                        [cs]: ai
                                                                    },
                                                                    [cf]: n
                                                                }, {
                                                                    endpoint: {
                                                                        [cl]: "https://{accessPointName}-{bucketArn#accountId}.{outpostId}.s3-outposts.{bucketArn#region}.{bucketPartition#dnsSuffix}",
                                                                        [cm]: bi,
                                                                        [cs]: ai
                                                                    },
                                                                    [cf]: n
                                                                }],
                                                                [cf]: o
                                                            }, {
                                                                error: "Expected an outpost type `accesspoint`, found {outpostType}",
                                                                [cf]: e
                                                            }],
                                                            [cf]: o
                                                        }, {
                                                            error: "Invalid ARN: expected an access point name",
                                                            [cf]: e
                                                        }],
                                                        [cf]: o
                                                    }, {
                                                        error: "Invalid ARN: Expected a 4-component resource",
                                                        [cf]: e
                                                    }],
                                                    [cf]: o
                                                }, bc],
                                                [cf]: o
                                            }, bd],
                                            [cf]: o
                                        }, be],
                                        [cf]: o
                                    }],
                                    [cf]: o
                                }],
                                [cf]: o
                            }, {
                                error: "Invalid ARN: The outpost Id may only contain a-z, A-Z, 0-9 and `-`. Found: `{outpostId}`",
                                [cf]: e
                            }],
                            [cf]: o
                        }, {
                            error: "Invalid ARN: The Outpost Id was not set",
                            [cf]: e
                        }],
                        [cf]: o
                    }, {
                        error: "Invalid ARN: Unrecognized format: {Bucket} (type: {arnType})",
                        [cf]: e
                    }],
                    [cf]: o
                }, {
                    error: "Invalid ARN: No ARN type specified",
                    [cf]: e
                }],
                [cf]: o
            }, {
                [cg]: [{
                    [ch]: j,
                    [ci]: [ac, 0, 4, a],
                    [ck]: O
                }, {
                    [ch]: g,
                    [ci]: [{
                        [cj]: O
                    }, "arn:"]
                }, {
                    [ch]: r,
                    [ci]: [{
                        [ch]: c,
                        [ci]: [bj]
                    }]
                }],
                error: "Invalid ARN: `{Bucket}` was not a valid ARN",
                [cf]: e
            }, {
                [cg]: [{
                    [ch]: d,
                    [ci]: [av, b]
                }, bj],
                error: "Path-style addressing cannot be used with ARN buckets",
                [cf]: e
            }, {
                [cg]: bE,
                rules: [{
                    [cg]: bP,
                    rules: [{
                        [cg]: [aw],
                        rules: [{
                            [cg]: [X, ao, W, ax],
                            endpoint: {
                                [cl]: "https://s3-fips.dualstack.us-east-1.{partitionResult#dnsSuffix}/{uri_encoded_bucket}",
                                [cm]: ay,
                                [cs]: ai
                            },
                            [cf]: n
                        }, {
                            [cg]: [X, ao, W, az, aA],
                            rules: [{
                                endpoint: bk,
                                [cf]: n
                            }],
                            [cf]: o
                        }, {
                            [cg]: [X, ao, W, az, aD],
                            endpoint: bk,
                            [cf]: n
                        }, {
                            [cg]: [aE, ao, W, ax],
                            endpoint: {
                                [cl]: "https://s3-fips.us-east-1.{partitionResult#dnsSuffix}/{uri_encoded_bucket}",
                                [cm]: ay,
                                [cs]: ai
                            },
                            [cf]: n
                        }, {
                            [cg]: [aE, ao, W, az, aA],
                            rules: [{
                                endpoint: bl,
                                [cf]: n
                            }],
                            [cf]: o
                        }, {
                            [cg]: [aE, ao, W, az, aD],
                            endpoint: bl,
                            [cf]: n
                        }, {
                            [cg]: [X, ao, aG, ax],
                            endpoint: {
                                [cl]: "https://s3.dualstack.us-east-1.{partitionResult#dnsSuffix}/{uri_encoded_bucket}",
                                [cm]: ay,
                                [cs]: ai
                            },
                            [cf]: n
                        }, {
                            [cg]: [X, ao, aG, az, aA],
                            rules: [{
                                endpoint: bm,
                                [cf]: n
                            }],
                            [cf]: o
                        }, {
                            [cg]: [X, ao, aG, az, aD],
                            endpoint: bm,
                            [cf]: n
                        }, {
                            [cg]: [aE, Y, ad, aG, ax],
                            endpoint: {
                                [cl]: P,
                                [cm]: ay,
                                [cs]: ai
                            },
                            [cf]: n
                        }, {
                            [cg]: [aE, Y, ad, aG, az, aA],
                            rules: [{
                                [cg]: bR,
                                endpoint: bn,
                                [cf]: n
                            }, {
                                endpoint: bn,
                                [cf]: n
                            }],
                            [cf]: o
                        }, {
                            [cg]: [aE, Y, ad, aG, az, aD],
                            endpoint: bn,
                            [cf]: n
                        }, {
                            [cg]: [aE, ao, aG, ax],
                            endpoint: {
                                [cl]: Q,
                                [cm]: ay,
                                [cs]: ai
                            },
                            [cf]: n
                        }, {
                            [cg]: [aE, ao, aG, az, aA],
                            rules: [{
                                [cg]: bR,
                                endpoint: {
                                    [cl]: Q,
                                    [cm]: aC,
                                    [cs]: ai
                                },
                                [cf]: n
                            }, {
                                endpoint: bo,
                                [cf]: n
                            }],
                            [cf]: o
                        }, {
                            [cg]: [aE, ao, aG, az, aD],
                            endpoint: bo,
                            [cf]: n
                        }],
                        [cf]: o
                    }, {
                        error: "Path-style addressing cannot be used with S3 Accelerate",
                        [cf]: e
                    }],
                    [cf]: o
                }],
                [cf]: o
            }],
            [cf]: o
        }, {
            [cg]: [{
                [ch]: c,
                [ci]: [bp]
            }, {
                [ch]: d,
                [ci]: [bp, b]
            }],
            rules: [{
                [cg]: bP,
                rules: [{
                    [cg]: cd,
                    rules: [aU, aV, {
                        [cg]: bB,
                        endpoint: {
                            [cl]: s,
                            [cm]: bq,
                            [cs]: ai
                        },
                        [cf]: n
                    }, {
                        [cg]: bG,
                        endpoint: {
                            [cl]: "https://s3-object-lambda-fips.{Region}.{partitionResult#dnsSuffix}",
                            [cm]: bq,
                            [cs]: ai
                        },
                        [cf]: n
                    }, {
                        endpoint: {
                            [cl]: "https://s3-object-lambda.{Region}.{partitionResult#dnsSuffix}",
                            [cm]: bq,
                            [cs]: ai
                        },
                        [cf]: n
                    }],
                    [cf]: o
                }, aP],
                [cf]: o
            }],
            [cf]: o
        }, {
            [cg]: [aq],
            rules: [{
                [cg]: bP,
                rules: [{
                    [cg]: cd,
                    rules: [{
                        [cg]: [W, X, ao, ax],
                        endpoint: {
                            [cl]: "https://s3-fips.dualstack.us-east-1.{partitionResult#dnsSuffix}",
                            [cm]: ay,
                            [cs]: ai
                        },
                        [cf]: n
                    }, {
                        [cg]: [W, X, ao, az, aA],
                        rules: [{
                            endpoint: br,
                            [cf]: n
                        }],
                        [cf]: o
                    }, {
                        [cg]: [W, X, ao, az, aD],
                        endpoint: br,
                        [cf]: n
                    }, {
                        [cg]: [W, aE, ao, ax],
                        endpoint: {
                            [cl]: "https://s3-fips.us-east-1.{partitionResult#dnsSuffix}",
                            [cm]: ay,
                            [cs]: ai
                        },
                        [cf]: n
                    }, {
                        [cg]: [W, aE, ao, az, aA],
                        rules: [{
                            endpoint: bs,
                            [cf]: n
                        }],
                        [cf]: o
                    }, {
                        [cg]: [W, aE, ao, az, aD],
                        endpoint: bs,
                        [cf]: n
                    }, {
                        [cg]: [aG, X, ao, ax],
                        endpoint: {
                            [cl]: "https://s3.dualstack.us-east-1.{partitionResult#dnsSuffix}",
                            [cm]: ay,
                            [cs]: ai
                        },
                        [cf]: n
                    }, {
                        [cg]: [aG, X, ao, az, aA],
                        rules: [{
                            endpoint: bt,
                            [cf]: n
                        }],
                        [cf]: o
                    }, {
                        [cg]: [aG, X, ao, az, aD],
                        endpoint: bt,
                        [cf]: n
                    }, {
                        [cg]: [aG, aE, Y, ad, ax],
                        endpoint: {
                            [cl]: s,
                            [cm]: ay,
                            [cs]: ai
                        },
                        [cf]: n
                    }, {
                        [cg]: [aG, aE, Y, ad, az, aA],
                        rules: [{
                            [cg]: bR,
                            endpoint: bu,
                            [cf]: n
                        }, {
                            endpoint: bu,
                            [cf]: n
                        }],
                        [cf]: o
                    }, {
                        [cg]: [aG, aE, Y, ad, az, aD],
                        endpoint: bu,
                        [cf]: n
                    }, {
                        [cg]: [aG, aE, ao, ax],
                        endpoint: {
                            [cl]: R,
                            [cm]: ay,
                            [cs]: ai
                        },
                        [cf]: n
                    }, {
                        [cg]: [aG, aE, ao, az, aA],
                        rules: [{
                            [cg]: bR,
                            endpoint: {
                                [cl]: R,
                                [cm]: aC,
                                [cs]: ai
                            },
                            [cf]: n
                        }, {
                            endpoint: bv,
                            [cf]: n
                        }],
                        [cf]: o
                    }, {
                        [cg]: [aG, aE, ao, az, aD],
                        endpoint: bv,
                        [cf]: n
                    }],
                    [cf]: o
                }, aP],
                [cf]: o
            }],
            [cf]: o
        }],
        [cf]: o
    }, {
        error: "A region must be set when sending requests to S3.",
        [cf]: e
    }]
};
var ruleSet = _data;

// node_modules/@aws-sdk/client-s3/dist-es/endpoint/endpointResolver.js
var cache = new EndpointCache({
    size: 50,
    params: ["Accelerate", "Bucket", "DisableAccessPoints", "DisableMultiRegionAccessPoints", "DisableS3ExpressSessionAuth", "Endpoint", "ForcePathStyle", "Region", "UseArnRegion", "UseDualStack", "UseFIPS", "UseGlobalEndpoint", "UseObjectLambdaEndpoint", "UseS3ExpressControlEndpoint"]
});
var defaultEndpointResolver = (endpointParams, context = {}) => {
    return cache.get(endpointParams, () => resolveEndpoint(ruleSet, {
        endpointParams,
        logger: context.logger
    }));
};
customEndpointFunctions.aws = awsEndpointFunctions;

// node_modules/@aws-sdk/client-s3/dist-es/auth/httpAuthSchemeProvider.js
var createEndpointRuleSetHttpAuthSchemeParametersProvider = (defaultHttpAuthSchemeParametersProvider) => (config, context, input) => __async(void 0, null, function* () {
    if (!input) {
        throw new Error(`Could not find \`input\` for \`defaultEndpointRuleSetHttpAuthSchemeParametersProvider\``);
    }
    const defaultParameters = yield defaultHttpAuthSchemeParametersProvider(config, context, input);
    const instructionsFn = getSmithyContext(context)?.commandInstance?.constructor?.getEndpointParameterInstructions;
    if (!instructionsFn) {
        throw new Error(`getEndpointParameterInstructions() is not defined on \`${context.commandName}\``);
    }
    const endpointParameters = yield resolveParams(input, {
        getEndpointParameterInstructions: instructionsFn
    }, config);
    return Object.assign(defaultParameters, endpointParameters);
});
var _defaultS3HttpAuthSchemeParametersProvider = (config, context, input) => __async(void 0, null, function* () {
    return {
        operation: getSmithyContext(context).operation,
        region: (yield normalizeProvider(config.region)()) || (() => {
            throw new Error("expected `region` to be configured for `aws.auth#sigv4`");
        })()
    };
});
var defaultS3HttpAuthSchemeParametersProvider = createEndpointRuleSetHttpAuthSchemeParametersProvider(_defaultS3HttpAuthSchemeParametersProvider);

function createAwsAuthSigv4HttpAuthOption(authParameters) {
    return {
        schemeId: "aws.auth#sigv4",
        signingProperties: {
            name: "s3",
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

function createAwsAuthSigv4aHttpAuthOption(authParameters) {
    return {
        schemeId: "aws.auth#sigv4a",
        signingProperties: {
            name: "s3",
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

var createEndpointRuleSetHttpAuthSchemeProvider = (defaultEndpointResolver2, defaultHttpAuthSchemeResolver, createHttpAuthOptionFunctions) => {
    const endpointRuleSetHttpAuthSchemeProvider = (authParameters) => {
        const endpoint = defaultEndpointResolver2(authParameters);
        const authSchemes = endpoint.properties?.authSchemes;
        if (!authSchemes) {
            return defaultHttpAuthSchemeResolver(authParameters);
        }
        const options = [];
        for (const scheme of authSchemes) {
            const _a = scheme, {
                name: resolvedName,
                properties = {}
            } = _a, rest = __objRest(_a, [
                "name",
                "properties"
            ]);
            const name = resolvedName.toLowerCase();
            if (resolvedName !== name) {
                console.warn(`HttpAuthScheme has been normalized with lowercasing: \`${resolvedName}\` to \`${name}\``);
            }
            let schemeId;
            if (name === "sigv4a") {
                schemeId = "aws.auth#sigv4a";
                const sigv4Present = authSchemes.find((s2) => {
                    const name2 = s2.name.toLowerCase();
                    return name2 !== "sigv4a" && name2.startsWith("sigv4");
                });
                if (!signatureV4CrtContainer.CrtSignerV4 && sigv4Present) {
                    continue;
                }
            } else if (name.startsWith("sigv4")) {
                schemeId = "aws.auth#sigv4";
            } else {
                throw new Error(`Unknown HttpAuthScheme found in \`@smithy.rules#endpointRuleSet\`: \`${name}\``);
            }
            const createOption = createHttpAuthOptionFunctions[schemeId];
            if (!createOption) {
                throw new Error(`Could not find HttpAuthOption create function for \`${schemeId}\``);
            }
            const option = createOption(authParameters);
            option.schemeId = schemeId;
            option.signingProperties = __spreadValues(__spreadValues(__spreadValues({}, option.signingProperties || {}), rest), properties);
            options.push(option);
        }
        return options;
    };
    return endpointRuleSetHttpAuthSchemeProvider;
};
var _defaultS3HttpAuthSchemeProvider = (authParameters) => {
    const options = [];
    switch (authParameters.operation) {
        default: {
            options.push(createAwsAuthSigv4HttpAuthOption(authParameters));
            options.push(createAwsAuthSigv4aHttpAuthOption(authParameters));
        }
    }
    return options;
};
var defaultS3HttpAuthSchemeProvider = createEndpointRuleSetHttpAuthSchemeProvider(defaultEndpointResolver, _defaultS3HttpAuthSchemeProvider, {
    "aws.auth#sigv4": createAwsAuthSigv4HttpAuthOption,
    "aws.auth#sigv4a": createAwsAuthSigv4aHttpAuthOption
});
var resolveHttpAuthSchemeConfig = (config) => {
    const config_0 = resolveAwsSdkSigV4Config(config);
    const config_1 = resolveAwsSdkSigV4AConfig(config_0);
    return __spreadValues({}, config_1);
};

// node_modules/@aws-sdk/client-s3/dist-es/endpoint/EndpointParameters.js
var resolveClientEndpointParameters = (options) => {
    return __spreadProps(__spreadValues({}, options), {
        useFipsEndpoint: options.useFipsEndpoint ?? false,
        useDualstackEndpoint: options.useDualstackEndpoint ?? false,
        forcePathStyle: options.forcePathStyle ?? false,
        useAccelerateEndpoint: options.useAccelerateEndpoint ?? false,
        useGlobalEndpoint: options.useGlobalEndpoint ?? false,
        disableMultiregionAccessPoints: options.disableMultiregionAccessPoints ?? false,
        defaultSigningName: "s3"
    });
};
var commonParams = {
    ForcePathStyle: {
        type: "clientContextParams",
        name: "forcePathStyle"
    },
    UseArnRegion: {
        type: "clientContextParams",
        name: "useArnRegion"
    },
    DisableMultiRegionAccessPoints: {
        type: "clientContextParams",
        name: "disableMultiregionAccessPoints"
    },
    Accelerate: {
        type: "clientContextParams",
        name: "useAccelerateEndpoint"
    },
    DisableS3ExpressSessionAuth: {
        type: "clientContextParams",
        name: "disableS3ExpressSessionAuth"
    },
    UseGlobalEndpoint: {
        type: "builtInParams",
        name: "useGlobalEndpoint"
    },
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

// node_modules/@aws-sdk/client-s3/dist-es/models/S3ServiceException.js
var S3ServiceException = class _S3ServiceException extends ServiceException {
    constructor(options) {
        super(options);
        Object.setPrototypeOf(this, _S3ServiceException.prototype);
    }
};

// node_modules/@aws-sdk/client-s3/dist-es/models/models_0.js
var NoSuchUpload = class _NoSuchUpload extends S3ServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "NoSuchUpload",
            $fault: "client"
        }, opts));
        this.name = "NoSuchUpload";
        this.$fault = "client";
        Object.setPrototypeOf(this, _NoSuchUpload.prototype);
    }
};
var ObjectNotInActiveTierError = class _ObjectNotInActiveTierError extends S3ServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "ObjectNotInActiveTierError",
            $fault: "client"
        }, opts));
        this.name = "ObjectNotInActiveTierError";
        this.$fault = "client";
        Object.setPrototypeOf(this, _ObjectNotInActiveTierError.prototype);
    }
};
var BucketAlreadyExists = class _BucketAlreadyExists extends S3ServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "BucketAlreadyExists",
            $fault: "client"
        }, opts));
        this.name = "BucketAlreadyExists";
        this.$fault = "client";
        Object.setPrototypeOf(this, _BucketAlreadyExists.prototype);
    }
};
var BucketAlreadyOwnedByYou = class _BucketAlreadyOwnedByYou extends S3ServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "BucketAlreadyOwnedByYou",
            $fault: "client"
        }, opts));
        this.name = "BucketAlreadyOwnedByYou";
        this.$fault = "client";
        Object.setPrototypeOf(this, _BucketAlreadyOwnedByYou.prototype);
    }
};
var NoSuchBucket = class _NoSuchBucket extends S3ServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "NoSuchBucket",
            $fault: "client"
        }, opts));
        this.name = "NoSuchBucket";
        this.$fault = "client";
        Object.setPrototypeOf(this, _NoSuchBucket.prototype);
    }
};
var AnalyticsFilter;
(function (AnalyticsFilter2) {
    AnalyticsFilter2.visit = (value, visitor) => {
        if (value.Prefix !== void 0) return visitor.Prefix(value.Prefix);
        if (value.Tag !== void 0) return visitor.Tag(value.Tag);
        if (value.And !== void 0) return visitor.And(value.And);
        return visitor._(value.$unknown[0], value.$unknown[1]);
    };
})(AnalyticsFilter || (AnalyticsFilter = {}));
var MetricsFilter;
(function (MetricsFilter2) {
    MetricsFilter2.visit = (value, visitor) => {
        if (value.Prefix !== void 0) return visitor.Prefix(value.Prefix);
        if (value.Tag !== void 0) return visitor.Tag(value.Tag);
        if (value.AccessPointArn !== void 0) return visitor.AccessPointArn(value.AccessPointArn);
        if (value.And !== void 0) return visitor.And(value.And);
        return visitor._(value.$unknown[0], value.$unknown[1]);
    };
})(MetricsFilter || (MetricsFilter = {}));
var InvalidObjectState = class _InvalidObjectState extends S3ServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "InvalidObjectState",
            $fault: "client"
        }, opts));
        this.name = "InvalidObjectState";
        this.$fault = "client";
        Object.setPrototypeOf(this, _InvalidObjectState.prototype);
        this.StorageClass = opts.StorageClass;
        this.AccessTier = opts.AccessTier;
    }
};
var NoSuchKey = class _NoSuchKey extends S3ServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "NoSuchKey",
            $fault: "client"
        }, opts));
        this.name = "NoSuchKey";
        this.$fault = "client";
        Object.setPrototypeOf(this, _NoSuchKey.prototype);
    }
};
var NotFound = class _NotFound extends S3ServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "NotFound",
            $fault: "client"
        }, opts));
        this.name = "NotFound";
        this.$fault = "client";
        Object.setPrototypeOf(this, _NotFound.prototype);
    }
};
var SessionCredentialsFilterSensitiveLog = (obj) => __spreadValues(__spreadValues(__spreadValues({}, obj), obj.SecretAccessKey && {
    SecretAccessKey: SENSITIVE_STRING
}), obj.SessionToken && {
    SessionToken: SENSITIVE_STRING
});
var CreateSessionOutputFilterSensitiveLog = (obj) => __spreadValues(__spreadValues(__spreadValues(__spreadValues({}, obj), obj.SSEKMSKeyId && {
    SSEKMSKeyId: SENSITIVE_STRING
}), obj.SSEKMSEncryptionContext && {
    SSEKMSEncryptionContext: SENSITIVE_STRING
}), obj.Credentials && {
    Credentials: SessionCredentialsFilterSensitiveLog(obj.Credentials)
});
var CreateSessionRequestFilterSensitiveLog = (obj) => __spreadValues(__spreadValues(__spreadValues({}, obj), obj.SSEKMSKeyId && {
    SSEKMSKeyId: SENSITIVE_STRING
}), obj.SSEKMSEncryptionContext && {
    SSEKMSEncryptionContext: SENSITIVE_STRING
});
var GetObjectOutputFilterSensitiveLog = (obj) => __spreadValues(__spreadValues({}, obj), obj.SSEKMSKeyId && {
    SSEKMSKeyId: SENSITIVE_STRING
});
var GetObjectRequestFilterSensitiveLog = (obj) => __spreadValues(__spreadValues({}, obj), obj.SSECustomerKey && {
    SSECustomerKey: SENSITIVE_STRING
});

// node_modules/@aws-sdk/xml-builder/dist-es/escape-attribute.js
function escapeAttribute(value) {
    return value.replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;").replace(/"/g, "&quot;");
}

// node_modules/@aws-sdk/xml-builder/dist-es/escape-element.js
function escapeElement(value) {
    return value.replace(/&/g, "&amp;").replace(/"/g, "&quot;").replace(/'/g, "&apos;").replace(/</g, "&lt;").replace(/>/g, "&gt;").replace(/\r/g, "&#x0D;").replace(/\n/g, "&#x0A;").replace(/\u0085/g, "&#x85;").replace(/\u2028/, "&#x2028;");
}

// node_modules/@aws-sdk/xml-builder/dist-es/XmlText.js
var XmlText = class {
    constructor(value) {
        this.value = value;
    }

    toString() {
        return escapeElement("" + this.value);
    }
};

// node_modules/@aws-sdk/xml-builder/dist-es/XmlNode.js
var XmlNode = class _XmlNode {
    constructor(name, children = []) {
        this.name = name;
        this.children = children;
        this.attributes = {};
    }

    static of(name, childText, withName) {
        const node = new _XmlNode(name);
        if (childText !== void 0) {
            node.addChildNode(new XmlText(childText));
        }
        if (withName !== void 0) {
            node.withName(withName);
        }
        return node;
    }

    withName(name) {
        this.name = name;
        return this;
    }

    addAttribute(name, value) {
        this.attributes[name] = value;
        return this;
    }

    addChildNode(child) {
        this.children.push(child);
        return this;
    }

    removeAttribute(name) {
        delete this.attributes[name];
        return this;
    }

    n(name) {
        this.name = name;
        return this;
    }

    c(child) {
        this.children.push(child);
        return this;
    }

    a(name, value) {
        if (value != null) {
            this.attributes[name] = value;
        }
        return this;
    }

    cc(input, field, withName = field) {
        if (input[field] != null) {
            const node = _XmlNode.of(field, input[field]).withName(withName);
            this.c(node);
        }
    }

    l(input, listName, memberName, valueProvider) {
        if (input[listName] != null) {
            const nodes = valueProvider();
            nodes.map((node) => {
                node.withName(memberName);
                this.c(node);
            });
        }
    }

    lc(input, listName, memberName, valueProvider) {
        if (input[listName] != null) {
            const nodes = valueProvider();
            const containerNode = new _XmlNode(memberName);
            nodes.map((node) => {
                containerNode.c(node);
            });
            this.c(containerNode);
        }
    }

    toString() {
        const hasChildren = Boolean(this.children.length);
        let xmlText = `<${this.name}`;
        const attributes = this.attributes;
        for (const attributeName of Object.keys(attributes)) {
            const attribute2 = attributes[attributeName];
            if (attribute2 != null) {
                xmlText += ` ${attributeName}="${escapeAttribute("" + attribute2)}"`;
            }
        }
        return xmlText += !hasChildren ? "/>" : `>${this.children.map((c2) => c2.toString()).join("")}</${this.name}>`;
    }
};

// node_modules/@aws-sdk/client-s3/dist-es/models/models_1.js
var ObjectAlreadyInActiveTierError = class _ObjectAlreadyInActiveTierError extends S3ServiceException {
    constructor(opts) {
        super(__spreadValues({
            name: "ObjectAlreadyInActiveTierError",
            $fault: "client"
        }, opts));
        this.name = "ObjectAlreadyInActiveTierError";
        this.$fault = "client";
        Object.setPrototypeOf(this, _ObjectAlreadyInActiveTierError.prototype);
    }
};
var SelectObjectContentEventStream;
(function (SelectObjectContentEventStream2) {
    SelectObjectContentEventStream2.visit = (value, visitor) => {
        if (value.Records !== void 0) return visitor.Records(value.Records);
        if (value.Stats !== void 0) return visitor.Stats(value.Stats);
        if (value.Progress !== void 0) return visitor.Progress(value.Progress);
        if (value.Cont !== void 0) return visitor.Cont(value.Cont);
        if (value.End !== void 0) return visitor.End(value.End);
        return visitor._(value.$unknown[0], value.$unknown[1]);
    };
})(SelectObjectContentEventStream || (SelectObjectContentEventStream = {}));
var PutObjectOutputFilterSensitiveLog = (obj) => __spreadValues(__spreadValues(__spreadValues({}, obj), obj.SSEKMSKeyId && {
    SSEKMSKeyId: SENSITIVE_STRING
}), obj.SSEKMSEncryptionContext && {
    SSEKMSEncryptionContext: SENSITIVE_STRING
});
var PutObjectRequestFilterSensitiveLog = (obj) => __spreadValues(__spreadValues(__spreadValues(__spreadValues({}, obj), obj.SSECustomerKey && {
    SSECustomerKey: SENSITIVE_STRING
}), obj.SSEKMSKeyId && {
    SSEKMSKeyId: SENSITIVE_STRING
}), obj.SSEKMSEncryptionContext && {
    SSEKMSEncryptionContext: SENSITIVE_STRING
});

// node_modules/@aws-sdk/client-s3/dist-es/protocols/Aws_restXml.js
var se_CreateBucketCommand = (input, context) => __async(void 0, null, function* () {
    const b2 = requestBuilder(input, context);
    const headers = map2({}, isSerializableHeaderValue, {
        "content-type": "application/xml",
        [_xaa]: input[_ACL],
        [_xagfc]: input[_GFC],
        [_xagr]: input[_GR],
        [_xagra]: input[_GRACP],
        [_xagw]: input[_GW],
        [_xagwa]: input[_GWACP],
        [_xabole]: [() => isSerializableHeaderValue(input[_OLEFB]), () => input[_OLEFB].toString()],
        [_xaoo]: input[_OO]
    });
    b2.bp("/");
    b2.p("Bucket", () => input.Bucket, "{Bucket}", false);
    let body;
    let contents;
    if (input.CreateBucketConfiguration !== void 0) {
        contents = se_CreateBucketConfiguration(input.CreateBucketConfiguration, context);
        body = _ve;
        contents.a("xmlns", "http://s3.amazonaws.com/doc/2006-03-01/");
        body += contents.toString();
    }
    b2.m("PUT").h(headers).b(body);
    return b2.build();
});
var se_CreateSessionCommand = (input, context) => __async(void 0, null, function* () {
    const b2 = requestBuilder(input, context);
    const headers = map2({}, isSerializableHeaderValue, {
        [_xacsm]: input[_SM],
        [_xasse]: input[_SSE],
        [_xasseakki]: input[_SSEKMSKI],
        [_xassec]: input[_SSEKMSEC],
        [_xassebke]: [() => isSerializableHeaderValue(input[_BKE]), () => input[_BKE].toString()]
    });
    b2.bp("/");
    b2.p("Bucket", () => input.Bucket, "{Bucket}", false);
    const query = map2({
        [_s]: [, ""]
    });
    let body;
    b2.m("GET").h(headers).q(query).b(body);
    return b2.build();
});
var se_DeleteBucketCommand = (input, context) => __async(void 0, null, function* () {
    const b2 = requestBuilder(input, context);
    const headers = map2({}, isSerializableHeaderValue, {
        [_xaebo]: input[_EBO]
    });
    b2.bp("/");
    b2.p("Bucket", () => input.Bucket, "{Bucket}", false);
    let body;
    b2.m("DELETE").h(headers).b(body);
    return b2.build();
});
var se_DeleteObjectCommand = (input, context) => __async(void 0, null, function* () {
    const b2 = requestBuilder(input, context);
    const headers = map2({}, isSerializableHeaderValue, {
        [_xam]: input[_MFA],
        [_xarp]: input[_RP],
        [_xabgr]: [() => isSerializableHeaderValue(input[_BGR]), () => input[_BGR].toString()],
        [_xaebo]: input[_EBO]
    });
    b2.bp("/{Key+}");
    b2.p("Bucket", () => input.Bucket, "{Bucket}", false);
    b2.p("Key", () => input.Key, "{Key+}", true);
    const query = map2({
        [_xi]: [, "DeleteObject"],
        [_vI]: [, input[_VI]]
    });
    let body;
    b2.m("DELETE").h(headers).q(query).b(body);
    return b2.build();
});
var se_GetObjectCommand = (input, context) => __async(void 0, null, function* () {
    const b2 = requestBuilder(input, context);
    const headers = map2({}, isSerializableHeaderValue, {
        [_im]: input[_IM],
        [_ims]: [() => isSerializableHeaderValue(input[_IMS]), () => dateToUtcString(input[_IMS]).toString()],
        [_inm]: input[_INM],
        [_ius]: [() => isSerializableHeaderValue(input[_IUS]), () => dateToUtcString(input[_IUS]).toString()],
        [_ra]: input[_R],
        [_xasseca]: input[_SSECA],
        [_xasseck]: input[_SSECK],
        [_xasseckm]: input[_SSECKMD],
        [_xarp]: input[_RP],
        [_xaebo]: input[_EBO],
        [_xacm]: input[_CM]
    });
    b2.bp("/{Key+}");
    b2.p("Bucket", () => input.Bucket, "{Bucket}", false);
    b2.p("Key", () => input.Key, "{Key+}", true);
    const query = map2({
        [_xi]: [, "GetObject"],
        [_rcc]: [, input[_RCC]],
        [_rcd]: [, input[_RCD]],
        [_rce]: [, input[_RCE]],
        [_rcl]: [, input[_RCL]],
        [_rct]: [, input[_RCT]],
        [_re]: [() => input.ResponseExpires !== void 0, () => dateToUtcString(input[_RE]).toString()],
        [_vI]: [, input[_VI]],
        [_pN]: [() => input.PartNumber !== void 0, () => input[_PN].toString()]
    });
    let body;
    b2.m("GET").h(headers).q(query).b(body);
    return b2.build();
});
var se_ListObjectsV2Command = (input, context) => __async(void 0, null, function* () {
    const b2 = requestBuilder(input, context);
    const headers = map2({}, isSerializableHeaderValue, {
        [_xarp]: input[_RP],
        [_xaebo]: input[_EBO],
        [_xaooa]: [() => isSerializableHeaderValue(input[_OOA]), () => (input[_OOA] || []).map(quoteHeader).join(", ")]
    });
    b2.bp("/");
    b2.p("Bucket", () => input.Bucket, "{Bucket}", false);
    const query = map2({
        [_lt]: [, "2"],
        [_de]: [, input[_D]],
        [_et]: [, input[_ET]],
        [_mk]: [() => input.MaxKeys !== void 0, () => input[_MK].toString()],
        [_pr]: [, input[_P]],
        [_ct_]: [, input[_CTo]],
        [_fo]: [() => input.FetchOwner !== void 0, () => input[_FO].toString()],
        [_sa]: [, input[_SA]]
    });
    let body;
    b2.m("GET").h(headers).q(query).b(body);
    return b2.build();
});
var se_PutObjectCommand = (input, context) => __async(void 0, null, function* () {
    const b2 = requestBuilder(input, context);
    const headers = map2({}, isSerializableHeaderValue, __spreadValues({
        [_ct]: input[_CT] || "application/octet-stream",
        [_xaa]: input[_ACL],
        [_cc]: input[_CC],
        [_cd]: input[_CD],
        [_ce]: input[_CE],
        [_cl]: input[_CL],
        [_cl_]: [() => isSerializableHeaderValue(input[_CLo]), () => input[_CLo].toString()],
        [_cm]: input[_CMD],
        [_xasca]: input[_CA],
        [_xacc]: input[_CCRC],
        [_xacc_]: input[_CCRCC],
        [_xacs]: input[_CSHA],
        [_xacs_]: input[_CSHAh],
        [_e]: [() => isSerializableHeaderValue(input[_E]), () => dateToUtcString(input[_E]).toString()],
        [_inm]: input[_INM],
        [_xagfc]: input[_GFC],
        [_xagr]: input[_GR],
        [_xagra]: input[_GRACP],
        [_xagwa]: input[_GWACP],
        [_xasse]: input[_SSE],
        [_xasc]: input[_SC],
        [_xawrl]: input[_WRL],
        [_xasseca]: input[_SSECA],
        [_xasseck]: input[_SSECK],
        [_xasseckm]: input[_SSECKMD],
        [_xasseakki]: input[_SSEKMSKI],
        [_xassec]: input[_SSEKMSEC],
        [_xassebke]: [() => isSerializableHeaderValue(input[_BKE]), () => input[_BKE].toString()],
        [_xarp]: input[_RP],
        [_xat]: input[_T],
        [_xaolm]: input[_OLM],
        [_xaolrud]: [() => isSerializableHeaderValue(input[_OLRUD]), () => serializeDateTime(input[_OLRUD]).toString()],
        [_xaollh]: input[_OLLHS],
        [_xaebo]: input[_EBO]
    }, input.Metadata !== void 0 && Object.keys(input.Metadata).reduce((acc, suffix) => {
        acc[`x-amz-meta-${suffix.toLowerCase()}`] = input.Metadata[suffix];
        return acc;
    }, {})));
    b2.bp("/{Key+}");
    b2.p("Bucket", () => input.Bucket, "{Bucket}", false);
    b2.p("Key", () => input.Key, "{Key+}", true);
    const query = map2({
        [_xi]: [, "PutObject"]
    });
    let body;
    let contents;
    if (input.Body !== void 0) {
        contents = input.Body;
        body = contents;
    }
    b2.m("PUT").h(headers).q(query).b(body);
    return b2.build();
});
var de_CreateBucketCommand = (output, context) => __async(void 0, null, function* () {
    if (output.statusCode !== 200 && output.statusCode >= 300) {
        return de_CommandError(output, context);
    }
    const contents = map2({
        $metadata: deserializeMetadata(output),
        [_L]: [, output.headers[_lo]]
    });
    yield collectBody(output.body, context);
    return contents;
});
var de_CreateSessionCommand = (output, context) => __async(void 0, null, function* () {
    if (output.statusCode !== 200 && output.statusCode >= 300) {
        return de_CommandError(output, context);
    }
    const contents = map2({
        $metadata: deserializeMetadata(output),
        [_SSE]: [, output.headers[_xasse]],
        [_SSEKMSKI]: [, output.headers[_xasseakki]],
        [_SSEKMSEC]: [, output.headers[_xassec]],
        [_BKE]: [() => void 0 !== output.headers[_xassebke], () => parseBoolean(output.headers[_xassebke])]
    });
    const data = expectNonNull(expectObject(yield parseXmlBody(output.body, context)), "body");
    if (data[_C] != null) {
        contents[_C] = de_SessionCredentials(data[_C], context);
    }
    return contents;
});
var de_DeleteBucketCommand = (output, context) => __async(void 0, null, function* () {
    if (output.statusCode !== 204 && output.statusCode >= 300) {
        return de_CommandError(output, context);
    }
    const contents = map2({
        $metadata: deserializeMetadata(output)
    });
    yield collectBody(output.body, context);
    return contents;
});
var de_DeleteObjectCommand = (output, context) => __async(void 0, null, function* () {
    if (output.statusCode !== 204 && output.statusCode >= 300) {
        return de_CommandError(output, context);
    }
    const contents = map2({
        $metadata: deserializeMetadata(output),
        [_DM]: [() => void 0 !== output.headers[_xadm], () => parseBoolean(output.headers[_xadm])],
        [_VI]: [, output.headers[_xavi]],
        [_RC]: [, output.headers[_xarc]]
    });
    yield collectBody(output.body, context);
    return contents;
});
var de_GetObjectCommand = (output, context) => __async(void 0, null, function* () {
    if (output.statusCode !== 200 && output.statusCode >= 300) {
        return de_CommandError(output, context);
    }
    const contents = map2({
        $metadata: deserializeMetadata(output),
        [_DM]: [() => void 0 !== output.headers[_xadm], () => parseBoolean(output.headers[_xadm])],
        [_AR]: [, output.headers[_ar]],
        [_Exp]: [, output.headers[_xae]],
        [_Re]: [, output.headers[_xar]],
        [_LM]: [() => void 0 !== output.headers[_lm], () => expectNonNull(parseRfc7231DateTime(output.headers[_lm]))],
        [_CLo]: [() => void 0 !== output.headers[_cl_], () => strictParseLong(output.headers[_cl_])],
        [_ETa]: [, output.headers[_eta]],
        [_CCRC]: [, output.headers[_xacc]],
        [_CCRCC]: [, output.headers[_xacc_]],
        [_CSHA]: [, output.headers[_xacs]],
        [_CSHAh]: [, output.headers[_xacs_]],
        [_MM]: [() => void 0 !== output.headers[_xamm], () => strictParseInt32(output.headers[_xamm])],
        [_VI]: [, output.headers[_xavi]],
        [_CC]: [, output.headers[_cc]],
        [_CD]: [, output.headers[_cd]],
        [_CE]: [, output.headers[_ce]],
        [_CL]: [, output.headers[_cl]],
        [_CR]: [, output.headers[_cr]],
        [_CT]: [, output.headers[_ct]],
        [_E]: [() => void 0 !== output.headers[_e], () => expectNonNull(parseRfc7231DateTime(output.headers[_e]))],
        [_ES]: [, output.headers[_ex]],
        [_WRL]: [, output.headers[_xawrl]],
        [_SSE]: [, output.headers[_xasse]],
        [_SSECA]: [, output.headers[_xasseca]],
        [_SSECKMD]: [, output.headers[_xasseckm]],
        [_SSEKMSKI]: [, output.headers[_xasseakki]],
        [_BKE]: [() => void 0 !== output.headers[_xassebke], () => parseBoolean(output.headers[_xassebke])],
        [_SC]: [, output.headers[_xasc]],
        [_RC]: [, output.headers[_xarc]],
        [_RS]: [, output.headers[_xars]],
        [_PC]: [() => void 0 !== output.headers[_xampc], () => strictParseInt32(output.headers[_xampc])],
        [_TC]: [() => void 0 !== output.headers[_xatc], () => strictParseInt32(output.headers[_xatc])],
        [_OLM]: [, output.headers[_xaolm]],
        [_OLRUD]: [() => void 0 !== output.headers[_xaolrud], () => expectNonNull(parseRfc3339DateTimeWithOffset(output.headers[_xaolrud]))],
        [_OLLHS]: [, output.headers[_xaollh]],
        Metadata: [, Object.keys(output.headers).filter((header) => header.startsWith("x-amz-meta-")).reduce((acc, header) => {
            acc[header.substring(11)] = output.headers[header];
            return acc;
        }, {})]
    });
    const data = output.body;
    context.sdkStreamMixin(data);
    contents.Body = data;
    return contents;
});
var de_ListObjectsV2Command = (output, context) => __async(void 0, null, function* () {
    if (output.statusCode !== 200 && output.statusCode >= 300) {
        return de_CommandError(output, context);
    }
    const contents = map2({
        $metadata: deserializeMetadata(output),
        [_RC]: [, output.headers[_xarc]]
    });
    const data = expectNonNull(expectObject(yield parseXmlBody(output.body, context)), "body");
    if (data.CommonPrefixes === "") {
        contents[_CP] = [];
    } else if (data[_CP] != null) {
        contents[_CP] = de_CommonPrefixList(getArrayIfSingleItem(data[_CP]), context);
    }
    if (data.Contents === "") {
        contents[_Co] = [];
    } else if (data[_Co] != null) {
        contents[_Co] = de_ObjectList(getArrayIfSingleItem(data[_Co]), context);
    }
    if (data[_CTo] != null) {
        contents[_CTo] = expectString(data[_CTo]);
    }
    if (data[_D] != null) {
        contents[_D] = expectString(data[_D]);
    }
    if (data[_ET] != null) {
        contents[_ET] = expectString(data[_ET]);
    }
    if (data[_IT] != null) {
        contents[_IT] = parseBoolean(data[_IT]);
    }
    if (data[_KC] != null) {
        contents[_KC] = strictParseInt32(data[_KC]);
    }
    if (data[_MK] != null) {
        contents[_MK] = strictParseInt32(data[_MK]);
    }
    if (data[_N] != null) {
        contents[_N] = expectString(data[_N]);
    }
    if (data[_NCT] != null) {
        contents[_NCT] = expectString(data[_NCT]);
    }
    if (data[_P] != null) {
        contents[_P] = expectString(data[_P]);
    }
    if (data[_SA] != null) {
        contents[_SA] = expectString(data[_SA]);
    }
    return contents;
});
var de_PutObjectCommand = (output, context) => __async(void 0, null, function* () {
    if (output.statusCode !== 200 && output.statusCode >= 300) {
        return de_CommandError(output, context);
    }
    const contents = map2({
        $metadata: deserializeMetadata(output),
        [_Exp]: [, output.headers[_xae]],
        [_ETa]: [, output.headers[_eta]],
        [_CCRC]: [, output.headers[_xacc]],
        [_CCRCC]: [, output.headers[_xacc_]],
        [_CSHA]: [, output.headers[_xacs]],
        [_CSHAh]: [, output.headers[_xacs_]],
        [_SSE]: [, output.headers[_xasse]],
        [_VI]: [, output.headers[_xavi]],
        [_SSECA]: [, output.headers[_xasseca]],
        [_SSECKMD]: [, output.headers[_xasseckm]],
        [_SSEKMSKI]: [, output.headers[_xasseakki]],
        [_SSEKMSEC]: [, output.headers[_xassec]],
        [_BKE]: [() => void 0 !== output.headers[_xassebke], () => parseBoolean(output.headers[_xassebke])],
        [_RC]: [, output.headers[_xarc]]
    });
    yield collectBody(output.body, context);
    return contents;
});
var de_CommandError = (output, context) => __async(void 0, null, function* () {
    const parsedOutput = __spreadProps(__spreadValues({}, output), {
        body: yield parseXmlErrorBody(output.body, context)
    });
    const errorCode = loadRestXmlErrorCode(output, parsedOutput.body);
    switch (errorCode) {
        case "NoSuchUpload":
        case "com.amazonaws.s3#NoSuchUpload":
            throw yield de_NoSuchUploadRes(parsedOutput, context);
        case "ObjectNotInActiveTierError":
        case "com.amazonaws.s3#ObjectNotInActiveTierError":
            throw yield de_ObjectNotInActiveTierErrorRes(parsedOutput, context);
        case "BucketAlreadyExists":
        case "com.amazonaws.s3#BucketAlreadyExists":
            throw yield de_BucketAlreadyExistsRes(parsedOutput, context);
        case "BucketAlreadyOwnedByYou":
        case "com.amazonaws.s3#BucketAlreadyOwnedByYou":
            throw yield de_BucketAlreadyOwnedByYouRes(parsedOutput, context);
        case "NoSuchBucket":
        case "com.amazonaws.s3#NoSuchBucket":
            throw yield de_NoSuchBucketRes(parsedOutput, context);
        case "InvalidObjectState":
        case "com.amazonaws.s3#InvalidObjectState":
            throw yield de_InvalidObjectStateRes(parsedOutput, context);
        case "NoSuchKey":
        case "com.amazonaws.s3#NoSuchKey":
            throw yield de_NoSuchKeyRes(parsedOutput, context);
        case "NotFound":
        case "com.amazonaws.s3#NotFound":
            throw yield de_NotFoundRes(parsedOutput, context);
        case "ObjectAlreadyInActiveTierError":
        case "com.amazonaws.s3#ObjectAlreadyInActiveTierError":
            throw yield de_ObjectAlreadyInActiveTierErrorRes(parsedOutput, context);
        default:
            const parsedBody = parsedOutput.body;
            return throwDefaultError({
                output,
                parsedBody,
                errorCode
            });
    }
});
var throwDefaultError = withBaseException(S3ServiceException);
var de_BucketAlreadyExistsRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const exception = new BucketAlreadyExists(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_BucketAlreadyOwnedByYouRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const exception = new BucketAlreadyOwnedByYou(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_InvalidObjectStateRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    if (data[_AT] != null) {
        contents[_AT] = expectString(data[_AT]);
    }
    if (data[_SC] != null) {
        contents[_SC] = expectString(data[_SC]);
    }
    const exception = new InvalidObjectState(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_NoSuchBucketRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const exception = new NoSuchBucket(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_NoSuchKeyRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const exception = new NoSuchKey(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_NoSuchUploadRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const exception = new NoSuchUpload(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_NotFoundRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const exception = new NotFound(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_ObjectAlreadyInActiveTierErrorRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const exception = new ObjectAlreadyInActiveTierError(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var de_ObjectNotInActiveTierErrorRes = (parsedOutput, context) => __async(void 0, null, function* () {
    const contents = map2({});
    const data = parsedOutput.body;
    const exception = new ObjectNotInActiveTierError(__spreadValues({
        $metadata: deserializeMetadata(parsedOutput)
    }, contents));
    return decorateServiceException(exception, parsedOutput.body);
});
var se_BucketInfo = (input, context) => {
    const bn2 = new XmlNode(_BI);
    bn2.cc(input, _DR);
    if (input[_Ty] != null) {
        bn2.c(XmlNode.of(_BT, input[_Ty]).n(_Ty));
    }
    return bn2;
};
var se_CreateBucketConfiguration = (input, context) => {
    const bn2 = new XmlNode(_CBC);
    if (input[_LC] != null) {
        bn2.c(XmlNode.of(_BLCu, input[_LC]).n(_LC));
    }
    if (input[_L] != null) {
        bn2.c(se_LocationInfo(input[_L], context).n(_L));
    }
    if (input[_B] != null) {
        bn2.c(se_BucketInfo(input[_B], context).n(_B));
    }
    return bn2;
};
var se_LocationInfo = (input, context) => {
    const bn2 = new XmlNode(_LI);
    if (input[_Ty] != null) {
        bn2.c(XmlNode.of(_LT, input[_Ty]).n(_Ty));
    }
    if (input[_N] != null) {
        bn2.c(XmlNode.of(_LNAS, input[_N]).n(_N));
    }
    return bn2;
};
var de_ChecksumAlgorithmList = (output, context) => {
    return (output || []).filter((e2) => e2 != null).map((entry) => {
        return expectString(entry);
    });
};
var de_CommonPrefix = (output, context) => {
    const contents = {};
    if (output[_P] != null) {
        contents[_P] = expectString(output[_P]);
    }
    return contents;
};
var de_CommonPrefixList = (output, context) => {
    return (output || []).filter((e2) => e2 != null).map((entry) => {
        return de_CommonPrefix(entry, context);
    });
};
var de__Object = (output, context) => {
    const contents = {};
    if (output[_K] != null) {
        contents[_K] = expectString(output[_K]);
    }
    if (output[_LM] != null) {
        contents[_LM] = expectNonNull(parseRfc3339DateTimeWithOffset(output[_LM]));
    }
    if (output[_ETa] != null) {
        contents[_ETa] = expectString(output[_ETa]);
    }
    if (output.ChecksumAlgorithm === "") {
        contents[_CA] = [];
    } else if (output[_CA] != null) {
        contents[_CA] = de_ChecksumAlgorithmList(getArrayIfSingleItem(output[_CA]), context);
    }
    if (output[_Si] != null) {
        contents[_Si] = strictParseLong(output[_Si]);
    }
    if (output[_SC] != null) {
        contents[_SC] = expectString(output[_SC]);
    }
    if (output[_O] != null) {
        contents[_O] = de_Owner(output[_O], context);
    }
    if (output[_RSe] != null) {
        contents[_RSe] = de_RestoreStatus(output[_RSe], context);
    }
    return contents;
};
var de_ObjectList = (output, context) => {
    return (output || []).filter((e2) => e2 != null).map((entry) => {
        return de__Object(entry, context);
    });
};
var de_Owner = (output, context) => {
    const contents = {};
    if (output[_DN] != null) {
        contents[_DN] = expectString(output[_DN]);
    }
    if (output[_ID_] != null) {
        contents[_ID_] = expectString(output[_ID_]);
    }
    return contents;
};
var de_RestoreStatus = (output, context) => {
    const contents = {};
    if (output[_IRIP] != null) {
        contents[_IRIP] = parseBoolean(output[_IRIP]);
    }
    if (output[_RED] != null) {
        contents[_RED] = expectNonNull(parseRfc3339DateTimeWithOffset(output[_RED]));
    }
    return contents;
};
var de_SessionCredentials = (output, context) => {
    const contents = {};
    if (output[_AKI] != null) {
        contents[_AKI] = expectString(output[_AKI]);
    }
    if (output[_SAK] != null) {
        contents[_SAK] = expectString(output[_SAK]);
    }
    if (output[_ST] != null) {
        contents[_ST] = expectString(output[_ST]);
    }
    if (output[_Exp] != null) {
        contents[_Exp] = expectNonNull(parseRfc3339DateTimeWithOffset(output[_Exp]));
    }
    return contents;
};
var deserializeMetadata = (output) => ({
    httpStatusCode: output.statusCode,
    requestId: output.headers["x-amzn-requestid"] ?? output.headers["x-amzn-request-id"] ?? output.headers["x-amz-request-id"],
    extendedRequestId: output.headers["x-amz-id-2"],
    cfId: output.headers["x-amz-cf-id"]
});
var _ACL = "ACL";
var _AKI = "AccessKeyId";
var _AR = "AcceptRanges";
var _AT = "AccessTier";
var _B = "Bucket";
var _BGR = "BypassGovernanceRetention";
var _BI = "BucketInfo";
var _BKE = "BucketKeyEnabled";
var _BLCu = "BucketLocationConstraint";
var _BT = "BucketType";
var _C = "Credentials";
var _CA = "ChecksumAlgorithm";
var _CBC = "CreateBucketConfiguration";
var _CC = "CacheControl";
var _CCRC = "ChecksumCRC32";
var _CCRCC = "ChecksumCRC32C";
var _CD = "ContentDisposition";
var _CE = "ContentEncoding";
var _CL = "ContentLanguage";
var _CLo = "ContentLength";
var _CM = "ChecksumMode";
var _CMD = "ContentMD5";
var _CP = "CommonPrefixes";
var _CR = "ContentRange";
var _CSHA = "ChecksumSHA1";
var _CSHAh = "ChecksumSHA256";
var _CT = "ContentType";
var _CTo = "ContinuationToken";
var _Co = "Contents";
var _D = "Delimiter";
var _DM = "DeleteMarker";
var _DN = "DisplayName";
var _DR = "DataRedundancy";
var _E = "Expires";
var _EBO = "ExpectedBucketOwner";
var _ES = "ExpiresString";
var _ET = "EncodingType";
var _ETa = "ETag";
var _Exp = "Expiration";
var _FO = "FetchOwner";
var _GFC = "GrantFullControl";
var _GR = "GrantRead";
var _GRACP = "GrantReadACP";
var _GW = "GrantWrite";
var _GWACP = "GrantWriteACP";
var _ID_ = "ID";
var _IM = "IfMatch";
var _IMS = "IfModifiedSince";
var _INM = "IfNoneMatch";
var _IRIP = "IsRestoreInProgress";
var _IT = "IsTruncated";
var _IUS = "IfUnmodifiedSince";
var _K = "Key";
var _KC = "KeyCount";
var _L = "Location";
var _LC = "LocationConstraint";
var _LI = "LocationInfo";
var _LM = "LastModified";
var _LNAS = "LocationNameAsString";
var _LT = "LocationType";
var _MFA = "MFA";
var _MK = "MaxKeys";
var _MM = "MissingMeta";
var _N = "Name";
var _NCT = "NextContinuationToken";
var _O = "Owner";
var _OLEFB = "ObjectLockEnabledForBucket";
var _OLLHS = "ObjectLockLegalHoldStatus";
var _OLM = "ObjectLockMode";
var _OLRUD = "ObjectLockRetainUntilDate";
var _OO = "ObjectOwnership";
var _OOA = "OptionalObjectAttributes";
var _P = "Prefix";
var _PC = "PartsCount";
var _PN = "PartNumber";
var _R = "Range";
var _RC = "RequestCharged";
var _RCC = "ResponseCacheControl";
var _RCD = "ResponseContentDisposition";
var _RCE = "ResponseContentEncoding";
var _RCL = "ResponseContentLanguage";
var _RCT = "ResponseContentType";
var _RE = "ResponseExpires";
var _RED = "RestoreExpiryDate";
var _RP = "RequestPayer";
var _RS = "ReplicationStatus";
var _RSe = "RestoreStatus";
var _Re = "Restore";
var _SA = "StartAfter";
var _SAK = "SecretAccessKey";
var _SC = "StorageClass";
var _SM = "SessionMode";
var _SSE = "ServerSideEncryption";
var _SSECA = "SSECustomerAlgorithm";
var _SSECK = "SSECustomerKey";
var _SSECKMD = "SSECustomerKeyMD5";
var _SSEKMSEC = "SSEKMSEncryptionContext";
var _SSEKMSKI = "SSEKMSKeyId";
var _ST = "SessionToken";
var _Si = "Size";
var _T = "Tagging";
var _TC = "TagCount";
var _Ty = "Type";
var _VI = "VersionId";
var _WRL = "WebsiteRedirectLocation";
var _ar = "accept-ranges";
var _cc = "cache-control";
var _cd = "content-disposition";
var _ce = "content-encoding";
var _cl = "content-language";
var _cl_ = "content-length";
var _cm = "content-md5";
var _cr = "content-range";
var _ct = "content-type";
var _ct_ = "continuation-token";
var _de = "delimiter";
var _e = "expires";
var _et = "encoding-type";
var _eta = "etag";
var _ex = "expiresstring";
var _fo = "fetch-owner";
var _im = "if-match";
var _ims = "if-modified-since";
var _inm = "if-none-match";
var _ius = "if-unmodified-since";
var _lm = "last-modified";
var _lo = "location";
var _lt = "list-type";
var _mk = "max-keys";
var _pN = "partNumber";
var _pr = "prefix";
var _ra = "range";
var _rcc = "response-cache-control";
var _rcd = "response-content-disposition";
var _rce = "response-content-encoding";
var _rcl = "response-content-language";
var _rct = "response-content-type";
var _re = "response-expires";
var _s = "session";
var _sa = "start-after";
var _vI = "versionId";
var _ve = '<?xml version="1.0" encoding="UTF-8"?>';
var _xaa = "x-amz-acl";
var _xabgr = "x-amz-bypass-governance-retention";
var _xabole = "x-amz-bucket-object-lock-enabled";
var _xacc = "x-amz-checksum-crc32";
var _xacc_ = "x-amz-checksum-crc32c";
var _xacm = "x-amz-checksum-mode";
var _xacs = "x-amz-checksum-sha1";
var _xacs_ = "x-amz-checksum-sha256";
var _xacsm = "x-amz-create-session-mode";
var _xadm = "x-amz-delete-marker";
var _xae = "x-amz-expiration";
var _xaebo = "x-amz-expected-bucket-owner";
var _xagfc = "x-amz-grant-full-control";
var _xagr = "x-amz-grant-read";
var _xagra = "x-amz-grant-read-acp";
var _xagw = "x-amz-grant-write";
var _xagwa = "x-amz-grant-write-acp";
var _xam = "x-amz-mfa";
var _xamm = "x-amz-missing-meta";
var _xampc = "x-amz-mp-parts-count";
var _xaollh = "x-amz-object-lock-legal-hold";
var _xaolm = "x-amz-object-lock-mode";
var _xaolrud = "x-amz-object-lock-retain-until-date";
var _xaoo = "x-amz-object-ownership";
var _xaooa = "x-amz-optional-object-attributes";
var _xar = "x-amz-restore";
var _xarc = "x-amz-request-charged";
var _xarp = "x-amz-request-payer";
var _xars = "x-amz-replication-status";
var _xasc = "x-amz-storage-class";
var _xasca = "x-amz-sdk-checksum-algorithm";
var _xasse = "x-amz-server-side-encryption";
var _xasseakki = "x-amz-server-side-encryption-aws-kms-key-id";
var _xassebke = "x-amz-server-side-encryption-bucket-key-enabled";
var _xassec = "x-amz-server-side-encryption-context";
var _xasseca = "x-amz-server-side-encryption-customer-algorithm";
var _xasseck = "x-amz-server-side-encryption-customer-key";
var _xasseckm = "x-amz-server-side-encryption-customer-key-md5";
var _xat = "x-amz-tagging";
var _xatc = "x-amz-tagging-count";
var _xavi = "x-amz-version-id";
var _xawrl = "x-amz-website-redirect-location";
var _xi = "x-id";

// node_modules/@aws-sdk/client-s3/dist-es/commands/CreateSessionCommand.js
var CreateSessionCommand = class extends Command.classBuilder().ep(__spreadProps(__spreadValues({}, commonParams), {
    DisableS3ExpressSessionAuth: {
        type: "staticContextParams",
        value: true
    },
    Bucket: {
        type: "contextParams",
        name: "Bucket"
    }
})).m(function (Command2, cs2, config, o2) {
    return [getSerdePlugin(config, this.serialize, this.deserialize), getEndpointPlugin(config, Command2.getEndpointParameterInstructions()), getThrow200ExceptionsPlugin(config)];
}).s("AmazonS3", "CreateSession", {}).n("S3Client", "CreateSessionCommand").f(CreateSessionRequestFilterSensitiveLog, CreateSessionOutputFilterSensitiveLog).ser(se_CreateSessionCommand).de(de_CreateSessionCommand).build() {
};

// node_modules/@aws-sdk/client-s3/package.json
var package_default = {
    name: "@aws-sdk/client-s3",
    description: "AWS SDK for JavaScript S3 Client for Node.js, Browser and React Native",
    version: "3.693.0",
    scripts: {
        build: "concurrently 'yarn:build:cjs' 'yarn:build:es' 'yarn:build:types'",
        "build:cjs": "node ../../scripts/compilation/inline client-s3",
        "build:es": "tsc -p tsconfig.es.json",
        "build:include:deps": "lerna run --scope $npm_package_name --include-dependencies build",
        "build:types": "tsc -p tsconfig.types.json",
        "build:types:downlevel": "downlevel-dts dist-types dist-types/ts3.4",
        clean: "rimraf ./dist-* && rimraf *.tsbuildinfo",
        "extract:docs": "api-extractor run --local",
        "generate:client": "node ../../scripts/generate-clients/single-service --solo s3",
        test: "yarn g:vitest run",
        "test:browser": "node ./test/browser-build/esbuild && vitest run -c vitest.config.browser.ts --mode development",
        "test:browser:watch": "node ./test/browser-build/esbuild && yarn g:vitest watch -c vitest.config.browser.ts",
        "test:e2e": "yarn g:vitest run -c vitest.config.e2e.ts --mode development && yarn test:browser",
        "test:e2e:watch": "yarn g:vitest watch -c vitest.config.e2e.ts",
        "test:watch": "yarn g:vitest watch"
    },
    main: "./dist-cjs/index.js",
    types: "./dist-types/index.d.ts",
    module: "./dist-es/index.js",
    sideEffects: false,
    dependencies: {
        "@aws-crypto/sha1-browser": "5.2.0",
        "@aws-crypto/sha256-browser": "5.2.0",
        "@aws-crypto/sha256-js": "5.2.0",
        "@aws-sdk/client-sso-oidc": "3.693.0",
        "@aws-sdk/client-sts": "3.693.0",
        "@aws-sdk/core": "3.693.0",
        "@aws-sdk/credential-provider-node": "3.693.0",
        "@aws-sdk/middleware-bucket-endpoint": "3.693.0",
        "@aws-sdk/middleware-expect-continue": "3.693.0",
        "@aws-sdk/middleware-flexible-checksums": "3.693.0",
        "@aws-sdk/middleware-host-header": "3.693.0",
        "@aws-sdk/middleware-location-constraint": "3.693.0",
        "@aws-sdk/middleware-logger": "3.693.0",
        "@aws-sdk/middleware-recursion-detection": "3.693.0",
        "@aws-sdk/middleware-sdk-s3": "3.693.0",
        "@aws-sdk/middleware-ssec": "3.693.0",
        "@aws-sdk/middleware-user-agent": "3.693.0",
        "@aws-sdk/region-config-resolver": "3.693.0",
        "@aws-sdk/signature-v4-multi-region": "3.693.0",
        "@aws-sdk/types": "3.692.0",
        "@aws-sdk/util-endpoints": "3.693.0",
        "@aws-sdk/util-user-agent-browser": "3.693.0",
        "@aws-sdk/util-user-agent-node": "3.693.0",
        "@aws-sdk/xml-builder": "3.693.0",
        "@smithy/config-resolver": "^3.0.11",
        "@smithy/core": "^2.5.2",
        "@smithy/eventstream-serde-browser": "^3.0.12",
        "@smithy/eventstream-serde-config-resolver": "^3.0.9",
        "@smithy/eventstream-serde-node": "^3.0.11",
        "@smithy/fetch-http-handler": "^4.1.0",
        "@smithy/hash-blob-browser": "^3.1.8",
        "@smithy/hash-node": "^3.0.9",
        "@smithy/hash-stream-node": "^3.1.8",
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
        "@smithy/util-stream": "^3.3.0",
        "@smithy/util-utf8": "^3.0.0",
        "@smithy/util-waiter": "^3.1.8",
        tslib: "^2.6.2"
    },
    devDependencies: {
        "@aws-sdk/signature-v4-crt": "3.693.0",
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
    homepage: "https://github.com/aws/aws-sdk-js-v3/tree/main/clients/client-s3",
    repository: {
        type: "git",
        url: "https://github.com/aws/aws-sdk-js-v3.git",
        directory: "clients/client-s3"
    }
};

// node_modules/@aws-crypto/sha1-browser/node_modules/@smithy/util-utf8/dist-es/fromUtf8.browser.js
var fromUtf82 = (input) => new TextEncoder().encode(input);

// node_modules/@aws-crypto/sha1-browser/build/module/isEmptyData.js
function isEmptyData2(data) {
    if (typeof data === "string") {
        return data.length === 0;
    }
    return data.byteLength === 0;
}

// node_modules/@aws-crypto/sha1-browser/build/module/constants.js
var SHA_1_HASH = {
    name: "SHA-1"
};
var SHA_1_HMAC_ALGO = {
    name: "HMAC",
    hash: SHA_1_HASH
};
var EMPTY_DATA_SHA_1 = new Uint8Array([218, 57, 163, 238, 94, 107, 75, 13, 50, 85, 191, 239, 149, 96, 24, 144, 175, 216, 7, 9]);

// node_modules/@aws-crypto/sha1-browser/build/module/webCryptoSha1.js
var Sha1 = (
    /** @class */
    function () {
        function Sha13(secret) {
            this.toHash = new Uint8Array(0);
            if (secret !== void 0) {
                this.key = new Promise(function (resolve, reject) {
                    locateWindow().crypto.subtle.importKey("raw", convertToBuffer2(secret), SHA_1_HMAC_ALGO, false, ["sign"]).then(resolve, reject);
                });
                this.key.catch(function () {
                });
            }
        }

        Sha13.prototype.update = function (data) {
            if (isEmptyData2(data)) {
                return;
            }
            var update = convertToBuffer2(data);
            var typedArray = new Uint8Array(this.toHash.byteLength + update.byteLength);
            typedArray.set(this.toHash, 0);
            typedArray.set(update, this.toHash.byteLength);
            this.toHash = typedArray;
        };
        Sha13.prototype.digest = function () {
            var _this = this;
            if (this.key) {
                return this.key.then(function (key) {
                    return locateWindow().crypto.subtle.sign(SHA_1_HMAC_ALGO, key, _this.toHash).then(function (data) {
                        return new Uint8Array(data);
                    });
                });
            }
            if (isEmptyData2(this.toHash)) {
                return Promise.resolve(EMPTY_DATA_SHA_1);
            }
            return Promise.resolve().then(function () {
                return locateWindow().crypto.subtle.digest(SHA_1_HASH, _this.toHash);
            }).then(function (data) {
                return Promise.resolve(new Uint8Array(data));
            });
        };
        Sha13.prototype.reset = function () {
            this.toHash = new Uint8Array(0);
        };
        return Sha13;
    }()
);

function convertToBuffer2(data) {
    if (typeof data === "string") {
        return fromUtf82(data);
    }
    if (ArrayBuffer.isView(data)) {
        return new Uint8Array(data.buffer, data.byteOffset, data.byteLength / Uint8Array.BYTES_PER_ELEMENT);
    }
    return new Uint8Array(data);
}

// node_modules/@aws-crypto/sha1-browser/build/module/crossPlatformSha1.js
var Sha12 = (
    /** @class */
    function () {
        function Sha13(secret) {
            if (supportsWebCrypto(locateWindow())) {
                this.hash = new Sha1(secret);
            } else {
                throw new Error("SHA1 not supported");
            }
        }

        Sha13.prototype.update = function (data, encoding) {
            this.hash.update(convertToBuffer(data));
        };
        Sha13.prototype.digest = function () {
            return this.hash.digest();
        };
        Sha13.prototype.reset = function () {
            this.hash.reset();
        };
        return Sha13;
    }()
);

// node_modules/@smithy/chunked-blob-reader/dist-es/index.js
function blobReader(_0, _1) {
    return __async(this, arguments, function* (blob, onChunk, chunkSize = 1024 * 1024) {
        const size = blob.size;
        let totalBytesRead = 0;
        while (totalBytesRead < size) {
            const slice = blob.slice(totalBytesRead, Math.min(size, totalBytesRead + chunkSize));
            onChunk(new Uint8Array(yield slice.arrayBuffer()));
            totalBytesRead += slice.size;
        }
    });
}

// node_modules/@smithy/hash-blob-browser/dist-es/index.js
var blobHasher = function blobHasher2(hashCtor, blob) {
    return __async(this, null, function* () {
        const hash = new hashCtor();
        yield blobReader(blob, (chunk) => {
            hash.update(chunk);
        });
        return hash.digest();
    });
};

// node_modules/@aws-sdk/client-s3/dist-es/runtimeConfig.shared.js
var getRuntimeConfig = (config) => {
    return {
        apiVersion: "2006-03-01",
        base64Decoder: config?.base64Decoder ?? fromBase64,
        base64Encoder: config?.base64Encoder ?? toBase64,
        disableHostPrefix: config?.disableHostPrefix ?? false,
        endpointProvider: config?.endpointProvider ?? defaultEndpointResolver,
        extensions: config?.extensions ?? [],
        getAwsChunkedEncodingStream: config?.getAwsChunkedEncodingStream ?? getAwsChunkedEncodingStream,
        httpAuthSchemeProvider: config?.httpAuthSchemeProvider ?? defaultS3HttpAuthSchemeProvider,
        httpAuthSchemes: config?.httpAuthSchemes ?? [{
            schemeId: "aws.auth#sigv4",
            identityProvider: (ipc) => ipc.getIdentityProvider("aws.auth#sigv4"),
            signer: new AwsSdkSigV4Signer()
        }, {
            schemeId: "aws.auth#sigv4a",
            identityProvider: (ipc) => ipc.getIdentityProvider("aws.auth#sigv4a"),
            signer: new AwsSdkSigV4ASigner()
        }],
        logger: config?.logger ?? new NoOpLogger(),
        sdkStreamMixin: config?.sdkStreamMixin ?? sdkStreamMixin,
        serviceId: config?.serviceId ?? "S3",
        signerConstructor: config?.signerConstructor ?? SignatureV4MultiRegion,
        signingEscapePath: config?.signingEscapePath ?? false,
        urlParser: config?.urlParser ?? parseUrl,
        useArnRegion: config?.useArnRegion ?? false,
        utf8Decoder: config?.utf8Decoder ?? fromUtf8,
        utf8Encoder: config?.utf8Encoder ?? toUtf8
    };
};

// node_modules/@aws-sdk/client-s3/dist-es/runtimeConfig.browser.js
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
        md5: config?.md5 ?? Md5,
        region: config?.region ?? invalidProvider("Region is missing"),
        requestHandler: FetchHttpHandler.create(config?.requestHandler ?? defaultConfigProvider),
        retryMode: config?.retryMode ?? (() => __async(void 0, null, function* () {
            return (yield defaultConfigProvider()).retryMode || DEFAULT_RETRY_MODE;
        })),
        sha1: config?.sha1 ?? Sha12,
        sha256: config?.sha256 ?? Sha256,
        streamCollector: config?.streamCollector ?? streamCollector,
        streamHasher: config?.streamHasher ?? blobHasher,
        useDualstackEndpoint: config?.useDualstackEndpoint ?? (() => Promise.resolve(DEFAULT_USE_DUALSTACK_ENDPOINT)),
        useFipsEndpoint: config?.useFipsEndpoint ?? (() => Promise.resolve(DEFAULT_USE_FIPS_ENDPOINT))
    });
};

// node_modules/@aws-sdk/client-s3/dist-es/auth/httpAuthExtensionConfiguration.js
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

// node_modules/@aws-sdk/client-s3/dist-es/runtimeExtensions.js
var asPartial = (t2) => t2;
var resolveRuntimeExtensions = (runtimeConfig, extensions) => {
    const extensionConfiguration = __spreadValues(__spreadValues(__spreadValues(__spreadValues({}, asPartial(getAwsRegionExtensionConfiguration(runtimeConfig))), asPartial(getDefaultExtensionConfiguration(runtimeConfig))), asPartial(getHttpHandlerExtensionConfiguration(runtimeConfig))), asPartial(getHttpAuthExtensionConfiguration(runtimeConfig)));
    extensions.forEach((extension) => extension.configure(extensionConfiguration));
    return __spreadValues(__spreadValues(__spreadValues(__spreadValues(__spreadValues({}, runtimeConfig), resolveAwsRegionExtensionConfiguration(extensionConfiguration)), resolveDefaultRuntimeConfig(extensionConfiguration)), resolveHttpHandlerRuntimeConfig(extensionConfiguration)), resolveHttpAuthRuntimeConfig(extensionConfiguration));
};

// node_modules/@aws-sdk/client-s3/dist-es/S3Client.js
var S3Client = class extends Client {
    constructor(...[configuration]) {
        const _config_0 = getRuntimeConfig2(configuration || {});
        const _config_1 = resolveClientEndpointParameters(_config_0);
        const _config_2 = resolveUserAgentConfig(_config_1);
        const _config_3 = resolveFlexibleChecksumsConfig(_config_2);
        const _config_4 = resolveRetryConfig(_config_3);
        const _config_5 = resolveRegionConfig(_config_4);
        const _config_6 = resolveHostHeaderConfig(_config_5);
        const _config_7 = resolveEndpointConfig(_config_6);
        const _config_8 = resolveEventStreamSerdeConfig(_config_7);
        const _config_9 = resolveHttpAuthSchemeConfig(_config_8);
        const _config_10 = resolveS3Config(_config_9, {
            session: [() => this, CreateSessionCommand]
        });
        const _config_11 = resolveRuntimeExtensions(_config_10, configuration?.extensions || []);
        super(_config_11);
        this.config = _config_11;
        this.middlewareStack.use(getUserAgentPlugin(this.config));
        this.middlewareStack.use(getRetryPlugin(this.config));
        this.middlewareStack.use(getContentLengthPlugin(this.config));
        this.middlewareStack.use(getHostHeaderPlugin(this.config));
        this.middlewareStack.use(getLoggerPlugin(this.config));
        this.middlewareStack.use(getRecursionDetectionPlugin(this.config));
        this.middlewareStack.use(getHttpAuthSchemeEndpointRuleSetPlugin(this.config, {
            httpAuthSchemeParametersProvider: defaultS3HttpAuthSchemeParametersProvider,
            identityProviderConfigProvider: (config) => __async(this, null, function* () {
                return new DefaultIdentityProviderConfig({
                    "aws.auth#sigv4": config.credentials,
                    "aws.auth#sigv4a": config.credentials
                });
            })
        }));
        this.middlewareStack.use(getHttpSigningPlugin(this.config));
        this.middlewareStack.use(getValidateBucketNamePlugin(this.config));
        this.middlewareStack.use(getAddExpectContinuePlugin(this.config));
        this.middlewareStack.use(getRegionRedirectMiddlewarePlugin(this.config));
        this.middlewareStack.use(getS3ExpressPlugin(this.config));
        this.middlewareStack.use(getS3ExpressHttpSigningPlugin(this.config));
    }

    destroy() {
        super.destroy();
    }
};

// node_modules/@aws-sdk/middleware-ssec/dist-es/index.js
function ssecMiddleware(options) {
    return (next) => (args) => __async(this, null, function* () {
        const input = __spreadValues({}, args.input);
        const properties = [{
            target: "SSECustomerKey",
            hash: "SSECustomerKeyMD5"
        }, {
            target: "CopySourceSSECustomerKey",
            hash: "CopySourceSSECustomerKeyMD5"
        }];
        for (const prop of properties) {
            const value = input[prop.target];
            if (value) {
                let valueForHash;
                if (typeof value === "string") {
                    if (isValidBase64EncodedSSECustomerKey(value, options)) {
                        valueForHash = options.base64Decoder(value);
                    } else {
                        valueForHash = options.utf8Decoder(value);
                        input[prop.target] = options.base64Encoder(valueForHash);
                    }
                } else {
                    valueForHash = ArrayBuffer.isView(value) ? new Uint8Array(value.buffer, value.byteOffset, value.byteLength) : new Uint8Array(value);
                    input[prop.target] = options.base64Encoder(valueForHash);
                }
                const hash = new options.md5();
                hash.update(valueForHash);
                input[prop.hash] = options.base64Encoder(yield hash.digest());
            }
        }
        return next(__spreadProps(__spreadValues({}, args), {
            input
        }));
    });
}

var ssecMiddlewareOptions = {
    name: "ssecMiddleware",
    step: "initialize",
    tags: ["SSE"],
    override: true
};
var getSsecPlugin = (config) => ({
    applyToStack: (clientStack) => {
        clientStack.add(ssecMiddleware(config), ssecMiddlewareOptions);
    }
});

function isValidBase64EncodedSSECustomerKey(str, options) {
    const base64Regex = /^(?:[A-Za-z0-9+/]{4})*([A-Za-z0-9+/]{2}==|[A-Za-z0-9+/]{3}=)?$/;
    if (!base64Regex.test(str)) return false;
    try {
        const decodedBytes = options.base64Decoder(str);
        return decodedBytes.length === 32;
    } catch {
        return false;
    }
}

// node_modules/@aws-sdk/middleware-location-constraint/dist-es/index.js
function locationConstraintMiddleware(options) {
    return (next) => (args) => __async(this, null, function* () {
        const {
            CreateBucketConfiguration
        } = args.input;
        const region = yield options.region();
        if (!CreateBucketConfiguration?.LocationConstraint && !CreateBucketConfiguration?.Location) {
            args = __spreadProps(__spreadValues({}, args), {
                input: __spreadProps(__spreadValues({}, args.input), {
                    CreateBucketConfiguration: region === "us-east-1" ? void 0 : {
                        LocationConstraint: region
                    }
                })
            });
        }
        return next(args);
    });
}

var locationConstraintMiddlewareOptions = {
    step: "initialize",
    tags: ["LOCATION_CONSTRAINT", "CREATE_BUCKET_CONFIGURATION"],
    name: "locationConstraintMiddleware",
    override: true
};
var getLocationConstraintPlugin = (config) => ({
    applyToStack: (clientStack) => {
        clientStack.add(locationConstraintMiddleware(config), locationConstraintMiddlewareOptions);
    }
});

// node_modules/@aws-sdk/client-s3/dist-es/commands/CreateBucketCommand.js
var CreateBucketCommand = class extends Command.classBuilder().ep(__spreadProps(__spreadValues({}, commonParams), {
    UseS3ExpressControlEndpoint: {
        type: "staticContextParams",
        value: true
    },
    DisableAccessPoints: {
        type: "staticContextParams",
        value: true
    },
    Bucket: {
        type: "contextParams",
        name: "Bucket"
    }
})).m(function (Command2, cs2, config, o2) {
    return [getSerdePlugin(config, this.serialize, this.deserialize), getEndpointPlugin(config, Command2.getEndpointParameterInstructions()), getThrow200ExceptionsPlugin(config), getLocationConstraintPlugin(config)];
}).s("AmazonS3", "CreateBucket", {}).n("S3Client", "CreateBucketCommand").f(void 0, void 0).ser(se_CreateBucketCommand).de(de_CreateBucketCommand).build() {
};

// node_modules/@aws-sdk/client-s3/dist-es/commands/DeleteBucketCommand.js
var DeleteBucketCommand = class extends Command.classBuilder().ep(__spreadProps(__spreadValues({}, commonParams), {
    UseS3ExpressControlEndpoint: {
        type: "staticContextParams",
        value: true
    },
    Bucket: {
        type: "contextParams",
        name: "Bucket"
    }
})).m(function (Command2, cs2, config, o2) {
    return [getSerdePlugin(config, this.serialize, this.deserialize), getEndpointPlugin(config, Command2.getEndpointParameterInstructions())];
}).s("AmazonS3", "DeleteBucket", {}).n("S3Client", "DeleteBucketCommand").f(void 0, void 0).ser(se_DeleteBucketCommand).de(de_DeleteBucketCommand).build() {
};

// node_modules/@aws-sdk/client-s3/dist-es/commands/DeleteObjectCommand.js
var DeleteObjectCommand = class extends Command.classBuilder().ep(__spreadProps(__spreadValues({}, commonParams), {
    Bucket: {
        type: "contextParams",
        name: "Bucket"
    },
    Key: {
        type: "contextParams",
        name: "Key"
    }
})).m(function (Command2, cs2, config, o2) {
    return [getSerdePlugin(config, this.serialize, this.deserialize), getEndpointPlugin(config, Command2.getEndpointParameterInstructions()), getThrow200ExceptionsPlugin(config)];
}).s("AmazonS3", "DeleteObject", {}).n("S3Client", "DeleteObjectCommand").f(void 0, void 0).ser(se_DeleteObjectCommand).de(de_DeleteObjectCommand).build() {
};

// node_modules/@aws-sdk/client-s3/dist-es/commands/GetObjectCommand.js
var GetObjectCommand = class extends Command.classBuilder().ep(__spreadProps(__spreadValues({}, commonParams), {
    Bucket: {
        type: "contextParams",
        name: "Bucket"
    },
    Key: {
        type: "contextParams",
        name: "Key"
    }
})).m(function (Command2, cs2, config, o2) {
    return [getSerdePlugin(config, this.serialize, this.deserialize), getEndpointPlugin(config, Command2.getEndpointParameterInstructions()), getFlexibleChecksumsPlugin(config, {
        input: this.input,
        requestChecksumRequired: false,
        requestValidationModeMember: "ChecksumMode",
        responseAlgorithms: ["CRC32", "CRC32C", "SHA256", "SHA1"]
    }), getSsecPlugin(config), getS3ExpiresMiddlewarePlugin(config)];
}).s("AmazonS3", "GetObject", {}).n("S3Client", "GetObjectCommand").f(GetObjectRequestFilterSensitiveLog, GetObjectOutputFilterSensitiveLog).ser(se_GetObjectCommand).de(de_GetObjectCommand).build() {
};

// node_modules/@aws-sdk/client-s3/dist-es/commands/ListObjectsV2Command.js
var ListObjectsV2Command = class extends Command.classBuilder().ep(__spreadProps(__spreadValues({}, commonParams), {
    Bucket: {
        type: "contextParams",
        name: "Bucket"
    },
    Prefix: {
        type: "contextParams",
        name: "Prefix"
    }
})).m(function (Command2, cs2, config, o2) {
    return [getSerdePlugin(config, this.serialize, this.deserialize), getEndpointPlugin(config, Command2.getEndpointParameterInstructions()), getThrow200ExceptionsPlugin(config)];
}).s("AmazonS3", "ListObjectsV2", {}).n("S3Client", "ListObjectsV2Command").f(void 0, void 0).ser(se_ListObjectsV2Command).de(de_ListObjectsV2Command).build() {
};

// node_modules/@aws-sdk/client-s3/dist-es/commands/PutObjectCommand.js
var PutObjectCommand = class extends Command.classBuilder().ep(__spreadProps(__spreadValues({}, commonParams), {
    Bucket: {
        type: "contextParams",
        name: "Bucket"
    },
    Key: {
        type: "contextParams",
        name: "Key"
    }
})).m(function (Command2, cs2, config, o2) {
    return [getSerdePlugin(config, this.serialize, this.deserialize), getEndpointPlugin(config, Command2.getEndpointParameterInstructions()), getFlexibleChecksumsPlugin(config, {
        input: this.input,
        requestAlgorithmMember: "ChecksumAlgorithm",
        requestChecksumRequired: false
    }), getCheckContentLengthHeaderPlugin(config), getThrow200ExceptionsPlugin(config), getSsecPlugin(config)];
}).s("AmazonS3", "PutObject", {}).n("S3Client", "PutObjectCommand").f(PutObjectRequestFilterSensitiveLog, PutObjectOutputFilterSensitiveLog).ser(se_PutObjectCommand).de(de_PutObjectCommand).build() {
};

// src/app/modules/s3/service/s3-service.component.ts
var S3Service = class _S3Service {
    constructor(http) {
        this.http = http;
        this.client = new S3Client({
            region: environment.awsmockRegion,
            endpoint: environment.gatewayEndpoint,
            forcePathStyle: true,
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

    createBucket(bucketName) {
        const input = {
            Bucket: bucketName
        };
        return this.client.send(new CreateBucketCommand(input));
    }

    listObjects(bucketName, pageSize, pageIndex) {
        const command = new ListObjectsV2Command({
            Bucket: bucketName,
            MaxKeys: pageSize * pageIndex
        });
        return this.client.send(command);
    }

    putObjects(bucketName, key, content) {
        return __async(this, null, function* () {
            const command = {
                Bucket: bucketName,
                Key: key,
                Body: content
            };
            return this.client.send(new PutObjectCommand(command));
        });
    }

    getObject(bucketName, key) {
        return __async(this, null, function* () {
            const command = {
                Bucket: bucketName,
                Key: key
            };
            return this.client.send(new GetObjectCommand(command));
        });
    }

    deleteObject(bucketName, key) {
        const input = {
            Bucket: bucketName,
            Key: key
        };
        return this.client.send(new DeleteObjectCommand(input));
    }

    deleteBucket(bucketName) {
        const input = {
            Bucket: bucketName
        };
        return this.client.send(new DeleteBucketCommand(input));
    }

    cleanup() {
        this.client.destroy();
    }

    /**
     * @brief List all bucket counters
     *
     * @par
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     *
     * @param prefix bucket name prefix
     * @param pageSize page size
     * @param pageIndex page index
     * @param sortColumns sorting columns
     */
    listBucketCounters(prefix, pageSize, pageIndex, sortColumns) {
        let headers = this.headers.set("x-awsmock-target", "s3").set("x-awsmock-action", "ListBucketCounters");
        const body = {
            region: environment.awsmockRegion,
            prefix,
            pageSize,
            pageIndex,
            sortColumns
        };
        return this.http.post(this.url, body, {headers});
    }

    /**
     * @brief List all object counters
     *
     * @par
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     *
     * @param bucket bucket name
     * @param prefix object name prefix
     * @param pageSize page size
     * @param pageIndex page index
     * @param sortColumns sorting columns
     */
    listObjectsCounters(bucket, prefix, pageSize, pageIndex, sortColumns) {
        let headers = this.headers.set("x-awsmock-target", "s3").set("x-awsmock-action", "ListObjectCounters");
        const body = {
            region: environment.awsmockRegion,
            bucket,
            prefix,
            pageSize,
            pageIndex,
            sortColumns
        };
        return this.http.post(this.url, body, {headers});
    }

    /**
     * @brief Get a bucket details
     *
     * @par
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     *
     * @param bucketName bucket name
     */
    getBucket(bucketName) {
        let headers = this.headers.set("x-awsmock-target", "s3").set("x-awsmock-action", "GetBucket");
        const body = {
            region: environment.awsmockRegion,
            bucketName
        };
        return this.http.post(this.url, body, {headers});
    }

    /**
     * @brief Saves a modified bucket.
     *
     * @par
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     *
     * @param bucket bucket object
     */
    saveBucket(bucket) {
        let headers = this.headers.set("x-awsmock-target", "s3").set("x-awsmock-action", "SaveBucket");
        return this.http.post(this.url, bucket, {headers});
    }

    /**
     * @brief Deletes a S3 bucket. This will delete all objects of that bucket.
     *
     * @par
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     *
     * @param bucketName bucket name
     */
    purgeBucket(bucketName) {
        let headers = this.headers.set("x-awsmock-target", "s3").set("x-awsmock-action", "PurgeBucket");
        const body = {
            region: environment.awsmockRegion,
            bucketName
        };
        return this.http.post(this.url, body, {headers});
    }

    /**
     * @brief Deletes a S3 bucket. This will delete all objects of that bucket.
     *
     * @par
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     *
     * @param bucketName bucket name
     */
    deleteObjects(bucketName) {
        let headers = this.headers.set("x-awsmock-target", "s3").set("x-awsmock-action", "DeleteObjects");
        const body = {
            region: environment.awsmockRegion,
            bucketName
        };
        return this.http.post(this.url, body, {headers});
    }

    static {
        this.\u0275fac = function S3Service_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _S3Service)(\u0275\u0275inject(HttpClient));
        };
    }
    static {
        this.\u0275prov = /* @__PURE__ */ \u0275\u0275defineInjectable({token: _S3Service, factory: _S3Service.\u0275fac, providedIn: "root"});
    }
};

// src/app/modules/s3/bucket-list/state/s3-bucket-list.effects.ts
var S3BucketListEffects = class _S3BucketListEffects {
    constructor(actions$, awsmockHttpService, s3Service) {
        this.actions$ = actions$;
        this.awsmockHttpService = awsmockHttpService;
        this.s3Service = s3Service;
        this.sortColumns = [];
        this.loadBucketCounters$ = createEffect(() => this.actions$.pipe(ofType(s3BucketListActions.loadBuckets), mergeMap((action) => this.s3Service.listBucketCounters(action.prefix, action.pageSize, action.pageIndex, action.sortColumns).pipe(map((buckets) => s3BucketListActions.loadBucketsSuccess({buckets})), catchError((error) => of(s3BucketListActions.loadBucketsFailure({error: error.message})))))));
        this.addQueue$ = createEffect(() => this.actions$.pipe(ofType(s3BucketListActions.addBucket), mergeMap((action) => this.s3Service.createBucket(action.bucketName).then(() => s3BucketListActions.addBucketSuccess()))));
        this.deleteBucket$ = createEffect(() => this.actions$.pipe(ofType(s3BucketListActions.deleteBucket), mergeMap((action) => this.s3Service.deleteBucket(action.bucketName).then(() => s3BucketListActions.deleteBucketSuccess()))));
        this.purgeBucket$ = createEffect(() => this.actions$.pipe(ofType(s3BucketListActions.purgeBucket), mergeMap((action) => this.s3Service.purgeBucket(action.bucketName).pipe(map((buckets) => s3BucketListActions.loadBucketsSuccess({buckets})), catchError((error) => of(s3BucketListActions.loadBucketsFailure({error: error.message})))))));
    }

    static {
        this.\u0275fac = function S3BucketListEffects_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _S3BucketListEffects)(\u0275\u0275inject(Actions), \u0275\u0275inject(AwsMockHttpService), \u0275\u0275inject(S3Service));
        };
    }
    static {
        this.\u0275prov = /* @__PURE__ */ \u0275\u0275defineInjectable({token: _S3BucketListEffects, factory: _S3BucketListEffects.\u0275fac});
    }
};

// src/app/modules/s3/bucket-add/bucket-add.component.ts
var BucketAddComponentDialog = class _BucketAddComponentDialog {
    constructor(dialogRef) {
        this.dialogRef = dialogRef;
        this.bucketName = "";
    }

    ngOnInit() {
    }

    save() {
        this.dialogRef.close(this.bucketName);
    }

    close() {
        this.dialogRef.close(false);
    }

    static {
        this.\u0275fac = function BucketAddComponentDialog_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _BucketAddComponentDialog)(\u0275\u0275directiveInject(MatDialogRef));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _BucketAddComponentDialog,
            selectors: [["bucket-add-dialog"]],
            standalone: true,
            features: [\u0275\u0275StandaloneFeature],
            decls: 12,
            vars: 1,
            consts: [["mat-dialog-title", ""], [1, "mat-typography", 2, "width", "500px"], [2, "width", "100%"], ["matInput", "", "value", "", 3, "ngModelChange", "ngModel"], ["align", "end"], ["mat-button", "", "mat-dialog-close", ""], ["cdkFocusInitial", "", "mat-button", "", 3, "click"]],
            template: function BucketAddComponentDialog_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "h2", 0);
                    \u0275\u0275text(1, "Add S3 Bucket");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(2, "mat-dialog-content", 1)(3, "mat-form-field", 2)(4, "mat-label");
                    \u0275\u0275text(5, "Bucket Name");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(6, "input", 3);
                    \u0275\u0275twoWayListener("ngModelChange", function BucketAddComponentDialog_Template_input_ngModelChange_6_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.bucketName, $event) || (ctx.bucketName = $event);
                        return $event;
                    });
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(7, "mat-dialog-actions", 4)(8, "button", 5);
                    \u0275\u0275text(9, "Cancel");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(10, "button", 6);
                    \u0275\u0275listener("click", function BucketAddComponentDialog_Template_button_click_10_listener() {
                        return ctx.save();
                    });
                    \u0275\u0275text(11, "Add");
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    \u0275\u0275advance(6);
                    \u0275\u0275twoWayProperty("ngModel", ctx.bucketName);
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
            ]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(BucketAddComponentDialog, {
        className: "BucketAddComponentDialog",
        filePath: "src/app/modules/s3/bucket-add/bucket-add.component.ts",
        lineNumber: 37
    });
})();

// src/app/modules/s3/bucket-list/state/s3-bucket-list.selectors.ts
var selectBucketListFeature = createFeatureSelector(s3BucketListFeatureKey);
var selectIsLoading = createSelector(selectBucketListFeature, (state) => state.loading);
var selectTotal = createSelector(selectBucketListFeature, (state) => state.total);
var selectBucketName = createSelector(selectBucketListFeature, (state) => state?.bucketName);
var selectPrefix = createSelector(selectBucketListFeature, (state) => state?.prefix);
var selectPageSize = createSelector(selectBucketListFeature, (state) => state?.pageSize);
var selectPageIndex = createSelector(selectBucketListFeature, (state) => state?.pageIndex);
var selectSortColumns = createSelector(selectBucketListFeature, (state) => state?.sortColumns);
var selectBucketCounters = createSelector(selectBucketListFeature, (state) => state?.s3BucketCounters);

// src/app/modules/s3/bucket-list/bucket-list.component.ts
var _c0 = () => [];

function S3BucketListComponent_button_21_Template(rf, ctx) {
    if (rf & 1) {
        const _r1 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "button", 29);
        \u0275\u0275listener("click", function S3BucketListComponent_button_21_Template_button_click_0_listener() {
            \u0275\u0275restoreView(_r1);
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.setPrefix());
        });
        \u0275\u0275elementStart(1, "mat-icon", 30);
        \u0275\u0275text(2, "search");
        \u0275\u0275elementEnd()();
    }
}

function S3BucketListComponent_button_22_Template(rf, ctx) {
    if (rf & 1) {
        const _r3 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "button", 29);
        \u0275\u0275listener("click", function S3BucketListComponent_button_22_Template_button_click_0_listener() {
            \u0275\u0275restoreView(_r3);
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.unsetPrefix());
        });
        \u0275\u0275elementStart(1, "mat-icon", 30);
        \u0275\u0275text(2, "close");
        \u0275\u0275elementEnd()();
    }
}

function S3BucketListComponent_th_27_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 31);
        \u0275\u0275text(1, "Name");
        \u0275\u0275elementEnd();
    }
}

function S3BucketListComponent_td_28_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 32)(1, "mat-nav-list")(2, "a", 33);
        \u0275\u0275text(3);
        \u0275\u0275elementEnd()()();
    }
    if (rf & 2) {
        const element_r4 = ctx.$implicit;
        \u0275\u0275advance(2);
        \u0275\u0275propertyInterpolate1("routerLink", "./objects/", element_r4.bucketName, "");
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r4.bucketName, "");
    }
}

function S3BucketListComponent_th_30_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 34);
        \u0275\u0275text(1, "Objects");
        \u0275\u0275elementEnd();
    }
}

function S3BucketListComponent_td_31_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 32);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r5 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r5.keys, "");
    }
}

function S3BucketListComponent_th_33_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 35);
        \u0275\u0275text(1, "Size");
        \u0275\u0275elementEnd();
    }
}

function S3BucketListComponent_td_34_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 32);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r6 = ctx.$implicit;
        const ctx_r1 = \u0275\u0275nextContext();
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", ctx_r1.byteConversion(element_r6.size), "");
    }
}

function S3BucketListComponent_th_36_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 36);
        \u0275\u0275text(1, "Created");
        \u0275\u0275elementEnd();
    }
}

function S3BucketListComponent_td_37_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 32);
        \u0275\u0275text(1);
        \u0275\u0275pipe(2, "date");
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r7 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", \u0275\u0275pipeBind2(2, 1, element_r7.created, "dd-MM-yyyy hh:mm:ss"), "");
    }
}

function S3BucketListComponent_th_39_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 37);
        \u0275\u0275text(1, "Modified");
        \u0275\u0275elementEnd();
    }
}

function S3BucketListComponent_td_40_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 32);
        \u0275\u0275text(1);
        \u0275\u0275pipe(2, "date");
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r8 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", \u0275\u0275pipeBind2(2, 1, element_r8.modified, "dd-MM-yyyy hh:mm:ss"), "");
    }
}

function S3BucketListComponent_th_42_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 38);
        \u0275\u0275text(1, "Actions");
        \u0275\u0275elementEnd();
    }
}

function S3BucketListComponent_td_43_Template(rf, ctx) {
    if (rf & 1) {
        const _r9 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "td", 32)(1, "button", 39)(2, "mat-icon");
        \u0275\u0275text(3, "edit");
        \u0275\u0275elementEnd()();
        \u0275\u0275elementStart(4, "button", 40);
        \u0275\u0275listener("click", function S3BucketListComponent_td_43_Template_button_click_4_listener() {
            const row_r10 = \u0275\u0275restoreView(_r9).$implicit;
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.purgeBucket(row_r10.bucketName));
        });
        \u0275\u0275elementStart(5, "mat-icon");
        \u0275\u0275text(6, "folder_delete");
        \u0275\u0275elementEnd()();
        \u0275\u0275elementStart(7, "button", 41);
        \u0275\u0275listener("click", function S3BucketListComponent_td_43_Template_button_click_7_listener() {
            const row_r10 = \u0275\u0275restoreView(_r9).$implicit;
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.deleteBucket(row_r10.bucketName));
        });
        \u0275\u0275elementStart(8, "mat-icon");
        \u0275\u0275text(9, "delete");
        \u0275\u0275elementEnd()()();
    }
    if (rf & 2) {
        const row_r10 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275propertyInterpolate1("routerLink", "./details/", row_r10.bucketName, "");
    }
}

function S3BucketListComponent_tr_44_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 42);
    }
}

function S3BucketListComponent_tr_45_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 43);
    }
}

function S3BucketListComponent_tr_46_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "tr", 44)(1, "td", 45);
        \u0275\u0275text(2, " No data matching the filter. ");
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const ctx_r1 = \u0275\u0275nextContext();
        \u0275\u0275advance();
        \u0275\u0275attribute("colspan", ctx_r1.columns.length);
    }
}

var S3BucketListComponent = class _S3BucketListComponent {
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
        this.s3BucketCountersResponse$ = this.store.select(selectBucketCounters);
        this.columns = ["name", "keys", "size", "created", "modified", "actions"];
        this.dataSource = new MatTableDataSource();
        this.defaultSort = {active: "keys", direction: "desc"};
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
        this.actionsSubj$.pipe(filter((action) => action.type === s3BucketListActions.addBucketSuccess.type || action.type === s3BucketListActions.purgeBucketSuccess.type || action.type === s3BucketListActions.deleteBucketSuccess.type)).subscribe(() => {
            this.lastUpdate = /* @__PURE__ */ new Date();
            this.loadBuckets();
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
        this.store.pipe(select(selectBucketCounters)).subscribe((buckets) => {
            this.initializeData(buckets.bucketCounters);
            this.total = buckets.total;
        });
        this.tableSubscription.add(this.store.pipe(select(selectIsLoading)).subscribe((loading) => {
            if (loading) {
                this.dataSource = new MatTableDataSource(this.noData);
            }
            this.loading = loading;
        }));
        this.updateSubscription = interval(6e4).subscribe(() => this.loadBuckets());
    }

    ngAfterViewInit() {
        this.loadBuckets();
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
                this.tableSubscription.add(merge(filter$, sort$, this.paginator.page).pipe(tap(() => this.loadBuckets())).subscribe());
            }
        }
    }

    ngOnDestroy() {
        this.updateSubscription?.unsubscribe();
    }

    back() {
        this.location.back();
    }

    refresh() {
        this.loadBuckets();
    }

    setPrefix() {
        this.prefixSet = true;
        this.state.value["s3-bucket-list"].prefix = this.prefixValue;
        this.loadBuckets();
    }

    unsetPrefix() {
        this.prefixValue = "";
        this.prefixSet = false;
        this.state.value["s3-bucket-list"].prefix = "";
        this.loadBuckets();
    }

    handlePageEvent(e2) {
        this.state.value["s3-bucket-list"].pageSize = e2.pageSize;
        this.state.value["s3-bucket-list"].pageIndex = e2.pageIndex;
        this.store.dispatch(s3BucketListActions.loadBuckets({
            prefix: this.state.value["s3-bucket-list"].prefix,
            pageSize: this.state.value["s3-bucket-list"].pageSize,
            pageIndex: this.state.value["s3-bucket-list"].pageIndex,
            sortColumns: this.state.value["s3-bucket-list"].sortColumns
        }));
    }

    sortChange(sortState) {
        this.state.value["s3-bucket-list"].sortColumns = [];
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
        this.state.value["s3-bucket-list"].sortColumns = [{column, sortDirection: direction}];
        this.loadBuckets();
    }

    loadBuckets() {
        this.store.dispatch(s3BucketListActions.loadBuckets({
            prefix: this.state.value["s3-bucket-list"].prefix,
            pageSize: this.state.value["s3-bucket-list"].pageSize,
            pageIndex: this.state.value["s3-bucket-list"].pageIndex,
            sortColumns: this.state.value["s3-bucket-list"].sortColumns
        }));
    }

    addBucket() {
        const dialogConfig = new MatDialogConfig();
        dialogConfig.disableClose = true;
        dialogConfig.autoFocus = true;
        this.dialog.open(BucketAddComponentDialog, dialogConfig).afterClosed().subscribe((result) => {
            if (result) {
                this.store.dispatch(s3BucketListActions.addBucket({bucketName: result}));
            }
        });
    }

    purgeBucket(bucketName) {
        this.store.dispatch(s3BucketListActions.purgeBucket({bucketName}));
    }

    deleteBucket(bucketName) {
        this.store.dispatch(s3BucketListActions.deleteBucket({bucketName}));
    }

    initializeData(buckets) {
        this.dataSource = new MatTableDataSource(buckets.length ? buckets : this.noData);
    }

    static {
        this.\u0275fac = function S3BucketListComponent_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _S3BucketListComponent)(\u0275\u0275directiveInject(MatSnackBar), \u0275\u0275directiveInject(MatDialog), \u0275\u0275directiveInject(Router), \u0275\u0275directiveInject(State), \u0275\u0275directiveInject(Store), \u0275\u0275directiveInject(ActionsSubject), \u0275\u0275directiveInject(Location));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _S3BucketListComponent,
            selectors: [["s3-bucket-list"]],
            viewQuery: function S3BucketListComponent_Query(rf, ctx) {
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
            features: [\u0275\u0275ProvidersFeature([S3Service, AwsMockHttpService])],
            decls: 53,
            vars: 24,
            consts: [["appearance", "outlined", 2, "margin", "3px"], ["aria-label", "Back", "mat-icon-button", "", 1, "head-buttons-left", 3, "click"], [1, "fill-remaining-space"], ["aria-label", "Refresh", "mat-icon-button", "", 3, "click"], ["appearance", "outlined", 2, "margin", "-10px"], ["align", "start"], [2, "width", "100%"], ["matInput", "", "name", "search", "placeholder", "Search", "type", "text", 3, "ngModelChange", "ngModel"], ["mat-icon-button", "", "matSuffix", "", "style", "float: right", 3, "click", 4, "ngIf"], [1, "table-container"], ["mat-table", "", "matSort", "", "matSortDisableClear", "false", 3, "matSortChange", "dataSource", "matSortActive", "matSortDirection"], ["matColumnDef", "name"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Queue name", "sortActionDescription", "Sort by queueUrl", 4, "matHeaderCellDef"], ["mat-cell", "", 4, "matCellDef"], ["matColumnDef", "keys"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Objects", "sortActionDescription", "Sort by objects", 4, "matHeaderCellDef"], ["matColumnDef", "size"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Size", "sortActionDescription", "Sort by size", 4, "matHeaderCellDef"], ["matColumnDef", "created", "matTooltip", "Created"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Create timestamp", "sortActionDescription", "Sort by created", 4, "matHeaderCellDef"], ["matColumnDef", "modified", "matTooltip", "Modified"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Modified timestamp", "sortActionDescription", "Sort by modified", 4, "matHeaderCellDef"], ["matColumnDef", "actions"], ["mat-header-cell", "", "style", "width:200px", 4, "matHeaderCellDef"], ["mat-header-row", "", 4, "matHeaderRowDef"], ["mat-row", "", 4, "matRowDef", "matRowDefColumns"], ["class", "mat-row", 4, "matNoDataRow"], ["aria-label", "Select page", 2, "width", "99%", "margin-left", "15px", 3, "page", "disabled", "hidePageSize", "length", "pageIndex", "pageSizeOptions", "pageSize", "showFirstLastButtons"], [1, "footer"], ["mat-icon-button", "", "matSuffix", "", 2, "float", "right", 3, "click"], ["matSuffix", ""], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Queue name", "sortActionDescription", "Sort by queueUrl"], ["mat-cell", ""], ["mat-list-item", "", 3, "routerLink"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Objects", "sortActionDescription", "Sort by objects"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Size", "sortActionDescription", "Sort by size"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Create timestamp", "sortActionDescription", "Sort by created"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Modified timestamp", "sortActionDescription", "Sort by modified"], ["mat-header-cell", "", 2, "width", "200px"], ["aria-label", "List", "mat-icon-button", "", "matTooltip", "Show details of the bucket", 3, "routerLink"], ["aria-label", "PurgeBucket", "mat-icon-button", "", "matTooltip", "Delete all objects in the bucket", 3, "click"], ["aria-label", "DeleteBucket", "mat-icon-button", "", "matTooltip", "Delete the bucket and all objects", 3, "click"], ["mat-header-row", ""], ["mat-row", ""], [1, "mat-row"], [1, "mat-cell", 2, "padding-left", "20px", "padding-top", "10px"]],
            template: function S3BucketListComponent_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "mat-card", 0)(1, "mat-card-header")(2, "button", 1);
                    \u0275\u0275listener("click", function S3BucketListComponent_Template_button_click_2_listener() {
                        return ctx.back();
                    });
                    \u0275\u0275elementStart(3, "mat-icon");
                    \u0275\u0275text(4, "arrow_back");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(5, "span", 2)(6, "h4");
                    \u0275\u0275text(7, "S3 Buckets");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(8, "button", 3);
                    \u0275\u0275listener("click", function S3BucketListComponent_Template_button_click_8_listener() {
                        return ctx.addBucket();
                    });
                    \u0275\u0275elementStart(9, "mat-icon");
                    \u0275\u0275text(10, "add");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(11, "button", 3);
                    \u0275\u0275listener("click", function S3BucketListComponent_Template_button_click_11_listener() {
                        return ctx.refresh();
                    });
                    \u0275\u0275elementStart(12, "mat-icon");
                    \u0275\u0275text(13, "refresh");
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(14, "mat-card-content")(15, "mat-card", 4)(16, "mat-card-actions", 5)(17, "mat-form-field", 6)(18, "mat-label");
                    \u0275\u0275text(19, "Prefix");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(20, "input", 7);
                    \u0275\u0275twoWayListener("ngModelChange", function S3BucketListComponent_Template_input_ngModelChange_20_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.prefixValue, $event) || (ctx.prefixValue = $event);
                        return $event;
                    });
                    \u0275\u0275elementEnd();
                    \u0275\u0275template(21, S3BucketListComponent_button_21_Template, 3, 0, "button", 8)(22, S3BucketListComponent_button_22_Template, 3, 0, "button", 8);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(23, "mat-card-content")(24, "div", 9)(25, "table", 10);
                    \u0275\u0275listener("matSortChange", function S3BucketListComponent_Template_table_matSortChange_25_listener($event) {
                        return ctx.sortChange($event);
                    });
                    \u0275\u0275elementContainerStart(26, 11);
                    \u0275\u0275template(27, S3BucketListComponent_th_27_Template, 2, 0, "th", 12)(28, S3BucketListComponent_td_28_Template, 4, 3, "td", 13);
                    \u0275\u0275elementContainerEnd();
                    \u0275\u0275elementContainerStart(29, 14);
                    \u0275\u0275template(30, S3BucketListComponent_th_30_Template, 2, 0, "th", 15)(31, S3BucketListComponent_td_31_Template, 2, 1, "td", 13);
                    \u0275\u0275elementContainerEnd();
                    \u0275\u0275elementContainerStart(32, 16);
                    \u0275\u0275template(33, S3BucketListComponent_th_33_Template, 2, 0, "th", 17)(34, S3BucketListComponent_td_34_Template, 2, 1, "td", 13);
                    \u0275\u0275elementContainerEnd();
                    \u0275\u0275elementContainerStart(35, 18);
                    \u0275\u0275template(36, S3BucketListComponent_th_36_Template, 2, 0, "th", 19)(37, S3BucketListComponent_td_37_Template, 3, 4, "td", 13);
                    \u0275\u0275elementContainerEnd();
                    \u0275\u0275elementContainerStart(38, 20);
                    \u0275\u0275template(39, S3BucketListComponent_th_39_Template, 2, 0, "th", 21)(40, S3BucketListComponent_td_40_Template, 3, 4, "td", 13);
                    \u0275\u0275elementContainerEnd();
                    \u0275\u0275elementContainerStart(41, 22);
                    \u0275\u0275template(42, S3BucketListComponent_th_42_Template, 2, 0, "th", 23)(43, S3BucketListComponent_td_43_Template, 10, 2, "td", 13);
                    \u0275\u0275elementContainerEnd();
                    \u0275\u0275template(44, S3BucketListComponent_tr_44_Template, 1, 0, "tr", 24)(45, S3BucketListComponent_tr_45_Template, 1, 0, "tr", 25)(46, S3BucketListComponent_tr_46_Template, 3, 1, "tr", 26);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(47, "mat-paginator", 27);
                    \u0275\u0275pipe(48, "async");
                    \u0275\u0275pipe(49, "async");
                    \u0275\u0275listener("page", function S3BucketListComponent_Template_mat_paginator_page_47_listener($event) {
                        return ctx.handlePageEvent($event);
                    });
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(50, "div", 28);
                    \u0275\u0275text(51);
                    \u0275\u0275pipe(52, "date");
                    \u0275\u0275elementEnd()()();
                }
                if (rf & 2) {
                    \u0275\u0275advance(20);
                    \u0275\u0275twoWayProperty("ngModel", ctx.prefixValue);
                    \u0275\u0275advance();
                    \u0275\u0275property("ngIf", !ctx.prefixSet);
                    \u0275\u0275advance();
                    \u0275\u0275property("ngIf", ctx.prefixSet);
                    \u0275\u0275advance(3);
                    \u0275\u0275property("dataSource", ctx.dataSource)("matSortActive", ctx.defaultSort.active)("matSortDirection", ctx.defaultSort.direction);
                    \u0275\u0275advance(19);
                    \u0275\u0275property("matHeaderRowDef", ctx.columns);
                    \u0275\u0275advance();
                    \u0275\u0275property("matRowDefColumns", ctx.columns);
                    \u0275\u0275advance(2);
                    \u0275\u0275property("disabled", ctx.disabled)("hidePageSize", ctx.hidePageSize)("length", ctx.total)("pageIndex", \u0275\u0275pipeBind1(48, 16, ctx.pageIndex$))("pageSizeOptions", ctx.showPageSizeOptions ? ctx.pageSizeOptions : \u0275\u0275pureFunction0(23, _c0))("pageSize", \u0275\u0275pipeBind1(49, 18, ctx.pageSize$))("showFirstLastButtons", ctx.showFirstLastButtons);
                    \u0275\u0275advance(4);
                    \u0275\u0275textInterpolate1(" Last update: ", \u0275\u0275pipeBind2(52, 20, ctx.lastUpdate, "HH:mm:ss"), " ");
                }
            },
            dependencies: [MatCard, MatCardHeader, MatCardContent, MatCardActions, MatTable, MatHeaderCellDef, MatCellDef, MatColumnDef, MatIcon, MatHeaderCell, MatCell, MatHeaderRowDef, MatHeaderRow, MatSortHeader, MatRowDef, MatNoDataRow, MatIconButton, MatRow, MatPaginator, MatSort, MatTooltip, RouterLink, MatListItem, MatNavList, MatFormField, MatInput, MatLabel, MatSuffix, NgIf, DefaultValueAccessor, NgControlStatus, NgModel, DatePipe, AsyncPipe],
            styles: ["\n\n[_nghost-%COMP%] {\n  position: relative;\n  width: 100%;\n  height: 30%;\n  margin-top: 0;\n  padding-bottom: 33%;\n}\n.head-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  justify-content: flex-end;\n}\n.head-buttons-left[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: start;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  justify-content: start;\n}\n.fill-remaining-space[_ngcontent-%COMP%] {\n  flex: 1 1 auto;\n}\n.table-container[_ngcontent-%COMP%] {\n  max-height: calc(100vh - 10px);\n  overflow: auto;\n}\n.footer-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  width: 50%;\n  justify-content: flex-end;\n}\n.footer[_ngcontent-%COMP%] {\n  display: flex;\n  width: 50%;\n  font-size: x-small;\n  color: black;\n  padding-top: 15px;\n}\n/*# sourceMappingURL=bucket-list.component.css.map */"]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(S3BucketListComponent, {
        className: "S3BucketListComponent",
        filePath: "src/app/modules/s3/bucket-list/bucket-list.component.ts",
        lineNumber: 26
    });
})();

// src/app/modules/s3/bucket-detail/bucket-detail.component.ts
function S3BucketDetailComponent_th_86_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 31);
        \u0275\u0275text(1, "ID");
        \u0275\u0275elementEnd();
    }
}

function S3BucketDetailComponent_td_87_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 32);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r1 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r1.id, "");
    }
}

function S3BucketDetailComponent_th_89_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 33);
        \u0275\u0275text(1, "ARN");
        \u0275\u0275elementEnd();
    }
}

function S3BucketDetailComponent_td_90_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 32);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r2 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r2.lambdaArn, "");
    }
}

function S3BucketDetailComponent_th_92_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 34);
        \u0275\u0275text(1, "Actions");
        \u0275\u0275elementEnd();
    }
}

function S3BucketDetailComponent_td_93_Template(rf, ctx) {
    if (rf & 1) {
        const _r3 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "td", 32)(1, "button", 35);
        \u0275\u0275listener("click", function S3BucketDetailComponent_td_93_Template_button_click_1_listener() {
            const row_r4 = \u0275\u0275restoreView(_r3).$implicit;
            const ctx_r4 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r4.deleteLambdaNotification(row_r4.lambdaArn));
        });
        \u0275\u0275elementStart(2, "mat-icon");
        \u0275\u0275text(3, "delete");
        \u0275\u0275elementEnd()()();
    }
}

function S3BucketDetailComponent_tr_94_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 36);
    }
}

function S3BucketDetailComponent_tr_95_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 37);
    }
}

function S3BucketDetailComponent_tr_96_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "tr", 38)(1, "td", 39);
        \u0275\u0275text(2, " No data matching the filter. ");
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const ctx_r4 = \u0275\u0275nextContext();
        \u0275\u0275advance();
        \u0275\u0275attribute("colspan", ctx_r4.lambdaNotificationColumns.length);
    }
}

var S3BucketDetailComponent = class _S3BucketDetailComponent {
    constructor(location, route, s3Service) {
        this.location = location;
        this.route = route;
        this.s3Service = s3Service;
        this.lastUpdate = "";
        this.bucketItem = {};
        this.bucketName = "";
        this.lambdaNotificationColumns = ["id", "lambdaArn", "actions"];
        this.lambdaNotificationData = [];
        this.lambdaNotificationDataSource = new MatTableDataSource(this.lambdaNotificationData);
        this.lambdaNotificationPageSize = 10;
        this.lambdaNotificationPageIndex = 0;
        this.lambdaNotificationLength = 0;
        this.lambdaNotificationPageSizeOptions = [5, 10, 20, 50, 100];
        this.byteConversion = byteConversion;
        this._liveAnnouncer = inject(LiveAnnouncer);
    }

    ngOnInit() {
        this.sub = this.route.params.subscribe((params) => {
            this.bucketName = params["bucketName"];
        });
        this.loadBucket();
    }

    ngOnDestroy() {
        this.sub.unsubscribe();
    }

    back() {
        this.location.back();
    }

    refresh() {
        this.loadBucket();
    }

    lastUpdateTime() {
        return (/* @__PURE__ */ new Date()).toLocaleTimeString("DE-de");
    }

    // ===================================================================================================================
    // Details
    // ===================================================================================================================
    loadBucket() {
        this.s3Service.getBucket(this.bucketName).subscribe((data) => {
            this.lastUpdate = this.lastUpdateTime();
            if (data) {
                this.bucketItem = data;
                if (this.bucketItem.lambdaConfigurations) {
                    this.lambdaNotificationData = this.bucketItem.lambdaConfigurations;
                    this.lambdaNotificationDataSource.data = this.lambdaNotificationData;
                }
            }
        });
    }

    // ===================================================================================================================
    // Lambda Notifications
    // ===================================================================================================================
    lambdaNotificationSortChange(sortState) {
        if (sortState.direction) {
            this._liveAnnouncer.announce(`Sorted ${sortState.direction}ending`);
        } else {
            this._liveAnnouncer.announce("Sorting cleared");
        }
        this.loadBucket();
    }

    handleLambdaNotificationPageEvent(e2) {
    }

    deleteLambdaNotification(lambdaNotificationArn) {
        this.bucketItem.lambdaConfigurations = this.bucketItem.lambdaConfigurations?.filter((ele) => ele.lambdaArn !== lambdaNotificationArn);
        if (this.bucketItem.lambdaConfigurations) {
            this.lambdaNotificationData = this.bucketItem.lambdaConfigurations;
            this.lambdaNotificationDataSource.data = this.lambdaNotificationData;
        }
    }

    // ===================================================================================================================
    // Queue Notifications
    // ===================================================================================================================
    // ===================================================================================================================
    // Topic Notifications
    // ===================================================================================================================
    save() {
        this.location.back();
    }

    static {
        this.\u0275fac = function S3BucketDetailComponent_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _S3BucketDetailComponent)(\u0275\u0275directiveInject(Location), \u0275\u0275directiveInject(ActivatedRoute), \u0275\u0275directiveInject(S3Service));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _S3BucketDetailComponent,
            selectors: [["bucket-detail-component"]],
            features: [\u0275\u0275ProvidersFeature([S3Service])],
            decls: 109,
            vars: 31,
            consts: [["appearance", "outlined", 2, "margin", "3px"], ["aria-label", "Back", "mat-icon-button", "", 1, "head-buttons-left", 3, "click"], [1, "fill-remaining-space"], ["aria-label", "Refresh", "mat-icon-button", "", 3, "click"], ["cols", "2", "rowHeight", "420px"], [3, "colspan", "rowspan"], [2, "width", "100%", "display", "flex", "align-items", "flex-start", "align-content", "flex-start"], [2, "height", "80px"], ["matListItemTitle", "", 1, "mat-list-span-title"], ["matListItemLine", "", 1, "mat-list-span-value"], [2, "height", "60px"], ["appearance", "outlined", 2, "margin-top", "5px"], ["label", "Lambda Notifications"], [1, "head-buttons"], ["mat-table", "", "matSort", "", 1, "mat-elevation-z8", 3, "matSortChange", "dataSource"], ["matColumnDef", "id"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "ID", "sortActionDescription", "Sort by ID", 4, "matHeaderCellDef"], ["mat-cell", "", 4, "matCellDef"], ["matColumnDef", "lambdaArn"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "ARN", "sortActionDescription", "Sort by arn", 4, "matHeaderCellDef"], ["matColumnDef", "actions"], ["mat-header-cell", "", "style", "width:120px", 4, "matHeaderCellDef"], ["mat-header-row", "", 4, "matHeaderRowDef"], ["mat-row", "", 4, "matRowDef", "matRowDefColumns"], ["class", "mat-row", 4, "matNoDataRow"], ["aria-label", "Select page", 3, "page", "disabled", "hidePageSize", "length", "pageIndex", "pageSizeOptions", "pageSize", "showFirstLastButtons"], ["label", "Queue Notifications"], ["label", "Topic Notifications"], ["align", "end"], ["mat-button", "", 3, "click"], [1, "footer"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "ID", "sortActionDescription", "Sort by ID"], ["mat-cell", ""], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "ARN", "sortActionDescription", "Sort by arn"], ["mat-header-cell", "", 2, "width", "120px"], ["aria-label", "Delete", "mat-icon-button", "", "matTooltip", "Delete lambda notification", 3, "click"], ["mat-header-row", ""], ["mat-row", ""], [1, "mat-row"], [1, "mat-cell"]],
            template: function S3BucketDetailComponent_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "mat-card", 0)(1, "mat-card-header")(2, "span")(3, "button", 1);
                    \u0275\u0275listener("click", function S3BucketDetailComponent_Template_button_click_3_listener() {
                        return ctx.back();
                    });
                    \u0275\u0275elementStart(4, "mat-icon");
                    \u0275\u0275text(5, "arrow_back");
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(6, "span", 2)(7, "h4");
                    \u0275\u0275text(8);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(9, "span")(10, "button", 3);
                    \u0275\u0275listener("click", function S3BucketDetailComponent_Template_button_click_10_listener() {
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
                    \u0275\u0275text(29, "Bucket name: ");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(30, "p", 9);
                    \u0275\u0275text(31);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(32, "mat-list-item", 7)(33, "p", 8);
                    \u0275\u0275text(34, "ARN: ");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(35, "p", 9);
                    \u0275\u0275text(36);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(37, "mat-list-item", 7)(38, "p", 8);
                    \u0275\u0275text(39, "Owner: ");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(40, "p", 9);
                    \u0275\u0275text(41);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(42, "mat-list-item", 7)(43, "p", 8);
                    \u0275\u0275text(44, "Version Status: ");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(45, "p", 9);
                    \u0275\u0275text(46);
                    \u0275\u0275elementEnd()()()()();
                    \u0275\u0275elementStart(47, "mat-grid-tile", 5)(48, "div", 6)(49, "mat-list")(50, "mat-list-item", 7)(51, "p", 8);
                    \u0275\u0275text(52, "Number of objects:");
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
                    \u0275\u0275text(62, "Created:");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(63, "p", 9);
                    \u0275\u0275text(64);
                    \u0275\u0275pipe(65, "date");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(66, "mat-list-item", 7)(67, "p", 8);
                    \u0275\u0275text(68, "Modified:");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(69, "p", 9);
                    \u0275\u0275text(70);
                    \u0275\u0275pipe(71, "date");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275element(72, "mat-list-item", 10);
                    \u0275\u0275elementEnd()()()()()();
                    \u0275\u0275elementStart(73, "mat-card", 11)(74, "mat-card-header")(75, "mat-card-title");
                    \u0275\u0275text(76, "Info");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(77, "mat-card-content")(78, "mat-tab-group")(79, "mat-tab", 12)(80, "mat-card-actions", 13)(81, "button", 3);
                    \u0275\u0275listener("click", function S3BucketDetailComponent_Template_button_click_81_listener() {
                        return ctx.loadBucket();
                    });
                    \u0275\u0275elementStart(82, "mat-icon");
                    \u0275\u0275text(83, "refresh");
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(84, "table", 14);
                    \u0275\u0275listener("matSortChange", function S3BucketDetailComponent_Template_table_matSortChange_84_listener($event) {
                        return ctx.lambdaNotificationSortChange($event);
                    });
                    \u0275\u0275elementContainerStart(85, 15);
                    \u0275\u0275template(86, S3BucketDetailComponent_th_86_Template, 2, 0, "th", 16)(87, S3BucketDetailComponent_td_87_Template, 2, 1, "td", 17);
                    \u0275\u0275elementContainerEnd();
                    \u0275\u0275elementContainerStart(88, 18);
                    \u0275\u0275template(89, S3BucketDetailComponent_th_89_Template, 2, 0, "th", 19)(90, S3BucketDetailComponent_td_90_Template, 2, 1, "td", 17);
                    \u0275\u0275elementContainerEnd();
                    \u0275\u0275elementContainerStart(91, 20);
                    \u0275\u0275template(92, S3BucketDetailComponent_th_92_Template, 2, 0, "th", 21)(93, S3BucketDetailComponent_td_93_Template, 4, 0, "td", 17);
                    \u0275\u0275elementContainerEnd();
                    \u0275\u0275template(94, S3BucketDetailComponent_tr_94_Template, 1, 0, "tr", 22)(95, S3BucketDetailComponent_tr_95_Template, 1, 0, "tr", 23)(96, S3BucketDetailComponent_tr_96_Template, 3, 1, "tr", 24);
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(97, "mat-paginator", 25);
                    \u0275\u0275listener("page", function S3BucketDetailComponent_Template_mat_paginator_page_97_listener($event) {
                        return ctx.handleLambdaNotificationPageEvent($event);
                    });
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(98, "mat-tab", 26);
                    \u0275\u0275text(99, " Queue Notifications ");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(100, "mat-tab", 27);
                    \u0275\u0275text(101, " Topic Notifications ");
                    \u0275\u0275elementEnd()()()();
                    \u0275\u0275elementStart(102, "mat-card-actions", 28)(103, "button", 29);
                    \u0275\u0275listener("click", function S3BucketDetailComponent_Template_button_click_103_listener() {
                        return ctx.back();
                    });
                    \u0275\u0275text(104, "Close");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(105, "button", 29);
                    \u0275\u0275listener("click", function S3BucketDetailComponent_Template_button_click_105_listener() {
                        return ctx.save();
                    });
                    \u0275\u0275text(106, "Save");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(107, "div", 30);
                    \u0275\u0275text(108);
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    \u0275\u0275advance(8);
                    \u0275\u0275textInterpolate1("S3 Buckets Details: ", ctx.bucketName, "");
                    \u0275\u0275advance(11);
                    \u0275\u0275property("colspan", 1)("rowspan", 1);
                    \u0275\u0275advance(7);
                    \u0275\u0275textInterpolate(ctx.bucketItem.region);
                    \u0275\u0275advance(5);
                    \u0275\u0275textInterpolate(ctx.bucketItem.bucketName);
                    \u0275\u0275advance(5);
                    \u0275\u0275textInterpolate(ctx.bucketItem.arn);
                    \u0275\u0275advance(5);
                    \u0275\u0275textInterpolate(ctx.bucketItem.owner);
                    \u0275\u0275advance(5);
                    \u0275\u0275textInterpolate(ctx.bucketItem.versionStatus);
                    \u0275\u0275advance();
                    \u0275\u0275property("colspan", 1)("rowspan", 1);
                    \u0275\u0275advance(7);
                    \u0275\u0275textInterpolate(ctx.bucketItem.keys);
                    \u0275\u0275advance(5);
                    \u0275\u0275textInterpolate(ctx.byteConversion(ctx.bucketItem.size));
                    \u0275\u0275advance(5);
                    \u0275\u0275textInterpolate(\u0275\u0275pipeBind2(65, 25, ctx.bucketItem.created, "yyyy-MM-dd HH:mm:ss"));
                    \u0275\u0275advance(6);
                    \u0275\u0275textInterpolate(\u0275\u0275pipeBind2(71, 28, ctx.bucketItem.modified, "yyyy-MM-dd HH:mm:ss"));
                    \u0275\u0275advance(14);
                    \u0275\u0275property("dataSource", ctx.lambdaNotificationDataSource);
                    \u0275\u0275advance(10);
                    \u0275\u0275property("matHeaderRowDef", ctx.lambdaNotificationColumns);
                    \u0275\u0275advance();
                    \u0275\u0275property("matRowDefColumns", ctx.lambdaNotificationColumns);
                    \u0275\u0275advance(2);
                    \u0275\u0275property("disabled", false)("hidePageSize", false)("length", ctx.lambdaNotificationLength)("pageIndex", ctx.lambdaNotificationPageIndex)("pageSizeOptions", ctx.lambdaNotificationPageSizeOptions)("pageSize", ctx.lambdaNotificationPageSize)("showFirstLastButtons", true);
                    \u0275\u0275advance(11);
                    \u0275\u0275textInterpolate1(" Last update: ", ctx.lastUpdate, " ");
                }
            },
            dependencies: [MatCard, MatCardHeader, MatCardContent, MatCardActions, MatCardTitle, MatTable, MatHeaderCellDef, MatCellDef, MatColumnDef, MatIcon, MatHeaderCell, MatCell, MatHeaderRowDef, MatHeaderRow, MatSortHeader, MatRowDef, MatNoDataRow, MatIconButton, MatRow, MatPaginator, MatSort, MatTooltip, MatListItem, MatGridTile, MatGridList, MatList, MatTabGroup, MatTab, MatButton, DatePipe],
            styles: ["\n\nbody[_ngcontent-%COMP%] {\n  margin: 40px;\n}\n.container[_ngcontent-%COMP%] {\n  width: 100%;\n}\n.form[_ngcontent-%COMP%] {\n  min-width: 150px;\n  width: 100%;\n  margin-right: 10px;\n}\n.form-full-width[_ngcontent-%COMP%] {\n  width: 100%;\n}\n.head-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  justify-content: flex-end;\n}\n.footer[_ngcontent-%COMP%] {\n  display: flex;\n  width: 50%;\n  font-size: x-small;\n  color: black;\n}\n.fill-remaining-space[_ngcontent-%COMP%] {\n  flex: 1 1 auto;\n}\n/*# sourceMappingURL=bucket-detail.component.css.map */"]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(S3BucketDetailComponent, {
        className: "S3BucketDetailComponent",
        filePath: "src/app/modules/s3/bucket-detail/bucket-detail.component.ts",
        lineNumber: 18
    });
})();

// src/app/modules/s3/object-list/state/s3-object-list.actions.ts
var s3ObjectListActions = {
    initialize: createAction("[s3-object-list] initialize"),
    // Load objects
    loadObjects: createAction("[s3-object-list] Load Objects", props()),
    loadObjectsSuccess: createAction("[s3-object-list] Load Objects Success", props()),
    loadObjectsFailure: createAction("[s3-object-list] Load Objects Error", props()),
    // Add object
    //addObject: createAction('[s3-object-list] Add Object', props<{ objectName: string }>()),
    //addObjectSuccess: createAction('[s3-object-list] Add Object Success'),
    //addObjectFailure: createAction('[s3-object-list] Add Object Error', props<{ error: string }>()),
    // Delete object
    deleteObject: createAction("[s3-object-list] Delete Object", props()),
    deleteObjectSuccess: createAction("[s3-object-list] Delete Object Success"),
    deleteObjectFailure: createAction("[s3-object-list] Delete Object Error", props())
};

// src/app/modules/s3/object-list/state/s3-object-list.reducer.ts
var s3ObjectListFeatureKey = "s3-object-list";
var initialState2 = {
    s3ObjectCounters: {total: 0, objectCounters: []},
    prefix: "",
    pageSize: 10,
    pageIndex: 0,
    loading: false,
    sortColumns: [{column: "key", sortDirection: -1}],
    error: {}
};
var s3ObjectListReducer = createReducer(
    initialState2,
    // Initialize
    on(s3ObjectListActions.initialize, (state) => __spreadProps(__spreadValues({}, state), {pageIndex: 0, pageSize: 10, loading: true})),
    // Object list
    on(s3ObjectListActions.loadObjects, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(s3ObjectListActions.loadObjectsSuccess, (state, {objects}) => __spreadProps(__spreadValues({}, state), {s3ObjectCounters: objects, loading: false})),
    on(s3ObjectListActions.loadObjectsFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false})),
    // Add object
    //on(s3ObjectListActions.addObject, (state: S3ObjectListState) => ({...state, loading: true})),
    //on(s3ObjectListActions.addObjectSuccess, (state: S3ObjectListState) => ({...state, loading: false})),
    //on(s3ObjectListActions.addObjectFailure, (state: S3ObjectListState, {error}) => ({...state, error: error, loading: false})),
    // Delete object
    on(s3ObjectListActions.deleteObject, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(s3ObjectListActions.deleteObjectSuccess, (state) => __spreadProps(__spreadValues({}, state), {loading: false})),
    on(s3ObjectListActions.deleteObjectFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false}))
);

// src/app/modules/s3/object-list/state/s3-object-list.selectors.ts
var selectObjectListFeature = createFeatureSelector(s3ObjectListFeatureKey);
var selectIsLoading2 = createSelector(selectObjectListFeature, (state) => state.loading);
var selectPrefix2 = createSelector(selectObjectListFeature, (state) => state?.prefix);
var selectPageSize2 = createSelector(selectObjectListFeature, (state) => state?.pageSize);
var selectPageIndex2 = createSelector(selectObjectListFeature, (state) => state?.pageIndex);
var selectSortColumns2 = createSelector(selectObjectListFeature, (state) => state?.sortColumns);
var selectObjectCounters = createSelector(selectObjectListFeature, (state) => state?.s3ObjectCounters);

// node_modules/@angular/material/fesm2022/progress-bar.mjs
function MatProgressBar_Conditional_2_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "div", 2);
    }
}

var MAT_PROGRESS_BAR_DEFAULT_OPTIONS = new InjectionToken("MAT_PROGRESS_BAR_DEFAULT_OPTIONS");
var MAT_PROGRESS_BAR_LOCATION = new InjectionToken("mat-progress-bar-location", {
    providedIn: "root",
    factory: MAT_PROGRESS_BAR_LOCATION_FACTORY
});

function MAT_PROGRESS_BAR_LOCATION_FACTORY() {
    const _document = inject(DOCUMENT);
    const _location = _document ? _document.location : null;
    return {
        // Note that this needs to be a function, rather than a property, because Angular
        // will only resolve it once, but we want the current path on each call.
        getPathname: () => _location ? _location.pathname + _location.search : ""
    };
}

var MatProgressBar = class _MatProgressBar {
    constructor(_elementRef, _ngZone, _changeDetectorRef, _animationMode, defaults) {
        this._elementRef = _elementRef;
        this._ngZone = _ngZone;
        this._changeDetectorRef = _changeDetectorRef;
        this._animationMode = _animationMode;
        this._isNoopAnimation = false;
        this._defaultColor = "primary";
        this._value = 0;
        this._bufferValue = 0;
        this.animationEnd = new EventEmitter();
        this._mode = "determinate";
        this._transitionendHandler = (event) => {
            if (this.animationEnd.observers.length === 0 || !event.target || !event.target.classList.contains("mdc-linear-progress__primary-bar")) {
                return;
            }
            if (this.mode === "determinate" || this.mode === "buffer") {
                this._ngZone.run(() => this.animationEnd.next({
                    value: this.value
                }));
            }
        };
        this._isNoopAnimation = _animationMode === "NoopAnimations";
        if (defaults) {
            if (defaults.color) {
                this.color = this._defaultColor = defaults.color;
            }
            this.mode = defaults.mode || this.mode;
        }
    }

    // TODO: should be typed as `ThemePalette` but internal apps pass in arbitrary strings.
    /**
     * Theme color of the progress bar. This API is supported in M2 themes only, it
     * has no effect in M3 themes.
     *
     * For information on applying color variants in M3, see
     * https://material.angular.io/guide/theming#using-component-color-variants.
     */
    get color() {
        return this._color || this._defaultColor;
    }

    set color(value) {
        this._color = value;
    }

    /** Value of the progress bar. Defaults to zero. Mirrored to aria-valuenow. */
    get value() {
        return this._value;
    }

    set value(v2) {
        this._value = clamp(v2 || 0);
        this._changeDetectorRef.markForCheck();
    }

    /** Buffer value of the progress bar. Defaults to zero. */
    get bufferValue() {
        return this._bufferValue || 0;
    }

    set bufferValue(v2) {
        this._bufferValue = clamp(v2 || 0);
        this._changeDetectorRef.markForCheck();
    }

    /**
     * Mode of the progress bar.
     *
     * Input must be one of these values: determinate, indeterminate, buffer, query, defaults to
     * 'determinate'.
     * Mirrored to mode attribute.
     */
    get mode() {
        return this._mode;
    }

    set mode(value) {
        this._mode = value;
        this._changeDetectorRef.markForCheck();
    }

    ngAfterViewInit() {
        this._ngZone.runOutsideAngular(() => {
            this._elementRef.nativeElement.addEventListener("transitionend", this._transitionendHandler);
        });
    }

    ngOnDestroy() {
        this._elementRef.nativeElement.removeEventListener("transitionend", this._transitionendHandler);
    }

    /** Gets the transform style that should be applied to the primary bar. */
    _getPrimaryBarTransform() {
        return `scaleX(${this._isIndeterminate() ? 1 : this.value / 100})`;
    }

    /** Gets the `flex-basis` value that should be applied to the buffer bar. */
    _getBufferBarFlexBasis() {
        return `${this.mode === "buffer" ? this.bufferValue : 100}%`;
    }

    /** Returns whether the progress bar is indeterminate. */
    _isIndeterminate() {
        return this.mode === "indeterminate" || this.mode === "query";
    }

    static {
        this.\u0275fac = function MatProgressBar_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _MatProgressBar)(\u0275\u0275directiveInject(ElementRef), \u0275\u0275directiveInject(NgZone), \u0275\u0275directiveInject(ChangeDetectorRef), \u0275\u0275directiveInject(ANIMATION_MODULE_TYPE, 8), \u0275\u0275directiveInject(MAT_PROGRESS_BAR_DEFAULT_OPTIONS, 8));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _MatProgressBar,
            selectors: [["mat-progress-bar"]],
            hostAttrs: ["role", "progressbar", "aria-valuemin", "0", "aria-valuemax", "100", "tabindex", "-1", 1, "mat-mdc-progress-bar", "mdc-linear-progress"],
            hostVars: 10,
            hostBindings: function MatProgressBar_HostBindings(rf, ctx) {
                if (rf & 2) {
                    \u0275\u0275attribute("aria-valuenow", ctx._isIndeterminate() ? null : ctx.value)("mode", ctx.mode);
                    \u0275\u0275classMap("mat-" + ctx.color);
                    \u0275\u0275classProp("_mat-animation-noopable", ctx._isNoopAnimation)("mdc-linear-progress--animation-ready", !ctx._isNoopAnimation)("mdc-linear-progress--indeterminate", ctx._isIndeterminate());
                }
            },
            inputs: {
                color: "color",
                value: [2, "value", "value", numberAttribute],
                bufferValue: [2, "bufferValue", "bufferValue", numberAttribute],
                mode: "mode"
            },
            outputs: {
                animationEnd: "animationEnd"
            },
            exportAs: ["matProgressBar"],
            standalone: true,
            features: [\u0275\u0275InputTransformsFeature, \u0275\u0275StandaloneFeature],
            decls: 7,
            vars: 5,
            consts: [["aria-hidden", "true", 1, "mdc-linear-progress__buffer"], [1, "mdc-linear-progress__buffer-bar"], [1, "mdc-linear-progress__buffer-dots"], ["aria-hidden", "true", 1, "mdc-linear-progress__bar", "mdc-linear-progress__primary-bar"], [1, "mdc-linear-progress__bar-inner"], ["aria-hidden", "true", 1, "mdc-linear-progress__bar", "mdc-linear-progress__secondary-bar"]],
            template: function MatProgressBar_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "div", 0);
                    \u0275\u0275element(1, "div", 1);
                    \u0275\u0275template(2, MatProgressBar_Conditional_2_Template, 1, 0, "div", 2);
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(3, "div", 3);
                    \u0275\u0275element(4, "span", 4);
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(5, "div", 5);
                    \u0275\u0275element(6, "span", 4);
                    \u0275\u0275elementEnd();
                }
                if (rf & 2) {
                    \u0275\u0275advance();
                    \u0275\u0275styleProp("flex-basis", ctx._getBufferBarFlexBasis());
                    \u0275\u0275advance();
                    \u0275\u0275conditional(ctx.mode === "buffer" ? 2 : -1);
                    \u0275\u0275advance();
                    \u0275\u0275styleProp("transform", ctx._getPrimaryBarTransform());
                }
            },
            styles: [`.mat-mdc-progress-bar{display:block;text-align:start}.mat-mdc-progress-bar[mode=query]{transform:scaleX(-1)}.mat-mdc-progress-bar._mat-animation-noopable .mdc-linear-progress__buffer-dots,.mat-mdc-progress-bar._mat-animation-noopable .mdc-linear-progress__primary-bar,.mat-mdc-progress-bar._mat-animation-noopable .mdc-linear-progress__secondary-bar,.mat-mdc-progress-bar._mat-animation-noopable .mdc-linear-progress__bar-inner.mdc-linear-progress__bar-inner{animation:none}.mat-mdc-progress-bar._mat-animation-noopable .mdc-linear-progress__primary-bar,.mat-mdc-progress-bar._mat-animation-noopable .mdc-linear-progress__buffer-bar{transition:transform 1ms}.mdc-linear-progress{position:relative;width:100%;transform:translateZ(0);outline:1px solid rgba(0,0,0,0);overflow-x:hidden;transition:opacity 250ms 0ms cubic-bezier(0.4, 0, 0.6, 1);height:max(var(--mdc-linear-progress-track-height),var(--mdc-linear-progress-active-indicator-height))}.cdk-high-contrast-active .mdc-linear-progress{outline-color:CanvasText}.mdc-linear-progress__bar{position:absolute;top:0;bottom:0;margin:auto 0;width:100%;animation:none;transform-origin:top left;transition:transform 250ms 0ms cubic-bezier(0.4, 0, 0.6, 1);height:var(--mdc-linear-progress-active-indicator-height)}.mdc-linear-progress--indeterminate .mdc-linear-progress__bar{transition:none}[dir=rtl] .mdc-linear-progress__bar{right:0;transform-origin:center right}.mdc-linear-progress__bar-inner{display:inline-block;position:absolute;width:100%;animation:none;border-top-style:solid;border-color:var(--mdc-linear-progress-active-indicator-color, var(--mat-app-primary));border-top-width:var(--mdc-linear-progress-active-indicator-height)}.mdc-linear-progress__buffer{display:flex;position:absolute;top:0;bottom:0;margin:auto 0;width:100%;overflow:hidden;height:var(--mdc-linear-progress-track-height);border-radius:var(--mdc-linear-progress-track-shape, var(--mat-app-corner-none))}.mdc-linear-progress__buffer-dots{-webkit-mask-image:url("data:image/svg+xml,%3Csvg version='1.1' xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink' x='0px' y='0px' enable-background='new 0 0 5 2' xml:space='preserve' viewBox='0 0 5 2' preserveAspectRatio='xMinYMin slice'%3E%3Ccircle cx='1' cy='1' r='1'/%3E%3C/svg%3E");mask-image:url("data:image/svg+xml,%3Csvg version='1.1' xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink' x='0px' y='0px' enable-background='new 0 0 5 2' xml:space='preserve' viewBox='0 0 5 2' preserveAspectRatio='xMinYMin slice'%3E%3Ccircle cx='1' cy='1' r='1'/%3E%3C/svg%3E");background-repeat:repeat-x;flex:auto;transform:rotate(180deg);animation:mdc-linear-progress-buffering 250ms infinite linear;background-color:var(--mdc-linear-progress-track-color, var(--mat-app-surface-variant))}.cdk-high-contrast-active .mdc-linear-progress__buffer-dots{background-color:ButtonBorder}[dir=rtl] .mdc-linear-progress__buffer-dots{animation:mdc-linear-progress-buffering-reverse 250ms infinite linear;transform:rotate(0)}.mdc-linear-progress__buffer-bar{flex:0 1 100%;transition:flex-basis 250ms 0ms cubic-bezier(0.4, 0, 0.6, 1);background-color:var(--mdc-linear-progress-track-color, var(--mat-app-surface-variant))}.mdc-linear-progress__primary-bar{transform:scaleX(0)}.mdc-linear-progress--indeterminate .mdc-linear-progress__primary-bar{left:-145.166611%}.mdc-linear-progress--indeterminate.mdc-linear-progress--animation-ready .mdc-linear-progress__primary-bar{animation:mdc-linear-progress-primary-indeterminate-translate 2s infinite linear}.mdc-linear-progress--indeterminate.mdc-linear-progress--animation-ready .mdc-linear-progress__primary-bar>.mdc-linear-progress__bar-inner{animation:mdc-linear-progress-primary-indeterminate-scale 2s infinite linear}[dir=rtl] .mdc-linear-progress.mdc-linear-progress--animation-ready .mdc-linear-progress__primary-bar{animation-name:mdc-linear-progress-primary-indeterminate-translate-reverse}[dir=rtl] .mdc-linear-progress.mdc-linear-progress--indeterminate .mdc-linear-progress__primary-bar{right:-145.166611%;left:auto}.mdc-linear-progress__secondary-bar{display:none}.mdc-linear-progress--indeterminate .mdc-linear-progress__secondary-bar{left:-54.888891%;display:block}.mdc-linear-progress--indeterminate.mdc-linear-progress--animation-ready .mdc-linear-progress__secondary-bar{animation:mdc-linear-progress-secondary-indeterminate-translate 2s infinite linear}.mdc-linear-progress--indeterminate.mdc-linear-progress--animation-ready .mdc-linear-progress__secondary-bar>.mdc-linear-progress__bar-inner{animation:mdc-linear-progress-secondary-indeterminate-scale 2s infinite linear}[dir=rtl] .mdc-linear-progress.mdc-linear-progress--animation-ready .mdc-linear-progress__secondary-bar{animation-name:mdc-linear-progress-secondary-indeterminate-translate-reverse}[dir=rtl] .mdc-linear-progress.mdc-linear-progress--indeterminate .mdc-linear-progress__secondary-bar{right:-54.888891%;left:auto}@keyframes mdc-linear-progress-buffering{from{transform:rotate(180deg) translateX(calc(var(--mdc-linear-progress-track-height) * -2.5))}}@keyframes mdc-linear-progress-primary-indeterminate-translate{0%{transform:translateX(0)}20%{animation-timing-function:cubic-bezier(0.5, 0, 0.701732, 0.495819);transform:translateX(0)}59.15%{animation-timing-function:cubic-bezier(0.302435, 0.381352, 0.55, 0.956352);transform:translateX(83.67142%)}100%{transform:translateX(200.611057%)}}@keyframes mdc-linear-progress-primary-indeterminate-scale{0%{transform:scaleX(0.08)}36.65%{animation-timing-function:cubic-bezier(0.334731, 0.12482, 0.785844, 1);transform:scaleX(0.08)}69.15%{animation-timing-function:cubic-bezier(0.06, 0.11, 0.6, 1);transform:scaleX(0.661479)}100%{transform:scaleX(0.08)}}@keyframes mdc-linear-progress-secondary-indeterminate-translate{0%{animation-timing-function:cubic-bezier(0.15, 0, 0.515058, 0.409685);transform:translateX(0)}25%{animation-timing-function:cubic-bezier(0.31033, 0.284058, 0.8, 0.733712);transform:translateX(37.651913%)}48.35%{animation-timing-function:cubic-bezier(0.4, 0.627035, 0.6, 0.902026);transform:translateX(84.386165%)}100%{transform:translateX(160.277782%)}}@keyframes mdc-linear-progress-secondary-indeterminate-scale{0%{animation-timing-function:cubic-bezier(0.205028, 0.057051, 0.57661, 0.453971);transform:scaleX(0.08)}19.15%{animation-timing-function:cubic-bezier(0.152313, 0.196432, 0.648374, 1.004315);transform:scaleX(0.457104)}44.15%{animation-timing-function:cubic-bezier(0.257759, -0.003163, 0.211762, 1.38179);transform:scaleX(0.72796)}100%{transform:scaleX(0.08)}}@keyframes mdc-linear-progress-primary-indeterminate-translate-reverse{0%{transform:translateX(0)}20%{animation-timing-function:cubic-bezier(0.5, 0, 0.701732, 0.495819);transform:translateX(0)}59.15%{animation-timing-function:cubic-bezier(0.302435, 0.381352, 0.55, 0.956352);transform:translateX(-83.67142%)}100%{transform:translateX(-200.611057%)}}@keyframes mdc-linear-progress-secondary-indeterminate-translate-reverse{0%{animation-timing-function:cubic-bezier(0.15, 0, 0.515058, 0.409685);transform:translateX(0)}25%{animation-timing-function:cubic-bezier(0.31033, 0.284058, 0.8, 0.733712);transform:translateX(-37.651913%)}48.35%{animation-timing-function:cubic-bezier(0.4, 0.627035, 0.6, 0.902026);transform:translateX(-84.386165%)}100%{transform:translateX(-160.277782%)}}@keyframes mdc-linear-progress-buffering-reverse{from{transform:translateX(-10px)}}`],
            encapsulation: 2,
            changeDetection: 0
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && setClassMetadata(MatProgressBar, [{
        type: Component,
        args: [{
            selector: "mat-progress-bar",
            exportAs: "matProgressBar",
            host: {
                "role": "progressbar",
                "aria-valuemin": "0",
                "aria-valuemax": "100",
                // set tab index to -1 so screen readers will read the aria-label
                // Note: there is a known issue with JAWS that does not read progressbar aria labels on FireFox
                "tabindex": "-1",
                "[attr.aria-valuenow]": "_isIndeterminate() ? null : value",
                "[attr.mode]": "mode",
                "class": "mat-mdc-progress-bar mdc-linear-progress",
                "[class]": '"mat-" + color',
                "[class._mat-animation-noopable]": "_isNoopAnimation",
                "[class.mdc-linear-progress--animation-ready]": "!_isNoopAnimation",
                "[class.mdc-linear-progress--indeterminate]": "_isIndeterminate()"
            },
            changeDetection: ChangeDetectionStrategy.OnPush,
            encapsulation: ViewEncapsulation$1.None,
            standalone: true,
            template: `<!--
  All children need to be hidden for screen readers in order to support ChromeVox.
  More context in the issue: https://github.com/angular/components/issues/22165.
-->
<div class="mdc-linear-progress__buffer" aria-hidden="true">
  <div
    class="mdc-linear-progress__buffer-bar"
    [style.flex-basis]="_getBufferBarFlexBasis()"></div>
  <!-- Remove the dots outside of buffer mode since they can cause CSP issues (see #28938) -->
  @if (mode === 'buffer') {
    <div class="mdc-linear-progress__buffer-dots"></div>
  }
</div>
<div
  class="mdc-linear-progress__bar mdc-linear-progress__primary-bar"
  aria-hidden="true"
  [style.transform]="_getPrimaryBarTransform()">
  <span class="mdc-linear-progress__bar-inner"></span>
</div>
<div class="mdc-linear-progress__bar mdc-linear-progress__secondary-bar" aria-hidden="true">
  <span class="mdc-linear-progress__bar-inner"></span>
</div>
`,
            styles: [`.mat-mdc-progress-bar{display:block;text-align:start}.mat-mdc-progress-bar[mode=query]{transform:scaleX(-1)}.mat-mdc-progress-bar._mat-animation-noopable .mdc-linear-progress__buffer-dots,.mat-mdc-progress-bar._mat-animation-noopable .mdc-linear-progress__primary-bar,.mat-mdc-progress-bar._mat-animation-noopable .mdc-linear-progress__secondary-bar,.mat-mdc-progress-bar._mat-animation-noopable .mdc-linear-progress__bar-inner.mdc-linear-progress__bar-inner{animation:none}.mat-mdc-progress-bar._mat-animation-noopable .mdc-linear-progress__primary-bar,.mat-mdc-progress-bar._mat-animation-noopable .mdc-linear-progress__buffer-bar{transition:transform 1ms}.mdc-linear-progress{position:relative;width:100%;transform:translateZ(0);outline:1px solid rgba(0,0,0,0);overflow-x:hidden;transition:opacity 250ms 0ms cubic-bezier(0.4, 0, 0.6, 1);height:max(var(--mdc-linear-progress-track-height),var(--mdc-linear-progress-active-indicator-height))}.cdk-high-contrast-active .mdc-linear-progress{outline-color:CanvasText}.mdc-linear-progress__bar{position:absolute;top:0;bottom:0;margin:auto 0;width:100%;animation:none;transform-origin:top left;transition:transform 250ms 0ms cubic-bezier(0.4, 0, 0.6, 1);height:var(--mdc-linear-progress-active-indicator-height)}.mdc-linear-progress--indeterminate .mdc-linear-progress__bar{transition:none}[dir=rtl] .mdc-linear-progress__bar{right:0;transform-origin:center right}.mdc-linear-progress__bar-inner{display:inline-block;position:absolute;width:100%;animation:none;border-top-style:solid;border-color:var(--mdc-linear-progress-active-indicator-color, var(--mat-app-primary));border-top-width:var(--mdc-linear-progress-active-indicator-height)}.mdc-linear-progress__buffer{display:flex;position:absolute;top:0;bottom:0;margin:auto 0;width:100%;overflow:hidden;height:var(--mdc-linear-progress-track-height);border-radius:var(--mdc-linear-progress-track-shape, var(--mat-app-corner-none))}.mdc-linear-progress__buffer-dots{-webkit-mask-image:url("data:image/svg+xml,%3Csvg version='1.1' xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink' x='0px' y='0px' enable-background='new 0 0 5 2' xml:space='preserve' viewBox='0 0 5 2' preserveAspectRatio='xMinYMin slice'%3E%3Ccircle cx='1' cy='1' r='1'/%3E%3C/svg%3E");mask-image:url("data:image/svg+xml,%3Csvg version='1.1' xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink' x='0px' y='0px' enable-background='new 0 0 5 2' xml:space='preserve' viewBox='0 0 5 2' preserveAspectRatio='xMinYMin slice'%3E%3Ccircle cx='1' cy='1' r='1'/%3E%3C/svg%3E");background-repeat:repeat-x;flex:auto;transform:rotate(180deg);animation:mdc-linear-progress-buffering 250ms infinite linear;background-color:var(--mdc-linear-progress-track-color, var(--mat-app-surface-variant))}.cdk-high-contrast-active .mdc-linear-progress__buffer-dots{background-color:ButtonBorder}[dir=rtl] .mdc-linear-progress__buffer-dots{animation:mdc-linear-progress-buffering-reverse 250ms infinite linear;transform:rotate(0)}.mdc-linear-progress__buffer-bar{flex:0 1 100%;transition:flex-basis 250ms 0ms cubic-bezier(0.4, 0, 0.6, 1);background-color:var(--mdc-linear-progress-track-color, var(--mat-app-surface-variant))}.mdc-linear-progress__primary-bar{transform:scaleX(0)}.mdc-linear-progress--indeterminate .mdc-linear-progress__primary-bar{left:-145.166611%}.mdc-linear-progress--indeterminate.mdc-linear-progress--animation-ready .mdc-linear-progress__primary-bar{animation:mdc-linear-progress-primary-indeterminate-translate 2s infinite linear}.mdc-linear-progress--indeterminate.mdc-linear-progress--animation-ready .mdc-linear-progress__primary-bar>.mdc-linear-progress__bar-inner{animation:mdc-linear-progress-primary-indeterminate-scale 2s infinite linear}[dir=rtl] .mdc-linear-progress.mdc-linear-progress--animation-ready .mdc-linear-progress__primary-bar{animation-name:mdc-linear-progress-primary-indeterminate-translate-reverse}[dir=rtl] .mdc-linear-progress.mdc-linear-progress--indeterminate .mdc-linear-progress__primary-bar{right:-145.166611%;left:auto}.mdc-linear-progress__secondary-bar{display:none}.mdc-linear-progress--indeterminate .mdc-linear-progress__secondary-bar{left:-54.888891%;display:block}.mdc-linear-progress--indeterminate.mdc-linear-progress--animation-ready .mdc-linear-progress__secondary-bar{animation:mdc-linear-progress-secondary-indeterminate-translate 2s infinite linear}.mdc-linear-progress--indeterminate.mdc-linear-progress--animation-ready .mdc-linear-progress__secondary-bar>.mdc-linear-progress__bar-inner{animation:mdc-linear-progress-secondary-indeterminate-scale 2s infinite linear}[dir=rtl] .mdc-linear-progress.mdc-linear-progress--animation-ready .mdc-linear-progress__secondary-bar{animation-name:mdc-linear-progress-secondary-indeterminate-translate-reverse}[dir=rtl] .mdc-linear-progress.mdc-linear-progress--indeterminate .mdc-linear-progress__secondary-bar{right:-54.888891%;left:auto}@keyframes mdc-linear-progress-buffering{from{transform:rotate(180deg) translateX(calc(var(--mdc-linear-progress-track-height) * -2.5))}}@keyframes mdc-linear-progress-primary-indeterminate-translate{0%{transform:translateX(0)}20%{animation-timing-function:cubic-bezier(0.5, 0, 0.701732, 0.495819);transform:translateX(0)}59.15%{animation-timing-function:cubic-bezier(0.302435, 0.381352, 0.55, 0.956352);transform:translateX(83.67142%)}100%{transform:translateX(200.611057%)}}@keyframes mdc-linear-progress-primary-indeterminate-scale{0%{transform:scaleX(0.08)}36.65%{animation-timing-function:cubic-bezier(0.334731, 0.12482, 0.785844, 1);transform:scaleX(0.08)}69.15%{animation-timing-function:cubic-bezier(0.06, 0.11, 0.6, 1);transform:scaleX(0.661479)}100%{transform:scaleX(0.08)}}@keyframes mdc-linear-progress-secondary-indeterminate-translate{0%{animation-timing-function:cubic-bezier(0.15, 0, 0.515058, 0.409685);transform:translateX(0)}25%{animation-timing-function:cubic-bezier(0.31033, 0.284058, 0.8, 0.733712);transform:translateX(37.651913%)}48.35%{animation-timing-function:cubic-bezier(0.4, 0.627035, 0.6, 0.902026);transform:translateX(84.386165%)}100%{transform:translateX(160.277782%)}}@keyframes mdc-linear-progress-secondary-indeterminate-scale{0%{animation-timing-function:cubic-bezier(0.205028, 0.057051, 0.57661, 0.453971);transform:scaleX(0.08)}19.15%{animation-timing-function:cubic-bezier(0.152313, 0.196432, 0.648374, 1.004315);transform:scaleX(0.457104)}44.15%{animation-timing-function:cubic-bezier(0.257759, -0.003163, 0.211762, 1.38179);transform:scaleX(0.72796)}100%{transform:scaleX(0.08)}}@keyframes mdc-linear-progress-primary-indeterminate-translate-reverse{0%{transform:translateX(0)}20%{animation-timing-function:cubic-bezier(0.5, 0, 0.701732, 0.495819);transform:translateX(0)}59.15%{animation-timing-function:cubic-bezier(0.302435, 0.381352, 0.55, 0.956352);transform:translateX(-83.67142%)}100%{transform:translateX(-200.611057%)}}@keyframes mdc-linear-progress-secondary-indeterminate-translate-reverse{0%{animation-timing-function:cubic-bezier(0.15, 0, 0.515058, 0.409685);transform:translateX(0)}25%{animation-timing-function:cubic-bezier(0.31033, 0.284058, 0.8, 0.733712);transform:translateX(-37.651913%)}48.35%{animation-timing-function:cubic-bezier(0.4, 0.627035, 0.6, 0.902026);transform:translateX(-84.386165%)}100%{transform:translateX(-160.277782%)}}@keyframes mdc-linear-progress-buffering-reverse{from{transform:translateX(-10px)}}`]
        }]
    }], () => [{
        type: ElementRef
    }, {
        type: NgZone
    }, {
        type: ChangeDetectorRef
    }, {
        type: void 0,
        decorators: [{
            type: Optional
        }, {
            type: Inject,
            args: [ANIMATION_MODULE_TYPE]
        }]
    }, {
        type: void 0,
        decorators: [{
            type: Optional
        }, {
            type: Inject,
            args: [MAT_PROGRESS_BAR_DEFAULT_OPTIONS]
        }]
    }], {
        color: [{
            type: Input
        }],
        value: [{
            type: Input,
            args: [{
                transform: numberAttribute
            }]
        }],
        bufferValue: [{
            type: Input,
            args: [{
                transform: numberAttribute
            }]
        }],
        animationEnd: [{
            type: Output
        }],
        mode: [{
            type: Input
        }]
    });
})();

function clamp(v2, min = 0, max = 100) {
    return Math.max(min, Math.min(max, v2));
}

var MatProgressBarModule = class _MatProgressBarModule {
    static {
        this.\u0275fac = function MatProgressBarModule_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _MatProgressBarModule)();
        };
    }
    static {
        this.\u0275mod = /* @__PURE__ */ \u0275\u0275defineNgModule({
            type: _MatProgressBarModule
        });
    }
    static {
        this.\u0275inj = /* @__PURE__ */ \u0275\u0275defineInjector({
            imports: [MatCommonModule]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && setClassMetadata(MatProgressBarModule, [{
        type: NgModule,
        args: [{
            imports: [MatProgressBar],
            exports: [MatProgressBar, MatCommonModule]
        }]
    }], null, null);
})();

// src/app/modules/s3/object-upload/object-upload.component.ts
var _c02 = ["fileInput"];
var ObjectUploadComponent = class _ObjectUploadComponent {
    constructor(snackBar, dialogRef, data) {
        this.snackBar = snackBar;
        this.dialogRef = dialogRef;
        this.data = data;
        this.key = "";
        this.bucketName = "";
        this.file = {};
        this.fileName = "";
        this.uploadDisabled = true;
        this.progress = 0;
        this.fileSize = signal(0);
        this.maxSize = 256 * 1024 * 1024;
        this.selectedFile = null;
        this.uploadSuccess = false;
        this.uploadError = false;
        this.byteConversion = byteConversion;
        this.bucketName = data.bucketName;
    }

    // Method to handle file upload
    // Handler for file input change
    onFileChange(event) {
        this.file = event.target.files[0];
        this.fileName = this.file.name;
        this.key = this.file.name;
        this.uploadDisabled = !(this.file && this.key && this.fileName);
    }

    // Handler for file drop
    onFileDrop(event) {
        event.preventDefault();
        if (event.dataTransfer) {
            this.file = event.dataTransfer.files[0];
            this.fileName = this.file.name;
        }
        this.uploadDisabled = !(this.file && this.key && this.fileName);
    }

    // Prevent default dragover behavior
    onDragOver(event) {
        event.preventDefault();
    }

    // Method to handle file upload
    uploadFile(file) {
        if (file) {
            this.selectedFile = file;
            this.fileSize.set(Math.round(file.size / 1024));
            if (file.size > this.maxSize) {
                const fileSizeInMegaBytes = (file.size / 1024 / 1024).toFixed(0);
                this.snackBar.open("File size is " + fileSizeInMegaBytes + "MB. Max size is 256MB, use the AWS CLI instead.", "Error", {duration: 5e3});
                return;
            }
            const reader = new FileReader();
            reader.onload = () => {
                this.dialogRef.close({content: new Blob([reader.result]), key: this.key});
            };
            reader.addEventListener("progress", this.handleProgress);
            reader.readAsText(file);
            this.uploadSuccess = true;
            this.uploadError = false;
        }
    }

    doUpload() {
        this.uploadFile(this.file);
    }

    handleProgress(event) {
        this.progress = event.loaded / event.total * 100;
    }

    static {
        this.\u0275fac = function ObjectUploadComponent_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _ObjectUploadComponent)(\u0275\u0275directiveInject(MatSnackBar), \u0275\u0275directiveInject(MatDialogRef), \u0275\u0275directiveInject(MAT_DIALOG_DATA));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _ObjectUploadComponent,
            selectors: [["s3-object-upload"]],
            viewQuery: function ObjectUploadComponent_Query(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275viewQuery(_c02, 5);
                }
                if (rf & 2) {
                    let _t;
                    \u0275\u0275queryRefresh(_t = \u0275\u0275loadQuery()) && (ctx.fileInput = _t.first);
                }
            },
            standalone: true,
            features: [\u0275\u0275StandaloneFeature],
            decls: 25,
            vars: 8,
            consts: [["fileInput", ""], ["mat-dialog-title", ""], [1, "mat-typography", 2, "width", "500px", "height", "200px"], [1, "file-upload-wrapper", 3, "dragover", "drop"], ["accept", "application/json", "hidden", "", "type", "file", 3, "change"], [1, "file-dropper", 3, "click"], [2, "width", "100%"], ["matInput", "", "readonly", "", "value", "", 3, "ngModelChange", "ngModel"], ["matInput", "", "value", "", 3, "ngModelChange", "ngModel"], ["mode", "determinate", 3, "value"], ["align", "end"], ["mat-button", "", "mat-dialog-close", ""], ["cdkFocusInitial", "", "mat-button", "", 3, "click", "disabled"]],
            template: function ObjectUploadComponent_Template(rf, ctx) {
                if (rf & 1) {
                    const _r1 = \u0275\u0275getCurrentView();
                    \u0275\u0275elementStart(0, "h2", 1);
                    \u0275\u0275text(1, "Upload File");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(2, "mat-dialog-content", 2)(3, "div", 3);
                    \u0275\u0275listener("dragover", function ObjectUploadComponent_Template_div_dragover_3_listener($event) {
                        \u0275\u0275restoreView(_r1);
                        return \u0275\u0275resetView(ctx.onDragOver($event));
                    })("drop", function ObjectUploadComponent_Template_div_drop_3_listener($event) {
                        \u0275\u0275restoreView(_r1);
                        return \u0275\u0275resetView(ctx.onFileDrop($event));
                    });
                    \u0275\u0275elementStart(4, "input", 4, 0);
                    \u0275\u0275listener("change", function ObjectUploadComponent_Template_input_change_4_listener($event) {
                        \u0275\u0275restoreView(_r1);
                        return \u0275\u0275resetView(ctx.onFileChange($event));
                    });
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(6, "div", 5);
                    \u0275\u0275listener("click", function ObjectUploadComponent_Template_div_click_6_listener() {
                        \u0275\u0275restoreView(_r1);
                        const fileInput_r2 = \u0275\u0275reference(5);
                        return \u0275\u0275resetView(fileInput_r2.click());
                    });
                    \u0275\u0275elementStart(7, "mat-icon");
                    \u0275\u0275text(8, "upload");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(9, "p");
                    \u0275\u0275text(10, "Upload file");
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(11, "mat-form-field", 6)(12, "mat-label");
                    \u0275\u0275text(13, "File");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(14, "input", 7);
                    \u0275\u0275twoWayListener("ngModelChange", function ObjectUploadComponent_Template_input_ngModelChange_14_listener($event) {
                        \u0275\u0275restoreView(_r1);
                        \u0275\u0275twoWayBindingSet(ctx.fileName, $event) || (ctx.fileName = $event);
                        return \u0275\u0275resetView($event);
                    });
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(15, "mat-form-field", 6)(16, "mat-label");
                    \u0275\u0275text(17, "Key");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(18, "input", 8);
                    \u0275\u0275twoWayListener("ngModelChange", function ObjectUploadComponent_Template_input_ngModelChange_18_listener($event) {
                        \u0275\u0275restoreView(_r1);
                        \u0275\u0275twoWayBindingSet(ctx.key, $event) || (ctx.key = $event);
                        return \u0275\u0275resetView($event);
                    });
                    \u0275\u0275elementEnd()();
                    \u0275\u0275element(19, "mat-progress-bar", 9);
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(20, "mat-dialog-actions", 10)(21, "button", 11);
                    \u0275\u0275text(22, "Cancel");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(23, "button", 12);
                    \u0275\u0275listener("click", function ObjectUploadComponent_Template_button_click_23_listener() {
                        \u0275\u0275restoreView(_r1);
                        return \u0275\u0275resetView(ctx.doUpload());
                    });
                    \u0275\u0275text(24, "Upload");
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    \u0275\u0275advance(3);
                    \u0275\u0275classProp("error", ctx.uploadError)("success", ctx.uploadSuccess);
                    \u0275\u0275advance(11);
                    \u0275\u0275twoWayProperty("ngModel", ctx.fileName);
                    \u0275\u0275advance(4);
                    \u0275\u0275twoWayProperty("ngModel", ctx.key);
                    \u0275\u0275advance();
                    \u0275\u0275propertyInterpolate("value", ctx.progress);
                    \u0275\u0275advance(4);
                    \u0275\u0275propertyInterpolate("disabled", ctx.uploadDisabled);
                }
            },
            dependencies: [
                MatIcon,
                FormsModule,
                DefaultValueAccessor,
                NgControlStatus,
                NgModel,
                MatButton,
                MatDialogActions,
                MatDialogClose,
                MatDialogContent,
                MatDialogTitle,
                MatFormField,
                MatInput,
                MatLabel,
                MatProgressBar
            ],
            styles: ["\n\n.footer-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  width: 50%;\n  justify-content: flex-end;\n}\n.footer[_ngcontent-%COMP%] {\n  display: flex;\n  width: 50%;\n  font-size: x-small;\n  color: black;\n}\n.file-upload-wrapper[_ngcontent-%COMP%] {\n  display: flex;\n  justify-content: center;\n  align-items: center;\n  flex-direction: column;\n  border: 2px dashed #ccc;\n  padding: 1rem;\n  margin-bottom: 1rem;\n  border-radius: 10px;\n  cursor: pointer;\n}\n.file-upload-wrapper.success[_ngcontent-%COMP%] {\n  border-color: green;\n}\n.file-upload-wrapper.error[_ngcontent-%COMP%] {\n  border-color: red;\n}\n.file-dropper[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: column;\n  align-items: center;\n}\n/*# sourceMappingURL=object-upload.component.css.map */"]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(ObjectUploadComponent, {
        className: "ObjectUploadComponent",
        filePath: "src/app/modules/s3/object-upload/object-upload.component.ts",
        lineNumber: 31
    });
})();

// src/app/modules/s3/object-list/download/s3-object-download.component.ts
var import_file_saver = __toESM(require_FileSaver_min());
var S3ObjectDownloadComponent = class _S3ObjectDownloadComponent {
    constructor(snackBar, dialogRef, data) {
        this.snackBar = snackBar;
        this.dialogRef = dialogRef;
        this.data = data;
        this.body = "";
        this.fileName = "";
        this.body = data;
    }

    // Method to handle file upload
    download() {
        if (this.fileName) {
            const blob = new Blob([this.body], {type: "application/json"});
            (0, import_file_saver.saveAs)(blob, this.fileName);
            this.snackBar.open("S3 object saved to local file: " + this.fileName, "Done", {duration: 5e3});
            this.dialogRef.close(true);
        }
    }

    static {
        this.\u0275fac = function S3ObjectDownloadComponent_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _S3ObjectDownloadComponent)(\u0275\u0275directiveInject(MatSnackBar), \u0275\u0275directiveInject(MatDialogRef), \u0275\u0275directiveInject(MAT_DIALOG_DATA));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _S3ObjectDownloadComponent,
            selectors: [["export-file-download"]],
            standalone: true,
            features: [\u0275\u0275ProvidersFeature([]), \u0275\u0275StandaloneFeature],
            decls: 12,
            vars: 1,
            consts: [["mat-dialog-title", ""], [1, "mat-typography", 2, "width", "500px", "height", "200px"], [2, "width", "100%"], ["matInput", "", "value", "", 3, "ngModelChange", "ngModel"], ["align", "end"], ["mat-button", "", "mat-dialog-close", ""], ["cdkFocusInitial", "", "mat-button", "", 3, "click"]],
            template: function S3ObjectDownloadComponent_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "h2", 0);
                    \u0275\u0275text(1, "Download Object");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(2, "mat-dialog-content", 1)(3, "mat-form-field", 2)(4, "mat-label");
                    \u0275\u0275text(5, "File name");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(6, "input", 3);
                    \u0275\u0275twoWayListener("ngModelChange", function S3ObjectDownloadComponent_Template_input_ngModelChange_6_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.fileName, $event) || (ctx.fileName = $event);
                        return $event;
                    });
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(7, "mat-dialog-actions", 4)(8, "button", 5);
                    \u0275\u0275text(9, "Cancel");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(10, "button", 6);
                    \u0275\u0275listener("click", function S3ObjectDownloadComponent_Template_button_click_10_listener() {
                        return ctx.download();
                    });
                    \u0275\u0275text(11, "Download");
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    \u0275\u0275advance(6);
                    \u0275\u0275twoWayProperty("ngModel", ctx.fileName);
                }
            },
            dependencies: [
                FormsModule,
                DefaultValueAccessor,
                NgControlStatus,
                NgModel,
                MatButton,
                MatDialogActions,
                MatDialogClose,
                MatDialogContent,
                MatDialogTitle,
                MatFormField,
                MatInput,
                MatLabel
            ],
            styles: ["\n\n.queue-table[_ngcontent-%COMP%] {\n  width: 100%;\n  height: 100%;\n}\n[_nghost-%COMP%] {\n  position: relative;\n  width: 100%;\n  height: 30%;\n  margin-top: 0;\n  padding-bottom: 33%;\n}\n.head-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  justify-content: flex-end;\n}\n.footer-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  width: 50%;\n  justify-content: flex-end;\n}\n.footer[_ngcontent-%COMP%] {\n  display: flex;\n  width: 50%;\n  font-size: x-small;\n  color: black;\n}\n/*# sourceMappingURL=s3-object-download.component.css.map */"]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(S3ObjectDownloadComponent, {
        className: "S3ObjectDownloadComponent",
        filePath: "src/app/modules/s3/object-list/download/s3-object-download.component.ts",
        lineNumber: 28
    });
})();

// node_modules/xml-parser-xo/dist/esm/index.js
var ParsingError = class extends Error {
    constructor(message, cause) {
        super(message);
        this.cause = cause;
    }
};
var parsingState;

function nextChild() {
    return element(false) || text() || comment() || cdata();
}

function nextRootChild() {
    match(/\s*/);
    return element(true) || comment() || doctype() || processingInstruction(false);
}

function parseDocument() {
    const declaration = processingInstruction(true);
    const children = [];
    let documentRootNode;
    let child = nextRootChild();
    while (child) {
        if (child.node.type === "Element") {
            if (documentRootNode) {
                throw new Error("Found multiple root nodes");
            }
            documentRootNode = child.node;
        }
        if (!child.excluded) {
            children.push(child.node);
        }
        child = nextRootChild();
    }
    if (!documentRootNode) {
        throw new ParsingError("Failed to parse XML", "Root Element not found");
    }
    if (parsingState.xml.length !== 0) {
        throw new ParsingError("Failed to parse XML", "Not Well-Formed XML");
    }
    return {
        declaration: declaration ? declaration.node : null,
        root: documentRootNode,
        children
    };
}

function processingInstruction(matchDeclaration) {
    const m2 = matchDeclaration ? match(/^<\?(xml)\s*/) : match(/^<\?([\w-:.]+)\s*/);
    if (!m2) return;
    const node = {
        name: m2[1],
        type: "ProcessingInstruction",
        attributes: {}
    };
    while (!(eos() || is("?>"))) {
        const attr = attribute();
        if (attr) {
            node.attributes[attr.name] = attr.value;
        } else {
            return;
        }
    }
    match(/\?>/);
    return {
        excluded: matchDeclaration ? false : parsingState.options.filter(node) === false,
        node
    };
}

function element(matchRoot) {
    const m2 = match(/^<([^?!</>\s]+)\s*/);
    if (!m2) return;
    const node = {
        type: "Element",
        name: m2[1],
        attributes: {},
        children: []
    };
    const excluded = matchRoot ? false : parsingState.options.filter(node) === false;
    while (!(eos() || is(">") || is("?>") || is("/>"))) {
        const attr = attribute();
        if (attr) {
            node.attributes[attr.name] = attr.value;
        } else {
            return;
        }
    }
    if (match(/^\s*\/>/)) {
        node.children = null;
        return {
            excluded,
            node
        };
    }
    match(/\??>/);
    let child = nextChild();
    while (child) {
        if (!child.excluded) {
            node.children.push(child.node);
        }
        child = nextChild();
    }
    if (parsingState.options.strictMode) {
        const closingTag = `</${node.name}>`;
        if (parsingState.xml.startsWith(closingTag)) {
            parsingState.xml = parsingState.xml.slice(closingTag.length);
        } else {
            throw new ParsingError("Failed to parse XML", `Closing tag not matching "${closingTag}"`);
        }
    } else {
        match(/^<\/[\w-:.\u00C0-\u00FF]+\s*>/);
    }
    return {
        excluded,
        node
    };
}

function doctype() {
    const m2 = match(/^<!DOCTYPE\s+\S+\s+SYSTEM[^>]*>/) || match(/^<!DOCTYPE\s+\S+\s+PUBLIC[^>]*>/) || match(/^<!DOCTYPE\s+\S+\s*\[[^\]]*]>/) || match(/^<!DOCTYPE\s+\S+\s*>/);
    if (m2) {
        const node = {
            type: "DocumentType",
            content: m2[0]
        };
        return {
            excluded: parsingState.options.filter(node) === false,
            node
        };
    }
}

function cdata() {
    if (parsingState.xml.startsWith("<![CDATA[")) {
        const endPositionStart = parsingState.xml.indexOf("]]>");
        if (endPositionStart > -1) {
            const endPositionFinish = endPositionStart + 3;
            const node = {
                type: "CDATA",
                content: parsingState.xml.substring(0, endPositionFinish)
            };
            parsingState.xml = parsingState.xml.slice(endPositionFinish);
            return {
                excluded: parsingState.options.filter(node) === false,
                node
            };
        }
    }
}

function comment() {
    const m2 = match(/^<!--[\s\S]*?-->/);
    if (m2) {
        const node = {
            type: "Comment",
            content: m2[0]
        };
        return {
            excluded: parsingState.options.filter(node) === false,
            node
        };
    }
}

function text() {
    const m2 = match(/^([^<]+)/);
    if (m2) {
        const node = {
            type: "Text",
            content: m2[1]
        };
        return {
            excluded: parsingState.options.filter(node) === false,
            node
        };
    }
}

function attribute() {
    const m2 = match(/([^=]+)\s*=\s*("[^"]*"|'[^']*'|[^>\s]+)\s*/);
    if (m2) {
        return {
            name: m2[1].trim(),
            value: stripQuotes(m2[2].trim())
        };
    }
}

function stripQuotes(val) {
    return val.replace(/^['"]|['"]$/g, "");
}

function match(re) {
    const m2 = parsingState.xml.match(re);
    if (m2) {
        parsingState.xml = parsingState.xml.slice(m2[0].length);
        return m2;
    }
}

function eos() {
    return 0 === parsingState.xml.length;
}

function is(prefix) {
    return 0 === parsingState.xml.indexOf(prefix);
}

function parseXml(xml, options = {}) {
    xml = xml.trim();
    const filter2 = options.filter || (() => true);
    parsingState = {
        xml,
        options: Object.assign(Object.assign({}, options), {
            filter: filter2,
            strictMode: options.strictMode === true
        })
    };
    return parseDocument();
}

if (typeof module !== "undefined" && typeof exports === "object") {
    module.exports = parseXml;
}
var esm_default = parseXml;

// node_modules/xml-formatter/dist/esm/index.js
function newLine(state) {
    if (!state.options.indentation && !state.options.lineSeparator) return;
    state.content += state.options.lineSeparator;
    let i2;
    for (i2 = 0; i2 < state.level; i2++) {
        state.content += state.options.indentation;
    }
}

function indent(state) {
    state.content = state.content.replace(/ +$/, "");
    let i2;
    for (i2 = 0; i2 < state.level; i2++) {
        state.content += state.options.indentation;
    }
}

function appendContent(state, content) {
    state.content += content;
}

function processNode(node, state, preserveSpace) {
    if (typeof node.content === "string") {
        processContent(node.content, state, preserveSpace);
    } else if (node.type === "Element") {
        processElementNode(node, state, preserveSpace);
    } else if (node.type === "ProcessingInstruction") {
        processProcessingIntruction(node, state);
    } else {
        throw new Error("Unknown node type: " + node.type);
    }
}

function processContent(content, state, preserveSpace) {
    if (!preserveSpace) {
        const trimmedContent = content.trim();
        if (state.options.lineSeparator) {
            content = trimmedContent;
        } else if (trimmedContent.length === 0) {
            content = trimmedContent;
        }
    }
    if (content.length > 0) {
        if (!preserveSpace && state.content.length > 0) {
            newLine(state);
        }
        appendContent(state, content);
    }
}

function isPathMatchingIgnoredPaths(path, ignoredPaths) {
    const fullPath = "/" + path.join("/");
    const pathLastPart = path[path.length - 1];
    return ignoredPaths.includes(pathLastPart) || ignoredPaths.includes(fullPath);
}

function processElementNode(node, state, preserveSpace) {
    state.path.push(node.name);
    if (!preserveSpace && state.content.length > 0) {
        newLine(state);
    }
    appendContent(state, "<" + node.name);
    processAttributes(state, node.attributes);
    if (node.children === null || state.options.forceSelfClosingEmptyTag && node.children.length === 0) {
        const selfClosingNodeClosingTag = state.options.whiteSpaceAtEndOfSelfclosingTag ? " />" : "/>";
        appendContent(state, selfClosingNodeClosingTag);
    } else if (node.children.length === 0) {
        appendContent(state, "></" + node.name + ">");
    } else {
        const nodeChildren = node.children;
        appendContent(state, ">");
        state.level++;
        let nodePreserveSpace = node.attributes["xml:space"] === "preserve";
        let ignoredPath = false;
        if (!nodePreserveSpace && state.options.ignoredPaths) {
            ignoredPath = isPathMatchingIgnoredPaths(state.path, state.options.ignoredPaths);
            nodePreserveSpace = ignoredPath;
        }
        if (!nodePreserveSpace && state.options.collapseContent) {
            let containsTextNodes = false;
            let containsTextNodesWithLineBreaks = false;
            let containsNonTextNodes = false;
            nodeChildren.forEach(function (child, index) {
                if (child.type === "Text") {
                    if (child.content.includes("\n")) {
                        containsTextNodesWithLineBreaks = true;
                        child.content = child.content.trim();
                    } else if ((index === 0 || index === nodeChildren.length - 1) && !preserveSpace) {
                        if (child.content.trim().length === 0) {
                            child.content = "";
                        }
                    }
                    if (child.content.trim().length > 0) {
                        containsTextNodes = true;
                    }
                } else if (child.type === "CDATA") {
                    containsTextNodes = true;
                } else {
                    containsNonTextNodes = true;
                }
            });
            if (containsTextNodes && (!containsNonTextNodes || !containsTextNodesWithLineBreaks)) {
                nodePreserveSpace = true;
            }
        }
        nodeChildren.forEach(function (child) {
            processNode(child, state, preserveSpace || nodePreserveSpace);
        });
        state.level--;
        if (!preserveSpace && !nodePreserveSpace) {
            newLine(state);
        }
        if (ignoredPath) {
            indent(state);
        }
        appendContent(state, "</" + node.name + ">");
    }
    state.path.pop();
}

function processAttributes(state, attributes) {
    Object.keys(attributes).forEach(function (attr) {
        const escaped = attributes[attr].replace(/"/g, "&quot;");
        appendContent(state, " " + attr + '="' + escaped + '"');
    });
}

function processProcessingIntruction(node, state) {
    if (state.content.length > 0) {
        newLine(state);
    }
    appendContent(state, "<?" + node.name);
    processAttributes(state, node.attributes);
    appendContent(state, "?>");
}

function formatXml(xml, options = {}) {
    options.indentation = "indentation" in options ? options.indentation : "    ";
    options.collapseContent = options.collapseContent === true;
    options.lineSeparator = "lineSeparator" in options ? options.lineSeparator : "\r\n";
    options.whiteSpaceAtEndOfSelfclosingTag = options.whiteSpaceAtEndOfSelfclosingTag === true;
    options.throwOnFailure = options.throwOnFailure !== false;
    try {
        const parsedXml = esm_default(xml, {
            filter: options.filter,
            strictMode: options.strictMode
        });
        const state = {
            content: "",
            level: 0,
            options,
            path: []
        };
        if (parsedXml.declaration) {
            processProcessingIntruction(parsedXml.declaration, state);
        }
        parsedXml.children.forEach(function (child) {
            processNode(child, state, false);
        });
        if (!options.lineSeparator) {
            return state.content;
        }
        return state.content.replace(/\r\n/g, "\n").replace(/\n/g, options.lineSeparator);
    } catch (err) {
        if (options.throwOnFailure) {
            throw err;
        }
        return xml;
    }
}

formatXml.minify = (xml, options = {}) => {
    return formatXml(xml, Object.assign(Object.assign({}, options), {
        indentation: "",
        lineSeparator: ""
    }));
};
if (typeof module !== "undefined" && typeof exports === "object") {
    module.exports = formatXml;
}
var esm_default2 = formatXml;

// src/app/modules/s3/object-list/view/object-view.component.ts
var S3ObjectViewDialog = class _S3ObjectViewDialog {
    constructor(dialogRef, data, s3Service) {
        this.dialogRef = dialogRef;
        this.data = data;
        this.s3Service = s3Service;
        this.bucketName = "";
        this.key = "";
        this.body = "";
        this.contentType = "";
        this.prettyPrint = true;
        this.transformedBody = "";
        this.bucketName = data.bucketName;
        this.key = data.key;
        this.contentType = data.contentType;
        this.s3Service.getObject(this.bucketName, this.key).then((data2) => {
            data2.Body?.transformToString().then((data3) => {
                this.body = data3;
                if (this.prettyPrint) {
                    this.transformedBody = this.transform(this.body);
                }
            });
        });
    }

    changePrettyPrint(event) {
        if (this.body !== void 0) {
            if (event.checked) {
                this.transformedBody = this.transform(this.body);
            } else {
                this.transformedBody = this.body;
            }
        }
    }

    transform(body) {
        if (this.isJson()) {
            return JSON.stringify(JSON.parse(body), null, 2);
        } else if (this.isXml()) {
            return esm_default2(body);
        }
        return body;
    }

    isJson() {
        return this.contentType === "application/json" || this.contentType.startsWith("text/plain");
    }

    isXml() {
        return this.contentType === "application/xml";
    }

    static {
        this.\u0275fac = function S3ObjectViewDialog_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _S3ObjectViewDialog)(\u0275\u0275directiveInject(MatDialogRef), \u0275\u0275directiveInject(MAT_DIALOG_DATA), \u0275\u0275directiveInject(S3Service));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _S3ObjectViewDialog,
            selectors: [["s3-object-view"]],
            standalone: true,
            features: [\u0275\u0275ProvidersFeature([S3Service]), \u0275\u0275StandaloneFeature],
            decls: 13,
            vars: 3,
            consts: [["cdkDrag", "", "cdkDragHandle", "", "cdkDragRootElement", ".cdk-overlay-pane", "mat-dialog-title", ""], ["labelPosition", "before", 3, "change", "checked"], [1, "mat-typography"], [2, "width", "100%", "height", "100%"], ["cdkAutosizeMinRows", "70", "cdkTextareaAutosize", "", "matInput", "", "placeholder", "Invalid object", "readonly", "", 2, "width", "100%", "height", "100%", 3, "ngModelChange", "ngModel"], ["align", "end"], ["mat-button", "", "mat-dialog-close", ""]],
            template: function S3ObjectViewDialog_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "h2", 0);
                    \u0275\u0275text(1);
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(2, "mat-dialog-actions")(3, "mat-slide-toggle", 1);
                    \u0275\u0275listener("change", function S3ObjectViewDialog_Template_mat_slide_toggle_change_3_listener($event) {
                        return ctx.changePrettyPrint($event);
                    });
                    \u0275\u0275text(4, " Pretty Print: ");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(5, "mat-dialog-content", 2)(6, "mat-form-field", 3)(7, "mat-label");
                    \u0275\u0275text(8, "Object");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(9, "textarea", 4);
                    \u0275\u0275twoWayListener("ngModelChange", function S3ObjectViewDialog_Template_textarea_ngModelChange_9_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.transformedBody, $event) || (ctx.transformedBody = $event);
                        return $event;
                    });
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(10, "mat-dialog-actions", 5)(11, "button", 6);
                    \u0275\u0275text(12, "Close");
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    \u0275\u0275advance();
                    \u0275\u0275textInterpolate1("S3 Object: ", ctx.key, "");
                    \u0275\u0275advance(2);
                    \u0275\u0275property("checked", ctx.prettyPrint);
                    \u0275\u0275advance(6);
                    \u0275\u0275twoWayProperty("ngModel", ctx.transformedBody);
                }
            },
            dependencies: [
                CdkDrag,
                CdkDragHandle,
                CdkTextareaAutosize,
                MatButton,
                MatDialogActions,
                MatDialogClose,
                MatDialogContent,
                MatDialogTitle,
                MatFormField,
                MatInput,
                MatLabel,
                ReactiveFormsModule,
                DefaultValueAccessor,
                NgControlStatus,
                FormsModule,
                NgModel,
                MatSlideToggle
            ],
            styles: ["\n\n.fill-remaining-space[_ngcontent-%COMP%] {\n  flex: 1 1 auto;\n}\n.table-container[_ngcontent-%COMP%] {\n  max-height: calc(100vh - 10px);\n  overflow: auto;\n}\n.footer[_ngcontent-%COMP%] {\n  display: flex;\n  width: 50%;\n  font-size: x-small;\n  color: black;\n  padding-top: 15px;\n  padding-left: 15px;\n}\n/*# sourceMappingURL=object-view.component.css.map */"]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(S3ObjectViewDialog, {
        className: "S3ObjectViewDialog",
        filePath: "src/app/modules/s3/object-list/view/object-view.component.ts",
        lineNumber: 37
    });
})();

// src/app/modules/s3/object-list/object-list.component.ts
var _c03 = () => [];

function S3ObjectListComponent_button_21_Template(rf, ctx) {
    if (rf & 1) {
        const _r1 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "button", 13);
        \u0275\u0275listener("click", function S3ObjectListComponent_button_21_Template_button_click_0_listener() {
            \u0275\u0275restoreView(_r1);
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.setPrefix());
        });
        \u0275\u0275elementStart(1, "mat-icon", 14);
        \u0275\u0275text(2, "search");
        \u0275\u0275elementEnd()();
    }
}

function S3ObjectListComponent_button_22_Template(rf, ctx) {
    if (rf & 1) {
        const _r3 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "button", 13);
        \u0275\u0275listener("click", function S3ObjectListComponent_button_22_Template_button_click_0_listener() {
            \u0275\u0275restoreView(_r3);
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.unsetPrefix());
        });
        \u0275\u0275elementStart(1, "mat-icon", 14);
        \u0275\u0275text(2, "close");
        \u0275\u0275elementEnd()();
    }
}

function S3ObjectListComponent_div_24_th_3_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 33);
        \u0275\u0275text(1, "Name");
        \u0275\u0275elementEnd();
    }
}

function S3ObjectListComponent_div_24_td_4_Template(rf, ctx) {
    if (rf & 1) {
        const _r5 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "td", 34)(1, "mat-nav-list")(2, "a", 35);
        \u0275\u0275listener("click", function S3ObjectListComponent_div_24_td_4_Template_a_click_2_listener() {
            const element_r6 = \u0275\u0275restoreView(_r5).$implicit;
            const ctx_r1 = \u0275\u0275nextContext(2);
            return \u0275\u0275resetView(ctx_r1.viewObject(element_r6));
        });
        \u0275\u0275text(3);
        \u0275\u0275elementEnd()()();
    }
    if (rf & 2) {
        const element_r6 = ctx.$implicit;
        \u0275\u0275advance(3);
        \u0275\u0275textInterpolate1(" ", element_r6.key, "");
    }
}

function S3ObjectListComponent_div_24_th_6_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 36);
        \u0275\u0275text(1, " Content-Type ");
        \u0275\u0275elementEnd();
    }
}

function S3ObjectListComponent_div_24_td_7_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 34);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r7 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r7.contentType, "");
    }
}

function S3ObjectListComponent_div_24_th_9_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 37);
        \u0275\u0275text(1, "Size");
        \u0275\u0275elementEnd();
    }
}

function S3ObjectListComponent_div_24_td_10_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 34);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r8 = ctx.$implicit;
        const ctx_r1 = \u0275\u0275nextContext(2);
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", ctx_r1.byteConversion(element_r8.size), "");
    }
}

function S3ObjectListComponent_div_24_th_12_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 38);
        \u0275\u0275text(1, "Created");
        \u0275\u0275elementEnd();
    }
}

function S3ObjectListComponent_div_24_td_13_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 34);
        \u0275\u0275text(1);
        \u0275\u0275pipe(2, "date");
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r9 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", \u0275\u0275pipeBind2(2, 1, element_r9.created, "dd-MM-yyyy hh:mm:ss"), "");
    }
}

function S3ObjectListComponent_div_24_th_15_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 39);
        \u0275\u0275text(1, "Modified");
        \u0275\u0275elementEnd();
    }
}

function S3ObjectListComponent_div_24_td_16_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 34);
        \u0275\u0275text(1);
        \u0275\u0275pipe(2, "date");
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r10 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", \u0275\u0275pipeBind2(2, 1, element_r10.modified, "dd-MM-yyyy hh:mm:ss"), "");
    }
}

function S3ObjectListComponent_div_24_th_18_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 40);
        \u0275\u0275text(1, "Actions");
        \u0275\u0275elementEnd();
    }
}

function S3ObjectListComponent_div_24_td_19_Template(rf, ctx) {
    if (rf & 1) {
        const _r11 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "td", 34)(1, "button", 41);
        \u0275\u0275listener("click", function S3ObjectListComponent_div_24_td_19_Template_button_click_1_listener() {
            const row_r12 = \u0275\u0275restoreView(_r11).$implicit;
            const ctx_r1 = \u0275\u0275nextContext(2);
            return \u0275\u0275resetView(ctx_r1.downloadObject(row_r12.bucketName, row_r12.key));
        });
        \u0275\u0275elementStart(2, "mat-icon");
        \u0275\u0275text(3, "download");
        \u0275\u0275elementEnd()();
        \u0275\u0275elementStart(4, "button", 42);
        \u0275\u0275listener("click", function S3ObjectListComponent_div_24_td_19_Template_button_click_4_listener() {
            const row_r12 = \u0275\u0275restoreView(_r11).$implicit;
            const ctx_r1 = \u0275\u0275nextContext(2);
            return \u0275\u0275resetView(ctx_r1.deleteObject(row_r12.key));
        });
        \u0275\u0275elementStart(5, "mat-icon");
        \u0275\u0275text(6, "delete");
        \u0275\u0275elementEnd()()();
    }
}

function S3ObjectListComponent_div_24_tr_20_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 43);
    }
}

function S3ObjectListComponent_div_24_tr_21_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 44);
    }
}

function S3ObjectListComponent_div_24_tr_22_Template(rf, ctx) {
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

function S3ObjectListComponent_div_24_Template(rf, ctx) {
    if (rf & 1) {
        const _r4 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "div", 15)(1, "table", 16);
        \u0275\u0275listener("matSortChange", function S3ObjectListComponent_div_24_Template_table_matSortChange_1_listener($event) {
            \u0275\u0275restoreView(_r4);
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.sortChange($event));
        });
        \u0275\u0275elementContainerStart(2, 17);
        \u0275\u0275template(3, S3ObjectListComponent_div_24_th_3_Template, 2, 0, "th", 18)(4, S3ObjectListComponent_div_24_td_4_Template, 4, 1, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(5, 20);
        \u0275\u0275template(6, S3ObjectListComponent_div_24_th_6_Template, 2, 0, "th", 21)(7, S3ObjectListComponent_div_24_td_7_Template, 2, 1, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(8, 22);
        \u0275\u0275template(9, S3ObjectListComponent_div_24_th_9_Template, 2, 0, "th", 23)(10, S3ObjectListComponent_div_24_td_10_Template, 2, 1, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(11, 24);
        \u0275\u0275template(12, S3ObjectListComponent_div_24_th_12_Template, 2, 0, "th", 25)(13, S3ObjectListComponent_div_24_td_13_Template, 3, 4, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(14, 26);
        \u0275\u0275template(15, S3ObjectListComponent_div_24_th_15_Template, 2, 0, "th", 27)(16, S3ObjectListComponent_div_24_td_16_Template, 3, 4, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(17, 28);
        \u0275\u0275template(18, S3ObjectListComponent_div_24_th_18_Template, 2, 0, "th", 29)(19, S3ObjectListComponent_div_24_td_19_Template, 7, 0, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275template(20, S3ObjectListComponent_div_24_tr_20_Template, 1, 0, "tr", 30)(21, S3ObjectListComponent_div_24_tr_21_Template, 1, 0, "tr", 31)(22, S3ObjectListComponent_div_24_tr_22_Template, 3, 1, "tr", 32);
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const objectCounters_r13 = ctx.ngIf;
        const ctx_r1 = \u0275\u0275nextContext();
        \u0275\u0275advance();
        \u0275\u0275property("dataSource", objectCounters_r13.objectCounters);
        \u0275\u0275advance(19);
        \u0275\u0275property("matHeaderRowDef", ctx_r1.columns);
        \u0275\u0275advance();
        \u0275\u0275property("matRowDefColumns", ctx_r1.columns);
    }
}

var S3ObjectListComponent = class _S3ObjectListComponent {
    constructor(snackBar, dialog, route, state, store, actionsSubj$, location, s3Service) {
        this.snackBar = snackBar;
        this.dialog = dialog;
        this.route = route;
        this.state = state;
        this.store = store;
        this.actionsSubj$ = actionsSubj$;
        this.location = location;
        this.s3Service = s3Service;
        this.lastUpdate = /* @__PURE__ */ new Date();
        this.bucketName = "";
        this.pageSize$ = this.store.select(selectPageSize);
        this.pageIndex$ = this.store.select(selectPageIndex);
        this.s3ObjectCountersResponse$ = this.store.select(selectObjectCounters);
        this.prefixValue = "";
        this.prefixSet = false;
        this.columns = ["key", "contentType", "size", "created", "modified", "actions"];
        this.pageSizeOptions = [5, 10, 20, 50, 100];
        this.hidePageSize = false;
        this.showPageSizeOptions = true;
        this.showFirstLastButtons = true;
        this.disabled = false;
        this.sortColumns = [];
        this.byteConversion = byteConversion;
        this.actionsSubj$.pipe(filter((action) => action.type === s3ObjectListActions.deleteObjectSuccess.type)).subscribe(() => {
            this.loadObjects();
        });
        this.s3ObjectCountersResponse$.subscribe((data) => {
            console.log(data);
        });
    }

    ngOnInit() {
        this.routerSubscription = this.route.params.subscribe((params) => {
            this.bucketName = decodeURI(params["bucketName"]);
            this.state.value.bucketName = decodeURI(params["bucketName"]);
        });
        this.updateSubscription = interval(6e4).subscribe(() => this.loadObjects());
        this.loadObjects();
    }

    ngOnDestroy() {
        this.updateSubscription?.unsubscribe();
    }

    ngAfterViewInit() {
        this.objectData.sort = this.sort;
    }

    setPrefix() {
        this.prefixSet = true;
        this.state.value["s3-object-list"].prefix = this.prefixValue;
        this.loadObjects();
    }

    unsetPrefix() {
        this.prefixValue = "";
        this.prefixSet = false;
        this.state.value["s3-object-list"].prefix = "";
        this.loadObjects();
    }

    back() {
        this.location.back();
    }

    refresh() {
        this.loadObjects();
    }

    handlePageEvent(e2) {
        this.state.value["s3-object-list"].pageSize = e2.pageSize;
        this.state.value["s3-object-list"].pageIndex = e2.pageIndex;
        this.store.dispatch(s3ObjectListActions.loadObjects({
            bucketName: this.bucketName,
            prefix: this.state.value["s3-object-list"].prefix,
            pageSize: this.state.value["s3-object-list"].pageSize,
            pageIndex: this.state.value["s3-object-list"].pageIndex,
            sortColumns: this.state.value["s3-object-list"].sortColumns
        }));
    }

    sortChange(sortState) {
        this.sortColumns = [];
        if (sortState.direction === "asc") {
            this.sortColumns.push({column: sortState.active, sortDirection: 1});
        } else {
            this.sortColumns.push({column: sortState.active, sortDirection: -1});
        }
        this.state.value["s3-object-list"].sortColumns = this.sortColumns;
        this.loadObjects();
    }

    loadObjects() {
        this.lastUpdate = /* @__PURE__ */ new Date();
        this.store.dispatch(s3ObjectListActions.loadObjects({
            bucketName: this.bucketName,
            prefix: this.state.value["s3-object-list"].prefix,
            pageSize: this.state.value["s3-object-list"].pageSize,
            pageIndex: this.state.value["s3-object-list"].pageIndex,
            sortColumns: this.state.value["s3-object-list"].sortColumns
        }));
    }

    downloadObject(bucketName, key) {
        const dialogConfig = new MatDialogConfig();
        dialogConfig.disableClose = true;
        dialogConfig.autoFocus = true;
        dialogConfig.data = {bucketName, key};
        dialogConfig.height = "430px";
        this.dialog.open(S3ObjectDownloadComponent, dialogConfig).afterClosed().subscribe((result) => {
            if (result) {
                this.snackBar.open("Object downloaded, bucket: " + this.bucketName + " key: " + result.key, "Done", {duration: 5e3});
                this.doUpload(result.content, result.key);
            }
        });
    }

    deleteObject(key) {
        this.store.dispatch(s3ObjectListActions.deleteObject({
            bucketName: this.bucketName,
            key
        }));
    }

    uploadObject() {
        const dialogConfig = new MatDialogConfig();
        dialogConfig.disableClose = true;
        dialogConfig.autoFocus = true;
        dialogConfig.data = {bucketName: this.bucketName};
        dialogConfig.height = "430px";
        this.dialog.open(ObjectUploadComponent, dialogConfig).afterClosed().subscribe((result) => {
            if (result) {
                this.snackBar.open("Object uploaded, bucket: " + this.bucketName + " key: " + result.key, "Done", {duration: 5e3});
                this.doUpload(result.content, result.key);
            }
        });
    }

    viewObject(object) {
        if (object !== void 0) {
            if (object.size !== void 0 && object.size > 1024 * 1024) {
                this.snackBar.open("Object to big, maxSize: 1MB", "Error", {duration: 5e3});
                return;
            }
            if (object.contentType !== void 0 && !this.hasAllowedContentType(object.contentType)) {
                this.snackBar.open("Invalid content type: " + object.contentType, "Error", {duration: 5e3});
                return;
            }
            const dialogConfig = new MatDialogConfig();
            dialogConfig.disableClose = true;
            dialogConfig.autoFocus = true;
            dialogConfig.maxWidth = "100vw";
            dialogConfig.maxHeight = "100vh";
            dialogConfig.panelClass = "full-screen-modal";
            dialogConfig.width = "80%";
            dialogConfig.minWidth = "280px";
            dialogConfig.data = {bucketName: this.bucketName, key: object.key, contentType: object.contentType};
            this.dialog.open(S3ObjectViewDialog, dialogConfig).afterClosed().subscribe((result) => {
            });
        }
    }

    // Method to handle file upload
    doUpload(content, key) {
        this.s3Service.putObjects(this.bucketName, key, content).then(() => this.loadObjects());
    }

    hasAllowedContentType(contentType) {
        return contentType === "application/xml" || contentType === "application/json" || contentType === "text/html" || contentType.startsWith("text/plain");
    }

    static {
        this.\u0275fac = function S3ObjectListComponent_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _S3ObjectListComponent)(\u0275\u0275directiveInject(MatSnackBar), \u0275\u0275directiveInject(MatDialog), \u0275\u0275directiveInject(ActivatedRoute), \u0275\u0275directiveInject(State), \u0275\u0275directiveInject(Store), \u0275\u0275directiveInject(ActionsSubject), \u0275\u0275directiveInject(Location), \u0275\u0275directiveInject(S3Service));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _S3ObjectListComponent,
            selectors: [["s3-object-list"]],
            features: [\u0275\u0275ProvidersFeature([S3Service, AwsMockHttpService])],
            decls: 33,
            vars: 25,
            consts: [["appearance", "outlined", 2, "margin", "3px"], ["aria-label", "Back", "mat-icon-button", "", 1, "head-buttons-left", 3, "click"], [1, "fill-remaining-space"], ["aria-label", "Refresh", "mat-icon-button", "", 3, "click"], ["appearance", "outlined", 2, "margin", "-10px"], [1, "head-buttons"], [2, "width", "100%"], ["matInput", "", "name", "search", "placeholder", "Search", "type", "text", 3, "ngModelChange", "ngModel"], ["mat-icon-button", "", "matSuffix", "", "style", "float: right", 3, "click", 4, "ngIf"], [1, "table-container"], ["class", "row", 4, "ngIf"], ["aria-label", "Select page", 2, "width", "99%", "margin-left", "15px", 3, "page", "disabled", "hidePageSize", "length", "pageIndex", "pageSizeOptions", "pageSize", "showFirstLastButtons"], [1, "footer"], ["mat-icon-button", "", "matSuffix", "", 2, "float", "right", 3, "click"], ["matSuffix", ""], [1, "row"], ["mat-table", "", "matSort", "", 1, "mat-elevation-z8", "queue-table", 3, "matSortChange", "dataSource"], ["matColumnDef", "key", "matTooltip", "Object key"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Object key", "sortActionDescription", "Sort by key", 4, "matHeaderCellDef"], ["mat-cell", "", 4, "matCellDef"], ["matColumnDef", "contentType", "matTooltip", "Object content type"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Object content type", "sortActionDescription", "Sort by contentType", 4, "matHeaderCellDef"], ["matColumnDef", "size", "matTooltip", "Object size in bytes"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Object size", "sortActionDescription", "Sort by key", 4, "matHeaderCellDef"], ["matColumnDef", "created", "matTooltip", "Created"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Create timestamp", "sortActionDescription", "Sort by created", 4, "matHeaderCellDef"], ["matColumnDef", "modified", "matTooltip", "Modified"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Modified timestamp", "sortActionDescription", "Sort by modified", 4, "matHeaderCellDef"], ["matColumnDef", "actions"], ["mat-header-cell", "", "style", "width:160px", 4, "matHeaderCellDef"], ["mat-header-row", "", 4, "matHeaderRowDef"], ["mat-row", "", 4, "matRowDef", "matRowDefColumns"], ["class", "mat-row", 4, "matNoDataRow"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Object key", "sortActionDescription", "Sort by key"], ["mat-cell", ""], ["mat-list-item", "", 3, "click"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Object content type", "sortActionDescription", "Sort by contentType"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Object size", "sortActionDescription", "Sort by key"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Create timestamp", "sortActionDescription", "Sort by created"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Modified timestamp", "sortActionDescription", "Sort by modified"], ["mat-header-cell", "", 2, "width", "160px"], ["aria-label", "List", "mat-icon-button", "", "matTooltip", "Lists all objects", 3, "click"], ["aria-label", "DeleteObject", "mat-icon-button", "", "matTooltip", "Delete object", 3, "click"], ["mat-header-row", ""], ["mat-row", ""], [1, "mat-row"], [1, "mat-cell", 2, "padding-left", "20px", "padding-top", "10px"]],
            template: function S3ObjectListComponent_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "mat-card", 0)(1, "mat-card-header")(2, "button", 1);
                    \u0275\u0275listener("click", function S3ObjectListComponent_Template_button_click_2_listener() {
                        return ctx.back();
                    });
                    \u0275\u0275elementStart(3, "mat-icon");
                    \u0275\u0275text(4, "arrow_back");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(5, "span", 2)(6, "h4");
                    \u0275\u0275text(7);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(8, "button", 3);
                    \u0275\u0275listener("click", function S3ObjectListComponent_Template_button_click_8_listener() {
                        return ctx.uploadObject();
                    });
                    \u0275\u0275elementStart(9, "mat-icon");
                    \u0275\u0275text(10, "upload");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(11, "button", 3);
                    \u0275\u0275listener("click", function S3ObjectListComponent_Template_button_click_11_listener() {
                        return ctx.refresh();
                    });
                    \u0275\u0275elementStart(12, "mat-icon");
                    \u0275\u0275text(13, "refresh");
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(14, "mat-card-content")(15, "mat-card", 4)(16, "mat-card-actions", 5)(17, "mat-form-field", 6)(18, "mat-label");
                    \u0275\u0275text(19, "Prefix");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(20, "input", 7);
                    \u0275\u0275twoWayListener("ngModelChange", function S3ObjectListComponent_Template_input_ngModelChange_20_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.prefixValue, $event) || (ctx.prefixValue = $event);
                        return $event;
                    });
                    \u0275\u0275elementEnd();
                    \u0275\u0275template(21, S3ObjectListComponent_button_21_Template, 3, 0, "button", 8)(22, S3ObjectListComponent_button_22_Template, 3, 0, "button", 8);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(23, "div", 9);
                    \u0275\u0275template(24, S3ObjectListComponent_div_24_Template, 23, 3, "div", 10);
                    \u0275\u0275pipe(25, "async");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(26, "mat-paginator", 11);
                    \u0275\u0275pipe(27, "async");
                    \u0275\u0275pipe(28, "async");
                    \u0275\u0275pipe(29, "async");
                    \u0275\u0275listener("page", function S3ObjectListComponent_Template_mat_paginator_page_26_listener($event) {
                        return ctx.handlePageEvent($event);
                    });
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(30, "div", 12);
                    \u0275\u0275text(31);
                    \u0275\u0275pipe(32, "date");
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    let tmp_7_0;
                    \u0275\u0275advance(7);
                    \u0275\u0275textInterpolate1("S3 Objects: ", ctx.bucketName, "");
                    \u0275\u0275advance(13);
                    \u0275\u0275twoWayProperty("ngModel", ctx.prefixValue);
                    \u0275\u0275advance();
                    \u0275\u0275property("ngIf", !ctx.prefixSet);
                    \u0275\u0275advance();
                    \u0275\u0275property("ngIf", ctx.prefixSet);
                    \u0275\u0275advance(2);
                    \u0275\u0275property("ngIf", \u0275\u0275pipeBind1(25, 13, ctx.s3ObjectCountersResponse$));
                    \u0275\u0275advance(2);
                    \u0275\u0275property("disabled", ctx.disabled)("hidePageSize", ctx.hidePageSize)("length", (tmp_7_0 = \u0275\u0275pipeBind1(27, 15, ctx.s3ObjectCountersResponse$)) == null ? null : tmp_7_0.total)("pageIndex", \u0275\u0275pipeBind1(28, 17, ctx.pageIndex$))("pageSizeOptions", ctx.showPageSizeOptions ? ctx.pageSizeOptions : \u0275\u0275pureFunction0(24, _c03))("pageSize", \u0275\u0275pipeBind1(29, 19, ctx.pageSize$))("showFirstLastButtons", ctx.showFirstLastButtons);
                    \u0275\u0275advance(5);
                    \u0275\u0275textInterpolate1(" Last update: ", \u0275\u0275pipeBind2(32, 21, ctx.lastUpdate, "HH:mm:ss"), " ");
                }
            },
            dependencies: [MatCard, MatCardHeader, MatCardContent, MatCardActions, MatTable, MatHeaderCellDef, MatCellDef, MatColumnDef, MatIcon, MatHeaderCell, MatCell, MatHeaderRowDef, MatHeaderRow, MatSortHeader, MatRowDef, MatNoDataRow, MatIconButton, MatRow, MatPaginator, MatSort, MatTooltip, MatListItem, MatNavList, MatFormField, MatInput, MatLabel, MatSuffix, NgIf, DefaultValueAccessor, NgControlStatus, NgModel, DatePipe, AsyncPipe],
            styles: ["\n\n.fill-remaining-space[_ngcontent-%COMP%] {\n  flex: 1 1 auto;\n}\n.table-container[_ngcontent-%COMP%] {\n  max-height: calc(100vh - 10px);\n  overflow: auto;\n}\n.footer[_ngcontent-%COMP%] {\n  display: flex;\n  width: 50%;\n  font-size: x-small;\n  color: black;\n  padding-top: 15px;\n  padding-left: 15px;\n}\n/*# sourceMappingURL=object-list.component.css.map */"]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(S3ObjectListComponent, {
        className: "S3ObjectListComponent",
        filePath: "src/app/modules/s3/object-list/object-list.component.ts",
        lineNumber: 29
    });
})();

// src/app/modules/s3/s3-routing.module.ts
var routes = [
    {
        path: "",
        title: "S3BucketList",
        component: S3BucketListComponent
    },
    {
        path: "details/:bucketName",
        component: S3BucketDetailComponent
    },
    {
        path: "objects/:bucketName",
        component: S3ObjectListComponent
    },
    {
        path: "objects/details/:id",
        component: S3ObjectViewDialog
    }
];
var S3RoutingModule = class _S3RoutingModule {
    static {
        this.\u0275fac = function S3RoutingModule_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _S3RoutingModule)();
        };
    }
    static {
        this.\u0275mod = /* @__PURE__ */ \u0275\u0275defineNgModule({type: _S3RoutingModule});
    }
    static {
        this.\u0275inj = /* @__PURE__ */ \u0275\u0275defineInjector({imports: [RouterModule.forChild(routes), RouterModule]});
    }
};

// src/app/modules/s3/object-list/state/s3-object-list.effects.ts
var S3ObjectListEffects = class _S3ObjectListEffects {
    constructor(actions$, s3Service) {
        this.actions$ = actions$;
        this.s3Service = s3Service;
        this.sortColumns = [];
        this.loadBucketCounters$ = createEffect(() => this.actions$.pipe(ofType(s3ObjectListActions.loadObjects), mergeMap((action) => this.s3Service.listObjectsCounters(action.bucketName, action.prefix, action.pageSize, action.pageIndex, action.sortColumns).pipe(map((objects) => s3ObjectListActions.loadObjectsSuccess({objects})), catchError((error) => of(s3ObjectListActions.loadObjectsFailure({error: error.message})))))));
        this.deleteObject$ = createEffect(() => this.actions$.pipe(ofType(s3ObjectListActions.deleteObject), mergeMap((action) => this.s3Service.deleteObject(action.bucketName, action.key).then(() => s3ObjectListActions.deleteObjectSuccess()))));
    }

    static {
        this.\u0275fac = function S3ObjectListEffects_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _S3ObjectListEffects)(\u0275\u0275inject(Actions), \u0275\u0275inject(S3Service));
        };
    }
    static {
        this.\u0275prov = /* @__PURE__ */ \u0275\u0275defineInjectable({token: _S3ObjectListEffects, factory: _S3ObjectListEffects.\u0275fac});
    }
};

// src/app/modules/s3/s3.module.ts
var S3Module = class _S3Module {
    static {
        this.\u0275fac = function S3Module_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _S3Module)();
        };
    }
    static {
        this.\u0275mod = /* @__PURE__ */ \u0275\u0275defineNgModule({type: _S3Module});
    }
    static {
        this.\u0275inj = /* @__PURE__ */ \u0275\u0275defineInjector({
            providers: [S3Service, AwsMockHttpService], imports: [
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
                S3RoutingModule,
                StoreModule.forFeature(s3BucketListFeatureKey, s3BucketListReducer),
                StoreModule.forFeature(s3ObjectListFeatureKey, s3ObjectListReducer),
                EffectsModule.forFeature([S3BucketListEffects, S3ObjectListEffects])
            ]
        });
    }
};
export {
    S3Module
};
//# sourceMappingURL=chunk-YHAKNSZF.js.map

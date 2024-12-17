import {collectBodyString} from "./chunk-5F2IFVYA.js";
import {__async} from "./chunk-G42SKTPL.js";

// node_modules/@aws-sdk/core/dist-es/submodules/protocols/json/parseJsonBody.js
var parseJsonBody = (streamBody, context) => collectBodyString(streamBody, context).then((encoded) => {
    if (encoded.length) {
        try {
            return JSON.parse(encoded);
        } catch (e) {
            if (e?.name === "SyntaxError") {
                Object.defineProperty(e, "$responseBodyText", {
                    value: encoded
                });
            }
            throw e;
        }
    }
    return {};
});
var parseJsonErrorBody = (errorBody, context) => __async(void 0, null, function* () {
    const value = yield parseJsonBody(errorBody, context);
    value.message = value.message ?? value.Message;
    return value;
});
var loadRestJsonErrorCode = (output, data) => {
    const findKey = (object, key) => Object.keys(object).find((k) => k.toLowerCase() === key.toLowerCase());
    const sanitizeErrorCode = (rawValue) => {
        let cleanValue = rawValue;
        if (typeof cleanValue === "number") {
            cleanValue = cleanValue.toString();
        }
        if (cleanValue.indexOf(",") >= 0) {
            cleanValue = cleanValue.split(",")[0];
        }
        if (cleanValue.indexOf(":") >= 0) {
            cleanValue = cleanValue.split(":")[0];
        }
        if (cleanValue.indexOf("#") >= 0) {
            cleanValue = cleanValue.split("#")[1];
        }
        return cleanValue;
    };
    const headerKey = findKey(output.headers, "x-amzn-errortype");
    if (headerKey !== void 0) {
        return sanitizeErrorCode(output.headers[headerKey]);
    }
    if (data.code !== void 0) {
        return sanitizeErrorCode(data.code);
    }
    if (data["__type"] !== void 0) {
        return sanitizeErrorCode(data["__type"]);
    }
};

export {
    parseJsonBody,
    parseJsonErrorBody,
    loadRestJsonErrorCode
};
//# sourceMappingURL=chunk-HK7D4W5I.js.map

import {__awaiter, __generator} from "./chunk-LGOS2CJL.js";
import {__async, __commonJS, __objRest, __spreadProps, __spreadValues, __toESM} from "./chunk-G42SKTPL.js";

// node_modules/bowser/es5.js
var require_es5 = __commonJS({
    "node_modules/bowser/es5.js"(exports, module) {
        "use strict";
        !function (e, t) {
            "object" == typeof exports && "object" == typeof module ? module.exports = t() : "function" == typeof define && define.amd ? define([], t) : "object" == typeof exports ? exports.bowser = t() : e.bowser = t();
        }(exports, function () {
            return function (e) {
                var t = {};

                function r(n) {
                    if (t[n]) return t[n].exports;
                    var i = t[n] = {
                        i: n,
                        l: false,
                        exports: {}
                    };
                    return e[n].call(i.exports, i, i.exports, r), i.l = true, i.exports;
                }

                return r.m = e, r.c = t, r.d = function (e2, t2, n) {
                    r.o(e2, t2) || Object.defineProperty(e2, t2, {
                        enumerable: true,
                        get: n
                    });
                }, r.r = function (e2) {
                    "undefined" != typeof Symbol && Symbol.toStringTag && Object.defineProperty(e2, Symbol.toStringTag, {
                        value: "Module"
                    }), Object.defineProperty(e2, "__esModule", {
                        value: true
                    });
                }, r.t = function (e2, t2) {
                    if (1 & t2 && (e2 = r(e2)), 8 & t2) return e2;
                    if (4 & t2 && "object" == typeof e2 && e2 && e2.__esModule) return e2;
                    var n = /* @__PURE__ */ Object.create(null);
                    if (r.r(n), Object.defineProperty(n, "default", {
                        enumerable: true,
                        value: e2
                    }), 2 & t2 && "string" != typeof e2) for (var i in e2) r.d(n, i, function (t3) {
                        return e2[t3];
                    }.bind(null, i));
                    return n;
                }, r.n = function (e2) {
                    var t2 = e2 && e2.__esModule ? function () {
                        return e2.default;
                    } : function () {
                        return e2;
                    };
                    return r.d(t2, "a", t2), t2;
                }, r.o = function (e2, t2) {
                    return Object.prototype.hasOwnProperty.call(e2, t2);
                }, r.p = "", r(r.s = 90);
            }({
                17: function (e, t, r) {
                    "use strict";
                    t.__esModule = true, t.default = void 0;
                    var n = r(18), i = function () {
                        function e2() {
                        }

                        return e2.getFirstMatch = function (e3, t2) {
                            var r2 = t2.match(e3);
                            return r2 && r2.length > 0 && r2[1] || "";
                        }, e2.getSecondMatch = function (e3, t2) {
                            var r2 = t2.match(e3);
                            return r2 && r2.length > 1 && r2[2] || "";
                        }, e2.matchAndReturnConst = function (e3, t2, r2) {
                            if (e3.test(t2)) return r2;
                        }, e2.getWindowsVersionName = function (e3) {
                            switch (e3) {
                                case "NT":
                                    return "NT";
                                case "XP":
                                    return "XP";
                                case "NT 5.0":
                                    return "2000";
                                case "NT 5.1":
                                    return "XP";
                                case "NT 5.2":
                                    return "2003";
                                case "NT 6.0":
                                    return "Vista";
                                case "NT 6.1":
                                    return "7";
                                case "NT 6.2":
                                    return "8";
                                case "NT 6.3":
                                    return "8.1";
                                case "NT 10.0":
                                    return "10";
                                default:
                                    return;
                            }
                        }, e2.getMacOSVersionName = function (e3) {
                            var t2 = e3.split(".").splice(0, 2).map(function (e4) {
                                return parseInt(e4, 10) || 0;
                            });
                            if (t2.push(0), 10 === t2[0]) switch (t2[1]) {
                                case 5:
                                    return "Leopard";
                                case 6:
                                    return "Snow Leopard";
                                case 7:
                                    return "Lion";
                                case 8:
                                    return "Mountain Lion";
                                case 9:
                                    return "Mavericks";
                                case 10:
                                    return "Yosemite";
                                case 11:
                                    return "El Capitan";
                                case 12:
                                    return "Sierra";
                                case 13:
                                    return "High Sierra";
                                case 14:
                                    return "Mojave";
                                case 15:
                                    return "Catalina";
                                default:
                                    return;
                            }
                        }, e2.getAndroidVersionName = function (e3) {
                            var t2 = e3.split(".").splice(0, 2).map(function (e4) {
                                return parseInt(e4, 10) || 0;
                            });
                            if (t2.push(0), !(1 === t2[0] && t2[1] < 5)) return 1 === t2[0] && t2[1] < 6 ? "Cupcake" : 1 === t2[0] && t2[1] >= 6 ? "Donut" : 2 === t2[0] && t2[1] < 2 ? "Eclair" : 2 === t2[0] && 2 === t2[1] ? "Froyo" : 2 === t2[0] && t2[1] > 2 ? "Gingerbread" : 3 === t2[0] ? "Honeycomb" : 4 === t2[0] && t2[1] < 1 ? "Ice Cream Sandwich" : 4 === t2[0] && t2[1] < 4 ? "Jelly Bean" : 4 === t2[0] && t2[1] >= 4 ? "KitKat" : 5 === t2[0] ? "Lollipop" : 6 === t2[0] ? "Marshmallow" : 7 === t2[0] ? "Nougat" : 8 === t2[0] ? "Oreo" : 9 === t2[0] ? "Pie" : void 0;
                        }, e2.getVersionPrecision = function (e3) {
                            return e3.split(".").length;
                        }, e2.compareVersions = function (t2, r2, n2) {
                            void 0 === n2 && (n2 = false);
                            var i2 = e2.getVersionPrecision(t2), s = e2.getVersionPrecision(r2), a = Math.max(i2, s), o = 0, u = e2.map([t2, r2], function (t3) {
                                var r3 = a - e2.getVersionPrecision(t3), n3 = t3 + new Array(r3 + 1).join(".0");
                                return e2.map(n3.split("."), function (e3) {
                                    return new Array(20 - e3.length).join("0") + e3;
                                }).reverse();
                            });
                            for (n2 && (o = a - Math.min(i2, s)), a -= 1; a >= o;) {
                                if (u[0][a] > u[1][a]) return 1;
                                if (u[0][a] === u[1][a]) {
                                    if (a === o) return 0;
                                    a -= 1;
                                } else if (u[0][a] < u[1][a]) return -1;
                            }
                        }, e2.map = function (e3, t2) {
                            var r2, n2 = [];
                            if (Array.prototype.map) return Array.prototype.map.call(e3, t2);
                            for (r2 = 0; r2 < e3.length; r2 += 1) n2.push(t2(e3[r2]));
                            return n2;
                        }, e2.find = function (e3, t2) {
                            var r2, n2;
                            if (Array.prototype.find) return Array.prototype.find.call(e3, t2);
                            for (r2 = 0, n2 = e3.length; r2 < n2; r2 += 1) {
                                var i2 = e3[r2];
                                if (t2(i2, r2)) return i2;
                            }
                        }, e2.assign = function (e3) {
                            for (var t2, r2, n2 = e3, i2 = arguments.length, s = new Array(i2 > 1 ? i2 - 1 : 0), a = 1; a < i2; a++) s[a - 1] = arguments[a];
                            if (Object.assign) return Object.assign.apply(Object, [e3].concat(s));
                            var o = function () {
                                var e4 = s[t2];
                                "object" == typeof e4 && null !== e4 && Object.keys(e4).forEach(function (t3) {
                                    n2[t3] = e4[t3];
                                });
                            };
                            for (t2 = 0, r2 = s.length; t2 < r2; t2 += 1) o();
                            return e3;
                        }, e2.getBrowserAlias = function (e3) {
                            return n.BROWSER_ALIASES_MAP[e3];
                        }, e2.getBrowserTypeByAlias = function (e3) {
                            return n.BROWSER_MAP[e3] || "";
                        }, e2;
                    }();
                    t.default = i, e.exports = t.default;
                },
                18: function (e, t, r) {
                    "use strict";
                    t.__esModule = true, t.ENGINE_MAP = t.OS_MAP = t.PLATFORMS_MAP = t.BROWSER_MAP = t.BROWSER_ALIASES_MAP = void 0;
                    t.BROWSER_ALIASES_MAP = {
                        "Amazon Silk": "amazon_silk",
                        "Android Browser": "android",
                        Bada: "bada",
                        BlackBerry: "blackberry",
                        Chrome: "chrome",
                        Chromium: "chromium",
                        Electron: "electron",
                        Epiphany: "epiphany",
                        Firefox: "firefox",
                        Focus: "focus",
                        Generic: "generic",
                        "Google Search": "google_search",
                        Googlebot: "googlebot",
                        "Internet Explorer": "ie",
                        "K-Meleon": "k_meleon",
                        Maxthon: "maxthon",
                        "Microsoft Edge": "edge",
                        "MZ Browser": "mz",
                        "NAVER Whale Browser": "naver",
                        Opera: "opera",
                        "Opera Coast": "opera_coast",
                        PhantomJS: "phantomjs",
                        Puffin: "puffin",
                        QupZilla: "qupzilla",
                        QQ: "qq",
                        QQLite: "qqlite",
                        Safari: "safari",
                        Sailfish: "sailfish",
                        "Samsung Internet for Android": "samsung_internet",
                        SeaMonkey: "seamonkey",
                        Sleipnir: "sleipnir",
                        Swing: "swing",
                        Tizen: "tizen",
                        "UC Browser": "uc",
                        Vivaldi: "vivaldi",
                        "WebOS Browser": "webos",
                        WeChat: "wechat",
                        "Yandex Browser": "yandex",
                        Roku: "roku"
                    };
                    t.BROWSER_MAP = {
                        amazon_silk: "Amazon Silk",
                        android: "Android Browser",
                        bada: "Bada",
                        blackberry: "BlackBerry",
                        chrome: "Chrome",
                        chromium: "Chromium",
                        electron: "Electron",
                        epiphany: "Epiphany",
                        firefox: "Firefox",
                        focus: "Focus",
                        generic: "Generic",
                        googlebot: "Googlebot",
                        google_search: "Google Search",
                        ie: "Internet Explorer",
                        k_meleon: "K-Meleon",
                        maxthon: "Maxthon",
                        edge: "Microsoft Edge",
                        mz: "MZ Browser",
                        naver: "NAVER Whale Browser",
                        opera: "Opera",
                        opera_coast: "Opera Coast",
                        phantomjs: "PhantomJS",
                        puffin: "Puffin",
                        qupzilla: "QupZilla",
                        qq: "QQ Browser",
                        qqlite: "QQ Browser Lite",
                        safari: "Safari",
                        sailfish: "Sailfish",
                        samsung_internet: "Samsung Internet for Android",
                        seamonkey: "SeaMonkey",
                        sleipnir: "Sleipnir",
                        swing: "Swing",
                        tizen: "Tizen",
                        uc: "UC Browser",
                        vivaldi: "Vivaldi",
                        webos: "WebOS Browser",
                        wechat: "WeChat",
                        yandex: "Yandex Browser"
                    };
                    t.PLATFORMS_MAP = {
                        tablet: "tablet",
                        mobile: "mobile",
                        desktop: "desktop",
                        tv: "tv"
                    };
                    t.OS_MAP = {
                        WindowsPhone: "Windows Phone",
                        Windows: "Windows",
                        MacOS: "macOS",
                        iOS: "iOS",
                        Android: "Android",
                        WebOS: "WebOS",
                        BlackBerry: "BlackBerry",
                        Bada: "Bada",
                        Tizen: "Tizen",
                        Linux: "Linux",
                        ChromeOS: "Chrome OS",
                        PlayStation4: "PlayStation 4",
                        Roku: "Roku"
                    };
                    t.ENGINE_MAP = {
                        EdgeHTML: "EdgeHTML",
                        Blink: "Blink",
                        Trident: "Trident",
                        Presto: "Presto",
                        Gecko: "Gecko",
                        WebKit: "WebKit"
                    };
                },
                90: function (e, t, r) {
                    "use strict";
                    t.__esModule = true, t.default = void 0;
                    var n, i = (n = r(91)) && n.__esModule ? n : {
                        default: n
                    }, s = r(18);

                    function a(e2, t2) {
                        for (var r2 = 0; r2 < t2.length; r2++) {
                            var n2 = t2[r2];
                            n2.enumerable = n2.enumerable || false, n2.configurable = true, "value" in n2 && (n2.writable = true), Object.defineProperty(e2, n2.key, n2);
                        }
                    }

                    var o = function () {
                        function e2() {
                        }

                        var t2, r2, n2;
                        return e2.getParser = function (e3, t3) {
                            if (void 0 === t3 && (t3 = false), "string" != typeof e3) throw new Error("UserAgent should be a string");
                            return new i.default(e3, t3);
                        }, e2.parse = function (e3) {
                            return new i.default(e3).getResult();
                        }, t2 = e2, n2 = [{
                            key: "BROWSER_MAP",
                            get: function () {
                                return s.BROWSER_MAP;
                            }
                        }, {
                            key: "ENGINE_MAP",
                            get: function () {
                                return s.ENGINE_MAP;
                            }
                        }, {
                            key: "OS_MAP",
                            get: function () {
                                return s.OS_MAP;
                            }
                        }, {
                            key: "PLATFORMS_MAP",
                            get: function () {
                                return s.PLATFORMS_MAP;
                            }
                        }], (r2 = null) && a(t2.prototype, r2), n2 && a(t2, n2), e2;
                    }();
                    t.default = o, e.exports = t.default;
                },
                91: function (e, t, r) {
                    "use strict";
                    t.__esModule = true, t.default = void 0;
                    var n = u(r(92)), i = u(r(93)), s = u(r(94)), a = u(r(95)), o = u(r(17));

                    function u(e2) {
                        return e2 && e2.__esModule ? e2 : {
                            default: e2
                        };
                    }

                    var d = function () {
                        function e2(e3, t3) {
                            if (void 0 === t3 && (t3 = false), null == e3 || "" === e3) throw new Error("UserAgent parameter can't be empty");
                            this._ua = e3, this.parsedResult = {}, true !== t3 && this.parse();
                        }

                        var t2 = e2.prototype;
                        return t2.getUA = function () {
                            return this._ua;
                        }, t2.test = function (e3) {
                            return e3.test(this._ua);
                        }, t2.parseBrowser = function () {
                            var e3 = this;
                            this.parsedResult.browser = {};
                            var t3 = o.default.find(n.default, function (t4) {
                                if ("function" == typeof t4.test) return t4.test(e3);
                                if (t4.test instanceof Array) return t4.test.some(function (t5) {
                                    return e3.test(t5);
                                });
                                throw new Error("Browser's test function is not valid");
                            });
                            return t3 && (this.parsedResult.browser = t3.describe(this.getUA())), this.parsedResult.browser;
                        }, t2.getBrowser = function () {
                            return this.parsedResult.browser ? this.parsedResult.browser : this.parseBrowser();
                        }, t2.getBrowserName = function (e3) {
                            return e3 ? String(this.getBrowser().name).toLowerCase() || "" : this.getBrowser().name || "";
                        }, t2.getBrowserVersion = function () {
                            return this.getBrowser().version;
                        }, t2.getOS = function () {
                            return this.parsedResult.os ? this.parsedResult.os : this.parseOS();
                        }, t2.parseOS = function () {
                            var e3 = this;
                            this.parsedResult.os = {};
                            var t3 = o.default.find(i.default, function (t4) {
                                if ("function" == typeof t4.test) return t4.test(e3);
                                if (t4.test instanceof Array) return t4.test.some(function (t5) {
                                    return e3.test(t5);
                                });
                                throw new Error("Browser's test function is not valid");
                            });
                            return t3 && (this.parsedResult.os = t3.describe(this.getUA())), this.parsedResult.os;
                        }, t2.getOSName = function (e3) {
                            var t3 = this.getOS().name;
                            return e3 ? String(t3).toLowerCase() || "" : t3 || "";
                        }, t2.getOSVersion = function () {
                            return this.getOS().version;
                        }, t2.getPlatform = function () {
                            return this.parsedResult.platform ? this.parsedResult.platform : this.parsePlatform();
                        }, t2.getPlatformType = function (e3) {
                            void 0 === e3 && (e3 = false);
                            var t3 = this.getPlatform().type;
                            return e3 ? String(t3).toLowerCase() || "" : t3 || "";
                        }, t2.parsePlatform = function () {
                            var e3 = this;
                            this.parsedResult.platform = {};
                            var t3 = o.default.find(s.default, function (t4) {
                                if ("function" == typeof t4.test) return t4.test(e3);
                                if (t4.test instanceof Array) return t4.test.some(function (t5) {
                                    return e3.test(t5);
                                });
                                throw new Error("Browser's test function is not valid");
                            });
                            return t3 && (this.parsedResult.platform = t3.describe(this.getUA())), this.parsedResult.platform;
                        }, t2.getEngine = function () {
                            return this.parsedResult.engine ? this.parsedResult.engine : this.parseEngine();
                        }, t2.getEngineName = function (e3) {
                            return e3 ? String(this.getEngine().name).toLowerCase() || "" : this.getEngine().name || "";
                        }, t2.parseEngine = function () {
                            var e3 = this;
                            this.parsedResult.engine = {};
                            var t3 = o.default.find(a.default, function (t4) {
                                if ("function" == typeof t4.test) return t4.test(e3);
                                if (t4.test instanceof Array) return t4.test.some(function (t5) {
                                    return e3.test(t5);
                                });
                                throw new Error("Browser's test function is not valid");
                            });
                            return t3 && (this.parsedResult.engine = t3.describe(this.getUA())), this.parsedResult.engine;
                        }, t2.parse = function () {
                            return this.parseBrowser(), this.parseOS(), this.parsePlatform(), this.parseEngine(), this;
                        }, t2.getResult = function () {
                            return o.default.assign({}, this.parsedResult);
                        }, t2.satisfies = function (e3) {
                            var t3 = this, r2 = {}, n2 = 0, i2 = {}, s2 = 0;
                            if (Object.keys(e3).forEach(function (t4) {
                                var a3 = e3[t4];
                                "string" == typeof a3 ? (i2[t4] = a3, s2 += 1) : "object" == typeof a3 && (r2[t4] = a3, n2 += 1);
                            }), n2 > 0) {
                                var a2 = Object.keys(r2), u2 = o.default.find(a2, function (e4) {
                                    return t3.isOS(e4);
                                });
                                if (u2) {
                                    var d2 = this.satisfies(r2[u2]);
                                    if (void 0 !== d2) return d2;
                                }
                                var c = o.default.find(a2, function (e4) {
                                    return t3.isPlatform(e4);
                                });
                                if (c) {
                                    var f = this.satisfies(r2[c]);
                                    if (void 0 !== f) return f;
                                }
                            }
                            if (s2 > 0) {
                                var l = Object.keys(i2), h = o.default.find(l, function (e4) {
                                    return t3.isBrowser(e4, true);
                                });
                                if (void 0 !== h) return this.compareVersion(i2[h]);
                            }
                        }, t2.isBrowser = function (e3, t3) {
                            void 0 === t3 && (t3 = false);
                            var r2 = this.getBrowserName().toLowerCase(), n2 = e3.toLowerCase(), i2 = o.default.getBrowserTypeByAlias(n2);
                            return t3 && i2 && (n2 = i2.toLowerCase()), n2 === r2;
                        }, t2.compareVersion = function (e3) {
                            var t3 = [0], r2 = e3, n2 = false, i2 = this.getBrowserVersion();
                            if ("string" == typeof i2) return ">" === e3[0] || "<" === e3[0] ? (r2 = e3.substr(1), "=" === e3[1] ? (n2 = true, r2 = e3.substr(2)) : t3 = [], ">" === e3[0] ? t3.push(1) : t3.push(-1)) : "=" === e3[0] ? r2 = e3.substr(1) : "~" === e3[0] && (n2 = true, r2 = e3.substr(1)), t3.indexOf(o.default.compareVersions(i2, r2, n2)) > -1;
                        }, t2.isOS = function (e3) {
                            return this.getOSName(true) === String(e3).toLowerCase();
                        }, t2.isPlatform = function (e3) {
                            return this.getPlatformType(true) === String(e3).toLowerCase();
                        }, t2.isEngine = function (e3) {
                            return this.getEngineName(true) === String(e3).toLowerCase();
                        }, t2.is = function (e3, t3) {
                            return void 0 === t3 && (t3 = false), this.isBrowser(e3, t3) || this.isOS(e3) || this.isPlatform(e3);
                        }, t2.some = function (e3) {
                            var t3 = this;
                            return void 0 === e3 && (e3 = []), e3.some(function (e4) {
                                return t3.is(e4);
                            });
                        }, e2;
                    }();
                    t.default = d, e.exports = t.default;
                },
                92: function (e, t, r) {
                    "use strict";
                    t.__esModule = true, t.default = void 0;
                    var n, i = (n = r(17)) && n.__esModule ? n : {
                        default: n
                    };
                    var s = /version\/(\d+(\.?_?\d+)+)/i, a = [{
                        test: [/googlebot/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Googlebot"
                            }, r2 = i.default.getFirstMatch(/googlebot\/(\d+(\.\d+))/i, e2) || i.default.getFirstMatch(s, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/opera/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Opera"
                            }, r2 = i.default.getFirstMatch(s, e2) || i.default.getFirstMatch(/(?:opera)[\s/](\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/opr\/|opios/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Opera"
                            }, r2 = i.default.getFirstMatch(/(?:opr|opios)[\s/](\S+)/i, e2) || i.default.getFirstMatch(s, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/SamsungBrowser/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Samsung Internet for Android"
                            }, r2 = i.default.getFirstMatch(s, e2) || i.default.getFirstMatch(/(?:SamsungBrowser)[\s/](\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/Whale/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "NAVER Whale Browser"
                            }, r2 = i.default.getFirstMatch(s, e2) || i.default.getFirstMatch(/(?:whale)[\s/](\d+(?:\.\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/MZBrowser/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "MZ Browser"
                            }, r2 = i.default.getFirstMatch(/(?:MZBrowser)[\s/](\d+(?:\.\d+)+)/i, e2) || i.default.getFirstMatch(s, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/focus/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Focus"
                            }, r2 = i.default.getFirstMatch(/(?:focus)[\s/](\d+(?:\.\d+)+)/i, e2) || i.default.getFirstMatch(s, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/swing/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Swing"
                            }, r2 = i.default.getFirstMatch(/(?:swing)[\s/](\d+(?:\.\d+)+)/i, e2) || i.default.getFirstMatch(s, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/coast/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Opera Coast"
                            }, r2 = i.default.getFirstMatch(s, e2) || i.default.getFirstMatch(/(?:coast)[\s/](\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/opt\/\d+(?:.?_?\d+)+/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Opera Touch"
                            }, r2 = i.default.getFirstMatch(/(?:opt)[\s/](\d+(\.?_?\d+)+)/i, e2) || i.default.getFirstMatch(s, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/yabrowser/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Yandex Browser"
                            }, r2 = i.default.getFirstMatch(/(?:yabrowser)[\s/](\d+(\.?_?\d+)+)/i, e2) || i.default.getFirstMatch(s, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/ucbrowser/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "UC Browser"
                            }, r2 = i.default.getFirstMatch(s, e2) || i.default.getFirstMatch(/(?:ucbrowser)[\s/](\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/Maxthon|mxios/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Maxthon"
                            }, r2 = i.default.getFirstMatch(s, e2) || i.default.getFirstMatch(/(?:Maxthon|mxios)[\s/](\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/epiphany/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Epiphany"
                            }, r2 = i.default.getFirstMatch(s, e2) || i.default.getFirstMatch(/(?:epiphany)[\s/](\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/puffin/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Puffin"
                            }, r2 = i.default.getFirstMatch(s, e2) || i.default.getFirstMatch(/(?:puffin)[\s/](\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/sleipnir/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Sleipnir"
                            }, r2 = i.default.getFirstMatch(s, e2) || i.default.getFirstMatch(/(?:sleipnir)[\s/](\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/k-meleon/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "K-Meleon"
                            }, r2 = i.default.getFirstMatch(s, e2) || i.default.getFirstMatch(/(?:k-meleon)[\s/](\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/micromessenger/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "WeChat"
                            }, r2 = i.default.getFirstMatch(/(?:micromessenger)[\s/](\d+(\.?_?\d+)+)/i, e2) || i.default.getFirstMatch(s, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/qqbrowser/i],
                        describe: function (e2) {
                            var t2 = {
                                name: /qqbrowserlite/i.test(e2) ? "QQ Browser Lite" : "QQ Browser"
                            }, r2 = i.default.getFirstMatch(/(?:qqbrowserlite|qqbrowser)[/](\d+(\.?_?\d+)+)/i, e2) || i.default.getFirstMatch(s, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/msie|trident/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Internet Explorer"
                            }, r2 = i.default.getFirstMatch(/(?:msie |rv:)(\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/\sedg\//i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Microsoft Edge"
                            }, r2 = i.default.getFirstMatch(/\sedg\/(\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/edg([ea]|ios)/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Microsoft Edge"
                            }, r2 = i.default.getSecondMatch(/edg([ea]|ios)\/(\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/vivaldi/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Vivaldi"
                            }, r2 = i.default.getFirstMatch(/vivaldi\/(\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/seamonkey/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "SeaMonkey"
                            }, r2 = i.default.getFirstMatch(/seamonkey\/(\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/sailfish/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Sailfish"
                            }, r2 = i.default.getFirstMatch(/sailfish\s?browser\/(\d+(\.\d+)?)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/silk/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Amazon Silk"
                            }, r2 = i.default.getFirstMatch(/silk\/(\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/phantom/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "PhantomJS"
                            }, r2 = i.default.getFirstMatch(/phantomjs\/(\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/slimerjs/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "SlimerJS"
                            }, r2 = i.default.getFirstMatch(/slimerjs\/(\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/blackberry|\bbb\d+/i, /rim\stablet/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "BlackBerry"
                            }, r2 = i.default.getFirstMatch(s, e2) || i.default.getFirstMatch(/blackberry[\d]+\/(\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/(web|hpw)[o0]s/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "WebOS Browser"
                            }, r2 = i.default.getFirstMatch(s, e2) || i.default.getFirstMatch(/w(?:eb)?[o0]sbrowser\/(\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/bada/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Bada"
                            }, r2 = i.default.getFirstMatch(/dolfin\/(\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/tizen/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Tizen"
                            }, r2 = i.default.getFirstMatch(/(?:tizen\s?)?browser\/(\d+(\.?_?\d+)+)/i, e2) || i.default.getFirstMatch(s, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/qupzilla/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "QupZilla"
                            }, r2 = i.default.getFirstMatch(/(?:qupzilla)[\s/](\d+(\.?_?\d+)+)/i, e2) || i.default.getFirstMatch(s, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/firefox|iceweasel|fxios/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Firefox"
                            }, r2 = i.default.getFirstMatch(/(?:firefox|iceweasel|fxios)[\s/](\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/electron/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Electron"
                            }, r2 = i.default.getFirstMatch(/(?:electron)\/(\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/MiuiBrowser/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Miui"
                            }, r2 = i.default.getFirstMatch(/(?:MiuiBrowser)[\s/](\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/chromium/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Chromium"
                            }, r2 = i.default.getFirstMatch(/(?:chromium)[\s/](\d+(\.?_?\d+)+)/i, e2) || i.default.getFirstMatch(s, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/chrome|crios|crmo/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Chrome"
                            }, r2 = i.default.getFirstMatch(/(?:chrome|crios|crmo)\/(\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/GSA/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Google Search"
                            }, r2 = i.default.getFirstMatch(/(?:GSA)\/(\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: function (e2) {
                            var t2 = !e2.test(/like android/i), r2 = e2.test(/android/i);
                            return t2 && r2;
                        },
                        describe: function (e2) {
                            var t2 = {
                                name: "Android Browser"
                            }, r2 = i.default.getFirstMatch(s, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/playstation 4/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "PlayStation 4"
                            }, r2 = i.default.getFirstMatch(s, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/safari|applewebkit/i],
                        describe: function (e2) {
                            var t2 = {
                                name: "Safari"
                            }, r2 = i.default.getFirstMatch(s, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/.*/i],
                        describe: function (e2) {
                            var t2 = -1 !== e2.search("\\(") ? /^(.*)\/(.*)[ \t]\((.*)/ : /^(.*)\/(.*) /;
                            return {
                                name: i.default.getFirstMatch(t2, e2),
                                version: i.default.getSecondMatch(t2, e2)
                            };
                        }
                    }];
                    t.default = a, e.exports = t.default;
                },
                93: function (e, t, r) {
                    "use strict";
                    t.__esModule = true, t.default = void 0;
                    var n, i = (n = r(17)) && n.__esModule ? n : {
                        default: n
                    }, s = r(18);
                    var a = [{
                        test: [/Roku\/DVP/],
                        describe: function (e2) {
                            var t2 = i.default.getFirstMatch(/Roku\/DVP-(\d+\.\d+)/i, e2);
                            return {
                                name: s.OS_MAP.Roku,
                                version: t2
                            };
                        }
                    }, {
                        test: [/windows phone/i],
                        describe: function (e2) {
                            var t2 = i.default.getFirstMatch(/windows phone (?:os)?\s?(\d+(\.\d+)*)/i, e2);
                            return {
                                name: s.OS_MAP.WindowsPhone,
                                version: t2
                            };
                        }
                    }, {
                        test: [/windows /i],
                        describe: function (e2) {
                            var t2 = i.default.getFirstMatch(/Windows ((NT|XP)( \d\d?.\d)?)/i, e2), r2 = i.default.getWindowsVersionName(t2);
                            return {
                                name: s.OS_MAP.Windows,
                                version: t2,
                                versionName: r2
                            };
                        }
                    }, {
                        test: [/Macintosh(.*?) FxiOS(.*?)\//],
                        describe: function (e2) {
                            var t2 = {
                                name: s.OS_MAP.iOS
                            }, r2 = i.default.getSecondMatch(/(Version\/)(\d[\d.]+)/, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/macintosh/i],
                        describe: function (e2) {
                            var t2 = i.default.getFirstMatch(/mac os x (\d+(\.?_?\d+)+)/i, e2).replace(/[_\s]/g, "."), r2 = i.default.getMacOSVersionName(t2), n2 = {
                                name: s.OS_MAP.MacOS,
                                version: t2
                            };
                            return r2 && (n2.versionName = r2), n2;
                        }
                    }, {
                        test: [/(ipod|iphone|ipad)/i],
                        describe: function (e2) {
                            var t2 = i.default.getFirstMatch(/os (\d+([_\s]\d+)*) like mac os x/i, e2).replace(/[_\s]/g, ".");
                            return {
                                name: s.OS_MAP.iOS,
                                version: t2
                            };
                        }
                    }, {
                        test: function (e2) {
                            var t2 = !e2.test(/like android/i), r2 = e2.test(/android/i);
                            return t2 && r2;
                        },
                        describe: function (e2) {
                            var t2 = i.default.getFirstMatch(/android[\s/-](\d+(\.\d+)*)/i, e2), r2 = i.default.getAndroidVersionName(t2), n2 = {
                                name: s.OS_MAP.Android,
                                version: t2
                            };
                            return r2 && (n2.versionName = r2), n2;
                        }
                    }, {
                        test: [/(web|hpw)[o0]s/i],
                        describe: function (e2) {
                            var t2 = i.default.getFirstMatch(/(?:web|hpw)[o0]s\/(\d+(\.\d+)*)/i, e2), r2 = {
                                name: s.OS_MAP.WebOS
                            };
                            return t2 && t2.length && (r2.version = t2), r2;
                        }
                    }, {
                        test: [/blackberry|\bbb\d+/i, /rim\stablet/i],
                        describe: function (e2) {
                            var t2 = i.default.getFirstMatch(/rim\stablet\sos\s(\d+(\.\d+)*)/i, e2) || i.default.getFirstMatch(/blackberry\d+\/(\d+([_\s]\d+)*)/i, e2) || i.default.getFirstMatch(/\bbb(\d+)/i, e2);
                            return {
                                name: s.OS_MAP.BlackBerry,
                                version: t2
                            };
                        }
                    }, {
                        test: [/bada/i],
                        describe: function (e2) {
                            var t2 = i.default.getFirstMatch(/bada\/(\d+(\.\d+)*)/i, e2);
                            return {
                                name: s.OS_MAP.Bada,
                                version: t2
                            };
                        }
                    }, {
                        test: [/tizen/i],
                        describe: function (e2) {
                            var t2 = i.default.getFirstMatch(/tizen[/\s](\d+(\.\d+)*)/i, e2);
                            return {
                                name: s.OS_MAP.Tizen,
                                version: t2
                            };
                        }
                    }, {
                        test: [/linux/i],
                        describe: function () {
                            return {
                                name: s.OS_MAP.Linux
                            };
                        }
                    }, {
                        test: [/CrOS/],
                        describe: function () {
                            return {
                                name: s.OS_MAP.ChromeOS
                            };
                        }
                    }, {
                        test: [/PlayStation 4/],
                        describe: function (e2) {
                            var t2 = i.default.getFirstMatch(/PlayStation 4[/\s](\d+(\.\d+)*)/i, e2);
                            return {
                                name: s.OS_MAP.PlayStation4,
                                version: t2
                            };
                        }
                    }];
                    t.default = a, e.exports = t.default;
                },
                94: function (e, t, r) {
                    "use strict";
                    t.__esModule = true, t.default = void 0;
                    var n, i = (n = r(17)) && n.__esModule ? n : {
                        default: n
                    }, s = r(18);
                    var a = [{
                        test: [/googlebot/i],
                        describe: function () {
                            return {
                                type: "bot",
                                vendor: "Google"
                            };
                        }
                    }, {
                        test: [/huawei/i],
                        describe: function (e2) {
                            var t2 = i.default.getFirstMatch(/(can-l01)/i, e2) && "Nova", r2 = {
                                type: s.PLATFORMS_MAP.mobile,
                                vendor: "Huawei"
                            };
                            return t2 && (r2.model = t2), r2;
                        }
                    }, {
                        test: [/nexus\s*(?:7|8|9|10).*/i],
                        describe: function () {
                            return {
                                type: s.PLATFORMS_MAP.tablet,
                                vendor: "Nexus"
                            };
                        }
                    }, {
                        test: [/ipad/i],
                        describe: function () {
                            return {
                                type: s.PLATFORMS_MAP.tablet,
                                vendor: "Apple",
                                model: "iPad"
                            };
                        }
                    }, {
                        test: [/Macintosh(.*?) FxiOS(.*?)\//],
                        describe: function () {
                            return {
                                type: s.PLATFORMS_MAP.tablet,
                                vendor: "Apple",
                                model: "iPad"
                            };
                        }
                    }, {
                        test: [/kftt build/i],
                        describe: function () {
                            return {
                                type: s.PLATFORMS_MAP.tablet,
                                vendor: "Amazon",
                                model: "Kindle Fire HD 7"
                            };
                        }
                    }, {
                        test: [/silk/i],
                        describe: function () {
                            return {
                                type: s.PLATFORMS_MAP.tablet,
                                vendor: "Amazon"
                            };
                        }
                    }, {
                        test: [/tablet(?! pc)/i],
                        describe: function () {
                            return {
                                type: s.PLATFORMS_MAP.tablet
                            };
                        }
                    }, {
                        test: function (e2) {
                            var t2 = e2.test(/ipod|iphone/i), r2 = e2.test(/like (ipod|iphone)/i);
                            return t2 && !r2;
                        },
                        describe: function (e2) {
                            var t2 = i.default.getFirstMatch(/(ipod|iphone)/i, e2);
                            return {
                                type: s.PLATFORMS_MAP.mobile,
                                vendor: "Apple",
                                model: t2
                            };
                        }
                    }, {
                        test: [/nexus\s*[0-6].*/i, /galaxy nexus/i],
                        describe: function () {
                            return {
                                type: s.PLATFORMS_MAP.mobile,
                                vendor: "Nexus"
                            };
                        }
                    }, {
                        test: [/[^-]mobi/i],
                        describe: function () {
                            return {
                                type: s.PLATFORMS_MAP.mobile
                            };
                        }
                    }, {
                        test: function (e2) {
                            return "blackberry" === e2.getBrowserName(true);
                        },
                        describe: function () {
                            return {
                                type: s.PLATFORMS_MAP.mobile,
                                vendor: "BlackBerry"
                            };
                        }
                    }, {
                        test: function (e2) {
                            return "bada" === e2.getBrowserName(true);
                        },
                        describe: function () {
                            return {
                                type: s.PLATFORMS_MAP.mobile
                            };
                        }
                    }, {
                        test: function (e2) {
                            return "windows phone" === e2.getBrowserName();
                        },
                        describe: function () {
                            return {
                                type: s.PLATFORMS_MAP.mobile,
                                vendor: "Microsoft"
                            };
                        }
                    }, {
                        test: function (e2) {
                            var t2 = Number(String(e2.getOSVersion()).split(".")[0]);
                            return "android" === e2.getOSName(true) && t2 >= 3;
                        },
                        describe: function () {
                            return {
                                type: s.PLATFORMS_MAP.tablet
                            };
                        }
                    }, {
                        test: function (e2) {
                            return "android" === e2.getOSName(true);
                        },
                        describe: function () {
                            return {
                                type: s.PLATFORMS_MAP.mobile
                            };
                        }
                    }, {
                        test: function (e2) {
                            return "macos" === e2.getOSName(true);
                        },
                        describe: function () {
                            return {
                                type: s.PLATFORMS_MAP.desktop,
                                vendor: "Apple"
                            };
                        }
                    }, {
                        test: function (e2) {
                            return "windows" === e2.getOSName(true);
                        },
                        describe: function () {
                            return {
                                type: s.PLATFORMS_MAP.desktop
                            };
                        }
                    }, {
                        test: function (e2) {
                            return "linux" === e2.getOSName(true);
                        },
                        describe: function () {
                            return {
                                type: s.PLATFORMS_MAP.desktop
                            };
                        }
                    }, {
                        test: function (e2) {
                            return "playstation 4" === e2.getOSName(true);
                        },
                        describe: function () {
                            return {
                                type: s.PLATFORMS_MAP.tv
                            };
                        }
                    }, {
                        test: function (e2) {
                            return "roku" === e2.getOSName(true);
                        },
                        describe: function () {
                            return {
                                type: s.PLATFORMS_MAP.tv
                            };
                        }
                    }];
                    t.default = a, e.exports = t.default;
                },
                95: function (e, t, r) {
                    "use strict";
                    t.__esModule = true, t.default = void 0;
                    var n, i = (n = r(17)) && n.__esModule ? n : {
                        default: n
                    }, s = r(18);
                    var a = [{
                        test: function (e2) {
                            return "microsoft edge" === e2.getBrowserName(true);
                        },
                        describe: function (e2) {
                            if (/\sedg\//i.test(e2)) return {
                                name: s.ENGINE_MAP.Blink
                            };
                            var t2 = i.default.getFirstMatch(/edge\/(\d+(\.?_?\d+)+)/i, e2);
                            return {
                                name: s.ENGINE_MAP.EdgeHTML,
                                version: t2
                            };
                        }
                    }, {
                        test: [/trident/i],
                        describe: function (e2) {
                            var t2 = {
                                name: s.ENGINE_MAP.Trident
                            }, r2 = i.default.getFirstMatch(/trident\/(\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: function (e2) {
                            return e2.test(/presto/i);
                        },
                        describe: function (e2) {
                            var t2 = {
                                name: s.ENGINE_MAP.Presto
                            }, r2 = i.default.getFirstMatch(/presto\/(\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: function (e2) {
                            var t2 = e2.test(/gecko/i), r2 = e2.test(/like gecko/i);
                            return t2 && !r2;
                        },
                        describe: function (e2) {
                            var t2 = {
                                name: s.ENGINE_MAP.Gecko
                            }, r2 = i.default.getFirstMatch(/gecko\/(\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }, {
                        test: [/(apple)?webkit\/537\.36/i],
                        describe: function () {
                            return {
                                name: s.ENGINE_MAP.Blink
                            };
                        }
                    }, {
                        test: [/(apple)?webkit/i],
                        describe: function (e2) {
                            var t2 = {
                                name: s.ENGINE_MAP.WebKit
                            }, r2 = i.default.getFirstMatch(/webkit\/(\d+(\.?_?\d+)+)/i, e2);
                            return r2 && (t2.version = r2), t2;
                        }
                    }];
                    t.default = a, e.exports = t.default;
                }
            });
        });
    }
});

// src/app/shared/byte-utils.component.ts
function byteConversion(bytes, decimals = 2) {
    if (bytes === 0 || bytes === void 0)
        return "0";
    const kiloByte = 1024;
    const decimal = decimals < 0 ? 0 : decimals;
    const sizes = ["bytes", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"];
    const i = Math.floor(Math.log(bytes) / Math.log(kiloByte));
    return `${parseFloat((bytes / kiloByte ** i).toFixed(decimal))} ${sizes[i]}`;
}

// node_modules/@smithy/protocol-http/dist-es/extensions/httpExtensionConfiguration.js
var getHttpHandlerExtensionConfiguration = (runtimeConfig) => {
    let httpHandler = runtimeConfig.httpHandler;
    return {
        setHttpHandler(handler) {
            httpHandler = handler;
        },
        httpHandler() {
            return httpHandler;
        },
        updateHttpClientConfig(key, value) {
            httpHandler.updateHttpClientConfig(key, value);
        },
        httpHandlerConfigs() {
            return httpHandler.httpHandlerConfigs();
        }
    };
};
var resolveHttpHandlerRuntimeConfig = (httpHandlerExtensionConfiguration) => {
    return {
        httpHandler: httpHandlerExtensionConfiguration.httpHandler()
    };
};

// node_modules/@smithy/types/dist-es/auth/auth.js
var HttpAuthLocation;
(function (HttpAuthLocation2) {
    HttpAuthLocation2["HEADER"] = "header";
    HttpAuthLocation2["QUERY"] = "query";
})(HttpAuthLocation || (HttpAuthLocation = {}));

// node_modules/@smithy/types/dist-es/auth/HttpApiKeyAuth.js
var HttpApiKeyAuthLocation;
(function (HttpApiKeyAuthLocation2) {
    HttpApiKeyAuthLocation2["HEADER"] = "header";
    HttpApiKeyAuthLocation2["QUERY"] = "query";
})(HttpApiKeyAuthLocation || (HttpApiKeyAuthLocation = {}));

// node_modules/@smithy/types/dist-es/endpoint.js
var EndpointURLScheme;
(function (EndpointURLScheme2) {
    EndpointURLScheme2["HTTP"] = "http";
    EndpointURLScheme2["HTTPS"] = "https";
})(EndpointURLScheme || (EndpointURLScheme = {}));

// node_modules/@smithy/types/dist-es/extensions/checksum.js
var AlgorithmId;
(function (AlgorithmId2) {
    AlgorithmId2["MD5"] = "md5";
    AlgorithmId2["CRC32"] = "crc32";
    AlgorithmId2["CRC32C"] = "crc32c";
    AlgorithmId2["SHA1"] = "sha1";
    AlgorithmId2["SHA256"] = "sha256";
})(AlgorithmId || (AlgorithmId = {}));

// node_modules/@smithy/types/dist-es/http.js
var FieldPosition;
(function (FieldPosition2) {
    FieldPosition2[FieldPosition2["HEADER"] = 0] = "HEADER";
    FieldPosition2[FieldPosition2["TRAILER"] = 1] = "TRAILER";
})(FieldPosition || (FieldPosition = {}));

// node_modules/@smithy/types/dist-es/middleware.js
var SMITHY_CONTEXT_KEY = "__smithy_context";

// node_modules/@smithy/types/dist-es/profile.js
var IniSectionType;
(function (IniSectionType2) {
    IniSectionType2["PROFILE"] = "profile";
    IniSectionType2["SSO_SESSION"] = "sso-session";
    IniSectionType2["SERVICES"] = "services";
})(IniSectionType || (IniSectionType = {}));

// node_modules/@smithy/types/dist-es/transfer.js
var RequestHandlerProtocol;
(function (RequestHandlerProtocol2) {
    RequestHandlerProtocol2["HTTP_0_9"] = "http/0.9";
    RequestHandlerProtocol2["HTTP_1_0"] = "http/1.0";
    RequestHandlerProtocol2["TDS_8_0"] = "tds/8.0";
})(RequestHandlerProtocol || (RequestHandlerProtocol = {}));

// node_modules/@smithy/protocol-http/dist-es/httpRequest.js
var HttpRequest = class _HttpRequest {
    constructor(options) {
        this.method = options.method || "GET";
        this.hostname = options.hostname || "localhost";
        this.port = options.port;
        this.query = options.query || {};
        this.headers = options.headers || {};
        this.body = options.body;
        this.protocol = options.protocol ? options.protocol.slice(-1) !== ":" ? `${options.protocol}:` : options.protocol : "https:";
        this.path = options.path ? options.path.charAt(0) !== "/" ? `/${options.path}` : options.path : "/";
        this.username = options.username;
        this.password = options.password;
        this.fragment = options.fragment;
    }

    static clone(request) {
        const cloned = new _HttpRequest(__spreadProps(__spreadValues({}, request), {
            headers: __spreadValues({}, request.headers)
        }));
        if (cloned.query) {
            cloned.query = cloneQuery(cloned.query);
        }
        return cloned;
    }

    static isInstance(request) {
        if (!request) {
            return false;
        }
        const req = request;
        return "method" in req && "protocol" in req && "hostname" in req && "path" in req && typeof req["query"] === "object" && typeof req["headers"] === "object";
    }

    clone() {
        return _HttpRequest.clone(this);
    }
};

function cloneQuery(query) {
    return Object.keys(query).reduce((carry, paramName) => {
        const param = query[paramName];
        return __spreadProps(__spreadValues({}, carry), {
            [paramName]: Array.isArray(param) ? [...param] : param
        });
    }, {});
}

// node_modules/@smithy/protocol-http/dist-es/httpResponse.js
var HttpResponse = class {
    constructor(options) {
        this.statusCode = options.statusCode;
        this.reason = options.reason;
        this.headers = options.headers || {};
        this.body = options.body;
    }

    static isInstance(response) {
        if (!response) return false;
        const resp = response;
        return typeof resp.statusCode === "number" && typeof resp.headers === "object";
    }
};

// node_modules/@aws-sdk/middleware-host-header/dist-es/index.js
function resolveHostHeaderConfig(input) {
    return input;
}

var hostHeaderMiddleware = (options) => (next) => (args) => __async(void 0, null, function* () {
    if (!HttpRequest.isInstance(args.request)) return next(args);
    const {
        request
    } = args;
    const {
        handlerProtocol = ""
    } = options.requestHandler.metadata || {};
    if (handlerProtocol.indexOf("h2") >= 0 && !request.headers[":authority"]) {
        delete request.headers["host"];
        request.headers[":authority"] = request.hostname + (request.port ? ":" + request.port : "");
    } else if (!request.headers["host"]) {
        let host = request.hostname;
        if (request.port != null) host += `:${request.port}`;
        request.headers["host"] = host;
    }
    return next(args);
});
var hostHeaderMiddlewareOptions = {
    name: "hostHeaderMiddleware",
    step: "build",
    priority: "low",
    tags: ["HOST"],
    override: true
};
var getHostHeaderPlugin = (options) => ({
    applyToStack: (clientStack) => {
        clientStack.add(hostHeaderMiddleware(options), hostHeaderMiddlewareOptions);
    }
});

// node_modules/@aws-sdk/middleware-logger/dist-es/loggerMiddleware.js
var loggerMiddleware = () => (next, context) => (args) => __async(void 0, null, function* () {
    try {
        const response = yield next(args);
        const {
            clientName,
            commandName,
            logger: logger2,
            dynamoDbDocumentClientOptions = {}
        } = context;
        const {
            overrideInputFilterSensitiveLog,
            overrideOutputFilterSensitiveLog
        } = dynamoDbDocumentClientOptions;
        const inputFilterSensitiveLog = overrideInputFilterSensitiveLog ?? context.inputFilterSensitiveLog;
        const outputFilterSensitiveLog = overrideOutputFilterSensitiveLog ?? context.outputFilterSensitiveLog;
        const _a = response.output, {
            $metadata
        } = _a, outputWithoutMetadata = __objRest(_a, [
            "$metadata"
        ]);
        logger2?.info?.({
            clientName,
            commandName,
            input: inputFilterSensitiveLog(args.input),
            output: outputFilterSensitiveLog(outputWithoutMetadata),
            metadata: $metadata
        });
        return response;
    } catch (error) {
        const {
            clientName,
            commandName,
            logger: logger2,
            dynamoDbDocumentClientOptions = {}
        } = context;
        const {
            overrideInputFilterSensitiveLog
        } = dynamoDbDocumentClientOptions;
        const inputFilterSensitiveLog = overrideInputFilterSensitiveLog ?? context.inputFilterSensitiveLog;
        logger2?.error?.({
            clientName,
            commandName,
            input: inputFilterSensitiveLog(args.input),
            error,
            metadata: error.$metadata
        });
        throw error;
    }
});
var loggerMiddlewareOptions = {
    name: "loggerMiddleware",
    tags: ["LOGGER"],
    step: "initialize",
    override: true
};
var getLoggerPlugin = (options) => ({
    applyToStack: (clientStack) => {
        clientStack.add(loggerMiddleware(), loggerMiddlewareOptions);
    }
});

// node_modules/@aws-sdk/middleware-recursion-detection/dist-es/index.js
var TRACE_ID_HEADER_NAME = "X-Amzn-Trace-Id";
var ENV_LAMBDA_FUNCTION_NAME = "AWS_LAMBDA_FUNCTION_NAME";
var ENV_TRACE_ID = "_X_AMZN_TRACE_ID";
var recursionDetectionMiddleware = (options) => (next) => (args) => __async(void 0, null, function* () {
    const {
        request
    } = args;
    if (!HttpRequest.isInstance(request) || options.runtime !== "node" || request.headers.hasOwnProperty(TRACE_ID_HEADER_NAME)) {
        return next(args);
    }
    const functionName = process.env[ENV_LAMBDA_FUNCTION_NAME];
    const traceId = process.env[ENV_TRACE_ID];
    const nonEmptyString = (str) => typeof str === "string" && str.length > 0;
    if (nonEmptyString(functionName) && nonEmptyString(traceId)) {
        request.headers[TRACE_ID_HEADER_NAME] = traceId;
    }
    return next(__spreadProps(__spreadValues({}, args), {
        request
    }));
});
var addRecursionDetectionMiddlewareOptions = {
    step: "build",
    tags: ["RECURSION_DETECTION"],
    name: "recursionDetectionMiddleware",
    override: true,
    priority: "low"
};
var getRecursionDetectionPlugin = (options) => ({
    applyToStack: (clientStack) => {
        clientStack.add(recursionDetectionMiddleware(options), addRecursionDetectionMiddlewareOptions);
    }
});

// node_modules/@smithy/middleware-stack/dist-es/MiddlewareStack.js
var getAllAliases = (name, aliases) => {
    const _aliases = [];
    if (name) {
        _aliases.push(name);
    }
    if (aliases) {
        for (const alias of aliases) {
            _aliases.push(alias);
        }
    }
    return _aliases;
};
var getMiddlewareNameWithAliases = (name, aliases) => {
    return `${name || "anonymous"}${aliases && aliases.length > 0 ? ` (a.k.a. ${aliases.join(",")})` : ""}`;
};
var constructStack = () => {
    let absoluteEntries = [];
    let relativeEntries = [];
    let identifyOnResolve = false;
    const entriesNameSet = /* @__PURE__ */ new Set();
    const sort = (entries) => entries.sort((a, b) => stepWeights[b.step] - stepWeights[a.step] || priorityWeights[b.priority || "normal"] - priorityWeights[a.priority || "normal"]);
    const removeByName = (toRemove) => {
        let isRemoved = false;
        const filterCb = (entry) => {
            const aliases = getAllAliases(entry.name, entry.aliases);
            if (aliases.includes(toRemove)) {
                isRemoved = true;
                for (const alias of aliases) {
                    entriesNameSet.delete(alias);
                }
                return false;
            }
            return true;
        };
        absoluteEntries = absoluteEntries.filter(filterCb);
        relativeEntries = relativeEntries.filter(filterCb);
        return isRemoved;
    };
    const removeByReference = (toRemove) => {
        let isRemoved = false;
        const filterCb = (entry) => {
            if (entry.middleware === toRemove) {
                isRemoved = true;
                for (const alias of getAllAliases(entry.name, entry.aliases)) {
                    entriesNameSet.delete(alias);
                }
                return false;
            }
            return true;
        };
        absoluteEntries = absoluteEntries.filter(filterCb);
        relativeEntries = relativeEntries.filter(filterCb);
        return isRemoved;
    };
    const cloneTo = (toStack) => {
        absoluteEntries.forEach((entry) => {
            toStack.add(entry.middleware, __spreadValues({}, entry));
        });
        relativeEntries.forEach((entry) => {
            toStack.addRelativeTo(entry.middleware, __spreadValues({}, entry));
        });
        toStack.identifyOnResolve?.(stack.identifyOnResolve());
        return toStack;
    };
    const expandRelativeMiddlewareList = (from) => {
        const expandedMiddlewareList = [];
        from.before.forEach((entry) => {
            if (entry.before.length === 0 && entry.after.length === 0) {
                expandedMiddlewareList.push(entry);
            } else {
                expandedMiddlewareList.push(...expandRelativeMiddlewareList(entry));
            }
        });
        expandedMiddlewareList.push(from);
        from.after.reverse().forEach((entry) => {
            if (entry.before.length === 0 && entry.after.length === 0) {
                expandedMiddlewareList.push(entry);
            } else {
                expandedMiddlewareList.push(...expandRelativeMiddlewareList(entry));
            }
        });
        return expandedMiddlewareList;
    };
    const getMiddlewareList = (debug = false) => {
        const normalizedAbsoluteEntries = [];
        const normalizedRelativeEntries = [];
        const normalizedEntriesNameMap = {};
        absoluteEntries.forEach((entry) => {
            const normalizedEntry = __spreadProps(__spreadValues({}, entry), {
                before: [],
                after: []
            });
            for (const alias of getAllAliases(normalizedEntry.name, normalizedEntry.aliases)) {
                normalizedEntriesNameMap[alias] = normalizedEntry;
            }
            normalizedAbsoluteEntries.push(normalizedEntry);
        });
        relativeEntries.forEach((entry) => {
            const normalizedEntry = __spreadProps(__spreadValues({}, entry), {
                before: [],
                after: []
            });
            for (const alias of getAllAliases(normalizedEntry.name, normalizedEntry.aliases)) {
                normalizedEntriesNameMap[alias] = normalizedEntry;
            }
            normalizedRelativeEntries.push(normalizedEntry);
        });
        normalizedRelativeEntries.forEach((entry) => {
            if (entry.toMiddleware) {
                const toMiddleware = normalizedEntriesNameMap[entry.toMiddleware];
                if (toMiddleware === void 0) {
                    if (debug) {
                        return;
                    }
                    throw new Error(`${entry.toMiddleware} is not found when adding ${getMiddlewareNameWithAliases(entry.name, entry.aliases)} middleware ${entry.relation} ${entry.toMiddleware}`);
                }
                if (entry.relation === "after") {
                    toMiddleware.after.push(entry);
                }
                if (entry.relation === "before") {
                    toMiddleware.before.push(entry);
                }
            }
        });
        const mainChain = sort(normalizedAbsoluteEntries).map(expandRelativeMiddlewareList).reduce((wholeList, expandedMiddlewareList) => {
            wholeList.push(...expandedMiddlewareList);
            return wholeList;
        }, []);
        return mainChain;
    };
    const stack = {
        add: (middleware, options = {}) => {
            const {
                name,
                override,
                aliases: _aliases
            } = options;
            const entry = __spreadValues({
                step: "initialize",
                priority: "normal",
                middleware
            }, options);
            const aliases = getAllAliases(name, _aliases);
            if (aliases.length > 0) {
                if (aliases.some((alias) => entriesNameSet.has(alias))) {
                    if (!override) throw new Error(`Duplicate middleware name '${getMiddlewareNameWithAliases(name, _aliases)}'`);
                    for (const alias of aliases) {
                        const toOverrideIndex = absoluteEntries.findIndex((entry2) => entry2.name === alias || entry2.aliases?.some((a) => a === alias));
                        if (toOverrideIndex === -1) {
                            continue;
                        }
                        const toOverride = absoluteEntries[toOverrideIndex];
                        if (toOverride.step !== entry.step || entry.priority !== toOverride.priority) {
                            throw new Error(`"${getMiddlewareNameWithAliases(toOverride.name, toOverride.aliases)}" middleware with ${toOverride.priority} priority in ${toOverride.step} step cannot be overridden by "${getMiddlewareNameWithAliases(name, _aliases)}" middleware with ${entry.priority} priority in ${entry.step} step.`);
                        }
                        absoluteEntries.splice(toOverrideIndex, 1);
                    }
                }
                for (const alias of aliases) {
                    entriesNameSet.add(alias);
                }
            }
            absoluteEntries.push(entry);
        },
        addRelativeTo: (middleware, options) => {
            const {
                name,
                override,
                aliases: _aliases
            } = options;
            const entry = __spreadValues({
                middleware
            }, options);
            const aliases = getAllAliases(name, _aliases);
            if (aliases.length > 0) {
                if (aliases.some((alias) => entriesNameSet.has(alias))) {
                    if (!override) throw new Error(`Duplicate middleware name '${getMiddlewareNameWithAliases(name, _aliases)}'`);
                    for (const alias of aliases) {
                        const toOverrideIndex = relativeEntries.findIndex((entry2) => entry2.name === alias || entry2.aliases?.some((a) => a === alias));
                        if (toOverrideIndex === -1) {
                            continue;
                        }
                        const toOverride = relativeEntries[toOverrideIndex];
                        if (toOverride.toMiddleware !== entry.toMiddleware || toOverride.relation !== entry.relation) {
                            throw new Error(`"${getMiddlewareNameWithAliases(toOverride.name, toOverride.aliases)}" middleware ${toOverride.relation} "${toOverride.toMiddleware}" middleware cannot be overridden by "${getMiddlewareNameWithAliases(name, _aliases)}" middleware ${entry.relation} "${entry.toMiddleware}" middleware.`);
                        }
                        relativeEntries.splice(toOverrideIndex, 1);
                    }
                }
                for (const alias of aliases) {
                    entriesNameSet.add(alias);
                }
            }
            relativeEntries.push(entry);
        },
        clone: () => cloneTo(constructStack()),
        use: (plugin) => {
            plugin.applyToStack(stack);
        },
        remove: (toRemove) => {
            if (typeof toRemove === "string") return removeByName(toRemove);
            else return removeByReference(toRemove);
        },
        removeByTag: (toRemove) => {
            let isRemoved = false;
            const filterCb = (entry) => {
                const {
                    tags,
                    name,
                    aliases: _aliases
                } = entry;
                if (tags && tags.includes(toRemove)) {
                    const aliases = getAllAliases(name, _aliases);
                    for (const alias of aliases) {
                        entriesNameSet.delete(alias);
                    }
                    isRemoved = true;
                    return false;
                }
                return true;
            };
            absoluteEntries = absoluteEntries.filter(filterCb);
            relativeEntries = relativeEntries.filter(filterCb);
            return isRemoved;
        },
        concat: (from) => {
            const cloned = cloneTo(constructStack());
            cloned.use(from);
            cloned.identifyOnResolve(identifyOnResolve || cloned.identifyOnResolve() || (from.identifyOnResolve?.() ?? false));
            return cloned;
        },
        applyToStack: cloneTo,
        identify: () => {
            return getMiddlewareList(true).map((mw) => {
                const step = mw.step ?? mw.relation + " " + mw.toMiddleware;
                return getMiddlewareNameWithAliases(mw.name, mw.aliases) + " - " + step;
            });
        },
        identifyOnResolve(toggle) {
            if (typeof toggle === "boolean") identifyOnResolve = toggle;
            return identifyOnResolve;
        },
        resolve: (handler, context) => {
            for (const middleware of getMiddlewareList().map((entry) => entry.middleware).reverse()) {
                handler = middleware(handler, context);
            }
            if (identifyOnResolve) {
                console.log(stack.identify());
            }
            return handler;
        }
    };
    return stack;
};
var stepWeights = {
    initialize: 5,
    serialize: 4,
    build: 3,
    finalizeRequest: 2,
    deserialize: 1
};
var priorityWeights = {
    high: 3,
    normal: 2,
    low: 1
};

// node_modules/@smithy/smithy-client/dist-es/client.js
var Client = class {
    constructor(config) {
        this.config = config;
        this.middlewareStack = constructStack();
    }

    send(command, optionsOrCb, cb) {
        const options = typeof optionsOrCb !== "function" ? optionsOrCb : void 0;
        const callback = typeof optionsOrCb === "function" ? optionsOrCb : cb;
        const useHandlerCache = options === void 0 && this.config.cacheMiddleware === true;
        let handler;
        if (useHandlerCache) {
            if (!this.handlers) {
                this.handlers = /* @__PURE__ */ new WeakMap();
            }
            const handlers = this.handlers;
            if (handlers.has(command.constructor)) {
                handler = handlers.get(command.constructor);
            } else {
                handler = command.resolveMiddleware(this.middlewareStack, this.config, options);
                handlers.set(command.constructor, handler);
            }
        } else {
            delete this.handlers;
            handler = command.resolveMiddleware(this.middlewareStack, this.config, options);
        }
        if (callback) {
            handler(command).then((result) => callback(null, result.output), (err) => callback(err)).catch(() => {
            });
        } else {
            return handler(command).then((result) => result.output);
        }
    }

    destroy() {
        this.config?.requestHandler?.destroy?.();
        delete this.handlers;
    }
};

// node_modules/@smithy/smithy-client/dist-es/command.js
var Command = class {
    constructor() {
        this.middlewareStack = constructStack();
    }

    static classBuilder() {
        return new ClassBuilder();
    }

    resolveMiddlewareWithContext(clientStack, configuration, options, {
        middlewareFn,
        clientName,
        commandName,
        inputFilterSensitiveLog,
        outputFilterSensitiveLog,
        smithyContext,
        additionalContext,
        CommandCtor
    }) {
        for (const mw of middlewareFn.bind(this)(CommandCtor, clientStack, configuration, options)) {
            this.middlewareStack.use(mw);
        }
        const stack = clientStack.concat(this.middlewareStack);
        const {
            logger: logger2
        } = configuration;
        const handlerExecutionContext = __spreadValues({
            logger: logger2,
            clientName,
            commandName,
            inputFilterSensitiveLog,
            outputFilterSensitiveLog,
            [SMITHY_CONTEXT_KEY]: __spreadValues({
                commandInstance: this
            }, smithyContext)
        }, additionalContext);
        const {
            requestHandler
        } = configuration;
        return stack.resolve((request) => requestHandler.handle(request.request, options || {}), handlerExecutionContext);
    }
};
var ClassBuilder = class {
    constructor() {
        this._init = () => {
        };
        this._ep = {};
        this._middlewareFn = () => [];
        this._commandName = "";
        this._clientName = "";
        this._additionalContext = {};
        this._smithyContext = {};
        this._inputFilterSensitiveLog = (_) => _;
        this._outputFilterSensitiveLog = (_) => _;
        this._serializer = null;
        this._deserializer = null;
    }

    init(cb) {
        this._init = cb;
    }

    ep(endpointParameterInstructions) {
        this._ep = endpointParameterInstructions;
        return this;
    }

    m(middlewareSupplier) {
        this._middlewareFn = middlewareSupplier;
        return this;
    }

    s(service, operation, smithyContext = {}) {
        this._smithyContext = __spreadValues({
            service,
            operation
        }, smithyContext);
        return this;
    }

    c(additionalContext = {}) {
        this._additionalContext = additionalContext;
        return this;
    }

    n(clientName, commandName) {
        this._clientName = clientName;
        this._commandName = commandName;
        return this;
    }

    f(inputFilter = (_) => _, outputFilter = (_) => _) {
        this._inputFilterSensitiveLog = inputFilter;
        this._outputFilterSensitiveLog = outputFilter;
        return this;
    }

    ser(serializer) {
        this._serializer = serializer;
        return this;
    }

    de(deserializer) {
        this._deserializer = deserializer;
        return this;
    }

    build() {
        const closure = this;
        let CommandRef;
        return CommandRef = class extends Command {
            constructor(...[input]) {
                super();
                this.serialize = closure._serializer;
                this.deserialize = closure._deserializer;
                this.input = input ?? {};
                closure._init(this);
            }

            static getEndpointParameterInstructions() {
                return closure._ep;
            }

            resolveMiddleware(stack, configuration, options) {
                return this.resolveMiddlewareWithContext(stack, configuration, options, {
                    CommandCtor: CommandRef,
                    middlewareFn: closure._middlewareFn,
                    clientName: closure._clientName,
                    commandName: closure._commandName,
                    inputFilterSensitiveLog: closure._inputFilterSensitiveLog,
                    outputFilterSensitiveLog: closure._outputFilterSensitiveLog,
                    smithyContext: closure._smithyContext,
                    additionalContext: closure._additionalContext
                });
            }
        };
    }
};

// node_modules/@smithy/util-base64/dist-es/constants.browser.js
var alphabetByEncoding = {};
var alphabetByValue = new Array(64);
for (let i = 0, start = "A".charCodeAt(0), limit = "Z".charCodeAt(0); i + start <= limit; i++) {
    const char = String.fromCharCode(i + start);
    alphabetByEncoding[char] = i;
    alphabetByValue[i] = char;
}
for (let i = 0, start = "a".charCodeAt(0), limit = "z".charCodeAt(0); i + start <= limit; i++) {
    const char = String.fromCharCode(i + start);
    const index = i + 26;
    alphabetByEncoding[char] = index;
    alphabetByValue[index] = char;
}
for (let i = 0; i < 10; i++) {
    alphabetByEncoding[i.toString(10)] = i + 52;
    const char = i.toString(10);
    const index = i + 52;
    alphabetByEncoding[char] = index;
    alphabetByValue[index] = char;
}
alphabetByEncoding["+"] = 62;
alphabetByValue[62] = "+";
alphabetByEncoding["/"] = 63;
alphabetByValue[63] = "/";
var bitsPerLetter = 6;
var bitsPerByte = 8;
var maxLetterValue = 63;

// node_modules/@smithy/util-base64/dist-es/fromBase64.browser.js
var fromBase64 = (input) => {
    let totalByteLength = input.length / 4 * 3;
    if (input.slice(-2) === "==") {
        totalByteLength -= 2;
    } else if (input.slice(-1) === "=") {
        totalByteLength--;
    }
    const out = new ArrayBuffer(totalByteLength);
    const dataView = new DataView(out);
    for (let i = 0; i < input.length; i += 4) {
        let bits = 0;
        let bitLength = 0;
        for (let j = i, limit = i + 3; j <= limit; j++) {
            if (input[j] !== "=") {
                if (!(input[j] in alphabetByEncoding)) {
                    throw new TypeError(`Invalid character ${input[j]} in base64 string.`);
                }
                bits |= alphabetByEncoding[input[j]] << (limit - j) * bitsPerLetter;
                bitLength += bitsPerLetter;
            } else {
                bits >>= bitsPerLetter;
            }
        }
        const chunkOffset = i / 4 * 3;
        bits >>= bitLength % bitsPerByte;
        const byteLength = Math.floor(bitLength / bitsPerByte);
        for (let k = 0; k < byteLength; k++) {
            const offset = (byteLength - k - 1) * bitsPerByte;
            dataView.setUint8(chunkOffset + k, (bits & 255 << offset) >> offset);
        }
    }
    return new Uint8Array(out);
};

// node_modules/@smithy/util-utf8/dist-es/fromUtf8.browser.js
var fromUtf8 = (input) => new TextEncoder().encode(input);

// node_modules/@smithy/util-utf8/dist-es/toUint8Array.js
var toUint8Array = (data) => {
    if (typeof data === "string") {
        return fromUtf8(data);
    }
    if (ArrayBuffer.isView(data)) {
        return new Uint8Array(data.buffer, data.byteOffset, data.byteLength / Uint8Array.BYTES_PER_ELEMENT);
    }
    return new Uint8Array(data);
};

// node_modules/@smithy/util-utf8/dist-es/toUtf8.browser.js
var toUtf8 = (input) => {
    if (typeof input === "string") {
        return input;
    }
    if (typeof input !== "object" || typeof input.byteOffset !== "number" || typeof input.byteLength !== "number") {
        throw new Error("@smithy/util-utf8: toUtf8 encoder function only accepts string | Uint8Array.");
    }
    return new TextDecoder("utf-8").decode(input);
};

// node_modules/@smithy/util-base64/dist-es/toBase64.browser.js
function toBase64(_input) {
    let input;
    if (typeof _input === "string") {
        input = fromUtf8(_input);
    } else {
        input = _input;
    }
    const isArrayLike = typeof input === "object" && typeof input.length === "number";
    const isUint8Array = typeof input === "object" && typeof input.byteOffset === "number" && typeof input.byteLength === "number";
    if (!isArrayLike && !isUint8Array) {
        throw new Error("@smithy/util-base64: toBase64 encoder function only accepts string | Uint8Array.");
    }
    let str = "";
    for (let i = 0; i < input.length; i += 3) {
        let bits = 0;
        let bitLength = 0;
        for (let j = i, limit = Math.min(i + 3, input.length); j < limit; j++) {
            bits |= input[j] << (limit - j - 1) * bitsPerByte;
            bitLength += bitsPerByte;
        }
        const bitClusterCount = Math.ceil(bitLength / bitsPerLetter);
        bits <<= bitClusterCount * bitsPerLetter - bitLength;
        for (let k = 1; k <= bitClusterCount; k++) {
            const offset = (bitClusterCount - k) * bitsPerLetter;
            str += alphabetByValue[(bits & maxLetterValue << offset) >> offset];
        }
        str += "==".slice(0, 4 - bitClusterCount);
    }
    return str;
}

// node_modules/@smithy/util-stream/dist-es/blob/transforms.js
function transformToString(payload, encoding = "utf-8") {
    if (encoding === "base64") {
        return toBase64(payload);
    }
    return toUtf8(payload);
}

function transformFromString(str, encoding) {
    if (encoding === "base64") {
        return Uint8ArrayBlobAdapter.mutate(fromBase64(str));
    }
    return Uint8ArrayBlobAdapter.mutate(fromUtf8(str));
}

// node_modules/@smithy/util-stream/dist-es/blob/Uint8ArrayBlobAdapter.js
var Uint8ArrayBlobAdapter = class _Uint8ArrayBlobAdapter extends Uint8Array {
    static fromString(source, encoding = "utf-8") {
        switch (typeof source) {
            case "string":
                return transformFromString(source, encoding);
            default:
                throw new Error(`Unsupported conversion from ${typeof source} to Uint8ArrayBlobAdapter.`);
        }
    }

    static mutate(source) {
        Object.setPrototypeOf(source, _Uint8ArrayBlobAdapter.prototype);
        return source;
    }

    transformToString(encoding = "utf-8") {
        return transformToString(this, encoding);
    }
};

// node_modules/@smithy/util-stream/dist-es/getAwsChunkedEncodingStream.browser.js
var getAwsChunkedEncodingStream = (readableStream, options) => {
    const {
        base64Encoder,
        bodyLengthChecker,
        checksumAlgorithmFn,
        checksumLocationName,
        streamHasher
    } = options;
    const checksumRequired = base64Encoder !== void 0 && bodyLengthChecker !== void 0 && checksumAlgorithmFn !== void 0 && checksumLocationName !== void 0 && streamHasher !== void 0;
    const digest = checksumRequired ? streamHasher(checksumAlgorithmFn, readableStream) : void 0;
    const reader = readableStream.getReader();
    return new ReadableStream({
        pull(controller) {
            return __async(this, null, function* () {
                const {
                    value,
                    done
                } = yield reader.read();
                if (done) {
                    controller.enqueue(`0\r
`);
                    if (checksumRequired) {
                        const checksum = base64Encoder(yield digest);
                        controller.enqueue(`${checksumLocationName}:${checksum}\r
`);
                        controller.enqueue(`\r
`);
                    }
                    controller.close();
                } else {
                    controller.enqueue(`${(bodyLengthChecker(value) || 0).toString(16)}\r
${value}\r
`);
                }
            });
        }
    });
};

// node_modules/@smithy/util-uri-escape/dist-es/escape-uri.js
var escapeUri = (uri) => encodeURIComponent(uri).replace(/[!'()*]/g, hexEncode);
var hexEncode = (c) => `%${c.charCodeAt(0).toString(16).toUpperCase()}`;

// node_modules/@smithy/querystring-builder/dist-es/index.js
function buildQueryString(query) {
    const parts = [];
    for (let key of Object.keys(query).sort()) {
        const value = query[key];
        key = escapeUri(key);
        if (Array.isArray(value)) {
            for (let i = 0, iLen = value.length; i < iLen; i++) {
                parts.push(`${key}=${escapeUri(value[i])}`);
            }
        } else {
            let qsEntry = key;
            if (value || typeof value === "string") {
                qsEntry += `=${escapeUri(value)}`;
            }
            parts.push(qsEntry);
        }
    }
    return parts.join("&");
}

// node_modules/@smithy/fetch-http-handler/dist-es/create-request.js
function createRequest(url, requestOptions) {
    return new Request(url, requestOptions);
}

// node_modules/@smithy/fetch-http-handler/dist-es/request-timeout.js
function requestTimeout(timeoutInMs = 0) {
    return new Promise((resolve, reject) => {
        if (timeoutInMs) {
            setTimeout(() => {
                const timeoutError = new Error(`Request did not complete within ${timeoutInMs} ms`);
                timeoutError.name = "TimeoutError";
                reject(timeoutError);
            }, timeoutInMs);
        }
    });
}

// node_modules/@smithy/fetch-http-handler/dist-es/fetch-http-handler.js
var keepAliveSupport = {
    supported: void 0
};
var FetchHttpHandler = class _FetchHttpHandler {
    constructor(options) {
        if (typeof options === "function") {
            this.configProvider = options().then((opts) => opts || {});
        } else {
            this.config = options ?? {};
            this.configProvider = Promise.resolve(this.config);
        }
        if (keepAliveSupport.supported === void 0) {
            keepAliveSupport.supported = Boolean(typeof Request !== "undefined" && "keepalive" in createRequest("https://[::1]"));
        }
    }

    static create(instanceOrOptions) {
        if (typeof instanceOrOptions?.handle === "function") {
            return instanceOrOptions;
        }
        return new _FetchHttpHandler(instanceOrOptions);
    }

    destroy() {
    }

    handle(_0) {
        return __async(this, arguments, function* (request, {
            abortSignal
        } = {}) {
            if (!this.config) {
                this.config = yield this.configProvider;
            }
            const requestTimeoutInMs = this.config.requestTimeout;
            const keepAlive = this.config.keepAlive === true;
            const credentials = this.config.credentials;
            if (abortSignal?.aborted) {
                const abortError = new Error("Request aborted");
                abortError.name = "AbortError";
                return Promise.reject(abortError);
            }
            let path = request.path;
            const queryString = buildQueryString(request.query || {});
            if (queryString) {
                path += `?${queryString}`;
            }
            if (request.fragment) {
                path += `#${request.fragment}`;
            }
            let auth = "";
            if (request.username != null || request.password != null) {
                const username = request.username ?? "";
                const password = request.password ?? "";
                auth = `${username}:${password}@`;
            }
            const {
                port,
                method
            } = request;
            const url = `${request.protocol}//${auth}${request.hostname}${port ? `:${port}` : ""}${path}`;
            const body = method === "GET" || method === "HEAD" ? void 0 : request.body;
            const requestOptions = {
                body,
                headers: new Headers(request.headers),
                method,
                credentials
            };
            if (this.config?.cache) {
                requestOptions.cache = this.config.cache;
            }
            if (body) {
                requestOptions.duplex = "half";
            }
            if (typeof AbortController !== "undefined") {
                requestOptions.signal = abortSignal;
            }
            if (keepAliveSupport.supported) {
                requestOptions.keepalive = keepAlive;
            }
            if (typeof this.config.requestInit === "function") {
                Object.assign(requestOptions, this.config.requestInit(request));
            }
            let removeSignalEventListener = () => {
            };
            const fetchRequest = createRequest(url, requestOptions);
            const raceOfPromises = [fetch(fetchRequest).then((response) => {
                const fetchHeaders = response.headers;
                const transformedHeaders = {};
                for (const pair of fetchHeaders.entries()) {
                    transformedHeaders[pair[0]] = pair[1];
                }
                const hasReadableStream = response.body != void 0;
                if (!hasReadableStream) {
                    return response.blob().then((body2) => ({
                        response: new HttpResponse({
                            headers: transformedHeaders,
                            reason: response.statusText,
                            statusCode: response.status,
                            body: body2
                        })
                    }));
                }
                return {
                    response: new HttpResponse({
                        headers: transformedHeaders,
                        reason: response.statusText,
                        statusCode: response.status,
                        body: response.body
                    })
                };
            }), requestTimeout(requestTimeoutInMs)];
            if (abortSignal) {
                raceOfPromises.push(new Promise((resolve, reject) => {
                    const onAbort = () => {
                        const abortError = new Error("Request aborted");
                        abortError.name = "AbortError";
                        reject(abortError);
                    };
                    if (typeof abortSignal.addEventListener === "function") {
                        const signal = abortSignal;
                        signal.addEventListener("abort", onAbort, {
                            once: true
                        });
                        removeSignalEventListener = () => signal.removeEventListener("abort", onAbort);
                    } else {
                        abortSignal.onabort = onAbort;
                    }
                }));
            }
            return Promise.race(raceOfPromises).finally(removeSignalEventListener);
        });
    }

    updateHttpClientConfig(key, value) {
        this.config = void 0;
        this.configProvider = this.configProvider.then((config) => {
            config[key] = value;
            return config;
        });
    }

    httpHandlerConfigs() {
        return this.config ?? {};
    }
};

// node_modules/@smithy/fetch-http-handler/dist-es/stream-collector.js
var streamCollector = (stream) => __async(void 0, null, function* () {
    if (typeof Blob === "function" && stream instanceof Blob || stream.constructor?.name === "Blob") {
        return new Uint8Array(yield stream.arrayBuffer());
    }
    return collectStream(stream);
});

function collectStream(stream) {
    return __async(this, null, function* () {
        const chunks = [];
        const reader = stream.getReader();
        let isDone = false;
        let length = 0;
        while (!isDone) {
            const {
                done,
                value
            } = yield reader.read();
            if (value) {
                chunks.push(value);
                length += value.length;
            }
            isDone = done;
        }
        const collected = new Uint8Array(length);
        let offset = 0;
        for (const chunk of chunks) {
            collected.set(chunk, offset);
            offset += chunk.length;
        }
        return collected;
    });
}

// node_modules/@smithy/util-hex-encoding/dist-es/index.js
var SHORT_TO_HEX = {};
var HEX_TO_SHORT = {};
for (let i = 0; i < 256; i++) {
    let encodedByte = i.toString(16).toLowerCase();
    if (encodedByte.length === 1) {
        encodedByte = `0${encodedByte}`;
    }
    SHORT_TO_HEX[i] = encodedByte;
    HEX_TO_SHORT[encodedByte] = i;
}

function fromHex(encoded) {
    if (encoded.length % 2 !== 0) {
        throw new Error("Hex encoded strings must have an even number length");
    }
    const out = new Uint8Array(encoded.length / 2);
    for (let i = 0; i < encoded.length; i += 2) {
        const encodedByte = encoded.slice(i, i + 2).toLowerCase();
        if (encodedByte in HEX_TO_SHORT) {
            out[i / 2] = HEX_TO_SHORT[encodedByte];
        } else {
            throw new Error(`Cannot decode unrecognized sequence ${encodedByte} as hexadecimal`);
        }
    }
    return out;
}

function toHex(bytes) {
    let out = "";
    for (let i = 0; i < bytes.byteLength; i++) {
        out += SHORT_TO_HEX[bytes[i]];
    }
    return out;
}

// node_modules/@smithy/util-stream/dist-es/stream-type-check.js
var isReadableStream = (stream) => typeof ReadableStream === "function" && (stream?.constructor?.name === ReadableStream.name || stream instanceof ReadableStream);

// node_modules/@smithy/util-stream/dist-es/sdk-stream-mixin.browser.js
var ERR_MSG_STREAM_HAS_BEEN_TRANSFORMED = "The stream has already been transformed.";
var sdkStreamMixin = (stream) => {
    if (!isBlobInstance(stream) && !isReadableStream(stream)) {
        const name = stream?.__proto__?.constructor?.name || stream;
        throw new Error(`Unexpected stream implementation, expect Blob or ReadableStream, got ${name}`);
    }
    let transformed = false;
    const transformToByteArray = () => __async(void 0, null, function* () {
        if (transformed) {
            throw new Error(ERR_MSG_STREAM_HAS_BEEN_TRANSFORMED);
        }
        transformed = true;
        return yield streamCollector(stream);
    });
    const blobToWebStream = (blob) => {
        if (typeof blob.stream !== "function") {
            throw new Error("Cannot transform payload Blob to web stream. Please make sure the Blob.stream() is polyfilled.\nIf you are using React Native, this API is not yet supported, see: https://react-native.canny.io/feature-requests/p/fetch-streaming-body");
        }
        return blob.stream();
    };
    return Object.assign(stream, {
        transformToByteArray,
        transformToString: (encoding) => __async(void 0, null, function* () {
            const buf = yield transformToByteArray();
            if (encoding === "base64") {
                return toBase64(buf);
            } else if (encoding === "hex") {
                return toHex(buf);
            } else if (encoding === void 0 || encoding === "utf8" || encoding === "utf-8") {
                return toUtf8(buf);
            } else if (typeof TextDecoder === "function") {
                return new TextDecoder(encoding).decode(buf);
            } else {
                throw new Error("TextDecoder is not available, please make sure polyfill is provided.");
            }
        }),
        transformToWebStream: () => {
            if (transformed) {
                throw new Error(ERR_MSG_STREAM_HAS_BEEN_TRANSFORMED);
            }
            transformed = true;
            if (isBlobInstance(stream)) {
                return blobToWebStream(stream);
            } else if (isReadableStream(stream)) {
                return stream;
            } else {
                throw new Error(`Cannot transform payload to web stream, got ${stream}`);
            }
        }
    });
};
var isBlobInstance = (stream) => typeof Blob === "function" && stream instanceof Blob;

// node_modules/@smithy/util-stream/dist-es/splitStream.browser.js
function splitStream(stream) {
    return __async(this, null, function* () {
        if (typeof stream.stream === "function") {
            stream = stream.stream();
        }
        const readableStream = stream;
        return readableStream.tee();
    });
}

// node_modules/@smithy/util-stream/dist-es/headStream.browser.js
function headStream(stream, bytes) {
    return __async(this, null, function* () {
        let byteLengthCounter = 0;
        const chunks = [];
        const reader = stream.getReader();
        let isDone = false;
        while (!isDone) {
            const {
                done,
                value
            } = yield reader.read();
            if (value) {
                chunks.push(value);
                byteLengthCounter += value?.byteLength ?? 0;
            }
            if (byteLengthCounter >= bytes) {
                break;
            }
            isDone = done;
        }
        reader.releaseLock();
        const collected = new Uint8Array(Math.min(bytes, byteLengthCounter));
        let offset = 0;
        for (const chunk of chunks) {
            if (chunk.byteLength > collected.byteLength - offset) {
                collected.set(chunk.subarray(0, collected.byteLength - offset), offset);
                break;
            } else {
                collected.set(chunk, offset);
            }
            offset += chunk.length;
        }
        return collected;
    });
}

// node_modules/@smithy/util-stream/dist-es/checksum/ChecksumStream.browser.js
var ReadableStreamRef = typeof ReadableStream === "function" ? ReadableStream : function () {
};
var ChecksumStream = class extends ReadableStreamRef {
};

// node_modules/@smithy/util-stream/dist-es/checksum/createChecksumStream.browser.js
var createChecksumStream = ({
                                expectedChecksum,
                                checksum,
                                source,
                                checksumSourceLocation,
                                base64Encoder
                            }) => {
    if (!isReadableStream(source)) {
        throw new Error(`@smithy/util-stream: unsupported source type ${source?.constructor?.name ?? source} in ChecksumStream.`);
    }
    const encoder = base64Encoder ?? toBase64;
    if (typeof TransformStream !== "function") {
        throw new Error("@smithy/util-stream: unable to instantiate ChecksumStream because API unavailable: ReadableStream/TransformStream.");
    }
    const transform = new TransformStream({
        start() {
        },
        transform(chunk, controller) {
            return __async(this, null, function* () {
                checksum.update(chunk);
                controller.enqueue(chunk);
            });
        },
        flush(controller) {
            return __async(this, null, function* () {
                const digest = yield checksum.digest();
                const received = encoder(digest);
                if (expectedChecksum !== received) {
                    const error = new Error(`Checksum mismatch: expected "${expectedChecksum}" but received "${received}" in response header "${checksumSourceLocation}".`);
                    controller.error(error);
                } else {
                    controller.terminate();
                }
            });
        }
    });
    source.pipeThrough(transform);
    const readable = transform.readable;
    Object.setPrototypeOf(readable, ChecksumStream.prototype);
    return readable;
};

// node_modules/@smithy/core/dist-es/submodules/protocols/collect-stream-body.js
var collectBody = (..._0) => __async(void 0, [..._0], function* (streamBody = new Uint8Array(), context) {
    if (streamBody instanceof Uint8Array) {
        return Uint8ArrayBlobAdapter.mutate(streamBody);
    }
    if (!streamBody) {
        return Uint8ArrayBlobAdapter.mutate(new Uint8Array());
    }
    const fromContext = context.streamCollector(streamBody);
    return Uint8ArrayBlobAdapter.mutate(yield fromContext);
});

// node_modules/@smithy/core/dist-es/submodules/protocols/extended-encode-uri-component.js
function extendedEncodeURIComponent(str) {
    return encodeURIComponent(str).replace(/[!'()*]/g, function (c) {
        return "%" + c.charCodeAt(0).toString(16).toUpperCase();
    });
}

// node_modules/@smithy/core/dist-es/submodules/protocols/resolve-path.js
var resolvedPath = (resolvedPath2, input, memberName, labelValueProvider, uriLabel, isGreedyLabel) => {
    if (input != null && input[memberName] !== void 0) {
        const labelValue = labelValueProvider();
        if (labelValue.length <= 0) {
            throw new Error("Empty value provided for input HTTP label: " + memberName + ".");
        }
        resolvedPath2 = resolvedPath2.replace(uriLabel, isGreedyLabel ? labelValue.split("/").map((segment) => extendedEncodeURIComponent(segment)).join("/") : extendedEncodeURIComponent(labelValue));
    } else {
        throw new Error("No value provided for input HTTP label: " + memberName + ".");
    }
    return resolvedPath2;
};

// node_modules/@smithy/core/dist-es/submodules/protocols/requestBuilder.js
function requestBuilder(input, context) {
    return new RequestBuilder(input, context);
}

var RequestBuilder = class {
    constructor(input, context) {
        this.input = input;
        this.context = context;
        this.query = {};
        this.method = "";
        this.headers = {};
        this.path = "";
        this.body = null;
        this.hostname = "";
        this.resolvePathStack = [];
    }

    build() {
        return __async(this, null, function* () {
            const {
                hostname,
                protocol = "https",
                port,
                path: basePath
            } = yield this.context.endpoint();
            this.path = basePath;
            for (const resolvePath of this.resolvePathStack) {
                resolvePath(this.path);
            }
            return new HttpRequest({
                protocol,
                hostname: this.hostname || hostname,
                port,
                method: this.method,
                path: this.path,
                query: this.query,
                body: this.body,
                headers: this.headers
            });
        });
    }

    hn(hostname) {
        this.hostname = hostname;
        return this;
    }

    bp(uriLabel) {
        this.resolvePathStack.push((basePath) => {
            this.path = `${basePath?.endsWith("/") ? basePath.slice(0, -1) : basePath || ""}` + uriLabel;
        });
        return this;
    }

    p(memberName, labelValueProvider, uriLabel, isGreedyLabel) {
        this.resolvePathStack.push((path) => {
            this.path = resolvedPath(path, this.input, memberName, labelValueProvider, uriLabel, isGreedyLabel);
        });
        return this;
    }

    h(headers) {
        this.headers = headers;
        return this;
    }

    q(query) {
        this.query = query;
        return this;
    }

    b(body) {
        this.body = body;
        return this;
    }

    m(method) {
        this.method = method;
        return this;
    }
};

// node_modules/@smithy/smithy-client/dist-es/constants.js
var SENSITIVE_STRING = "***SensitiveInformation***";

// node_modules/@smithy/smithy-client/dist-es/parse-utils.js
var parseBoolean = (value) => {
    switch (value) {
        case "true":
            return true;
        case "false":
            return false;
        default:
            throw new Error(`Unable to parse boolean value "${value}"`);
    }
};
var expectNumber = (value) => {
    if (value === null || value === void 0) {
        return void 0;
    }
    if (typeof value === "string") {
        const parsed = parseFloat(value);
        if (!Number.isNaN(parsed)) {
            if (String(parsed) !== String(value)) {
                logger.warn(stackTraceWarning(`Expected number but observed string: ${value}`));
            }
            return parsed;
        }
    }
    if (typeof value === "number") {
        return value;
    }
    throw new TypeError(`Expected number, got ${typeof value}: ${value}`);
};
var MAX_FLOAT = Math.ceil(2 ** 127 * (2 - 2 ** -23));
var expectFloat32 = (value) => {
    const expected = expectNumber(value);
    if (expected !== void 0 && !Number.isNaN(expected) && expected !== Infinity && expected !== -Infinity) {
        if (Math.abs(expected) > MAX_FLOAT) {
            throw new TypeError(`Expected 32-bit float, got ${value}`);
        }
    }
    return expected;
};
var expectLong = (value) => {
    if (value === null || value === void 0) {
        return void 0;
    }
    if (Number.isInteger(value) && !Number.isNaN(value)) {
        return value;
    }
    throw new TypeError(`Expected integer, got ${typeof value}: ${value}`);
};
var expectInt32 = (value) => expectSizedInt(value, 32);
var expectShort = (value) => expectSizedInt(value, 16);
var expectByte = (value) => expectSizedInt(value, 8);
var expectSizedInt = (value, size) => {
    const expected = expectLong(value);
    if (expected !== void 0 && castInt(expected, size) !== expected) {
        throw new TypeError(`Expected ${size}-bit integer, got ${value}`);
    }
    return expected;
};
var castInt = (value, size) => {
    switch (size) {
        case 32:
            return Int32Array.of(value)[0];
        case 16:
            return Int16Array.of(value)[0];
        case 8:
            return Int8Array.of(value)[0];
    }
};
var expectNonNull = (value, location) => {
    if (value === null || value === void 0) {
        if (location) {
            throw new TypeError(`Expected a non-null value for ${location}`);
        }
        throw new TypeError("Expected a non-null value");
    }
    return value;
};
var expectObject = (value) => {
    if (value === null || value === void 0) {
        return void 0;
    }
    if (typeof value === "object" && !Array.isArray(value)) {
        return value;
    }
    const receivedType = Array.isArray(value) ? "array" : typeof value;
    throw new TypeError(`Expected object, got ${receivedType}: ${value}`);
};
var expectString = (value) => {
    if (value === null || value === void 0) {
        return void 0;
    }
    if (typeof value === "string") {
        return value;
    }
    if (["boolean", "number", "bigint"].includes(typeof value)) {
        logger.warn(stackTraceWarning(`Expected string, got ${typeof value}: ${value}`));
        return String(value);
    }
    throw new TypeError(`Expected string, got ${typeof value}: ${value}`);
};
var strictParseFloat32 = (value) => {
    if (typeof value == "string") {
        return expectFloat32(parseNumber(value));
    }
    return expectFloat32(value);
};
var NUMBER_REGEX = /(-?(?:0|[1-9]\d*)(?:\.\d+)?(?:[eE][+-]?\d+)?)|(-?Infinity)|(NaN)/g;
var parseNumber = (value) => {
    const matches = value.match(NUMBER_REGEX);
    if (matches === null || matches[0].length !== value.length) {
        throw new TypeError(`Expected real number, got implicit NaN`);
    }
    return parseFloat(value);
};
var strictParseLong = (value) => {
    if (typeof value === "string") {
        return expectLong(parseNumber(value));
    }
    return expectLong(value);
};
var strictParseInt32 = (value) => {
    if (typeof value === "string") {
        return expectInt32(parseNumber(value));
    }
    return expectInt32(value);
};
var strictParseShort = (value) => {
    if (typeof value === "string") {
        return expectShort(parseNumber(value));
    }
    return expectShort(value);
};
var strictParseByte = (value) => {
    if (typeof value === "string") {
        return expectByte(parseNumber(value));
    }
    return expectByte(value);
};
var stackTraceWarning = (message) => {
    return String(new TypeError(message).stack || message).split("\n").slice(0, 5).filter((s) => !s.includes("stackTraceWarning")).join("\n");
};
var logger = {
    warn: console.warn
};

// node_modules/@smithy/smithy-client/dist-es/date-utils.js
var DAYS = ["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"];
var MONTHS = ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"];

function dateToUtcString(date) {
    const year = date.getUTCFullYear();
    const month = date.getUTCMonth();
    const dayOfWeek = date.getUTCDay();
    const dayOfMonthInt = date.getUTCDate();
    const hoursInt = date.getUTCHours();
    const minutesInt = date.getUTCMinutes();
    const secondsInt = date.getUTCSeconds();
    const dayOfMonthString = dayOfMonthInt < 10 ? `0${dayOfMonthInt}` : `${dayOfMonthInt}`;
    const hoursString = hoursInt < 10 ? `0${hoursInt}` : `${hoursInt}`;
    const minutesString = minutesInt < 10 ? `0${minutesInt}` : `${minutesInt}`;
    const secondsString = secondsInt < 10 ? `0${secondsInt}` : `${secondsInt}`;
    return `${DAYS[dayOfWeek]}, ${dayOfMonthString} ${MONTHS[month]} ${year} ${hoursString}:${minutesString}:${secondsString} GMT`;
}

var RFC3339 = new RegExp(/^(\d{4})-(\d{2})-(\d{2})[tT](\d{2}):(\d{2}):(\d{2})(?:\.(\d+))?[zZ]$/);
var RFC3339_WITH_OFFSET = new RegExp(/^(\d{4})-(\d{2})-(\d{2})[tT](\d{2}):(\d{2}):(\d{2})(?:\.(\d+))?(([-+]\d{2}\:\d{2})|[zZ])$/);
var parseRfc3339DateTimeWithOffset = (value) => {
    if (value === null || value === void 0) {
        return void 0;
    }
    if (typeof value !== "string") {
        throw new TypeError("RFC-3339 date-times must be expressed as strings");
    }
    const match = RFC3339_WITH_OFFSET.exec(value);
    if (!match) {
        throw new TypeError("Invalid RFC-3339 date-time value");
    }
    const [_, yearStr, monthStr, dayStr, hours, minutes, seconds, fractionalMilliseconds, offsetStr] = match;
    const year = strictParseShort(stripLeadingZeroes(yearStr));
    const month = parseDateValue(monthStr, "month", 1, 12);
    const day = parseDateValue(dayStr, "day", 1, 31);
    const date = buildDate(year, month, day, {
        hours,
        minutes,
        seconds,
        fractionalMilliseconds
    });
    if (offsetStr.toUpperCase() != "Z") {
        date.setTime(date.getTime() - parseOffsetToMilliseconds(offsetStr));
    }
    return date;
};
var IMF_FIXDATE = new RegExp(/^(?:Mon|Tue|Wed|Thu|Fri|Sat|Sun), (\d{2}) (Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec) (\d{4}) (\d{1,2}):(\d{2}):(\d{2})(?:\.(\d+))? GMT$/);
var RFC_850_DATE = new RegExp(/^(?:Monday|Tuesday|Wednesday|Thursday|Friday|Saturday|Sunday), (\d{2})-(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec)-(\d{2}) (\d{1,2}):(\d{2}):(\d{2})(?:\.(\d+))? GMT$/);
var ASC_TIME = new RegExp(/^(?:Mon|Tue|Wed|Thu|Fri|Sat|Sun) (Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec) ( [1-9]|\d{2}) (\d{1,2}):(\d{2}):(\d{2})(?:\.(\d+))? (\d{4})$/);
var parseRfc7231DateTime = (value) => {
    if (value === null || value === void 0) {
        return void 0;
    }
    if (typeof value !== "string") {
        throw new TypeError("RFC-7231 date-times must be expressed as strings");
    }
    let match = IMF_FIXDATE.exec(value);
    if (match) {
        const [_, dayStr, monthStr, yearStr, hours, minutes, seconds, fractionalMilliseconds] = match;
        return buildDate(strictParseShort(stripLeadingZeroes(yearStr)), parseMonthByShortName(monthStr), parseDateValue(dayStr, "day", 1, 31), {
            hours,
            minutes,
            seconds,
            fractionalMilliseconds
        });
    }
    match = RFC_850_DATE.exec(value);
    if (match) {
        const [_, dayStr, monthStr, yearStr, hours, minutes, seconds, fractionalMilliseconds] = match;
        return adjustRfc850Year(buildDate(parseTwoDigitYear(yearStr), parseMonthByShortName(monthStr), parseDateValue(dayStr, "day", 1, 31), {
            hours,
            minutes,
            seconds,
            fractionalMilliseconds
        }));
    }
    match = ASC_TIME.exec(value);
    if (match) {
        const [_, monthStr, dayStr, hours, minutes, seconds, fractionalMilliseconds, yearStr] = match;
        return buildDate(strictParseShort(stripLeadingZeroes(yearStr)), parseMonthByShortName(monthStr), parseDateValue(dayStr.trimLeft(), "day", 1, 31), {
            hours,
            minutes,
            seconds,
            fractionalMilliseconds
        });
    }
    throw new TypeError("Invalid RFC-7231 date-time value");
};
var buildDate = (year, month, day, time) => {
    const adjustedMonth = month - 1;
    validateDayOfMonth(year, adjustedMonth, day);
    return new Date(Date.UTC(year, adjustedMonth, day, parseDateValue(time.hours, "hour", 0, 23), parseDateValue(time.minutes, "minute", 0, 59), parseDateValue(time.seconds, "seconds", 0, 60), parseMilliseconds(time.fractionalMilliseconds)));
};
var parseTwoDigitYear = (value) => {
    const thisYear = (/* @__PURE__ */ new Date()).getUTCFullYear();
    const valueInThisCentury = Math.floor(thisYear / 100) * 100 + strictParseShort(stripLeadingZeroes(value));
    if (valueInThisCentury < thisYear) {
        return valueInThisCentury + 100;
    }
    return valueInThisCentury;
};
var FIFTY_YEARS_IN_MILLIS = 50 * 365 * 24 * 60 * 60 * 1e3;
var adjustRfc850Year = (input) => {
    if (input.getTime() - (/* @__PURE__ */ new Date()).getTime() > FIFTY_YEARS_IN_MILLIS) {
        return new Date(Date.UTC(input.getUTCFullYear() - 100, input.getUTCMonth(), input.getUTCDate(), input.getUTCHours(), input.getUTCMinutes(), input.getUTCSeconds(), input.getUTCMilliseconds()));
    }
    return input;
};
var parseMonthByShortName = (value) => {
    const monthIdx = MONTHS.indexOf(value);
    if (monthIdx < 0) {
        throw new TypeError(`Invalid month: ${value}`);
    }
    return monthIdx + 1;
};
var DAYS_IN_MONTH = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
var validateDayOfMonth = (year, month, day) => {
    let maxDays = DAYS_IN_MONTH[month];
    if (month === 1 && isLeapYear(year)) {
        maxDays = 29;
    }
    if (day > maxDays) {
        throw new TypeError(`Invalid day for ${MONTHS[month]} in ${year}: ${day}`);
    }
};
var isLeapYear = (year) => {
    return year % 4 === 0 && (year % 100 !== 0 || year % 400 === 0);
};
var parseDateValue = (value, type, lower, upper) => {
    const dateVal = strictParseByte(stripLeadingZeroes(value));
    if (dateVal < lower || dateVal > upper) {
        throw new TypeError(`${type} must be between ${lower} and ${upper}, inclusive`);
    }
    return dateVal;
};
var parseMilliseconds = (value) => {
    if (value === null || value === void 0) {
        return 0;
    }
    return strictParseFloat32("0." + value) * 1e3;
};
var parseOffsetToMilliseconds = (value) => {
    const directionStr = value[0];
    let direction = 1;
    if (directionStr == "+") {
        direction = 1;
    } else if (directionStr == "-") {
        direction = -1;
    } else {
        throw new TypeError(`Offset direction, ${directionStr}, must be "+" or "-"`);
    }
    const hour = Number(value.substring(1, 3));
    const minute = Number(value.substring(4, 6));
    return direction * (hour * 60 + minute) * 60 * 1e3;
};
var stripLeadingZeroes = (value) => {
    let idx = 0;
    while (idx < value.length - 1 && value.charAt(idx) === "0") {
        idx++;
    }
    if (idx === 0) {
        return value;
    }
    return value.slice(idx);
};

// node_modules/@smithy/smithy-client/dist-es/exceptions.js
var ServiceException = class _ServiceException extends Error {
    constructor(options) {
        super(options.message);
        Object.setPrototypeOf(this, _ServiceException.prototype);
        this.name = options.name;
        this.$fault = options.$fault;
        this.$metadata = options.$metadata;
    }
};
var decorateServiceException = (exception, additions = {}) => {
    Object.entries(additions).filter(([, v]) => v !== void 0).forEach(([k, v]) => {
        if (exception[k] == void 0 || exception[k] === "") {
            exception[k] = v;
        }
    });
    const message = exception.message || exception.Message || "UnknownError";
    exception.message = message;
    delete exception.Message;
    return exception;
};

// node_modules/@smithy/smithy-client/dist-es/default-error-handler.js
var throwDefaultError = ({
                             output,
                             parsedBody,
                             exceptionCtor,
                             errorCode
                         }) => {
    const $metadata = deserializeMetadata(output);
    const statusCode = $metadata.httpStatusCode ? $metadata.httpStatusCode + "" : void 0;
    const response = new exceptionCtor({
        name: parsedBody?.code || parsedBody?.Code || errorCode || statusCode || "UnknownError",
        $fault: "client",
        $metadata
    });
    throw decorateServiceException(response, parsedBody);
};
var withBaseException = (ExceptionCtor) => {
    return ({
                output,
                parsedBody,
                errorCode
            }) => {
        throwDefaultError({
            output,
            parsedBody,
            exceptionCtor: ExceptionCtor,
            errorCode
        });
    };
};
var deserializeMetadata = (output) => ({
    httpStatusCode: output.statusCode,
    requestId: output.headers["x-amzn-requestid"] ?? output.headers["x-amzn-request-id"] ?? output.headers["x-amz-request-id"],
    extendedRequestId: output.headers["x-amz-id-2"],
    cfId: output.headers["x-amz-cf-id"]
});

// node_modules/@smithy/smithy-client/dist-es/defaults-mode.js
var loadConfigsForDefaultMode = (mode) => {
    switch (mode) {
        case "standard":
            return {
                retryMode: "standard",
                connectionTimeout: 3100
            };
        case "in-region":
            return {
                retryMode: "standard",
                connectionTimeout: 1100
            };
        case "cross-region":
            return {
                retryMode: "standard",
                connectionTimeout: 3100
            };
        case "mobile":
            return {
                retryMode: "standard",
                connectionTimeout: 3e4
            };
        default:
            return {};
    }
};

// node_modules/@smithy/smithy-client/dist-es/extensions/checksum.js
var getChecksumConfiguration2 = (runtimeConfig) => {
    const checksumAlgorithms = [];
    for (const id in AlgorithmId) {
        const algorithmId = AlgorithmId[id];
        if (runtimeConfig[algorithmId] === void 0) {
            continue;
        }
        checksumAlgorithms.push({
            algorithmId: () => algorithmId,
            checksumConstructor: () => runtimeConfig[algorithmId]
        });
    }
    return {
        _checksumAlgorithms: checksumAlgorithms,
        addChecksumAlgorithm(algo) {
            this._checksumAlgorithms.push(algo);
        },
        checksumAlgorithms() {
            return this._checksumAlgorithms;
        }
    };
};
var resolveChecksumRuntimeConfig2 = (clientConfig) => {
    const runtimeConfig = {};
    clientConfig.checksumAlgorithms().forEach((checksumAlgorithm) => {
        runtimeConfig[checksumAlgorithm.algorithmId()] = checksumAlgorithm.checksumConstructor();
    });
    return runtimeConfig;
};

// node_modules/@smithy/smithy-client/dist-es/extensions/retry.js
var getRetryConfiguration = (runtimeConfig) => {
    let _retryStrategy = runtimeConfig.retryStrategy;
    return {
        setRetryStrategy(retryStrategy) {
            _retryStrategy = retryStrategy;
        },
        retryStrategy() {
            return _retryStrategy;
        }
    };
};
var resolveRetryRuntimeConfig = (retryStrategyConfiguration) => {
    const runtimeConfig = {};
    runtimeConfig.retryStrategy = retryStrategyConfiguration.retryStrategy();
    return runtimeConfig;
};

// node_modules/@smithy/smithy-client/dist-es/extensions/defaultExtensionConfiguration.js
var getDefaultExtensionConfiguration = (runtimeConfig) => {
    return __spreadValues(__spreadValues({}, getChecksumConfiguration2(runtimeConfig)), getRetryConfiguration(runtimeConfig));
};
var resolveDefaultRuntimeConfig = (config) => {
    return __spreadValues(__spreadValues({}, resolveChecksumRuntimeConfig2(config)), resolveRetryRuntimeConfig(config));
};

// node_modules/@smithy/smithy-client/dist-es/get-array-if-single-item.js
var getArrayIfSingleItem = (mayBeArray) => Array.isArray(mayBeArray) ? mayBeArray : [mayBeArray];

// node_modules/@smithy/smithy-client/dist-es/get-value-from-text-node.js
var getValueFromTextNode = (obj) => {
    const textNodeName = "#text";
    for (const key in obj) {
        if (obj.hasOwnProperty(key) && obj[key][textNodeName] !== void 0) {
            obj[key] = obj[key][textNodeName];
        } else if (typeof obj[key] === "object" && obj[key] !== null) {
            obj[key] = getValueFromTextNode(obj[key]);
        }
    }
    return obj;
};

// node_modules/@smithy/smithy-client/dist-es/is-serializable-header-value.js
var isSerializableHeaderValue = (value) => {
    return value != null;
};

// node_modules/@smithy/smithy-client/dist-es/lazy-json.js
var StringWrapper = function () {
    const Class = Object.getPrototypeOf(this).constructor;
    const Constructor = Function.bind.apply(String, [null, ...arguments]);
    const instance = new Constructor();
    Object.setPrototypeOf(instance, Class.prototype);
    return instance;
};
StringWrapper.prototype = Object.create(String.prototype, {
    constructor: {
        value: StringWrapper,
        enumerable: false,
        writable: true,
        configurable: true
    }
});
Object.setPrototypeOf(StringWrapper, String);

// node_modules/@smithy/smithy-client/dist-es/NoOpLogger.js
var NoOpLogger = class {
    trace() {
    }

    debug() {
    }

    info() {
    }

    warn() {
    }

    error() {
    }
};

// node_modules/@smithy/smithy-client/dist-es/object-mapping.js
function map(arg0, arg1, arg2) {
    let target;
    let filter;
    let instructions;
    if (typeof arg1 === "undefined" && typeof arg2 === "undefined") {
        target = {};
        instructions = arg0;
    } else {
        target = arg0;
        if (typeof arg1 === "function") {
            filter = arg1;
            instructions = arg2;
            return mapWithFilter(target, filter, instructions);
        } else {
            instructions = arg1;
        }
    }
    for (const key of Object.keys(instructions)) {
        if (!Array.isArray(instructions[key])) {
            target[key] = instructions[key];
            continue;
        }
        applyInstruction(target, null, instructions, key);
    }
    return target;
}

var take = (source, instructions) => {
    const out = {};
    for (const key in instructions) {
        applyInstruction(out, source, instructions, key);
    }
    return out;
};
var mapWithFilter = (target, filter, instructions) => {
    return map(target, Object.entries(instructions).reduce((_instructions, [key, value]) => {
        if (Array.isArray(value)) {
            _instructions[key] = value;
        } else {
            if (typeof value === "function") {
                _instructions[key] = [filter, value()];
            } else {
                _instructions[key] = [filter, value];
            }
        }
        return _instructions;
    }, {}));
};
var applyInstruction = (target, source, instructions, targetKey) => {
    if (source !== null) {
        let instruction = instructions[targetKey];
        if (typeof instruction === "function") {
            instruction = [, instruction];
        }
        const [filter2 = nonNullish, valueFn = pass, sourceKey = targetKey] = instruction;
        if (typeof filter2 === "function" && filter2(source[sourceKey]) || typeof filter2 !== "function" && !!filter2) {
            target[targetKey] = valueFn(source[sourceKey]);
        }
        return;
    }
    let [filter, value] = instructions[targetKey];
    if (typeof value === "function") {
        let _value;
        const defaultFilterPassed = filter === void 0 && (_value = value()) != null;
        const customFilterPassed = typeof filter === "function" && !!filter(void 0) || typeof filter !== "function" && !!filter;
        if (defaultFilterPassed) {
            target[targetKey] = _value;
        } else if (customFilterPassed) {
            target[targetKey] = value();
        }
    } else {
        const defaultFilterPassed = filter === void 0 && value != null;
        const customFilterPassed = typeof filter === "function" && !!filter(value) || typeof filter !== "function" && !!filter;
        if (defaultFilterPassed || customFilterPassed) {
            target[targetKey] = value;
        }
    }
};
var nonNullish = (_) => _ != null;
var pass = (_) => _;

// node_modules/@smithy/smithy-client/dist-es/quote-header.js
function quoteHeader(part) {
    if (part.includes(",") || part.includes('"')) {
        part = `"${part.replace(/"/g, '\\"')}"`;
    }
    return part;
}

// node_modules/@smithy/smithy-client/dist-es/ser-utils.js
var serializeDateTime = (date) => date.toISOString().replace(".000Z", "Z");

// node_modules/@smithy/smithy-client/dist-es/serde-json.js
var _json = (obj) => {
    if (obj == null) {
        return {};
    }
    if (Array.isArray(obj)) {
        return obj.filter((_) => _ != null).map(_json);
    }
    if (typeof obj === "object") {
        const target = {};
        for (const key of Object.keys(obj)) {
            if (obj[key] == null) {
                continue;
            }
            target[key] = _json(obj[key]);
        }
        return target;
    }
    return obj;
};

// node_modules/@smithy/util-middleware/dist-es/getSmithyContext.js
var getSmithyContext = (context) => context[SMITHY_CONTEXT_KEY] || (context[SMITHY_CONTEXT_KEY] = {});

// node_modules/@smithy/util-middleware/dist-es/normalizeProvider.js
var normalizeProvider = (input) => {
    if (typeof input === "function") return input;
    const promisified = Promise.resolve(input);
    return () => promisified;
};

// node_modules/@smithy/core/dist-es/middleware-http-auth-scheme/httpAuthSchemeMiddleware.js
function convertHttpAuthSchemesToMap(httpAuthSchemes) {
    const map2 = /* @__PURE__ */ new Map();
    for (const scheme of httpAuthSchemes) {
        map2.set(scheme.schemeId, scheme);
    }
    return map2;
}

var httpAuthSchemeMiddleware = (config, mwOptions) => (next, context) => (args) => __async(void 0, null, function* () {
    const options = config.httpAuthSchemeProvider(yield mwOptions.httpAuthSchemeParametersProvider(config, context, args.input));
    const authSchemes = convertHttpAuthSchemesToMap(config.httpAuthSchemes);
    const smithyContext = getSmithyContext(context);
    const failureReasons = [];
    for (const option of options) {
        const scheme = authSchemes.get(option.schemeId);
        if (!scheme) {
            failureReasons.push(`HttpAuthScheme \`${option.schemeId}\` was not enabled for this service.`);
            continue;
        }
        const identityProvider = scheme.identityProvider(yield mwOptions.identityProviderConfigProvider(config));
        if (!identityProvider) {
            failureReasons.push(`HttpAuthScheme \`${option.schemeId}\` did not have an IdentityProvider configured.`);
            continue;
        }
        const {
            identityProperties = {},
            signingProperties = {}
        } = option.propertiesExtractor?.(config, context) || {};
        option.identityProperties = Object.assign(option.identityProperties || {}, identityProperties);
        option.signingProperties = Object.assign(option.signingProperties || {}, signingProperties);
        smithyContext.selectedHttpAuthScheme = {
            httpAuthOption: option,
            identity: yield identityProvider(option.identityProperties),
            signer: scheme.signer
        };
        break;
    }
    if (!smithyContext.selectedHttpAuthScheme) {
        throw new Error(failureReasons.join("\n"));
    }
    return next(args);
});

// node_modules/@smithy/core/dist-es/middleware-http-auth-scheme/getHttpAuthSchemeEndpointRuleSetPlugin.js
var httpAuthSchemeEndpointRuleSetMiddlewareOptions = {
    step: "serialize",
    tags: ["HTTP_AUTH_SCHEME"],
    name: "httpAuthSchemeMiddleware",
    override: true,
    relation: "before",
    toMiddleware: "endpointV2Middleware"
};
var getHttpAuthSchemeEndpointRuleSetPlugin = (config, {
    httpAuthSchemeParametersProvider,
    identityProviderConfigProvider
}) => ({
    applyToStack: (clientStack) => {
        clientStack.addRelativeTo(httpAuthSchemeMiddleware(config, {
            httpAuthSchemeParametersProvider,
            identityProviderConfigProvider
        }), httpAuthSchemeEndpointRuleSetMiddlewareOptions);
    }
});

// node_modules/@smithy/middleware-serde/dist-es/deserializerMiddleware.js
var deserializerMiddleware = (options, deserializer) => (next) => (args) => __async(void 0, null, function* () {
    const {
        response
    } = yield next(args);
    try {
        const parsed = yield deserializer(response, options);
        return {
            response,
            output: parsed
        };
    } catch (error) {
        Object.defineProperty(error, "$response", {
            value: response
        });
        if (!("$metadata" in error)) {
            const hint = `Deserialization error: to see the raw response, inspect the hidden field {error}.$response on this object.`;
            error.message += "\n  " + hint;
            if (typeof error.$responseBodyText !== "undefined") {
                if (error.$response) {
                    error.$response.body = error.$responseBodyText;
                }
            }
        }
        throw error;
    }
});

// node_modules/@smithy/middleware-serde/dist-es/serializerMiddleware.js
var serializerMiddleware = (options, serializer) => (next, context) => (args) => __async(void 0, null, function* () {
    const endpoint = context.endpointV2?.url && options.urlParser ? () => __async(void 0, null, function* () {
        return options.urlParser(context.endpointV2.url);
    }) : options.endpoint;
    if (!endpoint) {
        throw new Error("No valid endpoint provider available.");
    }
    const request = yield serializer(args.input, __spreadProps(__spreadValues({}, options), {
        endpoint
    }));
    return next(__spreadProps(__spreadValues({}, args), {
        request
    }));
});

// node_modules/@smithy/middleware-serde/dist-es/serdePlugin.js
var deserializerMiddlewareOption = {
    name: "deserializerMiddleware",
    step: "deserialize",
    tags: ["DESERIALIZER"],
    override: true
};
var serializerMiddlewareOption = {
    name: "serializerMiddleware",
    step: "serialize",
    tags: ["SERIALIZER"],
    override: true
};

function getSerdePlugin(config, serializer, deserializer) {
    return {
        applyToStack: (commandStack) => {
            commandStack.add(deserializerMiddleware(config, deserializer), deserializerMiddlewareOption);
            commandStack.add(serializerMiddleware(config, serializer), serializerMiddlewareOption);
        }
    };
}

// node_modules/@smithy/core/dist-es/middleware-http-signing/httpSigningMiddleware.js
var defaultErrorHandler = (signingProperties) => (error) => {
    throw error;
};
var defaultSuccessHandler = (httpResponse, signingProperties) => {
};
var httpSigningMiddleware = (config) => (next, context) => (args) => __async(void 0, null, function* () {
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
    const output = yield next(__spreadProps(__spreadValues({}, args), {
        request: yield signer.sign(args.request, identity, signingProperties)
    })).catch((signer.errorHandler || defaultErrorHandler)(signingProperties));
    (signer.successHandler || defaultSuccessHandler)(output.response, signingProperties);
    return output;
});

// node_modules/@smithy/core/dist-es/middleware-http-signing/getHttpSigningMiddleware.js
var httpSigningMiddlewareOptions = {
    step: "finalizeRequest",
    tags: ["HTTP_SIGNING"],
    name: "httpSigningMiddleware",
    aliases: ["apiKeyMiddleware", "tokenMiddleware", "awsAuthMiddleware"],
    override: true,
    relation: "after",
    toMiddleware: "retryMiddleware"
};
var getHttpSigningPlugin = (config) => ({
    applyToStack: (clientStack) => {
        clientStack.addRelativeTo(httpSigningMiddleware(config), httpSigningMiddlewareOptions);
    }
});

// node_modules/@smithy/core/dist-es/util-identity-and-auth/DefaultIdentityProviderConfig.js
var DefaultIdentityProviderConfig = class {
    constructor(config) {
        this.authSchemes = /* @__PURE__ */ new Map();
        for (const [key, value] of Object.entries(config)) {
            if (value !== void 0) {
                this.authSchemes.set(key, value);
            }
        }
    }

    getIdentityProvider(schemeId) {
        return this.authSchemes.get(schemeId);
    }
};

// node_modules/@smithy/core/dist-es/middleware-http-auth-scheme/getHttpAuthSchemePlugin.js
var httpAuthSchemeMiddlewareOptions = {
    step: "serialize",
    tags: ["HTTP_AUTH_SCHEME"],
    name: "httpAuthSchemeMiddleware",
    override: true,
    relation: "before",
    toMiddleware: serializerMiddlewareOption.name
};

// node_modules/@smithy/core/dist-es/normalizeProvider.js
var normalizeProvider2 = (input) => {
    if (typeof input === "function") return input;
    const promisified = Promise.resolve(input);
    return () => promisified;
};

// node_modules/@smithy/core/dist-es/setFeature.js
function setFeature(context, feature, value) {
    if (!context.__smithy_context) {
        context.__smithy_context = {
            features: {}
        };
    } else if (!context.__smithy_context.features) {
        context.__smithy_context.features = {};
    }
    context.__smithy_context.features[feature] = value;
}

// node_modules/@smithy/core/dist-es/util-identity-and-auth/memoizeIdentityProvider.js
var createIsIdentityExpiredFunction = (expirationMs) => (identity) => doesIdentityRequireRefresh(identity) && identity.expiration.getTime() - Date.now() < expirationMs;
var EXPIRATION_MS = 3e5;
var isIdentityExpired = createIsIdentityExpiredFunction(EXPIRATION_MS);
var doesIdentityRequireRefresh = (identity) => identity.expiration !== void 0;
var memoizeIdentityProvider = (provider, isExpired, requiresRefresh) => {
    if (provider === void 0) {
        return void 0;
    }
    const normalizedProvider = typeof provider !== "function" ? () => __async(void 0, null, function* () {
        return Promise.resolve(provider);
    }) : provider;
    let resolved;
    let pending;
    let hasResult;
    let isConstant = false;
    const coalesceProvider = (options) => __async(void 0, null, function* () {
        if (!pending) {
            pending = normalizedProvider(options);
        }
        try {
            resolved = yield pending;
            hasResult = true;
            isConstant = false;
        } finally {
            pending = void 0;
        }
        return resolved;
    });
    if (isExpired === void 0) {
        return (options) => __async(void 0, null, function* () {
            if (!hasResult || options?.forceRefresh) {
                resolved = yield coalesceProvider(options);
            }
            return resolved;
        });
    }
    return (options) => __async(void 0, null, function* () {
        if (!hasResult || options?.forceRefresh) {
            resolved = yield coalesceProvider(options);
        }
        if (isConstant) {
            return resolved;
        }
        if (!requiresRefresh(resolved)) {
            isConstant = true;
            return resolved;
        }
        if (isExpired(resolved)) {
            yield coalesceProvider(options);
            return resolved;
        }
        return resolved;
    });
};

// node_modules/@aws-sdk/middleware-user-agent/dist-es/configurations.js
var DEFAULT_UA_APP_ID = void 0;

function isValidUserAgentAppId(appId) {
    if (appId === void 0) {
        return true;
    }
    return typeof appId === "string" && appId.length <= 50;
}

function resolveUserAgentConfig(input) {
    const normalizedAppIdProvider = normalizeProvider2(input.userAgentAppId ?? DEFAULT_UA_APP_ID);
    return __spreadProps(__spreadValues({}, input), {
        customUserAgent: typeof input.customUserAgent === "string" ? [[input.customUserAgent]] : input.customUserAgent,
        userAgentAppId: () => __async(this, null, function* () {
            const appId = yield normalizedAppIdProvider();
            if (!isValidUserAgentAppId(appId)) {
                const logger2 = input.logger?.constructor?.name === "NoOpLogger" || !input.logger ? console : input.logger;
                if (typeof appId !== "string") {
                    logger2?.warn("userAgentAppId must be a string or undefined.");
                } else if (appId.length > 50) {
                    logger2?.warn("The provided userAgentAppId exceeds the maximum length of 50 characters.");
                }
            }
            return appId;
        })
    });
}

// node_modules/@smithy/util-endpoints/dist-es/cache/EndpointCache.js
var EndpointCache = class {
    constructor({
                    size,
                    params
                }) {
        this.data = /* @__PURE__ */ new Map();
        this.parameters = [];
        this.capacity = size ?? 50;
        if (params) {
            this.parameters = params;
        }
    }

    get(endpointParams, resolver) {
        const key = this.hash(endpointParams);
        if (key === false) {
            return resolver();
        }
        if (!this.data.has(key)) {
            if (this.data.size > this.capacity + 10) {
                const keys = this.data.keys();
                let i = 0;
                while (true) {
                    const {
                        value,
                        done
                    } = keys.next();
                    this.data.delete(value);
                    if (done || ++i > 10) {
                        break;
                    }
                }
            }
            this.data.set(key, resolver());
        }
        return this.data.get(key);
    }

    size() {
        return this.data.size;
    }

    hash(endpointParams) {
        let buffer = "";
        const {
            parameters
        } = this;
        if (parameters.length === 0) {
            return false;
        }
        for (const param of parameters) {
            const val = String(endpointParams[param] ?? "");
            if (val.includes("|;")) {
                return false;
            }
            buffer += val + "|;";
        }
        return buffer;
    }
};

// node_modules/@smithy/util-endpoints/dist-es/lib/isIpAddress.js
var IP_V4_REGEX = new RegExp(`^(?:25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]\\d|\\d)(?:\\.(?:25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]\\d|\\d)){3}$`);
var isIpAddress = (value) => IP_V4_REGEX.test(value) || value.startsWith("[") && value.endsWith("]");

// node_modules/@smithy/util-endpoints/dist-es/lib/isValidHostLabel.js
var VALID_HOST_LABEL_REGEX = new RegExp(`^(?!.*-$)(?!-)[a-zA-Z0-9-]{1,63}$`);
var isValidHostLabel = (value, allowSubDomains = false) => {
    if (!allowSubDomains) {
        return VALID_HOST_LABEL_REGEX.test(value);
    }
    const labels = value.split(".");
    for (const label of labels) {
        if (!isValidHostLabel(label)) {
            return false;
        }
    }
    return true;
};

// node_modules/@smithy/util-endpoints/dist-es/utils/customEndpointFunctions.js
var customEndpointFunctions = {};

// node_modules/@smithy/util-endpoints/dist-es/debug/debugId.js
var debugId = "endpoints";

// node_modules/@smithy/util-endpoints/dist-es/debug/toDebugString.js
function toDebugString(input) {
    if (typeof input !== "object" || input == null) {
        return input;
    }
    if ("ref" in input) {
        return `$${toDebugString(input.ref)}`;
    }
    if ("fn" in input) {
        return `${input.fn}(${(input.argv || []).map(toDebugString).join(", ")})`;
    }
    return JSON.stringify(input, null, 2);
}

// node_modules/@smithy/util-endpoints/dist-es/types/EndpointError.js
var EndpointError = class extends Error {
    constructor(message) {
        super(message);
        this.name = "EndpointError";
    }
};

// node_modules/@smithy/util-endpoints/dist-es/lib/booleanEquals.js
var booleanEquals = (value1, value2) => value1 === value2;

// node_modules/@smithy/util-endpoints/dist-es/lib/getAttrPathList.js
var getAttrPathList = (path) => {
    const parts = path.split(".");
    const pathList = [];
    for (const part of parts) {
        const squareBracketIndex = part.indexOf("[");
        if (squareBracketIndex !== -1) {
            if (part.indexOf("]") !== part.length - 1) {
                throw new EndpointError(`Path: '${path}' does not end with ']'`);
            }
            const arrayIndex = part.slice(squareBracketIndex + 1, -1);
            if (Number.isNaN(parseInt(arrayIndex))) {
                throw new EndpointError(`Invalid array index: '${arrayIndex}' in path: '${path}'`);
            }
            if (squareBracketIndex !== 0) {
                pathList.push(part.slice(0, squareBracketIndex));
            }
            pathList.push(arrayIndex);
        } else {
            pathList.push(part);
        }
    }
    return pathList;
};

// node_modules/@smithy/util-endpoints/dist-es/lib/getAttr.js
var getAttr = (value, path) => getAttrPathList(path).reduce((acc, index) => {
    if (typeof acc !== "object") {
        throw new EndpointError(`Index '${index}' in '${path}' not found in '${JSON.stringify(value)}'`);
    } else if (Array.isArray(acc)) {
        return acc[parseInt(index)];
    }
    return acc[index];
}, value);

// node_modules/@smithy/util-endpoints/dist-es/lib/isSet.js
var isSet = (value) => value != null;

// node_modules/@smithy/util-endpoints/dist-es/lib/not.js
var not = (value) => !value;

// node_modules/@smithy/util-endpoints/dist-es/lib/parseURL.js
var DEFAULT_PORTS = {
    [EndpointURLScheme.HTTP]: 80,
    [EndpointURLScheme.HTTPS]: 443
};
var parseURL = (value) => {
    const whatwgURL = (() => {
        try {
            if (value instanceof URL) {
                return value;
            }
            if (typeof value === "object" && "hostname" in value) {
                const {
                    hostname: hostname2,
                    port,
                    protocol: protocol2 = "",
                    path = "",
                    query = {}
                } = value;
                const url = new URL(`${protocol2}//${hostname2}${port ? `:${port}` : ""}${path}`);
                url.search = Object.entries(query).map(([k, v]) => `${k}=${v}`).join("&");
                return url;
            }
            return new URL(value);
        } catch (error) {
            return null;
        }
    })();
    if (!whatwgURL) {
        console.error(`Unable to parse ${JSON.stringify(value)} as a whatwg URL.`);
        return null;
    }
    const urlString = whatwgURL.href;
    const {
        host,
        hostname,
        pathname,
        protocol,
        search
    } = whatwgURL;
    if (search) {
        return null;
    }
    const scheme = protocol.slice(0, -1);
    if (!Object.values(EndpointURLScheme).includes(scheme)) {
        return null;
    }
    const isIp = isIpAddress(hostname);
    const inputContainsDefaultPort = urlString.includes(`${host}:${DEFAULT_PORTS[scheme]}`) || typeof value === "string" && value.includes(`${host}:${DEFAULT_PORTS[scheme]}`);
    const authority = `${host}${inputContainsDefaultPort ? `:${DEFAULT_PORTS[scheme]}` : ``}`;
    return {
        scheme,
        authority,
        path: pathname,
        normalizedPath: pathname.endsWith("/") ? pathname : `${pathname}/`,
        isIp
    };
};

// node_modules/@smithy/util-endpoints/dist-es/lib/stringEquals.js
var stringEquals = (value1, value2) => value1 === value2;

// node_modules/@smithy/util-endpoints/dist-es/lib/substring.js
var substring = (input, start, stop, reverse) => {
    if (start >= stop || input.length < stop) {
        return null;
    }
    if (!reverse) {
        return input.substring(start, stop);
    }
    return input.substring(input.length - stop, input.length - start);
};

// node_modules/@smithy/util-endpoints/dist-es/lib/uriEncode.js
var uriEncode = (value) => encodeURIComponent(value).replace(/[!*'()]/g, (c) => `%${c.charCodeAt(0).toString(16).toUpperCase()}`);

// node_modules/@smithy/util-endpoints/dist-es/utils/endpointFunctions.js
var endpointFunctions = {
    booleanEquals,
    getAttr,
    isSet,
    isValidHostLabel,
    not,
    parseURL,
    stringEquals,
    substring,
    uriEncode
};

// node_modules/@smithy/util-endpoints/dist-es/utils/evaluateTemplate.js
var evaluateTemplate = (template, options) => {
    const evaluatedTemplateArr = [];
    const templateContext = __spreadValues(__spreadValues({}, options.endpointParams), options.referenceRecord);
    let currentIndex = 0;
    while (currentIndex < template.length) {
        const openingBraceIndex = template.indexOf("{", currentIndex);
        if (openingBraceIndex === -1) {
            evaluatedTemplateArr.push(template.slice(currentIndex));
            break;
        }
        evaluatedTemplateArr.push(template.slice(currentIndex, openingBraceIndex));
        const closingBraceIndex = template.indexOf("}", openingBraceIndex);
        if (closingBraceIndex === -1) {
            evaluatedTemplateArr.push(template.slice(openingBraceIndex));
            break;
        }
        if (template[openingBraceIndex + 1] === "{" && template[closingBraceIndex + 1] === "}") {
            evaluatedTemplateArr.push(template.slice(openingBraceIndex + 1, closingBraceIndex));
            currentIndex = closingBraceIndex + 2;
        }
        const parameterName = template.substring(openingBraceIndex + 1, closingBraceIndex);
        if (parameterName.includes("#")) {
            const [refName, attrName] = parameterName.split("#");
            evaluatedTemplateArr.push(getAttr(templateContext[refName], attrName));
        } else {
            evaluatedTemplateArr.push(templateContext[parameterName]);
        }
        currentIndex = closingBraceIndex + 1;
    }
    return evaluatedTemplateArr.join("");
};

// node_modules/@smithy/util-endpoints/dist-es/utils/getReferenceValue.js
var getReferenceValue = ({
                             ref
                         }, options) => {
    const referenceRecord = __spreadValues(__spreadValues({}, options.endpointParams), options.referenceRecord);
    return referenceRecord[ref];
};

// node_modules/@smithy/util-endpoints/dist-es/utils/evaluateExpression.js
var evaluateExpression = (obj, keyName, options) => {
    if (typeof obj === "string") {
        return evaluateTemplate(obj, options);
    } else if (obj["fn"]) {
        return callFunction(obj, options);
    } else if (obj["ref"]) {
        return getReferenceValue(obj, options);
    }
    throw new EndpointError(`'${keyName}': ${String(obj)} is not a string, function or reference.`);
};

// node_modules/@smithy/util-endpoints/dist-es/utils/callFunction.js
var callFunction = ({
                        fn,
                        argv
                    }, options) => {
    const evaluatedArgs = argv.map((arg) => ["boolean", "number"].includes(typeof arg) ? arg : evaluateExpression(arg, "arg", options));
    const fnSegments = fn.split(".");
    if (fnSegments[0] in customEndpointFunctions && fnSegments[1] != null) {
        return customEndpointFunctions[fnSegments[0]][fnSegments[1]](...evaluatedArgs);
    }
    return endpointFunctions[fn](...evaluatedArgs);
};

// node_modules/@smithy/util-endpoints/dist-es/utils/evaluateCondition.js
var evaluateCondition = (_a, options) => {
    var _b = _a, {
        assign
    } = _b, fnArgs = __objRest(_b, [
        "assign"
    ]);
    if (assign && assign in options.referenceRecord) {
        throw new EndpointError(`'${assign}' is already defined in Reference Record.`);
    }
    const value = callFunction(fnArgs, options);
    options.logger?.debug?.(`${debugId} evaluateCondition: ${toDebugString(fnArgs)} = ${toDebugString(value)}`);
    return __spreadValues({
        result: value === "" ? true : !!value
    }, assign != null && {
        toAssign: {
            name: assign,
            value
        }
    });
};

// node_modules/@smithy/util-endpoints/dist-es/utils/evaluateConditions.js
var evaluateConditions = (conditions = [], options) => {
    const conditionsReferenceRecord = {};
    for (const condition of conditions) {
        const {
            result,
            toAssign
        } = evaluateCondition(condition, __spreadProps(__spreadValues({}, options), {
            referenceRecord: __spreadValues(__spreadValues({}, options.referenceRecord), conditionsReferenceRecord)
        }));
        if (!result) {
            return {
                result
            };
        }
        if (toAssign) {
            conditionsReferenceRecord[toAssign.name] = toAssign.value;
            options.logger?.debug?.(`${debugId} assign: ${toAssign.name} := ${toDebugString(toAssign.value)}`);
        }
    }
    return {
        result: true,
        referenceRecord: conditionsReferenceRecord
    };
};

// node_modules/@smithy/util-endpoints/dist-es/utils/getEndpointHeaders.js
var getEndpointHeaders = (headers, options) => Object.entries(headers).reduce((acc, [headerKey, headerVal]) => __spreadProps(__spreadValues({}, acc), {
    [headerKey]: headerVal.map((headerValEntry) => {
        const processedExpr = evaluateExpression(headerValEntry, "Header value entry", options);
        if (typeof processedExpr !== "string") {
            throw new EndpointError(`Header '${headerKey}' value '${processedExpr}' is not a string`);
        }
        return processedExpr;
    })
}), {});

// node_modules/@smithy/util-endpoints/dist-es/utils/getEndpointProperty.js
var getEndpointProperty = (property, options) => {
    if (Array.isArray(property)) {
        return property.map((propertyEntry) => getEndpointProperty(propertyEntry, options));
    }
    switch (typeof property) {
        case "string":
            return evaluateTemplate(property, options);
        case "object":
            if (property === null) {
                throw new EndpointError(`Unexpected endpoint property: ${property}`);
            }
            return getEndpointProperties(property, options);
        case "boolean":
            return property;
        default:
            throw new EndpointError(`Unexpected endpoint property type: ${typeof property}`);
    }
};

// node_modules/@smithy/util-endpoints/dist-es/utils/getEndpointProperties.js
var getEndpointProperties = (properties, options) => Object.entries(properties).reduce((acc, [propertyKey, propertyVal]) => __spreadProps(__spreadValues({}, acc), {
    [propertyKey]: getEndpointProperty(propertyVal, options)
}), {});

// node_modules/@smithy/util-endpoints/dist-es/utils/getEndpointUrl.js
var getEndpointUrl = (endpointUrl, options) => {
    const expression = evaluateExpression(endpointUrl, "Endpoint URL", options);
    if (typeof expression === "string") {
        try {
            return new URL(expression);
        } catch (error) {
            console.error(`Failed to construct URL with ${expression}`, error);
            throw error;
        }
    }
    throw new EndpointError(`Endpoint URL must be a string, got ${typeof expression}`);
};

// node_modules/@smithy/util-endpoints/dist-es/utils/evaluateEndpointRule.js
var evaluateEndpointRule = (endpointRule, options) => {
    const {
        conditions,
        endpoint
    } = endpointRule;
    const {
        result,
        referenceRecord
    } = evaluateConditions(conditions, options);
    if (!result) {
        return;
    }
    const endpointRuleOptions = __spreadProps(__spreadValues({}, options), {
        referenceRecord: __spreadValues(__spreadValues({}, options.referenceRecord), referenceRecord)
    });
    const {
        url,
        properties,
        headers
    } = endpoint;
    options.logger?.debug?.(`${debugId} Resolving endpoint from template: ${toDebugString(endpoint)}`);
    return __spreadProps(__spreadValues(__spreadValues({}, headers != void 0 && {
        headers: getEndpointHeaders(headers, endpointRuleOptions)
    }), properties != void 0 && {
        properties: getEndpointProperties(properties, endpointRuleOptions)
    }), {
        url: getEndpointUrl(url, endpointRuleOptions)
    });
};

// node_modules/@smithy/util-endpoints/dist-es/utils/evaluateErrorRule.js
var evaluateErrorRule = (errorRule, options) => {
    const {
        conditions,
        error
    } = errorRule;
    const {
        result,
        referenceRecord
    } = evaluateConditions(conditions, options);
    if (!result) {
        return;
    }
    throw new EndpointError(evaluateExpression(error, "Error", __spreadProps(__spreadValues({}, options), {
        referenceRecord: __spreadValues(__spreadValues({}, options.referenceRecord), referenceRecord)
    })));
};

// node_modules/@smithy/util-endpoints/dist-es/utils/evaluateTreeRule.js
var evaluateTreeRule = (treeRule, options) => {
    const {
        conditions,
        rules
    } = treeRule;
    const {
        result,
        referenceRecord
    } = evaluateConditions(conditions, options);
    if (!result) {
        return;
    }
    return evaluateRules(rules, __spreadProps(__spreadValues({}, options), {
        referenceRecord: __spreadValues(__spreadValues({}, options.referenceRecord), referenceRecord)
    }));
};

// node_modules/@smithy/util-endpoints/dist-es/utils/evaluateRules.js
var evaluateRules = (rules, options) => {
    for (const rule of rules) {
        if (rule.type === "endpoint") {
            const endpointOrUndefined = evaluateEndpointRule(rule, options);
            if (endpointOrUndefined) {
                return endpointOrUndefined;
            }
        } else if (rule.type === "error") {
            evaluateErrorRule(rule, options);
        } else if (rule.type === "tree") {
            const endpointOrUndefined = evaluateTreeRule(rule, options);
            if (endpointOrUndefined) {
                return endpointOrUndefined;
            }
        } else {
            throw new EndpointError(`Unknown endpoint rule: ${rule}`);
        }
    }
    throw new EndpointError(`Rules evaluation failed`);
};

// node_modules/@smithy/util-endpoints/dist-es/resolveEndpoint.js
var resolveEndpoint = (ruleSetObject, options) => {
    const {
        endpointParams,
        logger: logger2
    } = options;
    const {
        parameters,
        rules
    } = ruleSetObject;
    options.logger?.debug?.(`${debugId} Initial EndpointParams: ${toDebugString(endpointParams)}`);
    const paramsWithDefault = Object.entries(parameters).filter(([, v]) => v.default != null).map(([k, v]) => [k, v.default]);
    if (paramsWithDefault.length > 0) {
        for (const [paramKey, paramDefaultValue] of paramsWithDefault) {
            endpointParams[paramKey] = endpointParams[paramKey] ?? paramDefaultValue;
        }
    }
    const requiredParams = Object.entries(parameters).filter(([, v]) => v.required).map(([k]) => k);
    for (const requiredParam of requiredParams) {
        if (endpointParams[requiredParam] == null) {
            throw new EndpointError(`Missing required parameter: '${requiredParam}'`);
        }
    }
    const endpoint = evaluateRules(rules, {
        endpointParams,
        logger: logger2,
        referenceRecord: {}
    });
    options.logger?.debug?.(`${debugId} Resolved endpoint: ${toDebugString(endpoint)}`);
    return endpoint;
};

// node_modules/@aws-sdk/util-endpoints/dist-es/lib/aws/isVirtualHostableS3Bucket.js
var isVirtualHostableS3Bucket = (value, allowSubDomains = false) => {
    if (allowSubDomains) {
        for (const label of value.split(".")) {
            if (!isVirtualHostableS3Bucket(label)) {
                return false;
            }
        }
        return true;
    }
    if (!isValidHostLabel(value)) {
        return false;
    }
    if (value.length < 3 || value.length > 63) {
        return false;
    }
    if (value !== value.toLowerCase()) {
        return false;
    }
    if (isIpAddress(value)) {
        return false;
    }
    return true;
};

// node_modules/@aws-sdk/util-endpoints/dist-es/lib/aws/parseArn.js
var ARN_DELIMITER = ":";
var RESOURCE_DELIMITER = "/";
var parseArn = (value) => {
    const segments = value.split(ARN_DELIMITER);
    if (segments.length < 6) return null;
    const [arn, partition2, service, region, accountId, ...resourcePath] = segments;
    if (arn !== "arn" || partition2 === "" || service === "" || resourcePath.join(ARN_DELIMITER) === "") return null;
    const resourceId = resourcePath.map((resource) => resource.split(RESOURCE_DELIMITER)).flat();
    return {
        partition: partition2,
        service,
        region,
        accountId,
        resourceId
    };
};

// node_modules/@aws-sdk/util-endpoints/dist-es/lib/aws/partitions.json
var partitions_default = {
    partitions: [{
        id: "aws",
        outputs: {
            dnsSuffix: "amazonaws.com",
            dualStackDnsSuffix: "api.aws",
            implicitGlobalRegion: "us-east-1",
            name: "aws",
            supportsDualStack: true,
            supportsFIPS: true
        },
        regionRegex: "^(us|eu|ap|sa|ca|me|af|il|mx)\\-\\w+\\-\\d+$",
        regions: {
            "af-south-1": {
                description: "Africa (Cape Town)"
            },
            "ap-east-1": {
                description: "Asia Pacific (Hong Kong)"
            },
            "ap-northeast-1": {
                description: "Asia Pacific (Tokyo)"
            },
            "ap-northeast-2": {
                description: "Asia Pacific (Seoul)"
            },
            "ap-northeast-3": {
                description: "Asia Pacific (Osaka)"
            },
            "ap-south-1": {
                description: "Asia Pacific (Mumbai)"
            },
            "ap-south-2": {
                description: "Asia Pacific (Hyderabad)"
            },
            "ap-southeast-1": {
                description: "Asia Pacific (Singapore)"
            },
            "ap-southeast-2": {
                description: "Asia Pacific (Sydney)"
            },
            "ap-southeast-3": {
                description: "Asia Pacific (Jakarta)"
            },
            "ap-southeast-4": {
                description: "Asia Pacific (Melbourne)"
            },
            "ap-southeast-5": {
                description: "Asia Pacific (Malaysia)"
            },
            "aws-global": {
                description: "AWS Standard global region"
            },
            "ca-central-1": {
                description: "Canada (Central)"
            },
            "ca-west-1": {
                description: "Canada West (Calgary)"
            },
            "eu-central-1": {
                description: "Europe (Frankfurt)"
            },
            "eu-central-2": {
                description: "Europe (Zurich)"
            },
            "eu-north-1": {
                description: "Europe (Stockholm)"
            },
            "eu-south-1": {
                description: "Europe (Milan)"
            },
            "eu-south-2": {
                description: "Europe (Spain)"
            },
            "eu-west-1": {
                description: "Europe (Ireland)"
            },
            "eu-west-2": {
                description: "Europe (London)"
            },
            "eu-west-3": {
                description: "Europe (Paris)"
            },
            "il-central-1": {
                description: "Israel (Tel Aviv)"
            },
            "me-central-1": {
                description: "Middle East (UAE)"
            },
            "me-south-1": {
                description: "Middle East (Bahrain)"
            },
            "sa-east-1": {
                description: "South America (Sao Paulo)"
            },
            "us-east-1": {
                description: "US East (N. Virginia)"
            },
            "us-east-2": {
                description: "US East (Ohio)"
            },
            "us-west-1": {
                description: "US West (N. California)"
            },
            "us-west-2": {
                description: "US West (Oregon)"
            }
        }
    }, {
        id: "aws-cn",
        outputs: {
            dnsSuffix: "amazonaws.com.cn",
            dualStackDnsSuffix: "api.amazonwebservices.com.cn",
            implicitGlobalRegion: "cn-northwest-1",
            name: "aws-cn",
            supportsDualStack: true,
            supportsFIPS: true
        },
        regionRegex: "^cn\\-\\w+\\-\\d+$",
        regions: {
            "aws-cn-global": {
                description: "AWS China global region"
            },
            "cn-north-1": {
                description: "China (Beijing)"
            },
            "cn-northwest-1": {
                description: "China (Ningxia)"
            }
        }
    }, {
        id: "aws-us-gov",
        outputs: {
            dnsSuffix: "amazonaws.com",
            dualStackDnsSuffix: "api.aws",
            implicitGlobalRegion: "us-gov-west-1",
            name: "aws-us-gov",
            supportsDualStack: true,
            supportsFIPS: true
        },
        regionRegex: "^us\\-gov\\-\\w+\\-\\d+$",
        regions: {
            "aws-us-gov-global": {
                description: "AWS GovCloud (US) global region"
            },
            "us-gov-east-1": {
                description: "AWS GovCloud (US-East)"
            },
            "us-gov-west-1": {
                description: "AWS GovCloud (US-West)"
            }
        }
    }, {
        id: "aws-iso",
        outputs: {
            dnsSuffix: "c2s.ic.gov",
            dualStackDnsSuffix: "c2s.ic.gov",
            implicitGlobalRegion: "us-iso-east-1",
            name: "aws-iso",
            supportsDualStack: false,
            supportsFIPS: true
        },
        regionRegex: "^us\\-iso\\-\\w+\\-\\d+$",
        regions: {
            "aws-iso-global": {
                description: "AWS ISO (US) global region"
            },
            "us-iso-east-1": {
                description: "US ISO East"
            },
            "us-iso-west-1": {
                description: "US ISO WEST"
            }
        }
    }, {
        id: "aws-iso-b",
        outputs: {
            dnsSuffix: "sc2s.sgov.gov",
            dualStackDnsSuffix: "sc2s.sgov.gov",
            implicitGlobalRegion: "us-isob-east-1",
            name: "aws-iso-b",
            supportsDualStack: false,
            supportsFIPS: true
        },
        regionRegex: "^us\\-isob\\-\\w+\\-\\d+$",
        regions: {
            "aws-iso-b-global": {
                description: "AWS ISOB (US) global region"
            },
            "us-isob-east-1": {
                description: "US ISOB East (Ohio)"
            }
        }
    }, {
        id: "aws-iso-e",
        outputs: {
            dnsSuffix: "cloud.adc-e.uk",
            dualStackDnsSuffix: "cloud.adc-e.uk",
            implicitGlobalRegion: "eu-isoe-west-1",
            name: "aws-iso-e",
            supportsDualStack: false,
            supportsFIPS: true
        },
        regionRegex: "^eu\\-isoe\\-\\w+\\-\\d+$",
        regions: {
            "eu-isoe-west-1": {
                description: "EU ISOE West"
            }
        }
    }, {
        id: "aws-iso-f",
        outputs: {
            dnsSuffix: "csp.hci.ic.gov",
            dualStackDnsSuffix: "csp.hci.ic.gov",
            implicitGlobalRegion: "us-isof-south-1",
            name: "aws-iso-f",
            supportsDualStack: false,
            supportsFIPS: true
        },
        regionRegex: "^us\\-isof\\-\\w+\\-\\d+$",
        regions: {}
    }],
    version: "1.1"
};

// node_modules/@aws-sdk/util-endpoints/dist-es/lib/aws/partition.js
var selectedPartitionsInfo = partitions_default;
var selectedUserAgentPrefix = "";
var partition = (value) => {
    const {
        partitions
    } = selectedPartitionsInfo;
    for (const partition2 of partitions) {
        const {
            regions,
            outputs
        } = partition2;
        for (const [region, regionData] of Object.entries(regions)) {
            if (region === value) {
                return __spreadValues(__spreadValues({}, outputs), regionData);
            }
        }
    }
    for (const partition2 of partitions) {
        const {
            regionRegex,
            outputs
        } = partition2;
        if (new RegExp(regionRegex).test(value)) {
            return __spreadValues({}, outputs);
        }
    }
    const DEFAULT_PARTITION = partitions.find((partition2) => partition2.id === "aws");
    if (!DEFAULT_PARTITION) {
        throw new Error("Provided region was not found in the partition array or regex, and default partition with id 'aws' doesn't exist.");
    }
    return __spreadValues({}, DEFAULT_PARTITION.outputs);
};
var getUserAgentPrefix = () => selectedUserAgentPrefix;

// node_modules/@aws-sdk/util-endpoints/dist-es/aws.js
var awsEndpointFunctions = {
    isVirtualHostableS3Bucket,
    parseArn,
    partition
};
customEndpointFunctions.aws = awsEndpointFunctions;

// node_modules/@aws-sdk/core/dist-es/submodules/client/setCredentialFeature.js
function setCredentialFeature(credentials, feature, value) {
    if (!credentials.$source) {
        credentials.$source = {};
    }
    credentials.$source[feature] = value;
    return credentials;
}

// node_modules/@aws-sdk/core/dist-es/submodules/client/setFeature.js
function setFeature2(context, feature, value) {
    if (!context.__aws_sdk_context) {
        context.__aws_sdk_context = {
            features: {}
        };
    } else if (!context.__aws_sdk_context.features) {
        context.__aws_sdk_context.features = {};
    }
    context.__aws_sdk_context.features[feature] = value;
}

// node_modules/@aws-sdk/core/dist-es/submodules/httpAuthSchemes/utils/getDateHeader.js
var getDateHeader = (response) => HttpResponse.isInstance(response) ? response.headers?.date ?? response.headers?.Date : void 0;

// node_modules/@aws-sdk/core/dist-es/submodules/httpAuthSchemes/utils/getSkewCorrectedDate.js
var getSkewCorrectedDate = (systemClockOffset) => new Date(Date.now() + systemClockOffset);

// node_modules/@aws-sdk/core/dist-es/submodules/httpAuthSchemes/utils/isClockSkewed.js
var isClockSkewed = (clockTime, systemClockOffset) => Math.abs(getSkewCorrectedDate(systemClockOffset).getTime() - clockTime) >= 3e5;

// node_modules/@aws-sdk/core/dist-es/submodules/httpAuthSchemes/utils/getUpdatedSystemClockOffset.js
var getUpdatedSystemClockOffset = (clockTime, currentSystemClockOffset) => {
    const clockTimeInMs = Date.parse(clockTime);
    if (isClockSkewed(clockTimeInMs, currentSystemClockOffset)) {
        return clockTimeInMs - Date.now();
    }
    return currentSystemClockOffset;
};

// node_modules/@aws-sdk/core/dist-es/submodules/httpAuthSchemes/aws_sdk/AwsSdkSigV4Signer.js
var throwSigningPropertyError = (name, property) => {
    if (!property) {
        throw new Error(`Property \`${name}\` is not resolved for AWS SDK SigV4Auth`);
    }
    return property;
};
var validateSigningProperties = (signingProperties) => __async(void 0, null, function* () {
    const context = throwSigningPropertyError("context", signingProperties.context);
    const config = throwSigningPropertyError("config", signingProperties.config);
    const authScheme = context.endpointV2?.properties?.authSchemes?.[0];
    const signerFunction = throwSigningPropertyError("signer", config.signer);
    const signer = yield signerFunction(authScheme);
    const signingRegion = signingProperties?.signingRegion;
    const signingRegionSet = signingProperties?.signingRegionSet;
    const signingName = signingProperties?.signingName;
    return {
        config,
        signer,
        signingRegion,
        signingRegionSet,
        signingName
    };
});
var AwsSdkSigV4Signer = class {
    sign(httpRequest, identity, signingProperties) {
        return __async(this, null, function* () {
            if (!HttpRequest.isInstance(httpRequest)) {
                throw new Error("The request is not an instance of `HttpRequest` and cannot be signed");
            }
            const validatedProps = yield validateSigningProperties(signingProperties);
            const {
                config,
                signer
            } = validatedProps;
            let {
                signingRegion,
                signingName
            } = validatedProps;
            const handlerExecutionContext = signingProperties.context;
            if (handlerExecutionContext?.authSchemes?.length ?? 0 > 1) {
                const [first, second] = handlerExecutionContext.authSchemes;
                if (first?.name === "sigv4a" && second?.name === "sigv4") {
                    signingRegion = second?.signingRegion ?? signingRegion;
                    signingName = second?.signingName ?? signingName;
                }
            }
            const signedRequest = yield signer.sign(httpRequest, {
                signingDate: getSkewCorrectedDate(config.systemClockOffset),
                signingRegion,
                signingService: signingName
            });
            return signedRequest;
        });
    }

    errorHandler(signingProperties) {
        return (error) => {
            const serverTime = error.ServerTime ?? getDateHeader(error.$response);
            if (serverTime) {
                const config = throwSigningPropertyError("config", signingProperties.config);
                const initialSystemClockOffset = config.systemClockOffset;
                config.systemClockOffset = getUpdatedSystemClockOffset(serverTime, config.systemClockOffset);
                const clockSkewCorrected = config.systemClockOffset !== initialSystemClockOffset;
                if (clockSkewCorrected && error.$metadata) {
                    error.$metadata.clockSkewCorrected = true;
                }
            }
            throw error;
        };
    }

    successHandler(httpResponse, signingProperties) {
        const dateHeader = getDateHeader(httpResponse);
        if (dateHeader) {
            const config = throwSigningPropertyError("config", signingProperties.config);
            config.systemClockOffset = getUpdatedSystemClockOffset(dateHeader, config.systemClockOffset);
        }
    }
};

// node_modules/@aws-sdk/core/dist-es/submodules/httpAuthSchemes/aws_sdk/AwsSdkSigV4ASigner.js
var AwsSdkSigV4ASigner = class extends AwsSdkSigV4Signer {
    sign(httpRequest, identity, signingProperties) {
        return __async(this, null, function* () {
            if (!HttpRequest.isInstance(httpRequest)) {
                throw new Error("The request is not an instance of `HttpRequest` and cannot be signed");
            }
            const {
                config,
                signer,
                signingRegion,
                signingRegionSet,
                signingName
            } = yield validateSigningProperties(signingProperties);
            const configResolvedSigningRegionSet = yield config.sigv4aSigningRegionSet?.();
            const multiRegionOverride = (configResolvedSigningRegionSet ?? signingRegionSet ?? [signingRegion]).join(",");
            const signedRequest = yield signer.sign(httpRequest, {
                signingDate: getSkewCorrectedDate(config.systemClockOffset),
                signingRegion: multiRegionOverride,
                signingService: signingName
            });
            return signedRequest;
        });
    }
};

// node_modules/@smithy/property-provider/dist-es/memoize.js
var memoize = (provider, isExpired, requiresRefresh) => {
    let resolved;
    let pending;
    let hasResult;
    let isConstant = false;
    const coalesceProvider = () => __async(void 0, null, function* () {
        if (!pending) {
            pending = provider();
        }
        try {
            resolved = yield pending;
            hasResult = true;
            isConstant = false;
        } finally {
            pending = void 0;
        }
        return resolved;
    });
    if (isExpired === void 0) {
        return (options) => __async(void 0, null, function* () {
            if (!hasResult || options?.forceRefresh) {
                resolved = yield coalesceProvider();
            }
            return resolved;
        });
    }
    return (options) => __async(void 0, null, function* () {
        if (!hasResult || options?.forceRefresh) {
            resolved = yield coalesceProvider();
        }
        if (isConstant) {
            return resolved;
        }
        if (requiresRefresh && !requiresRefresh(resolved)) {
            isConstant = true;
            return resolved;
        }
        if (isExpired(resolved)) {
            yield coalesceProvider();
            return resolved;
        }
        return resolved;
    });
};

// node_modules/@aws-sdk/core/dist-es/submodules/httpAuthSchemes/aws_sdk/resolveAwsSdkSigV4AConfig.js
var resolveAwsSdkSigV4AConfig = (config) => {
    config.sigv4aSigningRegionSet = normalizeProvider2(config.sigv4aSigningRegionSet);
    return config;
};

// node_modules/@smithy/signature-v4/dist-es/constants.js
var ALGORITHM_QUERY_PARAM = "X-Amz-Algorithm";
var CREDENTIAL_QUERY_PARAM = "X-Amz-Credential";
var AMZ_DATE_QUERY_PARAM = "X-Amz-Date";
var SIGNED_HEADERS_QUERY_PARAM = "X-Amz-SignedHeaders";
var EXPIRES_QUERY_PARAM = "X-Amz-Expires";
var SIGNATURE_QUERY_PARAM = "X-Amz-Signature";
var TOKEN_QUERY_PARAM = "X-Amz-Security-Token";
var AUTH_HEADER = "authorization";
var AMZ_DATE_HEADER = AMZ_DATE_QUERY_PARAM.toLowerCase();
var DATE_HEADER = "date";
var GENERATED_HEADERS = [AUTH_HEADER, AMZ_DATE_HEADER, DATE_HEADER];
var SIGNATURE_HEADER = SIGNATURE_QUERY_PARAM.toLowerCase();
var SHA256_HEADER = "x-amz-content-sha256";
var TOKEN_HEADER = TOKEN_QUERY_PARAM.toLowerCase();
var ALWAYS_UNSIGNABLE_HEADERS = {
    authorization: true,
    "cache-control": true,
    connection: true,
    expect: true,
    from: true,
    "keep-alive": true,
    "max-forwards": true,
    pragma: true,
    referer: true,
    te: true,
    trailer: true,
    "transfer-encoding": true,
    upgrade: true,
    "user-agent": true,
    "x-amzn-trace-id": true
};
var PROXY_HEADER_PATTERN = /^proxy-/;
var SEC_HEADER_PATTERN = /^sec-/;
var ALGORITHM_IDENTIFIER = "AWS4-HMAC-SHA256";
var EVENT_ALGORITHM_IDENTIFIER = "AWS4-HMAC-SHA256-PAYLOAD";
var UNSIGNED_PAYLOAD = "UNSIGNED-PAYLOAD";
var MAX_CACHE_SIZE = 50;
var KEY_TYPE_IDENTIFIER = "aws4_request";
var MAX_PRESIGNED_TTL = 60 * 60 * 24 * 7;

// node_modules/@smithy/signature-v4/dist-es/credentialDerivation.js
var signingKeyCache = {};
var cacheQueue = [];
var createScope = (shortDate, region, service) => `${shortDate}/${region}/${service}/${KEY_TYPE_IDENTIFIER}`;
var getSigningKey = (sha256Constructor, credentials, shortDate, region, service) => __async(void 0, null, function* () {
    const credsHash = yield hmac(sha256Constructor, credentials.secretAccessKey, credentials.accessKeyId);
    const cacheKey = `${shortDate}:${region}:${service}:${toHex(credsHash)}:${credentials.sessionToken}`;
    if (cacheKey in signingKeyCache) {
        return signingKeyCache[cacheKey];
    }
    cacheQueue.push(cacheKey);
    while (cacheQueue.length > MAX_CACHE_SIZE) {
        delete signingKeyCache[cacheQueue.shift()];
    }
    let key = `AWS4${credentials.secretAccessKey}`;
    for (const signable of [shortDate, region, service, KEY_TYPE_IDENTIFIER]) {
        key = yield hmac(sha256Constructor, key, signable);
    }
    return signingKeyCache[cacheKey] = key;
});
var hmac = (ctor, secret, data) => {
    const hash = new ctor(secret);
    hash.update(toUint8Array(data));
    return hash.digest();
};

// node_modules/@smithy/signature-v4/dist-es/getCanonicalHeaders.js
var getCanonicalHeaders = ({
                               headers
                           }, unsignableHeaders, signableHeaders) => {
    const canonical = {};
    for (const headerName of Object.keys(headers).sort()) {
        if (headers[headerName] == void 0) {
            continue;
        }
        const canonicalHeaderName = headerName.toLowerCase();
        if (canonicalHeaderName in ALWAYS_UNSIGNABLE_HEADERS || unsignableHeaders?.has(canonicalHeaderName) || PROXY_HEADER_PATTERN.test(canonicalHeaderName) || SEC_HEADER_PATTERN.test(canonicalHeaderName)) {
            if (!signableHeaders || signableHeaders && !signableHeaders.has(canonicalHeaderName)) {
                continue;
            }
        }
        canonical[canonicalHeaderName] = headers[headerName].trim().replace(/\s+/g, " ");
    }
    return canonical;
};

// node_modules/@smithy/signature-v4/dist-es/getCanonicalQuery.js
var getCanonicalQuery = ({
                             query = {}
                         }) => {
    const keys = [];
    const serialized = {};
    for (const key of Object.keys(query)) {
        if (key.toLowerCase() === SIGNATURE_HEADER) {
            continue;
        }
        const encodedKey = escapeUri(key);
        keys.push(encodedKey);
        const value = query[key];
        if (typeof value === "string") {
            serialized[encodedKey] = `${encodedKey}=${escapeUri(value)}`;
        } else if (Array.isArray(value)) {
            serialized[encodedKey] = value.slice(0).reduce((encoded, value2) => encoded.concat([`${encodedKey}=${escapeUri(value2)}`]), []).sort().join("&");
        }
    }
    return keys.sort().map((key) => serialized[key]).filter((serialized2) => serialized2).join("&");
};

// node_modules/@smithy/is-array-buffer/dist-es/index.js
var isArrayBuffer = (arg) => typeof ArrayBuffer === "function" && arg instanceof ArrayBuffer || Object.prototype.toString.call(arg) === "[object ArrayBuffer]";

// node_modules/@smithy/signature-v4/dist-es/getPayloadHash.js
var getPayloadHash = (_0, _1) => __async(void 0, [_0, _1], function* ({
                                                                          headers,
                                                                          body
                                                                      }, hashConstructor) {
    for (const headerName of Object.keys(headers)) {
        if (headerName.toLowerCase() === SHA256_HEADER) {
            return headers[headerName];
        }
    }
    if (body == void 0) {
        return "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";
    } else if (typeof body === "string" || ArrayBuffer.isView(body) || isArrayBuffer(body)) {
        const hashCtor = new hashConstructor();
        hashCtor.update(toUint8Array(body));
        return toHex(yield hashCtor.digest());
    }
    return UNSIGNED_PAYLOAD;
});

// node_modules/@smithy/signature-v4/dist-es/HeaderFormatter.js
var HeaderFormatter = class {
    format(headers) {
        const chunks = [];
        for (const headerName of Object.keys(headers)) {
            const bytes = fromUtf8(headerName);
            chunks.push(Uint8Array.from([bytes.byteLength]), bytes, this.formatHeaderValue(headers[headerName]));
        }
        const out = new Uint8Array(chunks.reduce((carry, bytes) => carry + bytes.byteLength, 0));
        let position = 0;
        for (const chunk of chunks) {
            out.set(chunk, position);
            position += chunk.byteLength;
        }
        return out;
    }

    formatHeaderValue(header) {
        switch (header.type) {
            case "boolean":
                return Uint8Array.from([header.value ? 0 : 1]);
            case "byte":
                return Uint8Array.from([2, header.value]);
            case "short":
                const shortView = new DataView(new ArrayBuffer(3));
                shortView.setUint8(0, 3);
                shortView.setInt16(1, header.value, false);
                return new Uint8Array(shortView.buffer);
            case "integer":
                const intView = new DataView(new ArrayBuffer(5));
                intView.setUint8(0, 4);
                intView.setInt32(1, header.value, false);
                return new Uint8Array(intView.buffer);
            case "long":
                const longBytes = new Uint8Array(9);
                longBytes[0] = 5;
                longBytes.set(header.value.bytes, 1);
                return longBytes;
            case "binary":
                const binView = new DataView(new ArrayBuffer(3 + header.value.byteLength));
                binView.setUint8(0, 6);
                binView.setUint16(1, header.value.byteLength, false);
                const binBytes = new Uint8Array(binView.buffer);
                binBytes.set(header.value, 3);
                return binBytes;
            case "string":
                const utf8Bytes = fromUtf8(header.value);
                const strView = new DataView(new ArrayBuffer(3 + utf8Bytes.byteLength));
                strView.setUint8(0, 7);
                strView.setUint16(1, utf8Bytes.byteLength, false);
                const strBytes = new Uint8Array(strView.buffer);
                strBytes.set(utf8Bytes, 3);
                return strBytes;
            case "timestamp":
                const tsBytes = new Uint8Array(9);
                tsBytes[0] = 8;
                tsBytes.set(Int64.fromNumber(header.value.valueOf()).bytes, 1);
                return tsBytes;
            case "uuid":
                if (!UUID_PATTERN.test(header.value)) {
                    throw new Error(`Invalid UUID received: ${header.value}`);
                }
                const uuidBytes = new Uint8Array(17);
                uuidBytes[0] = 9;
                uuidBytes.set(fromHex(header.value.replace(/\-/g, "")), 1);
                return uuidBytes;
        }
    }
};
var HEADER_VALUE_TYPE;
(function (HEADER_VALUE_TYPE2) {
    HEADER_VALUE_TYPE2[HEADER_VALUE_TYPE2["boolTrue"] = 0] = "boolTrue";
    HEADER_VALUE_TYPE2[HEADER_VALUE_TYPE2["boolFalse"] = 1] = "boolFalse";
    HEADER_VALUE_TYPE2[HEADER_VALUE_TYPE2["byte"] = 2] = "byte";
    HEADER_VALUE_TYPE2[HEADER_VALUE_TYPE2["short"] = 3] = "short";
    HEADER_VALUE_TYPE2[HEADER_VALUE_TYPE2["integer"] = 4] = "integer";
    HEADER_VALUE_TYPE2[HEADER_VALUE_TYPE2["long"] = 5] = "long";
    HEADER_VALUE_TYPE2[HEADER_VALUE_TYPE2["byteArray"] = 6] = "byteArray";
    HEADER_VALUE_TYPE2[HEADER_VALUE_TYPE2["string"] = 7] = "string";
    HEADER_VALUE_TYPE2[HEADER_VALUE_TYPE2["timestamp"] = 8] = "timestamp";
    HEADER_VALUE_TYPE2[HEADER_VALUE_TYPE2["uuid"] = 9] = "uuid";
})(HEADER_VALUE_TYPE || (HEADER_VALUE_TYPE = {}));
var UUID_PATTERN = /^[a-f0-9]{8}-[a-f0-9]{4}-[a-f0-9]{4}-[a-f0-9]{4}-[a-f0-9]{12}$/;
var Int64 = class _Int64 {
    constructor(bytes) {
        this.bytes = bytes;
        if (bytes.byteLength !== 8) {
            throw new Error("Int64 buffers must be exactly 8 bytes");
        }
    }

    static fromNumber(number) {
        if (number > 9223372036854776e3 || number < -9223372036854776e3) {
            throw new Error(`${number} is too large (or, if negative, too small) to represent as an Int64`);
        }
        const bytes = new Uint8Array(8);
        for (let i = 7, remaining = Math.abs(Math.round(number)); i > -1 && remaining > 0; i--, remaining /= 256) {
            bytes[i] = remaining;
        }
        if (number < 0) {
            negate(bytes);
        }
        return new _Int64(bytes);
    }

    valueOf() {
        const bytes = this.bytes.slice(0);
        const negative = bytes[0] & 128;
        if (negative) {
            negate(bytes);
        }
        return parseInt(toHex(bytes), 16) * (negative ? -1 : 1);
    }

    toString() {
        return String(this.valueOf());
    }
};

function negate(bytes) {
    for (let i = 0; i < 8; i++) {
        bytes[i] ^= 255;
    }
    for (let i = 7; i > -1; i--) {
        bytes[i]++;
        if (bytes[i] !== 0) break;
    }
}

// node_modules/@smithy/signature-v4/dist-es/headerUtil.js
var hasHeader = (soughtHeader, headers) => {
    soughtHeader = soughtHeader.toLowerCase();
    for (const headerName of Object.keys(headers)) {
        if (soughtHeader === headerName.toLowerCase()) {
            return true;
        }
    }
    return false;
};

// node_modules/@smithy/signature-v4/dist-es/moveHeadersToQuery.js
var moveHeadersToQuery = (request, options = {}) => {
    const {
        headers,
        query = {}
    } = HttpRequest.clone(request);
    for (const name of Object.keys(headers)) {
        const lname = name.toLowerCase();
        if (lname.slice(0, 6) === "x-amz-" && !options.unhoistableHeaders?.has(lname) || options.hoistableHeaders?.has(lname)) {
            query[name] = headers[name];
            delete headers[name];
        }
    }
    return __spreadProps(__spreadValues({}, request), {
        headers,
        query
    });
};

// node_modules/@smithy/signature-v4/dist-es/prepareRequest.js
var prepareRequest = (request) => {
    request = HttpRequest.clone(request);
    for (const headerName of Object.keys(request.headers)) {
        if (GENERATED_HEADERS.indexOf(headerName.toLowerCase()) > -1) {
            delete request.headers[headerName];
        }
    }
    return request;
};

// node_modules/@smithy/signature-v4/dist-es/utilDate.js
var iso8601 = (time) => toDate(time).toISOString().replace(/\.\d{3}Z$/, "Z");
var toDate = (time) => {
    if (typeof time === "number") {
        return new Date(time * 1e3);
    }
    if (typeof time === "string") {
        if (Number(time)) {
            return new Date(Number(time) * 1e3);
        }
        return new Date(time);
    }
    return time;
};

// node_modules/@smithy/signature-v4/dist-es/SignatureV4.js
var SignatureV4 = class {
    constructor({
                    applyChecksum,
                    credentials,
                    region,
                    service,
                    sha256,
                    uriEscapePath = true
                }) {
        this.headerFormatter = new HeaderFormatter();
        this.service = service;
        this.sha256 = sha256;
        this.uriEscapePath = uriEscapePath;
        this.applyChecksum = typeof applyChecksum === "boolean" ? applyChecksum : true;
        this.regionProvider = normalizeProvider(region);
        this.credentialProvider = normalizeProvider(credentials);
    }

    presign(_0) {
        return __async(this, arguments, function* (originalRequest, options = {}) {
            const {
                signingDate = /* @__PURE__ */ new Date(),
                expiresIn = 3600,
                unsignableHeaders,
                unhoistableHeaders,
                signableHeaders,
                hoistableHeaders,
                signingRegion,
                signingService
            } = options;
            const credentials = yield this.credentialProvider();
            this.validateResolvedCredentials(credentials);
            const region = signingRegion ?? (yield this.regionProvider());
            const {
                longDate,
                shortDate
            } = formatDate(signingDate);
            if (expiresIn > MAX_PRESIGNED_TTL) {
                return Promise.reject("Signature version 4 presigned URLs must have an expiration date less than one week in the future");
            }
            const scope = createScope(shortDate, region, signingService ?? this.service);
            const request = moveHeadersToQuery(prepareRequest(originalRequest), {
                unhoistableHeaders,
                hoistableHeaders
            });
            if (credentials.sessionToken) {
                request.query[TOKEN_QUERY_PARAM] = credentials.sessionToken;
            }
            request.query[ALGORITHM_QUERY_PARAM] = ALGORITHM_IDENTIFIER;
            request.query[CREDENTIAL_QUERY_PARAM] = `${credentials.accessKeyId}/${scope}`;
            request.query[AMZ_DATE_QUERY_PARAM] = longDate;
            request.query[EXPIRES_QUERY_PARAM] = expiresIn.toString(10);
            const canonicalHeaders = getCanonicalHeaders(request, unsignableHeaders, signableHeaders);
            request.query[SIGNED_HEADERS_QUERY_PARAM] = getCanonicalHeaderList(canonicalHeaders);
            request.query[SIGNATURE_QUERY_PARAM] = yield this.getSignature(longDate, scope, this.getSigningKey(credentials, region, shortDate, signingService), this.createCanonicalRequest(request, canonicalHeaders, yield getPayloadHash(originalRequest, this.sha256)));
            return request;
        });
    }

    sign(toSign, options) {
        return __async(this, null, function* () {
            if (typeof toSign === "string") {
                return this.signString(toSign, options);
            } else if (toSign.headers && toSign.payload) {
                return this.signEvent(toSign, options);
            } else if (toSign.message) {
                return this.signMessage(toSign, options);
            } else {
                return this.signRequest(toSign, options);
            }
        });
    }

    signEvent(_0, _1) {
        return __async(this, arguments, function* ({
                                                       headers,
                                                       payload
                                                   }, {
                                                       signingDate = /* @__PURE__ */ new Date(),
                                                       priorSignature,
                                                       signingRegion,
                                                       signingService
                                                   }) {
            const region = signingRegion ?? (yield this.regionProvider());
            const {
                shortDate,
                longDate
            } = formatDate(signingDate);
            const scope = createScope(shortDate, region, signingService ?? this.service);
            const hashedPayload = yield getPayloadHash({
                headers: {},
                body: payload
            }, this.sha256);
            const hash = new this.sha256();
            hash.update(headers);
            const hashedHeaders = toHex(yield hash.digest());
            const stringToSign = [EVENT_ALGORITHM_IDENTIFIER, longDate, scope, priorSignature, hashedHeaders, hashedPayload].join("\n");
            return this.signString(stringToSign, {
                signingDate,
                signingRegion: region,
                signingService
            });
        });
    }

    signMessage(_0, _1) {
        return __async(this, arguments, function* (signableMessage, {
            signingDate = /* @__PURE__ */ new Date(),
            signingRegion,
            signingService
        }) {
            const promise = this.signEvent({
                headers: this.headerFormatter.format(signableMessage.message.headers),
                payload: signableMessage.message.body
            }, {
                signingDate,
                signingRegion,
                signingService,
                priorSignature: signableMessage.priorSignature
            });
            return promise.then((signature) => {
                return {
                    message: signableMessage.message,
                    signature
                };
            });
        });
    }

    signString(_0) {
        return __async(this, arguments, function* (stringToSign, {
            signingDate = /* @__PURE__ */ new Date(),
            signingRegion,
            signingService
        } = {}) {
            const credentials = yield this.credentialProvider();
            this.validateResolvedCredentials(credentials);
            const region = signingRegion ?? (yield this.regionProvider());
            const {
                shortDate
            } = formatDate(signingDate);
            const hash = new this.sha256(yield this.getSigningKey(credentials, region, shortDate, signingService));
            hash.update(toUint8Array(stringToSign));
            return toHex(yield hash.digest());
        });
    }

    signRequest(_0) {
        return __async(this, arguments, function* (requestToSign, {
            signingDate = /* @__PURE__ */ new Date(),
            signableHeaders,
            unsignableHeaders,
            signingRegion,
            signingService
        } = {}) {
            const credentials = yield this.credentialProvider();
            this.validateResolvedCredentials(credentials);
            const region = signingRegion ?? (yield this.regionProvider());
            const request = prepareRequest(requestToSign);
            const {
                longDate,
                shortDate
            } = formatDate(signingDate);
            const scope = createScope(shortDate, region, signingService ?? this.service);
            request.headers[AMZ_DATE_HEADER] = longDate;
            if (credentials.sessionToken) {
                request.headers[TOKEN_HEADER] = credentials.sessionToken;
            }
            const payloadHash = yield getPayloadHash(request, this.sha256);
            if (!hasHeader(SHA256_HEADER, request.headers) && this.applyChecksum) {
                request.headers[SHA256_HEADER] = payloadHash;
            }
            const canonicalHeaders = getCanonicalHeaders(request, unsignableHeaders, signableHeaders);
            const signature = yield this.getSignature(longDate, scope, this.getSigningKey(credentials, region, shortDate, signingService), this.createCanonicalRequest(request, canonicalHeaders, payloadHash));
            request.headers[AUTH_HEADER] = `${ALGORITHM_IDENTIFIER} Credential=${credentials.accessKeyId}/${scope}, SignedHeaders=${getCanonicalHeaderList(canonicalHeaders)}, Signature=${signature}`;
            return request;
        });
    }

    createCanonicalRequest(request, canonicalHeaders, payloadHash) {
        const sortedHeaders = Object.keys(canonicalHeaders).sort();
        return `${request.method}
${this.getCanonicalPath(request)}
${getCanonicalQuery(request)}
${sortedHeaders.map((name) => `${name}:${canonicalHeaders[name]}`).join("\n")}

${sortedHeaders.join(";")}
${payloadHash}`;
    }

    createStringToSign(longDate, credentialScope, canonicalRequest) {
        return __async(this, null, function* () {
            const hash = new this.sha256();
            hash.update(toUint8Array(canonicalRequest));
            const hashedRequest = yield hash.digest();
            return `${ALGORITHM_IDENTIFIER}
${longDate}
${credentialScope}
${toHex(hashedRequest)}`;
        });
    }

    getCanonicalPath({
                         path
                     }) {
        if (this.uriEscapePath) {
            const normalizedPathSegments = [];
            for (const pathSegment of path.split("/")) {
                if (pathSegment?.length === 0) continue;
                if (pathSegment === ".") continue;
                if (pathSegment === "..") {
                    normalizedPathSegments.pop();
                } else {
                    normalizedPathSegments.push(pathSegment);
                }
            }
            const normalizedPath = `${path?.startsWith("/") ? "/" : ""}${normalizedPathSegments.join("/")}${normalizedPathSegments.length > 0 && path?.endsWith("/") ? "/" : ""}`;
            const doubleEncoded = escapeUri(normalizedPath);
            return doubleEncoded.replace(/%2F/g, "/");
        }
        return path;
    }

    getSignature(longDate, credentialScope, keyPromise, canonicalRequest) {
        return __async(this, null, function* () {
            const stringToSign = yield this.createStringToSign(longDate, credentialScope, canonicalRequest);
            const hash = new this.sha256(yield keyPromise);
            hash.update(toUint8Array(stringToSign));
            return toHex(yield hash.digest());
        });
    }

    getSigningKey(credentials, region, shortDate, service) {
        return getSigningKey(this.sha256, credentials, shortDate, region, service || this.service);
    }

    validateResolvedCredentials(credentials) {
        if (typeof credentials !== "object" || typeof credentials.accessKeyId !== "string" || typeof credentials.secretAccessKey !== "string") {
            throw new Error("Resolved credential object is not valid");
        }
    }
};
var formatDate = (now) => {
    const longDate = iso8601(now).replace(/[\-:]/g, "");
    return {
        longDate,
        shortDate: longDate.slice(0, 8)
    };
};
var getCanonicalHeaderList = (headers) => Object.keys(headers).sort().join(";");

// node_modules/@aws-sdk/core/dist-es/submodules/httpAuthSchemes/aws_sdk/resolveAwsSdkSigV4Config.js
var resolveAwsSdkSigV4Config = (config) => {
    let isUserSupplied = false;
    let normalizedCreds;
    if (config.credentials) {
        isUserSupplied = true;
        normalizedCreds = memoizeIdentityProvider(config.credentials, isIdentityExpired, doesIdentityRequireRefresh);
    }
    if (!normalizedCreds) {
        if (config.credentialDefaultProvider) {
            normalizedCreds = normalizeProvider2(config.credentialDefaultProvider(Object.assign({}, config, {
                parentClientConfig: config
            })));
        } else {
            normalizedCreds = () => __async(void 0, null, function* () {
                throw new Error("`credentials` is missing");
            });
        }
    }
    const {
        signingEscapePath = true,
        systemClockOffset = config.systemClockOffset || 0,
        sha256
    } = config;
    let signer;
    if (config.signer) {
        signer = normalizeProvider2(config.signer);
    } else if (config.regionInfoProvider) {
        signer = () => normalizeProvider2(config.region)().then((region) => __async(void 0, null, function* () {
            return [(yield config.regionInfoProvider(region, {
                useFipsEndpoint: yield config.useFipsEndpoint(),
                useDualstackEndpoint: yield config.useDualstackEndpoint()
            })) || {}, region];
        })).then(([regionInfo, region]) => {
            const {
                signingRegion,
                signingService
            } = regionInfo;
            config.signingRegion = config.signingRegion || signingRegion || region;
            config.signingName = config.signingName || signingService || config.serviceId;
            const params = __spreadProps(__spreadValues({}, config), {
                credentials: normalizedCreds,
                region: config.signingRegion,
                service: config.signingName,
                sha256,
                uriEscapePath: signingEscapePath
            });
            const SignerCtor = config.signerConstructor || SignatureV4;
            return new SignerCtor(params);
        });
    } else {
        signer = (authScheme) => __async(void 0, null, function* () {
            authScheme = Object.assign({}, {
                name: "sigv4",
                signingName: config.signingName || config.defaultSigningName,
                signingRegion: yield normalizeProvider2(config.region)(),
                properties: {}
            }, authScheme);
            const signingRegion = authScheme.signingRegion;
            const signingService = authScheme.signingName;
            config.signingRegion = config.signingRegion || signingRegion;
            config.signingName = config.signingName || signingService || config.serviceId;
            const params = __spreadProps(__spreadValues({}, config), {
                credentials: normalizedCreds,
                region: config.signingRegion,
                service: config.signingName,
                sha256,
                uriEscapePath: signingEscapePath
            });
            const SignerCtor = config.signerConstructor || SignatureV4;
            return new SignerCtor(params);
        });
    }
    return __spreadProps(__spreadValues({}, config), {
        systemClockOffset,
        signingEscapePath,
        credentials: isUserSupplied ? () => __async(void 0, null, function* () {
            return normalizedCreds().then((creds) => setCredentialFeature(creds, "CREDENTIALS_CODE", "e"));
        }) : normalizedCreds,
        signer
    });
};

// node_modules/@aws-sdk/core/dist-es/submodules/protocols/common.js
var collectBodyString = (streamBody, context) => collectBody(streamBody, context).then((body) => context.utf8Encoder(body));

// node_modules/@aws-sdk/middleware-user-agent/dist-es/check-features.js
var ACCOUNT_ID_ENDPOINT_REGEX = /\d{12}\.ddb/;

function checkFeatures(context, config, args) {
    return __async(this, null, function* () {
        const request = args.request;
        if (request?.headers?.["smithy-protocol"] === "rpc-v2-cbor") {
            setFeature2(context, "PROTOCOL_RPC_V2_CBOR", "M");
        }
        if (typeof config.retryStrategy === "function") {
            const retryStrategy = yield config.retryStrategy();
            if (typeof retryStrategy.acquireInitialRetryToken === "function") {
                if (retryStrategy.constructor?.name?.includes("Adaptive")) {
                    setFeature2(context, "RETRY_MODE_ADAPTIVE", "F");
                } else {
                    setFeature2(context, "RETRY_MODE_STANDARD", "E");
                }
            } else {
                setFeature2(context, "RETRY_MODE_LEGACY", "D");
            }
        }
        if (typeof config.accountIdEndpointMode === "function") {
            const endpointV2 = context.endpointV2;
            if (String(endpointV2?.url?.hostname).match(ACCOUNT_ID_ENDPOINT_REGEX)) {
                setFeature2(context, "ACCOUNT_ID_ENDPOINT", "O");
            }
            switch (yield config.accountIdEndpointMode?.()) {
                case "disabled":
                    setFeature2(context, "ACCOUNT_ID_MODE_DISABLED", "Q");
                    break;
                case "preferred":
                    setFeature2(context, "ACCOUNT_ID_MODE_PREFERRED", "P");
                    break;
                case "required":
                    setFeature2(context, "ACCOUNT_ID_MODE_REQUIRED", "R");
                    break;
            }
        }
        const identity = context.__smithy_context?.selectedHttpAuthScheme?.identity;
        if (identity?.$source) {
            const credentials = identity;
            if (credentials.accountId) {
                setFeature2(context, "RESOLVED_ACCOUNT_ID", "T");
            }
            for (const [key, value] of Object.entries(credentials.$source ?? {})) {
                setFeature2(context, key, value);
            }
        }
    });
}

// node_modules/@aws-sdk/middleware-user-agent/dist-es/constants.js
var USER_AGENT = "user-agent";
var X_AMZ_USER_AGENT = "x-amz-user-agent";
var SPACE = " ";
var UA_NAME_SEPARATOR = "/";
var UA_NAME_ESCAPE_REGEX = /[^\!\$\%\&\'\*\+\-\.\^\_\`\|\~\d\w]/g;
var UA_VALUE_ESCAPE_REGEX = /[^\!\$\%\&\'\*\+\-\.\^\_\`\|\~\d\w\#]/g;
var UA_ESCAPE_CHAR = "-";

// node_modules/@aws-sdk/middleware-user-agent/dist-es/encode-features.js
var BYTE_LIMIT = 1024;

function encodeFeatures(features) {
    let buffer = "";
    for (const key in features) {
        const val = features[key];
        if (buffer.length + val.length + 1 <= BYTE_LIMIT) {
            if (buffer.length) {
                buffer += "," + val;
            } else {
                buffer += val;
            }
            continue;
        }
        break;
    }
    return buffer;
}

// node_modules/@aws-sdk/middleware-user-agent/dist-es/user-agent-middleware.js
var userAgentMiddleware = (options) => (next, context) => (args) => __async(void 0, null, function* () {
    const {
        request
    } = args;
    if (!HttpRequest.isInstance(request)) {
        return next(args);
    }
    const {
        headers
    } = request;
    const userAgent = context?.userAgent?.map(escapeUserAgent) || [];
    const defaultUserAgent = (yield options.defaultUserAgentProvider()).map(escapeUserAgent);
    yield checkFeatures(context, options, args);
    const awsContext = context;
    defaultUserAgent.push(`m/${encodeFeatures(Object.assign({}, context.__smithy_context?.features, awsContext.__aws_sdk_context?.features))}`);
    const customUserAgent = options?.customUserAgent?.map(escapeUserAgent) || [];
    const appId = yield options.userAgentAppId();
    if (appId) {
        defaultUserAgent.push(escapeUserAgent([`app/${appId}`]));
    }
    const prefix = getUserAgentPrefix();
    const sdkUserAgentValue = (prefix ? [prefix] : []).concat([...defaultUserAgent, ...userAgent, ...customUserAgent]).join(SPACE);
    const normalUAValue = [...defaultUserAgent.filter((section) => section.startsWith("aws-sdk-")), ...customUserAgent].join(SPACE);
    if (options.runtime !== "browser") {
        if (normalUAValue) {
            headers[X_AMZ_USER_AGENT] = headers[X_AMZ_USER_AGENT] ? `${headers[USER_AGENT]} ${normalUAValue}` : normalUAValue;
        }
        headers[USER_AGENT] = sdkUserAgentValue;
    } else {
        headers[X_AMZ_USER_AGENT] = sdkUserAgentValue;
    }
    return next(__spreadProps(__spreadValues({}, args), {
        request
    }));
});
var escapeUserAgent = (userAgentPair) => {
    const name = userAgentPair[0].split(UA_NAME_SEPARATOR).map((part) => part.replace(UA_NAME_ESCAPE_REGEX, UA_ESCAPE_CHAR)).join(UA_NAME_SEPARATOR);
    const version = userAgentPair[1]?.replace(UA_VALUE_ESCAPE_REGEX, UA_ESCAPE_CHAR);
    const prefixSeparatorIndex = name.indexOf(UA_NAME_SEPARATOR);
    const prefix = name.substring(0, prefixSeparatorIndex);
    let uaName = name.substring(prefixSeparatorIndex + 1);
    if (prefix === "api") {
        uaName = uaName.toLowerCase();
    }
    return [prefix, uaName, version].filter((item) => item && item.length > 0).reduce((acc, item, index) => {
        switch (index) {
            case 0:
                return item;
            case 1:
                return `${acc}/${item}`;
            default:
                return `${acc}#${item}`;
        }
    }, "");
};
var getUserAgentMiddlewareOptions = {
    name: "getUserAgentMiddleware",
    step: "build",
    priority: "low",
    tags: ["SET_USER_AGENT", "USER_AGENT"],
    override: true
};
var getUserAgentPlugin = (config) => ({
    applyToStack: (clientStack) => {
        clientStack.add(userAgentMiddleware(config), getUserAgentMiddlewareOptions);
    }
});

// node_modules/@smithy/config-resolver/dist-es/regionConfig/isFipsRegion.js
var isFipsRegion = (region) => typeof region === "string" && (region.startsWith("fips-") || region.endsWith("-fips"));

// node_modules/@smithy/config-resolver/dist-es/regionConfig/getRealRegion.js
var getRealRegion = (region) => isFipsRegion(region) ? ["fips-aws-global", "aws-fips"].includes(region) ? "us-east-1" : region.replace(/fips-(dkr-|prod-)?|-fips/, "") : region;

// node_modules/@smithy/config-resolver/dist-es/regionConfig/resolveRegionConfig.js
var resolveRegionConfig = (input) => {
    const {
        region,
        useFipsEndpoint
    } = input;
    if (!region) {
        throw new Error("Region is missing");
    }
    return __spreadProps(__spreadValues({}, input), {
        region: () => __async(void 0, null, function* () {
            if (typeof region === "string") {
                return getRealRegion(region);
            }
            const providedRegion = yield region();
            return getRealRegion(providedRegion);
        }),
        useFipsEndpoint: () => __async(void 0, null, function* () {
            const providedRegion = typeof region === "string" ? region : yield region();
            if (isFipsRegion(providedRegion)) {
                return true;
            }
            return typeof useFipsEndpoint !== "function" ? Promise.resolve(!!useFipsEndpoint) : useFipsEndpoint();
        })
    });
};

// node_modules/@smithy/util-config-provider/dist-es/types.js
var SelectorType;
(function (SelectorType2) {
    SelectorType2["ENV"] = "env";
    SelectorType2["CONFIG"] = "shared config entry";
})(SelectorType || (SelectorType = {}));

// node_modules/@smithy/config-resolver/dist-es/endpointsConfig/NodeUseDualstackEndpointConfigOptions.js
var DEFAULT_USE_DUALSTACK_ENDPOINT = false;

// node_modules/@smithy/config-resolver/dist-es/endpointsConfig/NodeUseFipsEndpointConfigOptions.js
var DEFAULT_USE_FIPS_ENDPOINT = false;

// node_modules/@smithy/middleware-content-length/dist-es/index.js
var CONTENT_LENGTH_HEADER = "content-length";

function contentLengthMiddleware(bodyLengthChecker) {
    return (next) => (args) => __async(this, null, function* () {
        const request = args.request;
        if (HttpRequest.isInstance(request)) {
            const {
                body,
                headers
            } = request;
            if (body && Object.keys(headers).map((str) => str.toLowerCase()).indexOf(CONTENT_LENGTH_HEADER) === -1) {
                try {
                    const length = bodyLengthChecker(body);
                    request.headers = __spreadProps(__spreadValues({}, request.headers), {
                        [CONTENT_LENGTH_HEADER]: String(length)
                    });
                } catch (error) {
                }
            }
        }
        return next(__spreadProps(__spreadValues({}, args), {
            request
        }));
    });
}

var contentLengthMiddlewareOptions = {
    step: "build",
    tags: ["SET_CONTENT_LENGTH", "CONTENT_LENGTH"],
    name: "contentLengthMiddleware",
    override: true
};
var getContentLengthPlugin = (options) => ({
    applyToStack: (clientStack) => {
        clientStack.add(contentLengthMiddleware(options.bodyLengthChecker), contentLengthMiddlewareOptions);
    }
});

// node_modules/@smithy/middleware-endpoint/dist-es/service-customizations/s3.js
var resolveParamsForS3 = (endpointParams) => __async(void 0, null, function* () {
    const bucket = endpointParams?.Bucket || "";
    if (typeof endpointParams.Bucket === "string") {
        endpointParams.Bucket = bucket.replace(/#/g, encodeURIComponent("#")).replace(/\?/g, encodeURIComponent("?"));
    }
    if (isArnBucketName(bucket)) {
        if (endpointParams.ForcePathStyle === true) {
            throw new Error("Path-style addressing cannot be used with ARN buckets");
        }
    } else if (!isDnsCompatibleBucketName(bucket) || bucket.indexOf(".") !== -1 && !String(endpointParams.Endpoint).startsWith("http:") || bucket.toLowerCase() !== bucket || bucket.length < 3) {
        endpointParams.ForcePathStyle = true;
    }
    if (endpointParams.DisableMultiRegionAccessPoints) {
        endpointParams.disableMultiRegionAccessPoints = true;
        endpointParams.DisableMRAP = true;
    }
    return endpointParams;
});
var DOMAIN_PATTERN = /^[a-z0-9][a-z0-9\.\-]{1,61}[a-z0-9]$/;
var IP_ADDRESS_PATTERN = /(\d+\.){3}\d+/;
var DOTS_PATTERN = /\.\./;
var isDnsCompatibleBucketName = (bucketName) => DOMAIN_PATTERN.test(bucketName) && !IP_ADDRESS_PATTERN.test(bucketName) && !DOTS_PATTERN.test(bucketName);
var isArnBucketName = (bucketName) => {
    const [arn, partition2, service, , , bucket] = bucketName.split(":");
    const isArn = arn === "arn" && bucketName.split(":").length >= 6;
    const isValidArn = Boolean(isArn && partition2 && service && bucket);
    if (isArn && !isValidArn) {
        throw new Error(`Invalid ARN: ${bucketName} was an invalid ARN.`);
    }
    return isValidArn;
};

// node_modules/@smithy/middleware-endpoint/dist-es/adaptors/createConfigValueProvider.js
var createConfigValueProvider = (configKey, canonicalEndpointParamKey, config) => {
    const configProvider = () => __async(void 0, null, function* () {
        const configValue = config[configKey] ?? config[canonicalEndpointParamKey];
        if (typeof configValue === "function") {
            return configValue();
        }
        return configValue;
    });
    if (configKey === "credentialScope" || canonicalEndpointParamKey === "CredentialScope") {
        return () => __async(void 0, null, function* () {
            const credentials = typeof config.credentials === "function" ? yield config.credentials() : config.credentials;
            const configValue = credentials?.credentialScope ?? credentials?.CredentialScope;
            return configValue;
        });
    }
    if (configKey === "accountId" || canonicalEndpointParamKey === "AccountId") {
        return () => __async(void 0, null, function* () {
            const credentials = typeof config.credentials === "function" ? yield config.credentials() : config.credentials;
            const configValue = credentials?.accountId ?? credentials?.AccountId;
            return configValue;
        });
    }
    if (configKey === "endpoint" || canonicalEndpointParamKey === "endpoint") {
        return () => __async(void 0, null, function* () {
            const endpoint = yield configProvider();
            if (endpoint && typeof endpoint === "object") {
                if ("url" in endpoint) {
                    return endpoint.url.href;
                }
                if ("hostname" in endpoint) {
                    const {
                        protocol,
                        hostname,
                        port,
                        path
                    } = endpoint;
                    return `${protocol}//${hostname}${port ? ":" + port : ""}${path}`;
                }
            }
            return endpoint;
        });
    }
    return configProvider;
};

// node_modules/@smithy/middleware-endpoint/dist-es/adaptors/getEndpointFromConfig.browser.js
var getEndpointFromConfig = (serviceId) => __async(void 0, null, function* () {
    return void 0;
});

// node_modules/@smithy/querystring-parser/dist-es/index.js
function parseQueryString(querystring) {
    const query = {};
    querystring = querystring.replace(/^\?/, "");
    if (querystring) {
        for (const pair of querystring.split("&")) {
            let [key, value = null] = pair.split("=");
            key = decodeURIComponent(key);
            if (value) {
                value = decodeURIComponent(value);
            }
            if (!(key in query)) {
                query[key] = value;
            } else if (Array.isArray(query[key])) {
                query[key].push(value);
            } else {
                query[key] = [query[key], value];
            }
        }
    }
    return query;
}

// node_modules/@smithy/url-parser/dist-es/index.js
var parseUrl = (url) => {
    if (typeof url === "string") {
        return parseUrl(new URL(url));
    }
    const {
        hostname,
        pathname,
        port,
        protocol,
        search
    } = url;
    let query;
    if (search) {
        query = parseQueryString(search);
    }
    return {
        hostname,
        port: port ? parseInt(port) : void 0,
        protocol,
        path: pathname,
        query
    };
};

// node_modules/@smithy/middleware-endpoint/dist-es/adaptors/toEndpointV1.js
var toEndpointV1 = (endpoint) => {
    if (typeof endpoint === "object") {
        if ("url" in endpoint) {
            return parseUrl(endpoint.url);
        }
        return endpoint;
    }
    return parseUrl(endpoint);
};

// node_modules/@smithy/middleware-endpoint/dist-es/adaptors/getEndpointFromInstructions.js
var getEndpointFromInstructions = (commandInput, instructionsSupplier, clientConfig, context) => __async(void 0, null, function* () {
    if (!clientConfig.endpoint) {
        let endpointFromConfig;
        if (clientConfig.serviceConfiguredEndpoint) {
            endpointFromConfig = yield clientConfig.serviceConfiguredEndpoint();
        } else {
            endpointFromConfig = yield getEndpointFromConfig(clientConfig.serviceId);
        }
        if (endpointFromConfig) {
            clientConfig.endpoint = () => Promise.resolve(toEndpointV1(endpointFromConfig));
        }
    }
    const endpointParams = yield resolveParams(commandInput, instructionsSupplier, clientConfig);
    if (typeof clientConfig.endpointProvider !== "function") {
        throw new Error("config.endpointProvider is not set.");
    }
    const endpoint = clientConfig.endpointProvider(endpointParams, context);
    return endpoint;
});
var resolveParams = (commandInput, instructionsSupplier, clientConfig) => __async(void 0, null, function* () {
    const endpointParams = {};
    const instructions = instructionsSupplier?.getEndpointParameterInstructions?.() || {};
    for (const [name, instruction] of Object.entries(instructions)) {
        switch (instruction.type) {
            case "staticContextParams":
                endpointParams[name] = instruction.value;
                break;
            case "contextParams":
                endpointParams[name] = commandInput[instruction.name];
                break;
            case "clientContextParams":
            case "builtInParams":
                endpointParams[name] = yield createConfigValueProvider(instruction.name, name, clientConfig)();
                break;
            default:
                throw new Error("Unrecognized endpoint parameter instruction: " + JSON.stringify(instruction));
        }
    }
    if (Object.keys(instructions).length === 0) {
        Object.assign(endpointParams, clientConfig);
    }
    if (String(clientConfig.serviceId).toLowerCase() === "s3") {
        yield resolveParamsForS3(endpointParams);
    }
    return endpointParams;
});

// node_modules/@smithy/middleware-endpoint/dist-es/endpointMiddleware.js
var endpointMiddleware = ({
                              config,
                              instructions
                          }) => {
    return (next, context) => (args) => __async(void 0, null, function* () {
        if (config.endpoint) {
            setFeature(context, "ENDPOINT_OVERRIDE", "N");
        }
        const endpoint = yield getEndpointFromInstructions(args.input, {
            getEndpointParameterInstructions() {
                return instructions;
            }
        }, __spreadValues({}, config), context);
        context.endpointV2 = endpoint;
        context.authSchemes = endpoint.properties?.authSchemes;
        const authScheme = context.authSchemes?.[0];
        if (authScheme) {
            context["signing_region"] = authScheme.signingRegion;
            context["signing_service"] = authScheme.signingName;
            const smithyContext = getSmithyContext(context);
            const httpAuthOption = smithyContext?.selectedHttpAuthScheme?.httpAuthOption;
            if (httpAuthOption) {
                httpAuthOption.signingProperties = Object.assign(httpAuthOption.signingProperties || {}, {
                    signing_region: authScheme.signingRegion,
                    signingRegion: authScheme.signingRegion,
                    signing_service: authScheme.signingName,
                    signingName: authScheme.signingName,
                    signingRegionSet: authScheme.signingRegionSet
                }, authScheme.properties);
            }
        }
        return next(__spreadValues({}, args));
    });
};

// node_modules/@smithy/middleware-endpoint/dist-es/getEndpointPlugin.js
var endpointMiddlewareOptions = {
    step: "serialize",
    tags: ["ENDPOINT_PARAMETERS", "ENDPOINT_V2", "ENDPOINT"],
    name: "endpointV2Middleware",
    override: true,
    relation: "before",
    toMiddleware: serializerMiddlewareOption.name
};
var getEndpointPlugin = (config, instructions) => ({
    applyToStack: (clientStack) => {
        clientStack.addRelativeTo(endpointMiddleware({
            config,
            instructions
        }), endpointMiddlewareOptions);
    }
});

// node_modules/@smithy/middleware-endpoint/dist-es/resolveEndpointConfig.js
var resolveEndpointConfig = (input) => {
    const tls = input.tls ?? true;
    const {
        endpoint
    } = input;
    const customEndpointProvider = endpoint != null ? () => __async(void 0, null, function* () {
        return toEndpointV1(yield normalizeProvider(endpoint)());
    }) : void 0;
    const isCustomEndpoint = !!endpoint;
    const resolvedConfig = __spreadProps(__spreadValues({}, input), {
        endpoint: customEndpointProvider,
        tls,
        isCustomEndpoint,
        useDualstackEndpoint: normalizeProvider(input.useDualstackEndpoint ?? false),
        useFipsEndpoint: normalizeProvider(input.useFipsEndpoint ?? false)
    });
    let configuredEndpointPromise = void 0;
    resolvedConfig.serviceConfiguredEndpoint = () => __async(void 0, null, function* () {
        if (input.serviceId && !configuredEndpointPromise) {
            configuredEndpointPromise = getEndpointFromConfig(input.serviceId);
        }
        return configuredEndpointPromise;
    });
    return resolvedConfig;
};

// node_modules/@smithy/util-retry/dist-es/config.js
var RETRY_MODES;
(function (RETRY_MODES2) {
    RETRY_MODES2["STANDARD"] = "standard";
    RETRY_MODES2["ADAPTIVE"] = "adaptive";
})(RETRY_MODES || (RETRY_MODES = {}));
var DEFAULT_MAX_ATTEMPTS = 3;
var DEFAULT_RETRY_MODE = RETRY_MODES.STANDARD;

// node_modules/@smithy/service-error-classification/dist-es/constants.js
var THROTTLING_ERROR_CODES = ["BandwidthLimitExceeded", "EC2ThrottledException", "LimitExceededException", "PriorRequestNotComplete", "ProvisionedThroughputExceededException", "RequestLimitExceeded", "RequestThrottled", "RequestThrottledException", "SlowDown", "ThrottledException", "Throttling", "ThrottlingException", "TooManyRequestsException", "TransactionInProgressException"];
var TRANSIENT_ERROR_CODES = ["TimeoutError", "RequestTimeout", "RequestTimeoutException"];
var TRANSIENT_ERROR_STATUS_CODES = [500, 502, 503, 504];
var NODEJS_TIMEOUT_ERROR_CODES = ["ECONNRESET", "ECONNREFUSED", "EPIPE", "ETIMEDOUT"];

// node_modules/@smithy/service-error-classification/dist-es/index.js
var isClockSkewCorrectedError = (error) => error.$metadata?.clockSkewCorrected;
var isThrottlingError = (error) => error.$metadata?.httpStatusCode === 429 || THROTTLING_ERROR_CODES.includes(error.name) || error.$retryable?.throttling == true;
var isTransientError = (error) => isClockSkewCorrectedError(error) || TRANSIENT_ERROR_CODES.includes(error.name) || NODEJS_TIMEOUT_ERROR_CODES.includes(error?.code || "") || TRANSIENT_ERROR_STATUS_CODES.includes(error.$metadata?.httpStatusCode || 0);
var isServerError = (error) => {
    if (error.$metadata?.httpStatusCode !== void 0) {
        const statusCode = error.$metadata.httpStatusCode;
        if (500 <= statusCode && statusCode <= 599 && !isTransientError(error)) {
            return true;
        }
        return false;
    }
    return false;
};

// node_modules/@smithy/util-retry/dist-es/DefaultRateLimiter.js
var DefaultRateLimiter = class _DefaultRateLimiter {
    constructor(options) {
        this.currentCapacity = 0;
        this.enabled = false;
        this.lastMaxRate = 0;
        this.measuredTxRate = 0;
        this.requestCount = 0;
        this.lastTimestamp = 0;
        this.timeWindow = 0;
        this.beta = options?.beta ?? 0.7;
        this.minCapacity = options?.minCapacity ?? 1;
        this.minFillRate = options?.minFillRate ?? 0.5;
        this.scaleConstant = options?.scaleConstant ?? 0.4;
        this.smooth = options?.smooth ?? 0.8;
        const currentTimeInSeconds = this.getCurrentTimeInSeconds();
        this.lastThrottleTime = currentTimeInSeconds;
        this.lastTxRateBucket = Math.floor(this.getCurrentTimeInSeconds());
        this.fillRate = this.minFillRate;
        this.maxCapacity = this.minCapacity;
    }

    getCurrentTimeInSeconds() {
        return Date.now() / 1e3;
    }

    getSendToken() {
        return __async(this, null, function* () {
            return this.acquireTokenBucket(1);
        });
    }

    acquireTokenBucket(amount) {
        return __async(this, null, function* () {
            if (!this.enabled) {
                return;
            }
            this.refillTokenBucket();
            if (amount > this.currentCapacity) {
                const delay = (amount - this.currentCapacity) / this.fillRate * 1e3;
                yield new Promise((resolve) => _DefaultRateLimiter.setTimeoutFn(resolve, delay));
            }
            this.currentCapacity = this.currentCapacity - amount;
        });
    }

    refillTokenBucket() {
        const timestamp = this.getCurrentTimeInSeconds();
        if (!this.lastTimestamp) {
            this.lastTimestamp = timestamp;
            return;
        }
        const fillAmount = (timestamp - this.lastTimestamp) * this.fillRate;
        this.currentCapacity = Math.min(this.maxCapacity, this.currentCapacity + fillAmount);
        this.lastTimestamp = timestamp;
    }

    updateClientSendingRate(response) {
        let calculatedRate;
        this.updateMeasuredRate();
        if (isThrottlingError(response)) {
            const rateToUse = !this.enabled ? this.measuredTxRate : Math.min(this.measuredTxRate, this.fillRate);
            this.lastMaxRate = rateToUse;
            this.calculateTimeWindow();
            this.lastThrottleTime = this.getCurrentTimeInSeconds();
            calculatedRate = this.cubicThrottle(rateToUse);
            this.enableTokenBucket();
        } else {
            this.calculateTimeWindow();
            calculatedRate = this.cubicSuccess(this.getCurrentTimeInSeconds());
        }
        const newRate = Math.min(calculatedRate, 2 * this.measuredTxRate);
        this.updateTokenBucketRate(newRate);
    }

    calculateTimeWindow() {
        this.timeWindow = this.getPrecise(Math.pow(this.lastMaxRate * (1 - this.beta) / this.scaleConstant, 1 / 3));
    }

    cubicThrottle(rateToUse) {
        return this.getPrecise(rateToUse * this.beta);
    }

    cubicSuccess(timestamp) {
        return this.getPrecise(this.scaleConstant * Math.pow(timestamp - this.lastThrottleTime - this.timeWindow, 3) + this.lastMaxRate);
    }

    enableTokenBucket() {
        this.enabled = true;
    }

    updateTokenBucketRate(newRate) {
        this.refillTokenBucket();
        this.fillRate = Math.max(newRate, this.minFillRate);
        this.maxCapacity = Math.max(newRate, this.minCapacity);
        this.currentCapacity = Math.min(this.currentCapacity, this.maxCapacity);
    }

    updateMeasuredRate() {
        const t = this.getCurrentTimeInSeconds();
        const timeBucket = Math.floor(t * 2) / 2;
        this.requestCount++;
        if (timeBucket > this.lastTxRateBucket) {
            const currentRate = this.requestCount / (timeBucket - this.lastTxRateBucket);
            this.measuredTxRate = this.getPrecise(currentRate * this.smooth + this.measuredTxRate * (1 - this.smooth));
            this.requestCount = 0;
            this.lastTxRateBucket = timeBucket;
        }
    }

    getPrecise(num) {
        return parseFloat(num.toFixed(8));
    }
};
DefaultRateLimiter.setTimeoutFn = setTimeout;

// node_modules/@smithy/util-retry/dist-es/constants.js
var DEFAULT_RETRY_DELAY_BASE = 100;
var MAXIMUM_RETRY_DELAY = 20 * 1e3;
var THROTTLING_RETRY_DELAY_BASE = 500;
var INITIAL_RETRY_TOKENS = 500;
var RETRY_COST = 5;
var TIMEOUT_RETRY_COST = 10;
var NO_RETRY_INCREMENT = 1;
var INVOCATION_ID_HEADER = "amz-sdk-invocation-id";
var REQUEST_HEADER = "amz-sdk-request";

// node_modules/@smithy/util-retry/dist-es/defaultRetryBackoffStrategy.js
var getDefaultRetryBackoffStrategy = () => {
    let delayBase = DEFAULT_RETRY_DELAY_BASE;
    const computeNextBackoffDelay = (attempts) => {
        return Math.floor(Math.min(MAXIMUM_RETRY_DELAY, Math.random() * 2 ** attempts * delayBase));
    };
    const setDelayBase = (delay) => {
        delayBase = delay;
    };
    return {
        computeNextBackoffDelay,
        setDelayBase
    };
};

// node_modules/@smithy/util-retry/dist-es/defaultRetryToken.js
var createDefaultRetryToken = ({
                                   retryDelay,
                                   retryCount,
                                   retryCost
                               }) => {
    const getRetryCount = () => retryCount;
    const getRetryDelay = () => Math.min(MAXIMUM_RETRY_DELAY, retryDelay);
    const getRetryCost = () => retryCost;
    return {
        getRetryCount,
        getRetryDelay,
        getRetryCost
    };
};

// node_modules/@smithy/util-retry/dist-es/StandardRetryStrategy.js
var StandardRetryStrategy = class {
    constructor(maxAttempts) {
        this.maxAttempts = maxAttempts;
        this.mode = RETRY_MODES.STANDARD;
        this.capacity = INITIAL_RETRY_TOKENS;
        this.retryBackoffStrategy = getDefaultRetryBackoffStrategy();
        this.maxAttemptsProvider = typeof maxAttempts === "function" ? maxAttempts : () => __async(this, null, function* () {
            return maxAttempts;
        });
    }

    acquireInitialRetryToken(retryTokenScope) {
        return __async(this, null, function* () {
            return createDefaultRetryToken({
                retryDelay: DEFAULT_RETRY_DELAY_BASE,
                retryCount: 0
            });
        });
    }

    refreshRetryTokenForRetry(token, errorInfo) {
        return __async(this, null, function* () {
            const maxAttempts = yield this.getMaxAttempts();
            if (this.shouldRetry(token, errorInfo, maxAttempts)) {
                const errorType = errorInfo.errorType;
                this.retryBackoffStrategy.setDelayBase(errorType === "THROTTLING" ? THROTTLING_RETRY_DELAY_BASE : DEFAULT_RETRY_DELAY_BASE);
                const delayFromErrorType = this.retryBackoffStrategy.computeNextBackoffDelay(token.getRetryCount());
                const retryDelay = errorInfo.retryAfterHint ? Math.max(errorInfo.retryAfterHint.getTime() - Date.now() || 0, delayFromErrorType) : delayFromErrorType;
                const capacityCost = this.getCapacityCost(errorType);
                this.capacity -= capacityCost;
                return createDefaultRetryToken({
                    retryDelay,
                    retryCount: token.getRetryCount() + 1,
                    retryCost: capacityCost
                });
            }
            throw new Error("No retry token available");
        });
    }

    recordSuccess(token) {
        this.capacity = Math.max(INITIAL_RETRY_TOKENS, this.capacity + (token.getRetryCost() ?? NO_RETRY_INCREMENT));
    }

    getCapacity() {
        return this.capacity;
    }

    getMaxAttempts() {
        return __async(this, null, function* () {
            try {
                return yield this.maxAttemptsProvider();
            } catch (error) {
                console.warn(`Max attempts provider could not resolve. Using default of ${DEFAULT_MAX_ATTEMPTS}`);
                return DEFAULT_MAX_ATTEMPTS;
            }
        });
    }

    shouldRetry(tokenToRenew, errorInfo, maxAttempts) {
        const attempts = tokenToRenew.getRetryCount() + 1;
        return attempts < maxAttempts && this.capacity >= this.getCapacityCost(errorInfo.errorType) && this.isRetryableError(errorInfo.errorType);
    }

    getCapacityCost(errorType) {
        return errorType === "TRANSIENT" ? TIMEOUT_RETRY_COST : RETRY_COST;
    }

    isRetryableError(errorType) {
        return errorType === "THROTTLING" || errorType === "TRANSIENT";
    }
};

// node_modules/@smithy/util-retry/dist-es/AdaptiveRetryStrategy.js
var AdaptiveRetryStrategy = class {
    constructor(maxAttemptsProvider, options) {
        this.maxAttemptsProvider = maxAttemptsProvider;
        this.mode = RETRY_MODES.ADAPTIVE;
        const {
            rateLimiter
        } = options ?? {};
        this.rateLimiter = rateLimiter ?? new DefaultRateLimiter();
        this.standardRetryStrategy = new StandardRetryStrategy(maxAttemptsProvider);
    }

    acquireInitialRetryToken(retryTokenScope) {
        return __async(this, null, function* () {
            yield this.rateLimiter.getSendToken();
            return this.standardRetryStrategy.acquireInitialRetryToken(retryTokenScope);
        });
    }

    refreshRetryTokenForRetry(tokenToRenew, errorInfo) {
        return __async(this, null, function* () {
            this.rateLimiter.updateClientSendingRate(errorInfo);
            return this.standardRetryStrategy.refreshRetryTokenForRetry(tokenToRenew, errorInfo);
        });
    }

    recordSuccess(token) {
        this.rateLimiter.updateClientSendingRate({});
        this.standardRetryStrategy.recordSuccess(token);
    }
};

// node_modules/@smithy/middleware-retry/dist-es/configurations.js
var resolveRetryConfig = (input) => {
    const {
        retryStrategy
    } = input;
    const maxAttempts = normalizeProvider(input.maxAttempts ?? DEFAULT_MAX_ATTEMPTS);
    return __spreadProps(__spreadValues({}, input), {
        maxAttempts,
        retryStrategy: () => __async(void 0, null, function* () {
            if (retryStrategy) {
                return retryStrategy;
            }
            const retryMode = yield normalizeProvider(input.retryMode)();
            if (retryMode === RETRY_MODES.ADAPTIVE) {
                return new AdaptiveRetryStrategy(maxAttempts);
            }
            return new StandardRetryStrategy(maxAttempts);
        })
    });
};

// node_modules/@smithy/middleware-retry/node_modules/uuid/dist/esm-browser/rng.js
var getRandomValues;
var rnds8 = new Uint8Array(16);

function rng() {
    if (!getRandomValues) {
        getRandomValues = typeof crypto !== "undefined" && crypto.getRandomValues && crypto.getRandomValues.bind(crypto);
        if (!getRandomValues) {
            throw new Error("crypto.getRandomValues() not supported. See https://github.com/uuidjs/uuid#getrandomvalues-not-supported");
        }
    }
    return getRandomValues(rnds8);
}

// node_modules/@smithy/middleware-retry/node_modules/uuid/dist/esm-browser/stringify.js
var byteToHex = [];
for (let i = 0; i < 256; ++i) {
    byteToHex.push((i + 256).toString(16).slice(1));
}

function unsafeStringify(arr, offset = 0) {
    return byteToHex[arr[offset + 0]] + byteToHex[arr[offset + 1]] + byteToHex[arr[offset + 2]] + byteToHex[arr[offset + 3]] + "-" + byteToHex[arr[offset + 4]] + byteToHex[arr[offset + 5]] + "-" + byteToHex[arr[offset + 6]] + byteToHex[arr[offset + 7]] + "-" + byteToHex[arr[offset + 8]] + byteToHex[arr[offset + 9]] + "-" + byteToHex[arr[offset + 10]] + byteToHex[arr[offset + 11]] + byteToHex[arr[offset + 12]] + byteToHex[arr[offset + 13]] + byteToHex[arr[offset + 14]] + byteToHex[arr[offset + 15]];
}

// node_modules/@smithy/middleware-retry/node_modules/uuid/dist/esm-browser/native.js
var randomUUID = typeof crypto !== "undefined" && crypto.randomUUID && crypto.randomUUID.bind(crypto);
var native_default = {
    randomUUID
};

// node_modules/@smithy/middleware-retry/node_modules/uuid/dist/esm-browser/v4.js
function v4(options, buf, offset) {
    if (native_default.randomUUID && !buf && !options) {
        return native_default.randomUUID();
    }
    options = options || {};
    const rnds = options.random || (options.rng || rng)();
    rnds[6] = rnds[6] & 15 | 64;
    rnds[8] = rnds[8] & 63 | 128;
    if (buf) {
        offset = offset || 0;
        for (let i = 0; i < 16; ++i) {
            buf[offset + i] = rnds[i];
        }
        return buf;
    }
    return unsafeStringify(rnds);
}

var v4_default = v4;

// node_modules/@smithy/middleware-retry/dist-es/isStreamingPayload/isStreamingPayload.browser.js
var isStreamingPayload = (request) => request?.body instanceof ReadableStream;

// node_modules/@smithy/middleware-retry/dist-es/util.js
var asSdkError = (error) => {
    if (error instanceof Error) return error;
    if (error instanceof Object) return Object.assign(new Error(), error);
    if (typeof error === "string") return new Error(error);
    return new Error(`AWS SDK error wrapper for ${error}`);
};

// node_modules/@smithy/middleware-retry/dist-es/retryMiddleware.js
var retryMiddleware = (options) => (next, context) => (args) => __async(void 0, null, function* () {
    let retryStrategy = yield options.retryStrategy();
    const maxAttempts = yield options.maxAttempts();
    if (isRetryStrategyV2(retryStrategy)) {
        retryStrategy = retryStrategy;
        let retryToken = yield retryStrategy.acquireInitialRetryToken(context["partition_id"]);
        let lastError = new Error();
        let attempts = 0;
        let totalRetryDelay = 0;
        const {
            request
        } = args;
        const isRequest = HttpRequest.isInstance(request);
        if (isRequest) {
            request.headers[INVOCATION_ID_HEADER] = v4_default();
        }
        while (true) {
            try {
                if (isRequest) {
                    request.headers[REQUEST_HEADER] = `attempt=${attempts + 1}; max=${maxAttempts}`;
                }
                const {
                    response,
                    output
                } = yield next(args);
                retryStrategy.recordSuccess(retryToken);
                output.$metadata.attempts = attempts + 1;
                output.$metadata.totalRetryDelay = totalRetryDelay;
                return {
                    response,
                    output
                };
            } catch (e) {
                const retryErrorInfo = getRetryErrorInfo(e);
                lastError = asSdkError(e);
                if (isRequest && isStreamingPayload(request)) {
                    (context.logger instanceof NoOpLogger ? console : context.logger)?.warn("An error was encountered in a non-retryable streaming request.");
                    throw lastError;
                }
                try {
                    retryToken = yield retryStrategy.refreshRetryTokenForRetry(retryToken, retryErrorInfo);
                } catch (refreshError) {
                    if (!lastError.$metadata) {
                        lastError.$metadata = {};
                    }
                    lastError.$metadata.attempts = attempts + 1;
                    lastError.$metadata.totalRetryDelay = totalRetryDelay;
                    throw lastError;
                }
                attempts = retryToken.getRetryCount();
                const delay = retryToken.getRetryDelay();
                totalRetryDelay += delay;
                yield new Promise((resolve) => setTimeout(resolve, delay));
            }
        }
    } else {
        retryStrategy = retryStrategy;
        if (retryStrategy?.mode) context.userAgent = [...context.userAgent || [], ["cfg/retry-mode", retryStrategy.mode]];
        return retryStrategy.retry(next, args);
    }
});
var isRetryStrategyV2 = (retryStrategy) => typeof retryStrategy.acquireInitialRetryToken !== "undefined" && typeof retryStrategy.refreshRetryTokenForRetry !== "undefined" && typeof retryStrategy.recordSuccess !== "undefined";
var getRetryErrorInfo = (error) => {
    const errorInfo = {
        error,
        errorType: getRetryErrorType(error)
    };
    const retryAfterHint = getRetryAfterHint(error.$response);
    if (retryAfterHint) {
        errorInfo.retryAfterHint = retryAfterHint;
    }
    return errorInfo;
};
var getRetryErrorType = (error) => {
    if (isThrottlingError(error)) return "THROTTLING";
    if (isTransientError(error)) return "TRANSIENT";
    if (isServerError(error)) return "SERVER_ERROR";
    return "CLIENT_ERROR";
};
var retryMiddlewareOptions = {
    name: "retryMiddleware",
    tags: ["RETRY"],
    step: "finalizeRequest",
    priority: "high",
    override: true
};
var getRetryPlugin = (options) => ({
    applyToStack: (clientStack) => {
        clientStack.add(retryMiddleware(options), retryMiddlewareOptions);
    }
});
var getRetryAfterHint = (response) => {
    if (!HttpResponse.isInstance(response)) return;
    const retryAfterHeaderName = Object.keys(response.headers).find((key) => key.toLowerCase() === "retry-after");
    if (!retryAfterHeaderName) return;
    const retryAfter = response.headers[retryAfterHeaderName];
    const retryAfterSeconds = Number(retryAfter);
    if (!Number.isNaN(retryAfterSeconds)) return new Date(retryAfterSeconds * 1e3);
    const retryAfterDate = new Date(retryAfter);
    return retryAfterDate;
};

// node_modules/@aws-crypto/util/node_modules/@smithy/util-utf8/dist-es/fromUtf8.browser.js
var fromUtf82 = (input) => new TextEncoder().encode(input);

// node_modules/@aws-crypto/util/build/module/convertToBuffer.js
var fromUtf83 = typeof Buffer !== "undefined" && Buffer.from ? function (input) {
    return Buffer.from(input, "utf8");
} : fromUtf82;

function convertToBuffer(data) {
    if (data instanceof Uint8Array) return data;
    if (typeof data === "string") {
        return fromUtf83(data);
    }
    if (ArrayBuffer.isView(data)) {
        return new Uint8Array(data.buffer, data.byteOffset, data.byteLength / Uint8Array.BYTES_PER_ELEMENT);
    }
    return new Uint8Array(data);
}

// node_modules/@aws-crypto/util/build/module/isEmptyData.js
function isEmptyData(data) {
    if (typeof data === "string") {
        return data.length === 0;
    }
    return data.byteLength === 0;
}

// node_modules/@aws-crypto/util/build/module/numToUint8.js
function numToUint8(num) {
    return new Uint8Array([(num & 4278190080) >> 24, (num & 16711680) >> 16, (num & 65280) >> 8, num & 255]);
}

// node_modules/@aws-crypto/util/build/module/uint32ArrayFrom.js
function uint32ArrayFrom(a_lookUpTable) {
    if (!Uint32Array.from) {
        var return_array = new Uint32Array(a_lookUpTable.length);
        var a_index = 0;
        while (a_index < a_lookUpTable.length) {
            return_array[a_index] = a_lookUpTable[a_index];
            a_index += 1;
        }
        return return_array;
    }
    return Uint32Array.from(a_lookUpTable);
}

// node_modules/@aws-crypto/sha256-browser/build/module/constants.js
var SHA_256_HASH = {
    name: "SHA-256"
};
var SHA_256_HMAC_ALGO = {
    name: "HMAC",
    hash: SHA_256_HASH
};
var EMPTY_DATA_SHA_256 = new Uint8Array([227, 176, 196, 66, 152, 252, 28, 20, 154, 251, 244, 200, 153, 111, 185, 36, 39, 174, 65, 228, 100, 155, 147, 76, 164, 149, 153, 27, 120, 82, 184, 85]);

// node_modules/@aws-sdk/util-locate-window/dist-es/index.js
var fallbackWindow = {};

function locateWindow() {
    if (typeof window !== "undefined") {
        return window;
    } else if (typeof self !== "undefined") {
        return self;
    }
    return fallbackWindow;
}

// node_modules/@aws-crypto/sha256-browser/build/module/webCryptoSha256.js
var Sha256 = (
    /** @class */
    function () {
        function Sha2564(secret) {
            this.toHash = new Uint8Array(0);
            this.secret = secret;
            this.reset();
        }

        Sha2564.prototype.update = function (data) {
            if (isEmptyData(data)) {
                return;
            }
            var update = convertToBuffer(data);
            var typedArray = new Uint8Array(this.toHash.byteLength + update.byteLength);
            typedArray.set(this.toHash, 0);
            typedArray.set(update, this.toHash.byteLength);
            this.toHash = typedArray;
        };
        Sha2564.prototype.digest = function () {
            var _this = this;
            if (this.key) {
                return this.key.then(function (key) {
                    return locateWindow().crypto.subtle.sign(SHA_256_HMAC_ALGO, key, _this.toHash).then(function (data) {
                        return new Uint8Array(data);
                    });
                });
            }
            if (isEmptyData(this.toHash)) {
                return Promise.resolve(EMPTY_DATA_SHA_256);
            }
            return Promise.resolve().then(function () {
                return locateWindow().crypto.subtle.digest(SHA_256_HASH, _this.toHash);
            }).then(function (data) {
                return Promise.resolve(new Uint8Array(data));
            });
        };
        Sha2564.prototype.reset = function () {
            var _this = this;
            this.toHash = new Uint8Array(0);
            if (this.secret && this.secret !== void 0) {
                this.key = new Promise(function (resolve, reject) {
                    locateWindow().crypto.subtle.importKey("raw", convertToBuffer(_this.secret), SHA_256_HMAC_ALGO, false, ["sign"]).then(resolve, reject);
                });
                this.key.catch(function () {
                });
            }
        };
        return Sha2564;
    }()
);

// node_modules/@aws-crypto/sha256-js/build/module/constants.js
var BLOCK_SIZE = 64;
var DIGEST_LENGTH = 32;
var KEY = new Uint32Array([1116352408, 1899447441, 3049323471, 3921009573, 961987163, 1508970993, 2453635748, 2870763221, 3624381080, 310598401, 607225278, 1426881987, 1925078388, 2162078206, 2614888103, 3248222580, 3835390401, 4022224774, 264347078, 604807628, 770255983, 1249150122, 1555081692, 1996064986, 2554220882, 2821834349, 2952996808, 3210313671, 3336571891, 3584528711, 113926993, 338241895, 666307205, 773529912, 1294757372, 1396182291, 1695183700, 1986661051, 2177026350, 2456956037, 2730485921, 2820302411, 3259730800, 3345764771, 3516065817, 3600352804, 4094571909, 275423344, 430227734, 506948616, 659060556, 883997877, 958139571, 1322822218, 1537002063, 1747873779, 1955562222, 2024104815, 2227730452, 2361852424, 2428436474, 2756734187, 3204031479, 3329325298]);
var INIT = [1779033703, 3144134277, 1013904242, 2773480762, 1359893119, 2600822924, 528734635, 1541459225];
var MAX_HASHABLE_LENGTH = Math.pow(2, 53) - 1;

// node_modules/@aws-crypto/sha256-js/build/module/RawSha256.js
var RawSha256 = (
    /** @class */
    function () {
        function RawSha2562() {
            this.state = Int32Array.from(INIT);
            this.temp = new Int32Array(64);
            this.buffer = new Uint8Array(64);
            this.bufferLength = 0;
            this.bytesHashed = 0;
            this.finished = false;
        }

        RawSha2562.prototype.update = function (data) {
            if (this.finished) {
                throw new Error("Attempted to update an already finished hash.");
            }
            var position = 0;
            var byteLength = data.byteLength;
            this.bytesHashed += byteLength;
            if (this.bytesHashed * 8 > MAX_HASHABLE_LENGTH) {
                throw new Error("Cannot hash more than 2^53 - 1 bits");
            }
            while (byteLength > 0) {
                this.buffer[this.bufferLength++] = data[position++];
                byteLength--;
                if (this.bufferLength === BLOCK_SIZE) {
                    this.hashBuffer();
                    this.bufferLength = 0;
                }
            }
        };
        RawSha2562.prototype.digest = function () {
            if (!this.finished) {
                var bitsHashed = this.bytesHashed * 8;
                var bufferView = new DataView(this.buffer.buffer, this.buffer.byteOffset, this.buffer.byteLength);
                var undecoratedLength = this.bufferLength;
                bufferView.setUint8(this.bufferLength++, 128);
                if (undecoratedLength % BLOCK_SIZE >= BLOCK_SIZE - 8) {
                    for (var i = this.bufferLength; i < BLOCK_SIZE; i++) {
                        bufferView.setUint8(i, 0);
                    }
                    this.hashBuffer();
                    this.bufferLength = 0;
                }
                for (var i = this.bufferLength; i < BLOCK_SIZE - 8; i++) {
                    bufferView.setUint8(i, 0);
                }
                bufferView.setUint32(BLOCK_SIZE - 8, Math.floor(bitsHashed / 4294967296), true);
                bufferView.setUint32(BLOCK_SIZE - 4, bitsHashed);
                this.hashBuffer();
                this.finished = true;
            }
            var out = new Uint8Array(DIGEST_LENGTH);
            for (var i = 0; i < 8; i++) {
                out[i * 4] = this.state[i] >>> 24 & 255;
                out[i * 4 + 1] = this.state[i] >>> 16 & 255;
                out[i * 4 + 2] = this.state[i] >>> 8 & 255;
                out[i * 4 + 3] = this.state[i] >>> 0 & 255;
            }
            return out;
        };
        RawSha2562.prototype.hashBuffer = function () {
            var _a = this, buffer = _a.buffer, state = _a.state;
            var state0 = state[0], state1 = state[1], state2 = state[2], state3 = state[3], state4 = state[4], state5 = state[5], state6 = state[6], state7 = state[7];
            for (var i = 0; i < BLOCK_SIZE; i++) {
                if (i < 16) {
                    this.temp[i] = (buffer[i * 4] & 255) << 24 | (buffer[i * 4 + 1] & 255) << 16 | (buffer[i * 4 + 2] & 255) << 8 | buffer[i * 4 + 3] & 255;
                } else {
                    var u = this.temp[i - 2];
                    var t1_1 = (u >>> 17 | u << 15) ^ (u >>> 19 | u << 13) ^ u >>> 10;
                    u = this.temp[i - 15];
                    var t2_1 = (u >>> 7 | u << 25) ^ (u >>> 18 | u << 14) ^ u >>> 3;
                    this.temp[i] = (t1_1 + this.temp[i - 7] | 0) + (t2_1 + this.temp[i - 16] | 0);
                }
                var t1 = (((state4 >>> 6 | state4 << 26) ^ (state4 >>> 11 | state4 << 21) ^ (state4 >>> 25 | state4 << 7)) + (state4 & state5 ^ ~state4 & state6) | 0) + (state7 + (KEY[i] + this.temp[i] | 0) | 0) | 0;
                var t2 = ((state0 >>> 2 | state0 << 30) ^ (state0 >>> 13 | state0 << 19) ^ (state0 >>> 22 | state0 << 10)) + (state0 & state1 ^ state0 & state2 ^ state1 & state2) | 0;
                state7 = state6;
                state6 = state5;
                state5 = state4;
                state4 = state3 + t1 | 0;
                state3 = state2;
                state2 = state1;
                state1 = state0;
                state0 = t1 + t2 | 0;
            }
            state[0] += state0;
            state[1] += state1;
            state[2] += state2;
            state[3] += state3;
            state[4] += state4;
            state[5] += state5;
            state[6] += state6;
            state[7] += state7;
        };
        return RawSha2562;
    }()
);

// node_modules/@aws-crypto/sha256-js/build/module/jsSha256.js
var Sha2562 = (
    /** @class */
    function () {
        function Sha2564(secret) {
            this.secret = secret;
            this.hash = new RawSha256();
            this.reset();
        }

        Sha2564.prototype.update = function (toHash) {
            if (isEmptyData(toHash) || this.error) {
                return;
            }
            try {
                this.hash.update(convertToBuffer(toHash));
            } catch (e) {
                this.error = e;
            }
        };
        Sha2564.prototype.digestSync = function () {
            if (this.error) {
                throw this.error;
            }
            if (this.outer) {
                if (!this.outer.finished) {
                    this.outer.update(this.hash.digest());
                }
                return this.outer.digest();
            }
            return this.hash.digest();
        };
        Sha2564.prototype.digest = function () {
            return __awaiter(this, void 0, void 0, function () {
                return __generator(this, function (_a) {
                    return [2, this.digestSync()];
                });
            });
        };
        Sha2564.prototype.reset = function () {
            this.hash = new RawSha256();
            if (this.secret) {
                this.outer = new RawSha256();
                var inner = bufferFromSecret(this.secret);
                var outer = new Uint8Array(BLOCK_SIZE);
                outer.set(inner);
                for (var i = 0; i < BLOCK_SIZE; i++) {
                    inner[i] ^= 54;
                    outer[i] ^= 92;
                }
                this.hash.update(inner);
                this.outer.update(outer);
                for (var i = 0; i < inner.byteLength; i++) {
                    inner[i] = 0;
                }
            }
        };
        return Sha2564;
    }()
);

function bufferFromSecret(secret) {
    var input = convertToBuffer(secret);
    if (input.byteLength > BLOCK_SIZE) {
        var bufferHash = new RawSha256();
        bufferHash.update(input);
        input = bufferHash.digest();
    }
    var buffer = new Uint8Array(BLOCK_SIZE);
    buffer.set(input);
    return buffer;
}

// node_modules/@aws-crypto/supports-web-crypto/build/module/supportsWebCrypto.js
var subtleCryptoMethods = ["decrypt", "digest", "encrypt", "exportKey", "generateKey", "importKey", "sign", "verify"];

function supportsWebCrypto(window2) {
    if (supportsSecureRandom(window2) && typeof window2.crypto.subtle === "object") {
        var subtle = window2.crypto.subtle;
        return supportsSubtleCrypto(subtle);
    }
    return false;
}

function supportsSecureRandom(window2) {
    if (typeof window2 === "object" && typeof window2.crypto === "object") {
        var getRandomValues2 = window2.crypto.getRandomValues;
        return typeof getRandomValues2 === "function";
    }
    return false;
}

function supportsSubtleCrypto(subtle) {
    return subtle && subtleCryptoMethods.every(function (methodName) {
        return typeof subtle[methodName] === "function";
    });
}

// node_modules/@aws-crypto/sha256-browser/build/module/crossPlatformSha256.js
var Sha2563 = (
    /** @class */
    function () {
        function Sha2564(secret) {
            if (supportsWebCrypto(locateWindow())) {
                this.hash = new Sha256(secret);
            } else {
                this.hash = new Sha2562(secret);
            }
        }

        Sha2564.prototype.update = function (data, encoding) {
            this.hash.update(convertToBuffer(data));
        };
        Sha2564.prototype.digest = function () {
            return this.hash.digest();
        };
        Sha2564.prototype.reset = function () {
            this.hash.reset();
        };
        return Sha2564;
    }()
);

// node_modules/@aws-sdk/util-user-agent-browser/dist-es/index.js
var import_bowser = __toESM(require_es5());
var createDefaultUserAgentProvider = ({
                                          serviceId,
                                          clientVersion
                                      }) => (config) => __async(void 0, null, function* () {
    const parsedUA = typeof window !== "undefined" && window?.navigator?.userAgent ? import_bowser.default.parse(window.navigator.userAgent) : void 0;
    const sections = [["aws-sdk-js", clientVersion], ["ua", "2.1"], [`os/${parsedUA?.os?.name || "other"}`, parsedUA?.os?.version], ["lang/js"], ["md/browser", `${parsedUA?.browser?.name ?? "unknown"}_${parsedUA?.browser?.version ?? "unknown"}`]];
    if (serviceId) {
        sections.push([`api/${serviceId}`, clientVersion]);
    }
    const appId = yield config?.userAgentAppId?.();
    if (appId) {
        sections.push([`app/${appId}`]);
    }
    return sections;
});

// node_modules/@smithy/invalid-dependency/dist-es/invalidProvider.js
var invalidProvider = (message) => () => Promise.reject(message);

// node_modules/@smithy/util-body-length-browser/dist-es/calculateBodyLength.js
var TEXT_ENCODER = typeof TextEncoder == "function" ? new TextEncoder() : null;
var calculateBodyLength = (body) => {
    if (typeof body === "string") {
        if (TEXT_ENCODER) {
            return TEXT_ENCODER.encode(body).byteLength;
        }
        let len = body.length;
        for (let i = len - 1; i >= 0; i--) {
            const code = body.charCodeAt(i);
            if (code > 127 && code <= 2047) len++;
            else if (code > 2047 && code <= 65535) len += 2;
            if (code >= 56320 && code <= 57343) i--;
        }
        return len;
    } else if (typeof body.byteLength === "number") {
        return body.byteLength;
    } else if (typeof body.size === "number") {
        return body.size;
    }
    throw new Error(`Body Length computation failed for ${body}`);
};

// node_modules/@smithy/util-defaults-mode-browser/dist-es/resolveDefaultsModeConfig.js
var import_bowser2 = __toESM(require_es5());

// node_modules/@smithy/util-defaults-mode-browser/dist-es/constants.js
var DEFAULTS_MODE_OPTIONS = ["in-region", "cross-region", "mobile", "standard", "legacy"];

// node_modules/@smithy/util-defaults-mode-browser/dist-es/resolveDefaultsModeConfig.js
var resolveDefaultsModeConfig = ({
                                     defaultsMode
                                 } = {}) => memoize(() => __async(void 0, null, function* () {
    const mode = typeof defaultsMode === "function" ? yield defaultsMode() : defaultsMode;
    switch (mode?.toLowerCase()) {
        case "auto":
            return Promise.resolve(isMobileBrowser() ? "mobile" : "standard");
        case "mobile":
        case "in-region":
        case "cross-region":
        case "standard":
        case "legacy":
            return Promise.resolve(mode?.toLocaleLowerCase());
        case void 0:
            return Promise.resolve("legacy");
        default:
            throw new Error(`Invalid parameter for "defaultsMode", expect ${DEFAULTS_MODE_OPTIONS.join(", ")}, got ${mode}`);
    }
}));
var isMobileBrowser = () => {
    const parsedUA = typeof window !== "undefined" && window?.navigator?.userAgent ? import_bowser2.default.parse(window.navigator.userAgent) : void 0;
    const platform = parsedUA?.platform?.type;
    return platform === "tablet" || platform === "mobile";
};

// node_modules/@aws-sdk/region-config-resolver/dist-es/extensions/index.js
var getAwsRegionExtensionConfiguration = (runtimeConfig) => {
    let runtimeConfigRegion = () => __async(void 0, null, function* () {
        if (runtimeConfig.region === void 0) {
            throw new Error("Region is missing from runtimeConfig");
        }
        const region = runtimeConfig.region;
        if (typeof region === "string") {
            return region;
        }
        return region();
    });
    return {
        setRegion(region) {
            runtimeConfigRegion = region;
        },
        region() {
            return runtimeConfigRegion;
        }
    };
};
var resolveAwsRegionExtensionConfiguration = (awsRegionExtensionConfiguration) => {
    return {
        region: awsRegionExtensionConfiguration.region()
    };
};

export {
    byteConversion,
    getHttpHandlerExtensionConfiguration,
    resolveHttpHandlerRuntimeConfig,
    HttpRequest,
    HttpResponse,
    resolveHostHeaderConfig,
    getHostHeaderPlugin,
    getLoggerPlugin,
    getRecursionDetectionPlugin,
    Client,
    fromBase64,
    fromUtf8,
    toUint8Array,
    toUtf8,
    toBase64,
    getAwsChunkedEncodingStream,
    FetchHttpHandler,
    streamCollector,
    fromHex,
    toHex,
    sdkStreamMixin,
    splitStream,
    headStream,
    createChecksumStream,
    collectBody,
    extendedEncodeURIComponent,
    requestBuilder,
    Command,
    SENSITIVE_STRING,
    parseBoolean,
    expectNonNull,
    expectObject,
    expectString,
    strictParseLong,
    strictParseInt32,
    dateToUtcString,
    parseRfc3339DateTimeWithOffset,
    parseRfc7231DateTime,
    ServiceException,
    decorateServiceException,
    withBaseException,
    loadConfigsForDefaultMode,
    getDefaultExtensionConfiguration,
    resolveDefaultRuntimeConfig,
    getArrayIfSingleItem,
    getValueFromTextNode,
    isSerializableHeaderValue,
    NoOpLogger,
    map,
    take,
    quoteHeader,
    serializeDateTime,
    _json,
    getSmithyContext,
    normalizeProvider,
    getHttpAuthSchemeEndpointRuleSetPlugin,
    getSerdePlugin,
    httpSigningMiddlewareOptions,
    getHttpSigningPlugin,
    DefaultIdentityProviderConfig,
    resolveUserAgentConfig,
    EndpointCache,
    customEndpointFunctions,
    resolveEndpoint,
    awsEndpointFunctions,
    setFeature2 as setFeature,
    AwsSdkSigV4Signer,
    AwsSdkSigV4ASigner,
    resolveAwsSdkSigV4AConfig,
    isArrayBuffer,
    SignatureV4,
    resolveAwsSdkSigV4Config,
    collectBodyString,
    getUserAgentPlugin,
    DEFAULT_USE_DUALSTACK_ENDPOINT,
    DEFAULT_USE_FIPS_ENDPOINT,
    resolveRegionConfig,
    getContentLengthPlugin,
    parseUrl,
    resolveParams,
    getEndpointPlugin,
    resolveEndpointConfig,
    DEFAULT_MAX_ATTEMPTS,
    DEFAULT_RETRY_MODE,
    resolveRetryConfig,
    getRetryPlugin,
    convertToBuffer,
    isEmptyData,
    numToUint8,
    uint32ArrayFrom,
    locateWindow,
    supportsWebCrypto,
    Sha2563 as Sha256,
    createDefaultUserAgentProvider,
    invalidProvider,
    calculateBodyLength,
    resolveDefaultsModeConfig,
    getAwsRegionExtensionConfiguration,
    resolveAwsRegionExtensionConfiguration
};
//# sourceMappingURL=chunk-5F2IFVYA.js.map

import {FileImportComponent} from "./chunk-E2KWZO4F.js";
import {require_FileSaver_min} from "./chunk-MHNP2PIU.js";
import {CdkDrag, CdkDragHandle} from "./chunk-L5B3QUPF.js";
import {ManagerConfig, MonitoringConfig} from "./chunk-4IO3RYFH.js";
import {
    _MatInternalFormField,
    Actions,
    ANIMATION_MODULE_TYPE,
    asapScheduler,
    Attribute,
    booleanAttribute,
    catchError,
    CdkTextareaAutosize,
    ChangeDetectionStrategy,
    ChangeDetectorRef,
    CheckboxRequiredValidator,
    Component,
    ContentChildren,
    createAction,
    createEffect,
    createReducer,
    DatePipe,
    DefaultValueAccessor,
    Directive,
    DOCUMENT,
    EffectsModule,
    ElementRef,
    environment,
    EventEmitter,
    FormsModule,
    forwardRef,
    HttpClient,
    Inject,
    inject,
    InjectionToken,
    Input,
    interval,
    isPlatformBrowser,
    map,
    MAT_DIALOG_DATA,
    MatButton,
    MatButtonModule,
    MatCard,
    MatCardActions,
    MatCardContent,
    MatCardHeader,
    MatCardModule,
    MatCardTitle,
    MatCommonModule,
    MatDialog,
    MatDialogActions,
    MatDialogClose,
    MatDialogConfig,
    MatDialogContent,
    MatDialogRef,
    MatDialogTitle,
    MatFormField,
    MatFormFieldModule,
    MatGridList,
    MatGridTile,
    MatIcon,
    MatIconModule,
    MatInput,
    MatInputModule,
    MatLabel,
    MatList,
    MatListItem,
    MatListModule,
    MatNavList,
    MatOption,
    MatOptionModule,
    MatRipple,
    MatSelect,
    MatSelectModule,
    MatSnackBar,
    MatTableModule,
    MatTooltip,
    MatTooltipModule,
    mergeMap,
    NG_VALIDATORS,
    NG_VALUE_ACCESSOR,
    NgControlStatus,
    NgForOf,
    NgIf,
    NgModel,
    NgModule,
    NgZone,
    numberAttribute,
    of,
    ofType,
    Optional,
    Output,
    Platform,
    PLATFORM_ID,
    props,
    ReactiveFormsModule,
    RouterModule,
    setClassMetadata,
    signal,
    SlicePipe,
    Store,
    StoreModule,
    throwError,
    ViewChild,
    ViewEncapsulation$1
} from "./chunk-LGOS2CJL.js";
import {__async, __toESM} from "./chunk-G42SKTPL.js";

// node_modules/ng-apexcharts/fesm2022/ng-apexcharts.mjs
var _c0 = ["chart"];
var ChartComponent = class _ChartComponent {
    constructor() {
        this.autoUpdateSeries = true;
        this.chartReady = new EventEmitter();
        this.chartInstance = signal(null);
        this.ngZone = inject(NgZone);
        this.isBrowser = isPlatformBrowser(inject(PLATFORM_ID));
    }

    ngOnChanges(changes) {
        if (!this.isBrowser) return;
        this.ngZone.runOutsideAngular(() => {
            asapScheduler.schedule(() => this.hydrate(changes));
        });
    }

    ngOnDestroy() {
        this.destroy();
    }

    hydrate(changes) {
        const shouldUpdateSeries = this.autoUpdateSeries && Object.keys(changes).filter((c) => c !== "series").length === 0;
        if (shouldUpdateSeries) {
            this.updateSeries(this.series, true);
            return;
        }
        this.createElement();
    }

    createElement() {
        return __async(this, null, function* () {
            const {
                default: ApexCharts
            } = yield import("./chunk-BI6O2Z7H.js");
            window.ApexCharts ||= ApexCharts;
            const options = {};
            if (this.annotations) {
                options.annotations = this.annotations;
            }
            if (this.chart) {
                options.chart = this.chart;
            }
            if (this.colors) {
                options.colors = this.colors;
            }
            if (this.dataLabels) {
                options.dataLabels = this.dataLabels;
            }
            if (this.series) {
                options.series = this.series;
            }
            if (this.stroke) {
                options.stroke = this.stroke;
            }
            if (this.labels) {
                options.labels = this.labels;
            }
            if (this.legend) {
                options.legend = this.legend;
            }
            if (this.fill) {
                options.fill = this.fill;
            }
            if (this.tooltip) {
                options.tooltip = this.tooltip;
            }
            if (this.plotOptions) {
                options.plotOptions = this.plotOptions;
            }
            if (this.responsive) {
                options.responsive = this.responsive;
            }
            if (this.markers) {
                options.markers = this.markers;
            }
            if (this.noData) {
                options.noData = this.noData;
            }
            if (this.xaxis) {
                options.xaxis = this.xaxis;
            }
            if (this.yaxis) {
                options.yaxis = this.yaxis;
            }
            if (this.forecastDataPoints) {
                options.forecastDataPoints = this.forecastDataPoints;
            }
            if (this.grid) {
                options.grid = this.grid;
            }
            if (this.states) {
                options.states = this.states;
            }
            if (this.title) {
                options.title = this.title;
            }
            if (this.subtitle) {
                options.subtitle = this.subtitle;
            }
            if (this.theme) {
                options.theme = this.theme;
            }
            this.destroy();
            const chartInstance = this.ngZone.runOutsideAngular(() => new ApexCharts(this.chartElement.nativeElement, options));
            this.chartInstance.set(chartInstance);
            this.render();
            this.chartReady.emit({
                chartObj: chartInstance
            });
        });
    }

    render() {
        return this.ngZone.runOutsideAngular(() => this.chartInstance()?.render());
    }

    updateOptions(options, redrawPaths, animate, updateSyncedCharts) {
        return this.ngZone.runOutsideAngular(() => this.chartInstance()?.updateOptions(options, redrawPaths, animate, updateSyncedCharts));
    }

    updateSeries(newSeries, animate) {
        return this.ngZone.runOutsideAngular(() => this.chartInstance()?.updateSeries(newSeries, animate));
    }

    appendSeries(newSeries, animate) {
        this.ngZone.runOutsideAngular(() => this.chartInstance()?.appendSeries(newSeries, animate));
    }

    appendData(newData) {
        this.ngZone.runOutsideAngular(() => this.chartInstance()?.appendData(newData));
    }

    highlightSeries(seriesName) {
        return this.ngZone.runOutsideAngular(() => this.chartInstance()?.highlightSeries(seriesName));
    }

    toggleSeries(seriesName) {
        return this.ngZone.runOutsideAngular(() => this.chartInstance()?.toggleSeries(seriesName));
    }

    showSeries(seriesName) {
        this.ngZone.runOutsideAngular(() => this.chartInstance()?.showSeries(seriesName));
    }

    hideSeries(seriesName) {
        this.ngZone.runOutsideAngular(() => this.chartInstance()?.hideSeries(seriesName));
    }

    resetSeries() {
        this.ngZone.runOutsideAngular(() => this.chartInstance()?.resetSeries());
    }

    zoomX(min, max) {
        this.ngZone.runOutsideAngular(() => this.chartInstance()?.zoomX(min, max));
    }

    toggleDataPointSelection(seriesIndex, dataPointIndex) {
        this.ngZone.runOutsideAngular(() => this.chartInstance()?.toggleDataPointSelection(seriesIndex, dataPointIndex));
    }

    destroy() {
        this.chartInstance()?.destroy();
        this.chartInstance.set(null);
    }

    setLocale(localeName) {
        this.ngZone.runOutsideAngular(() => this.chartInstance()?.setLocale(localeName));
    }

    paper() {
        this.ngZone.runOutsideAngular(() => this.chartInstance()?.paper());
    }

    addXaxisAnnotation(options, pushToMemory, context) {
        this.ngZone.runOutsideAngular(() => this.chartInstance()?.addXaxisAnnotation(options, pushToMemory, context));
    }

    addYaxisAnnotation(options, pushToMemory, context) {
        this.ngZone.runOutsideAngular(() => this.chartInstance()?.addYaxisAnnotation(options, pushToMemory, context));
    }

    addPointAnnotation(options, pushToMemory, context) {
        this.ngZone.runOutsideAngular(() => this.chartInstance()?.addPointAnnotation(options, pushToMemory, context));
    }

    removeAnnotation(id, options) {
        this.ngZone.runOutsideAngular(() => this.chartInstance()?.removeAnnotation(id, options));
    }

    clearAnnotations(options) {
        this.ngZone.runOutsideAngular(() => this.chartInstance()?.clearAnnotations(options));
    }

    dataURI(options) {
        return this.chartInstance()?.dataURI(options);
    }

    static {
        this.\u0275fac = function ChartComponent_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _ChartComponent)();
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _ChartComponent,
            selectors: [["apx-chart"]],
            viewQuery: function ChartComponent_Query(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275viewQuery(_c0, 7);
                }
                if (rf & 2) {
                    let _t;
                    \u0275\u0275queryRefresh(_t = \u0275\u0275loadQuery()) && (ctx.chartElement = _t.first);
                }
            },
            inputs: {
                chart: "chart",
                annotations: "annotations",
                colors: "colors",
                dataLabels: "dataLabels",
                series: "series",
                stroke: "stroke",
                labels: "labels",
                legend: "legend",
                markers: "markers",
                noData: "noData",
                fill: "fill",
                tooltip: "tooltip",
                plotOptions: "plotOptions",
                responsive: "responsive",
                xaxis: "xaxis",
                yaxis: "yaxis",
                forecastDataPoints: "forecastDataPoints",
                grid: "grid",
                states: "states",
                title: "title",
                subtitle: "subtitle",
                theme: "theme",
                autoUpdateSeries: "autoUpdateSeries"
            },
            outputs: {
                chartReady: "chartReady"
            },
            standalone: true,
            features: [\u0275\u0275NgOnChangesFeature, \u0275\u0275StandaloneFeature],
            decls: 2,
            vars: 0,
            consts: [["chart", ""]],
            template: function ChartComponent_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275element(0, "div", null, 0);
                }
            },
            encapsulation: 2,
            changeDetection: 0
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && setClassMetadata(ChartComponent, [{
        type: Component,
        args: [{
            selector: "apx-chart",
            template: `<div #chart></div>`,
            changeDetection: ChangeDetectionStrategy.OnPush,
            standalone: true
        }]
    }], null, {
        chart: [{
            type: Input
        }],
        annotations: [{
            type: Input
        }],
        colors: [{
            type: Input
        }],
        dataLabels: [{
            type: Input
        }],
        series: [{
            type: Input
        }],
        stroke: [{
            type: Input
        }],
        labels: [{
            type: Input
        }],
        legend: [{
            type: Input
        }],
        markers: [{
            type: Input
        }],
        noData: [{
            type: Input
        }],
        fill: [{
            type: Input
        }],
        tooltip: [{
            type: Input
        }],
        plotOptions: [{
            type: Input
        }],
        responsive: [{
            type: Input
        }],
        xaxis: [{
            type: Input
        }],
        yaxis: [{
            type: Input
        }],
        forecastDataPoints: [{
            type: Input
        }],
        grid: [{
            type: Input
        }],
        states: [{
            type: Input
        }],
        title: [{
            type: Input
        }],
        subtitle: [{
            type: Input
        }],
        theme: [{
            type: Input
        }],
        autoUpdateSeries: [{
            type: Input
        }],
        chartReady: [{
            type: Output
        }],
        chartElement: [{
            type: ViewChild,
            args: ["chart", {
                static: true
            }]
        }]
    });
})();
var declarations = [ChartComponent];
var NgApexchartsModule = class _NgApexchartsModule {
    static {
        this.\u0275fac = function NgApexchartsModule_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _NgApexchartsModule)();
        };
    }
    static {
        this.\u0275mod = /* @__PURE__ */ \u0275\u0275defineNgModule({
            type: _NgApexchartsModule
        });
    }
    static {
        this.\u0275inj = /* @__PURE__ */ \u0275\u0275defineInjector({});
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && setClassMetadata(NgApexchartsModule, [{
        type: NgModule,
        args: [{
            imports: [declarations],
            exports: [declarations]
        }]
    }], null, null);
})();

// src/app/services/monitoring.service.ts
var MonitoringService = class _MonitoringService {
    constructor(http) {
        this.http = http;
        this.monitoringConfig = new MonitoringConfig();
        this.url = environment.gatewayEndpoint + "/";
    }

    /**
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     */
    getCounters(name, start, end, step) {
        let headers = this.monitoringConfig.monitoringHttpOptions.headers.set("x-awsmock-Target", "monitoring").set("x-awsmock-action", "get-counters");
        const body = {
            region: environment.awsmockRegion,
            name,
            start: start.getTime(),
            end: end.getTime(),
            step
        };
        return this.http.post(this.url, body, {headers});
    }

    static {
        this.\u0275fac = function MonitoringService_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _MonitoringService)(\u0275\u0275inject(HttpClient));
        };
    }
    static {
        this.\u0275prov = /* @__PURE__ */ \u0275\u0275defineInjectable({token: _MonitoringService, factory: _MonitoringService.\u0275fac});
    }
};

// src/app/services/chart-service.component.ts
var TimeRanges = [
    {value: "Today", viewValue: "Today"},
    {value: "LastHour", viewValue: "Last Hour"},
    {value: "Last3Hours", viewValue: "Last 3 Hours"},
    {value: "Last6Hours", viewValue: "Last 6 Hours"},
    {value: "Last12Hours", viewValue: "Last 12 Hours"}
];
var ChartService = class _ChartService {
    constructor() {
    }

    getAnimation() {
        return {enabled: false};
    }

    getRanges() {
        return TimeRanges;
    }

    getDefaultRange() {
        return TimeRanges[0].value;
    }

    getStartTime(choice) {
        let startTime = /* @__PURE__ */ new Date();
        if (choice == "Today") {
            startTime.setHours(0, 0, 0, 0);
        } else if (choice == "LastHour") {
            startTime.setHours(startTime.getHours() - 1);
        } else if (choice == "Last3Hours") {
            startTime.setHours(startTime.getHours() - 3);
        } else if (choice == "Last6Hours") {
            startTime.setHours(startTime.getHours() - 6);
        } else if (choice == "Last12Hours") {
            startTime.setHours(startTime.getHours() - 12);
        }
        startTime.setSeconds(0);
        startTime.setMilliseconds(0);
        return startTime;
    }

    getEndTime() {
        let endTime = /* @__PURE__ */ new Date();
        endTime.setSeconds(0);
        endTime.setMilliseconds(0);
        return endTime;
    }

    static {
        this.\u0275fac = function ChartService_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _ChartService)();
        };
    }
    static {
        this.\u0275prov = /* @__PURE__ */ \u0275\u0275defineInjectable({token: _ChartService, factory: _ChartService.\u0275fac, providedIn: "root"});
    }
};

// src/app/modules/dashboard/charts/cpu-chart/cpu-chart.component.ts
var _c02 = ["cpuChart"];

function CpuChartComponent_For_10_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "mat-option", 6);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const range_r1 = ctx.$implicit;
        \u0275\u0275property("value", range_r1.value);
        \u0275\u0275advance();
        \u0275\u0275textInterpolate(range_r1.viewValue);
    }
}

function CpuChartComponent_apx_chart_12_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "apx-chart", 8);
    }
    if (rf & 2) {
        const ctx_r1 = \u0275\u0275nextContext();
        \u0275\u0275property("chart", ctx_r1.cpuChartOptions.chart)("dataLabels", ctx_r1.cpuChartOptions.dataLabels)("grid", ctx_r1.cpuChartOptions.grid)("series", ctx_r1.cpuChartOptions.series)("stroke", ctx_r1.cpuChartOptions.stroke)("title", ctx_r1.cpuChartOptions.title)("tooltip", ctx_r1.cpuChartOptions.tooltip)("xaxis", ctx_r1.cpuChartOptions.xaxis)("yaxis", ctx_r1.cpuChartOptions.yaxis);
    }
}

var CpuChartComponent = class _CpuChartComponent {
    constructor(monitoringService, chartService) {
        this.monitoringService = monitoringService;
        this.chartService = chartService;
        this.ranges = [];
        this.selectedTimeRange = "";
    }

    ngOnInit() {
        this.ranges = this.chartService.getRanges();
        this.selectedTimeRange = this.chartService.getDefaultRange();
        this.loadCpuChart();
    }

    loadCpuChart() {
        let start = this.chartService.getStartTime(this.selectedTimeRange);
        let end = this.chartService.getEndTime();
        this.monitoringService.getCounters("total_cpu", start, end, 5).subscribe((data) => {
            if (data) {
                this.cpuChartOptions = {
                    series: [{name: "CPU Usage", data: data.counters}],
                    chart: {height: 350, type: "line", animations: this.chartService.getAnimation()},
                    dataLabels: {enabled: false},
                    stroke: {show: true, curve: "smooth", width: 2},
                    tooltip: {shared: true, x: {format: "dd/MM HH:mm:ss"}},
                    title: {text: "CPU", align: "center"},
                    grid: {row: {colors: ["#f3f3f3", "transparent"], opacity: 0.5}, column: {colors: ["#f3f3f3", "transparent"], opacity: 0.5}},
                    xaxis: {type: "datetime", title: {text: "Time"}, labels: {datetimeUTC: false}, min: start.getTime(), max: end.getTime()},
                    yaxis: {min: 0, decimalsInFloat: 3, title: {text: "CPU [%]"}, labels: {offsetX: 10}}
                };
            }
        });
    }

    static {
        this.\u0275fac = function CpuChartComponent_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _CpuChartComponent)(\u0275\u0275directiveInject(MonitoringService), \u0275\u0275directiveInject(ChartService));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _CpuChartComponent,
            selectors: [["cpu-chart-component"]],
            viewQuery: function CpuChartComponent_Query(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275viewQuery(_c02, 5);
                }
                if (rf & 2) {
                    let _t;
                    \u0275\u0275queryRefresh(_t = \u0275\u0275loadQuery()) && (ctx.cpuChart = _t.first);
                }
            },
            standalone: true,
            features: [\u0275\u0275StandaloneFeature],
            decls: 13,
            vars: 2,
            consts: [[1, "mat-elevation-z4"], [1, "container"], [1, "flex-container-left"], [1, "flex-item"], [1, "flex-container-right"], [2, "width", "200px", 3, "selectionChange", "ngModelChange", "ngModel"], [3, "value"], [3, "chart", "dataLabels", "grid", "series", "stroke", "title", "tooltip", "xaxis", "yaxis", 4, "ngIf"], [3, "chart", "dataLabels", "grid", "series", "stroke", "title", "tooltip", "xaxis", "yaxis"]],
            template: function CpuChartComponent_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "mat-card", 0)(1, "mat-card-header")(2, "div", 1)(3, "div", 2);
                    \u0275\u0275element(4, "div", 3);
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(5, "div", 4)(6, "div", 3)(7, "mat-card-actions")(8, "mat-select", 5);
                    \u0275\u0275listener("selectionChange", function CpuChartComponent_Template_mat_select_selectionChange_8_listener() {
                        return ctx.loadCpuChart();
                    });
                    \u0275\u0275twoWayListener("ngModelChange", function CpuChartComponent_Template_mat_select_ngModelChange_8_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.selectedTimeRange, $event) || (ctx.selectedTimeRange = $event);
                        return $event;
                    });
                    \u0275\u0275repeaterCreate(9, CpuChartComponent_For_10_Template, 2, 2, "mat-option", 6, \u0275\u0275repeaterTrackByIdentity);
                    \u0275\u0275elementEnd()()()()()();
                    \u0275\u0275elementStart(11, "mat-card-content");
                    \u0275\u0275template(12, CpuChartComponent_apx_chart_12_Template, 1, 9, "apx-chart", 7);
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    \u0275\u0275advance(8);
                    \u0275\u0275twoWayProperty("ngModel", ctx.selectedTimeRange);
                    \u0275\u0275advance();
                    \u0275\u0275repeater(ctx.ranges);
                    \u0275\u0275advance(3);
                    \u0275\u0275property("ngIf", ctx.cpuChartOptions);
                }
            },
            dependencies: [
                MatCard,
                MatCardHeader,
                MatCardActions,
                MatSelect,
                FormsModule,
                NgControlStatus,
                NgModel,
                MatOption,
                MatCardContent,
                ChartComponent,
                NgIf
            ],
            styles: ["\n\nbody[_ngcontent-%COMP%] {\n  margin: 40px;\n}\n.wrapper[_ngcontent-%COMP%] {\n  display: grid;\n  grid-template-columns: 1fr 1fr 1fr;\n  grid-gap: 10px;\n  background-color: #fff;\n  color: #444;\n  padding: 10px;\n}\n.box[_ngcontent-%COMP%] {\n  background-color: #444;\n  color: #fff;\n  border-radius: 5px;\n  padding: 20px;\n  height: 400px;\n}\n.container[_ngcontent-%COMP%] {\n  margin: 0 auto;\n  width: 100%;\n  display: flex;\n  align-items: center;\n  justify-content: space-between;\n}\n.flex-container-left[_ngcontent-%COMP%] {\n  display: flex;\n  align-items: flex-start;\n  justify-content: flex-start;\n  height: 100%;\n}\n.flex-container-right[_ngcontent-%COMP%] {\n  display: flex;\n  align-items: flex-start;\n  justify-content: flex-end;\n  height: 100%;\n}\n.flex-item[_ngcontent-%COMP%] {\n  margin: 5px;\n  height: 100%;\n}\n.card-header[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: start;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  justify-content: flex-start;\n}\n.action-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  justify-content: flex-end;\n}\n.full-screen-modal[_ngcontent-%COMP%]   .mat-dialog-container[_ngcontent-%COMP%] {\n  max-width: none;\n}\n.body[_ngcontent-%COMP%] {\n  flex-grow: 1;\n  overflow: hidden;\n}\n.footer[_ngcontent-%COMP%] {\n  display: flex;\n  width: 50%;\n  font-size: x-small;\n  color: black;\n}\n/*# sourceMappingURL=cpu-chart.component.css.map */"]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(CpuChartComponent, {
        className: "CpuChartComponent",
        filePath: "src/app/modules/dashboard/charts/cpu-chart/cpu-chart.component.ts",
        lineNumber: 50
    });
})();

// src/app/modules/dashboard/charts/thread-chart/threads-chart.component.ts
var _c03 = ["threadsChart"];

function ThreadsChartComponent_For_10_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "mat-option", 6);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const range_r1 = ctx.$implicit;
        \u0275\u0275property("value", range_r1.value);
        \u0275\u0275advance();
        \u0275\u0275textInterpolate(range_r1.viewValue);
    }
}

function ThreadsChartComponent_apx_chart_12_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "apx-chart", 8);
    }
    if (rf & 2) {
        const ctx_r1 = \u0275\u0275nextContext();
        \u0275\u0275property("chart", ctx_r1.threadsChartOptions.chart)("dataLabels", ctx_r1.threadsChartOptions.dataLabels)("grid", ctx_r1.threadsChartOptions.grid)("series", ctx_r1.threadsChartOptions.series)("stroke", ctx_r1.threadsChartOptions.stroke)("title", ctx_r1.threadsChartOptions.title)("tooltip", ctx_r1.threadsChartOptions.tooltip)("xaxis", ctx_r1.threadsChartOptions.xaxis)("yaxis", ctx_r1.threadsChartOptions.yaxis);
    }
}

var ThreadsChartComponent = class _ThreadsChartComponent {
    constructor(monitoringService, chartService) {
        this.monitoringService = monitoringService;
        this.chartService = chartService;
        this.ranges = [];
        this.selectedTimeRange = "";
    }

    ngOnInit() {
        this.ranges = this.chartService.getRanges();
        this.selectedTimeRange = this.chartService.getDefaultRange();
        this.loadThreadChart();
    }

    loadThreadChart() {
        let start = this.chartService.getStartTime(this.selectedTimeRange);
        let end = this.chartService.getEndTime();
        this.monitoringService.getCounters("total_threads", start, end, 5).subscribe((data) => {
            if (data) {
                this.threadsChartOptions = {
                    series: [{name: "Threads", data: data.counters}],
                    chart: {height: 350, type: "line", animations: this.chartService.getAnimation()},
                    dataLabels: {enabled: false},
                    stroke: {show: true, curve: "smooth", width: 2},
                    tooltip: {shared: true, x: {format: "dd/MM HH:mm:ss"}},
                    title: {text: "Threads", align: "center"},
                    grid: {row: {colors: ["#f3f3f3", "transparent"], opacity: 0.5}, column: {colors: ["#f3f3f3", "transparent"], opacity: 0.5}},
                    xaxis: {type: "datetime", title: {text: "Time"}, labels: {datetimeUTC: false}, min: start.getTime(), max: end.getTime()},
                    yaxis: {min: 0, decimalsInFloat: 0, title: {text: "CPU [%]"}, labels: {offsetX: 10}}
                };
            }
        });
    }

    static {
        this.\u0275fac = function ThreadsChartComponent_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _ThreadsChartComponent)(\u0275\u0275directiveInject(MonitoringService), \u0275\u0275directiveInject(ChartService));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _ThreadsChartComponent,
            selectors: [["threads-chart-component"]],
            viewQuery: function ThreadsChartComponent_Query(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275viewQuery(_c03, 5);
                }
                if (rf & 2) {
                    let _t;
                    \u0275\u0275queryRefresh(_t = \u0275\u0275loadQuery()) && (ctx.threadsChart = _t.first);
                }
            },
            standalone: true,
            features: [\u0275\u0275StandaloneFeature],
            decls: 13,
            vars: 2,
            consts: [[1, "mat-elevation-z4"], [1, "container"], [1, "flex-container-left"], [1, "flex-item"], [1, "flex-container-right"], [2, "width", "200px", 3, "selectionChange", "ngModelChange", "ngModel"], [3, "value"], [3, "chart", "dataLabels", "grid", "series", "stroke", "title", "tooltip", "xaxis", "yaxis", 4, "ngIf"], [3, "chart", "dataLabels", "grid", "series", "stroke", "title", "tooltip", "xaxis", "yaxis"]],
            template: function ThreadsChartComponent_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "mat-card", 0)(1, "mat-card-header")(2, "div", 1)(3, "div", 2);
                    \u0275\u0275element(4, "div", 3);
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(5, "div", 4)(6, "div", 3)(7, "mat-card-actions")(8, "mat-select", 5);
                    \u0275\u0275listener("selectionChange", function ThreadsChartComponent_Template_mat_select_selectionChange_8_listener() {
                        return ctx.loadThreadChart();
                    });
                    \u0275\u0275twoWayListener("ngModelChange", function ThreadsChartComponent_Template_mat_select_ngModelChange_8_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.selectedTimeRange, $event) || (ctx.selectedTimeRange = $event);
                        return $event;
                    });
                    \u0275\u0275repeaterCreate(9, ThreadsChartComponent_For_10_Template, 2, 2, "mat-option", 6, \u0275\u0275repeaterTrackByIdentity);
                    \u0275\u0275elementEnd()()()()()();
                    \u0275\u0275elementStart(11, "mat-card-content");
                    \u0275\u0275template(12, ThreadsChartComponent_apx_chart_12_Template, 1, 9, "apx-chart", 7);
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    \u0275\u0275advance(8);
                    \u0275\u0275twoWayProperty("ngModel", ctx.selectedTimeRange);
                    \u0275\u0275advance();
                    \u0275\u0275repeater(ctx.ranges);
                    \u0275\u0275advance(3);
                    \u0275\u0275property("ngIf", ctx.threadsChartOptions);
                }
            },
            dependencies: [
                MatCardHeader,
                MatCard,
                MatCardActions,
                MatSelect,
                FormsModule,
                NgControlStatus,
                NgModel,
                MatOption,
                MatCardContent,
                ChartComponent,
                NgIf
            ],
            styles: ["\n\nbody[_ngcontent-%COMP%] {\n  margin: 40px;\n}\n.wrapper[_ngcontent-%COMP%] {\n  display: grid;\n  grid-template-columns: 1fr 1fr 1fr;\n  grid-gap: 10px;\n  background-color: #fff;\n  color: #444;\n  padding: 10px;\n}\n.box[_ngcontent-%COMP%] {\n  background-color: #444;\n  color: #fff;\n  border-radius: 5px;\n  padding: 20px;\n  height: 400px;\n}\n.container[_ngcontent-%COMP%] {\n  margin: 0 auto;\n  width: 100%;\n  display: flex;\n  align-items: center;\n  justify-content: space-between;\n}\n.flex-container-left[_ngcontent-%COMP%] {\n  display: flex;\n  align-items: flex-start;\n  justify-content: flex-start;\n  height: 100%;\n}\n.flex-container-right[_ngcontent-%COMP%] {\n  display: flex;\n  align-items: flex-start;\n  justify-content: flex-end;\n  height: 100%;\n}\n.flex-item[_ngcontent-%COMP%] {\n  margin: 5px;\n  height: 100%;\n}\n.card-header[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: start;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  justify-content: flex-start;\n}\n.action-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  justify-content: flex-end;\n}\n.full-screen-modal[_ngcontent-%COMP%]   .mat-dialog-container[_ngcontent-%COMP%] {\n  max-width: none;\n}\n.body[_ngcontent-%COMP%] {\n  flex-grow: 1;\n  overflow: hidden;\n}\n.footer[_ngcontent-%COMP%] {\n  display: flex;\n  width: 50%;\n  font-size: x-small;\n  color: black;\n}\n/*# sourceMappingURL=threads-chart.component.css.map */"]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(ThreadsChartComponent, {
        className: "ThreadsChartComponent",
        filePath: "src/app/modules/dashboard/charts/thread-chart/threads-chart.component.ts",
        lineNumber: 50
    });
})();

// src/app/modules/dashboard/charts/gateway-time/gateway-time.component.ts
var _c04 = ["httpTimerChart"];

function GatewayTimeComponent_For_10_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "mat-option", 6);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const range_r1 = ctx.$implicit;
        \u0275\u0275property("value", range_r1.value);
        \u0275\u0275advance();
        \u0275\u0275textInterpolate(range_r1.viewValue);
    }
}

function GatewayTimeComponent_apx_chart_13_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "apx-chart", 8);
    }
    if (rf & 2) {
        const ctx_r1 = \u0275\u0275nextContext();
        \u0275\u0275property("chart", ctx_r1.httpTimeChartOptions.chart)("dataLabels", ctx_r1.httpTimeChartOptions.dataLabels)("grid", ctx_r1.httpTimeChartOptions.grid)("series", ctx_r1.httpTimeChartOptions.series)("stroke", ctx_r1.httpTimeChartOptions.stroke)("title", ctx_r1.httpTimeChartOptions.title)("tooltip", ctx_r1.httpTimeChartOptions.tooltip)("xaxis", ctx_r1.httpTimeChartOptions.xaxis)("yaxis", ctx_r1.httpTimeChartOptions.yaxis);
    }
}

var GatewayTimeComponent = class _GatewayTimeComponent {
    constructor(monitoringService, chartService) {
        this.monitoringService = monitoringService;
        this.chartService = chartService;
        this.ranges = [];
        this.selectedTimeRange = "";
    }

    ngOnInit() {
        this.ranges = this.chartService.getRanges();
        this.selectedTimeRange = this.chartService.getDefaultRange();
        this.loadHttpTimeChart();
    }

    loadHttpTimeChart() {
        let start = this.chartService.getStartTime(this.selectedTimeRange);
        let end = this.chartService.getEndTime();
        this.monitoringService.getCounters("gateway_http_timer", start, end, 5).subscribe((data) => {
            if (data) {
                this.httpTimeChartOptions = {
                    series: [{name: "HTTP Response Time", data: data.counters}],
                    chart: {height: 350, type: "line", animations: this.chartService.getAnimation()},
                    dataLabels: {enabled: false},
                    stroke: {show: true, curve: "smooth", width: 2},
                    title: {text: "HTTP Response Time", align: "center"},
                    tooltip: {x: {format: "dd/MM HH:mm:ss"}},
                    grid: {row: {colors: ["#f3f3f3", "transparent"], opacity: 0.5}, column: {colors: ["#f3f3f3", "transparent"], opacity: 0.5}},
                    xaxis: {type: "datetime", title: {text: "Time"}, labels: {datetimeUTC: false}, min: start.getTime(), max: end.getTime()},
                    yaxis: {
                        min: 0,
                        forceNiceScale: true,
                        decimalsInFloat: 0,
                        title: {text: "HTTP Response Time [ms]"},
                        labels: {
                            formatter: function (val) {
                                return val.toFixed(0);
                            },
                            offsetX: 10
                        }
                    }
                };
            }
        });
    }

    static {
        this.\u0275fac = function GatewayTimeComponent_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _GatewayTimeComponent)(\u0275\u0275directiveInject(MonitoringService), \u0275\u0275directiveInject(ChartService));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _GatewayTimeComponent,
            selectors: [["gateway-time-chart-component"]],
            viewQuery: function GatewayTimeComponent_Query(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275viewQuery(_c04, 5);
                }
                if (rf & 2) {
                    let _t;
                    \u0275\u0275queryRefresh(_t = \u0275\u0275loadQuery()) && (ctx.httpTimerChart = _t.first);
                }
            },
            standalone: true,
            features: [\u0275\u0275StandaloneFeature],
            decls: 14,
            vars: 2,
            consts: [[1, "mat-elevation-z3"], [1, "container"], [1, "flex-container-left"], [1, "flex-item"], [1, "flex-container-right"], [2, "width", "200px", 3, "selectionChange", "ngModelChange", "ngModel"], [3, "value"], [3, "chart", "dataLabels", "grid", "series", "stroke", "title", "tooltip", "xaxis", "yaxis", 4, "ngIf"], [3, "chart", "dataLabels", "grid", "series", "stroke", "title", "tooltip", "xaxis", "yaxis"]],
            template: function GatewayTimeComponent_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "mat-card", 0)(1, "mat-card-header")(2, "div", 1)(3, "div", 2);
                    \u0275\u0275element(4, "div", 3);
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(5, "div", 4)(6, "div", 3)(7, "mat-card-actions")(8, "mat-select", 5);
                    \u0275\u0275listener("selectionChange", function GatewayTimeComponent_Template_mat_select_selectionChange_8_listener() {
                        return ctx.loadHttpTimeChart();
                    });
                    \u0275\u0275twoWayListener("ngModelChange", function GatewayTimeComponent_Template_mat_select_ngModelChange_8_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.selectedTimeRange, $event) || (ctx.selectedTimeRange = $event);
                        return $event;
                    });
                    \u0275\u0275repeaterCreate(9, GatewayTimeComponent_For_10_Template, 2, 2, "mat-option", 6, \u0275\u0275repeaterTrackByIdentity);
                    \u0275\u0275elementEnd()()()()()();
                    \u0275\u0275elementStart(11, "mat-card-content")(12, "div");
                    \u0275\u0275template(13, GatewayTimeComponent_apx_chart_13_Template, 1, 9, "apx-chart", 7);
                    \u0275\u0275elementEnd()()();
                }
                if (rf & 2) {
                    \u0275\u0275advance(8);
                    \u0275\u0275twoWayProperty("ngModel", ctx.selectedTimeRange);
                    \u0275\u0275advance();
                    \u0275\u0275repeater(ctx.ranges);
                    \u0275\u0275advance(4);
                    \u0275\u0275property("ngIf", ctx.httpTimeChartOptions);
                }
            },
            dependencies: [
                MatCardHeader,
                MatCard,
                MatCardActions,
                MatSelect,
                FormsModule,
                NgControlStatus,
                NgModel,
                MatOption,
                MatCardContent,
                ChartComponent,
                NgIf
            ],
            styles: ["\n\nbody[_ngcontent-%COMP%] {\n  margin: 40px;\n}\n.wrapper[_ngcontent-%COMP%] {\n  display: grid;\n  grid-template-columns: 1fr 1fr 1fr;\n  grid-gap: 10px;\n  background-color: #fff;\n  color: #444;\n  padding: 10px;\n}\n.box[_ngcontent-%COMP%] {\n  background-color: #444;\n  color: #fff;\n  border-radius: 5px;\n  padding: 20px;\n  height: 400px;\n}\n.container[_ngcontent-%COMP%] {\n  margin: 0 auto;\n  width: 100%;\n  display: flex;\n  align-items: center;\n  justify-content: space-between;\n}\n.flex-container-left[_ngcontent-%COMP%] {\n  display: flex;\n  align-items: flex-start;\n  justify-content: flex-start;\n  height: 100%;\n}\n.flex-container-right[_ngcontent-%COMP%] {\n  display: flex;\n  align-items: flex-start;\n  justify-content: flex-end;\n  height: 100%;\n}\n.flex-item[_ngcontent-%COMP%] {\n  margin: 5px;\n  height: 100%;\n}\n.card-header[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: start;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  justify-content: flex-start;\n}\n.action-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  justify-content: flex-end;\n}\n.full-screen-modal[_ngcontent-%COMP%]   .mat-dialog-container[_ngcontent-%COMP%] {\n  max-width: none;\n}\n.body[_ngcontent-%COMP%] {\n  flex-grow: 1;\n  overflow: hidden;\n}\n.footer[_ngcontent-%COMP%] {\n  display: flex;\n  width: 50%;\n  font-size: x-small;\n  color: black;\n}\n/*# sourceMappingURL=gateway-time.component.css.map */"]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(GatewayTimeComponent, {
        className: "GatewayTimeComponent",
        filePath: "src/app/modules/dashboard/charts/gateway-time/gateway-time.component.ts",
        lineNumber: 50
    });
})();

// src/app/modules/dashboard/charts/memory-chart/memory-chart.component.ts
var _c05 = ["memoryChart"];

function MemoryChartComponent_For_10_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "mat-option", 6);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const range_r1 = ctx.$implicit;
        \u0275\u0275property("value", range_r1.value);
        \u0275\u0275advance();
        \u0275\u0275textInterpolate(range_r1.viewValue);
    }
}

function MemoryChartComponent_apx_chart_13_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "apx-chart", 8);
    }
    if (rf & 2) {
        const ctx_r1 = \u0275\u0275nextContext();
        \u0275\u0275property("chart", ctx_r1.memChartOptions.chart)("dataLabels", ctx_r1.memChartOptions.dataLabels)("grid", ctx_r1.memChartOptions.grid)("series", ctx_r1.memChartOptions.series)("stroke", ctx_r1.memChartOptions.stroke)("title", ctx_r1.memChartOptions.title)("tooltip", ctx_r1.memChartOptions.tooltip)("xaxis", ctx_r1.memChartOptions.xaxis)("yaxis", ctx_r1.memChartOptions.yaxis);
    }
}

var MemoryChartComponent = class _MemoryChartComponent {
    constructor(monitoringService, chartService) {
        this.monitoringService = monitoringService;
        this.chartService = chartService;
        this.ranges = [];
        this.selectedTimeRange = "";
    }

    ngOnInit() {
        this.ranges = this.chartService.getRanges();
        this.selectedTimeRange = this.chartService.getDefaultRange();
        this.loadMemoryChart();
    }

    loadMemoryChart() {
        let start = this.chartService.getStartTime(this.selectedTimeRange);
        let end = this.chartService.getEndTime();
        this.monitoringService.getCounters("real_memory_used", start, end, 5).subscribe((data) => {
            if (data) {
                this.memChartOptions = {
                    series: [{name: "memoryChart", data: data.counters}],
                    chart: {height: 350, type: "line", animations: this.chartService.getAnimation()},
                    dataLabels: {enabled: false},
                    stroke: {show: true, curve: "smooth", width: 2},
                    title: {text: "Memory", align: "center"},
                    tooltip: {x: {format: "dd/MM HH:mm:ss"}},
                    grid: {row: {colors: ["#f3f3f3", "transparent"], opacity: 0.5}, column: {colors: ["#f3f3f3", "transparent"], opacity: 0.5}},
                    xaxis: {type: "datetime", title: {text: "Time"}, labels: {datetimeUTC: false}, min: start.getTime(), max: end.getTime()},
                    yaxis: {
                        min: 0,
                        forceNiceScale: true,
                        decimalsInFloat: 0,
                        title: {text: "Memory [MB]"},
                        labels: {
                            formatter: function (val) {
                                val /= 1024;
                                return val.toFixed(0);
                            },
                            offsetX: 10
                        }
                    }
                };
            }
        });
    }

    static {
        this.\u0275fac = function MemoryChartComponent_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _MemoryChartComponent)(\u0275\u0275directiveInject(MonitoringService), \u0275\u0275directiveInject(ChartService));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _MemoryChartComponent,
            selectors: [["memory-chart-component"]],
            viewQuery: function MemoryChartComponent_Query(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275viewQuery(_c05, 5);
                }
                if (rf & 2) {
                    let _t;
                    \u0275\u0275queryRefresh(_t = \u0275\u0275loadQuery()) && (ctx.memoryChart = _t.first);
                }
            },
            standalone: true,
            features: [\u0275\u0275StandaloneFeature],
            decls: 14,
            vars: 2,
            consts: [[1, "mat-elevation-z3"], [1, "container"], [1, "flex-container-left"], [1, "flex-item"], [1, "flex-container-right"], [2, "width", "200px", 3, "selectionChange", "ngModelChange", "ngModel"], [3, "value"], [3, "chart", "dataLabels", "grid", "series", "stroke", "title", "tooltip", "xaxis", "yaxis", 4, "ngIf"], [3, "chart", "dataLabels", "grid", "series", "stroke", "title", "tooltip", "xaxis", "yaxis"]],
            template: function MemoryChartComponent_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "mat-card", 0)(1, "mat-card-header")(2, "div", 1)(3, "div", 2);
                    \u0275\u0275element(4, "div", 3);
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(5, "div", 4)(6, "div", 3)(7, "mat-card-actions")(8, "mat-select", 5);
                    \u0275\u0275listener("selectionChange", function MemoryChartComponent_Template_mat_select_selectionChange_8_listener() {
                        return ctx.loadMemoryChart();
                    });
                    \u0275\u0275twoWayListener("ngModelChange", function MemoryChartComponent_Template_mat_select_ngModelChange_8_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.selectedTimeRange, $event) || (ctx.selectedTimeRange = $event);
                        return $event;
                    });
                    \u0275\u0275repeaterCreate(9, MemoryChartComponent_For_10_Template, 2, 2, "mat-option", 6, \u0275\u0275repeaterTrackByIdentity);
                    \u0275\u0275elementEnd()()()()()();
                    \u0275\u0275elementStart(11, "mat-card-content")(12, "div");
                    \u0275\u0275template(13, MemoryChartComponent_apx_chart_13_Template, 1, 9, "apx-chart", 7);
                    \u0275\u0275elementEnd()()();
                }
                if (rf & 2) {
                    \u0275\u0275advance(8);
                    \u0275\u0275twoWayProperty("ngModel", ctx.selectedTimeRange);
                    \u0275\u0275advance();
                    \u0275\u0275repeater(ctx.ranges);
                    \u0275\u0275advance(4);
                    \u0275\u0275property("ngIf", ctx.memChartOptions);
                }
            },
            dependencies: [
                MatCardActions,
                MatSelect,
                MatCardHeader,
                MatCard,
                MatCardContent,
                ChartComponent,
                NgIf,
                FormsModule,
                NgControlStatus,
                NgModel,
                MatOption
            ],
            styles: ["\n\nbody[_ngcontent-%COMP%] {\n  margin: 40px;\n}\n.wrapper[_ngcontent-%COMP%] {\n  display: grid;\n  grid-template-columns: 1fr 1fr 1fr;\n  grid-gap: 10px;\n  background-color: #fff;\n  color: #444;\n  padding: 10px;\n}\n.box[_ngcontent-%COMP%] {\n  background-color: #444;\n  color: #fff;\n  border-radius: 5px;\n  padding: 20px;\n  height: 400px;\n}\n.container[_ngcontent-%COMP%] {\n  margin: 0 auto;\n  width: 100%;\n  display: flex;\n  align-items: center;\n  justify-content: space-between;\n}\n.flex-container-left[_ngcontent-%COMP%] {\n  display: flex;\n  align-items: flex-start;\n  justify-content: flex-start;\n  height: 100%;\n}\n.flex-container-right[_ngcontent-%COMP%] {\n  display: flex;\n  align-items: flex-start;\n  justify-content: flex-end;\n  height: 100%;\n}\n.flex-item[_ngcontent-%COMP%] {\n  margin: 5px;\n  height: 100%;\n}\n.card-header[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: start;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  justify-content: flex-start;\n}\n.action-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  justify-content: flex-end;\n}\n.full-screen-modal[_ngcontent-%COMP%]   .mat-dialog-container[_ngcontent-%COMP%] {\n  max-width: none;\n}\n.body[_ngcontent-%COMP%] {\n  flex-grow: 1;\n  overflow: hidden;\n}\n.footer[_ngcontent-%COMP%] {\n  display: flex;\n  width: 50%;\n  font-size: x-small;\n  color: black;\n}\n/*# sourceMappingURL=memory-chart.component.css.map */"]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(MemoryChartComponent, {
        className: "MemoryChartComponent",
        filePath: "src/app/modules/dashboard/charts/memory-chart/memory-chart.component.ts",
        lineNumber: 50
    });
})();

// node_modules/@angular/material/fesm2022/toolbar.mjs
var _c06 = ["*", [["mat-toolbar-row"]]];
var _c1 = ["*", "mat-toolbar-row"];
var MatToolbarRow = class _MatToolbarRow {
    static {
        this.\u0275fac = function MatToolbarRow_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _MatToolbarRow)();
        };
    }
    static {
        this.\u0275dir = /* @__PURE__ */ \u0275\u0275defineDirective({
            type: _MatToolbarRow,
            selectors: [["mat-toolbar-row"]],
            hostAttrs: [1, "mat-toolbar-row"],
            exportAs: ["matToolbarRow"],
            standalone: true
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && setClassMetadata(MatToolbarRow, [{
        type: Directive,
        args: [{
            selector: "mat-toolbar-row",
            exportAs: "matToolbarRow",
            host: {
                "class": "mat-toolbar-row"
            },
            standalone: true
        }]
    }], null, null);
})();
var MatToolbar = class _MatToolbar {
    constructor(_elementRef, _platform, document) {
        this._elementRef = _elementRef;
        this._platform = _platform;
        this._document = document;
    }

    ngAfterViewInit() {
        if (this._platform.isBrowser) {
            this._checkToolbarMixedModes();
            this._toolbarRows.changes.subscribe(() => this._checkToolbarMixedModes());
        }
    }

    /**
     * Throws an exception when developers are attempting to combine the different toolbar row modes.
     */
    _checkToolbarMixedModes() {
        if (this._toolbarRows.length && (typeof ngDevMode === "undefined" || ngDevMode)) {
            const isCombinedUsage = Array.from(this._elementRef.nativeElement.childNodes).filter((node) => !(node.classList && node.classList.contains("mat-toolbar-row"))).filter((node) => node.nodeType !== (this._document ? this._document.COMMENT_NODE : 8)).some((node) => !!(node.textContent && node.textContent.trim()));
            if (isCombinedUsage) {
                throwToolbarMixedModesError();
            }
        }
    }

    static {
        this.\u0275fac = function MatToolbar_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _MatToolbar)(\u0275\u0275directiveInject(ElementRef), \u0275\u0275directiveInject(Platform), \u0275\u0275directiveInject(DOCUMENT));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _MatToolbar,
            selectors: [["mat-toolbar"]],
            contentQueries: function MatToolbar_ContentQueries(rf, ctx, dirIndex) {
                if (rf & 1) {
                    \u0275\u0275contentQuery(dirIndex, MatToolbarRow, 5);
                }
                if (rf & 2) {
                    let _t;
                    \u0275\u0275queryRefresh(_t = \u0275\u0275loadQuery()) && (ctx._toolbarRows = _t);
                }
            },
            hostAttrs: [1, "mat-toolbar"],
            hostVars: 6,
            hostBindings: function MatToolbar_HostBindings(rf, ctx) {
                if (rf & 2) {
                    \u0275\u0275classMap(ctx.color ? "mat-" + ctx.color : "");
                    \u0275\u0275classProp("mat-toolbar-multiple-rows", ctx._toolbarRows.length > 0)("mat-toolbar-single-row", ctx._toolbarRows.length === 0);
                }
            },
            inputs: {
                color: "color"
            },
            exportAs: ["matToolbar"],
            standalone: true,
            features: [\u0275\u0275StandaloneFeature],
            ngContentSelectors: _c1,
            decls: 2,
            vars: 0,
            template: function MatToolbar_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275projectionDef(_c06);
                    \u0275\u0275projection(0);
                    \u0275\u0275projection(1, 1);
                }
            },
            styles: [".mat-toolbar{background:var(--mat-toolbar-container-background-color, var(--mat-app-surface));color:var(--mat-toolbar-container-text-color, var(--mat-app-on-surface))}.mat-toolbar,.mat-toolbar h1,.mat-toolbar h2,.mat-toolbar h3,.mat-toolbar h4,.mat-toolbar h5,.mat-toolbar h6{font-family:var(--mat-toolbar-title-text-font, var(--mat-app-title-large-font));font-size:var(--mat-toolbar-title-text-size, var(--mat-app-title-large-size));line-height:var(--mat-toolbar-title-text-line-height, var(--mat-app-title-large-line-height));font-weight:var(--mat-toolbar-title-text-weight, var(--mat-app-title-large-weight));letter-spacing:var(--mat-toolbar-title-text-tracking, var(--mat-app-title-large-tracking));margin:0}.cdk-high-contrast-active .mat-toolbar{outline:solid 1px}.mat-toolbar .mat-form-field-underline,.mat-toolbar .mat-form-field-ripple,.mat-toolbar .mat-focused .mat-form-field-ripple{background-color:currentColor}.mat-toolbar .mat-form-field-label,.mat-toolbar .mat-focused .mat-form-field-label,.mat-toolbar .mat-select-value,.mat-toolbar .mat-select-arrow,.mat-toolbar .mat-form-field.mat-focused .mat-select-arrow{color:inherit}.mat-toolbar .mat-input-element{caret-color:currentColor}.mat-toolbar .mat-mdc-button-base.mat-mdc-button-base.mat-unthemed{--mdc-text-button-label-text-color:var(--mat-toolbar-container-text-color, var(--mat-app-on-surface));--mdc-outlined-button-label-text-color:var(--mat-toolbar-container-text-color, var(--mat-app-on-surface))}.mat-toolbar-row,.mat-toolbar-single-row{display:flex;box-sizing:border-box;padding:0 16px;width:100%;flex-direction:row;align-items:center;white-space:nowrap;height:var(--mat-toolbar-standard-height)}@media(max-width: 599px){.mat-toolbar-row,.mat-toolbar-single-row{height:var(--mat-toolbar-mobile-height)}}.mat-toolbar-multiple-rows{display:flex;box-sizing:border-box;flex-direction:column;width:100%;min-height:var(--mat-toolbar-standard-height)}@media(max-width: 599px){.mat-toolbar-multiple-rows{min-height:var(--mat-toolbar-mobile-height)}}"],
            encapsulation: 2,
            changeDetection: 0
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && setClassMetadata(MatToolbar, [{
        type: Component,
        args: [{
            selector: "mat-toolbar",
            exportAs: "matToolbar",
            host: {
                "class": "mat-toolbar",
                "[class]": 'color ? "mat-" + color : ""',
                "[class.mat-toolbar-multiple-rows]": "_toolbarRows.length > 0",
                "[class.mat-toolbar-single-row]": "_toolbarRows.length === 0"
            },
            changeDetection: ChangeDetectionStrategy.OnPush,
            encapsulation: ViewEncapsulation$1.None,
            standalone: true,
            template: '<ng-content></ng-content>\n<ng-content select="mat-toolbar-row"></ng-content>\n',
            styles: [".mat-toolbar{background:var(--mat-toolbar-container-background-color, var(--mat-app-surface));color:var(--mat-toolbar-container-text-color, var(--mat-app-on-surface))}.mat-toolbar,.mat-toolbar h1,.mat-toolbar h2,.mat-toolbar h3,.mat-toolbar h4,.mat-toolbar h5,.mat-toolbar h6{font-family:var(--mat-toolbar-title-text-font, var(--mat-app-title-large-font));font-size:var(--mat-toolbar-title-text-size, var(--mat-app-title-large-size));line-height:var(--mat-toolbar-title-text-line-height, var(--mat-app-title-large-line-height));font-weight:var(--mat-toolbar-title-text-weight, var(--mat-app-title-large-weight));letter-spacing:var(--mat-toolbar-title-text-tracking, var(--mat-app-title-large-tracking));margin:0}.cdk-high-contrast-active .mat-toolbar{outline:solid 1px}.mat-toolbar .mat-form-field-underline,.mat-toolbar .mat-form-field-ripple,.mat-toolbar .mat-focused .mat-form-field-ripple{background-color:currentColor}.mat-toolbar .mat-form-field-label,.mat-toolbar .mat-focused .mat-form-field-label,.mat-toolbar .mat-select-value,.mat-toolbar .mat-select-arrow,.mat-toolbar .mat-form-field.mat-focused .mat-select-arrow{color:inherit}.mat-toolbar .mat-input-element{caret-color:currentColor}.mat-toolbar .mat-mdc-button-base.mat-mdc-button-base.mat-unthemed{--mdc-text-button-label-text-color:var(--mat-toolbar-container-text-color, var(--mat-app-on-surface));--mdc-outlined-button-label-text-color:var(--mat-toolbar-container-text-color, var(--mat-app-on-surface))}.mat-toolbar-row,.mat-toolbar-single-row{display:flex;box-sizing:border-box;padding:0 16px;width:100%;flex-direction:row;align-items:center;white-space:nowrap;height:var(--mat-toolbar-standard-height)}@media(max-width: 599px){.mat-toolbar-row,.mat-toolbar-single-row{height:var(--mat-toolbar-mobile-height)}}.mat-toolbar-multiple-rows{display:flex;box-sizing:border-box;flex-direction:column;width:100%;min-height:var(--mat-toolbar-standard-height)}@media(max-width: 599px){.mat-toolbar-multiple-rows{min-height:var(--mat-toolbar-mobile-height)}}"]
        }]
    }], () => [{
        type: ElementRef
    }, {
        type: Platform
    }, {
        type: void 0,
        decorators: [{
            type: Inject,
            args: [DOCUMENT]
        }]
    }], {
        color: [{
            type: Input
        }],
        _toolbarRows: [{
            type: ContentChildren,
            args: [MatToolbarRow, {
                descendants: true
            }]
        }]
    });
})();

function throwToolbarMixedModesError() {
    throw Error("MatToolbar: Attempting to combine different toolbar modes. Either specify multiple `<mat-toolbar-row>` elements explicitly or just place content inside of a `<mat-toolbar>` for a single row.");
}

var MatToolbarModule = class _MatToolbarModule {
    static {
        this.\u0275fac = function MatToolbarModule_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _MatToolbarModule)();
        };
    }
    static {
        this.\u0275mod = /* @__PURE__ */ \u0275\u0275defineNgModule({
            type: _MatToolbarModule
        });
    }
    static {
        this.\u0275inj = /* @__PURE__ */ \u0275\u0275defineInjector({
            imports: [MatCommonModule, MatCommonModule]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && setClassMetadata(MatToolbarModule, [{
        type: NgModule,
        args: [{
            imports: [MatCommonModule, MatToolbar, MatToolbarRow],
            exports: [MatToolbar, MatToolbarRow, MatCommonModule]
        }]
    }], null, null);
})();

// node_modules/@angular/material/fesm2022/checkbox.mjs
var _c07 = ["input"];
var _c12 = ["label"];
var _c2 = ["*"];
var MAT_CHECKBOX_DEFAULT_OPTIONS = new InjectionToken("mat-checkbox-default-options", {
    providedIn: "root",
    factory: MAT_CHECKBOX_DEFAULT_OPTIONS_FACTORY
});

function MAT_CHECKBOX_DEFAULT_OPTIONS_FACTORY() {
    return {
        color: "accent",
        clickAction: "check-indeterminate",
        disabledInteractive: false
    };
}

var TransitionCheckState;
(function (TransitionCheckState2) {
    TransitionCheckState2[TransitionCheckState2["Init"] = 0] = "Init";
    TransitionCheckState2[TransitionCheckState2["Checked"] = 1] = "Checked";
    TransitionCheckState2[TransitionCheckState2["Unchecked"] = 2] = "Unchecked";
    TransitionCheckState2[TransitionCheckState2["Indeterminate"] = 3] = "Indeterminate";
})(TransitionCheckState || (TransitionCheckState = {}));
var MAT_CHECKBOX_CONTROL_VALUE_ACCESSOR = {
    provide: NG_VALUE_ACCESSOR,
    useExisting: forwardRef(() => MatCheckbox),
    multi: true
};
var MatCheckboxChange = class {
};
var nextUniqueId = 0;
var defaults = MAT_CHECKBOX_DEFAULT_OPTIONS_FACTORY();
var MatCheckbox = class _MatCheckbox {
    constructor(_elementRef, _changeDetectorRef, _ngZone, tabIndex, _animationMode, _options) {
        this._elementRef = _elementRef;
        this._changeDetectorRef = _changeDetectorRef;
        this._ngZone = _ngZone;
        this._animationMode = _animationMode;
        this._options = _options;
        this._animationClasses = {
            uncheckedToChecked: "mdc-checkbox--anim-unchecked-checked",
            uncheckedToIndeterminate: "mdc-checkbox--anim-unchecked-indeterminate",
            checkedToUnchecked: "mdc-checkbox--anim-checked-unchecked",
            checkedToIndeterminate: "mdc-checkbox--anim-checked-indeterminate",
            indeterminateToChecked: "mdc-checkbox--anim-indeterminate-checked",
            indeterminateToUnchecked: "mdc-checkbox--anim-indeterminate-unchecked"
        };
        this.ariaLabel = "";
        this.ariaLabelledby = null;
        this.labelPosition = "after";
        this.name = null;
        this.change = new EventEmitter();
        this.indeterminateChange = new EventEmitter();
        this._onTouched = () => {
        };
        this._currentAnimationClass = "";
        this._currentCheckState = TransitionCheckState.Init;
        this._controlValueAccessorChangeFn = () => {
        };
        this._validatorChangeFn = () => {
        };
        this._checked = false;
        this._disabled = false;
        this._indeterminate = false;
        this._options = this._options || defaults;
        this.color = this._options.color || defaults.color;
        this.tabIndex = parseInt(tabIndex) || 0;
        this.id = this._uniqueId = `mat-mdc-checkbox-${++nextUniqueId}`;
        this.disabledInteractive = _options?.disabledInteractive ?? false;
    }

    /** Returns the unique id for the visual hidden input. */
    get inputId() {
        return `${this.id || this._uniqueId}-input`;
    }

    /** Whether the checkbox is checked. */
    get checked() {
        return this._checked;
    }

    set checked(value) {
        if (value != this.checked) {
            this._checked = value;
            this._changeDetectorRef.markForCheck();
        }
    }

    /** Whether the checkbox is disabled. */
    get disabled() {
        return this._disabled;
    }

    set disabled(value) {
        if (value !== this.disabled) {
            this._disabled = value;
            this._changeDetectorRef.markForCheck();
        }
    }

    /**
     * Whether the checkbox is indeterminate. This is also known as "mixed" mode and can be used to
     * represent a checkbox with three states, e.g. a checkbox that represents a nested list of
     * checkable items. Note that whenever checkbox is manually clicked, indeterminate is immediately
     * set to false.
     */
    get indeterminate() {
        return this._indeterminate;
    }

    set indeterminate(value) {
        const changed = value != this._indeterminate;
        this._indeterminate = value;
        if (changed) {
            if (this._indeterminate) {
                this._transitionCheckState(TransitionCheckState.Indeterminate);
            } else {
                this._transitionCheckState(this.checked ? TransitionCheckState.Checked : TransitionCheckState.Unchecked);
            }
            this.indeterminateChange.emit(this._indeterminate);
        }
        this._syncIndeterminate(this._indeterminate);
    }

    /** Focuses the checkbox. */
    focus() {
        this._inputElement.nativeElement.focus();
    }

    /** Creates the change event that will be emitted by the checkbox. */
    _createChangeEvent(isChecked) {
        const event = new MatCheckboxChange();
        event.source = this;
        event.checked = isChecked;
        return event;
    }

    /** Gets the element on which to add the animation CSS classes. */
    _getAnimationTargetElement() {
        return this._inputElement?.nativeElement;
    }

    ngOnChanges(changes) {
        if (changes["required"]) {
            this._validatorChangeFn();
        }
    }

    ngAfterViewInit() {
        this._syncIndeterminate(this._indeterminate);
    }

    _isRippleDisabled() {
        return this.disableRipple || this.disabled;
    }

    /** Method being called whenever the label text changes. */
    _onLabelTextChange() {
        this._changeDetectorRef.detectChanges();
    }

    // Implemented as part of ControlValueAccessor.
    writeValue(value) {
        this.checked = !!value;
    }

    // Implemented as part of ControlValueAccessor.
    registerOnChange(fn) {
        this._controlValueAccessorChangeFn = fn;
    }

    // Implemented as part of ControlValueAccessor.
    registerOnTouched(fn) {
        this._onTouched = fn;
    }

    // Implemented as part of ControlValueAccessor.
    setDisabledState(isDisabled) {
        this.disabled = isDisabled;
    }

    // Implemented as a part of Validator.
    validate(control) {
        return this.required && control.value !== true ? {
            "required": true
        } : null;
    }

    // Implemented as a part of Validator.
    registerOnValidatorChange(fn) {
        this._validatorChangeFn = fn;
    }

    _transitionCheckState(newState) {
        let oldState = this._currentCheckState;
        let element = this._getAnimationTargetElement();
        if (oldState === newState || !element) {
            return;
        }
        if (this._currentAnimationClass) {
            element.classList.remove(this._currentAnimationClass);
        }
        this._currentAnimationClass = this._getAnimationClassForCheckStateTransition(oldState, newState);
        this._currentCheckState = newState;
        if (this._currentAnimationClass.length > 0) {
            element.classList.add(this._currentAnimationClass);
            const animationClass = this._currentAnimationClass;
            this._ngZone.runOutsideAngular(() => {
                setTimeout(() => {
                    element.classList.remove(animationClass);
                }, 1e3);
            });
        }
    }

    _emitChangeEvent() {
        this._controlValueAccessorChangeFn(this.checked);
        this.change.emit(this._createChangeEvent(this.checked));
        if (this._inputElement) {
            this._inputElement.nativeElement.checked = this.checked;
        }
    }

    /** Toggles the `checked` state of the checkbox. */
    toggle() {
        this.checked = !this.checked;
        this._controlValueAccessorChangeFn(this.checked);
    }

    _handleInputClick() {
        const clickAction = this._options?.clickAction;
        if (!this.disabled && clickAction !== "noop") {
            if (this.indeterminate && clickAction !== "check") {
                Promise.resolve().then(() => {
                    this._indeterminate = false;
                    this.indeterminateChange.emit(this._indeterminate);
                });
            }
            this._checked = !this._checked;
            this._transitionCheckState(this._checked ? TransitionCheckState.Checked : TransitionCheckState.Unchecked);
            this._emitChangeEvent();
        } else if (this.disabled && this.disabledInteractive || !this.disabled && clickAction === "noop") {
            this._inputElement.nativeElement.checked = this.checked;
            this._inputElement.nativeElement.indeterminate = this.indeterminate;
        }
    }

    _onInteractionEvent(event) {
        event.stopPropagation();
    }

    _onBlur() {
        Promise.resolve().then(() => {
            this._onTouched();
            this._changeDetectorRef.markForCheck();
        });
    }

    _getAnimationClassForCheckStateTransition(oldState, newState) {
        if (this._animationMode === "NoopAnimations") {
            return "";
        }
        switch (oldState) {
            case TransitionCheckState.Init:
                if (newState === TransitionCheckState.Checked) {
                    return this._animationClasses.uncheckedToChecked;
                } else if (newState == TransitionCheckState.Indeterminate) {
                    return this._checked ? this._animationClasses.checkedToIndeterminate : this._animationClasses.uncheckedToIndeterminate;
                }
                break;
            case TransitionCheckState.Unchecked:
                return newState === TransitionCheckState.Checked ? this._animationClasses.uncheckedToChecked : this._animationClasses.uncheckedToIndeterminate;
            case TransitionCheckState.Checked:
                return newState === TransitionCheckState.Unchecked ? this._animationClasses.checkedToUnchecked : this._animationClasses.checkedToIndeterminate;
            case TransitionCheckState.Indeterminate:
                return newState === TransitionCheckState.Checked ? this._animationClasses.indeterminateToChecked : this._animationClasses.indeterminateToUnchecked;
        }
        return "";
    }

    /**
     * Syncs the indeterminate value with the checkbox DOM node.
     *
     * We sync `indeterminate` directly on the DOM node, because in Ivy the check for whether a
     * property is supported on an element boils down to `if (propName in element)`. Domino's
     * HTMLInputElement doesn't have an `indeterminate` property so Ivy will warn during
     * server-side rendering.
     */
    _syncIndeterminate(value) {
        const nativeCheckbox = this._inputElement;
        if (nativeCheckbox) {
            nativeCheckbox.nativeElement.indeterminate = value;
        }
    }

    _onInputClick() {
        this._handleInputClick();
    }

    _onTouchTargetClick() {
        this._handleInputClick();
        if (!this.disabled) {
            this._inputElement.nativeElement.focus();
        }
    }

    /**
     *  Prevent click events that come from the `<label/>` element from bubbling. This prevents the
     *  click handler on the host from triggering twice when clicking on the `<label/>` element. After
     *  the click event on the `<label/>` propagates, the browsers dispatches click on the associated
     *  `<input/>`. By preventing clicks on the label by bubbling, we ensure only one click event
     *  bubbles when the label is clicked.
     */
    _preventBubblingFromLabel(event) {
        if (!!event.target && this._labelElement.nativeElement.contains(event.target)) {
            event.stopPropagation();
        }
    }

    static {
        this.\u0275fac = function MatCheckbox_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _MatCheckbox)(\u0275\u0275directiveInject(ElementRef), \u0275\u0275directiveInject(ChangeDetectorRef), \u0275\u0275directiveInject(NgZone), \u0275\u0275injectAttribute("tabindex"), \u0275\u0275directiveInject(ANIMATION_MODULE_TYPE, 8), \u0275\u0275directiveInject(MAT_CHECKBOX_DEFAULT_OPTIONS, 8));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _MatCheckbox,
            selectors: [["mat-checkbox"]],
            viewQuery: function MatCheckbox_Query(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275viewQuery(_c07, 5);
                    \u0275\u0275viewQuery(_c12, 5);
                    \u0275\u0275viewQuery(MatRipple, 5);
                }
                if (rf & 2) {
                    let _t;
                    \u0275\u0275queryRefresh(_t = \u0275\u0275loadQuery()) && (ctx._inputElement = _t.first);
                    \u0275\u0275queryRefresh(_t = \u0275\u0275loadQuery()) && (ctx._labelElement = _t.first);
                    \u0275\u0275queryRefresh(_t = \u0275\u0275loadQuery()) && (ctx.ripple = _t.first);
                }
            },
            hostAttrs: [1, "mat-mdc-checkbox"],
            hostVars: 16,
            hostBindings: function MatCheckbox_HostBindings(rf, ctx) {
                if (rf & 2) {
                    \u0275\u0275hostProperty("id", ctx.id);
                    \u0275\u0275attribute("tabindex", null)("aria-label", null)("aria-labelledby", null);
                    \u0275\u0275classMap(ctx.color ? "mat-" + ctx.color : "mat-accent");
                    \u0275\u0275classProp("_mat-animation-noopable", ctx._animationMode === "NoopAnimations")("mdc-checkbox--disabled", ctx.disabled)("mat-mdc-checkbox-disabled", ctx.disabled)("mat-mdc-checkbox-checked", ctx.checked)("mat-mdc-checkbox-disabled-interactive", ctx.disabledInteractive);
                }
            },
            inputs: {
                ariaLabel: [0, "aria-label", "ariaLabel"],
                ariaLabelledby: [0, "aria-labelledby", "ariaLabelledby"],
                ariaDescribedby: [0, "aria-describedby", "ariaDescribedby"],
                id: "id",
                required: [2, "required", "required", booleanAttribute],
                labelPosition: "labelPosition",
                name: "name",
                value: "value",
                disableRipple: [2, "disableRipple", "disableRipple", booleanAttribute],
                tabIndex: [2, "tabIndex", "tabIndex", (value) => value == null ? void 0 : numberAttribute(value)],
                color: "color",
                disabledInteractive: [2, "disabledInteractive", "disabledInteractive", booleanAttribute],
                checked: [2, "checked", "checked", booleanAttribute],
                disabled: [2, "disabled", "disabled", booleanAttribute],
                indeterminate: [2, "indeterminate", "indeterminate", booleanAttribute]
            },
            outputs: {
                change: "change",
                indeterminateChange: "indeterminateChange"
            },
            exportAs: ["matCheckbox"],
            standalone: true,
            features: [\u0275\u0275ProvidersFeature([MAT_CHECKBOX_CONTROL_VALUE_ACCESSOR, {
                provide: NG_VALIDATORS,
                useExisting: _MatCheckbox,
                multi: true
            }]), \u0275\u0275InputTransformsFeature, \u0275\u0275NgOnChangesFeature, \u0275\u0275StandaloneFeature],
            ngContentSelectors: _c2,
            decls: 15,
            vars: 20,
            consts: [["checkbox", ""], ["input", ""], ["label", ""], ["mat-internal-form-field", "", 3, "click", "labelPosition"], [1, "mdc-checkbox"], [1, "mat-mdc-checkbox-touch-target", 3, "click"], ["type", "checkbox", 1, "mdc-checkbox__native-control", 3, "blur", "click", "change", "checked", "indeterminate", "disabled", "id", "required", "tabIndex"], [1, "mdc-checkbox__ripple"], [1, "mdc-checkbox__background"], ["focusable", "false", "viewBox", "0 0 24 24", "aria-hidden", "true", 1, "mdc-checkbox__checkmark"], ["fill", "none", "d", "M1.73,12.91 8.1,19.28 22.79,4.59", 1, "mdc-checkbox__checkmark-path"], [1, "mdc-checkbox__mixedmark"], ["mat-ripple", "", 1, "mat-mdc-checkbox-ripple", "mat-mdc-focus-indicator", 3, "matRippleTrigger", "matRippleDisabled", "matRippleCentered"], [1, "mdc-label", 3, "for"]],
            template: function MatCheckbox_Template(rf, ctx) {
                if (rf & 1) {
                    const _r1 = \u0275\u0275getCurrentView();
                    \u0275\u0275projectionDef();
                    \u0275\u0275elementStart(0, "div", 3);
                    \u0275\u0275listener("click", function MatCheckbox_Template_div_click_0_listener($event) {
                        \u0275\u0275restoreView(_r1);
                        return \u0275\u0275resetView(ctx._preventBubblingFromLabel($event));
                    });
                    \u0275\u0275elementStart(1, "div", 4, 0)(3, "div", 5);
                    \u0275\u0275listener("click", function MatCheckbox_Template_div_click_3_listener() {
                        \u0275\u0275restoreView(_r1);
                        return \u0275\u0275resetView(ctx._onTouchTargetClick());
                    });
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(4, "input", 6, 1);
                    \u0275\u0275listener("blur", function MatCheckbox_Template_input_blur_4_listener() {
                        \u0275\u0275restoreView(_r1);
                        return \u0275\u0275resetView(ctx._onBlur());
                    })("click", function MatCheckbox_Template_input_click_4_listener() {
                        \u0275\u0275restoreView(_r1);
                        return \u0275\u0275resetView(ctx._onInputClick());
                    })("change", function MatCheckbox_Template_input_change_4_listener($event) {
                        \u0275\u0275restoreView(_r1);
                        return \u0275\u0275resetView(ctx._onInteractionEvent($event));
                    });
                    \u0275\u0275elementEnd();
                    \u0275\u0275element(6, "div", 7);
                    \u0275\u0275elementStart(7, "div", 8);
                    \u0275\u0275namespaceSVG();
                    \u0275\u0275elementStart(8, "svg", 9);
                    \u0275\u0275element(9, "path", 10);
                    \u0275\u0275elementEnd();
                    \u0275\u0275namespaceHTML();
                    \u0275\u0275element(10, "div", 11);
                    \u0275\u0275elementEnd();
                    \u0275\u0275element(11, "div", 12);
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(12, "label", 13, 2);
                    \u0275\u0275projection(14);
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    const checkbox_r2 = \u0275\u0275reference(2);
                    \u0275\u0275property("labelPosition", ctx.labelPosition);
                    \u0275\u0275advance(4);
                    \u0275\u0275classProp("mdc-checkbox--selected", ctx.checked);
                    \u0275\u0275property("checked", ctx.checked)("indeterminate", ctx.indeterminate)("disabled", ctx.disabled && !ctx.disabledInteractive)("id", ctx.inputId)("required", ctx.required)("tabIndex", ctx.disabled && !ctx.disabledInteractive ? -1 : ctx.tabIndex);
                    \u0275\u0275attribute("aria-label", ctx.ariaLabel || null)("aria-labelledby", ctx.ariaLabelledby)("aria-describedby", ctx.ariaDescribedby)("aria-checked", ctx.indeterminate ? "mixed" : null)("aria-disabled", ctx.disabled && ctx.disabledInteractive ? true : null)("name", ctx.name)("value", ctx.value);
                    \u0275\u0275advance(7);
                    \u0275\u0275property("matRippleTrigger", checkbox_r2)("matRippleDisabled", ctx.disableRipple || ctx.disabled)("matRippleCentered", true);
                    \u0275\u0275advance();
                    \u0275\u0275property("for", ctx.inputId);
                }
            },
            dependencies: [MatRipple, _MatInternalFormField],
            styles: ['.mdc-checkbox{display:inline-block;position:relative;flex:0 0 18px;box-sizing:content-box;width:18px;height:18px;line-height:0;white-space:nowrap;cursor:pointer;vertical-align:bottom;padding:calc((var(--mdc-checkbox-state-layer-size, 40px) - 18px)/2);margin:calc((var(--mdc-checkbox-state-layer-size, 40px) - var(--mdc-checkbox-state-layer-size, 40px))/2)}.mdc-checkbox:hover .mdc-checkbox__ripple{opacity:var(--mdc-checkbox-unselected-hover-state-layer-opacity, var(--mat-app-hover-state-layer-opacity));background-color:var(--mdc-checkbox-unselected-hover-state-layer-color, var(--mat-app-on-surface))}.mdc-checkbox:hover .mat-mdc-checkbox-ripple .mat-ripple-element{background-color:var(--mdc-checkbox-unselected-hover-state-layer-color, var(--mat-app-on-surface))}.mdc-checkbox .mdc-checkbox__native-control:focus~.mdc-checkbox__ripple{opacity:var(--mdc-checkbox-unselected-focus-state-layer-opacity, var(--mat-app-focus-state-layer-opacity));background-color:var(--mdc-checkbox-unselected-focus-state-layer-color, var(--mat-app-on-surface))}.mdc-checkbox .mdc-checkbox__native-control:focus~.mat-mdc-checkbox-ripple .mat-ripple-element{background-color:var(--mdc-checkbox-unselected-focus-state-layer-color, var(--mat-app-on-surface))}.mdc-checkbox:active .mdc-checkbox__native-control~.mdc-checkbox__ripple{opacity:var(--mdc-checkbox-unselected-pressed-state-layer-opacity, var(--mat-app-pressed-state-layer-opacity));background-color:var(--mdc-checkbox-unselected-pressed-state-layer-color, var(--mat-app-primary))}.mdc-checkbox:active .mdc-checkbox__native-control~.mat-mdc-checkbox-ripple .mat-ripple-element{background-color:var(--mdc-checkbox-unselected-pressed-state-layer-color, var(--mat-app-primary))}.mdc-checkbox:hover .mdc-checkbox__native-control:checked~.mdc-checkbox__ripple{opacity:var(--mdc-checkbox-selected-hover-state-layer-opacity, var(--mat-app-hover-state-layer-opacity));background-color:var(--mdc-checkbox-selected-hover-state-layer-color, var(--mat-app-primary))}.mdc-checkbox:hover .mdc-checkbox__native-control:checked~.mat-mdc-checkbox-ripple .mat-ripple-element{background-color:var(--mdc-checkbox-selected-hover-state-layer-color, var(--mat-app-primary))}.mdc-checkbox .mdc-checkbox__native-control:focus:checked~.mdc-checkbox__ripple{opacity:var(--mdc-checkbox-selected-focus-state-layer-opacity, var(--mat-app-focus-state-layer-opacity));background-color:var(--mdc-checkbox-selected-focus-state-layer-color, var(--mat-app-primary))}.mdc-checkbox .mdc-checkbox__native-control:focus:checked~.mat-mdc-checkbox-ripple .mat-ripple-element{background-color:var(--mdc-checkbox-selected-focus-state-layer-color, var(--mat-app-primary))}.mdc-checkbox:active .mdc-checkbox__native-control:checked~.mdc-checkbox__ripple{opacity:var(--mdc-checkbox-selected-pressed-state-layer-opacity, var(--mat-app-pressed-state-layer-opacity));background-color:var(--mdc-checkbox-selected-pressed-state-layer-color, var(--mat-app-on-surface))}.mdc-checkbox:active .mdc-checkbox__native-control:checked~.mat-mdc-checkbox-ripple .mat-ripple-element{background-color:var(--mdc-checkbox-selected-pressed-state-layer-color, var(--mat-app-on-surface))}.mdc-checkbox--disabled.mat-mdc-checkbox-disabled-interactive .mdc-checkbox .mdc-checkbox__native-control~.mat-mdc-checkbox-ripple .mat-ripple-element,.mdc-checkbox--disabled.mat-mdc-checkbox-disabled-interactive .mdc-checkbox .mdc-checkbox__native-control~.mdc-checkbox__ripple{background-color:var(--mdc-checkbox-unselected-hover-state-layer-color, var(--mat-app-on-surface))}.mdc-checkbox .mdc-checkbox__native-control{position:absolute;margin:0;padding:0;opacity:0;cursor:inherit;width:var(--mdc-checkbox-state-layer-size, 40px);height:var(--mdc-checkbox-state-layer-size, 40px);top:calc((var(--mdc-checkbox-state-layer-size, 40px) - var(--mdc-checkbox-state-layer-size, 40px))/2);right:calc((var(--mdc-checkbox-state-layer-size, 40px) - var(--mdc-checkbox-state-layer-size, 40px))/2);left:calc((var(--mdc-checkbox-state-layer-size, 40px) - var(--mdc-checkbox-state-layer-size, 40px))/2)}.mdc-checkbox--disabled{cursor:default;pointer-events:none}.cdk-high-contrast-active .mdc-checkbox--disabled{opacity:.5}.mdc-checkbox__background{display:inline-flex;position:absolute;align-items:center;justify-content:center;box-sizing:border-box;width:18px;height:18px;border:2px solid currentColor;border-radius:2px;background-color:rgba(0,0,0,0);pointer-events:none;will-change:background-color,border-color;transition:background-color 90ms cubic-bezier(0.4, 0, 0.6, 1),border-color 90ms cubic-bezier(0.4, 0, 0.6, 1);-webkit-print-color-adjust:exact;color-adjust:exact;border-color:var(--mdc-checkbox-unselected-icon-color, var(--mat-app-on-surface-variant));top:calc((var(--mdc-checkbox-state-layer-size, 40px) - 18px)/2);left:calc((var(--mdc-checkbox-state-layer-size, 40px) - 18px)/2)}.mdc-checkbox__native-control:enabled:checked~.mdc-checkbox__background,.mdc-checkbox__native-control:enabled:indeterminate~.mdc-checkbox__background{border-color:var(--mdc-checkbox-selected-icon-color, var(--mat-app-primary));background-color:var(--mdc-checkbox-selected-icon-color, var(--mat-app-primary))}.mdc-checkbox--disabled .mdc-checkbox__background{border-color:var(--mdc-checkbox-disabled-unselected-icon-color)}.mdc-checkbox__native-control:disabled:checked~.mdc-checkbox__background,.mdc-checkbox__native-control:disabled:indeterminate~.mdc-checkbox__background{background-color:var(--mdc-checkbox-disabled-selected-icon-color);border-color:rgba(0,0,0,0)}.mdc-checkbox:hover .mdc-checkbox__native-control:not(:checked)~.mdc-checkbox__background,.mdc-checkbox:hover .mdc-checkbox__native-control:not(:indeterminate)~.mdc-checkbox__background{border-color:var(--mdc-checkbox-unselected-hover-icon-color, var(--mat-app-on-surface));background-color:rgba(0,0,0,0)}.mdc-checkbox:hover .mdc-checkbox__native-control:checked~.mdc-checkbox__background,.mdc-checkbox:hover .mdc-checkbox__native-control:indeterminate~.mdc-checkbox__background{border-color:var(--mdc-checkbox-selected-hover-icon-color, var(--mat-app-primary));background-color:var(--mdc-checkbox-selected-hover-icon-color, var(--mat-app-primary))}.mdc-checkbox__native-control:focus:focus:not(:checked)~.mdc-checkbox__background,.mdc-checkbox__native-control:focus:focus:not(:indeterminate)~.mdc-checkbox__background{border-color:var(--mdc-checkbox-unselected-focus-icon-color, var(--mat-app-on-surface))}.mdc-checkbox__native-control:focus:focus:checked~.mdc-checkbox__background,.mdc-checkbox__native-control:focus:focus:indeterminate~.mdc-checkbox__background{border-color:var(--mdc-checkbox-selected-focus-icon-color, var(--mat-app-primary));background-color:var(--mdc-checkbox-selected-focus-icon-color, var(--mat-app-primary))}.mdc-checkbox--disabled.mat-mdc-checkbox-disabled-interactive .mdc-checkbox:hover .mdc-checkbox__native-control~.mdc-checkbox__background,.mdc-checkbox--disabled.mat-mdc-checkbox-disabled-interactive .mdc-checkbox .mdc-checkbox__native-control:focus~.mdc-checkbox__background,.mdc-checkbox--disabled.mat-mdc-checkbox-disabled-interactive .mdc-checkbox__background{border-color:var(--mdc-checkbox-disabled-unselected-icon-color)}.mdc-checkbox--disabled.mat-mdc-checkbox-disabled-interactive .mdc-checkbox__native-control:checked~.mdc-checkbox__background,.mdc-checkbox--disabled.mat-mdc-checkbox-disabled-interactive .mdc-checkbox__native-control:indeterminate~.mdc-checkbox__background{background-color:var(--mdc-checkbox-disabled-selected-icon-color);border-color:rgba(0,0,0,0)}.mdc-checkbox__checkmark{position:absolute;top:0;right:0;bottom:0;left:0;width:100%;opacity:0;transition:opacity 180ms cubic-bezier(0.4, 0, 0.6, 1);color:var(--mdc-checkbox-selected-checkmark-color, var(--mat-app-on-primary))}.cdk-high-contrast-active .mdc-checkbox__checkmark{color:CanvasText}.mdc-checkbox--disabled .mdc-checkbox__checkmark,.mdc-checkbox--disabled.mat-mdc-checkbox-disabled-interactive .mdc-checkbox__checkmark{color:var(--mdc-checkbox-disabled-selected-checkmark-color, var(--mat-app-surface))}.cdk-high-contrast-active .mdc-checkbox--disabled .mdc-checkbox__checkmark,.cdk-high-contrast-active .mdc-checkbox--disabled.mat-mdc-checkbox-disabled-interactive .mdc-checkbox__checkmark{color:CanvasText}.mdc-checkbox__checkmark-path{transition:stroke-dashoffset 180ms cubic-bezier(0.4, 0, 0.6, 1);stroke:currentColor;stroke-width:3.12px;stroke-dashoffset:29.7833385;stroke-dasharray:29.7833385}.mdc-checkbox__mixedmark{width:100%;height:0;transform:scaleX(0) rotate(0deg);border-width:1px;border-style:solid;opacity:0;transition:opacity 90ms cubic-bezier(0.4, 0, 0.6, 1),transform 90ms cubic-bezier(0.4, 0, 0.6, 1);border-color:var(--mdc-checkbox-selected-checkmark-color, var(--mat-app-on-primary))}.cdk-high-contrast-active .mdc-checkbox__mixedmark{margin:0 1px}.mdc-checkbox--disabled .mdc-checkbox__mixedmark,.mdc-checkbox--disabled.mat-mdc-checkbox-disabled-interactive .mdc-checkbox__mixedmark{border-color:var(--mdc-checkbox-disabled-selected-checkmark-color, var(--mat-app-surface))}.mdc-checkbox--anim-unchecked-checked .mdc-checkbox__background,.mdc-checkbox--anim-unchecked-indeterminate .mdc-checkbox__background,.mdc-checkbox--anim-checked-unchecked .mdc-checkbox__background,.mdc-checkbox--anim-indeterminate-unchecked .mdc-checkbox__background{animation-duration:180ms;animation-timing-function:linear}.mdc-checkbox--anim-unchecked-checked .mdc-checkbox__checkmark-path{animation:mdc-checkbox-unchecked-checked-checkmark-path 180ms linear;transition:none}.mdc-checkbox--anim-unchecked-indeterminate .mdc-checkbox__mixedmark{animation:mdc-checkbox-unchecked-indeterminate-mixedmark 90ms linear;transition:none}.mdc-checkbox--anim-checked-unchecked .mdc-checkbox__checkmark-path{animation:mdc-checkbox-checked-unchecked-checkmark-path 90ms linear;transition:none}.mdc-checkbox--anim-checked-indeterminate .mdc-checkbox__checkmark{animation:mdc-checkbox-checked-indeterminate-checkmark 90ms linear;transition:none}.mdc-checkbox--anim-checked-indeterminate .mdc-checkbox__mixedmark{animation:mdc-checkbox-checked-indeterminate-mixedmark 90ms linear;transition:none}.mdc-checkbox--anim-indeterminate-checked .mdc-checkbox__checkmark{animation:mdc-checkbox-indeterminate-checked-checkmark 500ms linear;transition:none}.mdc-checkbox--anim-indeterminate-checked .mdc-checkbox__mixedmark{animation:mdc-checkbox-indeterminate-checked-mixedmark 500ms linear;transition:none}.mdc-checkbox--anim-indeterminate-unchecked .mdc-checkbox__mixedmark{animation:mdc-checkbox-indeterminate-unchecked-mixedmark 300ms linear;transition:none}.mdc-checkbox__native-control:checked~.mdc-checkbox__background,.mdc-checkbox__native-control:indeterminate~.mdc-checkbox__background{transition:border-color 90ms cubic-bezier(0, 0, 0.2, 1),background-color 90ms cubic-bezier(0, 0, 0.2, 1)}.mdc-checkbox__native-control:checked~.mdc-checkbox__background .mdc-checkbox__checkmark-path,.mdc-checkbox__native-control:indeterminate~.mdc-checkbox__background .mdc-checkbox__checkmark-path{stroke-dashoffset:0}.mdc-checkbox__native-control:checked~.mdc-checkbox__background .mdc-checkbox__checkmark{transition:opacity 180ms cubic-bezier(0, 0, 0.2, 1),transform 180ms cubic-bezier(0, 0, 0.2, 1);opacity:1}.mdc-checkbox__native-control:checked~.mdc-checkbox__background .mdc-checkbox__mixedmark{transform:scaleX(1) rotate(-45deg)}.mdc-checkbox__native-control:indeterminate~.mdc-checkbox__background .mdc-checkbox__checkmark{transform:rotate(45deg);opacity:0;transition:opacity 90ms cubic-bezier(0.4, 0, 0.6, 1),transform 90ms cubic-bezier(0.4, 0, 0.6, 1)}.mdc-checkbox__native-control:indeterminate~.mdc-checkbox__background .mdc-checkbox__mixedmark{transform:scaleX(1) rotate(0deg);opacity:1}@keyframes mdc-checkbox-unchecked-checked-checkmark-path{0%,50%{stroke-dashoffset:29.7833385}50%{animation-timing-function:cubic-bezier(0, 0, 0.2, 1)}100%{stroke-dashoffset:0}}@keyframes mdc-checkbox-unchecked-indeterminate-mixedmark{0%,68.2%{transform:scaleX(0)}68.2%{animation-timing-function:cubic-bezier(0, 0, 0, 1)}100%{transform:scaleX(1)}}@keyframes mdc-checkbox-checked-unchecked-checkmark-path{from{animation-timing-function:cubic-bezier(0.4, 0, 1, 1);opacity:1;stroke-dashoffset:0}to{opacity:0;stroke-dashoffset:-29.7833385}}@keyframes mdc-checkbox-checked-indeterminate-checkmark{from{animation-timing-function:cubic-bezier(0, 0, 0.2, 1);transform:rotate(0deg);opacity:1}to{transform:rotate(45deg);opacity:0}}@keyframes mdc-checkbox-indeterminate-checked-checkmark{from{animation-timing-function:cubic-bezier(0.14, 0, 0, 1);transform:rotate(45deg);opacity:0}to{transform:rotate(360deg);opacity:1}}@keyframes mdc-checkbox-checked-indeterminate-mixedmark{from{animation-timing-function:cubic-bezier(0, 0, 0.2, 1);transform:rotate(-45deg);opacity:0}to{transform:rotate(0deg);opacity:1}}@keyframes mdc-checkbox-indeterminate-checked-mixedmark{from{animation-timing-function:cubic-bezier(0.14, 0, 0, 1);transform:rotate(0deg);opacity:1}to{transform:rotate(315deg);opacity:0}}@keyframes mdc-checkbox-indeterminate-unchecked-mixedmark{0%{animation-timing-function:linear;transform:scaleX(1);opacity:1}32.8%,100%{transform:scaleX(0);opacity:0}}.mat-mdc-checkbox{display:inline-block;position:relative;-webkit-tap-highlight-color:rgba(0,0,0,0)}.mat-mdc-checkbox._mat-animation-noopable .mdc-checkbox *,.mat-mdc-checkbox._mat-animation-noopable .mdc-checkbox *::before{transition:none !important;animation:none !important}.mat-mdc-checkbox label{cursor:pointer}.mat-mdc-checkbox .mat-internal-form-field{color:var(--mat-checkbox-label-text-color, var(--mat-app-on-surface));font-family:var(--mat-checkbox-label-text-font, var(--mat-app-body-medium-font));line-height:var(--mat-checkbox-label-text-line-height, var(--mat-app-body-medium-line-height));font-size:var(--mat-checkbox-label-text-size, var(--mat-app-body-medium-size));letter-spacing:var(--mat-checkbox-label-text-tracking, var(--mat-app-body-medium-tracking));font-weight:var(--mat-checkbox-label-text-weight, var(--mat-app-body-medium-weight))}.mat-mdc-checkbox.mat-mdc-checkbox-disabled.mat-mdc-checkbox-disabled-interactive{pointer-events:auto}.mat-mdc-checkbox.mat-mdc-checkbox-disabled.mat-mdc-checkbox-disabled-interactive input{cursor:default}.mat-mdc-checkbox.mat-mdc-checkbox-disabled label{cursor:default;color:var(--mat-checkbox-disabled-label-color)}.mat-mdc-checkbox label:empty{display:none}.mat-mdc-checkbox .mdc-checkbox__ripple{opacity:0}.mat-mdc-checkbox-ripple,.mdc-checkbox__ripple{top:0;left:0;right:0;bottom:0;position:absolute;border-radius:50%;pointer-events:none}.mat-mdc-checkbox-ripple:not(:empty),.mdc-checkbox__ripple:not(:empty){transform:translateZ(0)}.mat-mdc-checkbox-ripple .mat-ripple-element{opacity:.1}.mat-mdc-checkbox-touch-target{position:absolute;top:50%;left:50%;height:48px;width:48px;transform:translate(-50%, -50%);display:var(--mat-checkbox-touch-target-display)}.mat-mdc-checkbox-ripple::before{border-radius:50%}.mdc-checkbox__native-control:focus~.mat-mdc-focus-indicator::before{content:""}'],
            encapsulation: 2,
            changeDetection: 0
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && setClassMetadata(MatCheckbox, [{
        type: Component,
        args: [{
            selector: "mat-checkbox",
            host: {
                "class": "mat-mdc-checkbox",
                "[attr.tabindex]": "null",
                "[attr.aria-label]": "null",
                "[attr.aria-labelledby]": "null",
                "[class._mat-animation-noopable]": `_animationMode === 'NoopAnimations'`,
                "[class.mdc-checkbox--disabled]": "disabled",
                "[id]": "id",
                // Add classes that users can use to more easily target disabled or checked checkboxes.
                "[class.mat-mdc-checkbox-disabled]": "disabled",
                "[class.mat-mdc-checkbox-checked]": "checked",
                "[class.mat-mdc-checkbox-disabled-interactive]": "disabledInteractive",
                "[class]": 'color ? "mat-" + color : "mat-accent"'
            },
            providers: [MAT_CHECKBOX_CONTROL_VALUE_ACCESSOR, {
                provide: NG_VALIDATORS,
                useExisting: MatCheckbox,
                multi: true
            }],
            exportAs: "matCheckbox",
            encapsulation: ViewEncapsulation$1.None,
            changeDetection: ChangeDetectionStrategy.OnPush,
            standalone: true,
            imports: [MatRipple, _MatInternalFormField],
            template: `<div mat-internal-form-field [labelPosition]="labelPosition" (click)="_preventBubblingFromLabel($event)">
  <div #checkbox class="mdc-checkbox">
    <!-- Render this element first so the input is on top. -->
    <div class="mat-mdc-checkbox-touch-target" (click)="_onTouchTargetClick()"></div>
    <input #input
           type="checkbox"
           class="mdc-checkbox__native-control"
           [class.mdc-checkbox--selected]="checked"
           [attr.aria-label]="ariaLabel || null"
           [attr.aria-labelledby]="ariaLabelledby"
           [attr.aria-describedby]="ariaDescribedby"
           [attr.aria-checked]="indeterminate ? 'mixed' : null"
           [attr.aria-disabled]="disabled && disabledInteractive ? true : null"
           [attr.name]="name"
           [attr.value]="value"
           [checked]="checked"
           [indeterminate]="indeterminate"
           [disabled]="disabled && !disabledInteractive"
           [id]="inputId"
           [required]="required"
           [tabIndex]="disabled && !disabledInteractive ? -1 : tabIndex"
           (blur)="_onBlur()"
           (click)="_onInputClick()"
           (change)="_onInteractionEvent($event)"/>
    <div class="mdc-checkbox__ripple"></div>
    <div class="mdc-checkbox__background">
      <svg class="mdc-checkbox__checkmark"
           focusable="false"
           viewBox="0 0 24 24"
           aria-hidden="true">
        <path class="mdc-checkbox__checkmark-path"
              fill="none"
              d="M1.73,12.91 8.1,19.28 22.79,4.59"/>
      </svg>
      <div class="mdc-checkbox__mixedmark"></div>
    </div>
    <div class="mat-mdc-checkbox-ripple mat-mdc-focus-indicator" mat-ripple
      [matRippleTrigger]="checkbox"
      [matRippleDisabled]="disableRipple || disabled"
      [matRippleCentered]="true"></div>
  </div>
  <!--
    Avoid putting a click handler on the <label/> to fix duplicate navigation stop on Talk Back
    (#14385). Putting a click handler on the <label/> caused this bug because the browser produced
    an unnecessary accessibility tree node.
  -->
  <label class="mdc-label" #label [for]="inputId">
    <ng-content></ng-content>
  </label>
</div>
`,
            styles: ['.mdc-checkbox{display:inline-block;position:relative;flex:0 0 18px;box-sizing:content-box;width:18px;height:18px;line-height:0;white-space:nowrap;cursor:pointer;vertical-align:bottom;padding:calc((var(--mdc-checkbox-state-layer-size, 40px) - 18px)/2);margin:calc((var(--mdc-checkbox-state-layer-size, 40px) - var(--mdc-checkbox-state-layer-size, 40px))/2)}.mdc-checkbox:hover .mdc-checkbox__ripple{opacity:var(--mdc-checkbox-unselected-hover-state-layer-opacity, var(--mat-app-hover-state-layer-opacity));background-color:var(--mdc-checkbox-unselected-hover-state-layer-color, var(--mat-app-on-surface))}.mdc-checkbox:hover .mat-mdc-checkbox-ripple .mat-ripple-element{background-color:var(--mdc-checkbox-unselected-hover-state-layer-color, var(--mat-app-on-surface))}.mdc-checkbox .mdc-checkbox__native-control:focus~.mdc-checkbox__ripple{opacity:var(--mdc-checkbox-unselected-focus-state-layer-opacity, var(--mat-app-focus-state-layer-opacity));background-color:var(--mdc-checkbox-unselected-focus-state-layer-color, var(--mat-app-on-surface))}.mdc-checkbox .mdc-checkbox__native-control:focus~.mat-mdc-checkbox-ripple .mat-ripple-element{background-color:var(--mdc-checkbox-unselected-focus-state-layer-color, var(--mat-app-on-surface))}.mdc-checkbox:active .mdc-checkbox__native-control~.mdc-checkbox__ripple{opacity:var(--mdc-checkbox-unselected-pressed-state-layer-opacity, var(--mat-app-pressed-state-layer-opacity));background-color:var(--mdc-checkbox-unselected-pressed-state-layer-color, var(--mat-app-primary))}.mdc-checkbox:active .mdc-checkbox__native-control~.mat-mdc-checkbox-ripple .mat-ripple-element{background-color:var(--mdc-checkbox-unselected-pressed-state-layer-color, var(--mat-app-primary))}.mdc-checkbox:hover .mdc-checkbox__native-control:checked~.mdc-checkbox__ripple{opacity:var(--mdc-checkbox-selected-hover-state-layer-opacity, var(--mat-app-hover-state-layer-opacity));background-color:var(--mdc-checkbox-selected-hover-state-layer-color, var(--mat-app-primary))}.mdc-checkbox:hover .mdc-checkbox__native-control:checked~.mat-mdc-checkbox-ripple .mat-ripple-element{background-color:var(--mdc-checkbox-selected-hover-state-layer-color, var(--mat-app-primary))}.mdc-checkbox .mdc-checkbox__native-control:focus:checked~.mdc-checkbox__ripple{opacity:var(--mdc-checkbox-selected-focus-state-layer-opacity, var(--mat-app-focus-state-layer-opacity));background-color:var(--mdc-checkbox-selected-focus-state-layer-color, var(--mat-app-primary))}.mdc-checkbox .mdc-checkbox__native-control:focus:checked~.mat-mdc-checkbox-ripple .mat-ripple-element{background-color:var(--mdc-checkbox-selected-focus-state-layer-color, var(--mat-app-primary))}.mdc-checkbox:active .mdc-checkbox__native-control:checked~.mdc-checkbox__ripple{opacity:var(--mdc-checkbox-selected-pressed-state-layer-opacity, var(--mat-app-pressed-state-layer-opacity));background-color:var(--mdc-checkbox-selected-pressed-state-layer-color, var(--mat-app-on-surface))}.mdc-checkbox:active .mdc-checkbox__native-control:checked~.mat-mdc-checkbox-ripple .mat-ripple-element{background-color:var(--mdc-checkbox-selected-pressed-state-layer-color, var(--mat-app-on-surface))}.mdc-checkbox--disabled.mat-mdc-checkbox-disabled-interactive .mdc-checkbox .mdc-checkbox__native-control~.mat-mdc-checkbox-ripple .mat-ripple-element,.mdc-checkbox--disabled.mat-mdc-checkbox-disabled-interactive .mdc-checkbox .mdc-checkbox__native-control~.mdc-checkbox__ripple{background-color:var(--mdc-checkbox-unselected-hover-state-layer-color, var(--mat-app-on-surface))}.mdc-checkbox .mdc-checkbox__native-control{position:absolute;margin:0;padding:0;opacity:0;cursor:inherit;width:var(--mdc-checkbox-state-layer-size, 40px);height:var(--mdc-checkbox-state-layer-size, 40px);top:calc((var(--mdc-checkbox-state-layer-size, 40px) - var(--mdc-checkbox-state-layer-size, 40px))/2);right:calc((var(--mdc-checkbox-state-layer-size, 40px) - var(--mdc-checkbox-state-layer-size, 40px))/2);left:calc((var(--mdc-checkbox-state-layer-size, 40px) - var(--mdc-checkbox-state-layer-size, 40px))/2)}.mdc-checkbox--disabled{cursor:default;pointer-events:none}.cdk-high-contrast-active .mdc-checkbox--disabled{opacity:.5}.mdc-checkbox__background{display:inline-flex;position:absolute;align-items:center;justify-content:center;box-sizing:border-box;width:18px;height:18px;border:2px solid currentColor;border-radius:2px;background-color:rgba(0,0,0,0);pointer-events:none;will-change:background-color,border-color;transition:background-color 90ms cubic-bezier(0.4, 0, 0.6, 1),border-color 90ms cubic-bezier(0.4, 0, 0.6, 1);-webkit-print-color-adjust:exact;color-adjust:exact;border-color:var(--mdc-checkbox-unselected-icon-color, var(--mat-app-on-surface-variant));top:calc((var(--mdc-checkbox-state-layer-size, 40px) - 18px)/2);left:calc((var(--mdc-checkbox-state-layer-size, 40px) - 18px)/2)}.mdc-checkbox__native-control:enabled:checked~.mdc-checkbox__background,.mdc-checkbox__native-control:enabled:indeterminate~.mdc-checkbox__background{border-color:var(--mdc-checkbox-selected-icon-color, var(--mat-app-primary));background-color:var(--mdc-checkbox-selected-icon-color, var(--mat-app-primary))}.mdc-checkbox--disabled .mdc-checkbox__background{border-color:var(--mdc-checkbox-disabled-unselected-icon-color)}.mdc-checkbox__native-control:disabled:checked~.mdc-checkbox__background,.mdc-checkbox__native-control:disabled:indeterminate~.mdc-checkbox__background{background-color:var(--mdc-checkbox-disabled-selected-icon-color);border-color:rgba(0,0,0,0)}.mdc-checkbox:hover .mdc-checkbox__native-control:not(:checked)~.mdc-checkbox__background,.mdc-checkbox:hover .mdc-checkbox__native-control:not(:indeterminate)~.mdc-checkbox__background{border-color:var(--mdc-checkbox-unselected-hover-icon-color, var(--mat-app-on-surface));background-color:rgba(0,0,0,0)}.mdc-checkbox:hover .mdc-checkbox__native-control:checked~.mdc-checkbox__background,.mdc-checkbox:hover .mdc-checkbox__native-control:indeterminate~.mdc-checkbox__background{border-color:var(--mdc-checkbox-selected-hover-icon-color, var(--mat-app-primary));background-color:var(--mdc-checkbox-selected-hover-icon-color, var(--mat-app-primary))}.mdc-checkbox__native-control:focus:focus:not(:checked)~.mdc-checkbox__background,.mdc-checkbox__native-control:focus:focus:not(:indeterminate)~.mdc-checkbox__background{border-color:var(--mdc-checkbox-unselected-focus-icon-color, var(--mat-app-on-surface))}.mdc-checkbox__native-control:focus:focus:checked~.mdc-checkbox__background,.mdc-checkbox__native-control:focus:focus:indeterminate~.mdc-checkbox__background{border-color:var(--mdc-checkbox-selected-focus-icon-color, var(--mat-app-primary));background-color:var(--mdc-checkbox-selected-focus-icon-color, var(--mat-app-primary))}.mdc-checkbox--disabled.mat-mdc-checkbox-disabled-interactive .mdc-checkbox:hover .mdc-checkbox__native-control~.mdc-checkbox__background,.mdc-checkbox--disabled.mat-mdc-checkbox-disabled-interactive .mdc-checkbox .mdc-checkbox__native-control:focus~.mdc-checkbox__background,.mdc-checkbox--disabled.mat-mdc-checkbox-disabled-interactive .mdc-checkbox__background{border-color:var(--mdc-checkbox-disabled-unselected-icon-color)}.mdc-checkbox--disabled.mat-mdc-checkbox-disabled-interactive .mdc-checkbox__native-control:checked~.mdc-checkbox__background,.mdc-checkbox--disabled.mat-mdc-checkbox-disabled-interactive .mdc-checkbox__native-control:indeterminate~.mdc-checkbox__background{background-color:var(--mdc-checkbox-disabled-selected-icon-color);border-color:rgba(0,0,0,0)}.mdc-checkbox__checkmark{position:absolute;top:0;right:0;bottom:0;left:0;width:100%;opacity:0;transition:opacity 180ms cubic-bezier(0.4, 0, 0.6, 1);color:var(--mdc-checkbox-selected-checkmark-color, var(--mat-app-on-primary))}.cdk-high-contrast-active .mdc-checkbox__checkmark{color:CanvasText}.mdc-checkbox--disabled .mdc-checkbox__checkmark,.mdc-checkbox--disabled.mat-mdc-checkbox-disabled-interactive .mdc-checkbox__checkmark{color:var(--mdc-checkbox-disabled-selected-checkmark-color, var(--mat-app-surface))}.cdk-high-contrast-active .mdc-checkbox--disabled .mdc-checkbox__checkmark,.cdk-high-contrast-active .mdc-checkbox--disabled.mat-mdc-checkbox-disabled-interactive .mdc-checkbox__checkmark{color:CanvasText}.mdc-checkbox__checkmark-path{transition:stroke-dashoffset 180ms cubic-bezier(0.4, 0, 0.6, 1);stroke:currentColor;stroke-width:3.12px;stroke-dashoffset:29.7833385;stroke-dasharray:29.7833385}.mdc-checkbox__mixedmark{width:100%;height:0;transform:scaleX(0) rotate(0deg);border-width:1px;border-style:solid;opacity:0;transition:opacity 90ms cubic-bezier(0.4, 0, 0.6, 1),transform 90ms cubic-bezier(0.4, 0, 0.6, 1);border-color:var(--mdc-checkbox-selected-checkmark-color, var(--mat-app-on-primary))}.cdk-high-contrast-active .mdc-checkbox__mixedmark{margin:0 1px}.mdc-checkbox--disabled .mdc-checkbox__mixedmark,.mdc-checkbox--disabled.mat-mdc-checkbox-disabled-interactive .mdc-checkbox__mixedmark{border-color:var(--mdc-checkbox-disabled-selected-checkmark-color, var(--mat-app-surface))}.mdc-checkbox--anim-unchecked-checked .mdc-checkbox__background,.mdc-checkbox--anim-unchecked-indeterminate .mdc-checkbox__background,.mdc-checkbox--anim-checked-unchecked .mdc-checkbox__background,.mdc-checkbox--anim-indeterminate-unchecked .mdc-checkbox__background{animation-duration:180ms;animation-timing-function:linear}.mdc-checkbox--anim-unchecked-checked .mdc-checkbox__checkmark-path{animation:mdc-checkbox-unchecked-checked-checkmark-path 180ms linear;transition:none}.mdc-checkbox--anim-unchecked-indeterminate .mdc-checkbox__mixedmark{animation:mdc-checkbox-unchecked-indeterminate-mixedmark 90ms linear;transition:none}.mdc-checkbox--anim-checked-unchecked .mdc-checkbox__checkmark-path{animation:mdc-checkbox-checked-unchecked-checkmark-path 90ms linear;transition:none}.mdc-checkbox--anim-checked-indeterminate .mdc-checkbox__checkmark{animation:mdc-checkbox-checked-indeterminate-checkmark 90ms linear;transition:none}.mdc-checkbox--anim-checked-indeterminate .mdc-checkbox__mixedmark{animation:mdc-checkbox-checked-indeterminate-mixedmark 90ms linear;transition:none}.mdc-checkbox--anim-indeterminate-checked .mdc-checkbox__checkmark{animation:mdc-checkbox-indeterminate-checked-checkmark 500ms linear;transition:none}.mdc-checkbox--anim-indeterminate-checked .mdc-checkbox__mixedmark{animation:mdc-checkbox-indeterminate-checked-mixedmark 500ms linear;transition:none}.mdc-checkbox--anim-indeterminate-unchecked .mdc-checkbox__mixedmark{animation:mdc-checkbox-indeterminate-unchecked-mixedmark 300ms linear;transition:none}.mdc-checkbox__native-control:checked~.mdc-checkbox__background,.mdc-checkbox__native-control:indeterminate~.mdc-checkbox__background{transition:border-color 90ms cubic-bezier(0, 0, 0.2, 1),background-color 90ms cubic-bezier(0, 0, 0.2, 1)}.mdc-checkbox__native-control:checked~.mdc-checkbox__background .mdc-checkbox__checkmark-path,.mdc-checkbox__native-control:indeterminate~.mdc-checkbox__background .mdc-checkbox__checkmark-path{stroke-dashoffset:0}.mdc-checkbox__native-control:checked~.mdc-checkbox__background .mdc-checkbox__checkmark{transition:opacity 180ms cubic-bezier(0, 0, 0.2, 1),transform 180ms cubic-bezier(0, 0, 0.2, 1);opacity:1}.mdc-checkbox__native-control:checked~.mdc-checkbox__background .mdc-checkbox__mixedmark{transform:scaleX(1) rotate(-45deg)}.mdc-checkbox__native-control:indeterminate~.mdc-checkbox__background .mdc-checkbox__checkmark{transform:rotate(45deg);opacity:0;transition:opacity 90ms cubic-bezier(0.4, 0, 0.6, 1),transform 90ms cubic-bezier(0.4, 0, 0.6, 1)}.mdc-checkbox__native-control:indeterminate~.mdc-checkbox__background .mdc-checkbox__mixedmark{transform:scaleX(1) rotate(0deg);opacity:1}@keyframes mdc-checkbox-unchecked-checked-checkmark-path{0%,50%{stroke-dashoffset:29.7833385}50%{animation-timing-function:cubic-bezier(0, 0, 0.2, 1)}100%{stroke-dashoffset:0}}@keyframes mdc-checkbox-unchecked-indeterminate-mixedmark{0%,68.2%{transform:scaleX(0)}68.2%{animation-timing-function:cubic-bezier(0, 0, 0, 1)}100%{transform:scaleX(1)}}@keyframes mdc-checkbox-checked-unchecked-checkmark-path{from{animation-timing-function:cubic-bezier(0.4, 0, 1, 1);opacity:1;stroke-dashoffset:0}to{opacity:0;stroke-dashoffset:-29.7833385}}@keyframes mdc-checkbox-checked-indeterminate-checkmark{from{animation-timing-function:cubic-bezier(0, 0, 0.2, 1);transform:rotate(0deg);opacity:1}to{transform:rotate(45deg);opacity:0}}@keyframes mdc-checkbox-indeterminate-checked-checkmark{from{animation-timing-function:cubic-bezier(0.14, 0, 0, 1);transform:rotate(45deg);opacity:0}to{transform:rotate(360deg);opacity:1}}@keyframes mdc-checkbox-checked-indeterminate-mixedmark{from{animation-timing-function:cubic-bezier(0, 0, 0.2, 1);transform:rotate(-45deg);opacity:0}to{transform:rotate(0deg);opacity:1}}@keyframes mdc-checkbox-indeterminate-checked-mixedmark{from{animation-timing-function:cubic-bezier(0.14, 0, 0, 1);transform:rotate(0deg);opacity:1}to{transform:rotate(315deg);opacity:0}}@keyframes mdc-checkbox-indeterminate-unchecked-mixedmark{0%{animation-timing-function:linear;transform:scaleX(1);opacity:1}32.8%,100%{transform:scaleX(0);opacity:0}}.mat-mdc-checkbox{display:inline-block;position:relative;-webkit-tap-highlight-color:rgba(0,0,0,0)}.mat-mdc-checkbox._mat-animation-noopable .mdc-checkbox *,.mat-mdc-checkbox._mat-animation-noopable .mdc-checkbox *::before{transition:none !important;animation:none !important}.mat-mdc-checkbox label{cursor:pointer}.mat-mdc-checkbox .mat-internal-form-field{color:var(--mat-checkbox-label-text-color, var(--mat-app-on-surface));font-family:var(--mat-checkbox-label-text-font, var(--mat-app-body-medium-font));line-height:var(--mat-checkbox-label-text-line-height, var(--mat-app-body-medium-line-height));font-size:var(--mat-checkbox-label-text-size, var(--mat-app-body-medium-size));letter-spacing:var(--mat-checkbox-label-text-tracking, var(--mat-app-body-medium-tracking));font-weight:var(--mat-checkbox-label-text-weight, var(--mat-app-body-medium-weight))}.mat-mdc-checkbox.mat-mdc-checkbox-disabled.mat-mdc-checkbox-disabled-interactive{pointer-events:auto}.mat-mdc-checkbox.mat-mdc-checkbox-disabled.mat-mdc-checkbox-disabled-interactive input{cursor:default}.mat-mdc-checkbox.mat-mdc-checkbox-disabled label{cursor:default;color:var(--mat-checkbox-disabled-label-color)}.mat-mdc-checkbox label:empty{display:none}.mat-mdc-checkbox .mdc-checkbox__ripple{opacity:0}.mat-mdc-checkbox-ripple,.mdc-checkbox__ripple{top:0;left:0;right:0;bottom:0;position:absolute;border-radius:50%;pointer-events:none}.mat-mdc-checkbox-ripple:not(:empty),.mdc-checkbox__ripple:not(:empty){transform:translateZ(0)}.mat-mdc-checkbox-ripple .mat-ripple-element{opacity:.1}.mat-mdc-checkbox-touch-target{position:absolute;top:50%;left:50%;height:48px;width:48px;transform:translate(-50%, -50%);display:var(--mat-checkbox-touch-target-display)}.mat-mdc-checkbox-ripple::before{border-radius:50%}.mdc-checkbox__native-control:focus~.mat-mdc-focus-indicator::before{content:""}']
        }]
    }], () => [{
        type: ElementRef
    }, {
        type: ChangeDetectorRef
    }, {
        type: NgZone
    }, {
        type: void 0,
        decorators: [{
            type: Attribute,
            args: ["tabindex"]
        }]
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
            args: [MAT_CHECKBOX_DEFAULT_OPTIONS]
        }]
    }], {
        ariaLabel: [{
            type: Input,
            args: ["aria-label"]
        }],
        ariaLabelledby: [{
            type: Input,
            args: ["aria-labelledby"]
        }],
        ariaDescribedby: [{
            type: Input,
            args: ["aria-describedby"]
        }],
        id: [{
            type: Input
        }],
        required: [{
            type: Input,
            args: [{
                transform: booleanAttribute
            }]
        }],
        labelPosition: [{
            type: Input
        }],
        name: [{
            type: Input
        }],
        change: [{
            type: Output
        }],
        indeterminateChange: [{
            type: Output
        }],
        value: [{
            type: Input
        }],
        disableRipple: [{
            type: Input,
            args: [{
                transform: booleanAttribute
            }]
        }],
        _inputElement: [{
            type: ViewChild,
            args: ["input"]
        }],
        _labelElement: [{
            type: ViewChild,
            args: ["label"]
        }],
        tabIndex: [{
            type: Input,
            args: [{
                transform: (value) => value == null ? void 0 : numberAttribute(value)
            }]
        }],
        color: [{
            type: Input
        }],
        disabledInteractive: [{
            type: Input,
            args: [{
                transform: booleanAttribute
            }]
        }],
        ripple: [{
            type: ViewChild,
            args: [MatRipple]
        }],
        checked: [{
            type: Input,
            args: [{
                transform: booleanAttribute
            }]
        }],
        disabled: [{
            type: Input,
            args: [{
                transform: booleanAttribute
            }]
        }],
        indeterminate: [{
            type: Input,
            args: [{
                transform: booleanAttribute
            }]
        }]
    });
})();
var MAT_CHECKBOX_REQUIRED_VALIDATOR = {
    provide: NG_VALIDATORS,
    useExisting: forwardRef(() => MatCheckboxRequiredValidator),
    multi: true
};
var MatCheckboxRequiredValidator = class _MatCheckboxRequiredValidator extends CheckboxRequiredValidator {
    static {
        this.\u0275fac = /* @__PURE__ */ (() => {
            let \u0275MatCheckboxRequiredValidator_BaseFactory;
            return function MatCheckboxRequiredValidator_Factory(__ngFactoryType__) {
                return (\u0275MatCheckboxRequiredValidator_BaseFactory || (\u0275MatCheckboxRequiredValidator_BaseFactory = \u0275\u0275getInheritedFactory(_MatCheckboxRequiredValidator)))(__ngFactoryType__ || _MatCheckboxRequiredValidator);
            };
        })();
    }
    static {
        this.\u0275dir = /* @__PURE__ */ \u0275\u0275defineDirective({
            type: _MatCheckboxRequiredValidator,
            selectors: [["mat-checkbox", "required", "", "formControlName", ""], ["mat-checkbox", "required", "", "formControl", ""], ["mat-checkbox", "required", "", "ngModel", ""]],
            standalone: true,
            features: [\u0275\u0275ProvidersFeature([MAT_CHECKBOX_REQUIRED_VALIDATOR]), \u0275\u0275InheritDefinitionFeature]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && setClassMetadata(MatCheckboxRequiredValidator, [{
        type: Directive,
        args: [{
            selector: `mat-checkbox[required][formControlName],
             mat-checkbox[required][formControl], mat-checkbox[required][ngModel]`,
            providers: [MAT_CHECKBOX_REQUIRED_VALIDATOR],
            standalone: true
        }]
    }], null, null);
})();
var _MatCheckboxRequiredValidatorModule = class __MatCheckboxRequiredValidatorModule {
    static {
        this.\u0275fac = function _MatCheckboxRequiredValidatorModule_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || __MatCheckboxRequiredValidatorModule)();
        };
    }
    static {
        this.\u0275mod = /* @__PURE__ */ \u0275\u0275defineNgModule({
            type: __MatCheckboxRequiredValidatorModule
        });
    }
    static {
        this.\u0275inj = /* @__PURE__ */ \u0275\u0275defineInjector({});
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && setClassMetadata(_MatCheckboxRequiredValidatorModule, [{
        type: NgModule,
        args: [{
            imports: [MatCheckboxRequiredValidator],
            exports: [MatCheckboxRequiredValidator]
        }]
    }], null, null);
})();
var MatCheckboxModule = class _MatCheckboxModule {
    static {
        this.\u0275fac = function MatCheckboxModule_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _MatCheckboxModule)();
        };
    }
    static {
        this.\u0275mod = /* @__PURE__ */ \u0275\u0275defineNgModule({
            type: _MatCheckboxModule
        });
    }
    static {
        this.\u0275inj = /* @__PURE__ */ \u0275\u0275defineInjector({
            imports: [MatCheckbox, MatCommonModule, MatCommonModule]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && setClassMetadata(MatCheckboxModule, [{
        type: NgModule,
        args: [{
            imports: [MatCheckbox, MatCommonModule],
            exports: [MatCheckbox, MatCommonModule]
        }]
    }], null, null);
})();

// src/app/services/module.service.ts
var ModuleService = class _ModuleService {
    constructor(http, snackBar) {
        this.http = http;
        this.snackBar = snackBar;
        this.managerConfig = new ManagerConfig();
        this.url = environment.gatewayEndpoint + "/";
    }

    /**
     * @brief Returns the available modules names
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     */
    getModuleList() {
        let headers = this.managerConfig.managerHttpOptions.headers.set("x-awsmock-target", "module").set("x-awsmock-action", "list-modules");
        return this.http.get(this.url, {headers}).pipe(catchError(this.handleError));
    }

    /**
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     */
    exportInfrastructure(moduleList, includeObjects, prettyPrint) {
        let body = {
            prettyPrint,
            includeObjects,
            modules: moduleList
        };
        let headers = this.managerConfig.managerHttpOptions.headers.set("x-awsmock-target", "module").set("x-awsmock-action", "export");
        return this.http.post(this.url, body, {headers}).pipe(catchError(this.handleError));
    }

    /**
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     */
    importInfrastructure(body) {
        let headers = this.managerConfig.managerHttpOptions.headers.set("x-awsmock-target", "module").set("x-awsmock-action", "import");
        return this.http.post(this.url, body, {headers}).pipe(catchError(this.handleError));
    }

    cleanInfrastructure(body) {
        let headers = this.managerConfig.managerHttpOptions.headers.set("x-awsmock-target", "module").set("x-awsmock-action", "clean-objects");
        return this.http.post(this.url, body, {headers}).pipe(catchError(this.handleError));
    }

    eraseInfrastructure(body) {
        let headers = this.managerConfig.managerHttpOptions.headers.set("x-awsmock-target", "module").set("x-awsmock-action", "erase-infrastructure");
        return this.http.post(this.url, body, {headers}).pipe(catchError(this.handleError));
    }

    getConfig() {
        let headers = this.managerConfig.managerHttpOptions.headers.set("x-awsmock-target", "module").set("x-awsmock-action", "get-config");
        return this.http.get(this.url, {headers}).pipe(catchError(this.handleError));
    }

    handleError(error) {
        if (error.status === 0) {
            console.error("An error occurred:", error.error);
            this.snackBar.open("Network error, message: " + error.error, "X", {duration: 5e3, panelClass: "error"});
        } else {
            console.error(`Backend returned code ${error.status}, body was: `, error.error);
            this.snackBar.open("Backend return code: " + error.status + ", message: " + error.error, "X", {duration: 5e3, panelClass: "error"});
        }
        return throwError(() => new Error("Something bad happened; please try again later."));
    }

    static {
        this.\u0275fac = function ModuleService_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _ModuleService)(\u0275\u0275inject(HttpClient), \u0275\u0275inject(MatSnackBar));
        };
    }
    static {
        this.\u0275prov = /* @__PURE__ */ \u0275\u0275defineInjectable({token: _ModuleService, factory: _ModuleService.\u0275fac});
    }
};

// src/app/modules/infrastructure/selection/module-selection.component.ts
function ModuleSelectionComponentDialog_mat_list_item_14_Template(rf, ctx) {
    if (rf & 1) {
        const _r1 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "mat-list-item")(1, "mat-checkbox", 10);
        \u0275\u0275twoWayListener("ngModelChange", function ModuleSelectionComponentDialog_mat_list_item_14_Template_mat_checkbox_ngModelChange_1_listener($event) {
            const module_r2 = \u0275\u0275restoreView(_r1).$implicit;
            \u0275\u0275twoWayBindingSet(module_r2.selected, $event) || (module_r2.selected = $event);
            return \u0275\u0275resetView($event);
        });
        \u0275\u0275text(2);
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const module_r2 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275twoWayProperty("ngModel", module_r2.selected);
        \u0275\u0275advance();
        \u0275\u0275textInterpolate(module_r2.displayName);
    }
}

function ModuleSelectionComponentDialog_mat_list_item_18_Template(rf, ctx) {
    if (rf & 1) {
        const _r3 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "mat-list-item")(1, "mat-checkbox", 10);
        \u0275\u0275twoWayListener("ngModelChange", function ModuleSelectionComponentDialog_mat_list_item_18_Template_mat_checkbox_ngModelChange_1_listener($event) {
            const module_r4 = \u0275\u0275restoreView(_r3).$implicit;
            \u0275\u0275twoWayBindingSet(module_r4.selected, $event) || (module_r4.selected = $event);
            return \u0275\u0275resetView($event);
        });
        \u0275\u0275text(2);
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const module_r4 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275twoWayProperty("ngModel", module_r4.selected);
        \u0275\u0275advance();
        \u0275\u0275textInterpolate(module_r4.displayName);
    }
}

function ModuleSelectionComponentDialog_mat_list_item_22_Template(rf, ctx) {
    if (rf & 1) {
        const _r5 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "mat-list-item")(1, "mat-checkbox", 10);
        \u0275\u0275twoWayListener("ngModelChange", function ModuleSelectionComponentDialog_mat_list_item_22_Template_mat_checkbox_ngModelChange_1_listener($event) {
            \u0275\u0275restoreView(_r5);
            const ctx_r5 = \u0275\u0275nextContext();
            \u0275\u0275twoWayBindingSet(ctx_r5.onlyObjects, $event) || (ctx_r5.onlyObjects = $event);
            return \u0275\u0275resetView($event);
        });
        \u0275\u0275text(2, "Only Objects");
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const ctx_r5 = \u0275\u0275nextContext();
        \u0275\u0275advance();
        \u0275\u0275twoWayProperty("ngModel", ctx_r5.onlyObjects);
    }
}

function ModuleSelectionComponentDialog_mat_list_item_23_Template(rf, ctx) {
    if (rf & 1) {
        const _r7 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "mat-list-item")(1, "mat-checkbox", 4);
        \u0275\u0275listener("click", function ModuleSelectionComponentDialog_mat_list_item_23_Template_mat_checkbox_click_1_listener() {
            \u0275\u0275restoreView(_r7);
            const ctx_r5 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r5.includeObjectsSelected());
        });
        \u0275\u0275twoWayListener("ngModelChange", function ModuleSelectionComponentDialog_mat_list_item_23_Template_mat_checkbox_ngModelChange_1_listener($event) {
            \u0275\u0275restoreView(_r7);
            const ctx_r5 = \u0275\u0275nextContext();
            \u0275\u0275twoWayBindingSet(ctx_r5.includeObjects, $event) || (ctx_r5.includeObjects = $event);
            return \u0275\u0275resetView($event);
        });
        \u0275\u0275text(2, "Include Objects");
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const ctx_r5 = \u0275\u0275nextContext();
        \u0275\u0275advance();
        \u0275\u0275twoWayProperty("ngModel", ctx_r5.includeObjects);
    }
}

function ModuleSelectionComponentDialog_mat_list_item_26_Template(rf, ctx) {
    if (rf & 1) {
        const _r8 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "mat-list-item")(1, "mat-checkbox", 10);
        \u0275\u0275twoWayListener("ngModelChange", function ModuleSelectionComponentDialog_mat_list_item_26_Template_mat_checkbox_ngModelChange_1_listener($event) {
            \u0275\u0275restoreView(_r8);
            const ctx_r5 = \u0275\u0275nextContext();
            \u0275\u0275twoWayBindingSet(ctx_r5.prettyPrint, $event) || (ctx_r5.prettyPrint = $event);
            return \u0275\u0275resetView($event);
        });
        \u0275\u0275text(2, "Pretty Print");
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const ctx_r5 = \u0275\u0275nextContext();
        \u0275\u0275advance();
        \u0275\u0275twoWayProperty("ngModel", ctx_r5.prettyPrint);
    }
}

var AllModules = {
    modules: [
        {name: "s3", displayName: "S3", selected: false},
        {name: "sqs", displayName: "SQS", selected: false},
        {name: "sns", displayName: "SNS", selected: false},
        {name: "kms", displayName: "KMS", selected: false},
        {name: "ssm", displayName: "SSM", selected: false},
        {name: "secretsmanager", displayName: "SecretsManager", selected: false},
        {name: "cognito", displayName: "Cognito", selected: false},
        {name: "dynamodb", displayName: "DynamoDB", selected: false},
        {name: "lambda", displayName: "Lambda", selected: false},
        {name: "transfer", displayName: "Transfer", selected: false}
    ]
};
var ModuleSelectionComponentDialog = class _ModuleSelectionComponentDialog {
    constructor(dialogRef, data, snackBar) {
        this.dialogRef = dialogRef;
        this.data = data;
        this.snackBar = snackBar;
        this.title = "";
        this.allSelected = true;
        this.includeObjects = false;
        this.includeObjectsVisible = false;
        this.onlyObjects = true;
        this.onlyObjectsVisible = false;
        this.prettyPrint = true;
        this.prettyPrintVisible = false;
        this.mode = "export";
        this.allModules = AllModules.modules;
        this.title = data.title;
        this.mode = data.mode;
        if (this.mode === "export") {
            this.includeObjectsVisible = true;
            this.prettyPrintVisible = true;
        } else if (this.mode === "clean") {
            this.onlyObjects = true;
            this.onlyObjectsVisible = true;
        } else if (this.mode === "erase") {
            this.onlyObjectsVisible = false;
        }
        this.setAll();
    }

    ngOnInit() {
    }

    setAll() {
        this.allModules?.forEach((item) => {
            item.selected = this.allSelected;
        });
    }

    includeObjectsSelected() {
        this.snackBar.open("The resulting file can be very big! Files bigger 10MB will be rejected! Use the command line client instead.", "Done", {duration: 3e3});
    }

    close() {
        this.dialogRef.close(false);
    }

    save() {
        this.dialogRef.close({modules: this.allModules, onlyObjects: this.onlyObjects, includeObjects: this.includeObjects, prettyPrint: this.prettyPrint});
    }

    static {
        this.\u0275fac = function ModuleSelectionComponentDialog_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _ModuleSelectionComponentDialog)(\u0275\u0275directiveInject(MatDialogRef), \u0275\u0275directiveInject(MAT_DIALOG_DATA), \u0275\u0275directiveInject(MatSnackBar));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _ModuleSelectionComponentDialog,
            selectors: [["module-selection-component"]],
            standalone: true,
            features: [\u0275\u0275ProvidersFeature([ModuleService]), \u0275\u0275StandaloneFeature],
            decls: 32,
            vars: 15,
            consts: [["cdkDrag", "", "cdkDragHandle", "", "cdkDragRootElement", ".cdk-overlay-pane", "mat-dialog-title", ""], [1, "mat-typography"], [1, "container"], [1, "item"], [3, "click", "ngModelChange", "ngModel"], [4, "ngFor", "ngForOf"], [4, "ngIf"], ["align", "end"], ["mat-button", "", "mat-dialog-close", "", 3, "click"], ["cdkFocusInitial", "", "mat-button", "", 3, "click"], [3, "ngModelChange", "ngModel"]],
            template: function ModuleSelectionComponentDialog_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "h2", 0);
                    \u0275\u0275text(1);
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(2, "mat-dialog-content", 1)(3, "h6");
                    \u0275\u0275text(4, "Select modules:");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(5, "div", 2)(6, "div", 3)(7, "mat-list")(8, "mat-list-item")(9, "mat-checkbox", 4);
                    \u0275\u0275listener("click", function ModuleSelectionComponentDialog_Template_mat_checkbox_click_9_listener() {
                        return ctx.setAll();
                    });
                    \u0275\u0275twoWayListener("ngModelChange", function ModuleSelectionComponentDialog_Template_mat_checkbox_ngModelChange_9_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.allSelected, $event) || (ctx.allSelected = $event);
                        return $event;
                    });
                    \u0275\u0275text(10, "All");
                    \u0275\u0275elementEnd()()()();
                    \u0275\u0275element(11, "div", 3);
                    \u0275\u0275elementStart(12, "div", 3)(13, "mat-list");
                    \u0275\u0275template(14, ModuleSelectionComponentDialog_mat_list_item_14_Template, 3, 2, "mat-list-item", 5);
                    \u0275\u0275pipe(15, "slice");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(16, "div", 3)(17, "mat-list");
                    \u0275\u0275template(18, ModuleSelectionComponentDialog_mat_list_item_18_Template, 3, 2, "mat-list-item", 5);
                    \u0275\u0275pipe(19, "slice");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(20, "div", 3)(21, "mat-list");
                    \u0275\u0275template(22, ModuleSelectionComponentDialog_mat_list_item_22_Template, 3, 1, "mat-list-item", 6)(23, ModuleSelectionComponentDialog_mat_list_item_23_Template, 3, 1, "mat-list-item", 6);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(24, "div", 3)(25, "mat-list");
                    \u0275\u0275template(26, ModuleSelectionComponentDialog_mat_list_item_26_Template, 3, 1, "mat-list-item", 6);
                    \u0275\u0275elementEnd()()()();
                    \u0275\u0275elementStart(27, "mat-dialog-actions", 7)(28, "button", 8);
                    \u0275\u0275listener("click", function ModuleSelectionComponentDialog_Template_button_click_28_listener() {
                        return ctx.close();
                    });
                    \u0275\u0275text(29, "Cancel");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(30, "button", 9);
                    \u0275\u0275listener("click", function ModuleSelectionComponentDialog_Template_button_click_30_listener() {
                        return ctx.save();
                    });
                    \u0275\u0275text(31, "Ok");
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    \u0275\u0275advance();
                    \u0275\u0275textInterpolate(ctx.title);
                    \u0275\u0275advance(8);
                    \u0275\u0275twoWayProperty("ngModel", ctx.allSelected);
                    \u0275\u0275advance(5);
                    \u0275\u0275property("ngForOf", \u0275\u0275pipeBind3(15, 7, ctx.allModules, 0, 5));
                    \u0275\u0275advance(4);
                    \u0275\u0275property("ngForOf", \u0275\u0275pipeBind3(19, 11, ctx.allModules, 5, 10));
                    \u0275\u0275advance(4);
                    \u0275\u0275property("ngIf", ctx.onlyObjectsVisible);
                    \u0275\u0275advance();
                    \u0275\u0275property("ngIf", ctx.includeObjectsVisible);
                    \u0275\u0275advance(3);
                    \u0275\u0275property("ngIf", ctx.prettyPrintVisible);
                }
            },
            dependencies: [
                MatButton,
                NgIf,
                NgForOf,
                MatList,
                MatListItem,
                MatDialogActions,
                MatDialogClose,
                MatDialogContent,
                MatDialogTitle,
                MatCheckbox,
                MatCheckboxModule,
                SlicePipe,
                FormsModule,
                NgControlStatus,
                NgModel,
                CdkDrag,
                CdkDragHandle
            ],
            styles: ["\n\n.container[_ngcontent-%COMP%] {\n  display: grid;\n  grid-template-columns: repeat(2, 3fr);\n  gap: 1rem;\n  width: 30ch;\n}\n.item[_ngcontent-%COMP%] {\n  padding: 1rem;\n}\n/*# sourceMappingURL=module-selection.component.css.map */"],
            changeDetection: 0
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(ModuleSelectionComponentDialog, {
        className: "ModuleSelectionComponentDialog",
        filePath: "src/app/modules/infrastructure/selection/module-selection.component.ts",
        lineNumber: 73
    });
})();

// src/app/modules/infrastructure/export/file-export/file-export.component.ts
var import_file_saver = __toESM(require_FileSaver_min());
var FileExportComponent = class _FileExportComponent {
    constructor(snackBar, dialogRef, data) {
        this.snackBar = snackBar;
        this.dialogRef = dialogRef;
        this.data = data;
        this.body = "";
        this.fileName = "";
        this.body = data;
    }

    ngOnInit() {
    }

    // Method to handle file upload
    download() {
        if (this.fileName) {
            const blob = new Blob([this.body], {type: "application/json"});
            (0, import_file_saver.saveAs)(blob, this.fileName);
            this.snackBar.open("Infrastructure saved to local file: " + this.fileName, "Done", {duration: 5e3});
            this.dialogRef.close(true);
        }
    }

    static {
        this.\u0275fac = function FileExportComponent_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _FileExportComponent)(\u0275\u0275directiveInject(MatSnackBar), \u0275\u0275directiveInject(MatDialogRef), \u0275\u0275directiveInject(MAT_DIALOG_DATA));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _FileExportComponent,
            selectors: [["export-file-download"]],
            standalone: true,
            features: [\u0275\u0275ProvidersFeature([]), \u0275\u0275StandaloneFeature],
            decls: 12,
            vars: 1,
            consts: [["mat-dialog-title", ""], [1, "mat-typography", 2, "width", "500px", "height", "200px"], [2, "width", "100%"], ["matInput", "", "value", "", 3, "ngModelChange", "ngModel"], ["align", "end"], ["mat-button", "", "mat-dialog-close", ""], ["cdkFocusInitial", "", "mat-button", "", 3, "click"]],
            template: function FileExportComponent_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "h2", 0);
                    \u0275\u0275text(1, "Upload Object");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(2, "mat-dialog-content", 1)(3, "mat-form-field", 2)(4, "mat-label");
                    \u0275\u0275text(5, "File name");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(6, "input", 3);
                    \u0275\u0275twoWayListener("ngModelChange", function FileExportComponent_Template_input_ngModelChange_6_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.fileName, $event) || (ctx.fileName = $event);
                        return $event;
                    });
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(7, "mat-dialog-actions", 4)(8, "button", 5);
                    \u0275\u0275text(9, "Cancel");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(10, "button", 6);
                    \u0275\u0275listener("click", function FileExportComponent_Template_button_click_10_listener() {
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
            styles: ["\n\n.queue-table[_ngcontent-%COMP%] {\n  width: 100%;\n  height: 100%;\n}\n[_nghost-%COMP%] {\n  position: relative;\n  width: 100%;\n  height: 30%;\n  margin-top: 0;\n  padding-bottom: 33%;\n}\n.head-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  justify-content: flex-end;\n}\n.footer-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  width: 50%;\n  justify-content: flex-end;\n}\n.footer[_ngcontent-%COMP%] {\n  display: flex;\n  width: 50%;\n  font-size: x-small;\n  color: black;\n}\n/*# sourceMappingURL=file-export.component.css.map */"]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(FileExportComponent, {
        className: "FileExportComponent",
        filePath: "src/app/modules/infrastructure/export/file-export/file-export.component.ts",
        lineNumber: 68
    });
})();

// src/app/modules/infrastructure/export/export-infrastructure.component.ts
var ExportInfrastructureComponentDialog = class _ExportInfrastructureComponentDialog {
    constructor(dialogRef, data, dialog) {
        this.dialogRef = dialogRef;
        this.data = data;
        this.dialog = dialog;
        this.body = JSON.stringify(data, null, 4);
    }

    ngOnInit() {
    }

    ngOnDestroy() {
    }

    fileExport() {
        const dialogConfig = new MatDialogConfig();
        dialogConfig.disableClose = true;
        dialogConfig.autoFocus = true;
        dialogConfig.data = this.body;
        this.dialog.open(FileExportComponent, dialogConfig).afterClosed().subscribe((result) => {
            if (result) {
                this.dialogRef.close(true);
            }
        });
    }

    static {
        this.\u0275fac = function ExportInfrastructureComponentDialog_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _ExportInfrastructureComponentDialog)(\u0275\u0275directiveInject(MatDialogRef), \u0275\u0275directiveInject(MAT_DIALOG_DATA), \u0275\u0275directiveInject(MatDialog));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _ExportInfrastructureComponentDialog,
            selectors: [["export-infrastructure-component"]],
            standalone: true,
            features: [\u0275\u0275ProvidersFeature([]), \u0275\u0275StandaloneFeature],
            decls: 12,
            vars: 1,
            consts: [["cdkDrag", "", "cdkDragHandle", "", "cdkDragRootElement", ".cdk-overlay-pane", "mat-dialog-title", ""], [1, "mat-typography"], [2, "width", "100%", "height", "100%"], ["cdkAutosizeMinRows", "70", "cdkTextareaAutosize", "", "matInput", "", "placeholder", "Infrastructure", "readonly", "", 2, "width", "100%", "height", "100%", 3, "ngModelChange", "ngModel"], ["align", "end"], ["mat-button", "", "mat-dialog-close", ""], ["cdkFocusInitial", "", "mat-button", "", 3, "click"]],
            template: function ExportInfrastructureComponentDialog_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "h2", 0);
                    \u0275\u0275text(1, "Export Infrastructure");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(2, "mat-dialog-content", 1)(3, "mat-form-field", 2)(4, "mat-label");
                    \u0275\u0275text(5, "Infrastructure:");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(6, "textarea", 3);
                    \u0275\u0275twoWayListener("ngModelChange", function ExportInfrastructureComponentDialog_Template_textarea_ngModelChange_6_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.body, $event) || (ctx.body = $event);
                        return $event;
                    });
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(7, "mat-dialog-actions", 4)(8, "button", 5);
                    \u0275\u0275text(9, "Cancel");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(10, "button", 6);
                    \u0275\u0275listener("click", function ExportInfrastructureComponentDialog_Template_button_click_10_listener() {
                        return ctx.fileExport();
                    });
                    \u0275\u0275text(11, "Save to file");
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    \u0275\u0275advance(6);
                    \u0275\u0275twoWayProperty("ngModel", ctx.body);
                }
            },
            dependencies: [
                MatButton,
                FormsModule,
                DefaultValueAccessor,
                NgControlStatus,
                NgModel,
                MatDialogActions,
                MatDialogClose,
                MatDialogContent,
                MatDialogTitle,
                MatFormField,
                MatInput,
                MatLabel,
                CdkDrag,
                CdkDragHandle,
                CdkTextareaAutosize
            ],
            styles: ["\n\n.full-screen-modal[_ngcontent-%COMP%]   .mat-dialog-container[_ngcontent-%COMP%] {\n  max-width: none;\n}\n/*# sourceMappingURL=export-infrastructure.component.css.map */"]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(ExportInfrastructureComponentDialog, {
        className: "ExportInfrastructureComponentDialog",
        filePath: "src/app/modules/infrastructure/export/export-infrastructure.component.ts",
        lineNumber: 59
    });
})();

// src/app/modules/infrastructure/import/import-infrastructure.component.ts
var ImportInfrastructureComponentDialog = class _ImportInfrastructureComponentDialog {
    constructor(dialogRef, data, snackBar, dialog, moduleService) {
        this.dialogRef = dialogRef;
        this.data = data;
        this.snackBar = snackBar;
        this.dialog = dialog;
        this.moduleService = moduleService;
        this.body = "";
    }

    ngOnInit() {
    }

    ngOnDestroy() {
    }

    importInfrastructure() {
        if (this.body === void 0 || this.body.length === 0) {
            this.snackBar.open("Empty infrastructure JSON", "Done", {duration: 5e3});
            return;
        }
        this.moduleService.importInfrastructure(this.body).subscribe(() => {
            this.snackBar.open("Infrastructure imported", "Done", {duration: 5e3});
            this.dialogRef.close(true);
        });
    }

    loadFromFile() {
        const dialogConfig = new MatDialogConfig();
        dialogConfig.disableClose = true;
        dialogConfig.autoFocus = true;
        dialogConfig.data = this.body;
        this.dialog.open(FileImportComponent, dialogConfig).afterClosed().subscribe((result) => {
            if (result) {
                this.body = result;
            }
        });
    }

    close() {
        this.dialogRef.close(false);
    }

    static {
        this.\u0275fac = function ImportInfrastructureComponentDialog_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _ImportInfrastructureComponentDialog)(\u0275\u0275directiveInject(MatDialogRef), \u0275\u0275directiveInject(MAT_DIALOG_DATA), \u0275\u0275directiveInject(MatSnackBar), \u0275\u0275directiveInject(MatDialog), \u0275\u0275directiveInject(ModuleService));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _ImportInfrastructureComponentDialog,
            selectors: [["export-infrastructure-component"]],
            standalone: true,
            features: [\u0275\u0275ProvidersFeature([ModuleService]), \u0275\u0275StandaloneFeature],
            decls: 15,
            vars: 2,
            consts: [["cdkDrag", "", "cdkDragHandle", "", "cdkDragRootElement", ".cdk-overlay-pane", "mat-dialog-title", ""], [1, "mat-typography"], [2, "width", "100%", "height", "100%"], ["cdkAutosizeMinRows", "70", "cdkTextareaAutosize", "", "matInput", "", "placeholder", "Infrastructure", "readonly", "", 2, "width", "100%", "height", "100%", 3, "ngModelChange", "ngModel"], ["align", "end"], ["mat-button", "", "mat-dialog-close", "", 3, "click"], ["mat-button", "", 3, "click"], ["cdkFocusInitial", "", "mat-button", "", 3, "click"]],
            template: function ImportInfrastructureComponentDialog_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "h2", 0);
                    \u0275\u0275text(1, "Import Infrastructure");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(2, "mat-dialog-content", 1)(3, "mat-form-field", 2)(4, "mat-label");
                    \u0275\u0275text(5, "Infrastructure:");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(6, "textarea", 3);
                    \u0275\u0275twoWayListener("ngModelChange", function ImportInfrastructureComponentDialog_Template_textarea_ngModelChange_6_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.body, $event) || (ctx.body = $event);
                        return $event;
                    });
                    \u0275\u0275text(7);
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(8, "mat-dialog-actions", 4)(9, "button", 5);
                    \u0275\u0275listener("click", function ImportInfrastructureComponentDialog_Template_button_click_9_listener() {
                        return ctx.close();
                    });
                    \u0275\u0275text(10, "Cancel");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(11, "button", 6);
                    \u0275\u0275listener("click", function ImportInfrastructureComponentDialog_Template_button_click_11_listener() {
                        return ctx.loadFromFile();
                    });
                    \u0275\u0275text(12, "Load File");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(13, "button", 7);
                    \u0275\u0275listener("click", function ImportInfrastructureComponentDialog_Template_button_click_13_listener() {
                        return ctx.importInfrastructure();
                    });
                    \u0275\u0275text(14, "Import");
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    \u0275\u0275advance(6);
                    \u0275\u0275twoWayProperty("ngModel", ctx.body);
                    \u0275\u0275advance();
                    \u0275\u0275textInterpolate(ctx.body);
                }
            },
            dependencies: [
                MatButton,
                FormsModule,
                DefaultValueAccessor,
                NgControlStatus,
                NgModel,
                MatDialogActions,
                MatDialogClose,
                MatDialogContent,
                MatDialogTitle,
                MatFormField,
                MatInput,
                MatLabel,
                CdkDrag,
                CdkDragHandle,
                CdkTextareaAutosize
            ],
            styles: ["\n\n.full-screen-modal[_ngcontent-%COMP%]   .mat-dialog-container[_ngcontent-%COMP%] {\n  max-width: none;\n}\n/*# sourceMappingURL=import-infrastructure.component.css.map */"]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(ImportInfrastructureComponentDialog, {
        className: "ImportInfrastructureComponentDialog",
        filePath: "src/app/modules/infrastructure/import/import-infrastructure.component.ts",
        lineNumber: 61
    });
})();

// src/app/modules/dashboard/dashboard.component.ts
var DashboardComponent = class _DashboardComponent {
    constructor(snackBar, moduleService, dialog, store) {
        this.snackBar = snackBar;
        this.moduleService = moduleService;
        this.dialog = dialog;
        this.store = store;
        this.lastUpdate = /* @__PURE__ */ new Date();
        this.updateSubscription = interval(6e4).subscribe(() => {
            this.lastUpdate = /* @__PURE__ */ new Date();
            this.cpuChart?.loadCpuChart();
            this.memoryChart?.loadMemoryChart();
            this.gatewayTimeChart?.loadHttpTimeChart();
            this.threadsChart?.loadThreadChart();
        });
    }

    ngOnInit() {
        this.lastUpdate = /* @__PURE__ */ new Date();
        this.cpuChart?.loadCpuChart();
        this.memoryChart?.loadMemoryChart();
        this.gatewayTimeChart?.loadHttpTimeChart();
        this.threadsChart?.loadThreadChart();
    }

    ngOnDestroy() {
        this.updateSubscription?.unsubscribe();
    }

    exportInfrastructure() {
        const moduleSelectedDialogConfig = new MatDialogConfig();
        moduleSelectedDialogConfig.disableClose = true;
        moduleSelectedDialogConfig.autoFocus = true;
        moduleSelectedDialogConfig.maxWidth = "100vw";
        moduleSelectedDialogConfig.maxHeight = "100vh";
        moduleSelectedDialogConfig.panelClass = "full-screen-modal";
        moduleSelectedDialogConfig.width = "20%";
        moduleSelectedDialogConfig.minWidth = "280px";
        moduleSelectedDialogConfig.data = {title: "Export modules", mode: "export"};
        this.dialog.open(ModuleSelectionComponentDialog, moduleSelectedDialogConfig).afterClosed().subscribe((result) => {
            if (result) {
                const moduleList = result.modules.filter((ele) => {
                    return ele.selected;
                }).map((ele) => ele.name);
                const includeObjects = result.includeObjects;
                const prettyPrint = result.prettyPrint;
                this.moduleService.exportInfrastructure(moduleList, includeObjects, prettyPrint).subscribe((data) => {
                    const exportDialogConfig = new MatDialogConfig();
                    exportDialogConfig.disableClose = true;
                    exportDialogConfig.autoFocus = true;
                    exportDialogConfig.maxWidth = "100vw";
                    exportDialogConfig.maxHeight = "100vh";
                    exportDialogConfig.panelClass = "full-screen-modal";
                    exportDialogConfig.width = "90%";
                    exportDialogConfig.data = data;
                    this.dialog.open(ExportInfrastructureComponentDialog, exportDialogConfig).afterClosed().subscribe((result2) => {
                        if (result2) {
                            console.log(result2);
                        }
                    });
                });
            }
        });
    }

    importInfrastructure() {
        const dialogConfig = new MatDialogConfig();
        dialogConfig.disableClose = true;
        dialogConfig.autoFocus = true;
        dialogConfig.maxWidth = "100vw";
        dialogConfig.maxHeight = "100vh";
        dialogConfig.panelClass = "full-screen-modal";
        dialogConfig.width = "90%";
        this.dialog.open(ImportInfrastructureComponentDialog, dialogConfig).afterClosed().subscribe((result) => {
            if (result) {
                console.log(result);
            }
        });
    }

    cleanInfrastructure() {
        const dialogConfig = new MatDialogConfig();
        dialogConfig.disableClose = true;
        dialogConfig.autoFocus = true;
        dialogConfig.width = "40%";
        dialogConfig.data = {title: "Clean Infrastructure", mode: "clean"};
        this.dialog.open(ModuleSelectionComponentDialog, dialogConfig).afterClosed().subscribe((result) => {
            if (result) {
                const moduleList = result.modules.filter((ele) => {
                    return ele.selected;
                }).map((ele) => ele.name);
                this.moduleService.cleanInfrastructure({modules: moduleList, onlyObjects: result.onlyObjects}).subscribe(() => {
                    this.snackBar.open("Infrastructure cleaned", "Done", {duration: 5e3});
                });
            }
        });
    }

    eraseInfrastructure() {
        const dialogConfig = new MatDialogConfig();
        dialogConfig.disableClose = true;
        dialogConfig.autoFocus = true;
        dialogConfig.width = "40%";
        dialogConfig.data = {title: "Erase Infrastructure", mode: "erase"};
        this.dialog.open(ModuleSelectionComponentDialog, dialogConfig).afterClosed().subscribe((result) => {
            if (result) {
                const moduleList = result.modules.filter((ele) => {
                    return ele.selected;
                }).map((ele) => ele.name);
                this.moduleService.eraseInfrastructure({modules: moduleList, onlyObjects: result.onlyObjects}).subscribe(() => {
                    this.snackBar.open("Infrastructure erased", "Done", {duration: 5e3});
                });
            }
        });
    }

    static {
        this.\u0275fac = function DashboardComponent_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _DashboardComponent)(\u0275\u0275directiveInject(MatSnackBar), \u0275\u0275directiveInject(ModuleService), \u0275\u0275directiveInject(MatDialog), \u0275\u0275directiveInject(Store));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _DashboardComponent,
            selectors: [["dashboard-component"]],
            viewQuery: function DashboardComponent_Query(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275viewQuery(CpuChartComponent, 5);
                    \u0275\u0275viewQuery(MemoryChartComponent, 5);
                    \u0275\u0275viewQuery(GatewayTimeComponent, 5);
                    \u0275\u0275viewQuery(ThreadsChartComponent, 5);
                }
                if (rf & 2) {
                    let _t;
                    \u0275\u0275queryRefresh(_t = \u0275\u0275loadQuery()) && (ctx.cpuChart = _t.first);
                    \u0275\u0275queryRefresh(_t = \u0275\u0275loadQuery()) && (ctx.memoryChart = _t.first);
                    \u0275\u0275queryRefresh(_t = \u0275\u0275loadQuery()) && (ctx.gatewayTimeChart = _t.first);
                    \u0275\u0275queryRefresh(_t = \u0275\u0275loadQuery()) && (ctx.threadsChart = _t.first);
                }
            },
            decls: 61,
            vars: 11,
            consts: [[1, "mat-elevation-z4"], [1, "wrapper"], ["cols", "2", "rowHeight", "200px"], [3, "colspan", "rowspan"], [2, "margin-left", "-10px", "width", "100%", "height", "100%"], [2, "height", "200px"], ["href", "/sqs-queue-list", "mat-list-item", ""], ["href", "/sns-topic-list", "mat-list-item", ""], ["href", "/s3-bucket-list", "mat-list-item", ""], ["href", "/cognito-user-pool-list", "mat-list-item", ""], [2, "margin-left", "-10px", "; width", "100%", "height", "100%"], ["href", "/lambda-function-list", "mat-list-item", ""], ["mat-list-item", "", "matTooltip", "Export infrastructure to local JSON file", 3, "click", "matTooltipShowDelay"], ["mat-list-item", "", "matTooltip", "Import infrastructure from local JSON file", 3, "click", "matTooltipShowDelay"], ["mat-list-item", "", "matTooltip", "Clean infrastructure, removes S3 objects, SQS message, etc.", 3, "click", "matTooltipShowDelay"], ["href", "/sqs-charts", "mat-list-item", ""], ["href", "/sns-charts", "mat-list-item", ""], ["href", "/s3-charts", "mat-list-item", ""], ["href", "/cognito-charts", "mat-list-item", ""], [1, "footer"]],
            template: function DashboardComponent_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "mat-card", 0)(1, "mat-card-content")(2, "div", 1)(3, "mat-card", 0)(4, "mat-card-header")(5, "mat-card-title");
                    \u0275\u0275text(6, "Services");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(7, "mat-card-content")(8, "mat-grid-list", 2)(9, "mat-grid-tile", 3)(10, "div", 4)(11, "mat-nav-list", 5)(12, "a", 6);
                    \u0275\u0275text(13, "Simple Queueing Service");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(14, "a", 7);
                    \u0275\u0275text(15, "Simple Notification Service");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(16, "a", 8);
                    \u0275\u0275text(17, "S3 Storage Service");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(18, "a", 9);
                    \u0275\u0275text(19, "Cognito Service");
                    \u0275\u0275elementEnd()()()();
                    \u0275\u0275elementStart(20, "mat-grid-tile", 3)(21, "div", 10)(22, "mat-nav-list")(23, "a", 11);
                    \u0275\u0275text(24, "Lambdas");
                    \u0275\u0275elementEnd();
                    \u0275\u0275element(25, "a", 11)(26, "a", 11)(27, "a", 11);
                    \u0275\u0275elementEnd()()()()()();
                    \u0275\u0275elementStart(28, "mat-card", 0)(29, "mat-card-header")(30, "mat-card-title");
                    \u0275\u0275text(31, "Import/Export");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(32, "mat-card-content")(33, "mat-nav-list")(34, "a", 12);
                    \u0275\u0275listener("click", function DashboardComponent_Template_a_click_34_listener() {
                        return ctx.exportInfrastructure();
                    });
                    \u0275\u0275text(35, "Export Infrastructure");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(36, "a", 13);
                    \u0275\u0275listener("click", function DashboardComponent_Template_a_click_36_listener() {
                        return ctx.importInfrastructure();
                    });
                    \u0275\u0275text(37, "Import Infrastructure");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(38, "a", 14);
                    \u0275\u0275listener("click", function DashboardComponent_Template_a_click_38_listener() {
                        return ctx.cleanInfrastructure();
                    });
                    \u0275\u0275text(39, "Clean Infrastructure");
                    \u0275\u0275elementEnd()()()();
                    \u0275\u0275elementStart(40, "mat-card", 0)(41, "mat-card-header")(42, "mat-card-title");
                    \u0275\u0275text(43, "Monitoring");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(44, "mat-card-content")(45, "mat-nav-list")(46, "a", 15);
                    \u0275\u0275text(47, "Simple Queueing Service");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(48, "a", 16);
                    \u0275\u0275text(49, "Simple Notification Service");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(50, "a", 17);
                    \u0275\u0275text(51, "S3 Storage Service");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(52, "a", 18);
                    \u0275\u0275text(53, "Cognito Service");
                    \u0275\u0275elementEnd()()()();
                    \u0275\u0275element(54, "cpu-chart-component")(55, "memory-chart-component")(56, "gateway-time-chart-component")(57, "threads-chart-component");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(58, "div", 19);
                    \u0275\u0275text(59);
                    \u0275\u0275pipe(60, "date");
                    \u0275\u0275elementEnd()()();
                }
                if (rf & 2) {
                    \u0275\u0275advance(9);
                    \u0275\u0275property("colspan", 1)("rowspan", 1);
                    \u0275\u0275advance(11);
                    \u0275\u0275property("colspan", 1)("rowspan", 1);
                    \u0275\u0275advance(14);
                    \u0275\u0275property("matTooltipShowDelay", 1e3);
                    \u0275\u0275advance(2);
                    \u0275\u0275property("matTooltipShowDelay", 1e3);
                    \u0275\u0275advance(2);
                    \u0275\u0275property("matTooltipShowDelay", 1e3);
                    \u0275\u0275advance(21);
                    \u0275\u0275textInterpolate1(" Last update: ", \u0275\u0275pipeBind2(60, 8, ctx.lastUpdate, "HH:mm:ss"), " ");
                }
            },
            dependencies: [MatCard, MatCardContent, MatCardHeader, MatCardTitle, MatTooltip, MatNavList, MatListItem, CpuChartComponent, MemoryChartComponent, GatewayTimeComponent, ThreadsChartComponent, MatGridList, MatGridTile, DatePipe],
            styles: ["\n\nbody[_ngcontent-%COMP%] {\n  margin: 40px;\n}\n.wrapper[_ngcontent-%COMP%] {\n  display: grid;\n  grid-template-columns: 1fr 1fr 1fr;\n  grid-gap: 10px;\n  background-color: #fff;\n  color: #444;\n  padding: 10px;\n}\n.box[_ngcontent-%COMP%] {\n  background-color: #444;\n  color: #fff;\n  border-radius: 5px;\n  padding: 20px;\n  height: 400px;\n}\n.container[_ngcontent-%COMP%] {\n  margin: 0 auto;\n  width: 100%;\n  display: flex;\n  align-items: center;\n  justify-content: space-between;\n}\n.flex-container-left[_ngcontent-%COMP%] {\n  display: flex;\n  align-items: flex-start;\n  justify-content: flex-start;\n  height: 100%;\n}\n.flex-container-right[_ngcontent-%COMP%] {\n  display: flex;\n  align-items: flex-start;\n  justify-content: flex-end;\n  height: 100%;\n}\n.flex-item[_ngcontent-%COMP%] {\n  margin: 5px;\n  height: 100%;\n}\n.card-header[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: start;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  justify-content: flex-start;\n}\n.action-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  justify-content: flex-end;\n}\n.full-screen-modal[_ngcontent-%COMP%]   .mat-dialog-container[_ngcontent-%COMP%] {\n  max-width: none;\n}\n.body[_ngcontent-%COMP%] {\n  flex-grow: 1;\n  overflow: hidden;\n}\n.footer[_ngcontent-%COMP%] {\n  display: flex;\n  width: 50%;\n  font-size: x-small;\n  color: black;\n}\n/*# sourceMappingURL=dashboard.component.css.map */"]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(DashboardComponent, {
        className: "DashboardComponent",
        filePath: "src/app/modules/dashboard/dashboard.component.ts",
        lineNumber: 20
    });
})();

// src/app/modules/dashboard/state/dashboard.reducer.ts
var dashboardFeatureKey = "dashboard";
var initialState = {
    loading: false,
    error: {}
};
var dashboardReducer = createReducer(initialState);

// src/app/modules/dashboard/state/dashboard.actions.ts
var dashboardActions = {
    initialize: createAction("[dashboard] initialize"),
    loadCpuChart: createAction("[dashboard] loadCpuChart", props()),
    loadCpuChartSuccess: createAction("[dashboard] loadCpuChartSuccess", props()),
    loadCpuChartFailure: createAction("[dashboard] loadCpuChartFailure", props())
};

// src/app/modules/dashboard/state/dashboard.effects.ts
var DashboardEffects = class _DashboardEffects {
    constructor(actions$, monitoringService) {
        this.actions$ = actions$;
        this.monitoringService = monitoringService;
        this.sortColumns = [];
        this.loadCpuChart$ = createEffect(() => this.actions$.pipe(ofType(dashboardActions.loadCpuChart), mergeMap(() => this.monitoringService.getCounters(dashboardActions.loadCpuChart.arguments.name, dashboardActions.loadCpuChart.arguments.start, dashboardActions.loadCpuChart.arguments.end, dashboardActions.loadCpuChart.arguments.step).pipe(map((counters) => dashboardActions.loadCpuChartSuccess(counters)), catchError((error) => of(dashboardActions.loadCpuChartFailure({error: error.message})))))));
    }

    static {
        this.\u0275fac = function DashboardEffects_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _DashboardEffects)(\u0275\u0275inject(Actions), \u0275\u0275inject(MonitoringService));
        };
    }
    static {
        this.\u0275prov = /* @__PURE__ */ \u0275\u0275defineInjectable({token: _DashboardEffects, factory: _DashboardEffects.\u0275fac});
    }
};

// src/app/modules/dashboard/dashboard-routing.module.ts
var routes = [
    {
        path: "",
        title: "Dashboard",
        component: DashboardComponent
    }
    // {
    //     path: KLAERFAELLE_DETAIL_PATH,
    //     title: 'Einzelansicht Klärfälle',
    //     component: KlaerfaelleDetailComponent
    // }
];
var DashboardRoutingModule = class _DashboardRoutingModule {
    static {
        this.\u0275fac = function DashboardRoutingModule_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _DashboardRoutingModule)();
        };
    }
    static {
        this.\u0275mod = /* @__PURE__ */ \u0275\u0275defineNgModule({type: _DashboardRoutingModule});
    }
    static {
        this.\u0275inj = /* @__PURE__ */ \u0275\u0275defineInjector({imports: [RouterModule.forChild(routes), RouterModule]});
    }
};

// src/app/modules/dashboard/dashboard.module.ts
var DashboardModule = class _DashboardModule {
    static {
        this.\u0275fac = function DashboardModule_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _DashboardModule)();
        };
    }
    static {
        this.\u0275mod = /* @__PURE__ */ \u0275\u0275defineNgModule({type: _DashboardModule});
    }
    static {
        this.\u0275inj = /* @__PURE__ */ \u0275\u0275defineInjector({
            providers: [MonitoringService, ModuleService], imports: [
                MatCardModule,
                MatTableModule,
                MatIconModule,
                MatButtonModule,
                MatIconModule,
                MatTooltipModule,
                MatListModule,
                MatFormFieldModule,
                MatInputModule,
                MatSelectModule,
                MatOptionModule,
                MatIcon,
                ReactiveFormsModule,
                FormsModule,
                ChartComponent,
                DashboardRoutingModule,
                CpuChartComponent,
                MemoryChartComponent,
                GatewayTimeComponent,
                ThreadsChartComponent,
                StoreModule.forFeature(dashboardFeatureKey, dashboardReducer),
                EffectsModule.forFeature([DashboardEffects]),
                MatGridList,
                MatGridTile
            ]
        });
    }
};

export {
    ModuleService,
    MatToolbar,
    MatToolbarModule,
    MonitoringService,
    ChartComponent,
    ChartService,
    DashboardModule
};
//# sourceMappingURL=chunk-BINZFY4V.js.map

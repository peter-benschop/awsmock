import {FileImportComponent} from "./chunk-E2KWZO4F.js";
import {SqsService} from "./chunk-7C5R5GF7.js";
import {MatSlideToggle} from "./chunk-4VAYYVT5.js";
import {CdkDrag, CdkDragHandle} from "./chunk-L5B3QUPF.js";
import "./chunk-HK7D4W5I.js";
import {byteConversion} from "./chunk-5F2IFVYA.js";
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
    filter,
    FormBuilder,
    FormsModule,
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
    MatPaginator,
    MatRow,
    MatRowDef,
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
import {__spreadProps, __spreadValues} from "./chunk-G42SKTPL.js";

// src/app/modules/sqs/queue-add/queue-add-component.ts
var QueueAddComponentDialog = class _QueueAddComponentDialog {
    constructor(fb, dialogRef, portList) {
        this.fb = fb;
        this.dialogRef = dialogRef;
        this.portList = portList;
        this.queueName = "";
    }

    ngOnInit() {
        this.form = this.fb.group({
            queueName: [""]
        });
    }

    save() {
        console.log("Formdata: ", this.queueName);
        this.dialogRef.close(this.queueName);
    }

    close() {
        this.dialogRef.close(false);
    }

    static {
        this.\u0275fac = function QueueAddComponentDialog_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _QueueAddComponentDialog)(\u0275\u0275directiveInject(FormBuilder), \u0275\u0275directiveInject(MatDialogRef), \u0275\u0275directiveInject(MAT_DIALOG_DATA));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _QueueAddComponentDialog,
            selectors: [["queue-add-dialog"]],
            standalone: true,
            features: [\u0275\u0275StandaloneFeature],
            decls: 12,
            vars: 1,
            consts: [["mat-dialog-title", ""], [1, "mat-typography", 2, "width", "500px"], [2, "width", "100%"], ["matInput", "", "value", "", 3, "ngModelChange", "ngModel"], ["align", "end"], ["mat-button", "", "mat-dialog-close", ""], ["cdkFocusInitial", "", "mat-button", "", 3, "click"]],
            template: function QueueAddComponentDialog_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "h2", 0);
                    \u0275\u0275text(1, "Add SQS Queue");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(2, "mat-dialog-content", 1)(3, "mat-form-field", 2)(4, "mat-label");
                    \u0275\u0275text(5, "Queue Name");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(6, "input", 3);
                    \u0275\u0275twoWayListener("ngModelChange", function QueueAddComponentDialog_Template_input_ngModelChange_6_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.queueName, $event) || (ctx.queueName = $event);
                        return $event;
                    });
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(7, "mat-dialog-actions", 4)(8, "button", 5);
                    \u0275\u0275text(9, "Cancel");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(10, "button", 6);
                    \u0275\u0275listener("click", function QueueAddComponentDialog_Template_button_click_10_listener() {
                        return ctx.save();
                    });
                    \u0275\u0275text(11, "Add");
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    \u0275\u0275advance(6);
                    \u0275\u0275twoWayProperty("ngModel", ctx.queueName);
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
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(QueueAddComponentDialog, {
        className: "QueueAddComponentDialog",
        filePath: "src/app/modules/sqs/queue-add/queue-add-component.ts",
        lineNumber: 38
    });
})();

// src/app/modules/sqs/send-message/send-message.component.ts
var SendMessageComponentDialog = class _SendMessageComponentDialog {
    constructor(fb, dialogRef, data, fileDialog) {
        this.fb = fb;
        this.dialogRef = dialogRef;
        this.data = data;
        this.fileDialog = fileDialog;
        this.queueUrl = "";
        this.queueName = "";
        this.message = "";
        this.queueUrl = data.queueUrl;
        this.queueName = data.queueUrl.substring(this.queueUrl.lastIndexOf("/") + 1);
    }

    ngOnInit() {
    }

    sendMessage() {
        this.dialogRef.close(this.message);
    }

    loadFromFile() {
        const dialogConfig = new MatDialogConfig();
        dialogConfig.disableClose = true;
        dialogConfig.autoFocus = true;
        this.fileDialog.open(FileImportComponent, dialogConfig).afterClosed().subscribe((result) => {
            if (result) {
                this.message = result;
            }
        });
    }

    close() {
        this.dialogRef.close(false);
    }

    static {
        this.\u0275fac = function SendMessageComponentDialog_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _SendMessageComponentDialog)(\u0275\u0275directiveInject(FormBuilder), \u0275\u0275directiveInject(MatDialogRef), \u0275\u0275directiveInject(MAT_DIALOG_DATA), \u0275\u0275directiveInject(MatDialog));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _SendMessageComponentDialog,
            selectors: [["queue-send-message-dialog"]],
            standalone: true,
            features: [\u0275\u0275StandaloneFeature],
            decls: 14,
            vars: 2,
            consts: [["cdkDrag", "", "cdkDragHandle", "", "cdkDragRootElement", ".cdk-overlay-pane", "mat-dialog-title", ""], [1, "mat-typography"], [2, "width", "100%", "height", "100%"], ["cdkAutosizeMinRows", "70", "cdkTextareaAutosize", "", "matInput", "", "placeholder", "Message", 2, "width", "100%", "height", "100%", 3, "ngModelChange", "ngModel"], ["align", "end"], ["mat-button", "", "mat-dialog-close", ""], ["mat-button", "", 3, "click"], ["cdkFocusInitial", "", "mat-button", "", 3, "click"]],
            template: function SendMessageComponentDialog_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "h2", 0);
                    \u0275\u0275text(1);
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(2, "mat-dialog-content", 1)(3, "mat-form-field", 2)(4, "mat-label");
                    \u0275\u0275text(5, "Message:");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(6, "textarea", 3);
                    \u0275\u0275twoWayListener("ngModelChange", function SendMessageComponentDialog_Template_textarea_ngModelChange_6_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.message, $event) || (ctx.message = $event);
                        return $event;
                    });
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(7, "mat-dialog-actions", 4)(8, "button", 5);
                    \u0275\u0275text(9, "Cancel");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(10, "button", 6);
                    \u0275\u0275listener("click", function SendMessageComponentDialog_Template_button_click_10_listener() {
                        return ctx.loadFromFile();
                    });
                    \u0275\u0275text(11, "Load File");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(12, "button", 7);
                    \u0275\u0275listener("click", function SendMessageComponentDialog_Template_button_click_12_listener() {
                        return ctx.sendMessage();
                    });
                    \u0275\u0275text(13, "Send");
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    \u0275\u0275advance();
                    \u0275\u0275textInterpolate1("Send SQS message: ", ctx.queueName, "");
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
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(SendMessageComponentDialog, {
        className: "SendMessageComponentDialog",
        filePath: "src/app/modules/sqs/send-message/send-message.component.ts",
        lineNumber: 37
    });
})();

// src/app/modules/sqs/queues-list/state/sqs-queue-list.actions.ts
var sqsQueueListActions = {
    initialize: createAction("[sqs-queue-list] initialize"),
    // Load queue
    loadQueues: createAction("[sqs-queue-list] Load Queues", props()),
    loadQueuesSuccess: createAction("[sqs-queue-list] Load Queues Success", props()),
    loadQueuesFailure: createAction("[sqs-queue-list] Load Queues Error", props()),
    // Add queue
    addQueue: createAction("[sqs-queue-list] Add Queue", props()),
    addQueueSuccess: createAction("[sqs-queue-list] Add Queue Success"),
    addQueueFailure: createAction("[sqs-queue-list] Add Queue Error", props()),
    // Delete queue
    deleteQueue: createAction("[sqs-queue-list] Delete Queue", props()),
    deleteQueueSuccess: createAction("[sqs-queue-list] Delete Queue Success"),
    deleteQueueFailure: createAction("[sqs-queue-list] Delete Queue Error", props()),
    // Purge queue
    purgeQueue: createAction("[sqs-queue-list] Delete Queue", props()),
    purgeQueueSuccess: createAction("[sqs-queue-list] Delete Queue Success"),
    purgeQueueFailure: createAction("[sqs-queue-list] Delete Queue Error", props())
};

// src/app/modules/sqs/queues-list/state/sqs-queue-list.reducer.ts
var sqsQueueListFeatureKey = "sqs-queue-list";
var initialState = {
    listQueueResponse: {Total: 0, QueueCounters: []},
    prefix: "",
    pageSize: 10,
    pageIndex: 0,
    loading: false,
    sortColumns: [{column: "attributes.approximateNumberOfMessages", sortDirection: -1}],
    error: {}
};
var sqsQueueListReducer = createReducer(
    initialState,
    // Initialize
    on(sqsQueueListActions.initialize, (state) => __spreadProps(__spreadValues({}, state), {pageIndex: 0, pageSize: 10, loading: true})),
    // Queue list
    on(sqsQueueListActions.loadQueues, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(sqsQueueListActions.loadQueuesSuccess, (state, {queues}) => __spreadProps(__spreadValues({}, state), {listQueueResponse: queues, loading: false})),
    on(sqsQueueListActions.loadQueuesFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false})),
    // Add queue
    on(sqsQueueListActions.addQueue, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(sqsQueueListActions.addQueueSuccess, (state) => __spreadProps(__spreadValues({}, state), {loading: false})),
    on(sqsQueueListActions.addQueueFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false})),
    // Purge queue
    on(sqsQueueListActions.purgeQueue, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(sqsQueueListActions.purgeQueueSuccess, (state) => __spreadProps(__spreadValues({}, state), {loading: false})),
    on(sqsQueueListActions.purgeQueueFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false})),
    // Delete queue
    on(sqsQueueListActions.deleteQueue, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(sqsQueueListActions.deleteQueueSuccess, (state) => __spreadProps(__spreadValues({}, state), {loading: false})),
    on(sqsQueueListActions.deleteQueueFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false}))
);

// src/app/modules/sqs/queues-list/state/sqs-queue-list.selectors.ts
var selectQueueListFeature = createFeatureSelector(sqsQueueListFeatureKey);
var selectIsLoading = createSelector(selectQueueListFeature, (state) => state.loading);
var selectPrefix = createSelector(selectQueueListFeature, (state) => state?.prefix);
var selectPageSize = createSelector(selectQueueListFeature, (state) => state?.pageSize);
var selectPageIndex = createSelector(selectQueueListFeature, (state) => state?.pageIndex);
var selectSortColumns = createSelector(selectQueueListFeature, (state) => state?.sortColumns);
var selectQueueCounters = createSelector(selectQueueListFeature, (state) => state?.listQueueResponse);

// src/app/modules/sqs/queues-list/sqs-queue-list.component.ts
var _c0 = () => [];

function SqsQueueListComponent_button_21_Template(rf, ctx) {
    if (rf & 1) {
        const _r1 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "button", 13);
        \u0275\u0275listener("click", function SqsQueueListComponent_button_21_Template_button_click_0_listener() {
            \u0275\u0275restoreView(_r1);
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.setPrefix());
        });
        \u0275\u0275elementStart(1, "mat-icon", 14);
        \u0275\u0275text(2, "search");
        \u0275\u0275elementEnd()();
    }
}

function SqsQueueListComponent_button_22_Template(rf, ctx) {
    if (rf & 1) {
        const _r3 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "button", 13);
        \u0275\u0275listener("click", function SqsQueueListComponent_button_22_Template_button_click_0_listener() {
            \u0275\u0275restoreView(_r3);
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.unsetPrefix());
        });
        \u0275\u0275elementStart(1, "mat-icon", 14);
        \u0275\u0275text(2, "close");
        \u0275\u0275elementEnd()();
    }
}

function SqsQueueListComponent_div_24_th_3_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 37);
        \u0275\u0275text(1, "Name");
        \u0275\u0275elementEnd();
    }
}

function SqsQueueListComponent_div_24_td_4_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 38)(1, "mat-nav-list")(2, "a", 39);
        \u0275\u0275text(3);
        \u0275\u0275elementEnd()()();
    }
    if (rf & 2) {
        const element_r5 = ctx.$implicit;
        \u0275\u0275advance(2);
        \u0275\u0275propertyInterpolate1("routerLink", "./messages/", element_r5.queueArn, "");
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r5.queueName, "");
    }
}

function SqsQueueListComponent_div_24_th_6_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 40);
        \u0275\u0275text(1, "Available ");
        \u0275\u0275elementEnd();
    }
}

function SqsQueueListComponent_div_24_td_7_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 38);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r6 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r6.available, "");
    }
}

function SqsQueueListComponent_div_24_th_9_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 41);
        \u0275\u0275text(1, "In flight ");
        \u0275\u0275elementEnd();
    }
}

function SqsQueueListComponent_div_24_td_10_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 38);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r7 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r7.invisible, "");
    }
}

function SqsQueueListComponent_div_24_th_12_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 42);
        \u0275\u0275text(1, "Delayed ");
        \u0275\u0275elementEnd();
    }
}

function SqsQueueListComponent_div_24_td_13_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 38);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r8 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r8.delayed, "");
    }
}

function SqsQueueListComponent_div_24_th_15_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 43);
        \u0275\u0275text(1, "Size ");
        \u0275\u0275elementEnd();
    }
}

function SqsQueueListComponent_div_24_td_16_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 38);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r9 = ctx.$implicit;
        const ctx_r1 = \u0275\u0275nextContext(2);
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", ctx_r1.byteConversion(element_r9.size), "");
    }
}

function SqsQueueListComponent_div_24_th_18_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 44);
        \u0275\u0275text(1, " Created ");
        \u0275\u0275elementEnd();
    }
}

function SqsQueueListComponent_div_24_td_19_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 38);
        \u0275\u0275text(1);
        \u0275\u0275pipe(2, "date");
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r10 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", \u0275\u0275pipeBind2(2, 1, element_r10.created, "dd-MM-yyyy HH:mm:ss"), " ");
    }
}

function SqsQueueListComponent_div_24_th_21_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 45);
        \u0275\u0275text(1, " Modified ");
        \u0275\u0275elementEnd();
    }
}

function SqsQueueListComponent_div_24_td_22_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 38);
        \u0275\u0275text(1);
        \u0275\u0275pipe(2, "date");
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r11 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", \u0275\u0275pipeBind2(2, 1, element_r11.modified, "dd-MM-yyyy HH:mm:ss"), " ");
    }
}

function SqsQueueListComponent_div_24_th_24_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 46);
        \u0275\u0275text(1, "Actions");
        \u0275\u0275elementEnd();
    }
}

function SqsQueueListComponent_div_24_td_25_Template(rf, ctx) {
    if (rf & 1) {
        const _r12 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "td", 38)(1, "button", 47);
        \u0275\u0275listener("click", function SqsQueueListComponent_div_24_td_25_Template_button_click_1_listener() {
            const row_r13 = \u0275\u0275restoreView(_r12).$implicit;
            const ctx_r1 = \u0275\u0275nextContext(2);
            return \u0275\u0275resetView(ctx_r1.sendMessage(row_r13.queueUrl));
        });
        \u0275\u0275elementStart(2, "mat-icon");
        \u0275\u0275text(3, "send");
        \u0275\u0275elementEnd()();
        \u0275\u0275elementStart(4, "button", 48)(5, "mat-icon");
        \u0275\u0275text(6, "edit");
        \u0275\u0275elementEnd()();
        \u0275\u0275elementStart(7, "button", 49);
        \u0275\u0275listener("click", function SqsQueueListComponent_div_24_td_25_Template_button_click_7_listener() {
            const row_r13 = \u0275\u0275restoreView(_r12).$implicit;
            const ctx_r1 = \u0275\u0275nextContext(2);
            return \u0275\u0275resetView(ctx_r1.purgeQueue(row_r13.queueUrl));
        });
        \u0275\u0275elementStart(8, "mat-icon");
        \u0275\u0275text(9, "clear_all");
        \u0275\u0275elementEnd()();
        \u0275\u0275elementStart(10, "button", 50);
        \u0275\u0275listener("click", function SqsQueueListComponent_div_24_td_25_Template_button_click_10_listener() {
            const row_r13 = \u0275\u0275restoreView(_r12).$implicit;
            const ctx_r1 = \u0275\u0275nextContext(2);
            return \u0275\u0275resetView(ctx_r1.deleteQueue(row_r13.queueUrl));
        });
        \u0275\u0275elementStart(11, "mat-icon");
        \u0275\u0275text(12, "delete");
        \u0275\u0275elementEnd()()();
    }
    if (rf & 2) {
        const row_r13 = ctx.$implicit;
        \u0275\u0275advance(4);
        \u0275\u0275propertyInterpolate1("routerLink", "./details/", row_r13.queueArn, "");
    }
}

function SqsQueueListComponent_div_24_tr_26_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 51);
    }
}

function SqsQueueListComponent_div_24_tr_27_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 52);
    }
}

function SqsQueueListComponent_div_24_tr_28_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "tr", 53)(1, "td", 54);
        \u0275\u0275text(2, " No data matching the filter. ");
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const ctx_r1 = \u0275\u0275nextContext(2);
        \u0275\u0275advance();
        \u0275\u0275attribute("colspan", ctx_r1.columns.length);
    }
}

function SqsQueueListComponent_div_24_Template(rf, ctx) {
    if (rf & 1) {
        const _r4 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "div", 15)(1, "table", 16);
        \u0275\u0275listener("matSortChange", function SqsQueueListComponent_div_24_Template_table_matSortChange_1_listener($event) {
            \u0275\u0275restoreView(_r4);
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.sortChange($event));
        });
        \u0275\u0275elementContainerStart(2, 17);
        \u0275\u0275template(3, SqsQueueListComponent_div_24_th_3_Template, 2, 0, "th", 18)(4, SqsQueueListComponent_div_24_td_4_Template, 4, 3, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(5, 20);
        \u0275\u0275template(6, SqsQueueListComponent_div_24_th_6_Template, 2, 0, "th", 21)(7, SqsQueueListComponent_div_24_td_7_Template, 2, 1, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(8, 22);
        \u0275\u0275template(9, SqsQueueListComponent_div_24_th_9_Template, 2, 0, "th", 23)(10, SqsQueueListComponent_div_24_td_10_Template, 2, 1, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(11, 24);
        \u0275\u0275template(12, SqsQueueListComponent_div_24_th_12_Template, 2, 0, "th", 25)(13, SqsQueueListComponent_div_24_td_13_Template, 2, 1, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(14, 26);
        \u0275\u0275template(15, SqsQueueListComponent_div_24_th_15_Template, 2, 0, "th", 27)(16, SqsQueueListComponent_div_24_td_16_Template, 2, 1, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(17, 28);
        \u0275\u0275template(18, SqsQueueListComponent_div_24_th_18_Template, 2, 0, "th", 29)(19, SqsQueueListComponent_div_24_td_19_Template, 3, 4, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(20, 30);
        \u0275\u0275template(21, SqsQueueListComponent_div_24_th_21_Template, 2, 0, "th", 31)(22, SqsQueueListComponent_div_24_td_22_Template, 3, 4, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(23, 32);
        \u0275\u0275template(24, SqsQueueListComponent_div_24_th_24_Template, 2, 0, "th", 33)(25, SqsQueueListComponent_div_24_td_25_Template, 13, 2, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275template(26, SqsQueueListComponent_div_24_tr_26_Template, 1, 0, "tr", 34)(27, SqsQueueListComponent_div_24_tr_27_Template, 1, 0, "tr", 35)(28, SqsQueueListComponent_div_24_tr_28_Template, 3, 1, "tr", 36);
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const queueCounters_r14 = ctx.ngIf;
        const ctx_r1 = \u0275\u0275nextContext();
        \u0275\u0275advance();
        \u0275\u0275property("dataSource", queueCounters_r14.QueueCounters);
        \u0275\u0275advance(25);
        \u0275\u0275property("matHeaderRowDef", ctx_r1.columns);
        \u0275\u0275advance();
        \u0275\u0275property("matRowDefColumns", ctx_r1.columns);
    }
}

var SqsQueueListComponent = class _SqsQueueListComponent {
    constructor(dialog, state, sqsService, location, store, actionsSubj$) {
        this.dialog = dialog;
        this.state = state;
        this.sqsService = sqsService;
        this.location = location;
        this.store = store;
        this.actionsSubj$ = actionsSubj$;
        this.lastUpdate = /* @__PURE__ */ new Date();
        this.pageSize$ = this.store.select(selectPageSize);
        this.pageIndex$ = this.store.select(selectPageIndex);
        this.prefix$ = this.store.select(selectPrefix);
        this.listQueueCountersResponse$ = this.store.select(selectQueueCounters);
        this.columns = ["queueName", "messagesAvailable", "messagesInFlight", "messagesDelayed", "size", "created", "modified", "actions"];
        this.pageSizeOptions = [5, 10, 20, 50, 100];
        this.hidePageSize = false;
        this.showPageSizeOptions = true;
        this.showFirstLastButtons = true;
        this.disabled = false;
        this.prefixValue = this.state.value["sqs-queue-list"].prefix;
        this.prefixSet = false;
        this.byteConversion = byteConversion;
        this.actionsSubj$.pipe(filter((action) => action.type === sqsQueueListActions.addQueueSuccess.type || action.type === sqsQueueListActions.purgeQueueSuccess.type || action.type === sqsQueueListActions.deleteQueueSuccess.type)).subscribe(() => {
            this.loadQueues();
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
        this.loadQueues();
        this.updateSubscription = interval(6e4).subscribe(() => this.loadQueues());
    }

    ngOnDestroy() {
        this.updateSubscription?.unsubscribe();
    }

    back() {
        this.location.back();
    }

    refresh() {
        this.loadQueues();
    }

    setPrefix() {
        this.prefixSet = true;
        this.state.value["sqs-queue-list"].pageIndex = 0;
        this.state.value["sqs-queue-list"].prefix = this.prefixValue;
        this.loadQueues();
    }

    unsetPrefix() {
        this.prefixValue = "";
        this.prefixSet = false;
        this.state.value["sqs-queue-list"].prefix = "";
        this.loadQueues();
    }

    handlePageEvent(e) {
        this.state.value["sqs-queue-list"].pageSize = e.pageSize;
        this.state.value["sqs-queue-list"].pageIndex = e.pageIndex;
        this.loadQueues();
    }

    sortChange(sortState) {
        this.state.value["sqs-queue-list"].sortColumns = [];
        let direction;
        let column = "attributes.approximateNumberOfMessages";
        if (sortState.active === "messagesInFlight") {
            column = "attributes.approximateNumberOfMessagesNotVisible";
        } else if (sortState.active === "messagesDelayed") {
            column = "attributes.approximateNumberOfMessagesDelayed";
        }
        if (sortState.direction === "asc") {
            direction = 1;
        } else {
            direction = -1;
        }
        this.state.value["sqs-queue-list"].sortColumns = [{column, sortDirection: direction}];
        this.loadQueues();
    }

    loadQueues() {
        this.lastUpdate = /* @__PURE__ */ new Date();
        this.store.dispatch(sqsQueueListActions.loadQueues({
            prefix: this.state.value["sqs-queue-list"].prefix,
            pageSize: this.state.value["sqs-queue-list"].pageSize,
            pageIndex: this.state.value["sqs-queue-list"].pageIndex,
            sortColumns: this.state.value["sqs-queue-list"].sortColumns
        }));
    }

    addQueue() {
        const dialogConfig = new MatDialogConfig();
        dialogConfig.disableClose = true;
        dialogConfig.autoFocus = true;
        this.dialog.open(QueueAddComponentDialog, dialogConfig).afterClosed().subscribe((result) => {
            if (result) {
                this.store.dispatch(sqsQueueListActions.addQueue({name: result}));
            }
        });
    }

    purgeQueue(queueUrl) {
        this.store.dispatch(sqsQueueListActions.purgeQueue({queueUrl}));
    }

    sendMessage(queueUrl) {
        const dialogConfig = new MatDialogConfig();
        dialogConfig.disableClose = true;
        dialogConfig.autoFocus = true;
        dialogConfig.data = {queueUrl};
        dialogConfig.maxWidth = "100vw";
        dialogConfig.maxHeight = "100vh";
        dialogConfig.panelClass = "full-screen-modal";
        dialogConfig.width = "90%";
        this.dialog.open(SendMessageComponentDialog, dialogConfig).afterClosed().subscribe((result) => {
            if (result) {
                this.sqsService.sendMessage(queueUrl, result);
                this.loadQueues();
            }
        });
    }

    deleteQueue(queueUrl) {
        this.store.dispatch(sqsQueueListActions.deleteQueue({queueUrl}));
    }

    static {
        this.\u0275fac = function SqsQueueListComponent_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _SqsQueueListComponent)(\u0275\u0275directiveInject(MatDialog), \u0275\u0275directiveInject(State), \u0275\u0275directiveInject(SqsService), \u0275\u0275directiveInject(Location), \u0275\u0275directiveInject(Store), \u0275\u0275directiveInject(ActionsSubject));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _SqsQueueListComponent,
            selectors: [["sqs-queue-list"]],
            decls: 33,
            vars: 24,
            consts: [["appearance", "outlined", 2, "margin", "3px"], ["aria-label", "Back", "mat-icon-button", "", 1, "head-buttons-left", 3, "click"], [1, "fill-remaining-space"], ["aria-label", "Refresh", "mat-icon-button", "", 3, "click"], ["appearance", "outlined", 2, "margin", "-10px"], ["align", "start"], [2, "width", "100%"], ["matInput", "", "name", "search", "placeholder", "Search", "type", "text", 3, "ngModelChange", "ngModel"], ["mat-icon-button", "", "matSuffix", "", "style", "float: right", 3, "click", 4, "ngIf"], [1, "table-container"], ["class", "row", 4, "ngIf"], ["aria-label", "Select page", 2, "width", "99%", "margin-left", "15px", 3, "page", "disabled", "hidePageSize", "length", "pageIndex", "pageSizeOptions", "pageSize", "showFirstLastButtons"], [1, "footer"], ["mat-icon-button", "", "matSuffix", "", 2, "float", "right", 3, "click"], ["matSuffix", ""], [1, "row"], ["mat-table", "", "matSort", "", 1, "mat-elevation-z8", "queue-table", 3, "matSortChange", "dataSource"], ["matColumnDef", "queueName"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Queue name", "sortActionDescription", "Sort by queueUrl", 4, "matHeaderCellDef"], ["mat-cell", "", 4, "matCellDef"], ["matColumnDef", "messagesAvailable"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Number of messages available", "sortActionDescription", "Sort by messageAvailable", 4, "matHeaderCellDef"], ["matColumnDef", "messagesInFlight"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Number of messages invisible", "sortActionDescription", "Sort by messagesInFlight", 4, "matHeaderCellDef"], ["matColumnDef", "messagesDelayed"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Number of messages delayed", "sortActionDescription", "Sort by messagesDelayed", 4, "matHeaderCellDef"], ["matColumnDef", "size"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Total size of all messages in bytes", "sortActionDescription", "Sort by size", 4, "matHeaderCellDef"], ["matColumnDef", "created"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Queue creation timestamp", "sortActionDescription", "Sort by created", 4, "matHeaderCellDef"], ["matColumnDef", "modified"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Queue modified timestamp", "sortActionDescription", "Sort by modified", 4, "matHeaderCellDef"], ["matColumnDef", "actions"], ["mat-header-cell", "", "style", "width:240px", 4, "matHeaderCellDef"], ["mat-header-row", "", 4, "matHeaderRowDef"], ["mat-row", "", 4, "matRowDef", "matRowDefColumns"], ["class", "mat-row", 4, "matNoDataRow"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Queue name", "sortActionDescription", "Sort by queueUrl"], ["mat-cell", ""], ["mat-list-item", "", 3, "routerLink"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Number of messages available", "sortActionDescription", "Sort by messageAvailable"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Number of messages invisible", "sortActionDescription", "Sort by messagesInFlight"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Number of messages delayed", "sortActionDescription", "Sort by messagesDelayed"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Total size of all messages in bytes", "sortActionDescription", "Sort by size"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Queue creation timestamp", "sortActionDescription", "Sort by created"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Queue modified timestamp", "sortActionDescription", "Sort by modified"], ["mat-header-cell", "", 2, "width", "240px"], ["aria-label", "Send", "mat-icon-button", "", "matTooltip", "Send a message", 3, "click"], ["aria-label", "MessageList", "mat-icon-button", "", "matTooltip", "Lists all messages", 3, "routerLink"], ["aria-label", "Purge", "mat-icon-button", "", "matTooltip", "Purge the queue", 3, "click"], ["aria-label", "Purge", "mat-icon-button", "", "matTooltip", "Delete the queue", 3, "click"], ["mat-header-row", ""], ["mat-row", ""], [1, "mat-row"], [1, "mat-cell"]],
            template: function SqsQueueListComponent_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "mat-card", 0)(1, "mat-card-header")(2, "button", 1);
                    \u0275\u0275listener("click", function SqsQueueListComponent_Template_button_click_2_listener() {
                        return ctx.back();
                    });
                    \u0275\u0275elementStart(3, "mat-icon");
                    \u0275\u0275text(4, "arrow_back");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(5, "span", 2)(6, "h4");
                    \u0275\u0275text(7, "SQS Queues");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(8, "button", 3);
                    \u0275\u0275listener("click", function SqsQueueListComponent_Template_button_click_8_listener() {
                        return ctx.addQueue();
                    });
                    \u0275\u0275elementStart(9, "mat-icon");
                    \u0275\u0275text(10, "add");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(11, "button", 3);
                    \u0275\u0275listener("click", function SqsQueueListComponent_Template_button_click_11_listener() {
                        return ctx.refresh();
                    });
                    \u0275\u0275elementStart(12, "mat-icon");
                    \u0275\u0275text(13, "refresh");
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(14, "mat-card-content")(15, "mat-card", 4)(16, "mat-card-actions", 5)(17, "mat-form-field", 6)(18, "mat-label");
                    \u0275\u0275text(19, "Prefix");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(20, "input", 7);
                    \u0275\u0275twoWayListener("ngModelChange", function SqsQueueListComponent_Template_input_ngModelChange_20_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.prefixValue, $event) || (ctx.prefixValue = $event);
                        return $event;
                    });
                    \u0275\u0275elementEnd();
                    \u0275\u0275template(21, SqsQueueListComponent_button_21_Template, 3, 0, "button", 8)(22, SqsQueueListComponent_button_22_Template, 3, 0, "button", 8);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(23, "div", 9);
                    \u0275\u0275template(24, SqsQueueListComponent_div_24_Template, 29, 3, "div", 10);
                    \u0275\u0275pipe(25, "async");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(26, "mat-paginator", 11);
                    \u0275\u0275pipe(27, "async");
                    \u0275\u0275pipe(28, "async");
                    \u0275\u0275pipe(29, "async");
                    \u0275\u0275listener("page", function SqsQueueListComponent_Template_mat_paginator_page_26_listener($event) {
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
                    let tmp_9_0;
                    \u0275\u0275advance(20);
                    \u0275\u0275twoWayProperty("ngModel", ctx.prefixValue);
                    \u0275\u0275advance();
                    \u0275\u0275property("ngIf", !ctx.prefixSet);
                    \u0275\u0275advance();
                    \u0275\u0275property("ngIf", ctx.prefixSet);
                    \u0275\u0275advance(2);
                    \u0275\u0275property("ngIf", \u0275\u0275pipeBind1(25, 12, ctx.listQueueCountersResponse$));
                    \u0275\u0275advance(2);
                    \u0275\u0275property("disabled", ctx.disabled)("hidePageSize", ctx.hidePageSize)("length", (tmp_6_0 = \u0275\u0275pipeBind1(27, 14, ctx.listQueueCountersResponse$)) == null ? null : tmp_6_0.Total)("pageIndex", \u0275\u0275pipeBind1(28, 16, ctx.pageIndex$))("pageSizeOptions", ctx.showPageSizeOptions ? ctx.pageSizeOptions : \u0275\u0275pureFunction0(23, _c0))("pageSize", (tmp_9_0 = \u0275\u0275pipeBind1(29, 18, ctx.pageSize$)) !== null && tmp_9_0 !== void 0 ? tmp_9_0 : false)("showFirstLastButtons", ctx.showFirstLastButtons);
                    \u0275\u0275advance(5);
                    \u0275\u0275textInterpolate1(" Last update: ", \u0275\u0275pipeBind2(32, 20, ctx.lastUpdate, "HH:mm:ss"), " ");
                }
            },
            dependencies: [MatCard, MatCardHeader, MatCardContent, MatCardActions, MatTable, MatHeaderCellDef, MatCellDef, MatColumnDef, MatIcon, MatHeaderCell, MatCell, MatHeaderRowDef, MatHeaderRow, MatSortHeader, MatRowDef, MatNoDataRow, MatIconButton, MatRow, MatPaginator, MatSort, MatTooltip, RouterLink, MatListItem, MatNavList, MatFormField, MatInput, MatLabel, MatSuffix, NgIf, DefaultValueAccessor, NgControlStatus, NgModel, DatePipe, AsyncPipe],
            styles: ['\n\n.queue-table[_ngcontent-%COMP%] {\n  width: 100%;\n  height: 100%;\n}\n[_nghost-%COMP%] {\n  position: relative;\n  width: 100%;\n  height: 30%;\n  margin-top: 0;\n  padding-bottom: 33%;\n}\n.head-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  justify-content: flex-end;\n}\n.footer-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  width: 50%;\n  justify-content: flex-end;\n}\n.full-screen-modal[_ngcontent-%COMP%]   .mat-dialog-container[_ngcontent-%COMP%] {\n  padding: 1em;\n  width: 90%;\n  height: 80%;\n  overflow-y: scroll;\n}\n.fill-remaining-space[_ngcontent-%COMP%] {\n  flex: 1 1 auto;\n}\n.table-container[_ngcontent-%COMP%] {\n  max-height: calc(100vh - 10px);\n  overflow: auto;\n}\n.cdk-global-overlay-wrapper[_ngcontent-%COMP%] {\n  pointer-events: auto;\n  display: block;\n  position: relative;\n  overflow: auto;\n  text-align: center;\n}\n.cdk-global-overlay-wrapper[_ngcontent-%COMP%]::before {\n  content: "";\n  display: inline-block;\n  height: 100%;\n  white-space: nowrap;\n}\n.cdk-overlay-pane[_ngcontent-%COMP%] {\n  display: inline-block;\n  position: relative;\n  text-align: left;\n  white-space: normal;\n}\n.footer[_ngcontent-%COMP%] {\n  display: flex;\n  width: 50%;\n  font-size: x-small;\n  color: black;\n  padding-top: 15px;\n}\n/*# sourceMappingURL=sqs-queue-list.component.css.map */']
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(SqsQueueListComponent, {
        className: "SqsQueueListComponent",
        filePath: "src/app/modules/sqs/queues-list/sqs-queue-list.component.ts",
        lineNumber: 22
    });
})();

// src/app/modules/sqs/queues-list/state/sqs-queue-list.effects.ts
var SqsQueueListEffects = class _SqsQueueListEffects {
    constructor(actions$, sqsService) {
        this.actions$ = actions$;
        this.sqsService = sqsService;
        this.sortColumns = [];
        this.loadQueues$ = createEffect(() => this.actions$.pipe(ofType(sqsQueueListActions.loadQueues), mergeMap((action) => this.sqsService.listQueueCounters(action.prefix, action.pageSize, action.pageIndex, action.sortColumns).pipe(map((queues) => sqsQueueListActions.loadQueuesSuccess({queues})), catchError((error) => of(sqsQueueListActions.loadQueuesFailure({error: error.message})))))));
        this.addQueue$ = createEffect(() => this.actions$.pipe(ofType(sqsQueueListActions.addQueue), mergeMap((action) => this.sqsService.saveQueue(action.name).then(() => sqsQueueListActions.addQueueSuccess()))));
        this.purgeQueue$ = createEffect(() => this.actions$.pipe(ofType(sqsQueueListActions.purgeQueue), mergeMap((action) => this.sqsService.purgeQueue(action.queueUrl).then(() => sqsQueueListActions.addQueueSuccess()))));
        this.deleteQueue$ = createEffect(() => this.actions$.pipe(ofType(sqsQueueListActions.deleteQueue), mergeMap((action) => this.sqsService.deleteQueue(action.queueUrl).then(() => sqsQueueListActions.addQueueSuccess()))));
    }

    static {
        this.\u0275fac = function SqsQueueListEffects_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _SqsQueueListEffects)(\u0275\u0275inject(Actions), \u0275\u0275inject(SqsService));
        };
    }
    static {
        this.\u0275prov = /* @__PURE__ */ \u0275\u0275defineInjectable({token: _SqsQueueListEffects, factory: _SqsQueueListEffects.\u0275fac});
    }
};

// src/app/modules/sqs/queue-detail/state/sqs-queue-detail.actions.ts
var sqsQueueDetailsActions = {
    initialize: createAction("[sqs-queue-details] initialize"),
    // Load details
    loadDetails: createAction("[sqs-queue-details] Load Queues Details", props()),
    loadDetailsSuccess: createAction("[sqs-queue-details] Load Queues Details Success", props()),
    loadDetailsFailure: createAction("[sqs-queue-details] Load Queues Details Error", props()),
    // Load attributes
    loadAttributes: createAction("[sqs-queue-details] Load Queues Attributes", props()),
    loadAttributesSuccess: createAction("[sqs-queue-details] Load Queues Attributes Success", props()),
    loadAttributesFailure: createAction("[sqs-queue-details] Load Queues Attributes Error", props())
};

// src/app/modules/sqs/queue-detail/state/sqs-queue-detail.reducer.ts
var sqsQueueDetailsFeatureKey = "sqs-queue-details";
var initialState2 = {
    sqsQueueDetails: {},
    loading: false,
    error: {}
};
var sqsQueueDetailReducer = createReducer(
    initialState2,
    // Initialize
    on(sqsQueueDetailsActions.initialize, (state) => __spreadProps(__spreadValues({}, state), {loading: false})),
    // Queue list
    on(sqsQueueDetailsActions.loadDetails, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(sqsQueueDetailsActions.loadDetailsSuccess, (state, {queueDetails}) => __spreadProps(__spreadValues({}, state), {sqsQueueDetails: queueDetails, loading: false})),
    on(sqsQueueDetailsActions.loadDetailsFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false}))
);

// src/app/modules/sqs/queue-detail/state/sqs-queue-detail.selectors.ts
var selectQueueDetailsFeature = createFeatureSelector(sqsQueueDetailsFeatureKey);
var selectDetails = createSelector(selectQueueDetailsFeature, (state) => state?.sqsQueueDetails);
var selectError = createSelector(selectQueueDetailsFeature, (state) => state?.error);

// src/app/modules/sqs/queue-detail/sqs-queue-detail.component.ts
function SqsQueueDetailComponent_div_19_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "div")(1, "mat-grid-list", 16)(2, "mat-grid-tile", 8)(3, "div", 17)(4, "mat-list")(5, "mat-list-item", 18)(6, "p", 9);
        \u0275\u0275text(7, "Name: ");
        \u0275\u0275elementEnd();
        \u0275\u0275elementStart(8, "p", 10);
        \u0275\u0275text(9);
        \u0275\u0275elementEnd()();
        \u0275\u0275elementStart(10, "mat-list-item", 18)(11, "p", 9);
        \u0275\u0275text(12, "ARN: ");
        \u0275\u0275elementEnd();
        \u0275\u0275elementStart(13, "p", 10);
        \u0275\u0275text(14);
        \u0275\u0275elementEnd()();
        \u0275\u0275elementStart(15, "mat-list-item", 18)(16, "p", 9);
        \u0275\u0275text(17, "URL: ");
        \u0275\u0275elementEnd();
        \u0275\u0275elementStart(18, "p", 10);
        \u0275\u0275text(19);
        \u0275\u0275elementEnd()()()()();
        \u0275\u0275elementStart(20, "mat-grid-tile", 8)(21, "div", 19)(22, "mat-list")(23, "mat-list-item", 18)(24, "p", 9);
        \u0275\u0275text(25, "Visibility Timeout (s): ");
        \u0275\u0275elementEnd();
        \u0275\u0275elementStart(26, "p", 10);
        \u0275\u0275text(27);
        \u0275\u0275elementEnd()();
        \u0275\u0275elementStart(28, "mat-list-item", 18)(29, "p", 9);
        \u0275\u0275text(30, "Delay (s): ");
        \u0275\u0275elementEnd();
        \u0275\u0275elementStart(31, "p", 10);
        \u0275\u0275text(32);
        \u0275\u0275elementEnd()();
        \u0275\u0275elementStart(33, "mat-list-item", 18)(34, "p", 9);
        \u0275\u0275text(35, "Max Message Size (kB): ");
        \u0275\u0275elementEnd();
        \u0275\u0275elementStart(36, "p", 10);
        \u0275\u0275text(37);
        \u0275\u0275elementEnd()()()()();
        \u0275\u0275elementStart(38, "mat-grid-tile", 8)(39, "div", 19)(40, "mat-list")(41, "mat-list-item", 18)(42, "p", 9);
        \u0275\u0275text(43, "Retention Period (s): ");
        \u0275\u0275elementEnd();
        \u0275\u0275elementStart(44, "p", 10);
        \u0275\u0275text(45);
        \u0275\u0275elementEnd()();
        \u0275\u0275elementStart(46, "mat-list-item", 18)(47, "p", 9);
        \u0275\u0275text(48, "Message Count: ");
        \u0275\u0275elementEnd();
        \u0275\u0275elementStart(49, "p", 10);
        \u0275\u0275text(50);
        \u0275\u0275elementEnd()();
        \u0275\u0275elementStart(51, "mat-list-item", 18)(52, "p", 9);
        \u0275\u0275text(53, "Total Size (kB): ");
        \u0275\u0275elementEnd();
        \u0275\u0275elementStart(54, "p", 10);
        \u0275\u0275text(55);
        \u0275\u0275elementEnd()()()()();
        \u0275\u0275elementStart(56, "mat-grid-tile", 8)(57, "div", 19)(58, "mat-list")(59, "mat-list-item", 18)(60, "p", 9);
        \u0275\u0275text(61, "Created: ");
        \u0275\u0275elementEnd();
        \u0275\u0275elementStart(62, "p", 10);
        \u0275\u0275text(63);
        \u0275\u0275pipe(64, "date");
        \u0275\u0275elementEnd()();
        \u0275\u0275elementStart(65, "mat-list-item", 18)(66, "p", 9);
        \u0275\u0275text(67, "Modified: ");
        \u0275\u0275elementEnd();
        \u0275\u0275elementStart(68, "p", 10);
        \u0275\u0275text(69);
        \u0275\u0275pipe(70, "date");
        \u0275\u0275elementEnd()();
        \u0275\u0275element(71, "mat-list-item", 18);
        \u0275\u0275elementEnd()()()()();
    }
    if (rf & 2) {
        const queueDetails_r1 = ctx.ngIf;
        \u0275\u0275advance(2);
        \u0275\u0275property("colspan", 2)("rowspan", 1);
        \u0275\u0275advance(7);
        \u0275\u0275textInterpolate(queueDetails_r1.queueName);
        \u0275\u0275advance(5);
        \u0275\u0275textInterpolate(queueDetails_r1.queueArn);
        \u0275\u0275advance(5);
        \u0275\u0275textInterpolate(queueDetails_r1.queueUrl);
        \u0275\u0275advance();
        \u0275\u0275property("colspan", 1)("rowspan", 1);
        \u0275\u0275advance(7);
        \u0275\u0275textInterpolate(queueDetails_r1.visibilityTimeout);
        \u0275\u0275advance(5);
        \u0275\u0275textInterpolate(queueDetails_r1.delay);
        \u0275\u0275advance(5);
        \u0275\u0275textInterpolate(queueDetails_r1.maxMessageSize / 1024);
        \u0275\u0275advance();
        \u0275\u0275property("colspan", 1)("rowspan", 1);
        \u0275\u0275advance(7);
        \u0275\u0275textInterpolate(queueDetails_r1.retentionPeriod);
        \u0275\u0275advance(5);
        \u0275\u0275textInterpolate(queueDetails_r1.messageCount);
        \u0275\u0275advance(5);
        \u0275\u0275textInterpolate((queueDetails_r1.size / 1024).toFixed(0));
        \u0275\u0275advance();
        \u0275\u0275property("colspan", 1)("rowspan", 1);
        \u0275\u0275advance(7);
        \u0275\u0275textInterpolate(\u0275\u0275pipeBind2(64, 19, queueDetails_r1.created, "yyyy-MM-dd HH:mm:ss"));
        \u0275\u0275advance(6);
        \u0275\u0275textInterpolate(\u0275\u0275pipeBind2(70, 22, queueDetails_r1.modified, "yyyy-MM-dd HH:mm:ss"));
    }
}

var SqsQueueDetailComponent = class _SqsQueueDetailComponent {
    constructor(snackBar, route, location, store) {
        this.snackBar = snackBar;
        this.route = route;
        this.location = location;
        this.store = store;
        this.lastUpdate = /* @__PURE__ */ new Date();
        this.queueArn = "";
        this.queueDetails$ = this.store.select(selectDetails);
        this.queueDetailsError$ = this.store.select(selectError);
        this.store.dispatch(sqsQueueDetailsActions.initialize());
    }

    ngOnInit() {
        this.sub = this.route.params.subscribe((params) => {
            this.queueArn = params["queueArn"];
            this.store.dispatch(sqsQueueDetailsActions.loadDetails({queueArn: this.queueArn}));
        });
        this.queueDetailsError$.subscribe((msg) => {
            if (msg.length) {
                this.snackBar.open("ErrorMessage: " + msg.toString());
            }
        });
    }

    ngOnDestroy() {
        this.sub.unsubscribe();
    }

    refresh() {
        this.store.dispatch(sqsQueueDetailsActions.loadDetails({queueArn: this.queueArn}));
        this.lastUpdate = /* @__PURE__ */ new Date();
    }

    back() {
        this.location.back();
    }

    save() {
    }

    close() {
        this.location.back();
    }

    static {
        this.\u0275fac = function SqsQueueDetailComponent_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _SqsQueueDetailComponent)(\u0275\u0275directiveInject(MatSnackBar), \u0275\u0275directiveInject(ActivatedRoute), \u0275\u0275directiveInject(Location), \u0275\u0275directiveInject(Store));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _SqsQueueDetailComponent,
            selectors: [["sqs-queue-detail-component"]],
            decls: 60,
            vars: 21,
            consts: [["appearance", "outlined", 2, "margin", "3px"], ["aria-label", "Back", "mat-icon-button", "", 1, "head-buttons-left", 3, "click"], [1, "fill-remaining-space"], ["aria-label", "Refresh", "mat-icon-button", "", 3, "click"], [4, "ngIf"], ["appearance", "outlined", 2, "margin-top", "5px"], ["label", "Attributes"], ["cols", "1"], [3, "colspan", "rowspan"], ["matListItemTitle", ""], ["matListItemLine", ""], ["label", "Tags"], ["label", "Access Policy"], ["align", "end"], ["mat-button", "", 3, "click"], [1, "footer"], ["cols", "5", "rowHeight", "300px"], [2, "width", "100%", "display", "flex", "align-items", "flex-start", "align-content", "flex-start", "justify-content", "flex-start"], [2, "height", "80px"], [2, "width", "100%", "display", "flex", "align-items", "flex-start", "align-content", "flex-start"]],
            template: function SqsQueueDetailComponent_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "mat-card", 0)(1, "mat-card-header")(2, "span")(3, "button", 1);
                    \u0275\u0275listener("click", function SqsQueueDetailComponent_Template_button_click_3_listener() {
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
                    \u0275\u0275listener("click", function SqsQueueDetailComponent_Template_button_click_11_listener() {
                        return ctx.refresh();
                    });
                    \u0275\u0275elementStart(12, "mat-icon");
                    \u0275\u0275text(13, "refresh");
                    \u0275\u0275elementEnd()()()();
                    \u0275\u0275elementStart(14, "mat-card", 0)(15, "mat-card-header")(16, "mat-card-title");
                    \u0275\u0275text(17, "Details");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(18, "mat-card-content");
                    \u0275\u0275template(19, SqsQueueDetailComponent_div_19_Template, 72, 25, "div", 4);
                    \u0275\u0275pipe(20, "async");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(21, "mat-card", 5)(22, "mat-card-header")(23, "mat-card-title");
                    \u0275\u0275text(24, "Attributes");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(25, "mat-card-content")(26, "mat-tab-group")(27, "mat-tab", 6)(28, "mat-grid-list", 7)(29, "mat-grid-tile", 8)(30, "mat-list")(31, "mat-list-item")(32, "span", 9);
                    \u0275\u0275text(33, "Available: ");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(34, "span", 10);
                    \u0275\u0275text(35);
                    \u0275\u0275pipe(36, "async");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(37, "mat-list-item")(38, "span", 9);
                    \u0275\u0275text(39, "Invisible: ");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(40, "span", 10);
                    \u0275\u0275text(41);
                    \u0275\u0275pipe(42, "async");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(43, "mat-list-item")(44, "span", 9);
                    \u0275\u0275text(45, "Delayed: ");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(46, "span", 10);
                    \u0275\u0275text(47);
                    \u0275\u0275pipe(48, "async");
                    \u0275\u0275elementEnd()()()()()();
                    \u0275\u0275elementStart(49, "mat-tab", 11);
                    \u0275\u0275text(50, " Tags ");
                    \u0275\u0275elementEnd();
                    \u0275\u0275element(51, "mat-tab", 12);
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(52, "mat-card-actions", 13)(53, "button", 14);
                    \u0275\u0275listener("click", function SqsQueueDetailComponent_Template_button_click_53_listener() {
                        return ctx.close();
                    });
                    \u0275\u0275text(54, "Close");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(55, "button", 14);
                    \u0275\u0275listener("click", function SqsQueueDetailComponent_Template_button_click_55_listener() {
                        return ctx.save();
                    });
                    \u0275\u0275text(56, "Save");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(57, "div", 15);
                    \u0275\u0275text(58);
                    \u0275\u0275pipe(59, "date");
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    let tmp_0_0;
                    let tmp_4_0;
                    let tmp_5_0;
                    let tmp_6_0;
                    \u0275\u0275advance(8);
                    \u0275\u0275textInterpolate1("Queue: ", (tmp_0_0 = \u0275\u0275pipeBind1(9, 8, ctx.queueDetails$)) == null ? null : tmp_0_0.queueName, "");
                    \u0275\u0275advance(11);
                    \u0275\u0275property("ngIf", \u0275\u0275pipeBind1(20, 10, ctx.queueDetails$));
                    \u0275\u0275advance(10);
                    \u0275\u0275property("colspan", 1)("rowspan", 1);
                    \u0275\u0275advance(6);
                    \u0275\u0275textInterpolate((tmp_4_0 = \u0275\u0275pipeBind1(36, 12, ctx.queueDetails$)) == null ? null : tmp_4_0.available);
                    \u0275\u0275advance(6);
                    \u0275\u0275textInterpolate((tmp_5_0 = \u0275\u0275pipeBind1(42, 14, ctx.queueDetails$)) == null ? null : tmp_5_0.invisible);
                    \u0275\u0275advance(6);
                    \u0275\u0275textInterpolate((tmp_6_0 = \u0275\u0275pipeBind1(48, 16, ctx.queueDetails$)) == null ? null : tmp_6_0.delayed);
                    \u0275\u0275advance(11);
                    \u0275\u0275textInterpolate1(" Last update: ", \u0275\u0275pipeBind2(59, 18, ctx.lastUpdate, "HH:mm:ss"), " ");
                }
            },
            dependencies: [MatCard, MatCardHeader, MatCardContent, MatCardActions, MatCardTitle, MatIcon, MatIconButton, MatListItem, MatGridTile, MatGridList, MatList, MatTabGroup, MatTab, MatButton, NgIf, DatePipe, AsyncPipe],
            styles: ["\n\n.head-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  justify-content: flex-end;\n}\n.fill-remaining-space[_ngcontent-%COMP%] {\n  flex: 1 1 auto;\n}\n.footer[_ngcontent-%COMP%] {\n  display: flex;\n  width: 50%;\n  font-size: x-small;\n  color: black;\n  padding-left: 15px;\n}\n/*# sourceMappingURL=sqs-queue-detail.component.css.map */"]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(SqsQueueDetailComponent, {
        className: "SqsQueueDetailComponent",
        filePath: "src/app/modules/sqs/queue-detail/sqs-queue-detail.component.ts",
        lineNumber: 16
    });
})();

// src/app/modules/sqs/message-list/view-message/view-message.component.ts
var ViewMessageComponentDialog = class _ViewMessageComponentDialog {
    constructor(dialogRef, data) {
        this.dialogRef = dialogRef;
        this.data = data;
        this.body = "";
        this.messageId = "";
        this.prettyPrint = true;
        this.message = data.message;
        if (this.prettyPrint) {
            this.body = JSON.stringify(JSON.parse(data.message.body), null, 2);
        } else {
            this.body = data.message.body;
        }
        this.messageId = this.message?.messageId;
    }

    ngOnInit() {
    }

    sendMessage() {
        this.dialogRef.close(true);
    }

    changePrettyPrint(event) {
        if (this.message.body !== void 0) {
            if (event.checked) {
                this.body = JSON.stringify(JSON.parse(this.message?.body), null, 2);
            } else {
                this.body = this.message?.body;
            }
        }
    }

    close() {
        this.dialogRef.close(false);
    }

    static {
        this.\u0275fac = function ViewMessageComponentDialog_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _ViewMessageComponentDialog)(\u0275\u0275directiveInject(MatDialogRef), \u0275\u0275directiveInject(MAT_DIALOG_DATA));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _ViewMessageComponentDialog,
            selectors: [["sqs-edit-message-dialog"]],
            standalone: true,
            features: [\u0275\u0275StandaloneFeature],
            decls: 13,
            vars: 3,
            consts: [["cdkDragHandle", "", "cdkDragRootElement", ".cdk-overlay-pane", "cdkcdkDrag", "", "mat-dialog-title", ""], ["labelPosition", "before", 3, "change", "checked"], [1, "mat-typography"], [2, "width", "100%", "height", "100%"], ["cdkAutosizeMinRows", "20", "cdkTextareaAutosize", "", "matInput", "", "placeholder", "Message", "readonly", "", 2, "width", "100%", "height", "100%", 3, "ngModelChange", "ngModel"], ["align", "end"], ["mat-button", "", "mat-dialog-close", ""]],
            template: function ViewMessageComponentDialog_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "h2", 0);
                    \u0275\u0275text(1);
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(2, "mat-dialog-actions")(3, "mat-slide-toggle", 1);
                    \u0275\u0275listener("change", function ViewMessageComponentDialog_Template_mat_slide_toggle_change_3_listener($event) {
                        return ctx.changePrettyPrint($event);
                    });
                    \u0275\u0275text(4, " Pretty Print: ");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(5, "mat-dialog-content", 2)(6, "mat-form-field", 3)(7, "mat-label");
                    \u0275\u0275text(8, "Message:");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(9, "textarea", 4);
                    \u0275\u0275twoWayListener("ngModelChange", function ViewMessageComponentDialog_Template_textarea_ngModelChange_9_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.body, $event) || (ctx.body = $event);
                        return $event;
                    });
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(10, "mat-dialog-actions", 5)(11, "button", 6);
                    \u0275\u0275text(12, "Close");
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    \u0275\u0275advance();
                    \u0275\u0275textInterpolate1("SQS message: ", ctx.messageId, "");
                    \u0275\u0275advance(2);
                    \u0275\u0275property("checked", ctx.prettyPrint);
                    \u0275\u0275advance(6);
                    \u0275\u0275twoWayProperty("ngModel", ctx.body);
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
                CdkDragHandle,
                CdkTextareaAutosize,
                MatSlideToggle
            ],
            styles: ["\n\n.full-screen-modal[_ngcontent-%COMP%]   .mat-dialog-container[_ngcontent-%COMP%] {\n  padding: 1em;\n  width: 90%;\n  height: 80%;\n  resize: both;\n  overflow: auto;\n  max-width: unset !important;\n  max-height: unset !important;\n  position: absolute !important;\n}\n/*# sourceMappingURL=view-message.component.css.map */"]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(ViewMessageComponentDialog, {
        className: "ViewMessageComponentDialog",
        filePath: "src/app/modules/sqs/message-list/view-message/view-message.component.ts",
        lineNumber: 41
    });
})();

// src/app/modules/sqs/message-list/state/sqs-message-list.actions.ts
var sqsMessageListActions = {
    initialize: createAction("[sqs-message-list] initialize"),
    // Load message
    loadMessages: createAction("[sqs-message-list] Load messages", props()),
    loadMessagesSuccess: createAction("[sqs-message-list] Load messages success", props()),
    loadMessagesFailure: createAction("[sqs-message-list] Load messages error", props()),
    // Add message
    addMessage: createAction("[sqs-message-list] Add message", props()),
    addMessageSuccess: createAction("[sqs-message-list] Add message success"),
    addMessageFailure: createAction("[sqs-message-list] Add message error", props()),
    // Delete message
    deleteMessage: createAction("[sqs-message-list] Delete message", props()),
    deleteMessageSuccess: createAction("[sqs-message-list] Delete message success"),
    deleteMessageFailure: createAction("[sqs-message-list] Delete message error", props())
};

// src/app/modules/sqs/message-list/state/sqs-message-list.reducer.ts
var sqsMessageListFeatureKey = "sqs-message-list";
var initialState3 = {
    listMessageCountersResponse: {Total: 0, Messages: []},
    prefix: "",
    pageSize: 10,
    pageIndex: 0,
    loading: false,
    sortColumns: [{column: "_id", sortDirection: -1}],
    error: {}
};
var sqsMessageListReducer = createReducer(
    initialState3,
    // Initialize
    on(sqsMessageListActions.initialize, (state) => __spreadProps(__spreadValues({}, state), {pageIndex: 0, pageSize: 10, loading: true})),
    // Load message list
    on(sqsMessageListActions.loadMessages, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(sqsMessageListActions.loadMessagesSuccess, (state, {messages}) => __spreadProps(__spreadValues({}, state), {
        listMessageCountersResponse: messages,
        loading: false
    })),
    on(sqsMessageListActions.loadMessagesFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false})),
    // Add message
    on(sqsMessageListActions.addMessage, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(sqsMessageListActions.addMessageSuccess, (state) => __spreadProps(__spreadValues({}, state), {loading: false})),
    on(sqsMessageListActions.addMessageFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false})),
    // Delete message
    on(sqsMessageListActions.deleteMessage, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(sqsMessageListActions.deleteMessageSuccess, (state) => __spreadProps(__spreadValues({}, state), {loading: false})),
    on(sqsMessageListActions.deleteMessageFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false}))
);

// src/app/modules/sqs/message-list/state/sqs-message-list.selectors.ts
var selectMessageListFeature = createFeatureSelector(sqsMessageListFeatureKey);
var selectIsLoading2 = createSelector(selectMessageListFeature, (state) => state.loading);
var selectPrefix2 = createSelector(selectMessageListFeature, (state) => state?.prefix);
var selectPageSize2 = createSelector(selectMessageListFeature, (state) => state?.pageSize);
var selectPageIndex2 = createSelector(selectMessageListFeature, (state) => state?.pageIndex);
var selectSortColumns2 = createSelector(selectMessageListFeature, (state) => state?.sortColumns);
var selectMessageCounters = createSelector(selectMessageListFeature, (state) => state?.listMessageCountersResponse);

// src/app/modules/sqs/message-list/sqs-message-list.component.ts
var _c02 = () => [];

function SqsMessageListComponent_button_21_Template(rf, ctx) {
    if (rf & 1) {
        const _r1 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "button", 13);
        \u0275\u0275listener("click", function SqsMessageListComponent_button_21_Template_button_click_0_listener() {
            \u0275\u0275restoreView(_r1);
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.setPrefix());
        });
        \u0275\u0275elementStart(1, "mat-icon", 14);
        \u0275\u0275text(2, "search");
        \u0275\u0275elementEnd()();
    }
}

function SqsMessageListComponent_button_22_Template(rf, ctx) {
    if (rf & 1) {
        const _r3 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "button", 13);
        \u0275\u0275listener("click", function SqsMessageListComponent_button_22_Template_button_click_0_listener() {
            \u0275\u0275restoreView(_r3);
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.unsetPrefix());
        });
        \u0275\u0275elementStart(1, "mat-icon", 14);
        \u0275\u0275text(2, "close");
        \u0275\u0275elementEnd()();
    }
}

function SqsMessageListComponent_div_24_th_3_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 29);
        \u0275\u0275text(1, "Message ID ");
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        \u0275\u0275property("matTooltipPositionAtOrigin", "left");
    }
}

function SqsMessageListComponent_div_24_td_4_Template(rf, ctx) {
    if (rf & 1) {
        const _r5 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "td", 30)(1, "mat-nav-list")(2, "a", 31);
        \u0275\u0275listener("click", function SqsMessageListComponent_div_24_td_4_Template_a_click_2_listener() {
            const element_r6 = \u0275\u0275restoreView(_r5).$implicit;
            const ctx_r1 = \u0275\u0275nextContext(2);
            return \u0275\u0275resetView(ctx_r1.editMessage(element_r6));
        });
        \u0275\u0275text(3);
        \u0275\u0275elementEnd()()();
    }
    if (rf & 2) {
        const element_r6 = ctx.$implicit;
        \u0275\u0275advance(3);
        \u0275\u0275textInterpolate1(" ", element_r6.messageId, "");
    }
}

function SqsMessageListComponent_div_24_th_6_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 32);
        \u0275\u0275text(1, "Created ");
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        \u0275\u0275property("matTooltipPositionAtOrigin", "left");
    }
}

function SqsMessageListComponent_div_24_td_7_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 30);
        \u0275\u0275text(1);
        \u0275\u0275pipe(2, "date");
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r7 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", \u0275\u0275pipeBind2(2, 1, element_r7.created, "dd-MM-yyyy HH:mm:ss"), "");
    }
}

function SqsMessageListComponent_div_24_th_9_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 33);
        \u0275\u0275text(1, "Modified ");
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        \u0275\u0275property("matTooltipPositionAtOrigin", "left");
    }
}

function SqsMessageListComponent_div_24_td_10_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 30);
        \u0275\u0275text(1);
        \u0275\u0275pipe(2, "date");
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r8 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", \u0275\u0275pipeBind2(2, 1, element_r8.modified, "dd-MM-yyyy HH:mm:ss"), "");
    }
}

function SqsMessageListComponent_div_24_th_12_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 34);
        \u0275\u0275text(1, "Actions");
        \u0275\u0275elementEnd();
    }
}

function SqsMessageListComponent_div_24_td_13_Template(rf, ctx) {
    if (rf & 1) {
        const _r9 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "td", 30)(1, "button", 35);
        \u0275\u0275listener("click", function SqsMessageListComponent_div_24_td_13_Template_button_click_1_listener() {
            const row_r10 = \u0275\u0275restoreView(_r9).$implicit;
            const ctx_r1 = \u0275\u0275nextContext(2);
            return \u0275\u0275resetView(ctx_r1.deleteMessage(row_r10.receiptHandle));
        });
        \u0275\u0275elementStart(2, "mat-icon");
        \u0275\u0275text(3, "delete");
        \u0275\u0275elementEnd()()();
    }
    if (rf & 2) {
        \u0275\u0275advance();
        \u0275\u0275property("matTooltipPositionAtOrigin", "left");
    }
}

function SqsMessageListComponent_div_24_tr_14_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 36);
    }
}

function SqsMessageListComponent_div_24_tr_15_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 37);
    }
}

function SqsMessageListComponent_div_24_tr_16_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "tr", 38)(1, "td", 39);
        \u0275\u0275text(2, " No data matching the filter. ");
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const ctx_r1 = \u0275\u0275nextContext(2);
        \u0275\u0275advance();
        \u0275\u0275attribute("colspan", ctx_r1.columns.length);
    }
}

function SqsMessageListComponent_div_24_Template(rf, ctx) {
    if (rf & 1) {
        const _r4 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "div", 15)(1, "table", 16);
        \u0275\u0275listener("matSortChange", function SqsMessageListComponent_div_24_Template_table_matSortChange_1_listener($event) {
            \u0275\u0275restoreView(_r4);
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.sortChange($event));
        });
        \u0275\u0275elementContainerStart(2, 17);
        \u0275\u0275template(3, SqsMessageListComponent_div_24_th_3_Template, 2, 1, "th", 18)(4, SqsMessageListComponent_div_24_td_4_Template, 4, 1, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(5, 20);
        \u0275\u0275template(6, SqsMessageListComponent_div_24_th_6_Template, 2, 1, "th", 21)(7, SqsMessageListComponent_div_24_td_7_Template, 3, 4, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(8, 22);
        \u0275\u0275template(9, SqsMessageListComponent_div_24_th_9_Template, 2, 1, "th", 23)(10, SqsMessageListComponent_div_24_td_10_Template, 3, 4, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(11, 24);
        \u0275\u0275template(12, SqsMessageListComponent_div_24_th_12_Template, 2, 0, "th", 25)(13, SqsMessageListComponent_div_24_td_13_Template, 4, 1, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275template(14, SqsMessageListComponent_div_24_tr_14_Template, 1, 0, "tr", 26)(15, SqsMessageListComponent_div_24_tr_15_Template, 1, 0, "tr", 27)(16, SqsMessageListComponent_div_24_tr_16_Template, 3, 1, "tr", 28);
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const messageCounters_r11 = ctx.ngIf;
        const ctx_r1 = \u0275\u0275nextContext();
        \u0275\u0275advance();
        \u0275\u0275property("dataSource", messageCounters_r11.Messages);
        \u0275\u0275advance(13);
        \u0275\u0275property("matHeaderRowDef", ctx_r1.columns);
        \u0275\u0275advance();
        \u0275\u0275property("matRowDefColumns", ctx_r1.columns);
    }
}

var SqsMessageListComponent = class _SqsMessageListComponent {
    constructor(snackBar, sqsService, route, dialog, state, location, store, actionsSubj$) {
        this.snackBar = snackBar;
        this.sqsService = sqsService;
        this.route = route;
        this.dialog = dialog;
        this.state = state;
        this.location = location;
        this.store = store;
        this.actionsSubj$ = actionsSubj$;
        this.lastUpdate = /* @__PURE__ */ new Date();
        this.pageSize$ = this.store.select(selectPageSize);
        this.pageIndex$ = this.store.select(selectPageIndex);
        this.prefix$ = this.store.select(selectPrefix);
        this.listMessageCountersResponse$ = this.store.select(selectMessageCounters);
        this.columns = ["messageId", "created", "modified", "actions"];
        this.pageSizeOptions = [5, 10, 20, 50, 100];
        this.hidePageSize = false;
        this.showPageSizeOptions = true;
        this.showFirstLastButtons = true;
        this.disabled = false;
        this.pageEvent = {length: 0, pageIndex: 0, pageSize: 0};
        this.queueArn = "";
        this.queueUrl = "";
        this.queueName = "";
        this.prefixValue = "";
        this.prefixSet = false;
        this.sortColumns = [{column: "created", sortDirection: 1}];
        this.actionsSubj$.pipe(filter((action) => action.type === sqsMessageListActions.addMessageSuccess.type)).subscribe(() => {
            this.loadMessages();
        });
        this.actionsSubj$.pipe(filter((action) => action.type === sqsMessageListActions.deleteMessageSuccess.type)).subscribe(() => {
            this.snackBar.open("Message send, queueArn: " + this.queueArn, "Done", {duration: 5e3});
            this.loadMessages();
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
        this.routerSubscription = this.route.params.subscribe((params) => {
            this.queueArn = decodeURI(params["queueArn"]);
        });
        this.queueName = this.queueArn.substring(this.queueArn.lastIndexOf(":") + 1);
        this.sqsService.getQueueUrl(this.queueName).then((data) => {
            this.queueUrl = data.QueueUrl;
        }).catch((error) => console.error(error)).finally(() => {
            this.sqsService.cleanup();
        });
        this.loadMessages();
        this.updateSubscription = interval(6e4).subscribe(() => this.loadMessages());
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

    setPrefix() {
        this.prefixSet = true;
        this.state.value["sqs-message-list"].pageIndex = 0;
        this.state.value["sqs-message-list"].prefix = this.prefixValue;
        this.loadMessages();
    }

    unsetPrefix() {
        this.prefixValue = "";
        this.prefixSet = false;
        this.state.value["sqs-message-list"].prefix = "";
        this.loadMessages();
    }

    sortChange(sortState) {
        this.sortColumns = [];
        if (sortState.direction === "asc") {
            this.sortColumns.push({column: sortState.active, sortDirection: 1});
        } else {
            this.sortColumns.push({column: sortState.active, sortDirection: -1});
        }
        this.state.value["sqs-message-list"].sortColumns = this.sortColumns;
        this.loadMessages();
    }

    handlePageEvent(e) {
        this.pageEvent = e;
        this.loadMessages();
    }

    loadMessages() {
        this.lastUpdate = /* @__PURE__ */ new Date();
        this.store.dispatch(sqsMessageListActions.loadMessages({
            queueArn: this.queueArn,
            prefix: this.state.value["sqs-message-list"].prefix,
            pageSize: this.state.value["sqs-message-list"].pageSize,
            pageIndex: this.state.value["sqs-message-list"].pageIndex,
            sortColumns: this.state.value["sqs-message-list"].sortColumns
        }));
    }

    editMessage(message) {
        const dialogConfig = new MatDialogConfig();
        dialogConfig.disableClose = true;
        dialogConfig.autoFocus = true;
        dialogConfig.data = {message};
        dialogConfig.maxWidth = "100vw";
        dialogConfig.maxHeight = "90vh";
        dialogConfig.panelClass = "full-screen-modal";
        dialogConfig.width = "70%";
        this.dialog.open(ViewMessageComponentDialog, dialogConfig).afterClosed().subscribe(() => {
        });
    }

    sendMessage() {
        const dialogConfig = new MatDialogConfig();
        dialogConfig.disableClose = true;
        dialogConfig.autoFocus = true;
        dialogConfig.data = {queueUrl: this.queueUrl};
        dialogConfig.maxWidth = "100vw";
        dialogConfig.maxHeight = "100vh";
        dialogConfig.width = "90%";
        dialogConfig.panelClass = "full-screen-modal";
        this.dialog.open(SendMessageComponentDialog, dialogConfig).afterClosed().subscribe((result) => {
            if (result) {
                this.sqsService.sendMessage(this.queueUrl, result).then(() => {
                    this.loadMessages();
                    this.snackBar.open("Message send, queueArn: " + this.queueArn, "Done", {duration: 5e3});
                });
            }
        });
    }

    deleteMessage(receiptHandle) {
        this.lastUpdate = /* @__PURE__ */ new Date();
        this.store.dispatch(sqsMessageListActions.deleteMessage({
            queueUrl: this.queueUrl,
            receiptHandle
        }));
    }

    static {
        this.\u0275fac = function SqsMessageListComponent_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _SqsMessageListComponent)(\u0275\u0275directiveInject(MatSnackBar), \u0275\u0275directiveInject(SqsService), \u0275\u0275directiveInject(ActivatedRoute), \u0275\u0275directiveInject(MatDialog), \u0275\u0275directiveInject(State), \u0275\u0275directiveInject(Location), \u0275\u0275directiveInject(Store), \u0275\u0275directiveInject(ActionsSubject));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _SqsMessageListComponent,
            selectors: [["sqs-message-list"]],
            decls: 32,
            vars: 22,
            consts: [["appearance", "outlined", 2, "margin", "3px"], ["aria-label", "Back", "mat-icon-button", "", 1, "head-buttons-left", 3, "click"], [1, "fill-remaining-space"], ["aria-label", "Refresh", "mat-icon-button", "", 3, "click"], ["appearance", "outlined", 2, "margin", "-10px"], ["align", "start"], [2, "width", "100%"], ["matInput", "", "name", "search", "placeholder", "Search", "type", "text", 3, "ngModelChange", "ngModel"], ["mat-icon-button", "", "matSuffix", "", "style", "float: right", 3, "click", 4, "ngIf"], [1, "table-container"], ["class", "row", 4, "ngIf"], ["aria-label", "Select page", 2, "width", "99%", "margin-left", "15px", 3, "page", "disabled", "hidePageSize", "length", "pageIndex", "pageSizeOptions", "pageSize", "showFirstLastButtons"], [1, "footer"], ["mat-icon-button", "", "matSuffix", "", 2, "float", "right", 3, "click"], ["matSuffix", ""], [1, "row"], ["mat-table", "", "matSort", "", 1, "mat-elevation-z8", "queue-table", 3, "matSortChange", "dataSource"], ["matColumnDef", "messageId"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Message ID", "sortActionDescription", "Sort by id", 3, "matTooltipPositionAtOrigin", 4, "matHeaderCellDef"], ["mat-cell", "", 4, "matCellDef"], ["matColumnDef", "created"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Created", "sortActionDescription", "Sort by created", 3, "matTooltipPositionAtOrigin", 4, "matHeaderCellDef"], ["matColumnDef", "modified"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Modified", "sortActionDescription", "Sort by modified", 3, "matTooltipPositionAtOrigin", 4, "matHeaderCellDef"], ["matColumnDef", "actions"], ["mat-header-cell", "", "style", "width:80px", 4, "matHeaderCellDef"], ["mat-header-row", "", 4, "matHeaderRowDef"], ["mat-row", "", 4, "matRowDef", "matRowDefColumns"], ["class", "mat-row", 4, "matNoDataRow"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Message ID", "sortActionDescription", "Sort by id", 3, "matTooltipPositionAtOrigin"], ["mat-cell", ""], ["mat-list-item", "", 3, "click"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Created", "sortActionDescription", "Sort by created", 3, "matTooltipPositionAtOrigin"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Modified", "sortActionDescription", "Sort by modified", 3, "matTooltipPositionAtOrigin"], ["mat-header-cell", "", 2, "width", "80px"], ["aria-label", "Delete", "mat-icon-button", "", "matTooltip", "Delete the message", 3, "click", "matTooltipPositionAtOrigin"], ["mat-header-row", ""], ["mat-row", ""], [1, "mat-row"], [1, "mat-cell", 2, "padding-left", "20px", "padding-top", "10px"]],
            template: function SqsMessageListComponent_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "mat-card", 0)(1, "mat-card-header")(2, "button", 1);
                    \u0275\u0275listener("click", function SqsMessageListComponent_Template_button_click_2_listener() {
                        return ctx.back();
                    });
                    \u0275\u0275elementStart(3, "mat-icon");
                    \u0275\u0275text(4, "arrow_back");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(5, "span", 2)(6, "h4");
                    \u0275\u0275text(7);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(8, "button", 3);
                    \u0275\u0275listener("click", function SqsMessageListComponent_Template_button_click_8_listener() {
                        return ctx.sendMessage();
                    });
                    \u0275\u0275elementStart(9, "mat-icon");
                    \u0275\u0275text(10, "add");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(11, "button", 3);
                    \u0275\u0275listener("click", function SqsMessageListComponent_Template_button_click_11_listener() {
                        return ctx.refresh();
                    });
                    \u0275\u0275elementStart(12, "mat-icon");
                    \u0275\u0275text(13, "refresh");
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(14, "mat-card-content")(15, "mat-card", 4)(16, "mat-card-actions", 5)(17, "mat-form-field", 6)(18, "mat-label");
                    \u0275\u0275text(19, "Prefix");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(20, "input", 7);
                    \u0275\u0275twoWayListener("ngModelChange", function SqsMessageListComponent_Template_input_ngModelChange_20_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.prefixValue, $event) || (ctx.prefixValue = $event);
                        return $event;
                    });
                    \u0275\u0275elementEnd();
                    \u0275\u0275template(21, SqsMessageListComponent_button_21_Template, 3, 0, "button", 8)(22, SqsMessageListComponent_button_22_Template, 3, 0, "button", 8);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(23, "div", 9);
                    \u0275\u0275template(24, SqsMessageListComponent_div_24_Template, 17, 3, "div", 10);
                    \u0275\u0275pipe(25, "async");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(26, "mat-paginator", 11);
                    \u0275\u0275pipe(27, "async");
                    \u0275\u0275pipe(28, "async");
                    \u0275\u0275pipe(29, "async");
                    \u0275\u0275listener("page", function SqsMessageListComponent_Template_mat_paginator_page_26_listener($event) {
                        return ctx.handlePageEvent($event);
                    });
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(30, "div", 12);
                    \u0275\u0275text(31);
                    \u0275\u0275elementEnd()()();
                }
                if (rf & 2) {
                    let tmp_7_0;
                    let tmp_10_0;
                    \u0275\u0275advance(7);
                    \u0275\u0275textInterpolate1("SQS Messages: ", ctx.queueName, "");
                    \u0275\u0275advance(13);
                    \u0275\u0275twoWayProperty("ngModel", ctx.prefixValue);
                    \u0275\u0275advance();
                    \u0275\u0275property("ngIf", !ctx.prefixSet);
                    \u0275\u0275advance();
                    \u0275\u0275property("ngIf", ctx.prefixSet);
                    \u0275\u0275advance(2);
                    \u0275\u0275property("ngIf", \u0275\u0275pipeBind1(25, 13, ctx.listMessageCountersResponse$));
                    \u0275\u0275advance(2);
                    \u0275\u0275property("disabled", ctx.disabled)("hidePageSize", ctx.hidePageSize)("length", (tmp_7_0 = \u0275\u0275pipeBind1(27, 15, ctx.listMessageCountersResponse$)) == null ? null : tmp_7_0.Total)("pageIndex", \u0275\u0275pipeBind1(28, 17, ctx.pageIndex$))("pageSizeOptions", ctx.showPageSizeOptions ? ctx.pageSizeOptions : \u0275\u0275pureFunction0(21, _c02))("pageSize", (tmp_10_0 = \u0275\u0275pipeBind1(29, 19, ctx.pageSize$)) !== null && tmp_10_0 !== void 0 ? tmp_10_0 : false)("showFirstLastButtons", ctx.showFirstLastButtons);
                    \u0275\u0275advance(5);
                    \u0275\u0275textInterpolate1(" Last update: ", ctx.lastUpdate, " ");
                }
            },
            dependencies: [MatCard, MatCardHeader, MatCardContent, MatCardActions, MatTable, MatHeaderCellDef, MatCellDef, MatColumnDef, MatIcon, MatHeaderCell, MatCell, MatHeaderRowDef, MatHeaderRow, MatSortHeader, MatRowDef, MatNoDataRow, MatIconButton, MatRow, MatPaginator, MatSort, MatTooltip, MatListItem, MatNavList, MatFormField, MatInput, MatLabel, MatSuffix, NgIf, DefaultValueAccessor, NgControlStatus, NgModel, DatePipe, AsyncPipe],
            styles: ["\n\n.message-table[_ngcontent-%COMP%] {\n  width: 100%;\n  height: 100%;\n}\n.table-container[_ngcontent-%COMP%] {\n  max-height: calc(100vh - 10px);\n  overflow: auto;\n}\n.head-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  justify-content: flex-end;\n}\n.footer-buttons[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: row;\n  align-items: end;\n  box-sizing: border-box;\n  min-height: 52px;\n  padding: 8px;\n  width: 50%;\n  justify-content: flex-end;\n}\n.fill-remaining-space[_ngcontent-%COMP%] {\n  flex: 1 1 auto;\n}\n.footer[_ngcontent-%COMP%] {\n  display: flex;\n  width: 50%;\n  font-size: x-small;\n  color: black;\n  padding-top: 15px;\n}\n.full-screen-modal[_ngcontent-%COMP%]   .mat-dialog-container[_ngcontent-%COMP%] {\n  padding: 1em;\n  width: 90%;\n  height: 80%;\n  resize: both;\n  overflow: auto;\n  max-width: unset !important;\n  max-height: unset !important;\n  position: absolute !important;\n}\n/*# sourceMappingURL=sqs-message-list.component.css.map */"]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(SqsMessageListComponent, {
        className: "SqsMessageListComponent",
        filePath: "src/app/modules/sqs/message-list/sqs-message-list.component.ts",
        lineNumber: 25
    });
})();

// src/app/modules/sqs/sqs-routing.module.ts
var routes = [
    {
        path: "",
        title: "SQSQueueList",
        component: SqsQueueListComponent
    },
    {
        path: "details/:queueArn",
        title: "SQSQueueDetails",
        component: SqsQueueDetailComponent
    },
    {
        path: "messages/:queueArn",
        title: "SQSQueueMessages",
        component: SqsMessageListComponent
    }
];
var SQSRoutingModule = class _SQSRoutingModule {
    static {
        this.\u0275fac = function SQSRoutingModule_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _SQSRoutingModule)();
        };
    }
    static {
        this.\u0275mod = /* @__PURE__ */ \u0275\u0275defineNgModule({type: _SQSRoutingModule});
    }
    static {
        this.\u0275inj = /* @__PURE__ */ \u0275\u0275defineInjector({imports: [RouterModule.forChild(routes), RouterModule]});
    }
};

// src/app/modules/sqs/queue-detail/state/sqs-queue-detail.effects.ts
var SqsQueueDetailEffects = class _SqsQueueDetailEffects {
    constructor(actions$, sqsService) {
        this.actions$ = actions$;
        this.sqsService = sqsService;
        this.sortColumns = [];
        this.loadQueuesDetails$ = createEffect(() => this.actions$.pipe(ofType(sqsQueueDetailsActions.loadDetails), mergeMap((action) => this.sqsService.getQueueDetails(action.queueArn).pipe(map((details) => sqsQueueDetailsActions.loadDetailsSuccess({queueDetails: details})), catchError((error) => of(sqsQueueDetailsActions.loadDetailsFailure({error: error.message})))))));
    }

    static {
        this.\u0275fac = function SqsQueueDetailEffects_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _SqsQueueDetailEffects)(\u0275\u0275inject(Actions), \u0275\u0275inject(SqsService));
        };
    }
    static {
        this.\u0275prov = /* @__PURE__ */ \u0275\u0275defineInjectable({token: _SqsQueueDetailEffects, factory: _SqsQueueDetailEffects.\u0275fac});
    }
};

// src/app/modules/sqs/message-list/state/sqs-message-list.effects.ts
var SqsMessageListEffects = class _SqsMessageListEffects {
    constructor(actions$, sqsService) {
        this.actions$ = actions$;
        this.sqsService = sqsService;
        this.loadMessages$ = createEffect(() => this.actions$.pipe(ofType(sqsMessageListActions.loadMessages), mergeMap((action) => this.sqsService.listMessageCounters(action.queueArn, action.prefix, action.pageSize, action.pageIndex, action.sortColumns).pipe(map((messages) => sqsMessageListActions.loadMessagesSuccess({messages})), catchError((error) => of(sqsMessageListActions.loadMessagesFailure({error: error.message})))))));
        this.deleteMessage$ = createEffect(() => this.actions$.pipe(ofType(sqsMessageListActions.deleteMessage), mergeMap((action) => this.sqsService.deleteMessageAws(action.queueUrl, action.receiptHandle).pipe(map(() => sqsMessageListActions.deleteMessageSuccess()), catchError((error) => of(sqsMessageListActions.deleteMessageFailure({error: error.message})))))));
    }

    static {
        this.\u0275fac = function SqsMessageListEffects_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _SqsMessageListEffects)(\u0275\u0275inject(Actions), \u0275\u0275inject(SqsService));
        };
    }
    static {
        this.\u0275prov = /* @__PURE__ */ \u0275\u0275defineInjectable({token: _SqsMessageListEffects, factory: _SqsMessageListEffects.\u0275fac});
    }
};

// src/app/modules/sqs/sqs.module.ts
var SQSModule = class _SQSModule {
    static {
        this.\u0275fac = function SQSModule_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _SQSModule)();
        };
    }
    static {
        this.\u0275mod = /* @__PURE__ */ \u0275\u0275defineNgModule({type: _SQSModule});
    }
    static {
        this.\u0275inj = /* @__PURE__ */ \u0275\u0275defineInjector({
            providers: [SqsService], imports: [
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
                SQSRoutingModule,
                StoreModule.forFeature(sqsQueueListFeatureKey, sqsQueueListReducer),
                StoreModule.forFeature(sqsQueueDetailsFeatureKey, sqsQueueDetailReducer),
                StoreModule.forFeature(sqsMessageListFeatureKey, sqsMessageListReducer),
                EffectsModule.forFeature([SqsQueueListEffects, SqsQueueDetailEffects, SqsMessageListEffects])
            ]
        });
    }
};
export {
    SQSModule
};
//# sourceMappingURL=chunk-DTKLUXRT.js.map

import {CognitoConfig} from "./chunk-4IO3RYFH.js";
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
    DefaultValueAccessor,
    EffectsModule,
    environment,
    filter,
    FormsModule,
    HttpClient,
    HttpHeaders,
    interval,
    Location,
    map,
    MatButton,
    MatCard,
    MatCardActions,
    MatCardContent,
    MatCardHeader,
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

// src/app/services/cognito.service.ts
var CognitoService = class _CognitoService {
    constructor(http) {
        this.http = http;
        this.cognitoConfig = new CognitoConfig();
        this.url = environment.gatewayEndpoint + "/";
    }

    /**
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     */
    listUserPools(maxResults, pageIndex, sortColumns) {
        let headers = this.cognitoConfig.cognitoOptions.headers.set("X-Amz-Target", "Cognito.ListUserPools");
        const body = {
            Region: environment.awsmockRegion,
            MaxResults: maxResults,
            PageIndex: pageIndex,
            sortColumns
        };
        return this.http.post(this.url, body, {headers});
    }

    listUsers(userPoolId, maxResults, pageIndex, sortColumns) {
        let headers = this.cognitoConfig.cognitoOptions.headers.set("X-Amz-Target", "Cognito.ListUsers");
        const body = {
            Region: environment.awsmockRegion,
            UserPoolId: userPoolId,
            MaxResults: maxResults,
            PageIndex: pageIndex,
            SortColumns: sortColumns
        };
        return this.http.post(this.url, body, {headers});
    }

    deleteUserPool(userPoolId) {
        let headers = this.cognitoConfig.cognitoOptions.headers.set("X-Amz-Target", "Cognito.DeleteUserPool");
        const body = {
            Region: environment.awsmockRegion,
            UserPoolId: userPoolId
        };
        return this.http.post(this.url, body, {headers});
    }

    deleteUser(userPoolId, userName) {
        let headers = this.cognitoConfig.cognitoOptions.headers.set("X-Amz-Target", "Cognito.AdminDeleteUser");
        const body = {
            Region: environment.awsmockRegion,
            UserPoolId: userPoolId,
            Username: userName
        };
        return this.http.post(this.url, body, {headers});
    }

    createUserPool(userPoolName) {
        let headers = this.cognitoConfig.cognitoOptions.headers.set("X-Amz-Target", "Cognito.CreateUserPool");
        const body = {
            Region: environment.awsmockRegion,
            PoolName: userPoolName
        };
        return this.http.post(this.url, body, {headers});
    }

    createUser(userPoolId, userName) {
        let headers = this.cognitoConfig.cognitoOptions.headers.set("X-Amz-Target", "Cognito.AdminCreateUser");
        const body = {
            Region: environment.awsmockRegion,
            Username: userName,
            UserPoolId: userPoolId
        };
        return this.http.post(this.url, body, {headers});
    }

    static {
        this.\u0275fac = function CognitoService_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _CognitoService)(\u0275\u0275inject(HttpClient));
        };
    }
    static {
        this.\u0275prov = /* @__PURE__ */ \u0275\u0275defineInjectable({token: _CognitoService, factory: _CognitoService.\u0275fac});
    }
};

// src/app/modules/cognito/user-pool-add/user-pool-add.component.ts
var UserPoolAddComponentDialog = class _UserPoolAddComponentDialog {
    constructor(dialogRef) {
        this.dialogRef = dialogRef;
        this.userPoolName = "";
    }

    ngOnInit() {
    }

    save() {
        this.dialogRef.close(this.userPoolName);
    }

    close() {
        this.dialogRef.close(false);
    }

    static {
        this.\u0275fac = function UserPoolAddComponentDialog_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _UserPoolAddComponentDialog)(\u0275\u0275directiveInject(MatDialogRef));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _UserPoolAddComponentDialog,
            selectors: [["user-pool-add-dialog"]],
            standalone: true,
            features: [\u0275\u0275StandaloneFeature],
            decls: 12,
            vars: 1,
            consts: [["mat-dialog-title", ""], [1, "mat-typography", 2, "width", "500px"], [2, "width", "100%"], ["matInput", "", "value", "", 3, "ngModelChange", "ngModel"], ["align", "end"], ["mat-button", "", "mat-dialog-close", ""], ["cdkFocusInitial", "", "mat-button", "", 3, "click"]],
            template: function UserPoolAddComponentDialog_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "h2", 0);
                    \u0275\u0275text(1, "Add Cognito User Pool");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(2, "mat-dialog-content", 1)(3, "mat-form-field", 2)(4, "mat-label");
                    \u0275\u0275text(5, "Userpool Name");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(6, "input", 3);
                    \u0275\u0275twoWayListener("ngModelChange", function UserPoolAddComponentDialog_Template_input_ngModelChange_6_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.userPoolName, $event) || (ctx.userPoolName = $event);
                        return $event;
                    });
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(7, "mat-dialog-actions", 4)(8, "button", 5);
                    \u0275\u0275text(9, "Cancel");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(10, "button", 6);
                    \u0275\u0275listener("click", function UserPoolAddComponentDialog_Template_button_click_10_listener() {
                        return ctx.save();
                    });
                    \u0275\u0275text(11, "Add");
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    \u0275\u0275advance(6);
                    \u0275\u0275twoWayProperty("ngModel", ctx.userPoolName);
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
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(UserPoolAddComponentDialog, {
        className: "UserPoolAddComponentDialog",
        filePath: "src/app/modules/cognito/user-pool-add/user-pool-add.component.ts",
        lineNumber: 37
    });
})();

// src/app/modules/cognito/user-pool-list/state/cognito-userpool-list.actions.ts
var cognitoUserpoolListActions = {
    initialize: createAction("[cognito-userpool-list] initialize"),
    // Load user pool
    loadUserPools: createAction("[cognito-userpool-list] Load userpools", props()),
    loadUserPoolsSuccess: createAction("[cognito-userpool-list] Load userpools success", props()),
    loadUserPoolsFailure: createAction("[cognito-userpool-list] Load userpools error", props()),
    // Add user pool
    addUserPool: createAction("[cognito-userpool-list] Add userpool", props()),
    addUserPoolSuccess: createAction("[cognito-userpool-list] Add userpool success"),
    addUserPoolFailure: createAction("[cognito-userpool-list] Add userpool error", props()),
    // Delete user pool
    deleteUserPool: createAction("[cognito-userpool-list] Delete userpool", props()),
    deleteUserPoolSuccess: createAction("[cognito-userpool-list] Delete userpool success"),
    deleteUserPoolFailure: createAction("[cognito-userpool-list] Delete userpool error", props())
};

// src/app/modules/cognito/user-pool-list/state/cognito-userpool-list.reducer.ts
var cognitoUserPoolListFeatureKey = "cognito-userpool-list";
var initialState = {
    listUserPoolResponse: {total: 0, userPools: []},
    prefix: "",
    pageSize: 10,
    pageIndex: 0,
    loading: false,
    sortColumns: [{column: "userPoolName", sortDirection: -1}],
    error: {}
};
var cognitoUserPoolListReducer = createReducer(
    initialState,
    // Initialize
    on(cognitoUserpoolListActions.initialize, (state) => __spreadProps(__spreadValues({}, state), {pageIndex: 0, pageSize: 10, loading: true})),
    // Queue list
    on(cognitoUserpoolListActions.loadUserPools, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(cognitoUserpoolListActions.loadUserPoolsSuccess, (state, {userPools}) => __spreadProps(__spreadValues({}, state), {
        listUserPoolResponse: userPools,
        loading: false
    })),
    on(cognitoUserpoolListActions.loadUserPoolsFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false})),
    // Add queue
    on(cognitoUserpoolListActions.addUserPool, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(cognitoUserpoolListActions.addUserPoolSuccess, (state) => __spreadProps(__spreadValues({}, state), {loading: false})),
    on(cognitoUserpoolListActions.addUserPoolFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false})),
    // Delete queue
    on(cognitoUserpoolListActions.deleteUserPool, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(cognitoUserpoolListActions.deleteUserPoolSuccess, (state) => __spreadProps(__spreadValues({}, state), {loading: false})),
    on(cognitoUserpoolListActions.deleteUserPoolFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false}))
);

// src/app/modules/cognito/user-pool-list/state/cognito-userpool-list.selectors.ts
var selectUserPoolListFeature = createFeatureSelector(cognitoUserPoolListFeatureKey);
var selectIsLoading = createSelector(selectUserPoolListFeature, (state) => state.loading);
var selectPrefix = createSelector(selectUserPoolListFeature, (state) => state?.prefix);
var selectPageSize = createSelector(selectUserPoolListFeature, (state) => state?.pageSize);
var selectPageIndex = createSelector(selectUserPoolListFeature, (state) => state?.pageIndex);
var selectSortColumns = createSelector(selectUserPoolListFeature, (state) => state?.sortColumns);
var selectUserPoolCounters = createSelector(selectUserPoolListFeature, (state) => state?.listUserPoolResponse);

// src/app/modules/cognito/user-pool-list/user-pool-list.component.ts
var _c0 = () => [];

function CognitoUserPoolListComponent_button_21_Template(rf, ctx) {
    if (rf & 1) {
        const _r1 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "button", 13);
        \u0275\u0275listener("click", function CognitoUserPoolListComponent_button_21_Template_button_click_0_listener() {
            \u0275\u0275restoreView(_r1);
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.setPrefix());
        });
        \u0275\u0275elementStart(1, "mat-icon", 14);
        \u0275\u0275text(2, "search");
        \u0275\u0275elementEnd()();
    }
}

function CognitoUserPoolListComponent_button_22_Template(rf, ctx) {
    if (rf & 1) {
        const _r3 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "button", 13);
        \u0275\u0275listener("click", function CognitoUserPoolListComponent_button_22_Template_button_click_0_listener() {
            \u0275\u0275restoreView(_r3);
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.unsetPrefix());
        });
        \u0275\u0275elementStart(1, "mat-icon", 14);
        \u0275\u0275text(2, "close");
        \u0275\u0275elementEnd()();
    }
}

function CognitoUserPoolListComponent_div_24_th_3_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 29);
        \u0275\u0275text(1, "ID");
        \u0275\u0275elementEnd();
    }
}

function CognitoUserPoolListComponent_div_24_td_4_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 30)(1, "mat-nav-list")(2, "a", 31);
        \u0275\u0275text(3);
        \u0275\u0275elementEnd()()();
    }
    if (rf & 2) {
        const element_r5 = ctx.$implicit;
        \u0275\u0275advance(2);
        \u0275\u0275propertyInterpolate1("routerLink", "./users/", element_r5.userPoolId, "");
        \u0275\u0275advance();
        \u0275\u0275textInterpolate(element_r5.userPoolId);
    }
}

function CognitoUserPoolListComponent_div_24_th_6_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 32);
        \u0275\u0275text(1, "Created");
        \u0275\u0275elementEnd();
    }
}

function CognitoUserPoolListComponent_div_24_td_7_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 30);
        \u0275\u0275text(1);
        \u0275\u0275pipe(2, "date");
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r6 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", \u0275\u0275pipeBind2(2, 1, element_r6.created, "dd-MM-yyyy hh:mm:ss"), "");
    }
}

function CognitoUserPoolListComponent_div_24_th_9_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 33);
        \u0275\u0275text(1, "Modified");
        \u0275\u0275elementEnd();
    }
}

function CognitoUserPoolListComponent_div_24_td_10_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 30);
        \u0275\u0275text(1);
        \u0275\u0275pipe(2, "date");
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r7 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", \u0275\u0275pipeBind2(2, 1, element_r7.modified, "dd-MM-yyyy hh:mm:ss"), "");
    }
}

function CognitoUserPoolListComponent_div_24_th_12_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 34);
        \u0275\u0275text(1, "Actions");
        \u0275\u0275elementEnd();
    }
}

function CognitoUserPoolListComponent_div_24_td_13_Template(rf, ctx) {
    if (rf & 1) {
        const _r8 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "td", 30)(1, "button", 35);
        \u0275\u0275listener("click", function CognitoUserPoolListComponent_div_24_td_13_Template_button_click_1_listener() {
            const row_r9 = \u0275\u0275restoreView(_r8).$implicit;
            const ctx_r1 = \u0275\u0275nextContext(2);
            return \u0275\u0275resetView(ctx_r1.deleteUserPool(row_r9.userPoolId));
        });
        \u0275\u0275elementStart(2, "mat-icon");
        \u0275\u0275text(3, "delete");
        \u0275\u0275elementEnd()()();
    }
}

function CognitoUserPoolListComponent_div_24_tr_14_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 36);
    }
}

function CognitoUserPoolListComponent_div_24_tr_15_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 37);
    }
}

function CognitoUserPoolListComponent_div_24_tr_16_Template(rf, ctx) {
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

function CognitoUserPoolListComponent_div_24_Template(rf, ctx) {
    if (rf & 1) {
        const _r4 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "div", 15)(1, "table", 16);
        \u0275\u0275listener("matSortChange", function CognitoUserPoolListComponent_div_24_Template_table_matSortChange_1_listener($event) {
            \u0275\u0275restoreView(_r4);
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.sortChange($event));
        });
        \u0275\u0275elementContainerStart(2, 17);
        \u0275\u0275template(3, CognitoUserPoolListComponent_div_24_th_3_Template, 2, 0, "th", 18)(4, CognitoUserPoolListComponent_div_24_td_4_Template, 4, 3, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(5, 20);
        \u0275\u0275template(6, CognitoUserPoolListComponent_div_24_th_6_Template, 2, 0, "th", 21)(7, CognitoUserPoolListComponent_div_24_td_7_Template, 3, 4, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(8, 22);
        \u0275\u0275template(9, CognitoUserPoolListComponent_div_24_th_9_Template, 2, 0, "th", 23)(10, CognitoUserPoolListComponent_div_24_td_10_Template, 3, 4, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(11, 24);
        \u0275\u0275template(12, CognitoUserPoolListComponent_div_24_th_12_Template, 2, 0, "th", 25)(13, CognitoUserPoolListComponent_div_24_td_13_Template, 4, 0, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275template(14, CognitoUserPoolListComponent_div_24_tr_14_Template, 1, 0, "tr", 26)(15, CognitoUserPoolListComponent_div_24_tr_15_Template, 1, 0, "tr", 27)(16, CognitoUserPoolListComponent_div_24_tr_16_Template, 3, 1, "tr", 28);
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const userPoolCounters_r10 = ctx.ngIf;
        const ctx_r1 = \u0275\u0275nextContext();
        \u0275\u0275advance();
        \u0275\u0275property("dataSource", userPoolCounters_r10.userPools);
        \u0275\u0275advance(13);
        \u0275\u0275property("matHeaderRowDef", ctx_r1.columns);
        \u0275\u0275advance();
        \u0275\u0275property("matRowDefColumns", ctx_r1.columns);
    }
}

var CognitoUserPoolListComponent = class _CognitoUserPoolListComponent {
    constructor(snackBar, dialog, location, state, store) {
        this.snackBar = snackBar;
        this.dialog = dialog;
        this.location = location;
        this.state = state;
        this.store = store;
        this.lastUpdate = /* @__PURE__ */ new Date();
        this.pageSize$ = this.store.select(selectPageSize);
        this.pageIndex$ = this.store.select(selectPageIndex);
        this.prefix$ = this.store.select(selectPrefix);
        this.listUserPoolCountersResponse$ = this.store.select(selectUserPoolCounters);
        this.columns = ["id", "created", "modified", "actions"];
        this.pageSizeOptions = [5, 10, 20, 50, 100];
        this.hidePageSize = false;
        this.showPageSizeOptions = true;
        this.showFirstLastButtons = true;
        this.disabled = false;
        this.pageEvent = {length: 0, pageIndex: 0, pageSize: 0};
        this.sortColumns = [];
        this.prefixValue = this.state.value["cognito-userpool-list"].prefix;
        this.prefixSet = false;
        this.prefix$.subscribe((data) => {
            this.prefixSet = false;
            if (data && data.length) {
                this.prefixValue = data;
                this.prefixSet = true;
            }
        });
    }

    ngOnInit() {
        this.loadUserpools();
        this.updateSubscription = interval(6e4).subscribe(() => this.loadUserpools());
    }

    ngOnDestroy() {
        this.updateSubscription?.unsubscribe();
    }

    setPrefix() {
        this.prefixSet = true;
        this.state.value["cognito-userpool-list"].pageIndex = 0;
        this.state.value["cognito-userpool-list"].prefix = this.prefixValue;
        this.loadUserpools();
    }

    unsetPrefix() {
        this.prefixValue = "";
        this.prefixSet = false;
        this.state.value["cognito-userpool-list"].prefix = "";
        this.loadUserpools();
    }

    back() {
        this.location.back();
    }

    refresh() {
        this.loadUserpools();
    }

    handlePageEvent(e) {
        this.state.value["cognito-userpool-list"].pageSize = e.pageSize;
        this.state.value["cognito-userpool-list"].pageIndex = e.pageIndex;
        this.loadUserpools();
    }

    sortChange(sortState) {
        this.sortColumns = [];
        if (sortState.direction === "asc") {
            this.sortColumns.push({column: sortState.active, sortDirection: 1});
        } else {
            this.sortColumns.push({column: sortState.active, sortDirection: -1});
        }
        this.loadUserpools();
    }

    loadUserpools() {
        this.lastUpdate = /* @__PURE__ */ new Date();
        this.store.dispatch(cognitoUserpoolListActions.loadUserPools({
            prefix: this.state.value["cognito-userpool-list"].prefix,
            pageSize: this.state.value["cognito-userpool-list"].pageSize,
            pageIndex: this.state.value["cognito-userpool-list"].pageIndex,
            sortColumns: this.state.value["cognito-userpool-list"].sortColumns
        }));
    }

    addUserPool() {
        const dialogConfig = new MatDialogConfig();
        dialogConfig.disableClose = true;
        dialogConfig.autoFocus = true;
        this.dialog.open(UserPoolAddComponentDialog, dialogConfig).afterClosed().subscribe((result) => {
            if (result) {
                this.createUserPool(result);
            }
        });
    }

    createUserPool(userPoolName) {
        this.store.dispatch(cognitoUserpoolListActions.addUserPool({userPoolName}));
    }

    deleteUserPool(userPoolId) {
    }

    static {
        this.\u0275fac = function CognitoUserPoolListComponent_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _CognitoUserPoolListComponent)(\u0275\u0275directiveInject(MatSnackBar), \u0275\u0275directiveInject(MatDialog), \u0275\u0275directiveInject(Location), \u0275\u0275directiveInject(State), \u0275\u0275directiveInject(Store));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _CognitoUserPoolListComponent,
            selectors: [["cognito-user-pool-list"]],
            features: [\u0275\u0275ProvidersFeature([CognitoService])],
            decls: 33,
            vars: 24,
            consts: [["appearance", "outlined", 2, "margin", "3px"], ["aria-label", "Back", "mat-icon-button", "", 1, "head-buttons-left", 3, "click"], [1, "fill-remaining-space"], ["aria-label", "Refresh", "mat-icon-button", "", 3, "click"], ["appearance", "outlined", 2, "margin", "-10px"], [1, "head-buttons"], [2, "width", "100%"], ["matInput", "", "name", "search", "placeholder", "Search", "type", "text", 3, "ngModelChange", "ngModel"], ["mat-icon-button", "", "matSuffix", "", "style", "float: right", 3, "click", 4, "ngIf"], [1, "table-container"], ["class", "row", 4, "ngIf"], ["aria-label", "Select page", 2, "width", "99%", "margin-left", "15px", 3, "page", "disabled", "hidePageSize", "length", "pageIndex", "pageSizeOptions", "pageSize", "showFirstLastButtons"], [1, "footer"], ["mat-icon-button", "", "matSuffix", "", 2, "float", "right", 3, "click"], ["matSuffix", ""], [1, "row"], ["mat-table", "", "matSort", "", 1, "mat-elevation-z8", "queue-table", 3, "matSortChange", "dataSource"], ["matColumnDef", "id", "matTooltip", "User PoolId"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "User Pool ID", "sortActionDescription", "Sort by userPoolId", 4, "matHeaderCellDef"], ["mat-cell", "", 4, "matCellDef"], ["matColumnDef", "created", "matTooltip", "Created"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Create timestamp", "sortActionDescription", "Sort by created", 4, "matHeaderCellDef"], ["matColumnDef", "modified", "matTooltip", "Modified"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Modified timestamp", "sortActionDescription", "Sort by modified", 4, "matHeaderCellDef"], ["matColumnDef", "actions"], ["mat-header-cell", "", "style", "width:80px", 4, "matHeaderCellDef"], ["mat-header-row", "", 4, "matHeaderRowDef"], ["mat-row", "", 4, "matRowDef", "matRowDefColumns"], ["class", "mat-row", 4, "matNoDataRow"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "User Pool ID", "sortActionDescription", "Sort by userPoolId"], ["mat-cell", ""], ["mat-list-item", "", 3, "routerLink"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Create timestamp", "sortActionDescription", "Sort by created"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Modified timestamp", "sortActionDescription", "Sort by modified"], ["mat-header-cell", "", 2, "width", "80px"], ["aria-label", "DeleteUserPool", "mat-icon-button", "", "matTooltip", "Delete user pool", 3, "click"], ["mat-header-row", ""], ["mat-row", ""], [1, "mat-row"], [1, "mat-cell"]],
            template: function CognitoUserPoolListComponent_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "mat-card", 0)(1, "mat-card-header")(2, "button", 1);
                    \u0275\u0275listener("click", function CognitoUserPoolListComponent_Template_button_click_2_listener() {
                        return ctx.back();
                    });
                    \u0275\u0275elementStart(3, "mat-icon");
                    \u0275\u0275text(4, "arrow_back");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(5, "span", 2)(6, "h4");
                    \u0275\u0275text(7, "Cognito User pools");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(8, "button", 3);
                    \u0275\u0275listener("click", function CognitoUserPoolListComponent_Template_button_click_8_listener() {
                        return ctx.addUserPool();
                    });
                    \u0275\u0275elementStart(9, "mat-icon");
                    \u0275\u0275text(10, "add");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(11, "button", 3);
                    \u0275\u0275listener("click", function CognitoUserPoolListComponent_Template_button_click_11_listener() {
                        return ctx.refresh();
                    });
                    \u0275\u0275elementStart(12, "mat-icon");
                    \u0275\u0275text(13, "refresh");
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(14, "mat-card-content")(15, "mat-card", 4)(16, "mat-card-actions", 5)(17, "mat-form-field", 6)(18, "mat-label");
                    \u0275\u0275text(19, "Prefix");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(20, "input", 7);
                    \u0275\u0275twoWayListener("ngModelChange", function CognitoUserPoolListComponent_Template_input_ngModelChange_20_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.prefixValue, $event) || (ctx.prefixValue = $event);
                        return $event;
                    });
                    \u0275\u0275elementEnd();
                    \u0275\u0275template(21, CognitoUserPoolListComponent_button_21_Template, 3, 0, "button", 8)(22, CognitoUserPoolListComponent_button_22_Template, 3, 0, "button", 8);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(23, "div", 9);
                    \u0275\u0275template(24, CognitoUserPoolListComponent_div_24_Template, 17, 3, "div", 10);
                    \u0275\u0275pipe(25, "async");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(26, "mat-paginator", 11);
                    \u0275\u0275pipe(27, "async");
                    \u0275\u0275pipe(28, "async");
                    \u0275\u0275pipe(29, "async");
                    \u0275\u0275listener("page", function CognitoUserPoolListComponent_Template_mat_paginator_page_26_listener($event) {
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
                    \u0275\u0275twoWayProperty("ngModel", ctx.prefixValue);
                    \u0275\u0275advance();
                    \u0275\u0275property("ngIf", !ctx.prefixSet);
                    \u0275\u0275advance();
                    \u0275\u0275property("ngIf", ctx.prefixSet);
                    \u0275\u0275advance(2);
                    \u0275\u0275property("ngIf", \u0275\u0275pipeBind1(25, 12, ctx.listUserPoolCountersResponse$));
                    \u0275\u0275advance(2);
                    \u0275\u0275property("disabled", ctx.disabled)("hidePageSize", ctx.hidePageSize)("length", (tmp_6_0 = \u0275\u0275pipeBind1(27, 14, ctx.listUserPoolCountersResponse$)) == null ? null : tmp_6_0.total)("pageIndex", \u0275\u0275pipeBind1(28, 16, ctx.pageIndex$))("pageSizeOptions", ctx.showPageSizeOptions ? ctx.pageSizeOptions : \u0275\u0275pureFunction0(23, _c0))("pageSize", \u0275\u0275pipeBind1(29, 18, ctx.pageSize$))("showFirstLastButtons", ctx.showFirstLastButtons);
                    \u0275\u0275advance(5);
                    \u0275\u0275textInterpolate1(" Last update: ", \u0275\u0275pipeBind2(32, 20, ctx.lastUpdate, "HH:mm:ss"), " ");
                }
            },
            dependencies: [MatCard, MatCardHeader, MatCardContent, MatCardActions, MatTable, MatHeaderCellDef, MatCellDef, MatColumnDef, MatIcon, MatHeaderCell, MatCell, MatHeaderRowDef, MatHeaderRow, MatSortHeader, MatRowDef, MatNoDataRow, MatIconButton, MatRow, MatPaginator, MatSort, MatTooltip, RouterLink, MatListItem, MatNavList, MatFormField, MatInput, MatLabel, MatSuffix, NgIf, DefaultValueAccessor, NgControlStatus, NgModel, DatePipe, AsyncPipe],
            styles: ["\n\n.fill-remaining-space[_ngcontent-%COMP%] {\n  flex: 1 1 auto;\n}\n.table-container[_ngcontent-%COMP%] {\n  max-height: calc(100vh - 10px);\n  max-width: calc(100vw - 15px);\n  overflow: hidden;\n}\n.footer[_ngcontent-%COMP%] {\n  display: flex;\n  width: 50%;\n  font-size: x-small;\n  color: black;\n}\n/*# sourceMappingURL=user-pool-list.component.css.map */"]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(CognitoUserPoolListComponent, {
        className: "CognitoUserPoolListComponent",
        filePath: "src/app/modules/cognito/user-pool-list/user-pool-list.component.ts",
        lineNumber: 23
    });
})();

// src/app/modules/cognito/service/cognito.service.ts
var CognitoService2 = class _CognitoService {
    constructor(http) {
        this.http = http;
        this.headers = new HttpHeaders({
            "Content-Type": "application/json",
            "Authorization": "AWS4-HMAC-SHA256 Credential=none/20240928/eu-central-1/cognito-idp/aws4_request, SignedHeaders=content-type;host;x-amz-date;x-amz-security-token;x-amz-target, Signature=01316d694335ec0e0bf68b08570490f1b0bae0b130ecbe13ebad511b3ece8a41"
        });
        this.url = environment.gatewayEndpoint + "/";
    }

    /**
     * This is a fake AWS NodeJS SDK request. This will only work, if runs against a AwsMock instance.
     */
    listUserPoolCounters(prefix, pageSize, pageIndex, sortColumns) {
        let headers = this.headers.set("x-awsmock-target", "cognito-idp").set("x-awsmock-action", "ListUserPoolCounters");
        const body = {
            region: environment.awsmockRegion,
            prefix,
            pageSize,
            pageIndex,
            sortColumns
        };
        return this.http.post(this.url, body, {headers});
    }

    listUserCounters(userPoolId, maxResults, pageIndex, sortColumns) {
        let headers = this.headers.set("x-awsmock-target", "cognito-idp").set("x-awsmock-action", "ListUserCounters");
        const body = {
            Region: environment.awsmockRegion,
            UserPoolId: userPoolId,
            MaxResults: maxResults,
            PageIndex: pageIndex,
            SortColumns: sortColumns
        };
        return this.http.post(this.url, body, {headers});
    }

    deleteUserPool(userPoolId) {
        let headers = this.headers.set("x-awsmock-target", "cognito-idp").set("x-awsmock-action", "DeleteUserPool");
        const body = {
            Region: environment.awsmockRegion,
            UserPoolId: userPoolId
        };
        return this.http.post(this.url, body, {headers});
    }

    deleteUser(userPoolId, userName) {
        let headers = this.headers.set("x-awsmock-target", "cognito-idp").set("x-awsmock-action", "AdminDeleteUser");
        const body = {
            Region: environment.awsmockRegion,
            UserPoolId: userPoolId,
            Username: userName
        };
        return this.http.post(this.url, body, {headers});
    }

    confirmUser(userPoolId, userName) {
        let headers = this.headers.set("x-awsmock-target", "cognito-idp").set("x-awsmock-action", "AdminConfirmSignUp");
        const body = {
            Region: environment.awsmockRegion,
            UserPoolId: userPoolId,
            Username: userName
        };
        return this.http.post(this.url, body, {headers});
    }

    createUserPool(userPoolName) {
        let headers = this.headers.set("x-awsmock-target", "cognito-idp").set("x-awsmock-action", "CreateUserPool");
        const body = {
            Region: environment.awsmockRegion,
            PoolName: userPoolName
        };
        return this.http.post(this.url, body, {headers});
    }

    createUser(userPoolId, userName) {
        let headers = this.headers.set("x-awsmock-target", "cognito-idp").set("x-awsmock-action", "AdminCreateUser");
        const body = {
            Region: environment.awsmockRegion,
            Username: userName,
            UserPoolId: userPoolId
        };
        return this.http.post(this.url, body, {headers});
    }

    static {
        this.\u0275fac = function CognitoService_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _CognitoService)(\u0275\u0275inject(HttpClient));
        };
    }
    static {
        this.\u0275prov = /* @__PURE__ */ \u0275\u0275defineInjectable({token: _CognitoService, factory: _CognitoService.\u0275fac});
    }
};

// src/app/modules/cognito/user-add/user-add.component.ts
var UserAddComponentDialog = class _UserAddComponentDialog {
    constructor(dialogRef) {
        this.dialogRef = dialogRef;
        this.userName = "";
    }

    ngOnInit() {
    }

    save() {
        this.dialogRef.close(this.userName);
    }

    close() {
        this.dialogRef.close(false);
    }

    static {
        this.\u0275fac = function UserAddComponentDialog_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _UserAddComponentDialog)(\u0275\u0275directiveInject(MatDialogRef));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _UserAddComponentDialog,
            selectors: [["user-add-dialog"]],
            standalone: true,
            features: [\u0275\u0275StandaloneFeature],
            decls: 12,
            vars: 1,
            consts: [["mat-dialog-title", ""], [1, "mat-typography", 2, "width", "500px"], [2, "width", "100%"], ["matInput", "", "value", "", 3, "ngModelChange", "ngModel"], ["align", "end"], ["mat-button", "", "mat-dialog-close", ""], ["cdkFocusInitial", "", "mat-button", "", 3, "click"]],
            template: function UserAddComponentDialog_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "h2", 0);
                    \u0275\u0275text(1, "Add Cognito User");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(2, "mat-dialog-content", 1)(3, "mat-form-field", 2)(4, "mat-label");
                    \u0275\u0275text(5, "User Name");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(6, "input", 3);
                    \u0275\u0275twoWayListener("ngModelChange", function UserAddComponentDialog_Template_input_ngModelChange_6_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.userName, $event) || (ctx.userName = $event);
                        return $event;
                    });
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(7, "mat-dialog-actions", 4)(8, "button", 5);
                    \u0275\u0275text(9, "Cancel");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(10, "button", 6);
                    \u0275\u0275listener("click", function UserAddComponentDialog_Template_button_click_10_listener() {
                        return ctx.save();
                    });
                    \u0275\u0275text(11, "Add");
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    \u0275\u0275advance(6);
                    \u0275\u0275twoWayProperty("ngModel", ctx.userName);
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
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(UserAddComponentDialog, {
        className: "UserAddComponentDialog",
        filePath: "src/app/modules/cognito/user-add/user-add.component.ts",
        lineNumber: 37
    });
})();

// src/app/modules/cognito/user-list/state/cognito-user-list.actions.ts
var cognitoUserActions = {
    initialize: createAction("[cognito-user-list] initialize"),
    // Load users
    loadUsers: createAction("[cognito-user-list] Load users", props()),
    loadUsersSuccess: createAction("[cognito-user-list] Load users success", props()),
    loadUsersFailure: createAction("[cognito-user-list] Load users error", props()),
    // Add user
    addUser: createAction("[cognito-user-list] Add user", props()),
    addUserSuccess: createAction("[cognito-user-list] Add user success"),
    addUserFailure: createAction("[cognito-user-list] Add user error", props()),
    // Confirm user
    confirmUser: createAction("[cognito-user-list] Confirm user", props()),
    confirmUserSuccess: createAction("[cognito-user-list] Confirm user success"),
    confirmUserFailure: createAction("[cognito-user-list] Confirm user error", props()),
    // Delete user pool
    deleteUser: createAction("[cognito-user-list] Delete user", props()),
    deleteUserSuccess: createAction("[cognito-user-list] Delete user success"),
    deleteUserFailure: createAction("[cognito-user-list] Delete user error", props())
};

// src/app/modules/cognito/user-list/state/cognito-user-list.reducer.ts
var cognitoUserListFeatureKey = "cognito-user-list";
var initialState2 = {
    listUsersResponse: {total: 0, users: []},
    prefix: "",
    pageSize: 10,
    pageIndex: 0,
    loading: false,
    sortColumns: [{column: "userPoolName", sortDirection: -1}],
    error: {}
};
var cognitoUserListReducer = createReducer(
    initialState2,
    // Initialize
    on(cognitoUserActions.initialize, (state) => __spreadProps(__spreadValues({}, state), {pageIndex: 0, pageSize: 10, loading: true})),
    // User list
    on(cognitoUserActions.loadUsers, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(cognitoUserActions.loadUsersSuccess, (state, {users}) => __spreadProps(__spreadValues({}, state), {listUsersResponse: users, loading: false})),
    on(cognitoUserActions.loadUsersFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false})),
    // Add user
    on(cognitoUserActions.addUser, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(cognitoUserActions.addUserSuccess, (state) => __spreadProps(__spreadValues({}, state), {loading: false})),
    on(cognitoUserActions.addUserFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false})),
    // Confirm user
    on(cognitoUserActions.confirmUser, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(cognitoUserActions.confirmUserSuccess, (state) => __spreadProps(__spreadValues({}, state), {loading: false})),
    on(cognitoUserActions.confirmUserFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false})),
    // Delete user
    on(cognitoUserActions.deleteUser, (state) => __spreadProps(__spreadValues({}, state), {loading: true})),
    on(cognitoUserActions.deleteUserSuccess, (state) => __spreadProps(__spreadValues({}, state), {loading: false})),
    on(cognitoUserActions.deleteUserFailure, (state, {error}) => __spreadProps(__spreadValues({}, state), {error, loading: false}))
);

// src/app/modules/cognito/user-list/state/cognito-user-list.selectors.ts
var selectUserListFeature = createFeatureSelector(cognitoUserListFeatureKey);
var selectIsLoading2 = createSelector(selectUserListFeature, (state) => state.loading);
var selectPrefix2 = createSelector(selectUserListFeature, (state) => state?.prefix);
var selectPageSize2 = createSelector(selectUserListFeature, (state) => state?.pageSize);
var selectPageIndex2 = createSelector(selectUserListFeature, (state) => state?.pageIndex);
var selectSortColumns2 = createSelector(selectUserListFeature, (state) => state?.sortColumns);
var selectUsersCounters = createSelector(selectUserListFeature, (state) => state?.listUsersResponse);

// src/app/modules/cognito/user-list/user-list.component.ts
var _c02 = () => [];

function CognitoUserListComponent_button_21_Template(rf, ctx) {
    if (rf & 1) {
        const _r1 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "button", 13);
        \u0275\u0275listener("click", function CognitoUserListComponent_button_21_Template_button_click_0_listener() {
            \u0275\u0275restoreView(_r1);
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.setPrefix());
        });
        \u0275\u0275elementStart(1, "mat-icon", 14);
        \u0275\u0275text(2, "search");
        \u0275\u0275elementEnd()();
    }
}

function CognitoUserListComponent_button_22_Template(rf, ctx) {
    if (rf & 1) {
        const _r3 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "button", 13);
        \u0275\u0275listener("click", function CognitoUserListComponent_button_22_Template_button_click_0_listener() {
            \u0275\u0275restoreView(_r3);
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.unsetPrefix());
        });
        \u0275\u0275elementStart(1, "mat-icon", 14);
        \u0275\u0275text(2, "close");
        \u0275\u0275elementEnd()();
    }
}

function CognitoUserListComponent_div_24_th_3_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 33);
        \u0275\u0275text(1, "Name");
        \u0275\u0275elementEnd();
    }
}

function CognitoUserListComponent_div_24_td_4_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 34);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r5 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r5.userName, "");
    }
}

function CognitoUserListComponent_div_24_th_6_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 35);
        \u0275\u0275text(1, "Status");
        \u0275\u0275elementEnd();
    }
}

function CognitoUserListComponent_div_24_td_7_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 34);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r6 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r6.userStatus, "");
    }
}

function CognitoUserListComponent_div_24_th_9_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 36);
        \u0275\u0275text(1, "Enabled");
        \u0275\u0275elementEnd();
    }
}

function CognitoUserListComponent_div_24_td_10_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 34);
        \u0275\u0275text(1);
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r7 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", element_r7.enabled, "");
    }
}

function CognitoUserListComponent_div_24_th_12_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 37);
        \u0275\u0275text(1, "Created");
        \u0275\u0275elementEnd();
    }
}

function CognitoUserListComponent_div_24_td_13_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 34);
        \u0275\u0275text(1);
        \u0275\u0275pipe(2, "date");
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r8 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", \u0275\u0275pipeBind2(2, 1, element_r8.created, "dd-MM-yyyy hh:mm:ss"), "");
    }
}

function CognitoUserListComponent_div_24_th_15_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 38);
        \u0275\u0275text(1, "Modified");
        \u0275\u0275elementEnd();
    }
}

function CognitoUserListComponent_div_24_td_16_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "td", 34);
        \u0275\u0275text(1);
        \u0275\u0275pipe(2, "date");
        \u0275\u0275elementEnd();
    }
    if (rf & 2) {
        const element_r9 = ctx.$implicit;
        \u0275\u0275advance();
        \u0275\u0275textInterpolate1(" ", \u0275\u0275pipeBind2(2, 1, element_r9.modified, "dd-MM-yyyy hh:mm:ss"), "");
    }
}

function CognitoUserListComponent_div_24_th_18_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "th", 39);
        \u0275\u0275text(1, "Actions");
        \u0275\u0275elementEnd();
    }
}

function CognitoUserListComponent_div_24_td_19_Template(rf, ctx) {
    if (rf & 1) {
        const _r10 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "td", 34)(1, "button", 40);
        \u0275\u0275listener("click", function CognitoUserListComponent_div_24_td_19_Template_button_click_1_listener() {
            const row_r11 = \u0275\u0275restoreView(_r10).$implicit;
            const ctx_r1 = \u0275\u0275nextContext(2);
            return \u0275\u0275resetView(ctx_r1.confirmUser(row_r11.userPoolId, row_r11.userName));
        });
        \u0275\u0275elementStart(2, "mat-icon");
        \u0275\u0275text(3, "check_circle");
        \u0275\u0275elementEnd()();
        \u0275\u0275elementStart(4, "button", 41);
        \u0275\u0275listener("click", function CognitoUserListComponent_div_24_td_19_Template_button_click_4_listener() {
            const row_r11 = \u0275\u0275restoreView(_r10).$implicit;
            const ctx_r1 = \u0275\u0275nextContext(2);
            return \u0275\u0275resetView(ctx_r1.deleteUser(row_r11.userName));
        });
        \u0275\u0275elementStart(5, "mat-icon");
        \u0275\u0275text(6, "delete");
        \u0275\u0275elementEnd()()();
    }
}

function CognitoUserListComponent_div_24_tr_20_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 42);
    }
}

function CognitoUserListComponent_div_24_tr_21_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275element(0, "tr", 43);
    }
}

function CognitoUserListComponent_div_24_tr_22_Template(rf, ctx) {
    if (rf & 1) {
        \u0275\u0275elementStart(0, "tr", 44)(1, "td", 45);
        \u0275\u0275text(2, " No data matching the filter. ");
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const ctx_r1 = \u0275\u0275nextContext(2);
        \u0275\u0275advance();
        \u0275\u0275attribute("colspan", ctx_r1.columns.length);
    }
}

function CognitoUserListComponent_div_24_Template(rf, ctx) {
    if (rf & 1) {
        const _r4 = \u0275\u0275getCurrentView();
        \u0275\u0275elementStart(0, "div", 15)(1, "table", 16);
        \u0275\u0275listener("matSortChange", function CognitoUserListComponent_div_24_Template_table_matSortChange_1_listener($event) {
            \u0275\u0275restoreView(_r4);
            const ctx_r1 = \u0275\u0275nextContext();
            return \u0275\u0275resetView(ctx_r1.sortChange($event));
        });
        \u0275\u0275elementContainerStart(2, 17);
        \u0275\u0275template(3, CognitoUserListComponent_div_24_th_3_Template, 2, 0, "th", 18)(4, CognitoUserListComponent_div_24_td_4_Template, 2, 1, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(5, 20);
        \u0275\u0275template(6, CognitoUserListComponent_div_24_th_6_Template, 2, 0, "th", 21)(7, CognitoUserListComponent_div_24_td_7_Template, 2, 1, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(8, 22);
        \u0275\u0275template(9, CognitoUserListComponent_div_24_th_9_Template, 2, 0, "th", 23)(10, CognitoUserListComponent_div_24_td_10_Template, 2, 1, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(11, 24);
        \u0275\u0275template(12, CognitoUserListComponent_div_24_th_12_Template, 2, 0, "th", 25)(13, CognitoUserListComponent_div_24_td_13_Template, 3, 4, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(14, 26);
        \u0275\u0275template(15, CognitoUserListComponent_div_24_th_15_Template, 2, 0, "th", 27)(16, CognitoUserListComponent_div_24_td_16_Template, 3, 4, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275elementContainerStart(17, 28);
        \u0275\u0275template(18, CognitoUserListComponent_div_24_th_18_Template, 2, 0, "th", 29)(19, CognitoUserListComponent_div_24_td_19_Template, 7, 0, "td", 19);
        \u0275\u0275elementContainerEnd();
        \u0275\u0275template(20, CognitoUserListComponent_div_24_tr_20_Template, 1, 0, "tr", 30)(21, CognitoUserListComponent_div_24_tr_21_Template, 1, 0, "tr", 31)(22, CognitoUserListComponent_div_24_tr_22_Template, 3, 1, "tr", 32);
        \u0275\u0275elementEnd()();
    }
    if (rf & 2) {
        const userCounters_r12 = ctx.ngIf;
        const ctx_r1 = \u0275\u0275nextContext();
        \u0275\u0275advance();
        \u0275\u0275property("dataSource", userCounters_r12.users);
        \u0275\u0275advance(19);
        \u0275\u0275property("matHeaderRowDef", ctx_r1.columns);
        \u0275\u0275advance();
        \u0275\u0275property("matRowDefColumns", ctx_r1.columns);
    }
}

var CognitoUserListComponent = class _CognitoUserListComponent {
    constructor(snackBar, dialog, route, location, store, state, cognitoService, actionsSubj$) {
        this.snackBar = snackBar;
        this.dialog = dialog;
        this.route = route;
        this.location = location;
        this.store = store;
        this.state = state;
        this.cognitoService = cognitoService;
        this.actionsSubj$ = actionsSubj$;
        this.lastUpdate = /* @__PURE__ */ new Date();
        this.userPoolId = "";
        this.pageSize$ = this.store.select(selectPageSize);
        this.pageIndex$ = this.store.select(selectPageIndex);
        this.prefix$ = this.store.select(selectPrefix);
        this.listUserCountersResponse$ = this.store.select(selectUsersCounters);
        this.columns = ["userName", "status", "enabled", "created", "modified", "actions"];
        this.pageSizeOptions = [5, 10, 20, 50, 100];
        this.hidePageSize = false;
        this.showPageSizeOptions = true;
        this.showFirstLastButtons = true;
        this.disabled = false;
        this.pageEvent = {length: 0, pageIndex: 0, pageSize: 0};
        this.prefixValue = this.state.value["cognito-user-list"].prefix;
        this.prefixSet = false;
        this.sortColumns = [];
        this.prefix$.subscribe((data) => {
            this.prefixSet = false;
            if (data && data.length) {
                this.prefixValue = data;
                this.prefixSet = true;
            }
        });
        this.actionsSubj$.pipe(filter((action) => action.type === cognitoUserActions.addUserSuccess.type || action.type === cognitoUserActions.confirmUserSuccess.type || action.type === cognitoUserActions.deleteUserSuccess.type)).subscribe(() => {
            this.loadUsers();
        });
    }

    ngOnInit() {
        this.routerSubscription = this.route.params.subscribe((params) => {
            this.userPoolId = params["userPoolId"];
        });
        this.loadUsers();
        this.updateSubscription = interval(6e4).subscribe(() => this.loadUsers());
    }

    ngOnDestroy() {
        this.updateSubscription?.unsubscribe();
        this.routerSubscription?.unsubscribe();
    }

    setPrefix() {
        this.prefixSet = true;
        this.state.value["cognito-user-list"].pageIndex = 0;
        this.state.value["cognito-user-list"].prefix = this.prefixValue;
        this.loadUsers();
    }

    unsetPrefix() {
        this.prefixValue = "";
        this.prefixSet = false;
        this.state.value["cognito-user-list"].prefix = "";
        this.loadUsers();
    }

    back() {
        this.location.back();
    }

    refresh() {
        this.loadUsers();
    }

    handlePageEvent(e) {
        this.state.value["cognito-user-list"].pageSize = e.pageSize;
        this.state.value["cognito-user-list"].pageIndex = e.pageIndex;
        this.loadUsers();
    }

    sortChange(sortState) {
        this.sortColumns = [];
        if (sortState.direction === "asc") {
            this.sortColumns.push({column: sortState.active, sortDirection: 1});
        } else {
            this.sortColumns.push({column: sortState.active, sortDirection: -1});
        }
        this.loadUsers();
    }

    loadUsers() {
        this.lastUpdate = /* @__PURE__ */ new Date();
        this.store.dispatch(cognitoUserActions.loadUsers({
            prefix: this.state.value["cognito-user-list"].prefix,
            pageSize: this.state.value["cognito-user-list"].pageSize,
            pageIndex: this.state.value["cognito-user-list"].pageIndex,
            sortColumns: this.state.value["cognito-user-list"].sortColumns
        }));
    }

    addUser() {
        const dialogConfig = new MatDialogConfig();
        dialogConfig.disableClose = true;
        dialogConfig.autoFocus = true;
        this.dialog.open(UserAddComponentDialog, dialogConfig).afterClosed().subscribe((result) => {
            if (result) {
                this.createUser(result);
            }
        });
    }

    createUser(userName) {
        this.cognitoService.createUser(this.userPoolId, userName).subscribe(() => {
            this.snackBar.open("User created, name: " + userName, "Done", {duration: 5e3});
            this.loadUsers();
        });
    }

    confirmUser(userPoolId, userName) {
        this.lastUpdate = /* @__PURE__ */ new Date();
        this.store.dispatch(cognitoUserActions.confirmUser({
            userPooId: userPoolId,
            userName
        }));
    }

    deleteUser(userName) {
        this.cognitoService.deleteUser(this.userPoolId, userName).subscribe(() => {
            this.snackBar.open("User deleted, name: " + userName, "Done", {duration: 5e3});
            this.loadUsers();
        });
    }

    static {
        this.\u0275fac = function CognitoUserListComponent_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _CognitoUserListComponent)(\u0275\u0275directiveInject(MatSnackBar), \u0275\u0275directiveInject(MatDialog), \u0275\u0275directiveInject(ActivatedRoute), \u0275\u0275directiveInject(Location), \u0275\u0275directiveInject(Store), \u0275\u0275directiveInject(State), \u0275\u0275directiveInject(CognitoService2), \u0275\u0275directiveInject(ActionsSubject));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _CognitoUserListComponent,
            selectors: [["cognito-user-list"]],
            features: [\u0275\u0275ProvidersFeature([CognitoService2])],
            decls: 33,
            vars: 25,
            consts: [["appearance", "outlined", 2, "margin", "3px"], ["aria-label", "Back", "mat-icon-button", "", 1, "head-buttons-left", 3, "click"], [1, "fill-remaining-space"], ["aria-label", "Refresh", "mat-icon-button", "", 3, "click"], ["appearance", "outlined", 2, "margin", "-10px"], [1, "head-buttons"], [2, "width", "100%"], ["matInput", "", "name", "search", "placeholder", "Search", "type", "text", 3, "ngModelChange", "ngModel"], ["mat-icon-button", "", "matSuffix", "", "style", "float: right", 3, "click", 4, "ngIf"], [1, "table-container"], ["class", "row", 4, "ngIf"], ["aria-label", "Select page", 2, "width", "99%", "margin-left", "15px", 3, "page", "disabled", "hidePageSize", "length", "pageIndex", "pageSizeOptions", "pageSize", "showFirstLastButtons"], [1, "footer"], ["mat-icon-button", "", "matSuffix", "", 2, "float", "right", 3, "click"], ["matSuffix", ""], [1, "row"], ["mat-table", "", "matSort", "", 1, "mat-elevation-z8", "queue-table", 3, "matSortChange", "dataSource"], ["matColumnDef", "userName", "matTooltip", "User name"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "User name", "sortActionDescription", "Sort by userName", 4, "matHeaderCellDef"], ["mat-cell", "", 4, "matCellDef"], ["matColumnDef", "status", "matTooltip", "userStatus"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "User status", "sortActionDescription", "Sort by created", 4, "matHeaderCellDef"], ["matColumnDef", "enabled", "matTooltip", "enabled"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "User enabled", "sortActionDescription", "Sort by enabled", 4, "matHeaderCellDef"], ["matColumnDef", "created", "matTooltip", "Created"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Create timestamp", "sortActionDescription", "Sort by created", 4, "matHeaderCellDef"], ["matColumnDef", "modified", "matTooltip", "Modified"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Modified timestamp", "sortActionDescription", "Sort by modified", 4, "matHeaderCellDef"], ["matColumnDef", "actions"], ["mat-header-cell", "", "style", "width:120px", 4, "matHeaderCellDef"], ["mat-header-row", "", 4, "matHeaderRowDef"], ["mat-row", "", 4, "matRowDef", "matRowDefColumns"], ["class", "mat-row", 4, "matNoDataRow"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "User name", "sortActionDescription", "Sort by userName"], ["mat-cell", ""], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "User status", "sortActionDescription", "Sort by created"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "User enabled", "sortActionDescription", "Sort by enabled"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Create timestamp", "sortActionDescription", "Sort by created"], ["mat-header-cell", "", "mat-sort-header", "", "matTooltip", "Modified timestamp", "sortActionDescription", "Sort by modified"], ["mat-header-cell", "", 2, "width", "120px"], ["aria-label", "List", "mat-icon-button", "", "matTooltip", "Confirm the user", 3, "click"], ["aria-label", "DeleteUser", "mat-icon-button", "", "matTooltip", "Delete user", 3, "click"], ["mat-header-row", ""], ["mat-row", ""], [1, "mat-row"], [1, "mat-cell"]],
            template: function CognitoUserListComponent_Template(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275elementStart(0, "mat-card", 0)(1, "mat-card-header")(2, "button", 1);
                    \u0275\u0275listener("click", function CognitoUserListComponent_Template_button_click_2_listener() {
                        return ctx.back();
                    });
                    \u0275\u0275elementStart(3, "mat-icon");
                    \u0275\u0275text(4, "arrow_back");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(5, "span", 2)(6, "h4");
                    \u0275\u0275text(7);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(8, "button", 3);
                    \u0275\u0275listener("click", function CognitoUserListComponent_Template_button_click_8_listener() {
                        return ctx.addUser();
                    });
                    \u0275\u0275elementStart(9, "mat-icon");
                    \u0275\u0275text(10, "add");
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(11, "button", 3);
                    \u0275\u0275listener("click", function CognitoUserListComponent_Template_button_click_11_listener() {
                        return ctx.refresh();
                    });
                    \u0275\u0275elementStart(12, "mat-icon");
                    \u0275\u0275text(13, "refresh");
                    \u0275\u0275elementEnd()()();
                    \u0275\u0275elementStart(14, "mat-card-content")(15, "mat-card", 4)(16, "mat-card-actions", 5)(17, "mat-form-field", 6)(18, "mat-label");
                    \u0275\u0275text(19, "Prefix");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(20, "input", 7);
                    \u0275\u0275twoWayListener("ngModelChange", function CognitoUserListComponent_Template_input_ngModelChange_20_listener($event) {
                        \u0275\u0275twoWayBindingSet(ctx.prefixValue, $event) || (ctx.prefixValue = $event);
                        return $event;
                    });
                    \u0275\u0275elementEnd();
                    \u0275\u0275template(21, CognitoUserListComponent_button_21_Template, 3, 0, "button", 8)(22, CognitoUserListComponent_button_22_Template, 3, 0, "button", 8);
                    \u0275\u0275elementEnd()();
                    \u0275\u0275elementStart(23, "div", 9);
                    \u0275\u0275template(24, CognitoUserListComponent_div_24_Template, 23, 3, "div", 10);
                    \u0275\u0275pipe(25, "async");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(26, "mat-paginator", 11);
                    \u0275\u0275pipe(27, "async");
                    \u0275\u0275pipe(28, "async");
                    \u0275\u0275pipe(29, "async");
                    \u0275\u0275listener("page", function CognitoUserListComponent_Template_mat_paginator_page_26_listener($event) {
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
                    \u0275\u0275textInterpolate1("Cognito Users: ", ctx.userPoolId, "");
                    \u0275\u0275advance(13);
                    \u0275\u0275twoWayProperty("ngModel", ctx.prefixValue);
                    \u0275\u0275advance();
                    \u0275\u0275property("ngIf", !ctx.prefixSet);
                    \u0275\u0275advance();
                    \u0275\u0275property("ngIf", ctx.prefixSet);
                    \u0275\u0275advance(2);
                    \u0275\u0275property("ngIf", \u0275\u0275pipeBind1(25, 13, ctx.listUserCountersResponse$));
                    \u0275\u0275advance(2);
                    \u0275\u0275property("disabled", ctx.disabled)("hidePageSize", ctx.hidePageSize)("length", (tmp_7_0 = \u0275\u0275pipeBind1(27, 15, ctx.listUserCountersResponse$)) == null ? null : tmp_7_0.total)("pageIndex", \u0275\u0275pipeBind1(28, 17, ctx.pageIndex$))("pageSizeOptions", ctx.showPageSizeOptions ? ctx.pageSizeOptions : \u0275\u0275pureFunction0(24, _c02))("pageSize", \u0275\u0275pipeBind1(29, 19, ctx.pageSize$))("showFirstLastButtons", ctx.showFirstLastButtons);
                    \u0275\u0275advance(5);
                    \u0275\u0275textInterpolate1(" Last update: ", \u0275\u0275pipeBind2(32, 21, ctx.lastUpdate, "HH:mm:ss"), " ");
                }
            },
            dependencies: [MatCard, MatCardHeader, MatCardContent, MatCardActions, MatTable, MatHeaderCellDef, MatCellDef, MatColumnDef, MatIcon, MatHeaderCell, MatCell, MatHeaderRowDef, MatHeaderRow, MatSortHeader, MatRowDef, MatNoDataRow, MatIconButton, MatRow, MatPaginator, MatSort, MatTooltip, MatFormField, MatInput, MatLabel, MatSuffix, NgIf, DefaultValueAccessor, NgControlStatus, NgModel, DatePipe, AsyncPipe],
            styles: ["\n\n.fill-remaining-space[_ngcontent-%COMP%] {\n  flex: 1 1 auto;\n}\n.table-container[_ngcontent-%COMP%] {\n  max-height: calc(100vh - 10px);\n  max-width: calc(100vw - 15px);\n  overflow: hidden;\n}\n.footer[_ngcontent-%COMP%] {\n  display: flex;\n  width: 50%;\n  font-size: x-small;\n  color: black;\n  padding-top: 15px;\n  padding-left: 15px;\n}\n/*# sourceMappingURL=user-list.component.css.map */"]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(CognitoUserListComponent, {
        className: "CognitoUserListComponent",
        filePath: "src/app/modules/cognito/user-list/user-list.component.ts",
        lineNumber: 25
    });
})();

// src/app/modules/cognito/cognito-routing.module.ts
var routes = [
    {
        path: "",
        title: "CognitoUserPoolsList",
        component: CognitoUserPoolListComponent
    },
    // {
    //     path: 'details/:queueArn',
    //     title: 'SQSQueueDetails',
    //     component: SqsQueueDetailComponent
    // },
    {
        path: "users/:userPoolId",
        title: "UserList",
        component: CognitoUserListComponent
    }
];
var CognitoRoutingModule = class _CognitoRoutingModule {
    static {
        this.\u0275fac = function CognitoRoutingModule_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _CognitoRoutingModule)();
        };
    }
    static {
        this.\u0275mod = /* @__PURE__ */ \u0275\u0275defineNgModule({type: _CognitoRoutingModule});
    }
    static {
        this.\u0275inj = /* @__PURE__ */ \u0275\u0275defineInjector({imports: [RouterModule.forChild(routes), RouterModule]});
    }
};

// src/app/modules/cognito/user-pool-list/state/cognito-userpool-list.effects.ts
var CognitoUserPoolListEffects = class _CognitoUserPoolListEffects {
    constructor(actions$, cognitoService) {
        this.actions$ = actions$;
        this.cognitoService = cognitoService;
        this.loadUserPools$ = createEffect(() => this.actions$.pipe(ofType(cognitoUserpoolListActions.loadUserPools), mergeMap((action) => this.cognitoService.listUserPoolCounters(action.prefix, action.pageSize, action.pageIndex, action.sortColumns).pipe(map((userPools) => cognitoUserpoolListActions.loadUserPoolsSuccess({userPools})), catchError((error) => of(cognitoUserpoolListActions.loadUserPoolsFailure({error: error.message})))))));
        this.addUserPool$ = createEffect(() => this.actions$.pipe(ofType(cognitoUserpoolListActions.deleteUserPool), mergeMap((action) => this.cognitoService.deleteUserPool(action.userPoolName).pipe(map(() => cognitoUserpoolListActions.addUserPoolSuccess()), catchError((error) => of(cognitoUserpoolListActions.addUserPoolFailure({error: error.message})))))));
        this.deleteUserPool$ = createEffect(() => this.actions$.pipe(ofType(cognitoUserpoolListActions.deleteUserPool), mergeMap((action) => this.cognitoService.deleteUserPool(action.userPoolName).pipe(map(() => cognitoUserpoolListActions.deleteUserPoolSuccess()), catchError((error) => of(cognitoUserpoolListActions.deleteUserPoolFailure({error: error.message})))))));
    }

    static {
        this.\u0275fac = function CognitoUserPoolListEffects_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _CognitoUserPoolListEffects)(\u0275\u0275inject(Actions), \u0275\u0275inject(CognitoService2));
        };
    }
    static {
        this.\u0275prov = /* @__PURE__ */ \u0275\u0275defineInjectable({token: _CognitoUserPoolListEffects, factory: _CognitoUserPoolListEffects.\u0275fac});
    }
};

// src/app/modules/cognito/user-list/state/cognito-user-list.effects.ts
var CognitoUserListEffects = class _CognitoUserListEffects {
    constructor(actions$, cognitoService) {
        this.actions$ = actions$;
        this.cognitoService = cognitoService;
        this.loadUsers$ = createEffect(() => this.actions$.pipe(ofType(cognitoUserActions.loadUsers), mergeMap((action) => this.cognitoService.listUserCounters(action.prefix, action.pageSize, action.pageIndex, action.sortColumns).pipe(map((users) => cognitoUserActions.loadUsersSuccess({users})), catchError((error) => of(cognitoUserActions.loadUsersFailure({error: error.message})))))));
        this.addUser$ = createEffect(() => this.actions$.pipe(ofType(cognitoUserActions.addUser), mergeMap((action) => this.cognitoService.createUser(action.userPoolName, action.userName).pipe(map((queues) => cognitoUserActions.addUserSuccess()), catchError((error) => of(cognitoUserActions.addUserFailure({error: error.message})))))));
        this.confirmUser$ = createEffect(() => this.actions$.pipe(ofType(cognitoUserActions.confirmUser), mergeMap((action) => this.cognitoService.confirmUser(action.userPooId, action.userName).pipe(map((queues) => cognitoUserActions.deleteUserSuccess()), catchError((error) => of(cognitoUserActions.deleteUserFailure({error: error.message})))))));
        this.deleteUser$ = createEffect(() => this.actions$.pipe(ofType(cognitoUserActions.deleteUser), mergeMap((action) => this.cognitoService.deleteUserPool(action.userPoolName).pipe(map((queues) => cognitoUserActions.deleteUserSuccess()), catchError((error) => of(cognitoUserActions.deleteUserFailure({error: error.message})))))));
    }

    static {
        this.\u0275fac = function CognitoUserListEffects_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _CognitoUserListEffects)(\u0275\u0275inject(Actions), \u0275\u0275inject(CognitoService2));
        };
    }
    static {
        this.\u0275prov = /* @__PURE__ */ \u0275\u0275defineInjectable({token: _CognitoUserListEffects, factory: _CognitoUserListEffects.\u0275fac});
    }
};

// src/app/modules/cognito/cognito.module.ts
var CognitoModule = class _CognitoModule {
    static {
        this.\u0275fac = function CognitoModule_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _CognitoModule)();
        };
    }
    static {
        this.\u0275mod = /* @__PURE__ */ \u0275\u0275defineNgModule({type: _CognitoModule});
    }
    static {
        this.\u0275inj = /* @__PURE__ */ \u0275\u0275defineInjector({
            providers: [CognitoService2], imports: [
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
                CognitoRoutingModule,
                StoreModule.forFeature(cognitoUserPoolListFeatureKey, cognitoUserPoolListReducer),
                StoreModule.forFeature(cognitoUserListFeatureKey, cognitoUserListReducer),
                EffectsModule.forFeature([CognitoUserPoolListEffects, CognitoUserListEffects])
            ]
        });
    }
};
export {
    CognitoModule
};
//# sourceMappingURL=chunk-X2THYRGN.js.map

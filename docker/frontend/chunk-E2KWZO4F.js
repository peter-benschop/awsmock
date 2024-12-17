import {
    FormsModule,
    MAT_DIALOG_DATA,
    MatButton,
    MatDialogActions,
    MatDialogClose,
    MatDialogContent,
    MatDialogRef,
    MatDialogTitle,
    MatIcon,
    MatSnackBar,
    signal
} from "./chunk-LGOS2CJL.js";

// src/app/modules/infrastructure/import/file-import/file-import.component.ts
var _c0 = ["fileInput"];
var FileImportComponent = class _FileImportComponent {
    constructor(snackBar, dialogRef, data) {
        this.snackBar = snackBar;
        this.dialogRef = dialogRef;
        this.data = data;
        this.imageName = signal("");
        this.fileSize = signal(0);
        this.uploadProgress = signal(0);
        this.imagePreview = signal("");
        this.selectedFile = null;
        this.uploadSuccess = false;
        this.uploadError = false;
    }

    // Method to handle file upload
    // Handler for file input change
    onFileChange(event) {
        const file = event.target.files[0];
        this.uploadFile(file);
    }

    // Handler for file drop
    onFileDrop(event) {
        event.preventDefault();
        const file = event.dataTransfer?.files[0];
        this.uploadFile(file);
    }

    // Prevent default dragover behavior
    onDragOver(event) {
        event.preventDefault();
    }

    // Method to handle file upload
    uploadFile(file) {
        if (file && file.type.startsWith("application/json")) {
            this.selectedFile = file;
            this.fileSize.set(Math.round(file.size / 1024));
            const reader = new FileReader();
            reader.onload = () => {
                this.dialogRef.close(reader.result);
            };
            reader.readAsText(file);
            this.uploadSuccess = true;
            this.uploadError = false;
        } else {
            this.uploadSuccess = false;
            this.uploadError = true;
            this.snackBar.open("Only JSON files are supported!", "Close", {duration: 3e3, panelClass: "error"});
        }
    }

    // Method to remove the uploaded files
    removeFile() {
        this.selectedFile = null;
        this.imageName.set("");
        this.fileSize.set(0);
        this.imagePreview.set("");
        this.uploadSuccess = false;
        this.uploadError = false;
        this.uploadProgress.set(0);
    }

    static {
        this.\u0275fac = function FileImportComponent_Factory(__ngFactoryType__) {
            return new (__ngFactoryType__ || _FileImportComponent)(\u0275\u0275directiveInject(MatSnackBar), \u0275\u0275directiveInject(MatDialogRef), \u0275\u0275directiveInject(MAT_DIALOG_DATA));
        };
    }
    static {
        this.\u0275cmp = /* @__PURE__ */ \u0275\u0275defineComponent({
            type: _FileImportComponent,
            selectors: [["import-file-component"]],
            viewQuery: function FileImportComponent_Query(rf, ctx) {
                if (rf & 1) {
                    \u0275\u0275viewQuery(_c0, 5);
                }
                if (rf & 2) {
                    let _t;
                    \u0275\u0275queryRefresh(_t = \u0275\u0275loadQuery()) && (ctx.fileInput = _t.first);
                }
            },
            standalone: true,
            features: [\u0275\u0275StandaloneFeature],
            decls: 14,
            vars: 4,
            consts: [["fileInput", ""], ["mat-dialog-title", ""], [1, "mat-typography", 2, "width", "500px", "height", "200px"], [1, "file-upload-wrapper", 3, "dragover", "drop"], ["accept", "application/json", "hidden", "", "type", "file", 3, "change"], [1, "file-dropper", 3, "click"], ["align", "end"], ["mat-button", "", "mat-dialog-close", ""]],
            template: function FileImportComponent_Template(rf, ctx) {
                if (rf & 1) {
                    const _r1 = \u0275\u0275getCurrentView();
                    \u0275\u0275elementStart(0, "h2", 1);
                    \u0275\u0275text(1, "Upload Infrastructure");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(2, "mat-dialog-content", 2)(3, "div", 3);
                    \u0275\u0275listener("dragover", function FileImportComponent_Template_div_dragover_3_listener($event) {
                        \u0275\u0275restoreView(_r1);
                        return \u0275\u0275resetView(ctx.onDragOver($event));
                    })("drop", function FileImportComponent_Template_div_drop_3_listener($event) {
                        \u0275\u0275restoreView(_r1);
                        return \u0275\u0275resetView(ctx.onFileDrop($event));
                    });
                    \u0275\u0275elementStart(4, "input", 4, 0);
                    \u0275\u0275listener("change", function FileImportComponent_Template_input_change_4_listener($event) {
                        \u0275\u0275restoreView(_r1);
                        return \u0275\u0275resetView(ctx.onFileChange($event));
                    });
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(6, "div", 5);
                    \u0275\u0275listener("click", function FileImportComponent_Template_div_click_6_listener() {
                        \u0275\u0275restoreView(_r1);
                        const fileInput_r2 = \u0275\u0275reference(5);
                        return \u0275\u0275resetView(fileInput_r2.click());
                    });
                    \u0275\u0275elementStart(7, "mat-icon");
                    \u0275\u0275text(8, "upload");
                    \u0275\u0275elementEnd();
                    \u0275\u0275elementStart(9, "p");
                    \u0275\u0275text(10, "Upload file");
                    \u0275\u0275elementEnd()()()();
                    \u0275\u0275elementStart(11, "mat-dialog-actions", 6)(12, "button", 7);
                    \u0275\u0275text(13, "Cancel");
                    \u0275\u0275elementEnd()();
                }
                if (rf & 2) {
                    \u0275\u0275advance(3);
                    \u0275\u0275classProp("error", ctx.uploadError)("success", ctx.uploadSuccess);
                }
            },
            dependencies: [
                MatIcon,
                FormsModule,
                MatButton,
                MatDialogActions,
                MatDialogClose,
                MatDialogContent,
                MatDialogTitle
            ],
            styles: ["\n\n.file-upload-wrapper[_ngcontent-%COMP%] {\n  display: flex;\n  justify-content: center;\n  align-items: center;\n  flex-direction: column;\n  border: 2px dashed #ccc;\n  padding: 1rem;\n  margin-bottom: 1rem;\n  border-radius: 10px;\n  cursor: pointer;\n}\n.file-upload-wrapper.success[_ngcontent-%COMP%] {\n  border-color: green;\n}\n.file-upload-wrapper.error[_ngcontent-%COMP%] {\n  border-color: red;\n}\n.file-dropper[_ngcontent-%COMP%] {\n  display: flex;\n  flex-direction: column;\n  align-items: center;\n}\n.image-name[_ngcontent-%COMP%] {\n  font-weight: bold;\n}\n.image-preview[_ngcontent-%COMP%] {\n  max-width: 100%;\n  height: auto;\n  margin-bottom: 0.5rem;\n  border-radius: 10px;\n}\n.delete-icon[_ngcontent-%COMP%] {\n  cursor: pointer;\n  color: red;\n}\n/*# sourceMappingURL=file-import.component.css.map */"]
        });
    }
};
(() => {
    (typeof ngDevMode === "undefined" || ngDevMode) && \u0275setClassDebugInfo(FileImportComponent, {
        className: "FileImportComponent",
        filePath: "src/app/modules/infrastructure/import/file-import/file-import.component.ts",
        lineNumber: 41
    });
})();

export {
    FileImportComponent
};
//# sourceMappingURL=chunk-E2KWZO4F.js.map

#include "TimedSettingEditor.h"
#include "ui_TimedSettingEditor.h"

TimedSettingEditor::TimedSettingEditor(QWidget* parent) : BasePumpScreen(parent, "", true, false, true), ui(new Ui::TimedSettingEditor) {
    ui->setupUi(this);
    ui->verticalLayout->insertWidget(0, buttonBar);
}

TimedSettingEditor::~TimedSettingEditor() {
    delete ui;
}

void TimedSettingEditor::openEditorFor(const TimedSetting& timedSet) {}

REGISTER_DERIVED_TYPE(TimedSettingEditor);

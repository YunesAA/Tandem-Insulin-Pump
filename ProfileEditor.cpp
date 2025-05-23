#include "ProfileEditor.h"
#include "ui_ProfileEditor.h"

ProfileEditor::ProfileEditor(QWidget* parent, const QString name)
    : BasePumpScreen(parent, name, true, false, true), ui(new Ui::ProfileEditor) {
    ui->setupUi(this);
    ui->verticalLayout->insertWidget(0, buttonBar);
    int width = buttonBar->layout()->itemAt(0)->widget()->sizeHint().width();
    ui->addButton->setMaximumWidth(width);
}

ProfileEditor::~ProfileEditor() {
    delete ui;
}

void ProfileEditor::loadProfileData(ProfileData* data) {
    openProfile = data;
    setTitle(data->getName() + " Editor");
    clearFormLayout();

    for (int i = 0; i < data->getTimedSettings().size(); i++) {
        addFormRow(data->getTimedSettings().at(i));
    }
}

void ProfileEditor::navigateToTimedSettingEditor(TimedSetting* set) {
    emit timedSettingButtonClicked(set);
}

void ProfileEditor::addTimedSetting() {
    TimedSetting* set = new TimedSetting(this);
    openProfile->addTimedSetting(set);
    addFormRow(set);
    emit timedSettingButtonClicked(set);
}

void ProfileEditor::clearFormLayout() {
    if (QLayout* oldLayout = ui->contentWidget->layout()) {
        QLayoutItem* item;

        while ((item = oldLayout->takeAt(0)) != nullptr) {
            if (QWidget* childWidget = item->widget()) {
                childWidget->setParent(nullptr);
            }

            delete item;
        }

        delete oldLayout;
    }

    QFormLayout* newLayout = new QFormLayout();
    ui->contentWidget->setLayout(newLayout);
}

void ProfileEditor::addFormRow(TimedSetting* set) {
    QFormLayout* layout = dynamic_cast<QFormLayout*>(ui->contentWidget->layout());
    QPushButton* del = new QPushButton("Delete");
    connect(set, &TimedSetting::timedSettingClicked, this, &ProfileEditor::navigateToTimedSettingEditor);
    del->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
    layout->addRow(del, set);
}

REGISTER_DERIVED_TYPE(ProfileEditor);

#include "ProfileActionsScreen.h"
#include "ui_ProfileActionsScreen.h"

ProfileActionsScreen::ProfileActionsScreen(QWidget* parent)
    : BasePumpScreen(parent, "Actions"), ui(new Ui::ProfileActionsScreen) {
    ui->setupUi(this);
    ui->verticalLayout->insertWidget(0, buttonBar);
}

ProfileActionsScreen::~ProfileActionsScreen() {
    delete ui;
}

void ProfileActionsScreen::loadProfile(ProfileData* data) {
    openProfile = data;
    setTitle(data->getName());
}

void ProfileActionsScreen::navigateToProfileEditor() {
    emit editButtonClicked(openProfile);
}

void ProfileActionsScreen::activateProfile() {
    openProfile->setActive(true);
    emit activateButtonClicked();
}

void ProfileActionsScreen::duplicateProfile() {
    emit duplicateButtonClicked();
}

void ProfileActionsScreen::deleteProfile() {
    emit deleteButtonClicked();
}

void ProfileActionsScreen::renameProfile() {
    connect(titleEdit, &QLineEdit::returnPressed, this, &ProfileActionsScreen::completeRename);
    connect(this, &BasePumpScreen::backClicked, this, &ProfileActionsScreen::completeRename);
    connect(this, &BasePumpScreen::confirmed, this, &ProfileActionsScreen::completeRename);
    renameTitle();
}

void ProfileActionsScreen::completeRename() {
    openProfile->setName(titleEdit->text());
}

REGISTER_DERIVED_TYPE(ProfileActionsScreen);

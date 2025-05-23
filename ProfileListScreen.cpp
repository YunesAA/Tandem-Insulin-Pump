#include "ProfileListScreen.h"
#include "ui_ProfileListScreen.h"

ProfileListScreen::ProfileListScreen(QWidget* parent)
    : BasePumpScreen(parent, "Personal Profiles", true, true), ui(new Ui::ProfileListScreen) {
    ui->setupUi(this);
    ui->verticalLayout->insertWidget(0, buttonBar);
    doubleButtonHeight(ui->mealButton);
    doubleButtonHeight(ui->exerciseButton);
}

ProfileListScreen::~ProfileListScreen() {}

void ProfileListScreen::navigateToActionsScreen(ProfileData* data) {
    emit profileButtonClicked(data);
}

void ProfileListScreen::navigateToExerciseScreen() {
    emit exerciseButtonClicked();
}

void ProfileListScreen::navigateToMealScreen() {
    emit mealButtonClicked();
}

void ProfileListScreen::createProfile() {
    ProfileData* newPro = new ProfileData(ui->contentWidget);
    connect(newPro, &ProfileData::profileClicked, this, &ProfileListScreen::navigateToActionsScreen);
    doubleButtonHeight(newPro);
    ui->contentWidget->layout()->addWidget(newPro);
    emit profileButtonClicked(newPro);
}

void ProfileListScreen::updateProfile() {}

void ProfileListScreen::deleteProfile() {}

void ProfileListScreen::doubleButtonHeight(QPushButton* button) {
    int height = button->sizeHint().height();
    button->setMinimumHeight(height * 2);
}

REGISTER_DERIVED_TYPE(ProfileListScreen);

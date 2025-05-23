#include "UserProfileScreen.h"
#include "ui_UserProfileScreen.h"

UserProfileScreen::UserProfileScreen(QWidget* parent)
    : BasePumpScreen(parent, "Profile", true, false, true) {
    ui->setupUi(this);
    ui->verticalLayout->insertWidget(0, topBar);
}

UserProfileScreen::~UserProfileScreen() {
    delete ui;
}

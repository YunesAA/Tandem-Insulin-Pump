#include "BasePumpScreen.h"

BasePumpScreen::BasePumpScreen(QWidget* parent, const QString& title, bool hasBackBtn, bool hasAddBtn, bool hasConfirmBtn) : QWidget(parent) {
    if (hasAddBtn && hasConfirmBtn) throw new std::bad_function_call;

    initialBarSetup();
    popup = false;

    if (hasBackBtn) {
        QPushButton* back = new QPushButton();
        addButton(back, "Back", &BasePumpScreen::backClicked);
    }

    titleEdit = new QLineEdit(title);
    titleEdit->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
    titleEdit->setAlignment(Qt::AlignCenter);
    titleEdit->setFrame(false);
    titleEdit->setReadOnly(true);
    titleEdit->setStyleSheet("font-size: 20pt;");
    buttonBar->layout()->addWidget(titleEdit);

    if (hasAddBtn) addButton(new QPushButton(), "Add", &BasePumpScreen::addClicked);
    else if (hasConfirmBtn) addButton(new QPushButton(), "Confirm", &BasePumpScreen::confirmed);
    else if (hasBackBtn) {
        int width = buttonBar->layout()->itemAt(0)->widget()->sizeHint().width();
        buttonBar->layout()->addItem(new QSpacerItem(width, 0));
    }
}

BasePumpScreen::BasePumpScreen(bool pop) {
    popup = pop;
    initialBarSetup();
    QPushButton* close = new QPushButton();
    addButton(close, "Close", &BasePumpScreen::backClicked);
}

bool BasePumpScreen::isPopup() {
    return popup;
}

void BasePumpScreen::setTitle(const QString& title) {
    titleEdit->setText(title);
}

QList<BasePumpScreen*> BasePumpScreen::createAllDerived() {
    QList<BasePumpScreen*> instances;

    for (const auto &func : std::as_const(registry())) {
        instances.append(func());
    }

    return instances;
}

void BasePumpScreen::registerType(const QString &name, CreatorFunc func) {
    registry().insert(name, std::move(func));
}

void BasePumpScreen::renameTitle() {
    connect(titleEdit, &QLineEdit::returnPressed, this, &BasePumpScreen::completeTitleRename);
    connect(this, &BasePumpScreen::backClicked, this, &BasePumpScreen::completeTitleRename);
    connect(this, &BasePumpScreen::confirmed, this, &BasePumpScreen::completeTitleRename);
    titleEdit->setReadOnly(false);
    titleEdit->setFrame(true);
}

void BasePumpScreen::completeTitleRename() {
    disconnect(this, &BasePumpScreen::backClicked, this, &BasePumpScreen::completeTitleRename);
    disconnect(this, &BasePumpScreen::confirmed, this, &BasePumpScreen::completeTitleRename);
    titleEdit->setReadOnly(true);
    titleEdit->setFrame(false);
}

void BasePumpScreen::initialBarSetup() {
    buttonBar = new QWidget();
    buttonBar->setLayout(new QHBoxLayout);
    buttonBar->setStyleSheet("font-size: 12pt;");
    buttonBar->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
}

void BasePumpScreen::addButton(QPushButton* button, const QString& text, void (BasePumpScreen::*signal)()) {
    button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
    button->setText(text);
    buttonBar->layout()->addWidget(button);
    connect(button, &QPushButton::clicked, this, signal);
}

QMap<QString, BasePumpScreen::CreatorFunc>& BasePumpScreen::registry() {
    static QMap<QString, CreatorFunc> instance;
    return instance;
}

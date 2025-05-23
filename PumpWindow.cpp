#include "PumpWindow.h"
#include "BolusScreen.h"
#include "HistoryScreen.h"
#include "HomeScreen.h"
#include "OptionsScreen.h"
#include "ProfileActionsScreen.h"
#include "ProfileEditor.h"
#include "ProfileListScreen.h"
#include "ui_PumpWindow.h"
#include "HistoryScreen.h"
#include "InsulinStartScreen.h"
#include "InsulinStopScreen.h"
#include "AlarmPopup.h"
#include "ExerciseScreen.h"
#include "MealScreen.h"
#include "TimedSettingEditor.h"

PumpWindow::PumpWindow(QWidget* parent, DeliveryHistory* delivery_history)
    : QMainWindow(parent), ui(new Ui::PumpWindow), deliveryHistory(delivery_history) {
    ui->setupUi(this);
    batteryIndicator = new BatteryIndicator(this);
    batteryIndicator->setPowerOffAction(ui->actionPowerOff);
    initStateMachine();
    this->getScreen<HistoryScreen>()->setDeliveryHistory(delivery_history);
    this->getScreen<HomeScreen>()->setDeliveryHistory(delivery_history);
    connections();
    connect(getScreen<InsulinStopScreen>(), &InsulinStopScreen::insulinStopConfirmed,
            getScreen<OptionsScreen>(), &OptionsScreen::onInsulinStopped);
    connect(getScreen<InsulinStartScreen>(), &InsulinStartScreen::insulinStartConfirmed,
            getScreen<OptionsScreen>(), &OptionsScreen::onInsulinResumed);
}

PumpWindow::~PumpWindow() {
    delete ui;
}

void PumpWindow::connections() {
    connect(getScreen<InsulinStopScreen>(), &InsulinStopScreen::insulinStopConfirmed,
            getScreen<OptionsScreen>(), &OptionsScreen::onInsulinStopped);
    connect(getScreen<InsulinStartScreen>(), &InsulinStartScreen::insulinStartConfirmed,
            getScreen<OptionsScreen>(), &OptionsScreen::onInsulinResumed);
}

void PumpWindow::initStateMachine() {
    screenStateMachine = new QStateMachine();
    mainState = new QState(QState::ExclusiveStates);
    screenStateMachine->addState(mainState);
    history = new QHistoryState(mainState);
    initAllStates();
    history->setDefaultState(getState<HomeScreen>());
    mainState->setInitialState(getState<HomeScreen>());
    initTransitions();
    screenStateMachine->setInitialState(mainState);
    screenStateMachine->start();
}

void PumpWindow::initAllStates() {
    QList<BasePumpScreen*> screens = BasePumpScreen::createAllDerived();

    for (int i = 0; i < screens.size(); i++) {
        screenStateMap[screens[i]] = initState(screens[i]);
    }
}

QState* PumpWindow::initState(BasePumpScreen* screen) {
    if (!screen) {
        qFatal("initState was passed a nullptr 'screen'");
    }

    QState* state;
    static int stackIndex = 0;
    ui->screenStack->addWidget(screen);

    if (screen->isPopup()) {
        state = new QState();
        screenStateMachine->addState(state);
    } else state = new QState(mainState);

    state->assignProperty(ui->screenStack, "currentIndex", stackIndex++);
    return state;
}

void PumpWindow::initTransitions() {
    // Miscellaneous
    BasePumpScreen* powerOff = new BasePumpScreen(true);
    QState* powerOffState = initState(powerOff);
    // Transitions
    powerOffState->addTransition(ui->actionPowerOn, &QAction::triggered, history);
    mainState->addTransition(ui->homeButton, &QPushButton::clicked, getState<HomeScreen>());
    mainState->addTransition(ui->actionPowerOff, &QAction::triggered, powerOffState);
    getState<AlarmPopup>()->addTransition(getScreen<AlarmPopup>(), &AlarmPopup::backClicked, getState<HomeScreen>());
    addCircularTransition<OptionsScreen>(&HomeScreen::optionsButtonClicked);
    addCircularTransition<BolusScreen>(&HomeScreen::bolusButtonClicked);
    addCircularTransition<InsulinStopScreen>(&OptionsScreen::stopInsulinButtonClicked);
    addCircularTransition<InsulinStartScreen>(&OptionsScreen::startInsulinButtonClicked);
    addCircularTransition<ProfileListScreen>(&OptionsScreen::profileButtonClicked);
    addCircularTransition<HistoryScreen>(&OptionsScreen::historyButtonClicked);
    addCircularTransition<>(&ProfileListScreen::profileButtonClicked, &ProfileActionsScreen::loadProfile);
    addCircularTransition<>(&ProfileActionsScreen::editButtonClicked, &ProfileEditor::loadProfileData);
    addCircularTransition<InsulinStopScreen>(&OptionsScreen::stopInsulinButtonClicked);
    addCircularTransition<InsulinStartScreen>(&OptionsScreen::startInsulinButtonClicked);
    addCircularTransition<HomeScreen>(&InsulinStopScreen::insulinStopConfirmed);
    addCircularTransition<HomeScreen>(&InsulinStartScreen::insulinStartConfirmed);
    addCircularTransition<ExerciseScreen>(&ProfileListScreen::exerciseButtonClicked);
    addCircularTransition<MealScreen>(&ProfileListScreen::mealButtonClicked);
    addCircularTransition<TimedSettingEditor>(&ProfileEditor::timedSettingButtonClicked);
}

template<typename T> T* PumpWindow::getScreen() {
    for (auto i = screenStateMap.cbegin(), end = screenStateMap.cend(); i != end; ++i) {
        if (auto casted = qobject_cast<T*>(i.key())) {
            return casted;
        }
    }

    return nullptr;
}

template<typename T> QState* PumpWindow::getState() {
    for (auto i = screenStateMap.cbegin(), end = screenStateMap.cend(); i != end; ++i) {
        if (auto casted = qobject_cast<T*>(i.key())) {
            return i.value();
        }
    }

    return nullptr;
}

void PumpWindow::onBatteryCharged() {
    qDebug() << "onBatteryCharged";
    batteryIndicator->chargeBattery();
}

void PumpWindow::onRefillInsulin(){
    qDebug() << "onRefillInsulin";
    emit refillInsulin(200.0f);

}


#include "InsulinPump.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QTimer>
#include "BolusScreen.h"
#include "ExerciseScreen.h"
#include "HistoryScreen.h"
#include "HomeScreen.h"
#include "MealScreen.h"


InsulinPump::InsulinPump(QObject* parent) : QObject(parent),
    history(new DeliveryHistory),
    glucoseMonitor(new GlucoseMonitor),
    window(new PumpWindow(nullptr, history)),
    bolusCalc(new BolusCalculator(this)),
    reservoir(new InsulinReservoir),
    battery(new BatteryIndicator()),
    errHandler(new ErrorHandler(nullptr, history)),
    timer(new PumpTimer),
    dataGraph(new DataGraph(history)) {
    connect(bolusCalc, &BolusCalculator::bolusCalculatedImmediate, reservoir, &InsulinReservoir::bolusImmediateSlot);
    connect(bolusCalc, &BolusCalculator::bolusCalculatedExtended, reservoir, &InsulinReservoir::bolusExtendedSlot);
    connect(battery, &BatteryIndicator::batteryLow, errHandler, &ErrorHandler::handleLowBattery);
    connect(window->getScreen<BolusScreen>(), &BolusScreen::signalBolusCalculator, bolusCalc, &BolusCalculator::calculateBolus);
    connect(bolusCalc, &BolusCalculator::bolusCalculatedDisplay, window->getScreen<BolusScreen>(), &BolusScreen::displayBolusResult);
    connect(window->getScreen<ExerciseScreen>(), &ExerciseScreen::newExerciseSignal, glucoseMonitor, &GlucoseMonitor::addExerciseEventSlot);
    connect(window->getScreen<MealScreen>(), &MealScreen::newMealSignal, glucoseMonitor, &GlucoseMonitor::addMealEventSlot);
    connect(glucoseMonitor, &GlucoseMonitor::signalGlucoseLevel, history, &DeliveryHistory::addCGMDatumSlot);
    connect(glucoseMonitor, &GlucoseMonitor::signalBolusCalculator, bolusCalc, &BolusCalculator::calculateBolus);
    connect(timer, &PumpTimer::measureGlucose, glucoseMonitor, &GlucoseMonitor::measureGlucose);
    connect(glucoseMonitor, &GlucoseMonitor::handleLowGlucose, errHandler, &ErrorHandler::handleLowGlucose);
    connect(glucoseMonitor, &GlucoseMonitor::handleHighGlucose, errHandler, &ErrorHandler::handleHighGlucose);
    connect(history, &DeliveryHistory::newDataAddedSignal, window->getScreen<HistoryScreen>(), &HistoryScreen::updateNewData);
    connect(reservoir, &InsulinReservoir::levelChanged, window->getScreen<HomeScreen>()->getGauge(), &InsulinGauge::levelChanged);
    connect(reservoir, &InsulinReservoir::addDeliveryHistory, history, &DeliveryHistory::addEventSlot);
    connect(reservoir, &InsulinReservoir::addDeliveryHistory, glucoseMonitor, &GlucoseMonitor::insulinDeliverySlot);
    connect(glucoseMonitor, &GlucoseMonitor::signalInsulinReduction, reservoir, &InsulinReservoir::exerciseInsulinReduction);
    connect(bolusCalc, &BolusCalculator::bolusCalculated, history, &DeliveryHistory::addEventSlot);

    connect(window, &PumpWindow::refillInsulin,reservoir, &InsulinReservoir::setLevel);

    connect(reservoir, &InsulinReservoir::noInsulinSignal, errHandler, &ErrorHandler::handleNoInsulin);
    connect(reservoir, &InsulinReservoir::lowInsulin, errHandler, &ErrorHandler::handleLowInsulin);
}

InsulinPump::~InsulinPump() {
    delete window;
    delete bolusCalc;
    delete reservoir;
    delete battery;
    delete errHandler;
    delete timer;
    delete glucoseMonitor;
}

void InsulinPump::startSimulation() {
    qDebug() << "Starting dynamic insulin delivery simulation...";
    QDateTime now = QDateTime::currentDateTime();
    double initialMealDose = 7.0;
    reservoir->bolusImmediateSlot(initialMealDose, now);
    QTimer* mealTimer = new QTimer(this);
    connect(mealTimer, &QTimer::timeout, this, [this]() {
        qDebug() << "Simulating new meal...";
        QDateTime mealTime = QDateTime::currentDateTime();
        double mealDose = QRandomGenerator::global()->bounded(3, 8); // Random 3 to 7 inclusive
        reservoir->bolusImmediateSlot(mealDose, mealTime);
    });

    mealTimer->start(15000);
    QTimer* exerciseTimer = new QTimer(this);
    connect(exerciseTimer, &QTimer::timeout, this, [this]() {
        qDebug() << "Simulating exercise event...";
        double intensity = QRandomGenerator::global()->bounded(1, 4); // 1, 2, or 3
        int minutes = QRandomGenerator::global()->bounded(10, 41); // 10 to 40 minutes
        glucoseMonitor->addExerciseEventSlot(intensity, minutes);
    });

    exerciseTimer->start(30000);
    QTimer* insulinMonitor = new QTimer(this);
    connect(insulinMonitor, &QTimer::timeout, this, [this]() {
        float level = reservoir->getLevel();

        if (level < 30.0) {
            qDebug() << "Low insulin detected!";
            errHandler->handleLowInsulin();
        }
    });

    insulinMonitor->start(5000);
    qDebug() << "Simulation setup complete.";
}

ProfileData* InsulinPump::getActiveProfile() const {
    for (auto pro : userProfiles) {
        if (pro->isActive()) return pro;
    }

    return nullptr;
}

QList<ProfileData*> InsulinPump::getUserProfiles() const {
    return userProfiles;
}

PumpWindow* InsulinPump::getWindow() const {
    return window;
}

DeliveryHistory* InsulinPump::getHistory() const {
    return history;
}

BolusCalculator* InsulinPump::getBolusCalc() const {
    return bolusCalc;
}

InsulinReservoir* InsulinPump::getReservoir() const {
    return reservoir;
}

BatteryIndicator* InsulinPump::getBattery() const {
    return battery;
}

ErrorHandler* InsulinPump::getErrHandler() const {
    return errHandler;
}

PumpTimer* InsulinPump::getTimer() const {
    return timer;
}

GlucoseMonitor* InsulinPump::getGlucoseMonitor() const {
    return glucoseMonitor;
}

DataGraph* InsulinPump::getDataGraph() const {
    return dataGraph;
}

#include <QApplication>
#include <QRegularExpression>
#include "PumpWindow.h"
#include "InsulinPump.h"
#include <QtGlobal>
#include <QTime>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    InsulinPump insulin_pump;
    insulin_pump.getWindow()->show();
    // insulin_pump.startSimulation(); // Do not need
    // insulin_pump.getHistory()->addTestData();
    return a.exec();
}

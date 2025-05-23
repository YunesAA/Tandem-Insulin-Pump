QT += core gui
QT += statemachine
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AlarmPopup.cpp \
    BasePumpScreen.cpp \
    BatteryIndicator.cpp \
    BolusCalculator.cpp \
    BolusScreen.cpp \
    DataGraph.cpp \
    DeliveryError.cpp \
    DeliveryEvent.cpp \
    DeliveryHistory.cpp \
    ErrorDialog.cpp \
    ErrorHandler.cpp \
    ExerciseScreen.cpp \
    GlucoseMonitor.cpp \
    HistoryScreen.cpp \
    HomeScreen.cpp \
    InsulinPump.cpp \
    InsulinReservoir.cpp \
    InsulinGauge.cpp \
    InsulinStartScreen.cpp \
    InsulinStopScreen.cpp \
    MealScreen.cpp \
    OptionsScreen.cpp \
    ProfileActionsScreen.cpp \
    ProfileData.cpp \
    ProfileEditor.cpp \
    ProfileListScreen.cpp \
    PumpTimer.cpp \
    PumpWindow.cpp \
    TimedSetting.cpp \
    TimedSettingEditor.cpp \
    main.cpp

HEADERS += \
    AlarmPopup.h \
    BasePumpScreen.h \
    BolusCalculator.h \
    DataGraph.h \
    DeliveryError.h \
    DeliveryEvent.h \
    DeliveryHistory.h \
    ErrorDialog.h \
    ExerciseScreen.h \
    GlucoseMonitor.h \
    InsulinGauge.h \
    BatteryIndicator.h \
    BolusScreen.h \
    ErrorHandler.h \
    HistoryScreen.h \
    HomeScreen.h \
    InsulinPump.h \
    InsulinReservoir.h \
    InsulinStartScreen.h \
    InsulinStopScreen.h \
    MealScreen.h \
    OptionsScreen.h \
    ProfileActionsScreen.h \
    ProfileData.h \
    ProfileEditor.h \
    ProfileListScreen.h \
    PumpTimer.h \
    PumpWindow.h \
    TimedSetting.h \
    TimedSettingEditor.h

FORMS += \
    AlarmPopup.ui \
    BatteryIndicator.ui \
    DataGraph.ui \
    ErrorDialog.ui \
    ExerciseScreen.ui \
    HistoryScreen.ui \
    InsulinGauge.ui \
    InsulinStartScreen.ui \
    InsulinStopScreen.ui \
    MealScreen.ui \
    OptionsScreen.ui \
    ProfileActionsScreen.ui \
    ProfileEditor.ui \
    ProfileListScreen.ui \
    PumpWindow.ui \
    HomeScreen.ui \
    BolusScreen.ui \
    TimedSettingButton.ui \
    TimedSettingEditor.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

STATECHARTS += \
	PumpStates.scxml

DISTFILES += \
	.gitignore

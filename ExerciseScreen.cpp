#include "ExerciseScreen.h"
#include "ui_ExerciseScreen.h"

ExerciseScreen::ExerciseScreen(QWidget* parent) : BasePumpScreen(parent, "Exercise"), ui(new Ui::ExerciseScreen) {
    ui->setupUi(this);
    ui->verticalLayout->insertWidget(0, buttonBar);
}

ExerciseScreen::~ExerciseScreen() {
    delete ui;
}

void ExerciseScreen::newExerciseSlot() {
    QTime start_time = ui->startTime->time();
    QTime end_time = ui->endTime->time();
    int duration_minutes = qMax(0, start_time.secsTo(end_time) / 60);
    int combo_index = ui->comboBox->currentIndex() + 1;
    emit newExerciseSignal(combo_index, duration_minutes);
}

REGISTER_DERIVED_TYPE(ExerciseScreen);

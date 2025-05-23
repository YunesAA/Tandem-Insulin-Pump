#ifndef EXERCISESCREEN_H
#define EXERCISESCREEN_H

#include <QWidget>
#include "BasePumpScreen.h"

namespace Ui {
    class ExerciseScreen;
}

class ExerciseScreen : public BasePumpScreen {
        Q_OBJECT

    public:
        explicit ExerciseScreen(QWidget* parent = nullptr);
        ~ExerciseScreen();

    public slots:
        void newExerciseSlot();

    signals:
        void newExerciseSignal(double intensity, int minutes);

    private:
        Ui::ExerciseScreen* ui;
};

#endif // EXERCISESCREEN_H

#ifndef MEALSCREEN_H
#define MEALSCREEN_H

#include <QWidget>
#include "BasePumpScreen.h"

namespace Ui {
    class MealScreen;
}

class MealScreen : public BasePumpScreen {
        Q_OBJECT

    public:
        explicit MealScreen(QWidget* parent = nullptr);
        ~MealScreen();

    public slots:
        void newMealSlot();

    signals:
        void newMealSignal(double carbs);

    private:
        Ui::MealScreen* ui;
};

#endif // MEALSCREEN_H

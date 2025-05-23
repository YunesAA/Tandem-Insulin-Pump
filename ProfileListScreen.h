#ifndef PROFILELISTSCREEN_H
#define PROFILELISTSCREEN_H

#include <QWidget>
#include "BasePumpScreen.h"
#include "ProfileData.h"

namespace Ui {
    class ProfileListScreen;
}

class ProfileListScreen : public BasePumpScreen {
        Q_OBJECT

    public:
        explicit ProfileListScreen(QWidget* parent = nullptr);
        ~ProfileListScreen();

    signals:
        void profileButtonClicked(ProfileData*);
        void exerciseButtonClicked();
        void mealButtonClicked();

    private slots:
        void navigateToActionsScreen(ProfileData* data);
        void navigateToExerciseScreen();
        void navigateToMealScreen();
        void createProfile();
        void updateProfile();
        void deleteProfile();

    private:
        Ui::ProfileListScreen* ui;

        void doubleButtonHeight(QPushButton* button);
};

#endif // PROFILELISTSCREEN_H

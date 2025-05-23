#ifndef PROFILEACTIONSSCREEN_H
#define PROFILEACTIONSSCREEN_H

#include <QWidget>
#include "BasePumpScreen.h"
#include "ProfileData.h"

namespace Ui {
    class ProfileActionsScreen;
}

class ProfileActionsScreen : public BasePumpScreen {
        Q_OBJECT

    public:
        explicit ProfileActionsScreen(QWidget* parent = nullptr);
        ~ProfileActionsScreen();

    signals:
        void editButtonClicked(ProfileData*);
        void activateButtonClicked();
        void duplicateButtonClicked();
        void deleteButtonClicked();

    public slots:
        void loadProfile(ProfileData* data);
        void navigateToProfileEditor();
        void activateProfile();
        void duplicateProfile();
        void deleteProfile();
        void renameProfile();
        void completeRename();

    private:
        Ui::ProfileActionsScreen* ui;
        ProfileData* openProfile;
};

#endif // PROFILEACTIONSSCREEN_H

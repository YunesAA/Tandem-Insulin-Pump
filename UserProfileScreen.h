#ifndef USERPROFILESCREEN_H
#define USERPROFILESCREEN_H

#include <QString>
#include <QWidget>
#include "BasePumpScreen.h"

namespace Ui {
    class UserProfile;
}

class UserProfileScreen : public BasePumpScreen {
        Q_OBJECT

    public:
        explicit UserProfileScreen(QWidget* parent = nullptr);
        ~UserProfileScreen();

        void setProfileName(const QString& name);

    private:
        Ui::UserProfile* ui;

};

#endif // USERPROFILESCREEN_H

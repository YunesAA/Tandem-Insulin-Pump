#ifndef PROFILEEDITOR_H
#define PROFILEEDITOR_H

#include <QWidget>
#include "BasePumpScreen.h"
#include "ProfileData.h"

namespace Ui {
    class ProfileEditor;
}

class ProfileEditor : public BasePumpScreen {
        Q_OBJECT

    public:
        explicit ProfileEditor(QWidget* parent = nullptr, const QString = "");
        ~ProfileEditor();

    public slots:
        void loadProfileData(ProfileData* data);
        void navigateToTimedSettingEditor(TimedSetting* set);
        void addTimedSetting();

    signals:
        void timedSettingButtonClicked(TimedSetting*);

    private:
        Ui::ProfileEditor* ui;
        ProfileData* openProfile;

        void clearFormLayout();
        void addFormRow(TimedSetting* set);
};

#endif // PROFILEEDITOR_H

#ifndef TIMEDSETTINGEDITOR_H
#define TIMEDSETTINGEDITOR_H

#include <QTime>
#include <QWidget>
#include "BasePumpScreen.h"
#include "TimedSetting.h"

namespace Ui {
    class TimedSettingEditor;
}

class TimedSettingEditor : public BasePumpScreen {
        Q_OBJECT

    public:
        explicit TimedSettingEditor(QWidget* parent = nullptr);
        ~TimedSettingEditor();

    public slots:
        void openEditorFor(const TimedSetting& timedSet);

    private:
        Ui::TimedSettingEditor* ui;
};

#endif // TIMEDSETTINGEDITOR_H

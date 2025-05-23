#ifndef TIMEDSETTING_H
#define TIMEDSETTING_H

#include <QObject>
#include <QTime>
#include <QPushButton>

namespace Ui {
    class TimedSettingButton;
}

class TimedSetting : public QPushButton {
        Q_OBJECT
    public:
        explicit TimedSetting(QWidget* parent = nullptr);
        explicit TimedSetting(QTime* time, float basalRate, float carbRatio, float correctionFactor, float targetGlucose);
        TimedSetting(const TimedSetting& other);
        ~TimedSetting();

        QTime* getTime() const;
        float getBasalRate() const;
        float getCarbRatio() const;
        float getCorrectionFactor() const;
        float getTargetGlucose() const;

        QSize sizeHint() const override;

    public slots:
        void setTime(QTime* newTime);
        void setBasalRate(float newBasalRate);
        void setCarbRatio(float newCarbRatio);
        void setCorrectionFactor(float newCorrectionFactor);
        void setTargetGlucose(float newTargetGlucose);
        void openEditor();

    signals:
        void timedSettingClicked(TimedSetting*);

    private:
        Ui::TimedSettingButton* ui;
        QTime* time;
        float basalRate; // units per hour
        float carbRatio; // carbs per unit
        float correctionFactor; // glucose drop per unit
        float targetGlucose; // millimole per litre
};

#endif // TIMEDSETTING_H

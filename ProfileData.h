#ifndef PROFILEDATA_H
#define PROFILEDATA_H

#include <QObject>
#include "TimedSetting.h"
#include <QTimer>

class ProfileData : public QPushButton {
        Q_OBJECT

    public:
        explicit ProfileData(QWidget* parent = nullptr, const QString& proName = "Profile Name");

        QString getName() const;
        QTime getInsulinDuration() const;
        bool getCarbs() const;
        QList<TimedSetting*> getTimedSettings() const;
        bool isActive() const;
        TimedSetting* getCurrentTimedSetting() const;
        float getCurrentBasalRate() const;
        float getCurrentCarbRatio() const;
        float getCurrentCorrectionFactor() const;
        float getCurrentTargetGlucose() const;

    public slots:
        void setName(const QString& newName);
        void setInsulinDuration(const QTime& newInsulinDuration);
        void setCarbs(bool newCarbs);
        void setActive(bool newActive);
        void addTimedSetting(TimedSetting* newTimedSetting);
        void deleteTimedSetting(int index);
        void openActions();

    signals:
        void activated();
        void profileClicked(ProfileData*);

    private:
        QTimer* timer;
        QString name;
        bool active;
        QList<TimedSetting*> timedSettings;
        TimedSetting* activeTimedSetting;
        QTime insulinDuration;
        bool carbs;
};

#endif // PROFILEDATA_H

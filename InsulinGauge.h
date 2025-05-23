#ifndef INSULINGAUGE_H
#define INSULINGAUGE_H

#include <QWidget>
#include <QObject>

namespace Ui {
    class InsulinGauge;
}

class InsulinGauge : public QWidget {
        Q_OBJECT

    public:
        explicit InsulinGauge(QWidget* parent = nullptr);
        ~InsulinGauge();
        int insulinlevel;
        void setInsulinlevel();

    public slots:
        void levelChanged(float level);


    private:
        Ui::InsulinGauge* ui;

};

#endif // INSULINGAUGE_H

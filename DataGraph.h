#ifndef DATA_GRAPH_H
#define DATA_GRAPH_H

#include <QWidget>
#include <QChart>
#include <QSplineSeries>
#include <QChartView>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QTimer>
#include "DeliveryHistory.h"

class DataGraph : public QWidget {
        Q_OBJECT

    public:
        explicit DataGraph(DeliveryHistory* history = nullptr, QWidget* parent = nullptr);
        ~DataGraph();

    public slots:
        void updateGraph();
        void setWindowMinutes(double minutes);

    private:

        QFont titleFont;
        QChart* chart;
        QChartView* chartView;
        QSplineSeries* cgmSpline;
        QDateTimeAxis* xAxis;
        QValueAxis* yAxis;
        QTimer* graphTimer;

        DeliveryHistory* deliveryHistory;
        int lastPlottedIndex;
        double windowMinutes;
};

#endif // DATA_GRAPH_H

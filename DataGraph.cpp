#include "DataGraph.h"
#include <QVBoxLayout>
#include <QtMath>
#include <algorithm>

DataGraph::DataGraph(DeliveryHistory* history, QWidget* parent) :
    QWidget(parent), chart(new QChart()),
    chartView(new QChartView(chart)),
    cgmSpline(new QSplineSeries()),
    xAxis(new QDateTimeAxis()),
    yAxis(new QValueAxis()),
    graphTimer(new QTimer(this)),
    deliveryHistory(history),
    lastPlottedIndex(0) {
    windowMinutes = 60.0;
    // Chart setup
    chart->legend()->hide();
    chart->setTitle("Continuous Glucose Monitoring (CGM)");
    chart->setBackgroundBrush(QBrush(Qt::white));
    // Title setup
    titleFont.setBold(true);
    titleFont.setPointSize(14);
    chart->setTitleFont(titleFont);
    // X-axis setup
    xAxis->setFormat("hh:mm");   // show as 24-hour clock
    xAxis->setTitleText("Time (HH:MM)");
    xAxis->setTickCount(7);
    chart->addAxis(xAxis, Qt::AlignBottom);
    // Y-axis setup
    yAxis->setTitleText("Blood Glucose (mmol/L)");
    yAxis->setRange(0, 200);
    chart->addAxis(yAxis, Qt::AlignLeft);
    // Spline Series setup
    QPen pen(Qt::red);
    pen.setWidth(4);
    cgmSpline->setPen(pen);
    chart->addSeries(cgmSpline);
    cgmSpline->attachAxis(xAxis);
    cgmSpline->attachAxis(yAxis);
    // ChartView setup
    chartView->setRenderHint(QPainter::Antialiasing);
    // Layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);
    // Timer for updates
    connect(graphTimer, &QTimer::timeout, this, &DataGraph::updateGraph);
    graphTimer->start(1000); // every second
}

DataGraph::~DataGraph() {}

void DataGraph::setWindowMinutes(double minutes) {
    windowMinutes = minutes;
    updateGraph();
}

void DataGraph::updateGraph() {
    if (!deliveryHistory) {
        qDebug() << "Delivery history pointer doesnt exist.";
        return;
    }

    const QMap<QDateTime*, qreal>& cgmData = deliveryHistory->getCGMData();

    if (cgmData.isEmpty()) {
        return;
    }

    QList<QPair<QDateTime, qreal>> sortedCGM;
    for (auto it = cgmData.begin(); it != cgmData.end(); ++it) {
        if (it.key()) {
            sortedCGM.append(qMakePair(*it.key(), it.value()));
        }
    }

    std::sort(sortedCGM.begin(), sortedCGM.end(),
    [](const QPair<QDateTime, qreal>& a, const QPair<QDateTime, qreal>& b) {
        return a.first < b.first;
    });

    if (lastPlottedIndex >= sortedCGM.size()) {
        return;
    }

    // Adds only new points
    for (int i = lastPlottedIndex; i < sortedCGM.size(); ++i) {
        qint64 timestamp = sortedCGM[i].first.toMSecsSinceEpoch();
        cgmSpline->append(timestamp, sortedCGM[i].second);
        //qDebug() << "Added point X:" << minutes << " Y:" << sortedCGM[i].second;
    }
    // Update last plotted index
    lastPlottedIndex = sortedCGM.size();

    if (!cgmSpline->points().isEmpty()) {
        // X-axis sliding
        qint64 latestTime = cgmSpline->points().last().x();
        qint64 minVisibleTime = latestTime - (windowMinutes * 60 * 1000); // convert windowMinutes into milliseconds

        if (minVisibleTime < 0) minVisibleTime = 0;

        xAxis->setRange(QDateTime::fromMSecsSinceEpoch(minVisibleTime),
                        QDateTime::fromMSecsSinceEpoch(latestTime));
        // Y-axis dynamic buffer
        QVector<QPointF> points = cgmSpline->points();
        double minY = points.first().y();
        double maxY = points.first().y();

        for (const QPointF& p : points) {
            if (p.x() >= minVisibleTime && p.x() <= latestTime) { // only points in visible window
                if (p.y() < minY) {
                    minY = p.y();
                }

                if (p.y() > maxY) {
                    maxY = p.y();
                }
            }
        }

        double buffer = 10.0;
        double yMin = qMax(0.0, minY - buffer);
        double yMax = maxY + buffer;
        yAxis->setRange(yMin, yMax);
    }
    chart->update();
    chartView->update();
}

#ifndef DRAWING_H
#define DRAWING_H

#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QChart>
#include <QList>
#include <QDebug>

QT_CHARTS_USE_NAMESPACE

class Drawing
{
public:
    QChartView virtual *draw(QList<QByteArray> x_list, QList<QByteArray> y_list) = 0;
};

class MyMethodDraw : public Drawing
{
public:
    QChartView *draw(QList<QByteArray> x_list, QList<QByteArray> y_list) override;

};

class DrawCharts
{
public:
    DrawCharts(Drawing* drw);

    QChartView *draw(QList<QByteArray> x_list, QList<QByteArray> y_list);

    Drawing* p;
};

#endif // DRAWING_H

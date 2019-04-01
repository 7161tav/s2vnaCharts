#include "drawing.h"

QChartView *MyMethodDraw::draw(QList<QByteArray> x_list, QList<QByteArray> y_list)
{
    qDebug() << x_list;
    //QList<QByteArray> vectX = m_vect.split(',');
    qDebug() << y_list;
    QLineSeries *series = new QLineSeries();
    for(int i = 0; i < x_list.size(); i++)
    {
        series->append(x_list[i].toDouble(),y_list[i*2].toDouble());
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();    

    QPen pen(QRgb(0x000000));
    pen.setWidth(2);
    series->setPen(pen);

    chart->setAnimationOptions(QChart::AllAnimations);

    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    return chartView;
}

DrawCharts::DrawCharts(Drawing* drw) : p(drw)
{

}

QChartView *DrawCharts::draw(QList<QByteArray> x_list, QList<QByteArray> y_list)
{
    return p->draw(x_list,y_list);
}

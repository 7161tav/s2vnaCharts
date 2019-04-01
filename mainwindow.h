#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QtCharts/QChartView>


QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void SendToServer(QString str);
    void test();

public slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError);
    void slotConnected();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket* m_pTcpSocket;
    QByteArray m_data;
    QChartView* charts;
};

#endif // MAINWINDOW_H

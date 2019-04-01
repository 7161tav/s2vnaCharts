#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawing.h"
#include <QThread>
#include <QList>
#include <QRegExp>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost("127.0.0.1", 5025);

    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,         SLOT(slotError(QAbstractSocket::SocketError)));

    ui->comboBox_Sparam->addItem("S11");
    ui->comboBox_Sparam->addItem("S21");
    ui->comboBox_Sparam->addItem("S12");
    ui->comboBox_Sparam->addItem("S22");

    QRegExp exp("^[1-9][0-9]+");
    QRegExp exp1("^[1][0]+");
    ui->lineEdit_start->setValidator(new QRegExpValidator(exp, this));
    ui->lineEdit_stop->setValidator(new QRegExpValidator(exp, this));
    ui->lineEdit_point->setValidator(new QRegExpValidator(exp, this));
    ui->lineEdit_bwidth->setValidator(new QRegExpValidator(exp1, this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotReadyRead()
{        
    m_data.append(m_pTcpSocket->readAll());
    //qDebug() << *m_data;
}

void MainWindow::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
            "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                             "The host was not found." :
                             err == QAbstractSocket::RemoteHostClosedError ?
                                 "The remote host is closed." :
                                 err == QAbstractSocket::ConnectionRefusedError ?
                                     "The connection was refused." :
                                     QString(m_pTcpSocket->errorString()));
    ui->statusBar->showMessage(strError);
}

void MainWindow::SendToServer(QString str)
{
    QByteArray block = str.toUtf8();
    //qDebug() << block;
    m_pTcpSocket->write(block);
    m_pTcpSocket->waitForBytesWritten(500);
}

void MainWindow::slotConnected()
{
    ui->statusBar->showMessage("Received the connected signal");
}

void MainWindow::on_pushButton_clicked()
{
    m_data = NULL;
    if(charts != NULL)
        ui->gridLayout_chart->removeWidget(charts);

    SendToServer("SENS1:FREQ:STAR " + ui->lineEdit_start->text()+ ";" +
                 "STOP " + ui->lineEdit_stop->text() + ";" +
                 ":SENS1:SWE:POIN " + ui->lineEdit_point->text() + ";" +
                 ":SENS1:BWID " + ui->lineEdit_bwidth->text() + ";" +
                 ":CALC1:PAR:DEF " + ui->comboBox_Sparam->currentText() + "\n");
    SendToServer(":TRIG:SOUR BUS;:TRIG:SING\n");
    SendToServer("*OPC?\n");
    m_pTcpSocket->waitForReadyRead(2000);
    SendToServer("CALC:DATA:FDAT?\n");
    m_pTcpSocket->waitForReadyRead(20000);
    SendToServer("SENS:FREQ:DATA?\n");
    m_pTcpSocket->waitForReadyRead(20000);

    //qDebug() << m_data;

    QList<QByteArray> m_list = m_data.split('\n');
    if(m_list.size() != 4)
    {
        qDebug() << "!%";
        on_pushButton_clicked();
    }
    else
    {
        QList<QByteArray> y_list = m_list[1].split(',');
        QList<QByteArray> x_list = m_list[2].split(',');
        DrawCharts* drw = new DrawCharts(new MyMethodDraw);
        if(x_list.size() > y_list.size())
        {
            charts = drw->draw(y_list, x_list);
            ui->gridLayout_chart->addWidget(charts);
        }
        else
        {
            charts = drw->draw(x_list, y_list);
            ui->gridLayout_chart->addWidget(charts);
        }
    }
}



#ifndef SENDTOSERVER_H
#define SENDTOSERVER_H

#include <QObject>
#include <QTcpSocket>

class Worker : public QObject
{
    Q_OBJECT

public slots:
    void doWork(QTcpSocket* m_pTcpSocket,const QString &parameter)
    {
        QByteArray block = parameter.toUtf8();
        //qDebug() << block;
        m_pTcpSocket->write(block);
        emit resultReady(result);
    }

signals:
    void resultReady(const QString &result);
};

#endif // SENDTOSERVER_H

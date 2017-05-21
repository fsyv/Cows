#ifndef COMDATA_H
#define COMDATA_H

#include <QObject>

class QSerialPort;

class ComData : public QObject
{
    Q_OBJECT
public:
    ComData(QSerialPort *serialPort);
    ~ComData();

    void start();

private:
    QSerialPort *m_pSerialPort;

protected:
    void timerEvent(QTimerEvent *e);

private:
    int m_iTimerID;
    quint32 m_ui32Tick;

signals:
    void dataRecv(quint32 tick, qreal x, qreal y, qreal z);
};

#endif // COMDATA_H

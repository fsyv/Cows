#ifndef COMDATA_H
#define COMDATA_H

#include <QObject>

class QSerialPort;

class ComData : public QObject
{
    Q_OBJECT
public:
    ComData(const QString &portName);
    ~ComData();

private:
    QSerialPort *m_pSerialPort;

protected:
    void timerEvent(QTimerEvent *e);

private:
    int m_iTimerID;
};

#endif // COMDATA_H

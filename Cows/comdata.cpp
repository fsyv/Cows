#include "stdafx.h"

#include "comdata.h"

ComData::ComData(const QString &portName)
{
    m_pSerialPort = new QSerialPort();

    m_pSerialPort->setPortName(portName);
    if(m_pSerialPort->open(QIODevice::ReadOnly))
    {
        m_pSerialPort->setBaudRate(QSerialPort::Baud9600);
        m_pSerialPort->setDataBits(QSerialPort::Data8);
        m_pSerialPort->setParity(QSerialPort::NoParity);
        m_pSerialPort->setStopBits(QSerialPort::OneStop);
        m_pSerialPort->setFlowControl(QSerialPort::NoFlowControl);

        m_iTimerID = startTimer(1000);
    }
    else
    {
        QMessageBox::critical(nullptr, QString("错误"), QString("串口打开失败"));
    }
}

ComData::~ComData()
{
    killTimer(m_iTimerID);
    delete m_pSerialPort;
}



void ComData::timerEvent(QTimerEvent *e)
{
    qDebug() << m_pSerialPort->readAll();
}

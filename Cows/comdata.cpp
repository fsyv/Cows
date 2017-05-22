#include "stdafx.h"

#include "comdata.h"

ComData::ComData(QSerialPort *serialPort)
{
    m_pSerialPort = serialPort;
    m_ui32Tick = 0;

	qsrand(QDateTime::currentDateTime().toTime_t());
}

ComData::~ComData()
{
    killTimer(m_iTimerID);
    if(m_pSerialPort)
        delete m_pSerialPort;
    m_pSerialPort = nullptr;
}

void ComData::start()
{
    m_iTimerID = startTimer(1000);
}



void ComData::timerEvent(QTimerEvent *e)
{
    //QByteArray byteArray = m_pSerialPort->readAll();
    //if(byteArray.size() > 1)
    //{
    //    QStringList xyzList = QString(byteArray).split(',');
    //    if(xyzList.size() >= 3)
    //    {
    //        emit dataRecv(m_ui32Tick++, \
    //                      xyzList.at(0).toDouble(), \
    //                      xyzList.at(1).toDouble(), \
    //                      xyzList.at(2).toDouble()  \
    //                      );
    //    }
    //}
	emit dataRecv(m_ui32Tick++, qrand() % 10 - 5, qrand() % 10 - 5, qrand() % 10 - 5);
}

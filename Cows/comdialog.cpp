#include "stdafx.h"

#include "comdialog.h"
#include "ui_comdialog.h"

ComDialog::ComDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowMinimizeButtonHint);
    setWindowTitle(QString(" "));

    connect(this, &ComDialog::reflush, this, &ComDialog::flushCom);
    flushCom();
}

ComDialog::~ComDialog()
{
    delete ui;
}

QSerialPort *ComDialog::getSerialPort() const
{
    return m_pSerialPort;
}

bool ComDialog::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = reinterpret_cast<MSG*>(message);
    int msgType = msg->message;
    if(msgType == WM_DEVICECHANGE)
    {
        PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)msg->lParam;
        switch (msg->wParam) {
        case DBT_DEVICEARRIVAL:
        case DBT_DEVICEREMOVECOMPLETE:
            if(DBT_DEVTYP_PORT == lpdb->dbch_devicetype)
            {
                //串口变换的信号
                emit reflush();
            }
            break;
        }
    }
    return false;
}

void ComDialog::initComPort(QSerialPort *port)
{
    //设置波特率
    port->setBaudRate(ui->comboBoxBaudRate->currentText().toInt());

    //设置数据位
    QSerialPort::DataBits dataBit;
    switch (ui->comboBoxDataBits->currentText().toInt()) {
    case 5:
        dataBit = QSerialPort::Data5;
        break;
    case 6:
        dataBit = QSerialPort::Data6;
        break;
    case 7:
        dataBit = QSerialPort::Data7;
        break;
    case 8:
        dataBit = QSerialPort::Data8;
        break;
    default:
        dataBit = QSerialPort::UnknownDataBits;
        break;
    }
    port->setDataBits(dataBit);

    //设置校验位
    QSerialPort::Parity parity;
    switch (ui->comboBoxParity->currentIndex()) {
    case 0:
        parity = QSerialPort::NoParity;
        break;
    case 1:
        parity = QSerialPort::EvenParity;
        break;
    case 2:
        parity = QSerialPort::OddParity;
        break;
    case 3:
        parity = QSerialPort::SpaceParity;
        break;
    case 4:
        parity = QSerialPort::MarkParity;
        break;
    default:
        parity = QSerialPort::UnknownParity;
        break;
    }
    port->setParity(parity);

    //设置停止位
    QSerialPort::StopBits stopBits;
    switch (ui->comboBoxParity->currentIndex()) {
    case 0:
        stopBits = QSerialPort::OneStop;
        break;
    case 1:
        stopBits = QSerialPort::OneAndHalfStop;
        break;
    case 2:
        stopBits = QSerialPort::TwoStop;
        break;
    default:
        stopBits = QSerialPort::UnknownStopBits;
        break;
    }
    port->setStopBits(stopBits);

    //流控
    QSerialPort::FlowControl flowControl;
    switch (ui->comboBoxFlowControl->currentIndex()) {
    case 0:
        flowControl = QSerialPort::NoFlowControl;
        break;
    case 1:
        flowControl = QSerialPort::HardwareControl;
        break;
    case 2:
        flowControl = QSerialPort::SoftwareControl;
        break;
    default:
        flowControl = QSerialPort::UnknownFlowControl;
        break;
    }
    port->setFlowControl(flowControl);
}

void ComDialog::on_okButton_clicked()
{
    m_pSerialPort = new QSerialPort();

    m_pSerialPort->setPortName(ui->comboBoxComName->currentText());
    if(m_pSerialPort->open(QIODevice::ReadOnly))
    {
        initComPort(m_pSerialPort);
        close();
    }
    else
    {
        QMessageBox::critical(nullptr, QString("错误"), QString("串口打开失败"));
        delete m_pSerialPort;
    }
}

void ComDialog::on_closeButton_clicked()
{
    exit(0);
}

void ComDialog::flushCom()
{
    QStringList comList;
    for(auto info : QSerialPortInfo::availablePorts())
        comList<<info.portName();

    ui->comboBoxComName->clear();
    ui->comboBoxComName->addItems(comList);
}

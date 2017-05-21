#ifndef COMDIALOG_H
#define COMDIALOG_H

#include <QDialog>

namespace Ui {
class ComDialog;
}

class QSerialPort;

class ComDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ComDialog(QWidget *parent = 0);
    ~ComDialog();

    QSerialPort *getSerialPort() const;

protected:
    //抽插事件
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

    void initComPort(QSerialPort *port);
private slots:
    void on_okButton_clicked();

    void on_closeButton_clicked();

    void flushCom();

private:
    Ui::ComDialog *ui;
    QSerialPort *m_pSerialPort;

signals:
    void reflush();
};

#endif // COMDIALOG_H

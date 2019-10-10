#ifndef WIDGET_H
#define WIDGET_H
#include "structdata.h"
#include <QWidget>
#include <QSerialPortInfo>
#include <QByteArray>
namespace Ui {
class Widget;
}
class QSerialPort;
class DataControl;
class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    Ui::Widget *uiWidget() const;
    void initSerialport();
    void openSerialport();
    void closeSerialport();
    void updateSerialport();
    void sendData(const QByteArray&);
    void record(const QString&);
    void setQss(const QString &);

private slots:
    void on_serialControlPushButton_clicked();
    void receiveInfo();

    void on_btn_run_clicked();

    void on_btn_stop_clicked();

private:
    void initUi();
    Ui::Widget *ui;
    QSerialPort *m_serialport = nullptr;
    DataControl *m_data_control;
    QList <QSerialPortInfo> m_portInfolist;
    bool m_serialport_state;
    Package m_package;

};

#endif // WIDGET_H

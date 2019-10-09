#ifndef WIDGET_H
#define WIDGET_H
#include "structdata.h"
#include <QWidget>
#include <QSerialPortInfo>
namespace Ui {
class Widget;
}
class QSerialPort;
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void initSerialport();
    void openSerialport();
    void closeSerialport();
    void updateSerialport();
    void writeData();

private slots:
    void on_serialControlPushButton_clicked();
    void receiveInfo();

private:
    Ui::Widget *ui;
    QSerialPort *m_serialport;
    QList <QSerialPortInfo> m_portInfolist;
    bool m_serialport_state;
    Package m_package;

};

#endif // WIDGET_H

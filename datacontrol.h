#ifndef DATACONTROL_H
#define DATACONTROL_H
#include <QString>
#include <QByteArray>
#include "datawriter.h"
#include "datareader.h"
#include "structdata.h"
namespace Ui {
class Widget;
}

class Widget;
class QWidget;
class DataControl
{
public:
    DataControl(QWidget *widget = 0);
    ~DataControl();
    QByteArray serialTestData();
    QByteArray packge_to_bytearray(const Package&);
    void save_serial_config();
    void save_serial_tofile();
    void save_general_config();
    void save_general_tofile();

    void read_serial_config();
    void read_serial_fromfile();
    void read_general_config();
    void read_general_fromfile();

    void servo_config();

private:
    Widget *m_widget;
    Ui::Widget*m_ui;
    Package m_packge;
    SerialServoConfig m_serial_servo_config;
    GeneralServoConfig m_general_servo_config;
    ServoConfig m_servo_config;
    DataWriter m_date_writer;
    DataReader m_data_reader;
};

#endif // DATACONTROL_H

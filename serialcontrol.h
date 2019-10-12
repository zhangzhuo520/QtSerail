#ifndef SERIALCONTROL_H
#define SERIALCONTROL_H
#include "structdata.h"
class QSerialPort;
class SerialControl
{
public:
    explicit SerialControl(QSerialPort *serial_port);
    ~SerialControl();


private:
    QSerialPort *m_serial_port;
    Package *m_packge;
    ServoConfig *m_servo_config;
    SerialServoConfig *m_serial_config;
    GeneralServoConfig * m_generail_config;
};

#endif // SERIALCONTROL_H

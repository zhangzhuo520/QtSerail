#ifndef STRUCTDATA_H
#define STRUCTDATA_H
#include <QString>

class Package
{
public:
    typedef unsigned char uchar;
    explicit Package():
        header(0xfa),
        address(0x00),
        command(0x00),
        state(0x00),
        id_arg1(0x00),
        id_arg2(0x00),
        checknum(0x00),
        exitcode(0x00)
    {
        arg1[0] = 0x00;
        arg1[1] = 0x00;
        arg2[0] = 0x00;
        arg2[0] = 0x00;
    }

    ~Package(){}

    Package operator =(const Package &data)
    {
        this->header = data.header;
        this->address = data.address;
        this->command = data.command;
        this->state = data.state;
        this->id_arg1 = data.id_arg1;
        this->arg1[0] = data.arg1[0];
        this->arg1[1] = data.arg1[1];
        this->id_arg2 = data.id_arg2;
        this->checknum = data.checknum;
        this->exitcode = data.exitcode;
        return *this;
    }

    uchar header;
    uchar address;
    uchar command;
    uchar state;
    uchar id_arg1;
    uchar arg1[2];
    uchar id_arg2;
    uchar arg2[2];
    uchar checknum;
    uchar exitcode;
};

class ServoConfig
{
public:
    ServoConfig():
        motor("0"),
        signal_toler("0"),
        version("1.00.1"),
        power_enabel("0"),
        reset_position("0"),
        reset_time("0"),
        reset_step("0"),
        start_time("0"),
        start_step("0"),
        stalling_time("0"),
        enable_power_reset("0"),
        common_id("0"),
        servo_id("0")
    {}
    ~ServoConfig(){}

    ServoConfig operator =(const ServoConfig &data)
    {
        this->motor = data.motor;
        this->signal_toler = data.signal_toler;
        this->version = data.version;
        this->power_enabel = data.power_enabel;
        this->reset_position = data.reset_position;
        this->reset_time = data.reset_time;
        this->reset_step = data.reset_step;
        this->start_time = data.start_time;
        this->start_step = data.start_step;
        this->stalling_time = data.stalling_time;
        this->enable_power_reset = data.enable_power_reset;
        this->common_id = data.common_id;
        this->servo_id = data.servo_id;
        return *this;
    }

    QString motor;
    QString signal_toler;
    QString version;
    QString power_enabel;
    QString reset_position;
    QString reset_time;
    QString reset_step;
    QString start_time;
    QString start_step;
    QString stalling_time;
    QString enable_power_reset;
    QString common_id;
    QString servo_id;
};

class GeneralServoConfig
{
public:
    GeneralServoConfig(){}
    ~GeneralServoConfig(){}

    GeneralServoConfig operator =(const GeneralServoConfig &data)
    {
        this->power_top = data.power_top;
        this->power_mid = data.power_mid;
        this->power_bottom = data.power_bottom;
        this->start_valtage = data.start_valtage;
        this->drive_freq = data.drive_freq;
        this->die_area = data.die_area;
        this->angle_top = data.angle_top;
        this->angle_mid = data.angle_mid;
        this->angle_bottom = data.angle_bottom;
        this->max_output = data.max_output;
        this->freq_set = data.freq_set;
        this->selflock_set = data.selflock_set;
        this->signal_reset = data.signal_reset;
        this->servo_direction = data.servo_direction;
        this->stalling_guard = data.stalling_guard;
        this->guard_time = data.guard_time;
        this->guard_output = data.guard_output;
        return *this;
    }

    QString power_top;
    QString power_mid;
    QString power_bottom;
    QString start_valtage;
    QString drive_freq;
    QString die_area;
    QString angle_top;
    QString angle_mid;
    QString angle_bottom;
    QString max_output;
    QString freq_set;
    QString selflock_set;
    QString signal_reset;
    QString servo_direction;
    QString stalling_guard;
    QString guard_time;
    QString guard_output;
 };

class SerialServoConfig :  public GeneralServoConfig
{
public:
    SerialServoConfig()
    {

    }

    ~SerialServoConfig()
    {

    }

    SerialServoConfig operator =(const SerialServoConfig &data)
    {
        this->current_id = data.current_id;
        this->new_id = data.new_id;
        this->power_top = data.power_top;
        this->power_mid = data.power_mid;
        this->power_bottom = data.power_bottom;
        this->start_valtage = data.start_valtage;
        this->drive_freq = data.drive_freq;
        this->die_area = data.die_area;
        this->angle_top = data.angle_top;
        this->angle_mid = data.angle_mid;
        this->angle_bottom = data.angle_bottom;
        this->max_output = data.max_output;
        this->freq_set = data.freq_set;
        this->selflock_set = data.selflock_set;
        this->signal_reset = data.signal_reset;
        this->servo_direction = data.servo_direction;
        this->stalling_guard = data.stalling_guard;
        this->guard_time = data.guard_time;
        this->guard_output = data.guard_output;
        return *this;
    }

    QString current_id;
    QString new_id;
};


#endif // STRUCTDATA_H

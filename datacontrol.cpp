#include "datacontrol.h"
#include "widget.h"
#include "api/myhelper.h"
#include "ui_widget.h"

DataControl::DataControl(QWidget *widget):
    m_widget(dynamic_cast<Widget *>(widget)),
    m_ui(m_widget->uiWidget())
{

}

DataControl::~DataControl()
{

}

QByteArray DataControl::serialTestData()
{
    int servo_id = m_ui->servo_id1_edit->text().toInt();
    int pos =  m_ui->servo_lpos1_edit->text().toInt();

    m_packge.header = 0x00FA;
    m_packge.address = servo_id;
    m_packge.command = 0x02;
    m_packge.state = 0x64;
    m_packge.id_arg1 = 0x20;
    m_packge.arg1[0] = pos >> 8;
    m_packge.arg1[1] = pos & 0xff;
    m_packge.id_arg2 = 0x18;
    m_packge.arg2[0] = 0x00F4;
    m_packge.arg2[1] = 0x01;
    m_packge.checknum = m_packge.address +  m_packge.command +    m_packge.id_arg1 +  m_packge.id_arg2;
    m_packge.exitcode = 0x00AF;
    return packge_to_bytearray(m_packge);
}

QByteArray DataControl::packge_to_bytearray(const Package & packge)
{
    QByteArray byteArray;
    byteArray.append(packge.header);
    byteArray.append(packge.address);
    byteArray.append(packge.command);
    byteArray.append(packge.state);
    byteArray.append(packge.id_arg1);
    byteArray.append(packge.arg1[1]);
    byteArray.append(packge.arg1[0]);
    byteArray.append(packge.id_arg2);
    byteArray.append(packge.arg2[1]);
    byteArray.append(packge.arg2[0]);
    byteArray.append(packge.checknum);
    byteArray.append(packge.exitcode);
    return byteArray;
}

void DataControl::save_serial_config()
{
    m_serial_servo_config.angle_bottom = m_ui->angleBottomEditS->text();
    m_serial_servo_config.angle_mid = m_ui->angleMidEditS->text();
    m_serial_servo_config.angle_top = m_ui->angleTopEditS->text();
    m_serial_servo_config.current_id = m_ui->currentIdEdit->text();
    m_serial_servo_config.new_id = m_ui->newIdEdit->text();
    m_serial_servo_config.die_area = m_ui->dieAreaEditS->text();
    m_serial_servo_config.drive_freq = m_ui->driveFreqEditS->text();
    m_serial_servo_config.freq_set = m_ui->freqSetEditS->text();
    m_serial_servo_config.guard_output = m_ui->GuardOutputEditS->text();
    m_serial_servo_config.guard_time = m_ui->GuardOutputEditS->text();
    m_serial_servo_config.max_output = m_ui->maxOutputEditS->text();
    m_serial_servo_config.power_bottom = m_ui->pwBottomEditS->text();
    m_serial_servo_config.power_mid = m_ui->pwMidEditS->text();
    m_serial_servo_config.power_top = m_ui->pwTopEditS->text();
    m_serial_servo_config.start_valtage = m_ui->startVEditS->text();
    m_serial_servo_config.selflock_set = m_ui->selflockSetEditS->text();
    m_serial_servo_config.servo_direction = m_ui->servoDirEditS->text();
    m_serial_servo_config.signal_reset = m_ui->signalResetEditS->text();
    m_serial_servo_config.stalling_guard = m_ui->stallingGuardEditS->text();
}

void DataControl::save_serial_tofile()
{
    m_date_writer.write("s_angle_bottom", m_serial_servo_config.angle_bottom);
    m_date_writer.write("s_angle_mid", m_serial_servo_config.angle_mid);
    m_date_writer.write("s_angle_top", m_serial_servo_config.angle_top);
    m_date_writer.write("s_current_id", m_serial_servo_config.current_id);
    m_date_writer.write("s_new_id", m_serial_servo_config.new_id);
    m_date_writer.write("s_die_area", m_serial_servo_config.die_area);
    m_date_writer.write("s_drive_freq", m_serial_servo_config.drive_freq);
    m_date_writer.write("s_freq_set", m_serial_servo_config.freq_set);
    m_date_writer.write("s_guard_output", m_serial_servo_config.guard_output);
    m_date_writer.write("s_guard_time", m_serial_servo_config.guard_time);
    m_date_writer.write("s_max_output", m_serial_servo_config.max_output);
    m_date_writer.write("s_power_bottom", m_serial_servo_config.power_bottom);
    m_date_writer.write("s_power_mid", m_serial_servo_config.power_mid);
    m_date_writer.write("s_power_top", m_serial_servo_config.power_top);
    m_date_writer.write("s_start_valtage", m_serial_servo_config.start_valtage);
    m_date_writer.write("s_selflock_set", m_serial_servo_config.selflock_set);
    m_date_writer.write("s_servo_direction", m_serial_servo_config.servo_direction);
    m_date_writer.write("s_signal_reset", m_serial_servo_config.signal_reset);
    m_date_writer.write("s_stalling_guard", m_serial_servo_config.stalling_guard);
}

void DataControl::save_general_config()
{
    m_general_servo_config.angle_bottom = m_ui->angleBottomEdit->text();
    m_general_servo_config.angle_mid = m_ui->angleMidEdit->text();
    m_general_servo_config.angle_top = m_ui->angleTopEdit->text();
    m_general_servo_config.die_area = m_ui->dieAreaEdit->text();
    m_general_servo_config.drive_freq = m_ui->driveFreqEdit->text();
    m_general_servo_config.freq_set = m_ui->freqSetEdit->text();
    m_general_servo_config.guard_output = m_ui->GuardOutputEdit->text();
    m_general_servo_config.guard_time = m_ui->GuardOutputEdit->text();
    m_general_servo_config.max_output = m_ui->maxOutputEdit->text();
    m_general_servo_config.power_bottom = m_ui->pwBottomEdit->text();
    m_general_servo_config.power_mid = m_ui->pwMidEdit->text();
    m_general_servo_config.power_top = m_ui->pwTopEdit->text();
    m_general_servo_config.start_valtage = m_ui->startVEdit->text();
    m_general_servo_config.selflock_set = m_ui->selflockSetEdit->text();
    m_general_servo_config.servo_direction = m_ui->servoDirEdit->text();
    m_general_servo_config.signal_reset = m_ui->signalResetEdit->text();
    m_general_servo_config.stalling_guard = m_ui->stallingGuardEdit->text();
}

void DataControl::save_general_tofile()
{
    m_date_writer.write("g_angle_bottom", m_general_servo_config.angle_bottom);
    m_date_writer.write("g_angle_mid", m_general_servo_config.angle_mid);
    m_date_writer.write("g_angle_top", m_general_servo_config.angle_top);
    m_date_writer.write("g_die_area", m_general_servo_config.die_area);
    m_date_writer.write("g_drive_freq", m_general_servo_config.drive_freq);
    m_date_writer.write("g_freq_set", m_general_servo_config.freq_set);
    m_date_writer.write("g_guard_output", m_general_servo_config.guard_output);
    m_date_writer.write("g_guard_time", m_general_servo_config.guard_time);
    m_date_writer.write("g_max_output", m_general_servo_config.max_output);
    m_date_writer.write("g_power_bottom", m_general_servo_config.power_bottom);
    m_date_writer.write("g_power_mid", m_general_servo_config.power_mid);
    m_date_writer.write("g_power_top", m_general_servo_config.power_top);
    m_date_writer.write("g_start_valtage", m_general_servo_config.start_valtage);
    m_date_writer.write("g_selflock_set", m_general_servo_config.selflock_set);
    m_date_writer.write("g_servo_direction", m_general_servo_config.servo_direction);
    m_date_writer.write("g_signal_reset", m_general_servo_config.signal_reset);
    m_date_writer.write("g_stalling_guard", m_general_servo_config.stalling_guard);
}

void DataControl::read_serial_config()
{
    m_ui->angleBottomEditS->setText( m_serial_servo_config.angle_bottom);
    m_ui->angleMidEditS->setText(m_serial_servo_config.angle_mid);
    m_ui->angleTopEditS->setText(m_serial_servo_config.angle_top);
    m_ui->currentIdEdit->setText(m_serial_servo_config.current_id);
    m_ui->newIdEdit->setText(  m_serial_servo_config.new_id);
    m_ui->dieAreaEditS->setText(    m_serial_servo_config.die_area);
    m_ui->driveFreqEditS->setText(m_serial_servo_config.drive_freq);
    m_ui->freqSetEditS->setText(m_serial_servo_config.freq_set);
    m_ui->GuardOutputEditS->setText(m_serial_servo_config.guard_output);
    m_ui->GuardOutputEditS->setText(m_serial_servo_config.guard_time);
    m_ui->maxOutputEditS->setText(m_serial_servo_config.max_output);
    m_ui->pwBottomEditS->setText(m_serial_servo_config.power_bottom);
    m_ui->pwMidEditS->setText( m_serial_servo_config.power_mid);
    m_ui->pwTopEditS->setText(m_serial_servo_config.power_top);
    m_ui->startVEditS->setText(m_serial_servo_config.start_valtage);
    m_ui->selflockSetEditS->setText(m_serial_servo_config.selflock_set);
    m_ui->servoDirEditS->setText(m_serial_servo_config.servo_direction);
    m_ui->signalResetEditS->setText( m_serial_servo_config.signal_reset);
    m_ui->stallingGuardEditS->setText(m_serial_servo_config.stalling_guard);
}

void DataControl::read_serial_fromfile()
{
   m_serial_servo_config.angle_bottom =  m_data_reader.read("s_angle_bottom");
    m_serial_servo_config.angle_mid = m_data_reader.read("s_angle_mid");
    m_serial_servo_config.angle_top = m_data_reader.read("s_angle_top");
    m_serial_servo_config.current_id = m_data_reader.read("s_current_id");
    m_serial_servo_config.new_id =  m_data_reader.read ("s_new_id");
    m_serial_servo_config.die_area =  m_data_reader.read("s_die_area");
    m_serial_servo_config.drive_freq = m_data_reader.read("s_drive_freq");
    m_serial_servo_config.freq_set = m_data_reader.read("s_freq_set");
    m_serial_servo_config.guard_output = m_data_reader.read ("s_guard_output");
    m_serial_servo_config.guard_time =m_data_reader.read ("s_guard_time");
    m_serial_servo_config.max_output = m_data_reader.read("s_max_output");
    m_serial_servo_config.power_bottom = m_data_reader.read("s_power_bottom");
    m_serial_servo_config.power_mid =  m_data_reader.read ("s_power_mid");
    m_serial_servo_config.power_top =  m_data_reader.read("s_power_top");
    m_serial_servo_config.start_valtage = m_data_reader.read("s_start_valtage");
    m_serial_servo_config.selflock_set = m_data_reader.read("s_selflock_set");
    m_serial_servo_config.servo_direction =m_data_reader.read("s_servo_direction");
    m_serial_servo_config.signal_reset = m_data_reader.read("s_signal_reset");
    m_serial_servo_config.stalling_guard = m_data_reader.read("s_stalling_guard");
}

void DataControl::read_general_config()
{
    m_ui->angleBottomEdit->setText( m_general_servo_config.angle_bottom);
    m_ui->angleMidEdit->setText(m_general_servo_config.angle_mid);
    m_ui->angleTopEdit->setText(m_general_servo_config.angle_top);
    m_ui->dieAreaEdit->setText(    m_general_servo_config.die_area);
    m_ui->driveFreqEdit->setText(m_general_servo_config.drive_freq);
    m_ui->freqSetEdit->setText(m_general_servo_config.freq_set);
    m_ui->GuardOutputEdit->setText(m_general_servo_config.guard_output);
    m_ui->GuardOutputEdit->setText(m_general_servo_config.guard_time);
    m_ui->maxOutputEdit->setText(m_general_servo_config.max_output);
    m_ui->pwBottomEdit->setText(m_general_servo_config.power_bottom);
    m_ui->pwMidEdit->setText( m_general_servo_config.power_mid);
    m_ui->pwTopEdit->setText(m_general_servo_config.power_top);
    m_ui->startVEdit->setText(m_general_servo_config.start_valtage);
    m_ui->selflockSetEdit->setText(m_general_servo_config.selflock_set);
    m_ui->servoDirEdit->setText(m_general_servo_config.servo_direction);
    m_ui->signalResetEdit->setText( m_general_servo_config.signal_reset);
    m_ui->stallingGuardEdit->setText(m_general_servo_config.stalling_guard);
}

void DataControl::read_general_fromfile()
{
    m_general_servo_config.angle_bottom =  m_data_reader.read("angle_bottom");
     m_general_servo_config.angle_mid = m_data_reader.read("angle_mid");
     m_general_servo_config.angle_top = m_data_reader.read("angle_top");
     m_general_servo_config.die_area =  m_data_reader.read("die_area");
     m_general_servo_config.drive_freq = m_data_reader.read("drive_freq");
     m_general_servo_config.freq_set = m_data_reader.read("freq_set");
     m_general_servo_config.guard_output = m_data_reader.read ("guard_output");
     m_general_servo_config.guard_time =m_data_reader.read ("guard_time");
     m_general_servo_config.max_output = m_data_reader.read("max_output");
     m_general_servo_config.power_bottom = m_data_reader.read("power_bottom");
     m_general_servo_config.power_mid =  m_data_reader.read ("power_mid");
     m_general_servo_config.power_top =  m_data_reader.read("power_top");
     m_general_servo_config.start_valtage = m_data_reader.read("start_valtage");
     m_general_servo_config.selflock_set = m_data_reader.read("selflock_set");
     m_general_servo_config.servo_direction =m_data_reader.read("servo_direction");
     m_general_servo_config.signal_reset = m_data_reader.read("signal_reset");
     m_general_servo_config.stalling_guard = m_data_reader.read("stalling_guard");
}

void DataControl::servo_config()
{
    m_ui->commonIdLineEdit->setText(m_servo_config.common_id);
    m_ui->enablePowerResetLineEdit->setText(m_servo_config.enable_power_reset);
    m_ui->motorLineEdit->setText(m_servo_config.motor);
    m_ui->powerEnableLineEdit->setText(m_servo_config.power_enabel);
    m_ui->resetPositionlineEdit->setText(m_servo_config.reset_position);
    m_ui->resetStepLineEdit->setText(m_servo_config.reset_step);
    m_ui->resetTimelineEdit->setText( m_servo_config.reset_time);
    m_ui->servoIdLineEdit->setText(m_servo_config.servo_id);
    m_ui->signalTolerLineEdit->setText(m_servo_config.signal_toler);
    m_ui->stallingTimeLineEdit->setText(m_servo_config.stalling_time);
    m_ui->startTimeLineEdit->setText( m_servo_config.start_time);
    m_ui->startStepLineEdit->setText( m_servo_config.start_step);
    m_ui->GuiVersionLineEdit->setText(m_servo_config.version);
}


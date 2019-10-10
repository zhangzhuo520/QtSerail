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

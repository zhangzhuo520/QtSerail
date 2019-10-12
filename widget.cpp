#include "widget.h"
#include "ui_widget.h"
#include "datacontrol.h"
#include <QSerialPort>
#include <QDebug>
#include <QTime>
#include <QPixmap>
#include <QIcon>
#include <QFile>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    m_data_control(new DataControl(this)),
    m_serialport_state(false)
{
    ui->setupUi(this);
    initUi();
    initSerialport();
}

Widget::~Widget()
{
    delete ui;
}

Ui::Widget *Widget::uiWidget() const
{
    return ui;
}

void Widget::initSerialport()
{
    QStringList nameList;
    m_portInfolist = QSerialPortInfo::availablePorts();
    foreach (QSerialPortInfo info, m_portInfolist)
    {
        nameList.append(info.portName());
    }
    ui->portNameComboBox->clear();
    ui->portNameComboBox->addItems(nameList);
}

bool Widget::openSerialport()
{
    QString port = ui->portNameComboBox->currentText();
    if(port.isEmpty())
    {
        record("打开串口失败, 没有可选择的串口!");
        return false;
    }

    m_serialport = new QSerialPort(this);
    if(m_serialport->isOpen())
    {
        m_serialport->clear();
        m_serialport->close();
    }

    m_serialport->setPortName(port);
    if(!m_serialport->open(QIODevice::ReadWrite))
    {
        qDebug() << "打开串口失败!";
        return false;
    }

    switch (ui->baudRateComboBox->currentText().toInt()) {
    case 1200:
        m_serialport->setBaudRate(QSerialPort::Baud1200,QSerialPort::AllDirections);
        break;
    case 2400:
        m_serialport->setBaudRate(QSerialPort::Baud2400,QSerialPort::AllDirections);
        break;
    case 4800:
        m_serialport->setBaudRate(QSerialPort::Baud4800,QSerialPort::AllDirections);
        break;
    case 9600:
        m_serialport->setBaudRate(QSerialPort::Baud9600,QSerialPort::AllDirections);
        break;
    case 19200:
        m_serialport->setBaudRate(QSerialPort::Baud19200,QSerialPort::AllDirections);
        break;
    case 38400:
        m_serialport->setBaudRate(QSerialPort::Baud38400,QSerialPort::AllDirections);
        break;
    case 57600:
        m_serialport->setBaudRate(QSerialPort::Baud57600,QSerialPort::AllDirections);
        break;
    case 115200:
        m_serialport->setBaudRate(QSerialPort::Baud115200,QSerialPort::AllDirections);
        break;
    default:
        m_serialport->setBaudRate(QSerialPort::UnknownBaud,QSerialPort::AllDirections);
        break;
    }

    switch (ui->dataTypeComboBox->currentText().toInt()) {
    case 5:
        m_serialport->setDataBits(QSerialPort::Data5);
        break;
    case 6:
        m_serialport->setDataBits(QSerialPort::Data6);
        break;
    case 7:
        m_serialport->setDataBits(QSerialPort::Data7);
        break;
    case 8:
        m_serialport->setDataBits(QSerialPort::Data8);
        break;
    default:
        m_serialport->setDataBits(QSerialPort::UnknownDataBits);
        break;
    }

    m_serialport->setFlowControl(QSerialPort::NoFlowControl);//无流控制
    m_serialport->setParity(QSerialPort::NoParity);	//无校验位
    m_serialport->setStopBits(QSerialPort::OneStop); //一位停止位
    connect(m_serialport,SIGNAL(readyRead()),this,SLOT(receiveInfo()));
    record("串口已打开");
    return true;
}

void Widget::closeSerialport()
{
    if(m_serialport->isOpen())
    {
        m_serialport->clear();
        m_serialport->close();
    }
    delete m_serialport;
    m_serialport = nullptr;
    record("串口已关闭");
}

void Widget::updateSerialport()
{
    openSerialport();
}

void Widget::sendData(const QByteArray& data)
{
    if(m_serialport_state && m_serialport!=nullptr)
    {
        m_serialport->write(data.data(), data.count());

        QString string;
        for (int i = 0; i < data.count(); i ++)
        {
           string = string  +  QString::number((uchar)data.at(i),  16) + "   ";
        }
        record("发送数据： " +  string);
    }
}

void Widget::record(const QString & info)
{
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    ui->debugTextBrowser->append(time + ":   " + info);
}

void Widget::setQss(const QString &qssFile )
{
        QFile file(qssFile);
        if (file.open(QFile::ReadOnly)) {
            QString qss = QLatin1String(file.readAll());
            qApp->setStyleSheet(qss);
            file.close();
        }
}

void Widget::on_serialControlPushButton_clicked()
{
    if (!m_serialport_state)
    {
        if(openSerialport())
        {
            m_serialport_state = true;
            QIcon icon(":/pic/picture/open.png");
            QPixmap pixmap = icon.pixmap(QSize(24, 24));
            ui->SerialStateLabel->setPixmap(pixmap);
            ui->serialControlPushButton->setText("关闭");
        }
    }
    else
    {
        closeSerialport();
        m_serialport_state = false;
        QIcon icon(":/pic/picture/close.png");
        QPixmap pixmap = icon.pixmap(QSize(24, 24));
        ui->SerialStateLabel->setPixmap(pixmap);
        ui->serialControlPushButton->setText("打开");
    }
}

void Widget::receiveInfo()
{
    QString string;
    string.prepend(m_serialport->readAll());
    ui->debugTextBrowser->append(string);
}

void Widget::initUi()
{
    setWindowFlags(Qt::FramelessWindowHint);
    QIcon icon(":/pic/picture/close.png");
    QPixmap pixmap = icon.pixmap(QSize(24, 24));
    ui->SerialStateLabel->setPixmap(pixmap);
}

void Widget::on_btn_run_clicked()
{
    sendData(m_data_control->serialTestData());
}

void Widget::on_btn_stop_clicked()
{

}

void Widget::on_btn_load_configU_clicked()
{
    m_data_control->save_general_config();
    m_data_control->save_general_tofile();
}

void Widget::on_btn_read_configU_clicked()
{
    m_data_control->read_general_config();
    m_data_control->read_general_fromfile();
}
void Widget::on_btn_servo_resetU_clicked()
{

}

void Widget::on_btn_load_configS_clicked()
{
    m_data_control->save_serial_config();
    m_data_control->save_serial_tofile();
}

void Widget::on_btn_read_configS_clicked()
{
   m_data_control->read_serial_config();
   m_data_control->read_serial_config();
}

void Widget::on_btn_servo_resetS_clicked()
{

}

void Widget::on_btn_top_clicked()
{

}

void Widget::on_btn_mid_clicked()
{

}

void Widget::on_btn_bottom_clicked()
{

}

void Widget::on_posHorSlider_sliderMoved(int position)
{

}

void Widget::on_btn_feedback_clicked()
{

}

void Widget::on_openFilePushButton_clicked()
{

}

void Widget::on_SaveFilePushButton_clicked()
{

}



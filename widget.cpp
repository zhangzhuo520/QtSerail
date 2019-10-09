#include "widget.h"
#include "ui_widget.h"
#include <QSerialPort>
#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    m_serialport_state(false)
{
    ui->setupUi(this);
    initSerialport();
}

Widget::~Widget()
{
    delete ui;
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

void Widget::openSerialport()
{
    m_serialport = new QSerialPort(this);
    if(m_serialport->isOpen())
    {
        m_serialport->clear();
        m_serialport->close();
    }

    m_serialport->setPortName(ui->portNameComboBox->currentText());
    if(!m_serialport->open(QIODevice::ReadWrite))
    {
        qDebug() << "Open serialport failed!";
        return;
    }

    m_serialport->setBaudRate(QSerialPort::Baud115200,QSerialPort::AllDirections);//设置波特率和读写方向
    m_serialport->setDataBits(QSerialPort::Data8);		//数据位为8位
    m_serialport->setFlowControl(QSerialPort::NoFlowControl);//无流控制
    m_serialport->setParity(QSerialPort::NoParity);	//无校验位
    m_serialport->setStopBits(QSerialPort::OneStop); //一位停止位
    connect(m_serialport,SIGNAL(readyRead()),this,SLOT(receiveInfo()));
}

void Widget::closeSerialport()
{
    if(m_serialport->isOpen())
    {
        m_serialport->clear();
        m_serialport->close();
    }
    delete m_serialport;
}

void Widget::updateSerialport()
{
    openSerialport();
}

void Widget::writeData()
{
    if(m_serialport_state)
    {
        QString string;
        m_serialport->write(string.toLatin1().data(), sizeof(string));
    }
}

void Widget::on_serialControlPushButton_clicked()
{
    if (!m_serialport_state)
    {
        m_serialport_state = true;
        openSerialport();
        ui->serialControlPushButton->setText("关闭");
    }
    else
    {
        closeSerialport();
        m_serialport_state = false;
        ui->serialControlPushButton->setText("打开");
    }
}

void Widget::receiveInfo()
{
    QString string;
    string.prepend(m_serialport->readAll());
    ui->debugTextBrowser->append(string);

}

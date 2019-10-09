#include "widget.h"
#include "ui_widget.h"
#include <QSerialPort>
#include <QDebug>
#include <QTime>
#include <QPixmap>
#include <QIcon>
#include <QFile>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
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
}

void Widget::closeSerialport()
{
    if(m_serialport->isOpen())
    {
        m_serialport->clear();
        m_serialport->close();
    }
    delete m_serialport;
    record("串口已关闭");
}

void Widget::updateSerialport()
{
    openSerialport();
}

void Widget::writeData(QString string)
{
    if(m_serialport_state)
    {
        m_serialport->write(string.toLatin1().data(), sizeof(string));
        record("发送数据： " + string);
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
        m_serialport_state = true;
        openSerialport();
        QIcon icon(":/pic/picture/open.png");
        QPixmap pixmap = icon.pixmap(QSize(24, 24));
        ui->SerialStateLabel->setPixmap(pixmap);
        ui->serialControlPushButton->setText("关闭");
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

#include "frmmain.h"
#include "ui_frmmain.h"
#include "api/myhelper.h"
#include <QDebug>
frmMain::frmMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmMain)
{
     ui->setupUi(this);
    this->initStyle();
    myHelper::moveFormToCenter(this);
}

frmMain::~frmMain()
{
    delete ui;
}

void frmMain::initStyle()
{
    this->m_max = false;
    this->locatRect = this->geometry();
    this->setProperty("Form", true);
    this->setProperty("CanMove", true);
    this->setWindowTitle(ui->lab_title->text());

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    ui->lab_title->installEventFilter(this);

    IconHelper::getInstance()->setIcon(ui->btn_close, QChar(0xf00d));
    IconHelper::getInstance()->setIcon(ui->btn_max, QChar(0xf096));
    IconHelper::getInstance()->setIcon(ui->btn_min, QChar(0xf068));

    QIcon title_icon(":/pic/picture/serial.png");
    QPixmap pixmap = title_icon.pixmap(QSize(16, 16));
    ui->lab_ico->setPixmap(pixmap);

    connect(ui->btn_close, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btn_min, SIGNAL(clicked()), this, SLOT(showMinimized()));
}

bool frmMain::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        this->on_btn_max_clicked();
        return true;
    }
    return QObject::eventFilter(obj, event);
}

void frmMain::on_btn_max_clicked()
{
    if (m_max) {
        this->setGeometry(locatRect);
        IconHelper::getInstance()->setIcon(ui->btn_max, QChar(0xf096));
        ui->btn_max->setToolTip("最大化");
        this->setProperty("CanMove", true);
    } else {
        locatRect = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
        IconHelper::getInstance()->setIcon(ui->btn_max, QChar(0xf079));
        ui->btn_max->setToolTip("还原");
        this->setProperty("CanMove", false);
    }
    m_max = !m_max;
}



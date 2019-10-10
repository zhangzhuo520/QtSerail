#ifndef DATACONTROL_H
#define DATACONTROL_H
#include <QString>
#include <QByteArray>
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

private:
    Widget *m_widget;
    Ui::Widget*m_ui;
    Package m_packge;
};

#endif // DATACONTROL_H

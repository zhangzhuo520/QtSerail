#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QDialog>
#include<QMap>
#include <qsystemtrayicon.h>
namespace Ui
{
    class frmMain;
}

class QSystemTrayIcon;
class frmMain : public QDialog
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void on_btn_max_clicked();
    void slot_systrayIcon_active(QSystemTrayIcon::ActivationReason);
private:
    Ui::frmMain *ui;

    void initStyle();
    void initSysIcon();

    bool m_max;
    QRect locatRect;
    QSystemTrayIcon *m_systrayIcon;
};

#endif // FRMMAIN_H

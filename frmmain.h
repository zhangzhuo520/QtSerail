#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QDialog>
#include<QMap>
namespace Ui
{
    class frmMain;
}

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

private:
    Ui::frmMain *ui;

    void initStyle();

    bool m_max;
    QRect locatRect;
};

#endif // FRMMAIN_H

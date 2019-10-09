#ifndef MYHELPER_H
#define MYHELPER_H

#include <QtCore>
#include <QtGui>
#if (QT_VERSION > QT_VERSION_CHECK(5,0,0))
#include <QtWidgets>
#endif
#include "usercontrol/frmmessagebox.h"
#include "usercontrol/frminputbox.h"
#include "iconhelper.h"
#include "app.h"

class myHelper: public QObject
{

public:
    static void autoRunWithSystem(bool ifAutoRun, QString appName, QString appPath) {
        QSettings *reg = new QSettings(
            "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
            QSettings::NativeFormat);

        if (ifAutoRun) {
            reg->setValue(appName, appPath);
        } else {
            reg->setValue(appName, "");
        }
    }

    static void setStyle(const QString &qssFile) {
        QFile file(qssFile);
        if (file.open(QFile::ReadOnly)) {
            QString qss = QLatin1String(file.readAll());
            qApp->setStyleSheet(qss);
            file.close();
        }
    }

    //加载中文字符
    static void setChinese() {
        QTranslator *translator = new QTranslator(qApp);
        translator->load(":/image/qt_zh_CN.qm");
        qApp->installTranslator(translator);
    }

    static QString showInputBox(const QString info, bool &blok) {
        frmInputBox input;

        input.setMessage(info);
        blok = input.exec();

        return input.getValue();
    }

    static void showMessageBoxInfo(const QString info) {
        frmMessageBox msg;

        msg.setMessage(info, 0);
        msg.exec();
    }

    static void showMessageBoxError(const QString info) {
        frmMessageBox msg;

        msg.setMessage(info, 2);
        msg.exec();
    }

    static int showMessageBoxQuesion(const QString info) {
        frmMessageBox msg;
        msg.setMessage(info, 1);
        return msg.exec();
    }

    static void sleep(int sec) {
        QTime dieTime = QTime::currentTime().addMSecs(sec);

        while ( QTime::currentTime() < dieTime ) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
    }

    static void moveFormToCenter(QWidget *frm) {
        int frmX = frm->width();
        int frmY = frm->height();

        QDesktopWidget dwt;

        int deskWidth = dwt.availableGeometry().width();
        int deskHeight = dwt.availableGeometry().height();

        QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
        frm->move(movePoint);
    }
};

#endif // MYHELPER_H

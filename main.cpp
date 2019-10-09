#include "frmmain.h"
#include <QApplication>
#include "api/appinit.h"
#include "api/myhelper.h"
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication appc(argc, argv);

    AppInit *initApp = new AppInit;
    initApp->loadInfo();

    frmMain wmin;
    myHelper::setStyle(":/pic/picture/qss/black.css");
    wmin.show();

    return appc.exec();
}

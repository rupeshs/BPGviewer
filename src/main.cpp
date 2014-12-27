#include <QtGui/QApplication>
#include "viewerwindow.h"
#include "qtsingleapplication.h"

int main(int argc, char *argv[])
{

    QtSingleApplication instance(argc, argv);
    if(instance.isRunning())
    {
        QString cmd;
        if (qApp->arguments().count()>1)
        {
            cmd=qApp->arguments().at(1);
            instance.sendMessage(cmd);
        }

        return 0;
    }

    QApplication::setApplicationName("BPGviewer");
    ViewerWindow w;
    instance.setActivationWindow(&w,true);
    QObject::connect(&instance, SIGNAL(messageReceived(const QString&)),
                     &w, SLOT(getMessage(QString)));
    w.show();

    return qApp->exec();

}

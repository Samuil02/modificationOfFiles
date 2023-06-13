#include <QCoreApplication>
#include "datauser.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    dataUser dataUser;

    if (dataUser.enterData() == 1) {
        qDebug() << "Data is entered successfully";
    }

    if (dataUser.getMode()) {
        while (1) {
            QTimer::singleShot(dataUser.getTimer(), &dataUser, SLOT(checkInputFile()));
        }
    } else {
        QTimer::singleShot(0, &dataUser, SLOT(checkInputFile()));
    }

    return a.exec();
}

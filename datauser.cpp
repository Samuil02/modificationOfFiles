#include "datauser.h"

QTextStream cout(stdout);
QTextStream cin(stdin);

dataUser::dataUser(QObject *parent)
    : QObject{parent}, del_file{false}, timer{0}, mode_work{false}
{

}

void dataUser::setMask(QString mask) {
    this->mask = mask;
}

void dataUser::setDelFile(QString del_file)
{
    if (del_file == "Y") {
        this->del_file = true;
    }
}

void dataUser::setPath(QString path_file)
{
    this->path_file.setPath(path_file);
}

void dataUser::setUpdate(QString update_file)
{
    this->update_file = update_file;
}

void dataUser::setTimer(int timer)
{
    this->timer = timer;
}

void dataUser::setMode(QString mode_work)
{
    if (mode_work == "Y") {
        this->mode_work = true;
    }
}

void dataUser::setLow(QByteArray low_mod_file)
{
    this->low_mod_file = low_mod_file;
}

QString dataUser::getMask()
{
    return mask;
}

bool dataUser::getDelFile()
{
    return del_file;
}

QDir dataUser::getPath()
{
    return path_file;
}

QString dataUser::getUpdate()
{
    return update_file;
}

int dataUser::getTimer()
{
    return timer;
}

bool dataUser::getMode()
{
    return mode_work;
}

QByteArray dataUser::getLow()
{
    return low_mod_file;
}

int dataUser::enterData() {
    qDebug() << "Enter the mask of input files:";
    this->setMask(cin.readLine());
    qDebug() << "Delete the file after the change? [Y/n]";
    this->setDelFile(cin.readLine());
    qDebug() << "Enter the path to the input files:";
    this->setPath(cin.readLine());
    qDebug() << "Overwrite files [O] or create new ones [C]?";
    this->setUpdate(cin.readLine());
    qDebug() << "Use a timer check for the presence of input data? [Y/n]";
    this->setMode(cin.readLine());
    if (mode_work) {
        this->setTimer(cin.readLine().toInt());
    }
    qDebug() << "Enter the file modification law:";
    this->setLow(cin.readLine().toLocal8Bit());
    return 1;
}

void dataUser::checkInputFile() {
    QStringList strList = (QStringList() << mask);
    path_file.setNameFilters(strList);
    if (path_file.isEmpty()) {
        qDebug() << "The files isn't found";
    }
    else {
        modificationFile(path_file.entryList());
    }
}

int dataUser::modificationFile(QStringList fileList) {
    for (QString file_name : fileList) {
        QFile file(file_name);
        if (!file.exists()) {
            qDebug() << "The file" << file_name << "not found";
        }
        else if (!file.isOpen()) {
            qDebug() << "The file" << file_name << "is opened";
        }
        else if (update_file == "O") {
            if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
                qDebug() << "Unable to open the file" << file_name;
            }

            QByteArray mod_data = file.readAll();
            int size_low = low_mod_file.size();
            for (int i = 0; i < mod_data.size(); i++) {
                mod_data[i] = mod_data[i] ^ low_mod_file[i % size_low];
            }
            file.write(mod_data);
            file.close();
            if (del_file) {
                file.remove();
            }
        }
        else if (update_file == "C") {
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                qDebug() << "Unable to open the file" << file_name;
            }

            QByteArray mod_data = file.readAll();
            int size_low = low_mod_file.size();
            for (int i = 0; i < mod_data.size(); i++) {
                mod_data[i] = mod_data[i] ^ low_mod_file[i % size_low];
            }

            int count = 1;

            QRegExp rx(" - copy (\\d+)");
            int pos = rx.indexIn(file_name);
            if (pos > -1) {
                count = rx.cap(1).toInt() + 1;
            }

            QFile new_file( + " - copy " + count);
            new_file.write(mod_data);
            file.close();
            new_file.close();
            if (del_file) {
                file.remove();
            }
        }
        else qDebug() << "Error!";
    }
    return 1;
}

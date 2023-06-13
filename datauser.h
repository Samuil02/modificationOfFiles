#ifndef DATAUSER_H
#define DATAUSER_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QTimer>
#include <QTime>
#include <QDir>
#include <QFile>
#include <QStringList>
#include <QRegExp>

class dataUser : public QObject
{
    Q_OBJECT
public:
    explicit dataUser(QObject *parent = nullptr);

    int enterData();

    int modificationFile(QStringList fileList);

    void setMask(QString mask);
    void setDelFile(QString del_file);
    void setPath(QString path_file);
    void setUpdate(QString update_file);
    void setTimer(int timer);
    void setMode(QString mode_work);
    void setLow(QByteArray low_mod_file);

    QString getMask();
    bool getDelFile();
    QDir getPath();
    QString getUpdate();
    int getTimer();
    bool getMode();
    QByteArray getLow();

signals:

private slots:
    void checkInputFile();

private:
    QString mask;
    bool del_file;
    QDir path_file;
    QString update_file;
    int timer;
    bool mode_work;
    QByteArray low_mod_file;
    QTimer *tmr;
};

#endif // DATAUSER_H

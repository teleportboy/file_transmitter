#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QSettings>

class Settings {

public:
    Settings(QString filepath);
    int getPort();
    int getThreadsCount();
    int getPacketSize();
    QString getAddress();
    QString getFilePath();
    QString getWorkMode();

private:
    QSettings settings;
};

#endif // SETTINGS_H

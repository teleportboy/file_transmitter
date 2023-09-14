#include "Settings.h"
#include <QFile>

#include "constants.h"

Settings::Settings(QString filePath) : settings(filePath, QSettings::IniFormat) {
    QFile configFile(filePath);
    if (!configFile.exists()) {
        settings.setValue("Network/port", DEFAULT_PORT);
        settings.setValue("Application/threads", DEFAULT_THREADS_COUNT);
        settings.setValue("Application/packetSize", DEFAULT_PACKET_SIZE);
        settings.setValue("Application/filePath", DEFAULT_FILE_PATH);
        settings.setValue("Network/address", DEFAULT_DESTINATION_ADDRESS);
        settings.setValue("Application/workMode", DEFAULT_WORK_MODE);
        settings.sync();
    }
}

int Settings::getPort() {
    return settings.value("Network/port", DEFAULT_PORT).toInt();
}

QString Settings::getAddress() {
    return settings.value("Network/address", DEFAULT_DESTINATION_ADDRESS).toString();
}

int Settings::getThreadsCount() {
    return settings.value("Application/threads", DEFAULT_THREADS_COUNT).toInt();
}

int Settings::getPacketSize() {
    return settings.value("Application/packetSize", DEFAULT_PACKET_SIZE).toInt();
}

QString Settings::getFilePath() {
    return settings.value("Application/filePath", DEFAULT_FILE_PATH).toString();
}

QString Settings::getWorkMode() {
    return settings.value("Application/workMode", DEFAULT_WORK_MODE).toString();
}

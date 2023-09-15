#include <QTime>
#include <QFile>

#include <QDebug>

#include "FileBuilder.h"
#include "types.h"

//что то надо было спросить про инициализацию QObject.. todo
FileBuilder::FileBuilder(QObject *parent)
    : QObject{parent}
{

}

void FileBuilder::addPacket(PacketData packet) {
    filePackets.insert(packet.packetId, packet.data);

    if (filePackets.size() == packet.packetsCount) {
        buildFile(packet.fileName);
    }
}

QString FileBuilder::generateFilePath(QString fileName) {
    qsrand(QTime::currentTime().msec());
    int randomNumber = qrand();
    QString numberAsText = "_" + QString::number(randomNumber, 16).toUpper();
    int dotIndex = fileName.lastIndexOf('.');
    fileName.insert(dotIndex, numberAsText);

    return fileName;
}


void FileBuilder::buildFile(QString fileName) {
    QMap<int, QByteArray>::iterator it;

    QString filePath = generateFilePath(fileName);

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        emit closeApp();
        return;
    }

    for (it = filePackets.begin(); it != filePackets.end(); it++) {
        file.write(it.value());
    }

    emit closeApp();
}


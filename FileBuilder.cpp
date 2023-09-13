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
        buildFile(packet.fileExtension);
    }
}


void FileBuilder::buildFile(QString fileExtension) {
    QMap<int, QByteArray>::iterator it;

    qsrand(QTime::currentTime().msec());
    int randomNumber = qrand();

    QString numberAsText = QString::number(randomNumber, 16).toUpper();

    QString filePath = "file" + numberAsText + "." + fileExtension;
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        return;
    }

    for (it = filePackets.begin(); it != filePackets.end(); it++) {
        file.write(it.value());
    }
}

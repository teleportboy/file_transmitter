#include <QFile>
#include <QByteArray>

#include "PacketsContainer.h"
#include "Packet.h"
#include "qfileinfo.h"

PacketsContainer::PacketsContainer(QString filePath, QString address, int packetSize, QObject* parent)
    : QObject(parent), filePath(filePath), address(address), packetSize(packetSize)
{
}

QVector<Packet*>* PacketsContainer::makePacketsFromFile() {
    packetsInVector = new QVector<Packet*>;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return nullptr;
    }

    QFileInfo fileInfo(file);
    const int fileSize = fileInfo.size();

    int totalPackets = fileSize / 1024;
    totalPackets += fileSize % 1024 > 0 ? 1 : 0;

    QString fileExtension = fileInfo.suffix();

    for (int i = 0; !file.atEnd(); i++) {
        QByteArray buffer = file.read(packetSize);
        Packet* packet = new Packet(buffer, address, i);
        packet->totalPackets(totalPackets);
        packet->fileExtension(fileExtension);
        packetsInVector->push_back(packet);
    }

    file.close();

    return packetsInVector;
}

void PacketsContainer::stopResendingPacket(int packetId) {
    packetsInVector->at(packetId)->packetSent();
}

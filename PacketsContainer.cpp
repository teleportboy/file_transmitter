#include <QFile>
#include <QByteArray>
#include <QCoreApplication>

#include "PacketsContainer.h"
#include "Packet.h"
#include "qfileinfo.h"
#include "Settings.h"

PacketsContainer::PacketsContainer(QObject* parent)
    : QObject(parent)
{

}

QMap<int, Packet*> PacketsContainer::makePacketsFromFile(Settings& settings) {
    QFile file(settings.getFilePath());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return packetsInMap;
    }

    QFileInfo fileInfo(file);
    const int fileSize = fileInfo.size();

    int totalPackets = fileSize / settings.getPacketSize();
    totalPackets += fileSize % settings.getPacketSize() > 0 ? 1 : 0;

    QString fileExtension = fileInfo.suffix();

    for (int i = 0; !file.atEnd(); i++) {
        QByteArray buffer = file.read(settings.getPacketSize());
        Packet* packet = new Packet(buffer, settings.getAddress(), i, settings.getPort());
        packet->totalPackets(totalPackets);
        packet->fileExtension(fileExtension);
        packetsInMap[i] = packet;
    }

    file.close();

    return packetsInMap;
}

void PacketsContainer::stopResendingPacket(int packetId) {
    if (packetsInMap.contains(packetId)) {
        packetsInMap[packetId]->packetSent();
        packetsInMap.remove(packetId);
    }

    if (packetsInMap.isEmpty()) {
        emit closeApp();
    }
}

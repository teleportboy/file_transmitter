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

    int fileSize = fileInfo.size();
    int totalPackets = (fileSize / settings.getPacketSize()) + (fileSize % settings.getPacketSize() > 0 ? 1 : 0);

    QString fileName = fileInfo.fileName();

    for (int i = 0; !file.atEnd(); i++) {
        QByteArray buffer = file.read(settings.getPacketSize());

        PacketBuilder packetBuilder;
        Packet* packet = packetBuilder
                         .setData(buffer)
                         .setAddress(settings.getAddress())
                         .setPacketId(i)
                         .setPort(settings.getPort())
                         .setMsDelayResent(250)
                         .setTotalPackets(totalPackets)
                         .setFileName(fileName)
                         .setPaketType()
                         .buildPacket();

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

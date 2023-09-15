#include "PacketsSender.h"

PacketsSender::PacketsSender(int threadsCount, QObject *parent)
    : QObject(parent), threadsCount(threadsCount)
{
    if (threadsCount < 1) {
        threadsCount = 1;
    }

    threads = QVector<QThread*>(threadsCount);
    for (int i = 0; i < threadsCount; i++) {
        threads[i] = new QThread(this);
        parallelizePackets.append(QVector<Packet*>());
    }
}

void PacketsSender::parallelizeSendingPackets(QMap<int, Packet*> packets) {
    for (int i = 0, currentThreadIndex = 0; i < packets.count(); i++) {
        parallelizePackets[currentThreadIndex].append(packets[i]);

        if (++currentThreadIndex == threadsCount) {
            currentThreadIndex = 0;
        }
    }
}

void PacketsSender::joinPacketsToThreads() {
    for (int i = 0; i < threadsCount; i++) {
        for (int j = 0; j < parallelizePackets[i].length(); j++) {
            parallelizePackets[i][j]->moveToThread(threads[i]);
        }
    }
}

void PacketsSender::connectPacketsWithThreads() {
    for (int i = 0; i < threadsCount; i++) {
        for (int j = 0; j < parallelizePackets[i].length(); j++) {
            connect(threads[i], &QThread::started, parallelizePackets[i][j], &Packet::startPacketSending);
        }
    }
}

void PacketsSender::start(QMap<int, Packet*> packets) {
    parallelizeSendingPackets(packets);
    joinPacketsToThreads();
    connectPacketsWithThreads();

    for (int i = 0; i < threadsCount; i++) {
        threads[i]->start();
    }
}

void PacketsSender::stop() {
    for (int i = 0; i < threadsCount; i++) {
        threads[i]->exit();
    }
}

void PacketsSender::sendApprovalPacket(QString address, quint16 port, PacketData packetData) {
    PacketBuilder packetBuilder;
    Packet* packet = packetBuilder
                    .setAddress(address)
                    .setPacketId(packetData.packetId)
                    .setPort(port)
                    .setTotalPackets(packetData.packetsCount)
                    .setFileName(packetData.fileName)
                    .setPaketType(PacketType::ApproveFilePacket)
                    .buildPacket();

    packet->trySendPacket();
}

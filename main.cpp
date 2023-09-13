#include <QCoreApplication>
#include <QThread>
#include <QVector>
#include <iostream>
#include "PacketsContainer.h"
#include "PacketsSender.h"
#include "PacketReceiver.h"
#include "FileBuilder.h"

#include <QTextStream>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    PacketsContainer packets("./CMakeCache.txt", "127.0.0.1");
    PacketsSender sender(2);    
    FileBuilder fileBuilder;
    PacketReceiver receiver;

    QObject::connect(&receiver, &PacketReceiver::packetReceived, &packets, &PacketsContainer::stopResendingPacket);
    QObject::connect(&receiver, &PacketReceiver::addPacketToFile, &fileBuilder, &FileBuilder::addPacket);
    QObject::connect(&receiver, &PacketReceiver::approvePacket, &sender, &PacketsSender::sendApprovalPacket);

    sender.start(packets.makePacketsFromFile());
    receiver.startReceive();

    a.exec();

    return 0;
}

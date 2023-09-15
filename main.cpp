#include <QCoreApplication>
#include <QThread>
#include <QVector>
#include <iostream>
#include "PacketsContainer.h"
#include "PacketsSender.h"
#include "PacketReceiver.h"
#include "FileBuilder.h"
#include "Settings.h"
#include "constants.h"

#include <QTextStream>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    Settings settings("config.ini");

    PacketsContainer packets;
    PacketsSender sender(settings.getThreadsCount());
    FileBuilder fileBuilder;
    PacketReceiver receiver(settings.getPort());

    QObject::connect(&receiver, &PacketReceiver::packetReceived, &packets, &PacketsContainer::stopResendingPacket);
    QObject::connect(&receiver, &PacketReceiver::addPacketToFile, &fileBuilder, &FileBuilder::addPacket);
    QObject::connect(&receiver, &PacketReceiver::approvePacket, &sender, &PacketsSender::sendApprovalPacket);

    QObject::connect(&packets, &PacketsContainer::closeApp, &sender, &PacketsSender::stop);
    QObject::connect(&fileBuilder, &FileBuilder::closeApp, &app, &QCoreApplication::quit);
    QObject::connect(&packets, &PacketsContainer::closeApp, &app, &QCoreApplication::quit);

    if (settings.getWorkMode() == WORK_MODE_SENDER) {
        sender.start(packets.makePacketsFromFile(settings));
    }
    receiver.startReceive();


    app.exec();

    //sender.stop(); ??

    return 0;
}

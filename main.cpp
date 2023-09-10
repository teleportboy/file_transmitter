#include <QCoreApplication>
#include <QThread>
#include <QVector>
#include <iostream>
#include "PacketsContainer.h"
#include "PacketsSender.h"
#include "PacketReceiver.h"

#include <QTextStream>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QTextStream input(stdin);
    qDebug() << "Режим работы: s - sender, r - receiver";

    PacketsContainer packets("./CMakeCache.txt", "127.0.0.1");
    PacketsSender sender(2);

    PacketReceiver receiver;

    QString mode = input.readLine();
    if (mode == "s") {
        qDebug() << "sender";
        sender.start(packets.makePacketsFromFile());
    } else {
        qDebug() << "receiver";
        receiver.startReceive();
    }

    return a.exec();
    input.readLine();
}

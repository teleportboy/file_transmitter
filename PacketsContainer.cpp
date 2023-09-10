#include <QFile>
#include <QByteArray>

#include "PacketsContainer.h"
#include "Packet.h"

PacketsContainer::PacketsContainer(QString filePath, QString address, int packetSize, QObject* parent)
    : QObject(parent), filePath(filePath), address(address), packetSize(packetSize)
{ }

QVector<Packet*>* PacketsContainer::makePacketsFromFile() {
    packetsInVector = new QVector<Packet*>;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return nullptr;
    }

    quint64 packetsCount = 0;
    for (packetsCount = 0; !file.atEnd(); packetsCount++) {
        QByteArray buffer = file.read(packetSize);
        packetsInVector->push_back(new Packet(buffer, address, packetsCount));
    }

    return packetsInVector;
}

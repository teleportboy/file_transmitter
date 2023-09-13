#ifndef TYPES_H
#define TYPES_H

#include <QByteArray>
#include <QString>

enum PacketType {
    SendFilePacket,
    ApproveFilePacket
};

typedef struct PacketData {
    int packetId;
    int packetType;
    int packetsCount;
    QString fileExtension;
    QByteArray data;
} PacketData;

#endif // TYPES_H

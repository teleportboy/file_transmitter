#ifndef TYPES_H
#define TYPES_H

#include <QByteArray>

typedef struct PacketData {
    int packetId;
    QByteArray data;
} PacketData;

#endif // TYPES_H

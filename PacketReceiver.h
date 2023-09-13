#ifndef PACKETRECEIVER_H
#define PACKETRECEIVER_H

#include <QUdpSocket>
#include <QObject>
#include <QMap>

#include "types.h"

class PacketReceiver : public QObject {
    Q_OBJECT
public:
    PacketReceiver(QObject *parent = nullptr);
    void startReceive();

private:
    QUdpSocket socket;
    QMap<int, QByteArray> packets;

signals:
    void packetReceived(int packetId);
    void addPacketToFile(PacketData packet);
    void approvePacket(QString address, int port, PacketData packetData);
};

#endif // PACKETRECEIVER_H

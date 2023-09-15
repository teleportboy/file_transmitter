#ifndef PACKET_H
#define PACKET_H

#include <QObject>
#include <QByteArray>
#include <QDataStream>
#include <QUdpSocket>
#include <QHostAddress>
#include <QTimer>

#include "types.h"

class Packet : public QObject {
    Q_OBJECT
public:
    Packet(QObject* parent = nullptr);
    ~Packet();

    void packetSent();

public slots:
    void trySendPacket();
    void startPacketSending();

protected:
    void stopPacketSending();

private:
    PacketData packet;

    bool isSent;

    QHostAddress* address;
    quint16 port;

    QTimer* timer;
    int msDelayResent;

    friend class PacketBuilder;
};

class PacketBuilder {
public:
    PacketBuilder(QObject* parent = nullptr);

    PacketBuilder& setData(QByteArray data);
    PacketBuilder& setAddress(QString address);
    PacketBuilder& setPort(quint16 port);
    PacketBuilder& setPacketId(int id);
    PacketBuilder& setPaketType(PacketType type = PacketType::SendFilePacket);
    PacketBuilder& setMsDelayResent(int msDelay);
    PacketBuilder& setTotalPackets(int totalPackets);
    PacketBuilder& setFileName(QString fileName);

    Packet* buildPacket();

private:
    Packet* packet;

};

#endif // PACKET_H

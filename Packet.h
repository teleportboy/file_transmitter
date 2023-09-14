#ifndef PACKET_H
#define PACKET_H

#include <QObject>
#include <QByteArray>
#include <QDataStream>
#include <QUdpSocket>
#include <QHostAddress>
#include <QTimer>

#include "types.h"


//чёт сложно стало создавать этот объект. надо упростить его создание
class Packet : public QObject {
    Q_OBJECT
public:
    Packet(QByteArray data, QString address, int id = 0, quint16 port = 2417,
           PacketType type = PacketType::SendFilePacket, int msDelayResent = 500, QObject* parent = nullptr);
    Packet(PacketData data, QString ipv4, quint16 port, QObject* parent = nullptr);
    ~Packet();

    void packetSent();

    //refactor nado
    void totalPackets(int packetsCount);
    void fileExtension(QString extension);

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
};

#endif // PACKET_H

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
    Packet(QByteArray data, QString address, int id = 0, quint16 port = 2417,
           int msDelayResent = 500, QObject* parent = nullptr);
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
};

#endif // PACKET_H

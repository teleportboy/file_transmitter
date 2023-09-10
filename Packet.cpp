#include "Packet.h"
#include <QDebug>

Packet::Packet(QByteArray data, QString ipv4, int id,
               quint16 port, int msDelayResent, QObject* parent)
    : port(port), QObject(parent), msDelayResent(msDelayResent)
{
    packet.packetId = id;
    packet.data = data;

    isSent = false;

    address = new QHostAddress(ipv4);
    timer = new QTimer(this);
}

void Packet::trySendPacket() {
    QUdpSocket socket;

    if (!isSent) {
        QByteArray dataToSend;
        QDataStream stream(&dataToSend, QIODevice::WriteOnly);
        stream << packet.packetId;
        stream << packet.data;

        socket.writeDatagram(dataToSend, *address, port);
        return;
    }

    stopPacketSending();
}

void Packet::packetSent() {
    isSent = true;
}

void Packet::stopPacketSending() {
    timer->stop();
    disconnect(timer, nullptr, nullptr, nullptr);
    deleteLater();
}

void Packet::startPacketSending() {
    connect(timer, &QTimer::timeout, this, &Packet::trySendPacket);
    timer->start(msDelayResent);
}

Packet::~Packet() {
    delete timer;
    delete address;
}

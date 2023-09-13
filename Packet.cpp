#include "Packet.h"
#include <QDebug>

Packet::Packet(QByteArray data, QString ipv4, int id, PacketType type,
               quint16 port, int msDelayResent, QObject* parent)
    : port(port), QObject(parent), msDelayResent(msDelayResent)
{
    packet.packetId = id;
    packet.data = data;
    packet.packetType = type;

    isSent = false;

    address = new QHostAddress(ipv4);
    timer = new QTimer(this);
}

Packet::Packet(PacketData data, QString ipv4, quint16 port, QObject* parent)
    : port(port), QObject(parent)
{
    packet = data;

    isSent = false;

    address = new QHostAddress(ipv4);
    timer = new QTimer(this);
}

void Packet::trySendPacket() {
    QUdpSocket socket;

    if (!isSent) {
        QByteArray dataToSend;
        QDataStream stream(&dataToSend, QIODevice::WriteOnly);
        //что то более общее надо
        stream << packet.packetId;
        stream << packet.packetType;
        stream << packet.packetsCount;
        stream << packet.fileExtension;
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
    //deleteLater();
}

void Packet::startPacketSending() {
    connect(timer, &QTimer::timeout, this, &Packet::trySendPacket);
    timer->start(msDelayResent);
}

void Packet::totalPackets(int packetsCount) {
    packet.packetsCount = packetsCount;
}

void Packet::fileExtension(QString fileExtension) {
    packet.fileExtension = fileExtension;
}

Packet::~Packet() {
    delete timer;
    delete address;
}

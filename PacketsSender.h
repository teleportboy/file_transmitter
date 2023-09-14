#ifndef PACKETSSENDER_H
#define PACKETSSENDER_H

#include <QObject>
#include <QVector>
#include <QThread>

#include "Packet.h"

class PacketsSender : public QObject {
    Q_OBJECT
public:
    PacketsSender(int threadsCount = 10, QObject *parent = nullptr);
    void start(QMap<int, Packet*> packets);


public slots:
    void sendApprovalPacket(QString address, quint16 port, PacketData packetData);
    void stop();

protected:
    void parallelizeSendingPackets(QMap<int, Packet*> packets);
    void joinPacketsToThreads();
    void connectPacketsWithThreads();

private:
    int threadsCount;
    QVector<QThread*> threads;
    QVector<QVector<Packet*>> parallelizePackets;
};

#endif // PACKETSSENDER_H

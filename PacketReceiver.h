#ifndef PACKETRECEIVER_H
#define PACKETRECEIVER_H

#include <QUdpSocket>
#include <QObject>
#include <QMap>

class PacketReceiver : public QObject {
    Q_OBJECT
public:
    PacketReceiver(QObject *parent = nullptr);
    void startReceive();

private:
    QUdpSocket socket;
    QMap<int, QByteArray> packets;


signals:

};

#endif // PACKETRECEIVER_H

#ifndef PacketsContainer_H
#define PacketsContainer_H

#include <QObject>
#include <QString>

#include "Packet.h"

class PacketsContainer : public QObject {
    Q_OBJECT
public:
    PacketsContainer(QString filePath, QString address, int packetSize = 1024, QObject* parent = nullptr);
    QVector<Packet*>* makePacketsFromFile();

private:
    QString filePath;
    QString address;
    int packetSize;

    QVector<Packet*>* packetsInVector;

public slots:
    void stopResendingPacket(int packetId);

};

#endif // PacketsContainer_H

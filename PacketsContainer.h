#ifndef PacketsContainer_H
#define PacketsContainer_H

#include <QObject>
#include <QString>
#include <QMap>

#include "Packet.h"
#include "Settings.h"

class PacketsContainer : public QObject {
    Q_OBJECT
public:
    PacketsContainer(QObject* parent = nullptr);
    QMap<int, Packet*> makePacketsFromFile(Settings& settings);

private:
    QString filePath;
    QString address;

    QMap<int, Packet*> packetsInMap;

public slots:
    void stopResendingPacket(int packetId);

signals:
    void closeApp();
};

#endif // PacketsContainer_H

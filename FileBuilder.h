#ifndef FILEBUILDER_H
#define FILEBUILDER_H

#include <QObject>
#include <QMap>
#include <QByteArray>

#include "types.h"

class FileBuilder : public QObject {
    Q_OBJECT
public:
    FileBuilder(QObject *parent = nullptr);
    void buildFile(QString fileName);

private:
    QMap<int, QByteArray> filePackets;

    QString generateFilePath(QString fileName);

public slots:
    void addPacket(PacketData packet);

signals:
    void closeApp();
};

#endif // FILEBUILDER_H

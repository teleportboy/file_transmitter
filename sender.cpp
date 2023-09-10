#include <QDateTime>
#include "QtNetwork/qhostaddress.h"
#include "QtNetwork/qudpsocket.h"
#include "sender.h"
#include <QDebug>
//#include <QUdpSocket>

Sender::Sender(QObject *parent) : QObject(parent) {}

void Sender::sendData() {
    QUdpSocket socket;

    QHostAddress address("192.168.0.175");
    quint16 port = 2417;

    while (true) {
        QByteArray data = QByteArray::fromStdString("suchara))");

        socket.writeDatagram(data, address, port);

        qDebug() << data;

        QThread::sleep(1);
    }
}

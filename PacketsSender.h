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
    void start(QVector<Packet*>* packets);

protected:
    void parallelizeSendingPackets(QVector<Packet*>* packets);
    void joinPacketsToThreads();
    void connectPacketsWithThreads();

private:
    int threadsCount;
    QVector<QThread*> threads;
    QVector<QVector<Packet*>> parallelizePackets;

signals:

};

#endif // PACKETSSENDER_H

/*  Надо два класса - два режима в которых может работать приложение.
    Первый работает в режиме получить файл по UDP  а второй отправить файл по UDP
    По скольку это UDP то отправлять пакеты придётся в обоих случаях.
    Поэтому во первых я хочу такую систему в которой каждому режиму работы
    описываются пакеты которые он может получать и которые он не может получать./
    На каждый тип пакета у него должно быть своё действие.
    Например есть тип пакета "установить соединение" - когда он приходит мы это понимаем
    и достаём/билдим нужный тип пакета и отправляем в ответ.

    Доп инфа: Приложение работает как p2p.
*/

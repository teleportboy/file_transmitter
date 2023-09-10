#ifndef SENDER_H
#define SENDER_H

#include <QObject>
#include <QThread>

class Sender : public QObject
{
    Q_OBJECT
public:
    explicit Sender(QObject *parent = nullptr);

public slots:
    void sendData();
};

#endif // SENDER_H

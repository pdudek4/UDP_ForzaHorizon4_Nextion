#ifndef MYUDP_H
#define MYUDP_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QString>


class MyUDP : public QObject
{
    Q_OBJECT
public:
    explicit MyUDP(QObject *parent = 0);
    ~MyUDP();

    QUdpSocket *udpSocketGet;

    void HelloUDP();
    void SendUDP(QByteArray Data);
    void GetRPM();
    void show();
    float ret_rpm();
    float ret_speed();
signals:

public slots:
void readyRead();

private:
    QUdpSocket *udpSocketSend;

    QHostAddress *telefon;
    QHostAddress *komputer;
    quint16 receiverPort;
    QByteArray rcv_buffer;

    float rpm;
    float speed;


};

#endif // MYUDP_H

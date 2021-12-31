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

    QString GetMyIP();
    void HelloUDP();
    void SendUDP(QByteArray Data);
    void GetRPM();
    void show();
    float ret_rpm();
    float ret_speed();
    float ret_yaw();
    uint8_t ret_gear();
signals:

public slots:
void readyRead();

private:
    QUdpSocket *udpSocketSend;

    QHostAddress *telefon;
    QHostAddress *komputer;
    QHostAddress *xbox;
    quint16 receiverPort;
    QByteArray rcv_buffer;

    float rpm;
    float rpmMax;
    float speed;
    float yaw;
    uint8_t gear;


};

#endif // MYUDP_H

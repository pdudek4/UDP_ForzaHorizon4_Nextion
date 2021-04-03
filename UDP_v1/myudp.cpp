#include "myudp.h"
#include "QDebug"

MyUDP::MyUDP(QObject *parent) :
    QObject(parent)
{
    // create a QUDP socket
    udpSocketSend = new QUdpSocket(this);
    udpSocketGet   = new QUdpSocket(this);
    telefon = new QHostAddress("192.168.0.101");
    komputer = new QHostAddress("192.168.0.103");
    //komputer = new QHostAddress("192.168.1.77");

    //port odczytany z drugiego urządzenia nadawczego, np PacketSender from port
    //na ten port wysylane beda wiadomosci
    receiverPort = 50124;

    // The most common way to use QUdpSocket class is
    // to bind to an address and port using bind()
    // bool QAbstractSocket::bind(const QHostAddress & address,
    //     quint16 port = 0, BindMode mode = DefaultForPlatform)

    //tutaj adres ip i port na ktory wysylamy wiadomosci
        //port dowolny inny niz przy Get->bind
    udpSocketSend->bind(*komputer, 55555);

    //tutaj adres ip i port skad odbieramy pakiety
        //te wartosci musimy wpisac do urzadzenia nadawczego
    udpSocketGet->bind(*komputer, 44444);
    connect(udpSocketGet  , SIGNAL(readyRead()), this, SLOT(readyRead()));
}

MyUDP::~MyUDP()
{
    delete udpSocketSend;
    delete udpSocketGet;
    delete telefon;
    delete komputer;
}

void MyUDP::HelloUDP()
{
    QByteArray Data;
    Data.append("Hello from UDP");

    // Sends the datagram datagram
    // to the host address and at port.
    // qint64 QUdpSocket::writeDatagram(const QByteArray & datagram,
    //                      const QHostAddress & host, quint16 port)
    udpSocketSend->writeDatagram(Data, *telefon, 55555);
}

void MyUDP::readyRead()
{
    // when data comes in
    rcv_buffer.resize(udpSocketGet->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    // qint64 QUdpSocket::readDatagram(char * data, qint64 maxSize,
    //                 QHostAddress * address = 0, quint16 * port = 0)
    // Receives a datagram no larger than maxSize bytes and stores it in data.
    // The sender's host address and port is stored in *address and *port
    // (unless the pointers are 0).

    udpSocketGet->readDatagram(rcv_buffer.data(), rcv_buffer.size(), &sender, &senderPort);

    //qDebug() << "Message from: " << sender.toString();
    //qDebug() << "Message port: " << senderPort;
    //qDebug() << "Message: " << rcv_buffer; //do sprawdzenia
    GetRPM();
    //show();

}

void MyUDP::SendUDP(QByteArray Data){

    //udpSocketSend->writeDatagram(Data, *telefon, 55555);
 udpSocketSend->writeDatagram(Data, *komputer, receiverPort);
}

void MyUDP::GetRPM()
{
    float sp;
    QByteArray ba_rpm;
    QByteArray ba_speed;
    ba_rpm.resize(4);
    ba_speed.resize(4);

    //***********RPM************
    memcpy(ba_rpm.data(), rcv_buffer.constData() + 16, 4);
    uchar r0 = ba_rpm[0];
    uchar r1 = ba_rpm[1];
    uchar r2 = ba_rpm[2];
    uchar r3 = ba_rpm[3];
    uchar b[4] = {r0, r1, r2, r3};
    memcpy(&rpm, &b, sizeof(rpm));

    //*********SPEED*************
    memcpy(ba_speed.data(), rcv_buffer.constData() + 40, 4);
    r0 = ba_speed[0];
    r1 = ba_speed[1];
    r2 = ba_speed[2];
    r3 = ba_speed[3];
    uchar b1[4] = {r0, r1, r2, r3};
    memcpy(&sp, &b1, sizeof(sp));
    speed = sp * 3.6;

    //show();
}

void MyUDP::show()
{
    qDebug() << rpm << speed;
}

float MyUDP::ret_rpm()
{
    return rpm;
}

float MyUDP::ret_speed()
{
    return speed;
}

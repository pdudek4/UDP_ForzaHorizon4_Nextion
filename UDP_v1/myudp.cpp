#include "myudp.h"
#include "QDebug"

#include "QHostInfo"
#include "QNetworkInterface"

MyUDP::MyUDP(QObject *parent) :
    QObject(parent)
{
    // create a QUDP socket
    udpSocketSend = new QUdpSocket(this);
    udpSocketGet   = new QUdpSocket(this);

//    telefon = new QHostAddress("192.168.0.101");
//    xbox = new QHostAddress("192.168.0.105");
    komputer = new QHostAddress(GetMyIP());         //get own IP from function

    //port odczytany z drugiego urządzenia nadawczego, np PacketSender->from port
    //na ten port wysylane beda wiadomosci
    receiverPort = 51874;

    // The most common way to use QUdpSocket class is
    // to bind to an address and port using bind()
    // bool QAbstractSocket::bind(const QHostAddress & address,
    //     quint16 port = 0, BindMode mode = DefaultForPlatform)

    //tutaj adres ip i port na ktory wysylamy wiadomosci
        //port dowolny inny niz przy Get->bind
//    udpSocketSend->bind(*xbox, 55555);

    //tutaj adres ip i port skad odbieramy pakiety, czyli adres komputera
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

QString MyUDP::GetMyIP()
{
    QString localhostname =  QHostInfo::localHostName();
    QString localhostIP;
    QList<QHostAddress> hostList = QHostInfo::fromName(localhostname).addresses();
    foreach (const QHostAddress& address, hostList) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address.isLoopback() == false) {
             localhostIP = address.toString();
        }
    }

//    QString localMacAddress;
//    QString localNetmask;
//    foreach (const QNetworkInterface& networkInterface, QNetworkInterface::allInterfaces()) {
//        foreach (const QNetworkAddressEntry& entry, networkInterface.addressEntries()) {
//            if (entry.ip().toString() == localhostIP) {
//                localMacAddress = networkInterface.hardwareAddress();
//                localNetmask = entry.netmask().toString();
//                break;
//            }
//        }
//    }
    qDebug() << "Localhost name: " << localhostname;
    qDebug() << "IP = " << localhostIP;
//    qDebug() << "MAC = " << localMacAddress;
//    qDebug() << "Netmask = " << localNetmask;

    return localhostIP;
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

//    qDebug() << "Message from: " << sender.toString();
//    qDebug() << "Message port: " << senderPort;
//    qDebug() << "Rozmiar: " << rcv_buffer.length();
//    qDebug() << "Message: " << rcv_buffer; //do sprawdzenia
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
    bool isNaN;

    //*********RPM MAX**********
    memcpy(&rpmMax, rcv_buffer.constData() + 8, 4);
    rpmMax -= 500;
    if(rpmMax < 0) rpmMax=0;

    //***********RPM************
    memcpy(&rpm, rcv_buffer.constData() + 16, 4);

    //*********SPEED*************
    memcpy(&sp, rcv_buffer.constData() + 40, 4);
    speed = sp * 3.6;
    if(speed<0) speed = -speed;

    //***********YAW************
    memcpy(&yaw, rcv_buffer.constData() + 32, 4);
    if(yaw >= 0){
        yaw = 1 + (yaw/18);
        if(yaw>2) yaw =2;
    }
    else{
        yaw = 1 - (-yaw/18);
        if(yaw<0) yaw =0;
    }

    //***********GEAR************
    memcpy(&gear, rcv_buffer.constData() + 319, 1);
    switch(gear){
        case 0:
         gear=7;
         break;
        case 5:
         gear=9;
         break;
        case 6:
         gear=10;
         break;
        case 7:
         gear=5;
         break;
        case 8:
         gear=5;
         break;
        case 9:
         gear=5;
         break;
    }

    //assert for e46 speedo
    rpm = (rpm/rpmMax) * 7200;
    isNaN = qIsNaN(rpm);
    if(isNaN) rpm = 0;
    if(speed > 255) speed = 255;

    //test new parameters

// 216 Car Class; //Between 0 (D -- worst cars) and 7 (X class -- best cars)
// 220 CarPerformance Index np 800
// 224 Drivetrain Type; 0 = FWD, 1 = RWD, 2 = AWD
// 268 272 276 280 tire temps
// 296 f32 BestLap;
// 300 f32 LastLap;
// 304 f32 CurrentLap;
// 308 f32 CurrentRaceTime;
// 312 u16 LapNumber; from 0
// 314 u8 RacePosition;
// 315 u8 Accel;
// 316 u8 Brake;
// 317 u8 Clutch;
// 318 u8 HandBrake;
// 319 u8 Gear;
// 320 s8 Steer;
//    float x,y,z,q;
//    uint16_t r;
//    uint8_t p[4];
//    memcpy(&p[0], rcv_buffer.constData() + 319, 1);
//    qDebug() << p[0];
//    memcpy(&p[1], rcv_buffer.constData() + 320, 1);
//    qDebug() << p[1];
//    memcpy(&p[2], rcv_buffer.constData() + 317, 1);
//    qDebug() << p[2];
//    memcpy(&p[3], rcv_buffer.constData() + 318, 1);
//    qDebug() << p[3] << "\n\n";
//    qDebug() << "\n\n";
}

void MyUDP::show()
{
    //qDebug() << rpmMax << "\t" << rpm << "\t" << speed;
}

float MyUDP::ret_rpm()
{
    return rpm;
}

float MyUDP::ret_speed()
{
    return speed;
}

float MyUDP::ret_yaw()
{
    //return ((int)yaw);
    return yaw;
}

uint8_t MyUDP::ret_gear()
{
    return gear;
}

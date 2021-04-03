#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <QList>
#include <QSerialPortInfo>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBarRpm->setMinimum(0);
    ui->progressBarRpm->setMaximum(9000);

    this->device = new QSerialPort(this);

   timer1 = new QTimer(this);

   connect(timer1, SIGNAL(timeout()), this, SLOT(run()));
   timer1->start(50);

}

MainWindow::~MainWindow()
{
    delete device;
    delete ui;
}

void MainWindow::run()
{
       //ui->progressBarRpm->setValue(clientUDP->ret_rpm());
       //ui->progressBarRpm->setValue(8000);
       //clientUDP->show();
    on_pushButtonSend_clicked();
}



void MainWindow::on_pushButtonSend_clicked()
{
    //qDebug() << "wyslano UDP";
    //QString text_wpr = ui->lineEditSend->text();
    //ui->lineEditSend->clear();
    //QByteArray dane = text_wpr.toLocal8Bit();
        //clientUDP->SendUDP(dane);
    //run();
    char buf[20];

//    static int spd = 0;
//    static int rpmm = 4000;

//    spd++, rpmm++;
//if(spd==200) spd = 0;
    //sprintf(buf, "%03d%04d", spd, rpmm);

    int sp = static_cast<int>(clientUDP->ret_speed());
    int rp = static_cast<int>(clientUDP->ret_rpm());
if(sp<0) sp = -sp;
    sprintf(buf, "%03d%04d", sp,  rp);
    sendMessageToDevice(buf);

//qDebug() << rp;
//qDebug() << sp;

}

void MainWindow::on_lineEditSend_returnPressed()
{
    on_pushButtonSend_clicked();
}

void MainWindow::on_pushButtonSearch_clicked()
{
    this->addToLogs("Szukam urządzeń...");
    QList<QSerialPortInfo> devices;
    devices = QSerialPortInfo::availablePorts();

    for(int i = 0; i < devices.count(); i++) {
      this->addToLogs("Znalazłem urządzenie: " + devices.at(i).portName() + " " + devices.at(i).description());
      ui->comboBoxDevices->addItem(devices.at(i).portName() + " " + devices.at(i).description());
    }
}

void MainWindow::on_pushButtonLink_clicked()
{
    if(ui->comboBoxDevices->count() == 0)
    {
        this->addToLogs("Nie wykryto żadnych urządzeń!");
        return;
    }

    QString comboBoxQString = ui->comboBoxDevices->currentText();
    QStringList portList = comboBoxQString.split(0x20);
    QString portName = portList.first();

    this->device->setPortName(portName);

    // OTWÓRZ I SKONFIGURUJ PORT:
    if(!device->isOpen())
    {

        if(device->open(QSerialPort::ReadWrite))
        {
            this->device->setBaudRate(QSerialPort::Baud115200);
            this->device->setDataBits(QSerialPort::Data8);
            this->device->setParity(QSerialPort::NoParity);
            this->device->setStopBits(QSerialPort::OneStop);
            this->device->setFlowControl(QSerialPort::NoFlowControl);
            // CONNECT:
            connect(this->device, SIGNAL(readyRead()),this, SLOT(readFromPort()));
            this->addToLogs("Otwarto port szeregowy.");
        }
        else
        {
            this->addToLogs("Otwarcie portu szeregowego się nie powiodło!");
        }
    }
    else
    {
        this->addToLogs("Port już jest otwarty!");
        return;
    }
}

void MainWindow::on_pushButtonClose_clicked()
{
    if(this->device->isOpen()) {
      this->device->close();
      this->addToLogs("Zamknięto połączenie.");
    }
    else {
      this->addToLogs("Port nie jest otwarty!");
      return;
    }
}

void MainWindow::addToLogs(QString message)
{
    ui->textEditLogi->append(message);
}

void MainWindow::sendMessageToDevice(QString message)
{
    QString canFrame;
    if(this->device->isOpen() && this->device->isWritable()) {

        this->device->write(message.toStdString().c_str());
    }
    else {
        this->addToLogs("Nie mogę wysłać wiadomości. Port nie jest otwarty!");
    }
   //this->addToLogs("Wysyłam do NXT: " + message);

}


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSerialPort>
#include "myudp.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    MyUDP *clientUDP;
    QTimer *timer1;

public slots:
    void on_pushButtonSend_clicked();

    void run();

    void on_lineEditSend_returnPressed();

private slots:
    void on_pushButtonSearch_clicked();

    void on_pushButtonLink_clicked();

    void on_pushButtonClose_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *device;
    void addToLogs(QString message);
    void sendMessageToDevice(QString message);

};
#endif // MAINWINDOW_H

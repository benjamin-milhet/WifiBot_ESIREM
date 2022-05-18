#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->connect_b = ui->connect_button;
    this->speed_slider = ui->speed_slider;

    connect(connect_b, &QPushButton::released, this, &MainWindow::handleButton);
    connect(speed_slider, SIGNAL(valueChanged(int)), this, SLOT(value(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::handleButton()
{
    rob.doConnect();
}



void MainWindow::value(int value)
{
    qDebug() << value;
    rob.DataToSend[6] = value+1;
//    short mycrcsend = Crc16(rob.DataToSend.data()+1,6);
//    rob.DataToSend[7] = (qint64)mycrcsend;
//    rob.DataToSend[8] = (qint64)(mycrcsend >> 8);
}

void MainWindow::on_BWebCam_clicked()
{
    qDebug() << "connection webcam";
    rob.getWebCam();
//    rob.getRequest();
}


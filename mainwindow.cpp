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
    this->_robot.doConnect();
}



void MainWindow::value(int value)
{
    qDebug() << value;
    this->_robot.DataToSend[6] = value+1;
//    short mycrcsend = Crc16(rob.DataToSend.data()+1,6);
//    rob.DataToSend[7] = (qint64)mycrcsend;
//    rob.DataToSend[8] = (qint64)(mycrcsend >> 8);
}

void MainWindow::on_BWebCam_clicked()
{
    qDebug() << "connection webcam";
    this->_robot.getWebCam();
//    rob.getRequest();
}


void MainWindow::on_up_button_pressed()
{
    this->_robot.GoForward();
}


void MainWindow::on_left_button_pressed()
{
    this->_robot.GoLeft();
}


void MainWindow::on_right_button_pressed()
{
    this->_robot.GoRight();
}


void MainWindow::on_down_button_pressed()
{
    this->_robot.GoBackward();
}


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
    connect(this->_robot, SIGNAL(updateUI(QByteArray)), this, SLOT(updateWindows(QByteArray)));


    // Affichage de la batterie
    lcdBattery = new QLCDNumber(this);
    lcdBattery->setDigitCount(3);
    lcdBattery->setGeometry(QRect(5,5,40,30));
    lcdBattery->display(0);

    // Affichage de la vitesse
    lcdSpeed = new QLCDNumber(this);
    lcdSpeed->setDigitCount(3);
    lcdSpeed->setGeometry(QRect(5,50,40,30));
    lcdSpeed->display(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::handleButton()
{
    this->_robot->doConnect();
}



void MainWindow::value(int value)
{
    qDebug() << value;
    this->_robot->DataToSend[6] = value+1;
//    short mycrcsend = Crc16(rob.DataToSend.data()+1,6);
//    rob.DataToSend[7] = (qint64)mycrcsend;
//    rob.DataToSend[8] = (qint64)(mycrcsend >> 8);
}

void MainWindow::on_BWebCam_clicked()
{
    this->view = new QWebEngineView(ui->openGLWidget);
    this->view->load(QUrl("http://192.168.1.106:8080/?action=stream"));
    this->view->resize(571, 361);
    this->view->show();
}


void MainWindow::on_up_button_pressed()
{
    this->_robot->GoForward();
}


void MainWindow::on_left_button_pressed()
{
    this->_robot->GoLeft();
}


void MainWindow::on_right_button_pressed()
{
    this->_robot->GoRight();
}


void MainWindow::on_down_button_pressed()
{
    this->_robot->GoBackward();
}


void MainWindow::on_up_button_released()
{
    this->_robot->Stop();

}


void MainWindow::on_left_button_released()
{
    this->_robot->Stop();

}


void MainWindow::on_right_button_released()
{
    this->_robot->Stop();

}


void MainWindow::on_down_button_released()
{
     this->_robot->Stop();

}


void MainWindow::on_pushButton_clicked()
{
    this->_robot->disConnect();
}


void MainWindow::on_speed_slider_valueChanged(int value)
{
    this->_robot->setSpeed(value);

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    this->updateSpeedValue();

    switch (event->key()) {
    case Qt::Key_W:
        this->_robot->GoForward();
        break;
    case Qt::Key_S:
        this->_robot->GoBackward();
        break;
    case Qt::Key_A:
        this->_robot->GoLeft();
        break;
    case Qt::Key_D:
        this->_robot->GoRight();
        break;
    case Qt::Key_Up:
        this->_webcam.deplacerCamera('H');
        break;
    case Qt::Key_Down:
        this->_webcam.deplacerCamera('B');
        break;
    case Qt::Key_Left:
        this->_webcam.deplacerCamera('G');
        break;
    case Qt::Key_Right:
        this->_webcam.deplacerCamera('D');
        break;

    default:
        this->_robot->Stop();
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    this->_robot->Stop();
}



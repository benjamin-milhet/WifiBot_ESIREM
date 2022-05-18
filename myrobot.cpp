// myrobot.cpp

#include "myrobot.h"

MyRobot::MyRobot(QObject *parent) : QObject(parent) {

    DataToSend.resize(9);
    DataToSend[0] = 255;
    DataToSend[1] = 0x07;
    DataToSend[2] = (qint64)230;
    DataToSend[3] = (qint64)(230 >> 8);
    DataToSend[4] = (qint64)230;
    DataToSend[5] = (qint64)(230 >> 8);
    DataToSend[6] = 80+1;
    short mycrcsend = Crc16(DataToSend.data()+1,6);
    DataToSend[7] = (qint64)mycrcsend;
    DataToSend[8] = (qint64)(mycrcsend >> 8);
    DataReceived.resize(21);
    TimerEnvoi = new QTimer();
    // setup signal and slot
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(MyTimerSlot())); //Send data to wifibot timer
}


//void MyRobot::getWebCam() {
//    socket = new QTcpSocket(this);
//    socket->connectToHost("192.168.1.106", 8080);

//    if(!socket->waitForConnected(5000)) {
//        qDebug() << "Error: " << socket->errorString();
//        return;
//    }
//    TimerEnvoi->start(75);
//}


void MyRobot::doConnect() {
    socket = new QTcpSocket(this); // socket creation
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    qDebug() << "connecting..."; // this is not blocking call
    //socket->connectToHost("LOCALHOST", 15020);
    socket->connectToHost("192.168.1.106", 15020); // connection to wifibot
    // we need to wait...
    if(!socket->waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
        return;
    }
    TimerEnvoi->start(75);

}

void MyRobot::disConnect() {
    TimerEnvoi->stop();
    socket->close();
}

void MyRobot::connected() {
    qDebug() << "connected..."; // Hey server, tell me about you.
}

void MyRobot::disconnected() {
    qDebug() << "disconnected...";
}

void MyRobot::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

void MyRobot::readyRead() {
    qDebug() << "reading..."; // read the data from the socket
    DataReceived = socket->readAll();
    emit updateUI(DataReceived);
    qDebug() << DataReceived[0] << DataReceived[1] << DataReceived[2];
}

void MyRobot::MyTimerSlot() {
    qDebug() << "Timer...";
    while(Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
}


short MyRobot::Crc16(char *addr_tab, unsigned char taille_max) {
    unsigned int Crc = 0xFFFF;
    unsigned int Polynome = 0xA001;
    unsigned int CptOctet = 0;
    unsigned int CptBit = 0;
    unsigned int Parity = 0;

    Crc = 0xFFFF;
    Polynome = 0xA001;
    for ( CptOctet = 0; CptOctet < taille_max ; CptOctet++) {
        Crc ^= *(addr_tab + CptOctet);

        for (CptBit = 0; CptBit <= 7; CptBit++)
        {
            Parity = Crc;
            Crc >>= 1;
            if (Parity%2 == true) Crc ^= Polynome;
        }
    }
    return(Crc);
}


void MyRobot::GoLeft(){

}

void MyRobot::GoRight(){

}

void MyRobot::GoForward(){

}

void MyRobot::GoBackward(){

}

void MyRobot::changeSpeed(){
    
}


// function to do a get request and get the stream from the camera
// void MyRobot::getWebCam() {
//     socket = new QTcpSocket(this);
//     socket->connectToHost("192.168.1.106:8080");



// function to do a get request
void MyRobot::getRequest() {
    QUrl url("192.168.1.106:8080/?action=stream");
    QNetworkRequest request(url);
    QNetworkAccessManager manager;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = manager.get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(getRequestFinished()));
}

// function to do a get request and display the stream from the camera
void MyRobot::getWebCam() {
    socket = new QTcpSocket(this);
    qDebug() << "connect to 192.168.1.106:8080";
    socket->connectToHost("192.168.1.106", 8080);
    qDebug() << "send get request";
//    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

    socket->write("GET /?action=stream\r\n");
    socket->write("User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:100.0) Gecko/20100101 Firefox/100.0\r\n");
    socket->write("Accept: image/avif,image/webp,*/*\r\n");
    socket->write("Accept-Language: fr,fr-FR;q=0.8,en-US;q=0.5,en;q=0.3\r\n");
    socket->write("Accept-Encoding: gzip, deflate\r\n");
    socket->write("Connection: keep-alive\r\n");
    socket->write("Referer: http://192.168.1.106:8080/stream.html\r\n");
    socket->waitForBytesWritten();
    socket->waitForReadyRead();
    qDebug() << "readAll";
    QByteArray data = socket->readAll();
    qDebug() << data;
}

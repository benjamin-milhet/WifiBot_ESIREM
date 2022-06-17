// myrobot.cpp

#include "myrobot.h"

MyRobot::MyRobot(QObject *parent) : QObject(parent) {
    dataLeft = (dataRobot*) malloc(sizeof(dataRobot)); // Information droite du robot
    dataRight = (dataRobot*) malloc(sizeof(dataRobot)); // Information gauche du robot

    // Information a envoyer lors de la connextion du robot -> Le robot ne fait rien
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0x0; // -> vitesse gauche
    DataToSend[3] = 0x0;
    DataToSend[4] = 0x0; // -> vitesse droite
    DataToSend[5] = 0x0;
    DataToSend[6] = 0x0; // -> direction du robot
    DataToSend[7] = 0x0; // -> crc
    DataToSend[8] = 0x0; // -> crc
    DataReceived.resize(21);

    TimerEnvoi = new QTimer();
    // setup signal and slot
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(MyTimerSlot())); //Send data to wifibot timer
}



// Fonction permettanty de se connecter au robot
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

// Fonction permettant de se deconnecter du robot
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

//Fonction permettant de recuperer les information recu par le robot
void MyRobot::readyRead() {
    qDebug() << "reading..."; // read the data from the socket
    DataReceived = socket->readAll();
    //emit updateUI(DataReceived);

    dataLeft->speed = (int)(( DataReceived[1] << 8) + DataReceived[0]);
    if (dataLeft->speed > 32767) dataLeft->speed = dataLeft->speed - 65536;

    dataLeft->batterie = DataReceived[2];
    dataLeft->IR1 = DataReceived[3];
    dataLeft->IR2 = DataReceived[4];

    dataLeft->odometry = ((( (long) DataReceived[8] << 24)) + (( (long) DataReceived[7] << 16))+(( (long) DataReceived[6] << 8))+( (long) DataReceived[5]));


    dataRight->speed=(int)(DataReceived[10] << 8) + DataReceived[9];
    if (dataRight->speed > 32767) dataRight->speed = dataRight->speed - 65536;

    dataRight->batterie = 0;
    dataRight->IR1 = DataReceived[11];
    dataRight->IR2 = DataReceived[12];

    dataRight->odometry = ((( (long) DataReceived[16] << 24)) + (( (long) DataReceived[15] << 16)) + (( (long) DataReceived[14] << 8))+( (long) DataReceived[13]));

    qDebug() << "--------------";
    qDebug() << DataReceived[2];
    qDebug() << dataLeft->batterie;
    qDebug() << dataRight->batterie;
    qDebug() << dataLeft->speed;

    emit updateUI(DataReceived); // On envoi les informations a la mainwindow pour update les infos


}

void MyRobot::MyTimerSlot() {
    qDebug() << "Timer...";
    while(Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
}

//Fonction permettant de calculer le crc pour controler les data envoyer
short MyRobot::Crc16(char *addr_tab, unsigned char taille_max) {
    unsigned int Crc = 0xFFFF;
    unsigned int Polynome = 0xA001;
    unsigned int CptOctet = 0;
    unsigned int CptBit = 0;
    unsigned int Parity = 0;

    Crc = 0xFFFF;
    Polynome = 0xA001;
    for ( CptOctet = 1; CptOctet < taille_max ; CptOctet++) {
        Crc ^= (unsigned char)(addr_tab[CptOctet]);

        for (CptBit = 0; CptBit <= 7; CptBit++)
        {
            Parity = Crc;
            Crc >>= 1;
            if (Parity%2 == true) Crc ^= Polynome;
        }
    }
    return(Crc);
}

// Permet au robot de se deplacer a gauche
void MyRobot::GoLeft() {
    DataToSend[2] = this->speed;
    DataToSend[4] = this->speed;
    DataToSend[6] = 16;

    short mycrcsend = Crc16(DataToSend.data(), 7);
    DataToSend[7] = mycrcsend;
    DataToSend[8] = mycrcsend >> 8;
}

// Permet au robot de se deplacer a droite
void MyRobot::GoRight() {
    DataToSend[2] = this->speed;
    DataToSend[4] = this->speed;
    DataToSend[6] = 64;

    short mycrcsend = Crc16(DataToSend.data(), 7);
    DataToSend[7] = mycrcsend;
    DataToSend[8] = mycrcsend >> 8;
}

// Permet au robot de se deplacer a en avant
void MyRobot::GoForward() {
    DataToSend[2] = this->speed;
    DataToSend[4] = this->speed;
    DataToSend[6] = 81;

    short mycrcsend = Crc16(DataToSend.data(), 7);
    DataToSend[7] = mycrcsend;
    DataToSend[8] = mycrcsend >> 8;

}

// Permet au robot de se deplacer a gauche
void MyRobot::GoBackward() {
    DataToSend[2] = this->speed;
    DataToSend[4] = this->speed;
    DataToSend[6] = 0;

    short mycrcsend = Crc16(DataToSend.data(), 7);
    DataToSend[7] = mycrcsend;
    DataToSend[8] = mycrcsend >> 8;
}

// Permet d'arreter le robot
void MyRobot::Stop() {
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0x0;
    DataToSend[3] = 0x0;
    DataToSend[4] = 0x0;
    DataToSend[5] = 0x0;
    DataToSend[6] = 80;

    short mycrcsend = Crc16(DataToSend.data()+1,6);
    DataToSend[7] = (qint64)mycrcsend;
    DataToSend[8] = (qint64)(mycrcsend >> 8);
}

//Permet de changer la vitesse
void MyRobot::setSpeed(int s){
    this->speed = s;
}

//Permet de recueprer la vitesse
int MyRobot::getSpeed() {
    return this->speed;
}



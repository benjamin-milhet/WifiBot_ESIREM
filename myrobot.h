#ifndef MYROBOT_H
#define MYROBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>
#include <QNetworkRequest>
#include <QNetworkReply>

typedef struct dataRobot {
    int speed;
    qint8 batterie;
    int IR1;
    int IR2;
    double odometry;
}dataRobot;

class MyRobot : public QObject {
    Q_OBJECT
public:
    explicit MyRobot(QObject *parent = 0);
    void doConnect();
    void disConnect();
    int getSpeed();
    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;

    dataRobot *dataLeft, *dataRight;


signals:
    void updateUI(const QByteArray Data);
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void MyTimerSlot();
    void GoLeft();
    void GoRight();
    void GoForward();
    void GoBackward();
    void Stop();
    void setSpeed(int s);
    short Crc16(char *buf, unsigned char len);

private:
    QTcpSocket *socket;
    QTimer *TimerEnvoi;
    int speed = 120;
};

#endif // MYROBOT_H

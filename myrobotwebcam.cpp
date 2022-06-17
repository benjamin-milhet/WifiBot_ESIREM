#include "myrobotwebcam.h"

myRobotWebCam::myRobotWebCam(QObject *parent): QObject{parent}
{

}

void myRobotWebCam::deplacerCamera(char direction)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    switch (direction) {
    case 'D':
        manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-200")));
        break;
    case 'G':
        manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=200")));
        break;
    case 'H':
        manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-200")));
        break;
    case 'B':
        manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=200")));
        break;
    default:
        break;
    }
}

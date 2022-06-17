#include "myrobotwebcam.h"

myRobotWebCam::myRobotWebCam(QObject *parent): QObject{parent}
{

}

// Permert de tourner la camera suivant l'ordre donne
void myRobotWebCam::deplacerCamera(char direction)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    switch (direction) {
    case 'D': // Permet de tourner la camera a droite
        manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-200")));
        break;
    case 'G': // Permet de tourner la camera a gauche
        manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=200")));
        break;
    case 'H': // Permet de tourner la camera en haut
        manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-200")));
        break;
    case 'B': // Permet de tourner la camera en bas
        manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=200")));
        break;
    default:
        break;
    }
}

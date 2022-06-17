#ifndef MYROBOTWEBCAM_H
#define MYROBOTWEBCAM_H

#include <QObject>
#include <QNetworkAccessManager>

class myRobotWebCam : public QObject
{
    Q_OBJECT
public:
    explicit myRobotWebCam(QObject *parent = nullptr);
    void deplacerCamera(char direction);


signals:

};

#endif // MYROBOTWEBCAM_H

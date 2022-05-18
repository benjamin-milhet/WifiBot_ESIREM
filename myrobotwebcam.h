#ifndef MYROBOTWEBCAM_H
#define MYROBOTWEBCAM_H

#include <QObject>

class myRobotWebCam : public QObject
{
    Q_OBJECT
public:
    explicit myRobotWebCam(QObject *parent = nullptr);

signals:

};

#endif // MYROBOTWEBCAM_H

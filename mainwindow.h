#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qpushbutton.h>
#include <myrobot.h>
#include <myRobotWebCam.h>
#include <QSlider>
#include <QDebug>
#include <QKeyEvent>
#include <QLCDNumber>
#include <QWebEngineView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:

private slots:
    void handleButton();
    void value(int);

    void on_BWebCam_clicked();

    void on_up_button_pressed();

    void on_left_button_pressed();

    void on_right_button_pressed();

    void on_down_button_pressed();

    void on_up_button_released();

    void on_left_button_released();

    void on_right_button_released();

    void on_down_button_released();

    void on_pushButton_clicked();

    void on_speed_slider_valueChanged(int value);


private:
    Ui::MainWindow *ui;
    QPushButton *connect_b;
    QSlider *speed_slider;
    QPushButton BWebCam;
    MyRobot *_robot = new MyRobot();
    myRobotWebCam _webcam = myRobotWebCam();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    QLCDNumber *lcdBattery;
    QLCDNumber *lcdSpeed;
    QWebEngineView *view;


};
#endif // MAINWINDOW_H

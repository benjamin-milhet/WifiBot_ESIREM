#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qpushbutton.h>
#include <myrobot.h>
#include <QSlider>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleButton();
    void value(int);

    void on_BWebCam_clicked();

private:
    Ui::MainWindow *ui;
    QPushButton *connect_b;
    QSlider *speed_slider;
    QPushButton BWebCam;
    MyRobot rob = MyRobot();
};
#endif // MAINWINDOW_H

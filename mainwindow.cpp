#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->connect_b = ui->connect_button;
    connect(connect_b, &QPushButton::released, this, &MainWindow::handleButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::handleButton()
{
    rob.doConnect();
}


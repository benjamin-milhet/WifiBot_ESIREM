#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->connect_b = ui->connect_button;
    this->speed_slider = ui->speed_slider;

    connect(connect_b, &QPushButton::released, this, &MainWindow::handleButton);
    connect(speed_slider, SIGNAL(valueChanged(int)), this, SLOT(value(int)));
    connect(this->_robot, SIGNAL(updateUI(QByteArray)), this, SLOT(updateWindows(QByteArray)));


    // Affichage de la batterie
    lcdBattery = new QLCDNumber(this); //creation de l'affichage
    lcdBattery->setDigitCount(3); // nombre de valeur sur l'ecran LCD
    lcdBattery->setGeometry(QRect(150,5,40,30)); // emplacement et taille de l'ecran LCD
    lcdBattery->display(0); // affichage de l'ecran lcd avec la valeur 0

    // Affichage de la vitesse
    lcdSpeed = new QLCDNumber(this);
    lcdSpeed->setDigitCount(3); // nombre de valeur sur l'ecran LCD
    lcdSpeed->setGeometry(QRect(150,55,40,30)); // emplacement et taille de l'ecran LCD
    lcdSpeed->display(0); // affichage de l'ecran lcd avec la valeur 0

    // Affichage de la valeur du capteur infrarouge en haut a gauche
    IRHautGauche = new QLCDNumber(this);
    IRHautGauche->setDigitCount(3); // nombre de valeur sur l'ecran LCD
    IRHautGauche->setGeometry(QRect(150,105,40,30)); // emplacement et taille de l'ecran LCD
    IRHautGauche->display(0); // affichage de l'ecran lcd avec la valeur 0

    // Affichage de la valeur du capteur infrarouge en haut a droite
    IRHautDroit = new QLCDNumber(this);
    IRHautDroit->setDigitCount(3); // nombre de valeur sur l'ecran LCD
    IRHautDroit->setGeometry(QRect(150,155,40,30)); // emplacement et taille de l'ecran LCD
    IRHautDroit->display(0); // affichage de l'ecran lcd avec la valeur 0

    // Affichage de la valeur du capteur infrarouge en bas a gauche
    IRBas = new QLCDNumber(this);
    IRBas->setDigitCount(3); // nombre de valeur sur l'ecran LCD
    IRBas->setGeometry(QRect(150,205,40,30)); // emplacement et taille de l'ecran LCD
    IRBas->display(0); // affichage de l'ecran lcd avec la valeur 0
}

MainWindow::~MainWindow()
{
    delete ui;
}

// action du bouton se connecterau robot si personne a casse le robot
void MainWindow::handleButton()
{
    this->_robot->doConnect();
}



void MainWindow::value(int value)
{
    qDebug() << value;
    this->_robot->DataToSend[6] = value+1;
}

// permet de se connecter au a la webcam du robot et l'afficher
void MainWindow::on_BWebCam_clicked()
{
    this->view = new QWebEngineView(ui->openGLWidget); // creation de l'element graphique ou sera l'image de la webcam
    this->view->load(QUrl("http://192.168.1.106:8080/?action=stream")); // Recuperation du flux d el a webcam
    this->view->resize(571, 361); // Redimensionnemnt de la fenetre d'affichage de la webcam
    this->view->show(); // Affichage de la webcam
}

// Action du bouton avancer le robot
void MainWindow::on_up_button_pressed()
{
    this->_robot->GoForward();
}

// Action du bouton aller a gauche du robot
void MainWindow::on_left_button_pressed()
{
    this->_robot->GoLeft();
}

// Action du bouton aller a droite du robot
void MainWindow::on_right_button_pressed()
{
    this->_robot->GoRight();
}

// Action du bouton aller en arriere du robot
void MainWindow::on_down_button_pressed()
{
    this->_robot->GoBackward();
}

// Permet d'arreter le robot lorsque l'on lache une touche
void MainWindow::on_up_button_released()
{
    this->_robot->Stop();

}

// Permet d'arreter le robot lorsque l'on lache une touche
void MainWindow::on_left_button_released()
{
    this->_robot->Stop();

}

// Permet d'arreter le robot lorsque l'on lache une touche
void MainWindow::on_right_button_released()
{
    this->_robot->Stop();

}

// Permet d'arreter le robot lorsque l'on lache une touche
void MainWindow::on_down_button_released()
{
     this->_robot->Stop();

}

//Action du bouton deconnecter pour se deconnecter du robot
void MainWindow::on_pushButton_clicked()
{
    this->_robot->disConnect();
}

// Action lors de la modification du slider pour changer la vitesse du robot
void MainWindow::on_speed_slider_valueChanged(int value)
{
    this->_robot->setSpeed(value);

}

// Recuperation des tocuhes du clavier et reatribution des actions
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_W:
        this->_robot->GoForward();
        break;
    case Qt::Key_S:
        this->_robot->GoBackward();
        break;
    case Qt::Key_A:
        this->_robot->GoLeft();
        break;
    case Qt::Key_D:
        this->_robot->GoRight();
        break;
    case Qt::Key_Up:
        this->_webcam.deplacerCamera('H');
        break;
    case Qt::Key_Down:
        this->_webcam.deplacerCamera('B');
        break;
    case Qt::Key_Left:
        this->_webcam.deplacerCamera('G');
        break;
    case Qt::Key_Right:
        this->_webcam.deplacerCamera('D');
        break;

    default:
        this->_robot->Stop();
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    this->_robot->Stop();
}

//Uptade des informations recu par le robot
void MainWindow::updateWindows(const QByteArray data)
{
    lcdBattery->display((quint8)data[2]); // update de la batterie
    lcdSpeed->display((quint8)data[1]); // update de la vitesse
    IRHautGauche->display((quint8)data[3]); // update du capteur IR haut gauche
    IRHautDroit->display((quint8)data[11]); // update du capteur IR haut droit
    IRBas->display((quint8)data[4]); // update du capteur IR bas gauche
}

// Action du bouton pour tourner la camera vers la gauche
void MainWindow::on_left_button_2_clicked()
{
    this->_webcam.deplacerCamera('G');
}

// Action du bouton pour tourner la camera vers le haut
void MainWindow::on_up_button_2_clicked()
{
    this->_webcam.deplacerCamera('H');
}

// Action du bouton pour tourner la camera vers la droite
void MainWindow::on_right_button_2_clicked()
{
    this->_webcam.deplacerCamera('D');
}

// Action du bouton pour tourner la camera vers le bas
void MainWindow::on_down_button_2_clicked()
{
    this->_webcam.deplacerCamera('B');
}


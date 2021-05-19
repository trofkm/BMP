#include "mw.h"
#include "ui_mw.h"
#include <mypicture.h>

MW::MW(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MW)
{
    ui->setupUi(this);
}

MW::~MW()
{
    delete ui;
}


void MW::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open the file");//Получаем имя файла
    ui->statusbar->showMessage(filename);
    Bitmap bmp(filename.toStdString());
    //ui->PictureView->setFixedSize(bmp.W()+15,bmp.H()+15);//mb don't even want
    QImage image(filename);
    QGraphicsScene* scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(image));
    ui->PictureView->setScene(scene);
    ui->PictureView->show();//change from show to showFullScreen

}

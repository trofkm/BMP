#include "mw.h"
#include "ui_mw.h"

MW::MW(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MW)
{
    ui->setupUi(this);
}

MW::~MW()
{
    //delete bmp;
    delete ui;
}


void MW::on_actionOpen_triggered()
{
    filename = QFileDialog::getOpenFileName(this,"Open the file");//Get filename
    ui->statusbar->showMessage(filename);

    bmp = new Bitmap(filename.toStdString());
    QImage image(filename);
    QGraphicsScene* scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(image));
    ui->PictureView->setScene(scene);
    ui->PictureView->show();//change from show to showFullScreen

}

void MW::on_InverseColors_Btn_clicked()
{
   // SecUi = new SecondWIndow(this);
    SecondWindow window;
    window.setResolution(QString::number(bmp->W())+"x"+QString::number(bmp->H()));
    window.setModal(true);
    window.exec();



   QImage image(filename);
    QGraphicsScene* scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(image));
    ui->PictureView->setScene(scene);
    ui->PictureView->show();
}

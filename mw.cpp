#include "mw.h"
#include "ui_mw.h"

bool opened = false;
int backgroundChanged = 1;
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
    QString filename = QFileDialog::getOpenFileName(this,"Open the file");//Get filename
    if(filename!=""){
        opened = true;
        ui->statusbar->showMessage(filename);

        bmp = std::make_unique<Bitmap>(filename.toStdString());
        QImage image(filename);
        QGraphicsScene* scene = new QGraphicsScene;
        scene->addPixmap(QPixmap::fromImage(image));
        ui->PictureView->setScene(scene);
        ui->PictureView->show();//change from show to showFullScreen
    }
}

void MW::on_InverseColors_Btn_clicked()
{
    if(opened)
    {
        mode = 0;
        SecondWindow window;
        window.setResolution("Image size: " +QString::number(bmp->W()-1)+"x"+QString::number(bmp->H()-1));
        window.setModal(true);
        window.exec();

        QImage image(QString::fromStdString(bmp->getFilename()));
        QGraphicsScene* scene = new QGraphicsScene;
        scene->addPixmap(QPixmap::fromImage(image));
        ui->PictureView->setScene(scene);
        ui->PictureView->show();
    }
}

void MW::on_ToMonochrome_btn_clicked()
{
    if(opened)
    {
        mode = 1;
        SecondWindow window;
        window.setResolution("Image size: " + QString::number(bmp->W()-1)+"x"+QString::number(bmp->H()-1));
        window.setModal(true);
        window.exec();

        QImage image(QString::fromStdString(bmp->getFilename()));
        QGraphicsScene* scene = new QGraphicsScene;
        scene->addPixmap(QPixmap::fromImage(image));
        ui->PictureView->setScene(scene);
        ui->PictureView->show();
    }
}

void MW::on_Vector_Btn_clicked()
{
    if (opened)
    {
        VectorWindow window;
        window.setResolution("Image size: " +QString::number(bmp->W()-1)+"x"+QString::number(bmp->H()-1));
        window.setModal(true);
        window.exec();

        QImage image(QString::fromStdString(bmp->getFilename()));
        QGraphicsScene* scene = new QGraphicsScene;
        scene->addPixmap(QPixmap::fromImage(image));
        ui->PictureView->setScene(scene);
        ui->PictureView->show();
    }

}

void MW::on_CutImage_btn_clicked()
{
    if (opened&&backgroundChanged>0)
    {
        mode = 0;
        ChangeImage window;
        window.setModal(true);
        window.setWindowTitle("Cut image");
        window.exec();

        QImage image(QString::fromStdString(bmp->getFilename()));
        QGraphicsScene* scene = new QGraphicsScene;
        scene->addPixmap(QPixmap::fromImage(image));
        ui->PictureView->setScene(scene);
        ui->PictureView->show();
        backgroundChanged--;
    }

}

void MW::on_IncreaseImage_btn_clicked()
{
    if (opened)
    {
        backgroundChanged++;
        mode = 1;
        ChangeImage window;
        window.setModal(true);
        window.setWindowTitle("Add background");
        window.exec();

        QImage image(QString::fromStdString(bmp->getFilename()));
        QGraphicsScene* scene = new QGraphicsScene;
        scene->addPixmap(QPixmap::fromImage(image));
        ui->PictureView->setScene(scene);
        ui->PictureView->show();
    }

}

void MW::on_actionSave_as_triggered()
{
    if (opened)
    {
        QString filename =QFileDialog::getSaveFileName(this);
        int index = filename.indexOf(".bmp");
        if(index==-1)filename+=".bmp";
        bmp->SaveImage(filename.toStdString());
    }

}

void MW::on_courseDef_btn_clicked()
{

    if(opened){
        QString filename = QFileDialog::getOpenFileName(this,"Open the file");//Get filename
        if(filename!=""){
            auto otherBmp = std::make_unique<Bitmap>(filename.toStdString());
            bmp->MergeImage(std::move(otherBmp));
            QImage image(QString::fromStdString(bmp->getFilename()));
            QGraphicsScene* scene = new QGraphicsScene;
            scene->addPixmap(QPixmap::fromImage(image));
            ui->PictureView->setScene(scene);
            ui->PictureView->show();
        }
    }
}





void MW::on_CutArea_btn_clicked()
{
   if(opened){
       mode = 10;
       SecondWindow window;
       window.setResolution("Image size: " + QString::number(bmp->W())+"x"+QString::number(bmp->H()));
       window.setModal(true);
       window.exec();
       QImage image(QString::fromStdString(bmp->getFilename()));
       QGraphicsScene* scene = new QGraphicsScene;
       scene->addPixmap(QPixmap::fromImage(image));
       ui->PictureView->setScene(scene);
       ui->PictureView->show();
   }
}

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
    MW::filename = QFileDialog::getOpenFileName(this,"Open the file");//Получаем имя файла
    ui->statusbar->showMessage(MW::filename);

    MW::bmp = new Bitmap(MW::filename.toStdString());
    QImage image(MW::filename);
    QGraphicsScene* scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(image));
    ui->PictureView->setScene(scene);
    ui->PictureView->show();//change from show to showFullScreen

}

void MW::on_InverseColors_Btn_clicked()
{
   // SecUi = new SecondWIndow(this);
    SecondWindow window;
    window.setResolution(QString::number(MW::bmp->W())+"x"+QString::number(MW::bmp->H()));
    window.setModal(true);
    window.exec();



   QImage image(filename);
    QGraphicsScene* scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(image));
    ui->PictureView->setScene(scene);
    ui->PictureView->show();
}

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
        window.setResolution("Image size: " +QString::number(bmp->W())+"x"+QString::number(bmp->H()));
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

void MW::on_Vector_Btn_clicked()
{
    if (opened)
    {
        VectorWindow window;
        window.setResolution("Image size: " +QString::number(bmp->W())+"x"+QString::number(bmp->H()));
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
            std::unique_ptr<Bitmap>bmp2;
            bmp2 = std::make_unique<Bitmap>(filename.toStdString());
            int maxH = 2*std::max(bmp->H(), bmp2->H());
            int maxW = 2*std::max(bmp->W(), bmp2->W());

            auto Bigtbl =std::make_unique<PixelTable>(maxH, maxW);
            for(int y = 0;y<maxH;++y){
                for(int x = 0;x<maxW;++x){
                    (*Bigtbl)[y][x] = {255,255,255};
                }
            }
            size_t pixelsCount = 0;
            size_t x1=0,x2=0,y1=0,y2=0;
            for(int y = 0;y<maxH;++y){
                for(int x = 0;x<maxW;++x){
                    if(pixelsCount%2==0){
                        if(y1<bmp->H()&&x1<bmp->W()){
                            (*Bigtbl)[y][x] = (*(bmp->tbl))[y1][x1++];
                        std::cout<<y<<":"<<x1<<std::endl;
                        }
                    }
                    else
                    {
                        if(y2<bmp2->H()&&x2<bmp2->W())
                            (*Bigtbl)[y][x] = (*(bmp2->tbl))[y2][x2++];
                    }
                   pixelsCount++;

                }
                x1 = 0;
                x2 = 0;
                y1++;
                y2++;
            }

            bmp->tbl = std::move(Bigtbl);
            bmp->picture.bih.height = maxH;
            bmp->picture.bih.width = maxW;
            bmp->setFilename("out.bmp");
            FILE *to = fopen("out.bmp","wb");
            fwrite(&bmp->picture.bfh, 1, sizeof(BitmapFileHeader), to);
            fwrite(&bmp->picture.bih, 1, sizeof(BitmapInfoHeader), to);
            unsigned int w = (maxW) * sizeof(Rgb) + (maxW * 3) % 4;
            for (size_t i = 0; i < maxH; ++i)
            {
                fwrite((*(bmp->tbl))[i], 1, w, to);
            }
            fclose(to);




            QImage image("out.bmp");
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

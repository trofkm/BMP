#include "changeimage.h"
#include "ui_changeimage.h"

ChangeImage::ChangeImage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeImage)
{
    ui->setupUi(this);
}

ChangeImage::~ChangeImage()
{
    delete ui;
}
void ChangeImage::on_leftDown_btn_clicked()
{
    bmp->setFilename("out.bmp");
    if (mode==0){
        bmp->DecreaseImage(1);
        this->close();
    }
    else{
        QColor clr = QColorDialog::getColor();
        Rgb BackgroundColor;
        BackgroundColor.r = clr.red();
        BackgroundColor.g = clr.green();
        BackgroundColor.b = clr.blue();
        bmp->AddBackground(BackgroundColor,1);
        this->close();
    }
}

void ChangeImage::on_LeftUp_btn_clicked()
{
    bmp->setFilename("out.bmp");
    if (mode==0){
        bmp->DecreaseImage(2);
        this->close();
    }
    else{
        QColor clr = QColorDialog::getColor();
        Rgb BackgroundColor;
        BackgroundColor.r = clr.red();
        BackgroundColor.g = clr.green();
        BackgroundColor.b = clr.blue();
        bmp->AddBackground(BackgroundColor,2);
        this->close();
    }
}



void ChangeImage::on_RightUp_btn_clicked()
{
    bmp->setFilename("out.bmp");
    if (mode==0){
        bmp->DecreaseImage(3);
        this->close();
    }
    else{
        QColor clr = QColorDialog::getColor();
        Rgb BackgroundColor;
        BackgroundColor.r = clr.red();
        BackgroundColor.g = clr.green();
        BackgroundColor.b = clr.blue();
        bmp->AddBackground(BackgroundColor,3);
        this->close();
    }
}

void ChangeImage::on_RightDown_btn_clicked()
{
    bmp->setFilename("out.bmp");
    if (mode==0){
        bmp->DecreaseImage(4);
        this->close();
    }
    else{
        QColor clr = QColorDialog::getColor();
        Rgb BackgroundColor;
        BackgroundColor.r = clr.red();
        BackgroundColor.g = clr.green();
        BackgroundColor.b = clr.blue();
        bmp->AddBackground(BackgroundColor,4);
        this->close();
    }
}

void ChangeImage::on_Center_clicked()
{
    bmp->setFilename("out.bmp");
    if (mode==0){
        bmp->DecreaseImage(5);
        this->close();
    }
    else{
        QColor clr = QColorDialog::getColor();
        Rgb BackgroundColor;
        BackgroundColor.r = clr.red();
        BackgroundColor.g = clr.green();
        BackgroundColor.b = clr.blue();
        bmp->AddBackground(BackgroundColor,5);

        this->close();
    }
}

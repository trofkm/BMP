#include "secondwindow.h"
#include "ui_secondwindow.h"

SecondWindow::SecondWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
}
void SecondWindow::setResolution(QString resolution){
    ui->SizeLbl->setText(resolution);
}
SecondWindow::~SecondWindow()
{
    delete ui;
}



void SecondWindow::on_Inverse_btn_clicked()
{
    if (mode==0)
        bmp->InverseColors({ui->X1->text().toInt(),ui->Y1->text().toInt()},{ui->X2->text().toInt(),ui->Y2->text().toInt()});
    else if(mode==1){
        bmp->ToMonochrome({ui->X1->text().toInt(),ui->Y1->text().toInt()},{ui->X2->text().toInt(),ui->Y2->text().toInt()});
    }
    bmp->setFilename("out.bmp");
    this->close();
}

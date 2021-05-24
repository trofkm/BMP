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
    MW::bmp->InverseColors({ui->X1->text().toInt(),ui->Y1->text().toInt()},{ui->X2->text().toInt(),ui->Y2->text().toInt()});
    MW::filename = "out.bmp";
    this->close();
}

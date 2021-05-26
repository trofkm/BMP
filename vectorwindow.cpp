#include "vectorwindow.h"
#include "ui_vectorwindow.h"

VectorWindow::VectorWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VectorWindow)
{
    ui->setupUi(this);
}

VectorWindow::~VectorWindow()
{
    delete ui;
}

void VectorWindow::setResolution(QString resolution){
    ui->SizeLbl->setText(resolution);
}

void VectorWindow::on_color_btn_clicked()
{
    QColor clr = QColorDialog::getColor();

    color.r = clr.red();
    color.g = clr.green();
    color.b = clr.blue();

}

void VectorWindow::on_Inverse_btn_clicked()
{
    bmp->DrawVector({ui->X1->text().toInt(),ui->Y1->text().toInt()},{ui->X2->text().toInt(),ui->Y2->text().toInt()},color,ui->LineWidth->text().toInt());
    bmp->setFilename("out.bmp");
    this->close();
}

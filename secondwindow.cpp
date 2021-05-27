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
    unsigned int x1 = ui->X1->text().toInt();
    unsigned int x2 = ui->X2->text().toInt();
    unsigned int y1 = ui->Y1->text().toInt();
    unsigned int y2 = ui->Y2->text().toInt();
    if(x1<0||x1>bmp->W()||x2<0||x2>bmp->W()||y1<0||y1>bmp->H()||y2<0||y2>bmp->H())
    {
       QMessageBox::warning(this,"Warning","Values are not correct");
    }
    else
    {
        if (mode==0)
            bmp->InverseColors({x1,y1},{x2,y2});
        else if(mode==1){
            bmp->ToMonochrome({x1,y1},{x2,y2});
        }
        bmp->setFilename("out.bmp");
        this->close();

    }


}

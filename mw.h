#ifndef MW_H
#define MW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QColorDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include "secondwindow.h"
#include "mypicture.h"
#include "vectorwindow.h"
#include "changeimage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MW; }
QT_END_NAMESPACE

class MW : public QMainWindow
{
    Q_OBJECT

public:
    MW(QWidget *parent = nullptr);
    ~MW();



private slots:
    void on_actionOpen_triggered();

    void on_InverseColors_Btn_clicked();

    void on_ToMonochrome_btn_clicked();

    void on_Vector_Btn_clicked();

    void on_CutImage_btn_clicked();

    void on_IncreaseImage_btn_clicked();


    void on_actionSave_as_triggered();

private:
    Ui::MW *ui;

};
#endif  //MW_H
